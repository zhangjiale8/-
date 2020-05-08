## Map

昨晚去了鸟巢，膜拜了5位40多岁的大爷们。算上这次，已是第三回了，每一次都有不同的感受、体验。期待，下一次的相遇。

说正题前，先附一张昨晚演唱会的图片！

![img](https:////upload-images.jianshu.io/upload_images/5621908-ff5f46ccea99ecd8.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/690/format/webp)

今天，笔者要介绍的是Java集合框架中的Map集合，在日常工作中Map的运用也十分广泛。

与List集合、Set集合隶属于Collection不同，Map是一个独立的接口，与Collection相同级别的接口。

重要的是，Map集合提供了一个不一样的元素存储方法，利用“key--value”的形式进行存储。其中，每个键映射一个值。而在Set集合中，元素的存储就是利用Map的这一特性来实现。

简单的介绍了下Map集合，接下来，就让笔者对其主要实现类HashMap、TreeMap、HashTable进行详细的说明。



![img](https:////upload-images.jianshu.io/upload_images/5621908-e47f417d73eb10f4.png?imageMogr2/auto-orient/strip|imageView2/2/w/625/format/webp)

### 3.1 Map常用方法

在具体介绍之前，我们先了解下Map接口本身，以便了解所有实现的共同点。



```java
public interface Map<K,V> {

    //返回Map中的key--value的数目
    int size();

    //如果Map不包含任何key--value，则返回 true
    boolean isEmpty();

    //如果Map中包含指定key的映射，则返回true
    boolean containsKey(Object key);

    //如果此Map将一个或多个键映射到指定值，则返回 true
    boolean containsValue(Object value);

    //返回与指定键关联的值
    V get(Object key);

    //将指定值与指定键相关联
    V put(K key, V value);

    //从Map中删除键和关联的值
    V remove(Object key);

    //将指定Map中的所有映射复制到此map
    void putAll(java.util.Map<? extends K, ? extends V> m);

    //从Map中删除所有映射
    void clear();

    //返回Map中所包含键的Set集合
    Set<K> keySet();

    //返回 map 中所包含值的 Collection集合。
    Collection<V> values();

    //返回Map中所包含映射的Set视图。Set中的每个元素都是一个 Map.Entry 对象
    Set<java.util.Map.Entry<K, V>> entrySet();

    //比较指定对象与此 Map 的等价性
    boolean equals(Object o);

    //返回此 Map 的哈希码
    int hashCode();

    //Map集合中存储key--value的对象Entry，在Map集合内形成数组结构
    interface Entry<K,V> {

        V getValue();

        V setValue(V value);

        boolean equals(Object o);

        int hashCode();
    }
}
```

### 3.2 HashMap

HashMap，我们工作中经常使用的集合之一，也是面试中最常被问到的集合。想必，你一定听到过：“来，说说HashMap的实现”等之类的问题！

下面，来做具体介绍：

HashMap基于哈希表，底层结构由数组来实现，添加到集合中的元素以“key--value”形式保存到数组中，在数组中key--value被包装成一个实体来处理---也就是上面Map接口中的Entry。

在HashMap中，Entry[]保存了集合中所有的键值对，当我们需要快速存储、获取、删除集合中的元素时，HashMap会根据hash算法来获得“键值对”在数组中存在的位置，以来实现对应的操作方法。

此时，细心的朋友可能会问，既然是基于哈希表的实现，那么当新增的元素出现了hash值重复了怎么办，怎么插入呢？

专业上来说，hash值重复的情况，我们称之为**哈希碰撞（又或者哈希冲突）**。在HashMap中，是通过链表的形式来解决的，在hash值重复的数组角标下，通过链表将新插入的元素依次排列，当然如果插入的key相同，那么我们会将新插入的value覆盖掉原有的value；

![img](image\hashmap实现图01.png)

像上图所示，当产生了hash冲突后，会在产生冲突的角标下，生成链表，依次排列。

HashMap继承于AbstractMap，实现了Map, Cloneable, Serializable接口。
 (1)HashMap继承AbstractMap，得到了Map接口中定义方法的实现，减少实现Map接口所需的工作；
 (2)HashMap实现Map，得到了Map接口定义的所有方法，其中一部分AbstractMap已实现；
 (3)HashMap实现Cloneable，得到了clone()方法，可以实现克隆功能；
 (4)HashMap实现Serializable，表示可以被序列化，通过序列化去传输，典型的应用就是hessian协议。

它具有如下特点：

- 允许存入null键，null值（null值只有一个，并存于数组第一个位置）
- 无序集合，而且顺序会随着元素的添加而随时改变（添加顺序，迭代顺序不一致）
- 随着元素的增加而动态扩容（与ArrayList原理一致）
- 不存在重复元素（得益于hashCode算法和equals方法）
- 线程不安全

### 3.2 HashMap基本操作

下面，我们来看下HashMap的常用方法：



```dart
 public static void main(String[] agrs){
    //创建HashMap集合：
    Map<String,String> map = new HashMap<String,String>();
    System.out.println("HashMap元素大小:"+map.size());

    //元素添加:
    map.put("hi","hello");
    map.put("my","hello");
    map.put("name","hello");
    map.put("is","hello");
    map.put("jiaboyan","hello");

    //遍历1：获取key的Set集合
    for(String key:map.keySet()){
        System.out.println("map的key是:"+key);
        System.out.println("map的value是:"+map.get(key));
    }

    //遍历2:得到Set集合迭代器
    Set<Map.Entry<String,String>> mapSet1 = map.entrySet();
    Iterator<Map.Entry<String,String>> iterator = mapSet1.iterator();
    while(iterator.hasNext()){
        Map.Entry<String,String> mapEntry = iterator.next();
        System.out.println("map的key是:" + mapEntry.getKey());
        System.out.println("map的value是:" + mapEntry.getValue());
    }

    //遍历3:转换成Set集合，增强for循环
    Set<Map.Entry<String,String>> mapSet2 = map.entrySet();
    for(Map.Entry<String,String> mapEntry : mapSet2){
        System.out.println("map的key是:" + mapEntry.getKey());
        System.out.println("map的value是:" + mapEntry.getValue());
    }

    //元素获取：通过key获取value
    String keyValue = map.get("jiaboyan");
    System.out.println("HashMap的key对应的value:" + keyValue);

    //元素替换：map没有提供直接set方法，而是使用新增来完成更新操作
    map.put("jiaboyan","helloworld");
    System.out.println("HashMap的key对应的value:" + map.get("jiaboyan"));

    //元素删除：
    String value = map.remove("jiaboyan");
    System.out.println("HashMap集合中被删除元素的value" + value);
    //清空所有元素：
    map.clear();

    //hashMap是否包含某个key：
    boolean isContain = map.containsKey("hello");
    //hashMap是否为空：
    boolean isEmpty = map.isEmpty();
}
```

### 3.4 HashMap源码讲解（基于JDK1.7.0_45）

接下来，我们对HashMap源码进行分析。

同理，我们还是带着问题去理解HashMap的实现！

1.HashMap底层数据结构如何？

2.HashMap如何保存数据，增删改咋实现？

3.HashMap如何扩容？

4.为什么扩容的大小一定要是2的整数次幂，也就是2的N次方.

- HashMap成员变量

我们先了解下HashMap中有哪些成员变量：table、DEFAULT_INITIAL_CAPACITY、DEFAULT_LOAD_FACTOR等；

其中，table就是HashMap底层保存元素的数组，默认情况下先赋值为空数组EMPTY_TABLE；

DEFAULT_INITIAL_CAPACITY是HashMap中数组的默认初始化大小。在JDK1.7.0_45版本中，当首次put(新增)元素时，会新建一个容量为16的Entry[]数组赋值给table属性；

DEFAULT_LOAD_FACTOR是HashMap扩容的关键参数，当HashMap中存储的元素个数达到一定的数量时，Entry[]会进行扩容。这个一定数量的值就是根据DEFAULT_LOAD_FACTOR计算得来，主要是数组大小*DEFAULT_LOAD_FACTOR；



```java
public class HashMap<K,V> extends AbstractMap<K,V> 
        implements Map<K,V>, Cloneable, Serializable {

    //hashMap中的数组初始化大小：1 << 4=2^4=16
    static final int DEFAULT_INITIAL_CAPACITY = 1 << 4;

    //1<<30 表示1左移30位，每左移一位乘以2，所以就是1*2^30=1073741824。
    static final int MAXIMUM_CAPACITY = 1 << 30;

    //默认装载因子：
    static final float DEFAULT_LOAD_FACTOR = 0.75f;

    //HashMap默认初始化的空数组：
    static final java.util.HashMap.Entry<?,?>[] EMPTY_TABLE = {};

    //HashMap中底层保存数据的数组：HashMap其实就是一个Entry数组
    transient java.util.HashMap.Entry<K,V>[] table = (java.util.HashMap.Entry<K,V>[]) EMPTY_TABLE;

    //Hashmap中元素的个数：
    transient int size;

    //threshold：等于capacity * loadFactory，决定了HashMap能够放进去的数据量
    int threshold;

    //loadFactor：装载因子，默认值为0.75，它决定了bucket填充程度；
    final float loadFactor;

    //HashMap被操作的次数：
    transient int modCount;

}
```

- HashMap的最终实现

在HashMap中，存储元素的是Entry[]数组，而其中的元素也就是Entry对象：



```java
static class Entry<K,V> implements Map.Entry<K,V> {
    //Entry属性-也就是HashMap的key
    final K key;

    //Entry属性-也就是HashMap的value
    V value;

    //指向下一个节点的引用：实现单向链表结构
    java.util.HashMap.Entry<K,V> next;

    //此Entry的hash值：也就是key的hash值
    int hash;

    // 构造函数：
    Entry(int h, K k, V v, java.util.HashMap.Entry<K,V> n) {
        value = v;
        next = n;
        key = k;
        hash = h;
    }
    public final K getKey() { return key;}
    public final V getValue() { return value; }
    public final V setValue(V newValue) {
        V oldValue = value;
        value = newValue;
        return oldValue;
    }
    public final boolean equals(Object o) {

        if (!(o instanceof Map.Entry))
            return false;
        Map.Entry e = (Map.Entry)o;
        Object k1 = getKey();
        Object k2 = e.getKey();
        if (k1 == k2 || (k1 != null && k1.equals(k2))) {
            Object v1 = getValue();
            Object v2 = e.getValue();
            if (v1 == v2 || (v1 != null && v1.equals(v2)))
                return true;
        }
        return false;
    }
    public final int hashCode() {
        return Objects.hashCode(getKey()) ^ Objects.hashCode(getValue());
    }
    public final String toString() {
        return getKey() + "=" + getValue();
    }
    void recordAccess(java.util.HashMap<K,V> m) {
    }
    void recordRemoval(java.util.HashMap<K,V> m) {
    }
}
```

- HashMap构造函数

我们来看下，HashMap具体的构造是如何实现？

最终都指定到了public HashMap(int initialCapacity, float loadFactor)方法中，对一些成员变量进行赋值。传入的初始容量，并没有改变Entry[]容量大小；



```java
public class HashMap<K,V> extends AbstractMap<K,V> 
            implements Map<K,V>, Cloneable, Serializable {

    //构造方法：初始化容量  指定装载因子
    public HashMap(int initialCapacity, float loadFactor) {
        if (initialCapacity < 0)
            throw new IllegalArgumentException("Illegal initial capacity: " + initialCapacity);
        //指定初始化容量大于 HashMap规定最大容量的话，就将其设置为最大容量；
        if (initialCapacity > MAXIMUM_CAPACITY)
            initialCapacity = MAXIMUM_CAPACITY;
        //不能小于0，判断参数float的值是否是数字
        if (loadFactor <= 0 || Float.isNaN(loadFactor))
            throw new IllegalArgumentException("Illegal load factor: " + loadFactor);
        //装载因子赋值：
        this.loadFactor = loadFactor;
        //初始容量赋值给 临界值属性
        threshold = initialCapacity;
        //空方法：没有任何实现
        init();
    }

    //构造方法：初始化容量
    public HashMap(int initialCapacity) {
        this(initialCapacity, DEFAULT_LOAD_FACTOR);
    }

    //无参构造：默认初始化容量16、默认装载因子0.75
    public HashMap() {
        this(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR);
    }

    public HashMap(Map<? extends K, ? extends V> m) {
        this(Math.max((int) (m.size() / DEFAULT_LOAD_FACTOR) + 1,
                DEFAULT_INITIAL_CAPACITY), DEFAULT_LOAD_FACTOR);
        inflateTable(threshold);

        putAllForCreate(m);
    }
}
```

- HashMap新增元素

对于HashMap来说，新增操作可谓是一个重要的方法，其中包括了最核心的扩容实现；

首先，直接来看put(K key, V value)方法：



```csharp
public V put(K key, V value) {
    //如果调用put方法时(第一次调用put方法)，还是空数组，则进行初始化操作
    if (table == EMPTY_TABLE) {
        //进行初始化HashMap的table属性，进行容量大小设置
        inflateTable(threshold);
    }
    //如果新增的key为null:
    if (key == null)
        //调用key为null的新增方法：
        return putForNullKey(value);

    //计算新增元素的hash值：
    int hash = hash(key);

    //根据hash值和数组长度，计算出新增的元素应该位于数组的哪个角标下：
    int i = indexFor(hash, table.length);

    //判断计算出的角标下，是否有相同的key，可以理解遍历该角标下的链表
    for (java.util.HashMap.Entry<K,V> e = table[i]; e != null; e = e.next) {
        Object k;
        //根据计算出的hash值，以及 equals方法 / == 来判断key是否相同：
        if (e.hash == hash && ((k = e.key) == key || key.equals(k))) {
            //key相同，则替换原有key下的value：
            V oldValue = e.value;
            e.value = value;
            e.recordAccess(this);
            //返回被替换的值：
            return oldValue;
        }
    }
    modCount++;
    //向HashMap中增加元素：
    addEntry(hash, key, value, i);
    return null;
}
```

**补充：在进行key一致性判断时，首先通过hash值判断，再通过equals()或者==进行判断；为什么要做这么多操作？**

**因为每一个对象的hashCode()可以进行重写，既然可以重写，那么就可能会出现相同的hash值。退一步说，哪怕使用JDK默认的计算方式，也会出现重复的可能。所以在进行完hash值比较后，还进行了equals()或者==的判断；**

**那么，既然使用了equals()方法，为什么还要进行==判断呢？（艹，就你问题最多，哪来的这么多为什么？）**

**说白了，主要是为了解决字符串的原因，才做的妥协！**

**对于字符串来说，“==”比较两个变量本身的值，即两个对象在内存中的首地址。而“equals()”比较字符串中所包含的内容是否相同。**

**但是对于非字符串的对象来说，"=="和"equals"都是用来比较对象在堆内存的首地址，即用来比较两个引用变量是否指向同一个对象。**

**这下你明白了吧！！！**

接下来，我们就对上面的方法进行逐一讲解：

当table还是一个空数组的时候，对数组进行初始化：



```cpp
//初始化Entry数组，默认16个大小：
private void inflateTable(int toSize) {
    //获取要创建的数组容量大小：计算大于等于toSize的2的次幂（2的几次方）
    int capacity = roundUpToPowerOf2(toSize);
    //计算HashMap的阀值：
    threshold = (int) Math.min(capacity * loadFactor, MAXIMUM_CAPACITY + 1);
    //创建Entry数组对象，重新对table赋值：
    table = new java.util.HashMap.Entry[capacity];
    //判断是否需要初始化hashSeed属性：
    initHashSeedAsNeeded(capacity);
}

//计算大于等于number的2的幂数（2的几次方）
private static int roundUpToPowerOf2(int number) {
    //在number不大于MAXIMUM_CAPACITY的情况下：
    return number >= MAXIMUM_CAPACITY ? 
        MAXIMUM_CAPACITY : 
            //再次进行三目运算：核心方法Integer.highestOneBit()
            (number > 1) ? Integer.highestOneBit((number - 1) << 1) : 1;
}
```

**补充：Integer.highestOneBit(num)只保留二进制的最高位的1，其余全为0；**

**例如：number=16, (16-1) << 1=30，再highestOneBit(30)，只保留最高位的1，其余全为0。30的二进制为11110，保留最高位的1，其余改为0，则为10000=16；**

**为什么在初始化HashMap的Entry[]时，一定要调用highestOneBit()，获取一个2的N次方的数字？稍后解答！！！！**

在之前介绍HashMap的成员变量时，笔者故意拉下了一个属性，这属性就是hashSeed。现在我们通过介绍initHashSeedAsNeeded()顺便对hashSeed做一个说明：



```java
public class HashMap<K,V> extends AbstractMap<K,V>
        implements Map<K,V>, Cloneable, Serializable {

    static final int ALTERNATIVE_HASHING_THRESHOLD_DEFAULT = Integer.MAX_VALUE;

    transient int hashSeed = 0;

    //HashMap的内部类：
    private static class Holder {
        //内部类成员变量：
        static final int ALTERNATIVE_HASHING_THRESHOLD;
        
        //静态代码块：
        static {
            //获取jvm参数-jdk.map.althashing.threshold，如果设置了，获取其中的值；
            String altThreshold = java.security.AccessController.
                    doPrivileged(new sun.security.action.GetPropertyAction("jdk.map.althashing.threshold"));
            
            int threshold;
            
            try {
                //判断是否设置了jdk.map.althashing.threshold参数：如果没设置，则将ALTERNATIVE_HASHING_THRESHOLD_DEFAULT的值赋值给threshold

                threshold = (null != altThreshold)? Integer.parseInt(altThreshold) : ALTERNATIVE_HASHING_THRESHOLD_DEFAULT;
                
                //threshold如果为-1，jdk.map.althashing.threshold通常设置为-1
                if (threshold == -1) {
                    threshold = Integer.MAX_VALUE;
                }
                if (threshold < 0) {
                    throw new IllegalArgumentException("value must be positive integer.");
                }
            } catch(IllegalArgumentException failed) {
                throw new Error("Illegal value for 'jdk.map.althashing.threshold'", failed);
            }
            //threshold赋值给ALTERNATIVE_HASHING_THRESHOLD，通常该值为Integer.MAX_VALUE
            ALTERNATIVE_HASHING_THRESHOLD = threshold;
        }
    }

    //判断是否初始化hashSeed参数：
    final boolean initHashSeedAsNeeded(int capacity) {
        //判断hashSeed是否等于0：
        boolean currentAltHashing = hashSeed != 0;

        boolean useAltHashing = sun.misc.VM.isBooted() &&
                (capacity >= java.util.HashMap.Holder.ALTERNATIVE_HASHING_THRESHOLD);
        
        boolean switching = currentAltHashing ^ useAltHashing;
        
        //判断是否需要对hashSeed赋值：通常情况下hashSeed的值就是0
        if (switching) {
            hashSeed = useAltHashing? sun.misc.Hashing.randomHashSeed(this): 0;
        }
        return switching;
    }
}
```

通过源码分析了下hashSeed初始化的过程，只要没有单独定义JVM属性--jdk.map.althashing.threshold的话，hashSeed的值一直为0，ALTERNATIVE_HASHING_THRESHOLD的值为Integer.MAX_VALUE；

那么，对于hashSeed是不是为0来说，又有什么意义呢？ 待我们后面进行解答！！！！！！

继续之前put(K key, V value)的源码分析：



```csharp
//新增元素的key为null的话：
private V putForNullKey(V value) {
    //遍历数组的第一个元素，看是否已存在为null的key：
    for (java.util.HashMap.Entry<K,V> e = table[0]; e != null; e = e.next) {
        //如果存在，则将原有的value替换
        if (e.key == null) {
            V oldValue = e.value;
            e.value = value;
            e.recordAccess(this);
            //返回原来的value：
            return oldValue;
        }
    }
    //如果不包含null，则进行添加操作：
    modCount++;
    //向数组中的第一个角标下插入为null的key--value：
    addEntry(0, null, value, 0);
    return null;
}、
```

继续看下，addEntry(int hash, K key, V value, int bucketIndex)--key的哈希值，key，value，所属数组角标



```csharp
void addEntry(int hash, K key, V value, int bucketIndex) {
    //当size大于等于临界值 并且 新增元素所属角标的元素不为null（出现了哈希冲突了），进行扩容
    if ((size >= threshold) && (null != table[bucketIndex])) {
        //变成原来大小的2倍：
        resize(2 * table.length);
        //重新计算新增元素的hash值（此处不太明白为什么要重新计算）
        hash = (null != key) ? hash(key) : 0;
        //重新计算新增元素所处数组的位置（由于数组长度改变，需要重新计算所属角标）
        bucketIndex = indexFor(hash, table.length);
    }
    //创建Entry数组中 entry对象：
    createEntry(hash, key, value, bucketIndex);
}
```

当集合中拥有的元素大于等于临界值 并且 新增元素所处的数组位置不为null 时候，进行扩容；新数组大小为原有的2倍，重新计算元素key的hash值，以及所处新数组的位置。

那么，怎么进行的扩容？



```java
//将HashMap进行扩容：
void resize(int newCapacity) {
    //将原有Entry数组赋值给oldTable参数：
    java.util.HashMap.Entry[] oldTable = table;
    
    //获取现阶段Entry数组的长度：
    int oldCapacity = oldTable.length;
    
    //如果现阶段Entry数组的长度 == MAXIMUM_CAPACITY的话：
    if (oldCapacity == MAXIMUM_CAPACITY) {
        //将阈值设置为Integer的最大值，并返回
        threshold = Integer.MAX_VALUE;
        //没有进行扩容操作：
        return;
    }
    
    //创建新Entry数组：容量为现有2倍大小
    java.util.HashMap.Entry[] newTable = new java.util.HashMap.Entry[newCapacity];
    
    //将原有Entry数组中的元素，添加到新数组中：
    transfer(newTable, initHashSeedAsNeeded(newCapacity));
    
    //新数组赋值给table属性：
    table = newTable;
    //重新计算扩容阈值：
    threshold = (int)Math.min(newCapacity * loadFactor, MAXIMUM_CAPACITY + 1);
}

//原有元素复制到新数组中：
void transfer(java.util.HashMap.Entry[] newTable, boolean rehash) {
    //新数组长度：
    int newCapacity = newTable.length;
    
    //遍历原有Entry数组：
    for (java.util.HashMap.Entry<K,V> e : table) {
        //判断Entry[]中不为null的对象： 
        while(null != e) {
            java.util.HashMap.Entry<K,V> next = e.next;
            //此处需要再次判断hashSeed是否进行初始化：
            if (rehash) {
                //对于Strig类型来说，hashSeed初始化后，需要调用sun.misc.Hashing.stringHash32来计算hash值
                e.hash = null == e.key ? 0 : hash(e.key);
            }
            //计算新数组中元素所处于的角标：
            int i = indexFor(e.hash, newCapacity);
            e.next = newTable[i];
            newTable[i] = e;
            e = next;
        }
    }
}
```

创建Entry对象，createEntry(int hash, K key, V value, int bucketIndex)--key的哈希值，key，value，所属数组角标



```csharp
void createEntry(int hash, K key, V value, int bucketIndex) {
    //获取此角标下的Entry对象：
    java.util.HashMap.Entry<K,V> e = table[bucketIndex];
    
    //无论该角标下是否有元素，都将新元素插入该位置下，将原来的元素置为第二个。
    table[bucketIndex] = new java.util.HashMap.Entry<>(hash, key, value, e);

    //Map集合长度+1
    size++;
}
```

 以上，就是HashMap添加元素的整个流程，也是HashMap的核心。

接下来，我们来解答之前的2个遗留问题：

首先，来解惑hashSeed，对应的是hash(Object k)方法；



```dart
//元素key的hash值计算：
final int hash(Object k) {
    int h = hashSeed;
    //如果为String类型，并且hashSeed不等于0，则会调用sun.misc.Hashing.stringHash32()进行hash值计算
    if (0 != h && k instanceof String) {
        return sun.misc.Hashing.stringHash32((String) k);
    }

    //计算key的hash值，调用key的hashCode方法：
    h ^= k.hashCode();
    h ^= (h >>> 20) ^ (h >>> 12);

    //经过一系列位运算，得出一个hash值：
    return h ^ (h >>> 7) ^ (h >>> 4);
}
```

此时，你应该知道hashSeed的作用了吧！如果hashSeed进行了初始化，那么添加到HashMap中的字符串将会调用sun.misc.Hashing.stringHash32()方法来计算hash值。

下面再来看看，highestOneBit()方法的 点：

通过上面的学习，我们知道Integer.highestOneBit(number)是计算一个大于等于number的2次幂，也就是一个2的N次方数字。并且这个数字，还是HashMap中Entry[]的初始长度。而在后面的扩容操作时，我们也是将原有的数组长度扩大了2倍。所以，无论如何HashMap中Entry[]的长度都是2的N次方；

此时，你可能会问：为什么一定是2的N次方呢？

下面的方法，是计算新增元素应该处于数组中的哪个角标？

通常来说，我们一般会对hash值进行取摸运算，但是，在HashMap中却使用的是与运算。主要是由于 %运算 会运用到除法，效率较低，而与运算直接操作的是101010二进制数据，效率更高。不信的话，我们实际测试下：



```java
public static void test() throws InterruptedException {

    Thread.sleep(3000);

    int hash = 4;

    int length = 16;

    long start = System.nanoTime();
    for(int x = 0;x<100000;x++){
        int result1 = hash%length;
        //int result2 = hash&(length-1);
    }
    long end = System.nanoTime()-start;
    System.out.println("共耗时：" + end);
}
```

测试结果：（纳秒）



```undefined
result1(模运算)：7515748  8673789  5734321  5426216  7897104

result2(与运算)：3858877  3656493  5005590  3932128  3924576
```

怎么样，这回你该相信了吧！

在进一步讲解之前，我们来回顾一下“与运算”的实现：



```undefined
在二进制情况下的处理：
0 & 0=0
0 & 1=0
1 & 0=0
1 & 1=1
```

当length为2的N次方的话，一定为偶数，这样length-1则一定为奇数，而奇数转换成二进制的话，最后一位定为1（可以自己测试下），这样当我们的hash值 与 奇数 进行与运算时候，得到的结果即可能为奇数，也可能为偶数（取决于hash值），此时的散列性更好，出现哈希冲突的情况就比较低，也就是说HashMap中形成链表的可能性更低；

而当length为奇数时，length-1为偶数，转换成二进制的话最后一位是0。根据上面的与运算实现来看，当用0来进行运算时，得到的结果均为0，既无论hash值是多少，最终都只能是偶数。相比于上面来说，length是奇数相当于浪费掉Entry数组一半的空间，更容易出现哈希冲突，形成链表，进而影响整个HashMap的性能。

所以，HashMap选择将length设置为2的N次方，既永远都是偶数；

//计算元素所处于数组的位置，进行与运算
 //一般使用hash值对length取模（即除法散列法）
 static int indexFor(int h, int length) {
 return h & (length-1);
 }

- HashMap查找元素

相比于新增来说，HashMap的查找方法就很简单了。一种是获取key为null的情况，一种是key非null的情况。



```kotlin
//通过key 获取对应的value:
public V get(Object key) {
    if (key == null)
        //获取key==null的value：
        return getForNullKey();

    //获取key不为null的value值：
    java.util.HashMap.Entry<K,V> entry = getEntry(key);

    //返回对应的value：
    return null == entry ? null : entry.getValue();
}

//获取hashMap中key为 null的value值：
private V getForNullKey() {
    //hashmap中没有元素，则返回null：
    if (size == 0) {
        return null;
    }
    //获取Entry数组中，角标为0的Entry对象（put的时候如果有null的key，就存放到角标为0的位置）
    //获取角标为0的Entry对象，遍历整个链表，看是否有key为null的key：返回对应的value：
    for (java.util.HashMap.Entry<K,V> e = table[0]; e != null; e = e.next) {
        if (e.key == null)
            return e.value;
    }
    //如果都不存在，则返回null：
    return null;
}

 //通过对应的key获取 Entry对象：
final java.util.HashMap.Entry<K,V> getEntry(Object key) {
    //hashmap长度为0 ，则返回null：
    if (size == 0) {
        return null;
    }
    //获取key对应的hash值：若key为null,则hash值为0；
    int hash = (key == null) ? 0 : hash(key);
    //计算hash值对应数组的角标，获取数组中角标下的Entry对象：对该元素所属的链表进行遍历；
    for (java.util.HashMap.Entry<K,V> e = table[indexFor(hash, table.length)]; e != null; e = e.next) {
        Object k;
        //判断key的hash值，再调用equlas方法进行判断：hash值可能会相同，equals进一步验证；
        if (e.hash == hash &&
                ((k = e.key) == key || (key != null && key.equals(k))))
            return e;
    }
    //没找到返回null:
    return null;
}
```

- HashMap删除元素

与查找相同，删除元素的方法也比较简单，主要是将元素移除HashMap的Entry[]数组。如果为数组角标下的第一个元素，则直接链表的第二个元素移动到头部来。如果不为第一个元素，则将当前元素的前一个元素的next属性指向当前元素的下一个元素即可；



```java
//移除hashMap中的元素，通过key：
public V remove(Object key) {
    //移除HashMap数组中的Entry对象：
    java.util.HashMap.Entry<K,V> e = removeEntryForKey(key);
    return (e == null ? null : e.value);
}

//通过key移除数组中Entry：
final java.util.HashMap.Entry<K,V> removeEntryForKey(Object key) {
    //如果Hashmap集合为0，则返回null：
    if (size == 0) {
        return null;
    }
    //计算key的hash值：
    int hash = (key == null) ? 0 : hash(key);
    //计算hash值对应的数组角标：
    int i = indexFor(hash, table.length);

    //获取key对应的Entry对象：
    java.util.HashMap.Entry<K,V> prev = table[i];
    //将此对象赋值给e：
    java.util.HashMap.Entry<K,V> e = prev;

    //单向链表的遍历：
    while (e != null) {
        //获取当前元素的下一个元素：
        java.util.HashMap.Entry<K,V> next = e.next;

        Object k;
        //判断元素的hash值、equals方法，是否和传入的key相同：
        if (e.hash == hash &&
                ((k = e.key) == key || (key != null && key.equals(k)))) {
            //增加操作数：
            modCount++;

            //减少元素数量：
            size--;
            //当为链表的第一个元素时，直接将下一个元素顶到链表头部：
            if (prev == e)
                table[i] = next;
            else
                //当前元素的下下一个元素
                prev.next = next;
            //删除当前遍历到的元素：空方法，
            // 将被删除的元素不再与map有关联，没有置为null之类的操作；
            e.recordRemoval(this);
            return e;
        }
        //不相同的话，就把
        prev = e;
        e = next;
    }
    return e;
}
```







































