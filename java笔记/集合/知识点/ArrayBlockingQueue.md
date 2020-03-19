# ArrayBlockingQueue

ArrayBlockingQueue是一个**阻塞队列，底层使用数组结构实现，按照先进先出（FIFO）的原则对元素进行排序**。

ArrayBlockingQueue是一个线**程安全的集合，通过ReentrantLock锁来实现，在并发情况下可以保证数据的一致性**。

此外，ArrayBlockingQueue的**容量是有限的，数组的大小在初始化时就固定了，不会随着队列元素的增加而出现扩容的情况，也就是说ArrayBlockingQueue是一个“有界缓存区”**。

在下面图片中，以数组形式展示了一个ArrayBlockingQueue：

![img](image\ArrayBlockingQueue01.png)

当向队列插入元素时，首先会插入到数组的0角标处，再有新元素进来时，依次类推，角标1、角标2、角标3。

整个item[]就是一个队伍，我们用时间来排序，展示入队场景。

![img](image\ArrayBlockingQueue02.png)

而当有元素出队时，先移除角标为0的元素，与入队一样，依次类推，移除角标1、角标2...上的元素。

这也形成了“**先进先出**”。

接下来，我们来看看ArrayBlockingQueue的源码实现！

## 1.1 构造方法

在多线程中，默认**不保证线程公平的访问队列**。

什么叫做公平访问队列？我们都知道，在ArrayBlockingQueue中为了保证数据的安全，使用了ReentrantLock锁。由于锁的引入，导致了线程之间的竞争。当有一个线程获取到锁时，其余线程处于等待状态。当锁被释放时，所有等待线程为夺锁而竞争。

而所谓的公平访问，就是等待的线程在获取锁而竞争时，按照等待的先后顺序进行获取操作，先等待的先获取，后等待的后获取。

而非公平访问，就是在获取时候，无论是先等待还是后等待的线程，均有可能获取到锁。

在ArrayBlockingQueue中，由于**公平锁会降低队列的性能，因而使用非公平锁(默认)**。

是否公平，根据ReentrantLock对象来实现---ReentrantLock lock = new ReentrantLock(false)，具体看下构造便可得知。

```java
public class ArrayBlockingQueue<E> extends AbstractQueue<E>
        implements BlockingQueue<E>, java.io.Serializable {

    //队列实现：数组
    final Object[] items;

    //当读取元素时数组的下标(下一个被添加元素的索引)
    int takeIndex;

    //添加元素时数组的下标 （下一个被取出元素的索引）
    int putIndex;

    //队列中元素个数：
    int count;

    //锁：
    final ReentrantLock lock;

    //控制take()操作时是否让线程等待
    private final Condition notEmpty;

    //控制put()操作时是否让线程等待
    private final Condition notFull;

    //初始化队列容量构造：
    public ArrayBlockingQueue(int capacity) {
        this(capacity, false);
    }

    //带初始容量大小和公平锁队列(公平锁通过ReentrantLock实现)：
    public ArrayBlockingQueue(int capacity, boolean fair) {
        if (capacity <= 0)
            throw new IllegalArgumentException();
        this.items = new Object[capacity];
        lock = new ReentrantLock(fair);
        notEmpty = lock.newCondition();
        notFull =  lock.newCondition();
    }
}
```

## 1.2 插入元素

在ArrayBlockingQueue中，提供了两种不同形式的元素插入--阻塞式和非阻塞式。

（1）对于阻塞式插入来说，当队列中的元素已满时，则会将此线程停止，让其处于等待状态，直到队列中有空余位置产生。

```csharp
//向队列尾部添加元素，如果队列满了，则线程等待
public void put(E e) throws InterruptedException {
    //不能插入非空元素,会抛出异常
    checkNotNull(e);
    //上锁，保证数据安全
    final ReentrantLock lock = this.lock;
    lock.lockInterruptibly();
    try {
        //队列中元素 == 数组长度(队列满了),则线程等待
        while (count == items.length)
            notFull.await();
        //添加队列元素
        insert(e);
    } finally {
        //插入完成，释放锁
        lock.unlock();
    }
}
```

（2）而对于非阻塞式来说，当队列中的元素已满时，并不会阻塞此线程的操作，而是让其返回又或者是抛出异常。

```csharp
//向队列尾部添加元素，队列满了返回false
public boolean offer(E e) {
    //不能插入非空元素,会抛出异常
    checkNotNull(e);
    //上锁，保证数据安全
    final ReentrantLock lock = this.lock;
    lock.lock();
    try {
        //队列中元素 == 数组长度(队列满了),则返回false
        if (count == items.length)
            return false;
        else {
            //添加队列元素
            insert(e);
            return true;
        }
    } finally {
        //插入完成，释放锁
        lock.unlock();
    }
}
```

上面的offer(E e)并不会阻塞线程的执行，但是如果想让阻塞和非阻塞相结合的话，需要怎么处理?

ArrayBlockingQueue为我们提供了折中的方法--offer(E e, long timeout, TimeUnit unit);

向队列尾部添加元素，可以设置线程等待时间，如果超过指定时间队列还是满的，则返回false；

```csharp
public boolean offer(E e, long timeout, TimeUnit unit) throws InterruptedException {
    //不能插入非空元素,会抛出异常
    checkNotNull(e);
    //转换成超时时间阀值：
    long nanos = unit.toNanos(timeout);
    //上锁，保证数据安全
    final ReentrantLock lock = this.lock;
    lock.lockInterruptibly();
    try {
        //对队列是否元素满了，做判断。
        while (count == items.length) {
            //如果队列是满的，则每次遍历都去递减一次nanos的值
            if (nanos <= 0)
                return false;
            nanos = notFull.awaitNanos(nanos);
        }
        //添加队列元素
        insert(e);
        return true;
    } finally {
        //插入完成，释放锁
        lock.unlock();
    }
}
```

以上添加方法，都是通过返回false/true来实现的，而在ArrayBlockingQueue中，还提供了集合最原始的插入方法--add(E e)。

该方法在插入时候，如果队列中的元素满了，则会抛出异常。如果插入成功，则返回true。

在add(E e)中，使用父类的add（E e）,实际上其底层也是调用的offer（E e）方法。

```java
//向队列尾部添加元素，队列满了抛出异常；
public boolean add(E e) {
    return super.add(e);
}
```

ArrayBlockingQueue中，最底层的插入方法，上面的各种实现，都是基于insert(E x)来实现的。由于insert(E x)是用private来修饰的，所以我们不能直接对其进行调用。

```cpp
//插入元素到队尾，调整putIndex，唤起等待的获取线程
private void insert(E x) {
    //向数组中插入元素
    items[putIndex] = x;
    //设置下一个被取出元素的索引
    putIndex = inc(putIndex);
    //增加队列元素个数：
    ++count;
    //唤醒notEmpty上的等待线程
    notEmpty.signal();
}
```

## 1.3 获取元素

```java
//获取队列头部元素，如果队列为空，则返回null.不为空。
 // 则返回队列头部，并从队列中删除。
 public E poll() {
     final ReentrantLock lock = this.lock;
     lock.lock();
     try {
     	return (count == 0) ? null : extract();
     } finally {
     	lock.unlock();
     }
 }
```



```csharp
    //返回队列的头部元素，并从队列中删除。如果队列为空，则等待
    public E take() throws InterruptedException {
        final ReentrantLock lock = this.lock;
        lock.lockInterruptibly();
        try {
            //如果队列为空，则进行等待
            while (count == 0)
                notEmpty.await();

            //获取头部元素：
            return extract();
        } finally {
            lock.unlock();
        }
    }

    //获取队列头部元素，如果队列为空，则设置线程等待时间，超过指定时间，还为空，则返回null。
    public E poll(long timeout, TimeUnit unit) throws InterruptedException {
        long nanos = unit.toNanos(timeout);
        final ReentrantLock lock = this.lock;
        lock.lockInterruptibly();
        try {
            while (count == 0) {
                if (nanos <= 0)
                    return null;
                nanos = notEmpty.awaitNanos(nanos);
            }
            return extract();
        } finally {
            lock.unlock();
        }
    }
```

以上就是关于ArrayBlockingQueue的全部内容！下面，我们继续说说LinkedBlockingQueue


原文链接：https://www.jianshu.com/p/4fd0de7e73a9
