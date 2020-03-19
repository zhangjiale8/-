# Java并发集合

## 5.1 引言

在前几章中，我们介绍了Java集合的内容，具体包括ArrayList、HashSet、HashMap、ArrayQueue等实现类。

不知道各位有没有发现，上述集合都有一个共同的特点，那就是线程不安全性，在并发情况下都不能保证数据的一致性。（当然，这个集合必须是共享了，所以才会有数据不一致）

所以，当我们在进行并发任务时候，共享了一个不适用于并发的数据结构，也就是将此数据结构变成了程序中的成员变量，那么我们将会遇到数据的不一致，进而影响到我们程序的运行。

为了应对并发场景的出现，Java在后续迭代过程中（具体应该是JDK1.5版本），推出了java.util.concurrent包。该包的出现，让Java并发编程变得更加轻松，帮助开发者编写更加高效、易维护、结构清晰的程序。

在java.util.concurrent包中，不但包含了我们本篇要说的线程安全的集合，还涉及到了多线程、CAS、线程锁等相关内容，可以说是完整覆盖了Java并发的知识栈。

对于Java开发人员来说，学好java.util.concurrent包下的内容，是一个必备的功课，也是逐渐提升自己的一个重要阶段。

## 5.2 并发集合实现1

JDK1.5的出现，对于集合并发编程来说，java developer有了更多的选择。不过，在JDK1.5之前，Java也还是提供了一些解决方案。

（1）最为简单直接的就是在程序中我们自己对共享变量进行加锁。不过，缺点也显而易见，手动实现线程安全间接增加了程序的复杂度，以及代码出错的概率---例如：线程死锁的产生；

（2）我们还可以使用Java集合框架中的Vector、Hashtable实现类，这两个类都是线程安全的。不过，Java已不提倡使用。

（3）此外，我们还可以使用集合工具类--Collections，通过调用其中的静态方法，来得到线程安全的集合。具体方法，包括：Collections.synchronizedCollection(Collection<T> c)、Collections.synchronizedSet(Set<T> s)、Collections.synchronizedList(List<T>)、Collections.synchronizedMap(Map<K, V>)。
 究其原理，他们都是通过在方法中加synchronized同步锁来实现的。我们知道synchronized锁的开销较大，在程序中不建议使用。

虽然，这三种方式可以实现线程安全的集合，但是都有显而易见的缺点，而且也不是我们今天所关注的重点。

接下来，就来具体看下java.util.concurrent包中的实现；

## 5.2 并发集合实现2

在java.util.concurrent包中，提供了**两种类型的并发集合：一种是阻塞式，另一种是非阻塞式**。

阻塞式集合：**当集合已满或为空时，被调用的添加（满）、移除（空）方法就不能立即被执行，调用这个方法的线程将被阻塞，一直等到该方法可以被成功执行**。

非阻塞式集合：**当集合已满或为空时，被调用的添加（满）、移除（空）方法就不能立即被执行，调用这个方法的线程不会被阻塞，而是直接则返回null或抛出异常**。

下面，就来看下concurrent包下，到底存在了哪些线程安全的集合：

### 5.2.1 Collection集合：

![img](image\concurrent包下Collection集合01.png)

#### 5.2.1.1  List：

​	CopyOnWriteArrayList

#### 5.2.1.2 Set：

​	CopyOnWriteArraySet
​	ConcurrentSkipListSet

#### 5.2.1.3 Queue：

BlockingQueue:
    LinkedBlockingQueue
    DelayQueue
    PriorityBlockingQueue
    ConcurrentLinkedQueue
    TransferQueue:
        LinkedTransferQueue
    BlockingDeque:
        LinkedBlockingDeque
        ConcurrentLinkedDeque

### 5.2.2 Map集合：

![img](image\concurrent包下Map集合01.png)

**Map:**

ConcurrentMap:
    ConcurrentHashMap
    ConcurrentSkipListMap
    ConcurrentNavigableMap

通过以上可以看出，java.util.concurrent包为每一类集合都提供了线程安全的实现。

接下来，我们做具体分析！

## 5.3 List并发集合（CopyOnWrite机制）

### 5.3.1 CopyOnWrite机制

CopyOnWrite（简称COW），是计算机程序设计领域中的一种优化策略，也是一种思想--即写入时复制思想。

那么，什么是写入时复制思想呢？就是当有多个调用者同时去请求一个资源时(可以是内存中的一个数据)，当其中一个调用者要对资源进行修改，系统会copy一个副本给该调用者，让其进行修改；而其他调用者所拥有资源并不会由于该调用者对资源的改动而发生改变。这就是写入时复制思想；

如果用代码来描述的话，就是创建多个线程，在每个线程中如果修改共享变量，那么就将此变量进行一次拷贝操作，每次的修改都是对副本进行。

代码如下：



```dart
public class CopyOnWriteThread implements Runnable {

    private List<String> list = new ArrayList<String>();

    public void run() {
        List<String> newList = new ArrayList<String>();
        newList.add("hello");
        Collections.copy(newList,list);
        
    }
   
    //创建线程：
    public static void main(String[] agrs){
        Thread thread1 = new Thread(new CopyOnWriteThread());
        thread1.start();

        Thread thread2 = new Thread(new CopyOnWriteThread());
        thread2.start();
    }
}
```

从JDK1.5开始，java.util.concurrent包中提供了两个CopyOnWrite机制容器，分别为CopyOnWriteArrayList和CopyOnWriteArraySet。

CopyOnWriteArrayList，直白翻译过来就是“当写入时复制ArrayList集合”。

简单的理解，就是当我们往CopyOnWrite容器中添加元素时，不直接操作当前容器，而是先将容器进行Copy，然后对Copy出的新容器进行修改，修改后，再将原容器的引用指向新的容器，即完成了整个修改操作；

### 5.3.2  CopyOnWriteArrayList的实现原理

CopyOnWriteArrayList，线程安全的集合，这一点主要区别与ArrayList。

通常来说，线程安全都是通过加锁实现的，那么CopyOnWriteArrayList是如何实现？

CopyOnWriteArrayList通过使用ReentrantLock锁来实现线程安全：



```java
public class CopyOnWriteArrayList<E>
        implements List<E>, RandomAccess, Cloneable, java.io.Serializable {
    private static final long serialVersionUID = 8673264195747942595L;

    //ReentrantLock锁，没有使用Synchronized
    transient final ReentrantLock lock = new ReentrantLock();

    //集合底层数据结构：数组（volatile修饰共享可见）
    private volatile transient Object[] array;
}
```

CopyOnWriteArrayList在添加、获取元素时，使用getArray（）获取底层数组对象，获取此时集合中的数组对象；使用setArray（）设置底层数组，将原有数组对象指针指向新的数组对象----实以此来实现CopyOnWrite副本概念：



```dart
//CopyOnWrite容器中重要方法：获取底层数组。
final Object[] getArray() {
    return array;
}

//CopyOnWrite容器中重要方法：设置底层数组
final void setArray(Object[] a) {
    array = a;
}
```

CopyOnWriteArrayList添加元素：在添加元素之前进行加锁操作，保证数据的原子性。在添加过程中，进行数组复制，修改操作，再将新生成的数组复制给集合中的array属性。最后，释放锁；

由于array属性被volatile修饰，所以当添加完成后，其他线程就可以立刻查看到被修改的内容。

```csharp
public boolean add(E e) {
    final ReentrantLock lock = this.lock;
    //加锁：
    lock.lock();
    try {
        //获取集合中的数组：
        Object[] elements = getArray();
        int len = elements.length;
        
        //数组复制：将此线程与其他线程对集合的操作区分开来，无论底层结构如何改变，本线程中的数据不受影响
        Object[] newElements = Arrays.copyOf(elements, len + 1);
        
        //对新的数组进行操作：
        newElements[len] = e;

        //将原有数组指针指向新的数组对象：
        setArray(newElements);
        return true;
    } finally {
        //释放锁：
        lock.unlock();
    }
}
```

CopyOnWriteArrayList获取元素：在获取元素时，由于array属性被volatile修饰，所以每当获取线程执行时，都会拿到最新的数据。此外，添加线程在进行添加元素时，会将新的数组赋值给array属性，所以在获取线程中并不会因为元素的添加而导致本线程的执行异常。因为获取线程中的array和被添加后的array指向了不同的内存区域。

```kotlin
//根据角标，获取对应的数组元素:
public E get(int index) {
    return get(getArray(), index);
}
@SuppressWarnings("unchecked")
private E get(Object[] a, int index) {
    return (E) a[index];
}
```

看到这，不知道你是不是跟我一样，突然有个疑惑，在add（）方法时已经加了锁，为什么还要进行数组复制呢，难道不是多此一举吗？

其实不然，为了能让get（）方法得到最大的性能，CopyOnWriteArrayList并没有进行加锁处理，而且也不需要加锁处理。

因为，在add（）时候加了锁，首先不会有多个线程同时进到add中去，这一点保证了数组的安全。当在一个线程执行add时，又进行了数组的复制操作，生成了一个新的数组对象，在add后又将新数组对象的指针指向了旧的数组对象指针，注意此时是指针的替换，原来旧的数组对象还存在。这样就实现了，添加方法无论如何操作数组对象，获取方法在获取到集合后，都不会受到其他线程添加元素的影响。

这也就是在执行add()时，为什么还要在加锁的同时又copy了一分新的数组对象！！！

### 5.3.3 模拟CopyOnWriteArrayList：

```cpp
public class CopyOnWriteThread{

    private static CopyOnWriteTestList copyOnWriteTestList = new CopyOnWriteTestList();

    static class CopyOnWriteTestList{
        private Object[] array;

        public CopyOnWriteTestList(){
            this.array=new Object[0];
        }
        //获取底层数组：
        public Object[] getArray(){
            return array;
        }
        //设置底层数组：
        public void setArray(Object[] array) {
            this.array = array;
        }

        //添加元素：
        public void add(String element){
            int len = array.length;
            Object[] newElements = Arrays.copyOf(array, len + 1);
            newElements[len] = element;
            setArray(newElements);
        }

        public void get(int index){
            Object[] array = getArray();
            get(array,index);
        }
        //此步骤，就是为了验证在获取元素时，array是否会随着元素的添加而改变；
        public void get(Object[] array,int index){
            for(;;){
                System.out.println("获取方法："+array.length);
            }
        }
    }
    //创建线程：
    public static void main(String[] agrs) throws InterruptedException {
        //启动异步线程，一直添加元素
        new ThreadPoolExecutor(10,10,10, TimeUnit.MINUTES,
                new ArrayBlockingQueue(11),
                new ThreadPoolExecutor.AbortPolicy()).execute(new Runnable() {
            public void run() {
                for(;;){
                    int x=0;;
                    copyOnWriteTestList.add("jiaboyan"+x);
                    ++x;
                }
            }
        });
        Thread.sleep(1000);
        System.out.println(copyOnWriteTestList.getArray().length);
        //启动线程：获取元素
        new Runnable() {
            public void run() {
                copyOnWriteTestList.get(0);
            }
        }.run();
    }
}
```

### 5.3.4 CopyOnWrite机制的优缺点

CopyOnWriteArrayList保证了数据在多线程操作时的最终一致性。

缺点也同样显著，那就是内存空间的浪费：因为在写操作时，进行数组复制，在内存中产生了两份相同的数组。如果数组对象比较大，那么就会造成频繁的GC操作，进而影响到系统的性能；

刚才说了，CopyOnWriteArrayList只能保证最终的数据一致性，而不能保证实时的数据一致性。这一点也是我们在使用的过程中，必须要考虑到的因素。

仔细思考下，其实CopyOnWrite容器也是一种读写分离，读和写是不同的容器。


原文链接：https://www.jianshu.com/p/4f594a84f2dd
