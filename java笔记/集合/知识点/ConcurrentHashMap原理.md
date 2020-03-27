ConcurrentHashMap原理。

put操作在单个segment内部加锁，继承ReentrantLock 并执行tryLock 和 unlock

### 1.1ConcurrentHashMap初始化

我们首先，来看下ConcurrentHashMap中的主要成员变量；



```java
public class ConcurrentHashMap<K, V> {

    //用于根据给定的key的hash值定位到一个Segment
    final int segmentMask;

    //用于根据给定的key的hash值定位到一个Segment
    final int segmentShift;

    //HashEntry[]初始容量：决定了HashEntry数组的初始容量和初始阀值大小
    static final int DEFAULT_INITIAL_CAPACITY = 16;

    //Segment对象下HashEntry[]的初始加载因子：
    static final float DEFAULT_LOAD_FACTOR = 0.75f;

    //Segment对象下HashEntry[]最大容量：
    static final int MAXIMUM_CAPACITY = 1 << 30;

    //Segment[]初始并发等级：决定了Segment[]的长度
    static final int DEFAULT_CONCURRENCY_LEVEL = 16;

    //最小Segment[]容量：
    static final int MIN_SEGMENT_TABLE_CAPACITY = 2;

    //最大Segement[]容量
    static final int MAX_SEGMENTS = 1 << 16;

    static final int RETRIES_BEFORE_LOCK = 2;

    //Segment[]
    final Segment<K,V>[] segments;
}
```

在ConcurrentHashMap中，定位到Segment[]中的某一角标，需要用到segmentMask和segmentShift这两个属性，他们的主要作用就是定位Segment[];

在上述属性中，有的属性是负责Segment[]的初始化，有的是负责HashEntry[]的初始化操作。如果单纯靠属性的名字来区分，还是很容易弄混淆的，这一点还要大家多多注意观察，以及后续的分析。

DEFAULT_INITIAL_CAPACITY、DEFAULT_LOAD_FACTOR、MAXIMUM_CAPACITY与HashEntry[]的构建有关。

DEFAULT_CONCURRENCY_LEVEL、MIN_SEGMENT_TABLE_CAPACITY、MAX_SEGMENTS与Segment[]的构建有关。

下面，来看看ConcurrentHashMap的构造，它是如何初始化的！



```cpp
public ConcurrentHashMap(int initialCapacity,
                         float loadFactor, int concurrencyLevel) {
    //对容量、加载因子、并发等级做限制，不能小于(等于0)
    if (!(loadFactor > 0) || initialCapacity < 0 || concurrencyLevel <= 0)
        throw new IllegalArgumentException();

    //传入的并发等级不能大于Segment[]长度最大值
    if (concurrencyLevel > MAX_SEGMENTS)
        concurrencyLevel = MAX_SEGMENTS;

    //sshift用来记录向左按位移动的次数
    int sshift = 0; 

    //ssize用来记录segment数组的大小
    int ssize = 1;

    while (ssize < concurrencyLevel) {
        ++sshift;
        ssize <<= 1;
    }

    //segmentShift、segmentMask用于元素在Segment[]数组的定位
    this.segmentShift = 32 - sshift;
    this.segmentMask = ssize - 1;

    //传入初始化的值大于最大容量值，则默认为最大容量值
    if (initialCapacity > MAXIMUM_CAPACITY)
        initialCapacity = MAXIMUM_CAPACITY;

    //c影响了每个Segment[]上要放置多少个HashEntry;
    int c = initialCapacity / ssize;
    if (c * ssize < initialCapacity)
        ++c;
    int cap = MIN_SEGMENT_TABLE_CAPACITY;
    while (cap < c)
        cap <<= 1;

    //创建第一个segment对象，并创建该对象下HashEntry[]
    Segment<K,V> s0 = new Segment<K,V>(loadFactor, (int)(cap * loadFactor), (HashEntry<K,V>[])new HashEntry[cap]);

    //创建Segment[]，指定segment数组的长度：
    Segment<K,V>[] ss = (Segment<K,V>[])new Segment[ssize];

    //使用CAS方式，将上面创建的segment对象放入segment[]数组中;
    UNSAFE.putOrderedObject(ss, SBASE, s0);

    //对ConcurrentHashMap中的segment数组赋值：
    this.segments = ss;
}
```

首先，我们来普及下 <<= 运算符的含义：



```undefined
x <<= 1，就是x等于x左移动1位，就是将左移的数据进行2次方处理；

例如：14 << 2，14的二进制的 00001110 向左移两位等于二进制 00111000，也就是十进制的56；

规律： 1 << i，是把1向左移i位，每次左移一位就是乘以2，所以 1 << i 的结果是 1 乘以 2的i次方；
```

在上面的代码中，initialCapacity--初始容量大小，该参数影响着Segment对象下HashEntry[]的长度大小；loadFactor--加载因子，该参数影响着Segment对象下HashEntry[]数组扩容阀值；concurrencyLevel--并发等级，该参数影响着Segment[]的长度大小。

在ConcurrentHashMap构造中，先是根据concurrencyLevel来计算出Segment[]的大小，而Segment[]的大小 就是**大于或等于concurrencyLevel的最小的2的N次方**。这样的好处是是为了方便采用位运算来加速进行元素的定位。假如concurrencyLevel等于14，15或16，ssize都会等于16；

接下来，根据intialCapacity的值来确定Segment[]的大小，与计算Segment[]的方法一致。

值得一提的是，segmentShift和segmentMask这两个属性。上面说了，Segment[]长度就是2的N次方，在下面这段代码里：



```cpp
int sshift = 0; 
int ssize = 1;
while (ssize < concurrencyLevel) {
    ++sshift;
    ssize <<= 1;
}
this.segmentShift = 32 - sshift;
this.segmentMask = ssize - 1;
```

这个N次方的N，就代表着sshift的大小，每while循环一次，sshift就增加1，那么segmentShift的值就等于32减去n，而segmentMask就等于2的n次方减去1。

### 1.2ConcurrentHashMap插入元素操作

在ConcurrentHashMap类中，使用put()最终调用的是Segment对象中的put()。

由于ConcurrentHashMap是线程安全的集合，所以在添加元素时，需要在操作时进行加锁处理。



```csharp
public V put(K key, V value) {
    Segment<K,V> s;

    //传入的value不能为null
    if (value == null)
        throw new NullPointerException();

    //计算key的hash值：
    int hash = hash(key);

    //通过key的hash值，定位ConcurrentHashMap中Segment[]的角标
    int j = (hash >>> segmentShift) & segmentMask;

    //使用CAS方式，从Segment[]中获取j角标下的Segment对象,并判断是否存在：
    if ((s = (Segment<K,V>)UNSAFE.getObject(segments, (j << SSHIFT) + SBASE)) == null)
        //如果在Segment[]中的j角标处没有元素，则在j角标处新建元素---Segment对象；
        s = ensureSegment(j);

    //底层使用Segment对象的put方法：
    return s.put(key, hash, value, false);
}
```

在ConcurrentHashMap的put()中，首先需要通过key来定位到Segment[]的角标，然后在Segment中进行插入操作。

通过源码可以看到：定位Segment[]操作不但需要key的hash值，还需要使用到segmentShift、segmentMask属性，前面提到过这两个属性的初始化是在ConcurrentHashMap中进行的。

Segment中插入元素方法：



```java
//Segment类，继承了ReentrantLock类：
static final class Segment<K,V> extends ReentrantLock implements Serializable {
    //插入元素：
    final V put(K key, int hash, V value, boolean onlyIfAbsent) {
        //获取锁：
        HashEntry<K,V> node = tryLock() ? null : scanAndLockForPut(key, hash, value);
        V oldValue;
        try {
            //获取Segment对象中的 HashEntry[]：
            HashEntry<K,V>[] tab = table;

            //计算key的hash值在HashEntry[]中的角标：
            int index = (tab.length - 1) & hash;

            //根据index角标获取HashEntry对象：
            HashEntry<K,V> first = entryAt(tab, index);
            //遍历此HashEntry对象(链表结构)：
            for (HashEntry<K,V> e = first;;) {
                //判断逻辑与HashMap大体相似：
                if (e != null) {
                    K k;
                    if ((k = e.key) == key || (e.hash == hash && key.equals(k))) {
                        oldValue = e.value;
                        if (!onlyIfAbsent) {
                            e.value = value;
                            ++modCount;
                        }
                        break;
                    }
                    e = e.next;
                } else {
                    if (node != null)
                        node.setNext(first);
                    else
                        node = new HashEntry<K,V>(hash, key, value, first);
                    int c = count + 1;
                    if (c > threshold && tab.length < MAXIMUM_CAPACITY)
                        //超过了Segment中HashEntry[]的阀值，对HashEntry[]进行扩容;
                        rehash(node);
                    else
                        setEntryAt(tab, index, node);
                    ++modCount;
                    count = c;
                    oldValue = null;
                    break;
                }
            }
        } finally {
            unlock();
        }
        return oldValue;
    }
}
```

在Segment对象中，首先进行获取锁操作，也就是说在ConcurrentHashMap中，锁是加到了每一个Segment对象上，而不是整个ConcurrentHashMap上。这样的好处就是，当我们进行插入操作时，只要插入的不是同一个Segment对象，那么并发线程就不需要进行等待操作，在保证安全的同时，又极大的提高了并发性能。

获取锁之后，通过hash值计算元素需要插入HashEntry[]的角标，再之后的操作基本与HashMap保持一致。

### 1.3 ConcurrentHashMap获取元素操作

通过key，去获取对应的value，大体逻辑与HashMap一致；



```csharp
public V get(Object key) {
    Segment<K,V> s;
    HashEntry<K,V>[] tab;

    //计算key的hash值：
    int h = hash(key);

    //计算该hash值所属的Segment[]的角标：
    long u = (((h >>> segmentShift) & segmentMask) << SSHIFT) + SBASE;

    //获取Segment[]中u角标下的Segment对象：不存在直接返回
    if ((s = (Segment<K,V>)UNSAFE.getObjectVolatile(segments, u)) != null && (tab = s.table) != null) {
        //再根据hash值，从Segment对象中的HashEntry[]获取HashEntry对象：并进行链表遍历
        for (HashEntry<K,V> e = (HashEntry<K,V>) UNSAFE.getObjectVolatile(tab, ((long)(((tab.length - 1) & h)) << TSHIFT) + TBASE);
             e != null; e = e.next) {
            K k;
            //在链表中找到对应元素，便返回；
            if ((k = e.key) == key || (e.hash == h && key.equals(k)))
                return e.value;
        }
    }
    return null;
}
```

在获取操作中，获取Segment对象和HashEntry对象，使用了不同的计算规则，其目的主要为了避免散列后的值一样，尽可能将元素分散开来。



```bash
int h = hash(key)

计算Segment[]角标：
(((h >>> segmentShift) & segmentMask) << SSHIFT) + SBASE

计算HashEntry[]角标：
(tab.length - 1) & h
```

上面我们说过，Segment[]的大小为2的N次方，segmentShift属性为32减去n，segmentMask属性为2的n次方减去1。当我们假设都使用ConcurrentHashMap的默认值时候，Segment[]的大小为16，n为4，segmentShift位28，segmentMask位15。

则h无符号右移28位，剩余4位有效值（高位补0）与segmentMask进行 &运算，得到Segment[]角标。



```undefined
0000 0000 0000 0000 0000 0000 0000 XXXX 4位有效值
0000 0000 0000 0000 0000 0000 0000 1111 15的二进制
---------------------------------- &运算
```

也就是根据元素的hash值的高n位就可以确定元素到底在哪一个Segment中。

与HashTable不同的是，ConcurrentHashMap在获取元素时并没有进行加锁处理，那么在并发场景下会不会产生数据隐患呢？

答案是NO！！！！

原因是，在ConcurrentHashMap的get（）中，要获取的元素被volatitle修饰符所修饰：HashEntry[]



```java
static final class Segment<K,V> extends ReentrantLock implements Serializable {
    transient volatile HashEntry<K,V>[] table;
}
```

被volatile所修饰的变量，可以在多线程中保持可见性，可以执行同时读的操作，并且保证不会读到过期的值。当HashEntry对象被修改后，会立刻更新到内存中，并且使存在于CPU缓存中的HashEntry对象过期无效，当其他线程进行读取时，永远都会读取到内存中最新的值。

### 1.4 ConcurrentHashMap获取长度操作

上面说完了put()和get()，本节在说说size()。与插入、获取不同的是，size（）有可能会对整个hash表进行加锁处理。



```java
public int size() {
    //得到所有的Segment[]：
    final Segment<K,V>[] segments = this.segments;
    int size;
    boolean overflow; // true if size overflows 32 bits
    long sum;         // sum of modCounts
    long last = 0L;   // previous sum
    int retries = -1; // first iteration isn't retry
    try {
        for (;;) {
            //先比较在++，所以说能进到此逻辑中来，肯定retries大于2了
            if (retries++ == RETRIES_BEFORE_LOCK) {
                //-1比较，变0
                //0比较，变1
                //1比较，变2
                //2比较，变3
                for (int j = 0; j < segments.length; ++j)
                    ensureSegment(j).lock(); // force creation
            }
            sum = 0L;
            size = 0;
            overflow = false;
            for (int j = 0; j < segments.length; ++j) {
                //遍历Segment[]，获取其中的Segment对象：
                Segment<K,V> seg = segmentAt(segments, j);
                if (seg != null) {
                    //Segment对象被操作的次数：
                    sum += seg.modCount;
                    //Segment对象内元素的个数：也就是HashEntry对象的个数；
                    int c = seg.count;
                    //size每遍历一次增加一次：
                    if (c < 0 || (size += c) < 0)
                        overflow = true;
                }
            }
            if (sum == last)
                break;
            last = sum;
        }
    } finally {
        //释放锁：retries只有大于2的情况下，才会加锁；
        if (retries > RETRIES_BEFORE_LOCK) {
            for (int j = 0; j < segments.length; ++j)
                segmentAt(segments, j).unlock();
        }
    }
    return overflow ? Integer.MAX_VALUE : size;
}
```

想要知道整个ConcurrentHashMap中的元素数量，就必须统计Segment对象下HashEntry[]中元素的个数。在Segment对象中有一个count属性，它是负责记录Segment对象中到底有多少个HashEntry的。当调用put()时，每增加一个元素，都会对count进行一次++，那么是不是统计所有Segment对象中的count值就行了呢？

答案：不一定。

如果在遍历Segment[]过程中，可能先遍历的Segment进行了插入（删除）操作，导致count发生了改变，引起整个统计结果不准确。所以最安全的做法就行是遍历之前，将整个ConcurrentHashMap加锁处理。

不过，整体加锁的做法有失考虑，毕竟加锁意味着性能下降，而ConcurrentHashMap的做法进行了一个折中处理。

我们思考下，在平常的工作场景，当我们对Map进行size（）操作时，会有多大的几率，又同时进行插入(删除)操作呢？

想必这个事情发生的可能还是很低的，那么ConcurrentHashMap的作法是，连续遍历2次Segment数组，将count的值，进行相加操作。如果遍历2次后的结果，都没有变化，那么就直接将count的和返回，如果此时发生的变化，那么就对整张hash表进行加锁处理。

这就是ConcurrentHashMap的处理方式，即保证了数据准确，又得到了效率！！