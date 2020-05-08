接下来，我，我们来看看队列在Java具体是如何成仙了，来看下Queue的代码！！！

![img](https:////upload-images.jianshu.io/upload_images/5621908-3e5406485acaed8b.png?imageMogr2/auto-orient/strip|imageView2/2/w/569/format/webp)

在Java中，ArrayDeque、LinkedList、PriorityQueue等类实现了Queue接口，模拟了队列的数据结构。

其中，PriorityQueue是Queue直接子类实现，在原有基础上实现了元素的排序功能。

除此之外，Queue还有一个子接口--**Deque**，对Queue进行了扩展，定义了头尾操作功能，既可在队头添加(删除)元素，也可在队尾添加(删除)元素，俗称“**双端队列**”。

接下来，我们来具体介绍下这几个实现类。

 # 1.Queue源码（基于JDK1.7.0_45）



在说Queue实现类之前，我们首先来了解下Queue到底提供了哪些功能！



```java
//接口Queue：
public interface Queue<E> extends Collection<E> {
    //将指定元素插入到队列的尾部（队列满了话，会抛出异常）
    boolean add(E e);

    //将指定元素插入此队列的尾部(队列满了话，会返回false)
    boolean offer(E e);

    /返回取队列头部的元素，并删除该元素(如果队列为空，则抛出异常)
    E remove();

    //返回队列头部的元素，并删除该元素(如果队列为空，则返回null)
    E poll();

    //返回队列头部的元素,不删除该元素(如果队列为空，则抛出异常)
    E element();

    //返回队列头部的元素，不删除该元素(如果队列为空，则返回null)
    E peek();
}
```

在Queue源码中，定义了队列的基本操作：

**在队尾插入元素，在队头获取(删除)元素；**

# 2. PriorityQueue源码（基于JDK1.7.0_45）

作为Queue的直接子类，PriorityQueue实现了Queue定义的方法。

不过，又与传统的队列不相。传统队列实现了“先进先出”数据模型，而PriorityQueue则实现了最小的元素优先出队，剩余元素依次按照大小顺序出队。

这就是所谓的“**优先级队列**”:

（1）元素按照任意的顺序插入，却总是按照顺序进行输出；

（2）每次从优先队列中取出来的元素要么是最大值，要么是最小值。

接下来，我们来看下PriorityQueue具体是如何实现的：

PriorityQueue成员变量和构造方法：

```java
public class PriorityQueue<E> extends AbstractQueue<E>
        implements java.io.Serializable {

    private static final long serialVersionUID = -7720805057305804111L;

    //默认初始化数组大小：
    private static final int DEFAULT_INITIAL_CAPACITY = 11;

    //队列底层数据结构：数组
    private transient Object[] queue;

    //队列长度：
    private int size = 0;

    //实现元素排序的比较器：
    private final Comparator<? super E> comparator;

    //对queue的操作次数：
    private transient int modCount = 0;

    //默认构造函数：
    public PriorityQueue() {
        this(DEFAULT_INITIAL_CAPACITY, null);
    }

    //可设置队列长度的构造函数：
    public PriorityQueue(int initialCapacity) {
        this(initialCapacity, null);
    }

    //可设置队列长度、元素比较器的构造函数：
    public PriorityQueue(int initialCapacity,
                         Comparator<? super E> comparator) {
        if (initialCapacity < 1)
            throw new IllegalArgumentException();
        this.queue = new Object[initialCapacity];
        this.comparator = comparator;
    }

    private static final int MAX_ARRAY_SIZE = Integer.MAX_VALUE - 8;
}
```

PriorityQueue新增元素：



```cpp
    //队列添加元素，底层调用offer:插入失败抛出异常
    public boolean add(E e) {
        return offer(e);
    }

    //队列添加元素: 插入失败返回false
    public boolean offer(E e) {
        //不支持添加为null的元素：
        if (e == null)
            throw new NullPointerException();

        //队列操作数+1：
        modCount++;
        int i = size;

        //队列长度 >= 数组长度时，扩容：
        if (i >= queue.length)
            grow(i + 1);

        //队列长度+1
        size = i + 1;

        //i==0，在数组角标为0处插入第一个元素：
        if (i == 0)
            queue[0] = e;
        else
            //插入的不是第一个元素：
            siftUp(i, e);
        return true;
    }

    //对队列底层数组扩容：
    private void grow(int minCapacity) {
        //现阶段数组长度：
        int oldCapacity = queue.length;
        
        //计算新数组的长度：
        // 如果 现阶段数组长度<64，则扩容为现阶段长度的2倍+2；
        // 如果 现阶段数组>=64，则扩容为现阶段长度的2倍+5；
        int newCapacity = oldCapacity + ((oldCapacity < 64) ?
                (oldCapacity + 2) :
                (oldCapacity >> 1));
        if (newCapacity - MAX_ARRAY_SIZE > 0)
            newCapacity = hugeCapacity(minCapacity);
        
        //数组复制：得到新数组
        queue = Arrays.copyOf(queue, newCapacity);
    }

    private static int hugeCapacity(int minCapacity) {
        if (minCapacity < 0)
            throw new OutOfMemoryError();
        return (minCapacity > MAX_ARRAY_SIZE) ?
                Integer.MAX_VALUE :
                MAX_ARRAY_SIZE;
    }
```

PriorityQueue获取队列头部元素：

```cpp
    //返回队列头部的元素，不删除该元素(如果队列为空，则返回null)
    public E peek() {
        if (size == 0)
            return null;
        return (E) queue[0];
    }

    //返回队列头部的元素，并删除该元素(如果队列为空，则返回null)
    public E poll() {
        if (size == 0)
            return null;
        int s = --size;
        modCount++;
        E result = (E) queue[0];
        E x = (E) queue[s];
        queue[s] = null;
        if (s != 0)
            siftDown(0, x);
        return result;
    }
```

PriorityQueue中核心方法：使用了比较器进行元素比较，当插入或者删除的元素后，对PriorityQueue中树的结构进行调整；

```cpp
    private void siftUp(int k, E x) {
        //元素比较器不为null：
        if (comparator != null)
            siftUpUsingComparator(k, x);
        else
            //元素比较器为null：
            siftUpComparable(k, x);
    }

    //进行堆结构的siftUp运算：使用元素比较器
    private void siftUpComparable(int k, E x) {
        Comparable<? super E> key = (Comparable<? super E>) x;
        while (k > 0) {
            int parent = (k - 1) >>> 1;
            Object e = queue[parent];
            if (key.compareTo((E) e) >= 0)
                break;
            queue[k] = e;
            k = parent;
        }
        queue[k] = key;
    }

    //进行堆结构的siftUp运算：使用自定义元素比较器
    private void siftUpUsingComparator(int k, E x) {
        while (k > 0) {
            int parent = (k - 1) >>> 1;
            Object e = queue[parent];
            if (comparator.compare(x, (E) e) >= 0)
                break;
            queue[k] = e;
            k = parent;
        }
        queue[k] = x;
    }

    private void siftDown(int k, E x) {
        //元素比较器不为null:
        if (comparator != null)
            siftDownUsingComparator(k, x);
        else
            //元素比较器为null：
            siftDownComparable(k, x);
    }

    //进行堆结构的siftDown运算：使用元素比较器
    private void siftDownComparable(int k, E x) {
        Comparable<? super E> key = (Comparable<? super E>)x;
        int half = size >>> 1; 
        while (k < half) {
            int child = (k << 1) + 1; 
            Object c = queue[child];
            int right = child + 1;
            if (right < size &&
                    ((Comparable<? super E>) c).compareTo((E) queue[right]) > 0)
                c = queue[child = right];
            if (key.compareTo((E) c) <= 0)
                break;
            queue[k] = c;
            k = child;
        }
        queue[k] = key;
    }

    //进行堆结构的siftDown运算：使用自定义元素比较器
    private void siftDownUsingComparator(int k, E x) {
        int half = size >>> 1;
        while (k < half) {
            int child = (k << 1) + 1;
            Object c = queue[child];
            int right = child + 1;
            if (right < size &&
                    comparator.compare((E) c, (E) queue[right]) > 0)
                c = queue[child = right];
            if (comparator.compare(x, (E) c) <= 0)
                break;
            queue[k] = c;
            k = child;
        }
        queue[k] = x;
    }

    //返回队列中的比较器：
    public Comparator<? super E> comparator() {
        return comparator;
    }
}
```

从上面的源码中，可以看出，PriorityQueue是由“堆结构”来实现的队列。而“堆结构”又是通过数组形成的一颗完全二叉树。所以，我们在代码中可以看到PriorityQueue最底层数据结构就是数组。

经过上面的源码的分析，对PriorityQueue的总结如下：

PriorityQueue是线程不安全的队列；

PriorityQueue中不允许插入null元素；

PriorityQueue是一个用“堆结构”来实现的队列；

原文链接：https://www.jianshu.com/p/89fb31e6c425
