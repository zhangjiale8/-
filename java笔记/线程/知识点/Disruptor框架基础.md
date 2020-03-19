# Disruptor学习

在上一篇文章中，笔者提到了log4j2中的异步logger。[通过测试数据来看](https://www.jianshu.com/p/3098942fbcbf)，在使用异步logger后，打印日志的时间明显缩短，系统响应时间得到了巨大的提升。

那么，disruptor究竟是什么，为什么它可以提升系统的性能？

## 1.1 Disruptor简介

![img](\java笔记\线程\image\disruptor01.png)

**Disruptor是一个开源框架，研发的初衷是为了解决高并发下列队锁的问题**，最早由LMAX（一种新型零售金融交易平台）提出并使用，能够在无锁的情况下实现队列的并发操作，并号称能够在一个线程里每秒处理6百万笔订单（我是不相信）。

**队列的特性：先进先出（FIFO）**--先进入队列的元素先出队列（可以理解为我们生活中的排队情况，早办完，早滚蛋）。生产者(Producer)往队列里发布(publish)事件，消费者(Consumer)获得通知，消费事件；如果队列中没有事件时，消费者堵塞，直到生产者发布了新事件。

说到队列，那就不得不提到Java中的concurrent包，其主要实现包括ArrayBlockingQueue、LinkedBlockingQueue、ConcurrentLinkedQueue、LinkedTransferQueue。下面，简单介绍下：

```css
ArrayBlockingQueue：基于数组形式的队列，通过加锁的方式，来保证多线程情况下数据的安全；

LinkedBlockingQueue：基于链表形式的队列，也通过加锁的方式，来保证多线程情况下数据的安全；

ConcurrentLinkedQueue：基于链表形式的队列，通过compare and swap(简称CAS)协议的方式，
来保证多线程情况下数据的安全，不加锁，主要使用了Java中的sun.misc.Unsafe类来实现；

LinkedTransferQueue：同上；
```

通过查看以上4个类的源码，可以发现：

（1）使用CAS协议实现队列的类，都是无界的，无法保证队列的长度，理论上来说可以是无限扩展，那么如果生产者生产过快，消费者还没来得及消费，最终可能会导致内存溢出，影响系统稳定；

（2）而使用加锁实现队列的类，虽然是有界的（可以设置队列的大小），但是有锁的存在，性能上有了很大的影响，线程由于锁的竞争被挂起，直到锁的释放，才能恢复。此外，由于伪共享的存在，也会影响性能

而**Disruptor解决了以上的问题，实现了无锁有界队列操作**。主要是使用了环形数组（ringbuffer）、CAS、缓存行填充、解决伪共享等技术，接下来我们一一讲解；

## 1.2 Disruptor结构

在讲解disruptor所使用的相关技术之前，我觉得有必要简单的介绍下的Disruptor结构！

前面介绍了，Disruptor是一个开源的框架，可以在无锁的情况下对队列进行操作，那么这个队列的设计就是Disruptor的核心所在；

![img](\java笔记\线程\image\disruptor02.png)

在Disruptor中，采用了**RingBuffer**来作为队列的数据结构，RingBuffer就是一个环形的数组，既然是数组，我们便可对其设置大小。在这个ringBuffer中，除了数组之外，还有一个**序列号**，是用来指向数组中的下一个可用元素，供生产者使用或者消费者使用，也就是生产者可以生产的地方，或者消费者可以消费的地方。（**序列号和数组索引**是两个概念，别搞错了）

Disruptor使用数组作为队列的另一个好处，就是可以快速定位到所需元素，通常使用取摸运算（序列号%数组大小=所需元素角标），但在Disruptor中使用的是**位运算**（具体实现：UNSAFE.getObject(entries, REF_ARRAY_BASE + ((sequence & indexMask) << REF_ELEMENT_SHIFT))），效率更高，定位更快；此外，在**Disruptor中数组内的元素并不会被删除，而是新数据来覆盖原有数据**；

## 1.3 Disruptor代码简单实现

我们就以一个简单例子来实现Disruptor：生产者传递一个long类型变量给消费者，消费者将这个变量打印出来。

单生产者，单消费者模型：

（1）向ringbuffer中插入的事件元素：就是在对象中放了一个long变量

```csharp
public class LongEvent {

    private long value;

    public long getValue() {
        return value;
    }

    public void setValue(long value) {
        this.value = value;
    }
}
```

（2）事件生产工厂：生产事件存入ringbuffer中

```java
public class LongEventFactory implements EventFactory<LongEvent> {

    public LongEvent newInstance() {
        return new LongEvent();
    }
}
```

（3）事件处理器，也就是消费者，就是将事件的值打印出来

```java
public class LongEventHandler implements EventHandler<LongEvent> {

    public void onEvent(LongEvent event, long sequence, boolean endOfBatch) throws Exception {
        System.out.println("Event："+event.getValue());
    }
}
```

（4）主函数：创建生产者，向ringbuffer中填充元素

```csharp
public class DisruptorMain {

    public static void main(String[] agrs) throws InterruptedException {
        
        //创建线程池：
        Executor executor = Executors.newCachedThreadPool();

        //事件生产工厂：
        LongEventFactory longEventFactory = new LongEventFactory();

        //ringbuffer的大小：
        int bufferSize = 256;

        //实例化disruptor对象：初始化ringbuffer
         Disruptor<LongEvent> disruptor = new Disruptor<LongEvent>(longEventFactory, bufferSize, executor,ProducerType.SINGLE, new BlockingWaitStrategy());

        //设置事件的执行者：(单消费者)
        disruptor.handleEventsWith(new LongEventHandler());
        
        //disruptor启动：
        disruptor.start();

        RingBuffer<LongEvent> ringBuffer = disruptor.getRingBuffer();

        //设置事件单生产者：
        for(int x = 0;x<256; x++){
            // 获取下一个可用位置的下标
            long sequence = ringBuffer.next();  
            try{
                // 返回可用位置的元素
                LongEvent event = ringBuffer.get(sequence); 
                // 设置该位置元素的值
                event.set(x); 
            }finally{
                //发布事件 
                ringBuffer.publish(sequence);
            }
            Thread.sleep(10);
        }
    }
}
```

## 1.4 Disruptor主要实现类

通过以上代码，我们来简单的分析下Disruptor的构成：

```css
Disruptor：Disruptor的入口，主要封装了环形队列RingBuffer、消费者集合ConsumerRepository的引用；主要提供了获取环形队列、添加消费者、生产者向RingBuffer中添加事件（可以理解为生产者生产数据）的操作；

RingBuffer：Disruptor中队列具体的实现，底层封装了Object[]数组；在初始化时，会使用Event事件对数组进行填充，填充的大小就是bufferSize设置的值；此外，该对象内部还维护了Sequencer（序列生产器）具体的实现；

Sequencer：序列生产器，分别有MultiProducerSequencer（多生产者序列生产器） 和 SingleProducerSequencer（单生产者序列生产器）两个实现类。上面的例子中，使用的是SingleProducerSequencer；在Sequencer中，维护了消费者的Sequence（序列对象）和生产者自己的Sequence（序列对象）；以及维护了生产者与消费者序列冲突时候的等待策略WaitStrategy；

Sequence：序列对象，内部维护了一个long型的value，这个序列指向了RingBuffer中Object[]数组具体的角标。生产者和消费者各自维护自己的Sequence；但都是指向RingBuffer的Object[]数组；

Wait Strategy：等待策略。当没有可消费的事件时，消费者根据特定的策略进行等待；当没有可生产的地方时，生产者根据特定的策略进行等待；

Event：事件对象，就是我们Ringbuffer中存在的数据，在Disruptor中用Event来定义数据，并不存在Event类，它只是一个定义；

EventProcessor：事件处理器，单独在一个线程内执行，判断消费者的序列和生产者序列关系，决定是否调用我们自定义的事件处理器，也就是是否可以进行消费；

EventHandler：事件处理器，由用户自定义实现，也就是最终的事件消费者，需要实现EventHandler接口；

Producer：事件生产者，也就是我们上面代码中最后那部门的for循环；
```

## 1.5 Disruptor的生产和消费

上面我们通过代码简单的实现了Disruptor，阐述其中具体实现类的含义，接下来再用图文的方式进一步介绍Disruptor的生产和消费；

暂时还是以单生产和单消费者举例：

（1）当Disruptor框架启动：

![img](\java笔记\线程\image\disruptor03.png)

（2）此时，还没有数据进行写入

![img](\java笔记\线程\image\disruptor04.png)

（3）准备写入数据前的准备，获取可以写入数据的最大序列；

![img](\java笔记\线程\image\disruptor05.png)

（4）写入数据完成，更新生产者序列对象的值；

![img](\java笔记\线程\image\disruptor06.png)

以上，就是单生产者写入数据的过程。要注意的是，无论是生产者还是消费者，序列的初始值都是-1；

当引入消费者后，生产者在获取可写入的序列之前，都会判断消费者所处的序列。

我们假设一种情况，当在我们的消费者端使用Thread.sleep(巨大的值)的时候，消费者使用被等待，无法进行消费。

那么此时，生产者会一直对数组中的元素进行生产，当生产到7准备生产序列8的时候，通过计算序列8对应的是index = 0的元素，我们此时会判断覆盖点所对应的角标是否大于消费者的序列大小，如果大于消费者序列，那么生产者不会进行生产，直到消费者消费了此角标下的元素；



```cpp
public long next(int n){
    if (n < 1)
    {
        throw new IllegalArgumentException("n must be > 0");
    }

    long nextValue = this.nextValue;

    long nextSequence = nextValue + n;
    long wrapPoint = nextSequence - bufferSize;
    long cachedGatingSequence = this.cachedValue;

    if (wrapPoint > cachedGatingSequence || cachedGatingSequence > nextValue){
        cursor.setVolatile(nextValue);  // StoreLoad fence

        long minSequence;
        //此处进行判断，如果覆盖点的大小，超过了消费者的序列，那么会一直while循环进行判断
        while (wrapPoint > (minSequence = Util.getMinimumSequence(gatingSequences, nextValue))){
            waitStrategy.signalAllWhenBlocking();
            LockSupport.parkNanos(1L); // TODO: Use waitStrategy to spin?
        }

        this.cachedValue = minSequence;
    }

    this.nextValue = nextSequence;

    return nextSequence;
}
```

单消费者，进行消费的逻辑，与单生产者类似，大家可以进行深入研究；

以上便是单消费者和单生产者的大体流程；


原文链接：https://www.jianshu.com/p/d6375295fad4
