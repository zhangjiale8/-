## Set集合主要源码分析

### 1.1 HashSet源码分析(基于JDK1.7.0_75)

HashSet基于HashMap，底层方法是通过调用HashMap的API来实现，因此HashSet源码结构比较简单，代码较少。

- 成员变量：

在HashSet中，有两个成员变量比较重要--map、PRESENT;

其中，map就是存储元素的地方，实际是一个HashMap。当有元素插入到HashSet中时，会被当做HashMap的key保存到map属性中去。

对于HashMap来说，光有key还不够，在HashSet的实现中，每个key对应的value都默认为PRESENT属性，也就是new了一个Object对象而已；



```java
public class HashSet<E> 
    extends AbstractSet<E> 
    implements Set<E>, Cloneable, java.io.Serializable{

    static final long serialVersionUID = -5024744406713321676L;

    //HashSet通过HashMap保存集合元素的：
    private transient HashMap<E,Object> map;

    //HashSet底层由HashMap实现，新增的元素为map的key，而value则默认为PRESENT。
    private static final Object PRESENT = new Object();
}
```

- 构造方法：

HashSet的构造方法很简单，主要是在方法内部初始化map属性，new了一个HashMap对象；

```java
public class HashSet<E>
        extends AbstractSet<E>
        implements Set<E>, Cloneable, java.io.Serializable {
    
    //无参构造方法：
    public HashSet() {
        //默认new一个HashMap
        map = new HashMap<>();
    }

    // 带集合的构造函数
    public HashSet(Collection<? extends E> c) {
        // 进行初始化HashMap容量判断，
        map = new HashMap<>(Math.max((int) (c.size()/.75f) + 1, 16));
        addAll(c);
    }

    // 指定HashSet初始容量和加载因子的构造函数：主要用于Map内部的扩容机制
    public HashSet(int initialCapacity, float loadFactor) {
        map = new HashMap<>(initialCapacity, loadFactor);
    }

    // 指定HashSet初始容量的构造函数
    public HashSet(int initialCapacity) {
        map = new HashMap<>(initialCapacity);
    }

    //与前4个不同，此构造最终new了一个LinkedHashMap对象：
    HashSet(int initialCapacity, float loadFactor, boolean dummy) {
        map = new LinkedHashMap<>(initialCapacity, loadFactor);
    }
}
```

- add():

HashSet的add(E e)方法，主要是调用底层HashMap的put(K key, V value)方法。

其中key就是HashSet集合插入的元素，而value则是默认的PRESENT属性(一个new Object());



```java
//调用HashMap中的put()方法:
public boolean add(E e) {
    return map.put(e, PRESENT)==null;
}
```

- remove():

与add(E e)方法类似，HashSet的remove(Object o)也是调用了底层HashMap的(Object key)方法；

主要是计算出要删除元素的hash值，在HashMap找到对应的对象，然后从Entry<K,V>[]数组中删除；



```cpp
//调用HashMap中的remove方法：
public boolean remove(Object o) {
    return map.remove(o)==PRESENT;
}
```

### 1.2 TreeSet源码分析(基于JDK1.7.0_75)

上面说了HashSet，接下来说说TreeSet。

与HashSet类似，TreeSet底层也是采用了一个Map来保存集合元素，这个Map就是NavigableMap。

不过，NavigableMap仅仅是一个接口，具体的实现还是使用了TreeMap类；

- 成员变量

当你看到下面的代码之后，你就会明白我为什么一直在说TreeSet底层使用了Map集合了；成员变量m是一个NavigableMap类型的Map集合，常用实现是TreeMap对象；

在TreeMap中，key是我们TreeSet插入的元素，而value则是TreeSet中另一个成员变量PRESENT，一个普通的不能再普通的Object对象；



```java
public class TreeSet<E> extends AbstractSet<E>
        implements NavigableSet<E>, Cloneable, java.io.Serializable {

    //TreeSet中保存元素的map对象：
    private transient NavigableMap<E,Object> m;

    //map对象中保存的value:
    private static final Object PRESENT = new Object();
}
```

- 构造方法

  public class TreeSet<E> extends AbstractSet<E>
   implements NavigableSet<E>, Cloneable, java.io.Serializable {

  

  ```java
    //最底层的构造方法，不对外。传入一个NavigableMap接口的实现类
    TreeSet(NavigableMap<E,Object> m) {
        this.m = m;
    }
  
    //无参构造：向底层构造传入一个TreeMap对象：
    public TreeSet() {
        this(new TreeMap<E,Object>());
    }
  
    //传入比较器的构造：通常传入一个自定义Comparator的实现类；
    public TreeSet(Comparator<? super E> comparator) {
        this(new TreeMap<>(comparator));
    }
  
    //将集合Collection传入TreeSet中：
    public TreeSet(Collection<? extends E> c) {
        this();
        addAll(c);
    }
  
    //将集合SortedSet传入TreeSet中：
    public TreeSet(SortedSet<E> s) {
        this(s.comparator());
        addAll(s);
    }
  ```

  }

- add

向TreeSet中添加元素：



```java
public boolean add(E e) {
    return m.put(e, PRESENT)==null;
}
```

- remove

删除TreeSet中元素o:



```csharp
public boolean remove(Object o) {
    return m.remove(o)==PRESENT;
}
```

无论是HashSet，还是TreeSet，它们的API都是通过底层的Map来实现的。所以就源码来说，没有太多需要去理解地方。

在后面的Map讲解中，我会在详细进行说明。当你理解了Map之后，再回过头来看Set，就很容易去理解了；

### 1.3 SortedSet和NavigableSet到底是什么

本章节，是我在写的时候突然想起来的，觉得有必要加进来阐述下。

为什么觉得有必要呢？

主要是看了一些关于TreeSet讲解的文章，在介绍TreeSet的时候都会提到NavigableSet，接着会说下NavigableSet是个"导航Set集合"，提供了一系列"导航"方法。看到这，我不禁想吐槽下，什么是"导航"方法。

针对于这个疑问，我查了下相关的资料，对这个类有个初步的理解。下面，我就说一下！

通过接口的定义，我们可以看到NavigableSet继承了SortedSet接口(后面说)，实现了对其的扩展；

而通过下面的方法，我们得出NavigableSet实际提供了一系列的搜索匹配元素的功能，能获取到某一区间内的集合元素 ；



```java
public interface NavigableSet<E> extends SortedSet<E> {
     
     E lower(E e);//返回此set集合中小于e元素的最大元素

     E floor(E e);//返回此set集合中小于等于e元素的最大元素

     E ceiling(E e);//返回此set集合中大于等于e元素的最小元素

     E higher(E e);//返回此set集合中大于e元素的最小元素
     
     E pollFirst(); //获取并移除此set集合中的第一个元素
     
     E pollLast();//获取并移除此set集合中的最后一个元素
     
     Iterator<E> iterator();//返回此set集合的迭代器--升序

     NavigableSet<E> descendingSet();//以倒序的顺序返回此set集合

     Iterator<E> descendingIterator();//返回此set集合的迭代器--倒序

     //返回此set集合的部分元素--从fromElement开始到toElement结束，其中fromInclusive、toInclusive意为返回的集合是否包含头尾元素
     NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive);

     //返回此set集合的部分元素--小于toElement，inclusive意味返回的集合是否包含toElement
     NavigableSet<E> headSet(E toElement, boolean inclusive);

     //返回此set集合的部分元素--从fromElement开始到toElement结束，包含头不含为尾
     SortedSet<E> subSet(E fromElement, E toElement);

     //返回此set集合的部分元素--小于toElement
     SortedSet<E> headSet(E toElement);
     
     //返回此set集合的部分元素--大于等于toElement
     SortedSet<E> tailSet(E fromElement);
}
```

说完了NavigableSet，我们在一起儿看下其父类SortedSet接口：

通过名字，我们可以得出此接口跟排序有关，会提供跟排序的方法；



```java
public interface SortedSet<E> extends Set<E> {

    //返回与排序有关的比较器
    Comparator<? super E> comparator();

    //返回从fromElement到toElement的元素集合：
    SortedSet<E> subSet(E fromElement, E toElement);
    
    //返回从第一个元素到toElement元素的集合：
    SortedSet<E> headSet(E toElement);
  
    //返回从fromElement开始到最后元素的集合：
    SortedSet<E> tailSet(E fromElement);
    
    //返回集合中的第一个元素：
    E first();
   
    //返回集合中的最后一个元素：
    E last();
}
```




原文链接：https://www.jianshu.com/p/2d7b4847454b
