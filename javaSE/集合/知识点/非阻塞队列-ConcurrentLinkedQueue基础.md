# 非阻塞队列

在上篇中，我们讲到了阻塞队列，以及阻塞队列中的几个实现类。

本篇，我们继续对队列进行研究。而今天的主题，则是非阻塞队列！在非阻塞队列中，ConcurrentLinkedQueue是主要代表。

之前，我们了解了什么是阻塞队列，在此我们再简单地回顾下！

## 1.1 什么是阻塞队列？

阻塞，顾名思义：当我们的生产者向队列中生产数据时，若队列已满，那么生产线程会暂停下来，直到队列中有可以存放数据的地方，才会继续工作；而当我们的消费者向队列中获取数据时，若队列为空，则消费者线程会暂停下来，直到容器中有元素出现，才能进行获取操作。

这就是阻塞队列。

那么，非阻塞队列又是什么含义呢？

## 1.2 什么是非阻塞队列？

与阻塞队列相反，非阻塞队列的执行并不会被阻塞，无论是消费者的出队，还是生产者的入队。

在底层，非阻塞队列使用的是CAS(compare and set)来实现线程执行的非阻塞。

## 1.3 非阻塞队列的操作

与阻塞队列相同，非阻塞队列中的常用方法，也是出队和入队。

### 1.3.1 入队方法：

add()：底层调用offer();

offer()：Queue接口继承下来的方法，实现队列的入队操作，不会阻碍线程的执行，插入成功返回true；

### 1.3.2 出队方法：

poll()：移动头结点指针，返回头结点元素，并将头结点元素出队；队列为空，则返回null；

peek()：移动头结点指针，返回头结点元素，并不会将头结点元素出队；队列为空，则返回null；

下面，我们具体说下ConcurrentLinkedQueue的原理，以及实现！

## 1.4 ConcurrentLinkedQueue

ConcurrentLinkedQueue是一个线程安全的队列，基于链表结构实现，是一个无界队列，理论上来说队列的长度可以无限扩大。

与其他队列相同，ConcurrentLinkedQueue也采用的是**先进先出（FIFO）**入队规则，对元素进行排序。当我们向队列中添加元素时，新插入的元素会插入到队列的尾部；而当我们获取一个元素时，它会从队列的头部中取出。

因为ConcurrentLinkedQueue是链表结构，所以当**入队时，插入的元素依次向后延伸，形成链表；而出队时，则从链表的第一个元素开始获取，依次递增**；

不知道，我这样形容能否让你对链表的入队、出队产生一个大概的思路！

## 1.5 简单使用

值得注意的是，在使用ConcurrentLinkedQueue时，**如果涉及到队列是否为空的判断，切记不可使用size()==0的做法，因为在size()方法中，是通过遍历整个链表来实现的，在队列元素很多的时候，size()方法十分消耗性能和时间，只是单纯的判断队列为空使用isEmpty()即可**！！！

```cpp
public class ConcurrentLinkedQueueTest {

    public static int threadCount = 100000;

    public static ConcurrentLinkedQueue<String> queue = new ConcurrentLinkedQueue<String>();

    static class Offer implements Runnable {
        public void run() {
            if(queue.size()==0){
                String ele = new Random().nextInt(Integer.MAX_VALUE)+"";
                queue.offer(ele);
                System.out.println("入队元素为"+ele);
            }
        }
    }

    static class Poll implements Runnable {
        public void run() {
            if(!queue.isEmpty()){
                String ele = queue.poll();
                System.out.println("出队元素为"+ele);
            }
        }
    }

    public static void main(String[] agrs) {
        ExecutorService executorService = Executors.newFixedThreadPool(4);
        for(int x=0;x<threadCount;x++){
            executorService.submit(new Offer());
            executorService.submit(new Poll());
        }
        executorService.shutdown();
    }
}
```

下篇中，我们详细来介绍ConcurrentLinkedQueue的底层实现。

**引言：**在笔者研究源码时，发现无论是idea,还是eclipse，在debug模式下，跟踪ConcurrentLinkedQueue源码时都会产生bug，具体情况就是debug控制台中类的内存地址和实际的内存地址不一致，导致代码在debug执行时并不会按照正常逻辑来执行。

详细描述，可参考如下内容：[神奇的控制台](https://link.jianshu.com?t=https%3A%2F%2Fwww.zhihu.com%2Fquestion%2F62501203%2Fanswer%2F278573225)

解决方案：将ConcurrentLinkedQueue源码拷出，本地新建一个类，使用run执行，在方法的前后增加自己的输出语句，打印出实际的内存地址，便可一探究竟。如果你不想对源码进行修改，只想用debug模式，建议将拷贝源码中的ConcurrentLinkedQueue的继承和实现统统去掉，形式如下：**public class ConcurrentLinkedQueue**，这样也可以保证debug模式的正常运行

原文链接：https://www.jianshu.com/p/799e7156867d
