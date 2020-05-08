# LinkedBlockingQueue

上篇中，说到了ArrayBlockingQueue阻塞队列。在ArrayBlockingQueue中，底层使用了数组结构来实现。

那么，提到数组了就不得不提及链表。作为两对成双成对的老冤家，链表也可以实现阻塞队列。

下面，就让我们进入今天的正题LinkedBlockingQueue！！！！

LinkedBlockingQueue是一个使用链表实现的阻塞队列，支持多线程并发操作，可保证数据的一致性。

与ArrayBlockingQueue相同的是，LinkedBlockingQueue也实现了元素“**先进先出（FIFO）**”规则，**也使用ReentrantLock来保证数据的一致性**；

与ArrayBlockingQueue不同的是，**LinkedBlockingQueue通常被认为是“无界”的，在默认情况下LinkedBlockingQueue的链表长度为Integer.MAX_VALUE**。

下面，我们就对LinkedBlockingQueue的原理具体分析分析！

## 1.1 成员变量

**对于ArrayBlockingQueue来说，当队列在进行入队和出队时，永远只能有一个操作被执行。因为该队列只有一把锁，所以在多线程执行中并不允许同时出队和入队**。

与ArrayBlockingQueue不同的是，**LinkedBlockingQueue拥有两把锁，一把读锁，一把写锁，可以在多线程情况下，满足同时出队和入队的操作**。

在**ArrayBlockingQueue**中，由于出队入队使用了同一把锁，无论元素增加还是减少，都不会影响到队列元素数量的统计，所以**使用了int类型的变量作为队列数量统计**。

但是，在**LinkedBlockingQueue**中则不同。上面说了，在LinkedBlockingQueue中使用了2把锁，在同时出队入队时，都会涉及到对元素数量的并发修改，会有线程安全的问题。因此，在**LinkedBlockingQueue中使用了原子操作类AtomicInteger，底层使用CAS（compare and set）来解决数据安全问题**。

```java
public class LinkedBlockingQueue<E> extends AbstractQueue<E>
        implements BlockingQueue<E>, java.io.Serializable {
    
    //队列容量大小，默认为Integer.MAX_VALUE
    private final int capacity;

    //队列中元素个数：(与ArrayBlockingQueue的不同)
    //出队和入队是两把锁
    private final AtomicInteger count = new AtomicInteger(0);

    //队列--头结点
    private transient Node<E> head;

    //队列--尾结点
    private transient Node<E> last;

    //与ArrayBlockingQueue的不同,两把锁
    //读取锁
    private final ReentrantLock takeLock = new ReentrantLock();

    //出队等待条件
    private final Condition notEmpty = takeLock.newCondition();

    //插入锁
    private final ReentrantLock putLock = new ReentrantLock();

    //入队等待条件
    private final Condition notFull = putLock.newCondition();
}
```

## 1.2 链表结点

由于LinkedBlockingQueue是链表结构，所以必然会有结点存在。

结点中，保存这元素的值，以及本结点指向下一个结点的指针。

```cpp
//队列存储元素的结点(链表结点):
static class Node<E> {
    //队列元素：
    E item;

    //链表中指向的下一个结点
    Node<E> next;

    //结点构造：
    Node(E x) { item = x; }
}
```

## 1.3 构造函数

之前，我们说了LinkedBlockingQueue可以称为是无界队列，为什么是无界的，就是因为LinkedBlockingQueue的默认构造函数中，指定的队列大小为Integer.MAX_VALUE = 2147483647，想必没有哪个应用程序能达到这个数量。

在初始化中，LinkedBlockingQueue的头尾结点中的元素被置为null；

```csharp
//默认构造函数：
public LinkedBlockingQueue() {
    //默认队列长度为Integer.MAX_VALUE
    this(Integer.MAX_VALUE);
}

//指定队列长度的构造函数：
public LinkedBlockingQueue(int capacity) {
    //初始化链表长度不能为0
    if (capacity <= 0) throw new IllegalArgumentException();
    this.capacity = capacity;
    //设置头尾结点，元素为null
    last = head = new Node<E>(null);
}
```

## 1.4 插入元素（入队）

LinkedBlockingQueue的插入获取和ArrayBlockingQueue基本类似，都包含有阻塞式和非阻塞式。

（1）put（E e）是阻塞式插入，如果队列中的元素与链表长度相同，则此线程等待，直到有空余空间时，才执行。

```java
//向队列尾部插入元素：队列满了线程等待
public void put(E e) throws InterruptedException {
    //不能插入为null元素：
    if (e == null) throw new NullPointerException();
    int c = -1;
    //创建元素结点：
    Node<E> node = new Node(e);
    final ReentrantLock putLock = this.putLock;
    final AtomicInteger count = this.count;
    //加插入锁，保证数据的一致性：
    putLock.lockInterruptibly();
    try {
        //当队列元素个数==链表长度
        while (count.get() == capacity) {
            //插入线程等待：
            notFull.await();
        }
        //插入元素：
        enqueue(node);
        //队列元素增加：count+1,但返回+1前的count值：
        c = count.getAndIncrement();
        //容量还没满，唤醒生产者线程
        // (例如链表长度为5，此时第五个元素已经插入，c=4，+1=5，所以超过了队列容量，则不会再唤醒生产者线程)
        if (c + 1 < capacity)
            notFull.signal();
    } finally {
        //释放锁：
        putLock.unlock();
    }
    //当c=0时，即意味着之前的队列是空队列,消费者线程都处于等待状态，需要被唤醒进行消费
    if (c == 0)
        //唤醒消费者线程：
        signalNotEmpty();
}
```

（2）offer(E e)是非阻塞式插入，队列中的元素与链表长度相同时，直接返回false,不会阻塞线程。

```swift
//向队列尾部插入元素：返回true/false
public boolean offer(E e) {
    //插入元素不能为空
    if (e == null) throw new NullPointerException();
    final AtomicInteger count = this.count;
    //如果队列元素==链表长度，则直接返回false
    if (count.get() == capacity)
        return false;
    int c = -1;
    //创建元素结点对象：
    Node<E> node = new Node(e);
    final ReentrantLock putLock = this.putLock;
    //加锁，保证数据一致性
    putLock.lock();
    try {
        //队列元素个数 小于 链表长度
        if (count.get() < capacity) {
            //向队列中插入元素：
            enqueue(node);
            //增加队列元素个数：
            c = count.getAndIncrement();
            //容量还没满，唤醒生产者线程：
            if (c + 1 < capacity)
                notFull.signal();
        }
    } finally {
        //释放锁：
        putLock.unlock();
    }
    //此时，代表队列中还有一条数据，可以进行消费，唤醒消费者线程
    if (c == 0)
        signalNotEmpty();
    return c >= 0;
}
```

## 1.5 获取元素（出队）

（1）take()：阻塞式出队，获取队列头部元素，如果队列中没有元素，则此线程的等待，直到队列中有元素才执行。

```swift
//从队列头部获取元素，并返回。队列为null，则一直等待
public E take() throws InterruptedException {
    E x;
    int c = -1;
    final AtomicInteger count = this.count;
    final ReentrantLock takeLock = this.takeLock;
    //设置读取锁：
    takeLock.lockInterruptibly();
    try {
        //如果此时队列为空，则获取线程等待
        while (count.get() == 0) {
            notEmpty.await();
        }
        //从队列头部获取元素：
        x = dequeue();
        //减少队列元素-1,返回count减少前的值；
        c = count.getAndDecrement();
        //队列中还有可以消费的元素，唤醒其他消费者线程
        if (c > 1)
            notEmpty.signal();
    } finally {
        //释放锁：
        takeLock.unlock();
    }
    //队列中出现了空余元素，唤醒生产者进行生产。
    // (链表长度为5，队列在执行take前有5个元素，执行到此处时候有4个元素了，但是c的值还是5，所以会进入到if中来)
    if (c == capacity)
        signalNotFull();
    return x;
}
```

poll()：非阻塞式出队，当队列中没有元素，则返回null.

```kotlin
//获取头部元素，并返回。队列为空，则直接返回null
public E poll() {
    final AtomicInteger count = this.count;
    //如果队列中还没有元素，则直接返回 null
    if (count.get() == 0)
        return null;
    E x = null;
    int c = -1;
    final ReentrantLock takeLock = this.takeLock;
    //加锁，保证数据的安全
    takeLock.lock();
    try {
        //此时在判断，队列元素是否大于0
        if (count.get() > 0) {
            //移除队头元素
            x = dequeue();
            //减少队列元素个数
            c = count.getAndDecrement();
            //此时队列中，还有1个元素，唤醒消费者线程继续执行
            if (c > 1)
                notEmpty.signal();
        }
    } finally {
        //释放锁：
        takeLock.unlock();
    }
    //队列中出现了空余元素，唤醒生产者进行生产。
    // (链表长度为5，队列在执行take前有5个元素，执行到此处时候有4个元素了，但是c的值还是5，所以会进入到if中来)
    if (c == capacity)
        signalNotFull();
    return x;
}
```

**(6)出队入队图片介绍**

**入队**

入队操作，很简单，就是向链表中逐个插入新的元素！

首先，将最后的结点指向新插入的结点，其次将last结点置为新插入的结点，流程结束！

**出队**

相比于入队来说，出队的情况要复杂一点点！

但是，请记住一点，就是头部元素永远为null！

[图片上传失败...(image-a955df-1512918370979)]

首先，将头部元素的指向下一个结点的引用，只向自己，主要为了GC的快速清理！

再将，队列中的第一个元素变成头结点，而头结点又保有永远为null的属性，则将头结点元素置为null，也就是出队操作！

## 1.7 ArrayBlockingQueue与LinkedBlockingQueue对比

ArrayBlockingQueue底层基于数组实现，需要使用者指定队列长度，是一个不折不扣的有界队列。

LinkedBlockingQueue底层基于链表实现，无需使用者指定队列长度（可自定义)，当使用默认大小时候，是一个无界队列。

ArrayBlockingQueue由于默认必须设置队列长度，所以在使用时会能更好的预测系统性能；而LinkedBlockingQueue默认无参构造，无需指定队列长度，所以在使用时一定要多加注意，当队列中元素短时间内暴增时，可能会对系统产生灾难性影响。

但是，LinkedBlockingQueue的一大优点也是ArrayBlockingQueue所不具备的，那么就是**在多个CPU的情况下，LinkedBlockingQueue可以做到同一时刻既消费、又生产**。故**LinkedBlockingQueue的性能也要优于ArrayBlockingQueue**。

## 1.8 生产者消费者实现

使用LinkedBlockingQueue简单模拟消费者生产者实现；

```java
public class LinkedBlockingQueueTest {

    static class Apple{

        String colour;

        public Apple(String colour){
            this.colour = colour;
        }

        public String getColour() {
            return colour;
        }

        public void setColour(String colour) {
            this.colour = colour;
        }
    }

    //生产者
    static class Producer implements Runnable{

        LinkedBlockingQueue<Apple> queueProducer ;

        Apple apple;

        public Producer( LinkedBlockingQueue<Apple> queueProducer,Apple apple){
            this.queueProducer = queueProducer;
            this.apple = apple;
        }

        public void run() {
            try {
                System.out.println("生产"+apple.getColour()+"的苹果");
                queueProducer.put(apple);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    //消费者
    static class Consumer implements Runnable{

        LinkedBlockingQueue<Apple> queueConsumer ;

        public Consumer(LinkedBlockingQueue<Apple> queueConsumer){
            this.queueConsumer = queueConsumer;
        }

        public void run() {
            try {
                Apple apple = queueConsumer.take();
                System.out.println("消费"+apple.getColour()+"的苹果");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        LinkedBlockingQueue<Apple> queue = new LinkedBlockingQueue<Apple>();

        Apple appleRed = new Apple("红色");
        Apple appleGreen = new Apple("绿色");

        Producer producer1 = new Producer(queue,appleRed);

        Producer producer2 = new Producer(queue,appleGreen);

        Consumer consumer = new Consumer(queue);

        producer1.run();
        producer2.run();
        consumer.run();

        Thread.sleep(10000);
    }
}
```


原文链接：https://www.jianshu.com/p/d2bbb300ce95
