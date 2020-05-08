## Set

Set继承于Collection接口，是一个不允许出现重复元素，并且无序的集合，主要有HashSet和TreeSet两大实现类。

在判断重复元素的时候，Set集合会调用hashCode()和equal()方法来实现。

HashSet是哈希表结构，主要利用HashMap的key来存储元素，计算插入元素的hashCode来获取元素在集合中的位置；

TreeSet是红黑树结构，每一个元素都是树中的一个节点，插入的元素都会进行排序；

Set集合框架结构：

![img](image\Set集合框架结构01.png)

### 1.1 Set常用方法

与List接口一样，Set接口也提供了集合操作的基本方法。

但与List不同的是，Set还提供了equals(Object o)和hashCode()，供其子类重写，以实现对集合中插入重复元素的处理；



```java
public interface Set<E> extends Collection<E> {

    A:添加功能
    boolean add(E e);
    boolean addAll(Collection<? extends E> c);

    B:删除功能
    boolean remove(Object o);
    boolean removeAll(Collection<?> c);
    void clear();

    C:长度功能
    int size();

    D:判断功能
    boolean isEmpty();
    boolean contains(Object o);
    boolean containsAll(Collection<?> c);
    boolean retainAll(Collection<?> c); 

    E:获取Set集合的迭代器：
    Iterator<E> iterator();

    F:把集合转换成数组
    Object[] toArray();
    <T> T[] toArray(T[] a);
    
    //判断元素是否重复，为子类提高重写方法
    boolean equals(Object o);
    int hashCode();
}
```

### 1.2 HashSet

HashSet实现Set接口，底层由HashMap(后面讲解)来实现，为哈希表结构，新增元素相当于HashMap的key，value默认为一个固定的Object。在我看来，HashSet相当于一个阉割版的HashMap;

当有元素插入的时候，会计算元素的hashCode值，将元素插入到哈希表对应的位置中来；

它继承于AbstractSet，实现了Set, Cloneable, Serializable接口。

(1)HashSet继承AbstractSet类，获得了Set接口大部分的实现，减少了实现此接口所需的工作，实际上是又继承了AbstractCollection类；

(2)HashSet实现了Set接口，获取Set接口的方法，可以自定义具体实现，也可以继承AbstractSet类中的实现；

(3)HashSet实现Cloneable，得到了clone()方法，可以实现克隆功能；

(4)HashSet实现Serializable，表示可以被序列化，通过序列化去传输，典型的应用就是hessian协议。

具有如下特点：

- 不允许出现重复因素；
- 允许插入Null值；
- 元素无序（添加顺序和遍历顺序不一致）；
- 线程不安全，若2个线程同时操作HashSet，必须通过代码实现同步；

### 1.3 HashSet基本操作

HashSet底层由HashMap实现，插入的元素被当做是HashMap的key，根据hashCode值来确定集合中的位置，由于Set集合中并没有角标的概念，所以并没有像List一样提供get（）方法。当获取HashSet中某个元素时，只能通过遍历集合的方式进行equals()比较来实现；



```csharp
public class HashSetTest {
    public static void main(String[] agrs){
        //创建HashSet集合：
        Set<String> hashSet = new HashSet<String>();
        System.out.println("HashSet初始容量大小："+hashSet.size());

        //元素添加：
        hashSet.add("my");
        hashSet.add("name");
        hashSet.add("is");
        hashSet.add("jiaboyan");
        hashSet.add(",");
        hashSet.add("hello");
        hashSet.add("world");
        hashSet.add("!");
        System.out.println("HashSet容量大小："+hashSet.size());

        //迭代器遍历：
        Iterator<String> iterator = hashSet.iterator();
        while (iterator.hasNext()){
            String str = iterator.next();
            System.out.println(str);
        }
        //增强for循环
        for(String str:hashSet){
            if("jiaboyan".equals(str)){
                System.out.println("你就是我想要的元素:"+str);
            }
            System.out.println(str);
        }

        //元素删除：
        hashSet.remove("jiaboyan");
        System.out.println("HashSet元素大小：" + hashSet.size());
        hashSet.clear();
        System.out.println("HashSet元素大小：" + hashSet.size());

        //集合判断：
        boolean isEmpty = hashSet.isEmpty();
        System.out.println("HashSet是否为空：" + isEmpty);
        boolean isContains = hashSet.contains("hello");
        System.out.println("HashSet是否为空：" + isContains);
    }
}
```

### 1.4 HashSet元素添加分析

Set集合不允许添加重复元素，那么到底是个怎么情况呢？

来看一个简单的例子：



```csharp
public class HashSetTest {

    public static void main(String[] agrs){
        //hashCode() 和 equals()测试：
        hashCodeAndEquals();
    }
    public static void hashCodeAndEquals(){
        //第一个 Set集合：
        Set<String> set1 = new HashSet<String>();
        String str1 = new String("jiaboyan");
        String str2 = new String("jiaboyan");
        set1.add(str1);
        set1.add(str2);
        System.out.println("长度："+set1.size()+",内容为："+set1);

        //第二个 Set集合：
        Set<App> set2 = new HashSet<App>();
        App app1 = new App();
        app1.setName("jiaboyan");

        App app2 = new App();
        app2.setName("jiaboyan");

        set2.add(app1);
        set2.add(app2);
        System.out.println("长度："+set2.size()+",内容为："+set2);

        //第三个 Set集合：
        Set<App> set3 = new HashSet<App>();
        App app3 = new App();
        app3.setName("jiaboyan");
        set3.add(app3);
        set3.add(app3);
        System.out.println("长度："+set3.size()+",内容为："+set3);
    }
}
```

测试结果：



```css
长度：1,内容为：[jiaboyan]
长度：2,内容为：[com.jiaboyan.collection.App@efb78af, com.jiaboyan.collection.App@5f3306ad]
长度：1,内容为：[com.jiaboyan.collection.App@1fb030d8]
```

可以看到，第一个Set集合中最终只有一个元素；第二个Set集合保留了2个元素；第三个集合也只有1个元素；

究竟是什么原因呢？

让我们来看看**HashSet**的add(E e)方法：



```java
public boolean add(E e) {
    return map.put(e, PRESENT)==null;
}
```

在底层HashSet调用了**HashMap**的put(K key, V value)方法:



```csharp
public V put(K key, V value) {
    if (table == EMPTY_TABLE) {
        inflateTable(threshold);
    }
    if (key == null)
        return putForNullKey(value);
    int hash = hash(key);
    int i = indexFor(hash, table.length);
    for (Entry<K,V> e = table[i]; e != null; e = e.next) {
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

通过查看以上的源码，我们可以了解到：实际的逻辑都是在HashMap的put()方法中。

int hash = hash(key) 对传入的key计算hash值；

int i = indexFor(hash, table.length) 对hash值进行转换，转换成数组的index(HashMap中底层存储使用了Entry<K,V>[]数组)；

for (Entry<K,V> e = table[i]; e != null; e = e.next) 判断对应index下是否存在元素；

如果存在，则if(e.hash == hash && ((k = e.key) == key || key.equals(k)))判断；

如果不存在，则addEntry(hash, key, value, i)直接添加；

简单概括如下：

在向HashMap中添加元素时，先判断key的hashCode值是否相同，如果相同，则调用equals()、==进行判断，若相同则覆盖原有元素；如果不同，则直接向Map中添加元素；

反过来，我们在看下上面的例子：

**在第一个Set集合中，我们new了两个String对象，赋了相同的值。当传入到HashMap中时，key均为“jiaboyan”，所以hash和i的值都相同。进行if (e.hash == hash && ((k = e.key) == key || key.equals(k)))判断，由于String对象重写了equals()方法，所以在((k = e.key) == key || key.equals(k))判断时，返回了true，所以第二次的插入并不会增加Set集合的长度；**

**第二个Set集合中，也是new了两个对象，但没有重写equals()方法（底层调用的Object的equals()，也就是==判断），所以会增加2个元素；**

**第三个Set集合中，只new了一个对象，调用的两次add方法都添加的这个新new的对象，所以也只是保留了1个元素；**

### 1.5 TreeSet

从名字上可以看出，此集合的实现和树结构有关。与HashSet集合类似，TreeSet也是基于Map来实现，具体实现**TreeMap**(后面讲解)，其底层结构为**红黑树**（特殊的二叉查找树）；

与HashSet不同的是，TreeSet具有排序功能，分为自然排序(123456)和自定义排序两类，默认是自然排序；在程序中，我们可以按照任意顺序将元素插入到集合中，等到遍历时TreeSet会按照一定顺序输出--倒序或者升序；

它继承AbstractSet，实现NavigableSet, Cloneable, Serializable接口。

（1）与HashSet同理，TreeSet继承AbstractSet类，获得了Set集合基础实现操作；

（2）TreeSet实现NavigableSet接口，而NavigableSet又扩展了SortedSet接口。这两个接口主要定义了搜索元素的能力，例如给定某个元素，查找该集合中比给定元素大于、小于、等于的元素集合，或者比给定元素大于、小于、等于的元素个数；简单地说，实现NavigableSet接口使得TreeSet具备了元素搜索功能；

（3）TreeSet实现Cloneable接口，意味着它也可以被克隆；

（4）TreeSet实现了Serializable接口，可以被序列化，可以使用hessian协议来传输；

具有如下特点：

- 对插入的元素进行排序，是一个有序的集合（主要与HashSet的区别）;
- 底层使用红黑树结构，而不是哈希表结构；
- 允许插入Null值；
- 不允许插入重复元素；
- 线程不安全；

### 1.6 TreeSet基本操作



```csharp
public class TreeSetTest {
    public static void main(String[] agrs){
        TreeSet<String> treeSet = new TreeSet<String>();
        System.out.println("TreeSet初始化容量大小："+treeSet.size());

        //元素添加：
        treeSet.add("my");
        treeSet.add("name");
        treeSet.add("jiaboyan");
        treeSet.add("hello");
        treeSet.add("world");
        treeSet.add("1");
        treeSet.add("2");
        treeSet.add("3");
        System.out.println("TreeSet容量大小：" + treeSet.size());
        System.out.println("TreeSet元素顺序为：" + treeSet.toString());

        //增加for循环遍历：
        for(String str:treeSet){
            System.out.println("遍历元素："+str);
        }

        //迭代器遍历：升序
        Iterator<String> iteratorAesc = treeSet.iterator();
        while(iteratorAesc.hasNext()){
            String str = iteratorAesc.next();
            System.out.println("遍历元素升序："+str);
        }

        //迭代器遍历：降序
        Iterator<String> iteratorDesc = treeSet.descendingIterator();
        while(iteratorDesc.hasNext()){
            String str = iteratorDesc.next();
            System.out.println("遍历元素降序："+str);
        }

        //元素获取:实现NavigableSet接口
        String firstEle = treeSet.first();//获取TreeSet头节点：
        System.out.println("TreeSet头节点为：" + firstEle);

        // 获取指定元素之前的所有元素集合：(不包含指定元素)
        SortedSet<String> headSet = treeSet.headSet("jiaboyan");
        System.out.println("jiaboyan节点之前的元素为："+headSet.toString());

        //获取给定元素之间的集合：（包含头，不包含尾）
        SortedSet subSet = treeSet.subSet("1","world");
        System.out.println("1--jiaboan之间节点元素为："+subSet.toString());

        //集合判断：
        boolean isEmpty = treeSet.isEmpty();
        System.out.println("TreeSet是否为空："+isEmpty);
        boolean isContain = treeSet.contains("who");
        System.out.println("TreeSet是否包含who元素："+isContain);

        //元素删除：
        boolean jiaboyanRemove = treeSet.remove("jiaboyan");
        System.out.println("jiaboyan元素是否被删除"+jiaboyanRemove);
        
        //集合中不存在的元素，删除返回false
        boolean whoRemove = treeSet.remove("who");
        System.out.println("who元素是否被删除"+whoRemove);

       //删除并返回第一个元素：如果set集合不存在元素，则返回null
        String pollFirst = treeSet.pollFirst();
        System.out.println("删除的第一个元素："+pollFirst);
        
        //删除并返回最后一个元素：如果set集合不存在元素，则返回null
        String pollLast = treeSet.pollLast();
        System.out.println("删除的最后一个元素："+pollLast);


        treeSet.clear();//清空集合:
    }
}
```

### 1.7 TreeSet元素排序

在前面的章节，我们讲到了TreeSet是一个有序集合，可以对集合元素排序，其中分为自然排序和自定义排序，那么这两种方式如何实现呢？

首先，我们通过JDK提供的对象来展示，我们使用String、Integer：



```JAVA
public class TreeSetTest {
    public static void main(String[] agrs){
        naturalSort();
    }

    //自然排序顺序：升序
    public static void naturalSort(){
        TreeSet<String> treeSetString = new TreeSet<String>();
        treeSetString.add("a");
        treeSetString.add("z");
        treeSetString.add("d");
        treeSetString.add("b");
        System.out.println("字母顺序：" + treeSetString.toString());

        TreeSet<Integer> treeSetInteger = new TreeSet<Integer>();
        treeSetInteger.add(1);
        treeSetInteger.add(24);
        treeSetInteger.add(23);
        treeSetInteger.add(6);
        System.out.println(treeSetInteger.toString());
        System.out.println("数字顺序：" + treeSetString.toString());
    }
}
```

测试结果：



```css
字母顺序：[a, b, d, z]
数字顺序：[1, 6, 23, 24]
```

接下来，我们自定义对象，看能否实现：

```csharp
public class App{

    private String name;

    private Integer age;

    public App(){}

    public App(String name,Integer age){
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public static void main(String[] args ){
        System.out.println( "Hello World!" );
    }
}

public class TreeSetTest {
    public static void main(String[] agrs){
        customSort();
    }

     //自定义排序顺序：升序
    public static void customSort(){
        TreeSet<App> treeSet = new TreeSet<App>();

        //排序对象：
        App app1 = new App("hello",10);
        App app2 = new App("world",20);
        App app3 = new App("my",15);
        App app4 = new App("name",25);

        //添加到集合：
        treeSet.add(app1);
        treeSet.add(app2);
        treeSet.add(app3);
        treeSet.add(app4);
        System.out.println("TreeSet集合顺序为："+treeSet);
    }
}
```

测试结果：



```css
抛出异常：提示App不能转换为Comparable对象：
Exception in thread "main" java.lang.ClassCastException: com.jiaboyan.collection.App cannot be cast to java.lang.Comparable
```

为什么会报错呢？



```dart
compare(key, key); // type (and possibly null) check

final int compare(Object k1, Object k2) {
    return comparator==null ? ((Comparable<? super K>)k1).compareTo((K)k2)
        : comparator.compare((K)k1, (K)k2);
}
```

通过查看源码发现，在TreeSet调用add方法时，会调用到底层TreeMap的put方法，在put方法中会调用到compare(key, key)方法，进行key大小的比较；

在比较的时候，会将传入的key进行类型强转，所以当我们自定义的App类进行比较的时候，自然就会抛出异常，因为App类并没有实现Comparable接口；

将App实现Comparable接口，在做比较:



```java
public class App implements Comparable<App>{
    private String name;
    private Integer age;
    public App(){}
    public App(String name,Integer age){
        this.name = name;
        this.age = age;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public Integer getAge() {
        return age;
    }
    public void setAge(Integer age) {
        this.age = age;
    }
    //自定义比较：先比较name的长度，在比较age的大小；
    public int compareTo(App app) {
        //比较name的长度：
        int num = this.name.length() - app.name.length();
        //如果name长度一样，则比较年龄的大小：
        return num == 0 ? this.age - app.age : num;
    }
    @Override
    public String toString() {
        return "App{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
```

测试结果如下：



```bash
TreeSet集合顺序为：[App{name='my', age=15}, App{name='name', age=25}, App{name='hello', age=10}, App{name='world', age=20}]
```

此外，还有另一种方式，那就是实现Comparetor<t>接口，并重写compare方法；



```dart
//自定义App类的比较器：
public class AppComparator implements Comparator<App> {

    //比较方法：先比较年龄，年龄若相同在比较名字长度；
    public int compare(App app1, App app2) {
        int num = app1.getAge() - app2.getAge();
        return num == 0 ? app1.getName().length() - app2.getName().length() : num;
    }
}
```

此时，App不用在实现Comparerable接口了，单纯的定义一个类即可；



```csharp
public class App{

    private String name;

    private Integer age;

    public App(){}

    public App(String name,Integer age){
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public static void main(String[] args ){
        System.out.println( "Hello World!" );
    }
}

public class TreeSetTest {
    public static void main(String[] agrs){
        customSort();
    }

    //自定义比较器：升序
    public static void customComparatorSort(){
        TreeSet<App> treeSet = new TreeSet<App>(new AppComparator());
        
        //排序对象：
        App app1 = new App("hello",10);
        App app2 = new App("world",20);
        App app3 = new App("my",15);
        App app4 = new App("name",25);
        
        //添加到集合：
        treeSet.add(app1);
        treeSet.add(app2);
        treeSet.add(app3);
        treeSet.add(app4);

        System.out.println("TreeSet集合顺序为："+treeSet);
    }
}
```

测试结果：

```bash
TreeSet集合顺序为：[App{name='hello', age=10}, App{name='my', age=15}, App{name='world', age=20}, App{name='name', age=25}]
```

最后，在说下关于compareTo()、compare()方法：



```tex
结果返回大于0时，方法前面的值大于方法中的值；

结果返回等于0时，方法前面的值等于方法中的值；

结果返回小于0时，方法前面的值小于方法中的值；
```

