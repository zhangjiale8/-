1.在jDK 5开始增加了线程安全的Map接口 ConcurrentMap

2.Hashtable是JDK 5之前唯一线程安全的内置实现。特别说明的是Hashtable的t是小写的，原因（暂不明确），

ConcurrentHashMap是HashMap的线程安全版本，ConcurrentSkipListMap是TreeMap的线程安全版本。

ConcurrentHashMap和ConcurrentSkipListMap应尽量多的使用。

HashMap的原理：

 我们从头开始设想，要将对象存放在一起，如何设计这个容器。有两条路可走，一种是采用分格技术，每一个对象存放于一个格子中没这样通过对格子的编号就能取到或者遍历对象；另一种技术就是采用串联的方式，各个对象串联起来，这需要各个对象至少带有下一个对象的索引。显然第一种就是数组的概念，第二张就是链表的概念，所有的容器的实现其实都是基于这两种方式的，不管是数组还是链表，或者二者具有。 HashMap就是采用的数组方式。

有了存取对象的容器后还需要以下两个条件才能完成Map所需的条件。

 1.能够快速定位元素：Map的需求就是能够根据一个查询条件快速得到需要的结果，所以这个过程需要的就是尽可能的快

  2.能够自动扩充容量：显然对于容器而然，不需要人工的去控制容器的容量是最好的，这样对于外部使用来说越少知道底部细节越好，不仅使用方便，也越安全。

 3.TreeMap和HashMap的区别和共同点

  1.实现：TreeMap：SortMap接口，基于红黑树，HashMap基于哈希散列表实现。

  2.存储：TreeMap：默认按键的升序排序，HashMap是随机存储

  3.遍历：TreeMap：Iterator遍历是排序的，HashMap是随机的

  4.性能损耗：TreeMap插入和删除

  5.键值对：TreeMap:键、值都不能为null   HashMap只允许键值都为null

  6.效率：TreeMap：效率低  HashMap：效率高。

HashMap是我们生产过程中使用较多的一个数据结构，平时非并发场景使用的HashMap，并发场景下使用的HashTable、ConcurrentHashMap。

表面的API看上去都基本是相同的，但不同的Map实现却差异较大，比如说1.6、1.17、1.8及以上版本中的HashMap、ConcurrentHashMap、远古的HashTable。在进行下面介绍之前默认大家已经理解红黑树、Hash计算等

按照顺序介绍：

## Java 1.6

### HashMap

默认负载因子为0.75，默认容量为16。也就是到达16*0.75 时会出发resize操作。基于数组和链表实现，这算是HashMap的一种教科书里的实现结构了（通常大学课本中特别常见），当key为null 时会添加元素至0的位置。

缺点：new HashMap时就开辟内存空间，在正式使用之前这段时间，造成了一定的内存浪费。下面是HashMap的一种实现结构

![img](image\jdk1.6-hashmap实现.png)

### HashTable

hashTbles的实现基本可以以HashMap结构为基础，要说差异的话就是每个方法都变成了sychronized，这种直接在每个方法上直接sychronized，怕不是当时当时临时上的策略了,Collections.synchronizedMap()也是同样的粗暴。自从ConcurrentHashMap出现后已经几乎没有使用的了。

### ConcurrentHashMap

1.6中的HashMap采用的是分段加锁的方式，可以简单理解为使用使用分段锁直接锁住某些段，然后减小争用的可能性（比HashTable稍微好一些），产生争用时取锁（通过reentrantlock保证并发的安全，直接继承的），来保证安全性。下面是大致的一种结构，锁的是Segment（片段）。有一个concurrency level 默认是16，也就是segment的数量，这个不可以扩容。负载因子同样是0.75，然后容量指定时是平均分配给每个桶的。

![img](image\CurrentHashMap锁-Segment.png)

## Java 1.7

HashTable的实现去查了下源码，一直到Java 10 都基本保持原始的样子。应该是停止更新了，所以以1.7 为准。

HashMap 相对于1.6中的，解决了上文提到的资源浪费问题，实现了简单的懒加载。

ConcurrentHashMap 相对于1.6 中基本没有发生变化。

## Java 8

真正的变化其实发生在1.8中

### HashMap：

优化点：解决碰撞过多的问题，理想情况下6和7中的实现碰撞是较少的，在底层结构看起来也就是链表的长度较短。但现实使用中并没法保证是在理想情况下或正常情况下工作的，所以经常出现链表长度很长，导致性能逐渐下降，并且有的还没开始使用，从一定角度上来说属于资源的分配不均，存在一定的浪费。针对这个问题，1.8中设定了一个阀值（8），当链表长度大于8时使用红黑树进行替换。也就是使用红黑树的方式减小碰撞所带来的代价（O(n) 到 O(logn)）

![img](https:////upload-images.jianshu.io/upload_images/4035167-c2aed5b8017bdd4f.png?imageMogr2/auto-orient/strip|imageView2/2/w/434/format/webp)

然后Hash算法更改为：XORs，扩容算法更改为：ewThr<<1,然后懒加载的特性仍然保留，第一次put的时候才真正的new。

### ConcurrentHashMap：

key&value都不允许为空，从1.8开始出现前置检查，并且舍弃concurrencylevel 改用动态分片。并且，这次可不是挤牙膏式更新，舍弃了之前Segment分段锁式设计，底层采用数组+链表+红黑树结构实现，采用CAS+sychronized实现并发安全。（结构基本同上面java 8中的HashMap）。

下面是putVal中的CAS+Sychronized的使用，putval也是整个ConcurrentHashMap中比较核心的，推荐详细去看一下，因为篇幅，只说里面的一两点。

![img](https:////upload-images.jianshu.io/upload_images/4035167-ceac685693303c22.png?imageMogr2/auto-orient/strip|imageView2/2/w/594/format/webp)



![img](https:////upload-images.jianshu.io/upload_images/4035167-f43cbbbbe1749367.png?imageMogr2/auto-orient/strip|imageView2/2/w/678/format/webp)

具体的hash算法：

![img](https:////upload-images.jianshu.io/upload_images/4035167-d24c6d9a385b8524.png?imageMogr2/auto-orient/strip|imageView2/2/w/369/format/webp)

再然后取元素时，利用了类似于volatile特性的UnSafe.getObjectVolatile()，保证取到的为最新值。

### 1.8中的扩容方式：

当table的数量达到阀值sizeCtl时，会构建一个nextTable（大小为之前的两倍），然后把table的数据复制到nextTable中（不断的遍历原有的完成复制）。其中sizeCtl利用CAS（UnSafe.compareAndSetInt() 完成操作）可以简单看一下。1.8之前的跟之后的ConcurrentHashMap 这个过程是有所差异的，因为结构不同的关系，1.7及之前的扩容时不需要对整个map做rehash只需要对于segment做rehash就OK了

line：2432

private final voidtransfer(Node<K,V>[]tab,Node<K,V>[]nextTab) {

说一个经典的问题：

为什么要使用ConcurrentHashMap，单纯使用HashMap存在什么问题。

看上去ConcurrentHashMap相对于HashMap 也就是在一个数据操作的环节增加了锁操作变为CAS操作。这么做的意义是什么呢？

因为HashMap在并发执行put操作时会引起死循环，多线程可能会导致HashMap的Entry链表形成环形数据结构，查找时会陷入死循环。（两个线程同时扩容相撞了，导致环形链表的产生，所以悲剧就出现了——Infinite Loop）

## 关于rehash：

Java 6 存在rehash

Java 7 存在rehash

Java 8 可能会发生rehash，在扩充HashMap的时候，不需要像JDK1.7的实现那样重新计算hash，只需要看原来的hash值新增的那个bit是1还是0，是0的话索引没变，是1的话索引变成“原索引+oldCap”



### 1 Map并发集合

#### 1.1 ConcurrentMap

ConcurrentMap，它是一个接口，是一个能够支持并发访问的java.util.map集合；

在原有java.util.map接口基础上又新提供了4种方法，进一步扩展了原有Map的功能：



```java
public interface ConcurrentMap<K, V> extends Map<K, V> {

    //插入元素
    V putIfAbsent(K key, V value);

    //移除元素
    boolean remove(Object key, Object value);

    //替换元素
    boolean replace(K key, V oldValue, V newValue);

    //替换元素
    V replace(K key, V value);
}
```

**putIfAbsent：**与原有put方法不同的是，putIfAbsent方法中如果插入的key相同，则不替换原有的value值；

**remove：**与原有remove方法不同的是，新remove方法中增加了对value的判断，如果要删除的key--value不能与Map中原有的key--value对应上，则不会删除该元素;

**replace(K,V,V)：**增加了对value值的判断，如果key--oldValue能与Map中原有的key--value对应上，才进行替换操作；

**replace(K,V)：**与上面的replace不同的是，此replace不会对Map中原有的key--value进行比较，如果key存在则直接替换；

其实，对于ConcurrentMap来说，我们更关注Map本身的操作，在并发情况下是如何实现数据安全的。在java.util.concurrent包中，ConcurrentMap的实现类主要以ConcurrentHashMap为主。接下来，我们具体来看下。

#### 1.2 ConcurrentHashMap

ConcurrentHashMap是一个线程安全，并且是一个高效的HashMap。

但是，如果从线程安全的角度来说，HashTable已经是一个线程安全的HashMap，那推出ConcurrentHashMap的意义又是什么呢？

说起ConcurrentHashMap，就不得不先提及下HashMap在线程不安全的表现，以及HashTable的效率！

- HashMap

关于HashMap的讲解，在此前的文章中已经说过了，本篇不在做过多的描述，有兴趣的朋友可以来这里看下--HashMap

在此节中，我们主要来说下，在多线程情况下HashMap的表现？

HashMap中添加元素的源码：（基于JDK1.7.0_45）



```csharp
public V put(K key, V value) {
    。。。忽略
    addEntry(hash, key, value, i);
    return null;
}
void addEntry(int hash, K key, V value, int bucketIndex) {
    。。。忽略
    createEntry(hash, key, value, bucketIndex);
}
//向链表头部插入元素：在数组的某一个角标下形成链表结构；
void createEntry(int hash, K key, V value, int bucketIndex) {
    Entry<K,V> e = table[bucketIndex];
    table[bucketIndex] = new Entry<>(hash, key, value, e);
    size++;
}
```

在多线程情况下，同时A、B两个线程走到createEntry()方法中，并且这两个线程中插入的元素hash值相同，bucketIndex值也相同，那么无论A线程先执行，还是B线程先被执行，最终都会2个元素先后向链表的头部插入，导致互相覆盖，致使其中1个线程中的数据丢失。这样就造成了HashMap的线程不安全，数据的不一致；

更要命的是，HashMap在多线程情况下还会出现死循环的可能，造成CPU占用率升高，导致系统卡死。

举个简单的例子：



```csharp
public class ConcurrentHashMapTest {
    public static void main(String[] agrs) throws InterruptedException {

        final HashMap<String,String> map = new HashMap<String,String>();

        Thread t = new Thread(new Runnable(){
            public  void run(){
                
                for(int x=0;x<10000;x++){
                    Thread tt = new Thread(new Runnable(){
                        public void run(){
                            map.put(UUID.randomUUID().toString(),"");
                        }
                    });
                    tt.start();
                    System.out.println(tt.getName());
                }
            }
        });
        t.start();
        t.join();
    }
}
```

在上面的例子中，我们利用for循环，启动了10000个线程，每个线程都向共享变量中添加一个元素。

测试结果：通过使用JDK自带的jconsole工具，可以看到HashMap内部形成了死循环，并且主要集中在两处代码上。

![img](image\jconsole-hashmap死循环分析01.png)

![img](image\jconsole-hashmap死循环分析02.png)

那么，是什么原因造成了死循环？

**HashMap--put()494行：**（基于JDK1.7.0_45）

```csharp
public V put(K key, V value) {
    if (table == EMPTY_TABLE) {
        inflateTable(threshold);
    }
    if (key == null)
        return putForNullKey(value);
    int hash = hash(key);
    int i = indexFor(hash, table.length);
    for (Entry<K,V> e = table[i]; e != null; e = e.next) {------**for循环494行**
        Object k;
        if (e.hash == hash && ((k = e.key) == key || key.equals(k))) {
            V oldValue = e.value;
            e.value = value;
            e.recordAccess(this);
            return oldValue;
        }
    }
    modCount++;
    addEntry(hash, key, value, i);
    return null;
}
```

**HashMap--transfer()601行：**（基于JDK1.7.0_45）

```java
void transfer(Entry[] newTable, boolean rehash) {
    int newCapacity = newTable.length;
    for (Entry<K,V> e : table) {
        while(null != e) {
            Entry<K,V> next = e.next;
            if (rehash) {
                e.hash = null == e.key ? 0 : hash(e.key);
            }
            int i = indexFor(e.hash, newCapacity);
            e.next = newTable[i];
            newTable[i] = e;
            e = next;
        }-----**while循环601行**
    }
}
```

通过查看代码，可以看出，死循环的产生：主要因为在遍历数组角标下的链表时，没有了为null的元素，单向链表变成了循环链表，头尾相连了。

以上两点，就是HashMap在多线程情况下的表现。

- HashTable

说完了HashMap的线程不安全，接下来说下HashTable的效率！！

HashTable与HashMap的结构一致，都是哈希表实现。

与HashMap不同的是，在HashTable中，所有的方法都加上了synchronized锁，用锁来实现线程的安全性。由于synchronized锁加在了HashTable的每一个方法上，所以这个锁就是HashTable本身--this。那么，可想而知HashTable的效率是如何，安全是保证了，但是效率却损失了。

无论执行哪个方法，整个哈希表都会被锁住，只有其中一个线程执行完毕，释放所，下一个线程才会执行。无论你是调用get方法，还是put方法皆是如此；

HashTable部分源码：（基于JDK1.7.0_45）

```java
public class Hashtable<K,V> extends Dictionary<K,V> 
    implements Map<K,V>, Cloneable, java.io.Serializable {
    
    public synchronized int size() {...}

    public synchronized boolean isEmpty() {...}

    public synchronized V get(Object key) {...}

    public synchronized V put(K key, V value) {...}
}
```

通过上述代码，可以清晰看出，在HashTable中的主要操作方法上都加了synchronized锁以来保证线程安全。

说完了HashMap和HashTable，下面我们就重点介绍下ConcurrentHashMap，看看ConcurrentHashMap是如何来解决上述的两个问题的！

### 1.3 ConcurrentHashMap结构

在说到ConcurrentHashMap源码之前，我们首先来了解下ConcurrentHashMap的整体结构，这样有利于我们快速理解源码。

不知道，大家还是否记得HashMap的整体结构呢？如果忘记的话，我们就在此进行回顾下！

![img](image\hashmap实现图01.png)

HashMap底层使用数组和链表，实现哈希表结构。插入的元素通过散列的形式分布到数组的各个角标下；当有重复的散列值时，便将新增的元素插入在链表头部，使其形成链表结构，依次向后排列。

**下面是，ConcurrentHashMap的结构：**

![img](image\CurrentHashMap实现图01.png)

与HashMap不同的是，ConcurrentHashMap中多了一层数组结构，由Segment和HashEntry两个数组组成。其中Segment起到了加锁同步的作用，而HashEntry则起到了存储K.V键值对的作用。

在ConcurrentHashMap中，每一个ConcurrentHashMap都包含了一个Segment数组，在Segment数组中每一个Segment对象则又包含了一个HashEntry数组，而在HashEntry数组中，每一个HashEntry对象保存K-V数据的同时又形成了链表结构，此时与HashMap结构相同。

在多线程中，每一个Segment对象守护了一个HashEntry数组，当对ConcurrentHashMap中的元素修改时，在获取到对应的Segment数组角标后，都会对此Segment对象加锁，之后再去操作后面的HashEntry元素，这样每一个Segment对象下，都形成了一个小小的HashMap，在保证数据安全性的同时，又提高了同步的效率。只要不是操作同一个Segment对象的话，就不会出现线程等待的问题！

