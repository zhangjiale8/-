# 一、lambda表达式

先看下 lambda 表达式是怎么定义的：

**lambda 表达式是一个匿名函数。** **lambda 表达式允许把一个函数作为参数进行传递。**

可能刚看到这两句话时，不知道是什么意思。那么，对比一下 js 中的 setInterval 函数的用法，你就能找到一些感觉了。

```java
//每一秒执行一次匿名函数。（模拟时钟）
setInterval(function() {
    console.log("当前时间为：" + new Date());
}, 1000);
```

如上，`function(){}`这段，就是一个匿名函数，并且可以把它作为参数传递给 setInterval 函数。

这是因为，在 js 中，函数是一等公民。

然而，在 Java 中，对象才是一等公民。但是，到了 JDK8 我们也可以通过 lambda 表达式表示同样的效果。

lambda 表达式语法如下：

```java
（参数1，参数2） ->  { 方法体 }
```

左边指定了 lambda 表达式所需要的所有参数，右边用来描述方法体。`->` 即为 lambda 运算符。

想一下，在之前我们通过匿名内部类的方式来启动一个线程，是怎么做的？

```java
public class LambdaTest {
    @Test
    public void test(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("线程运行...");
            }
        }).start();
    }
}
```

现在，若把它改为用 lambda 表达式，则为,

```java
public class LambdaTest {
    @Test
    public void test(){
     // 一行搞定
        new Thread(()->System.out.println("线程运行...")).start();
    }
}
```

可以发现，明显用 lambda 表达式，写法更简洁了。

其实，Lambda 表达式就是函数式编程的体现。（什么，你还不知道什么是函数式编程？那还不赶快百度去。）

**注意事项：**

- 参数列表的数据类型会自动推断。也就是说，如果匿名函数有参数列表的话，只需要写参数名即可，不需要写参数的类型。
- 如果参数列表为空，则左边只需要写小括号即可。
- 如果参数只有一个，则可以省略小括号，只写参数的名称即可。
- 如果方法体中只有一条执行语句，则可以省略右边的大括号。若有返回值，则可以把 return 和大括号同时省略。

# 二、接口默认方法和静态方法

## 2.1 接口默认方法

​	我们知道，在 Java 的接口中，只能定义方法名，不能实现方法体的，具体的实现需要子类去做。

但是，到了 JDK8 就不一样了。在接口中，也可以通过 `default`关键字来实现方法体。

那么，就有小伙伴疑惑了。好端端的，为什么要加入这个奇怪的功能呢，它有什么用？

当然是为了提高代码的重用性了。此外，接口的默认方法可以在不影响原来的继承体系的情况下，进行功能的拓展，实现接口的向下兼容。

我滴天，好抽象。那，就用实例来说明一下吧。

假设各种动物的继承体系如下，

```java
public interface Animal {
    //所有动物都需要吃东西，具体吃什么，让子类去实现
    void eat();
}
public class Bird implements Animal {
    @Override
    public void eat() {
        System.out.println("早起的鸟儿有虫吃！");
    }
}
public class Cat implements Animal {
    @Override
    public void eat() {
        System.out.println("小猫爱吃鱼！");
    }
}
```

现在，需要对 Animal接口拓展功能了。动物不能只会吃东西吧，它也许会奔跑，也许会飞行。那么，我在接口中添加两个方法, run 和 fly 就可以了吧。

这样定义方法虽然是可以的，但是，问题就来了。接口中定义了方法，实现类就要实现它的所有方法。小猫会奔跑，但是不会飞啊。而小鸟会飞，你让它在地上跑不是委屈人家嘛。

所以，这个设计不是太合理。

此时，就可以在接口中定义默认方法。子类不需要实现所有方法，可以按需实现，或者直接使用接口的默认方法。

因此，修改 Animal 接口如下，把 run 和 fly 定义为默认方法，

```java
public interface Animal {
    //所有动物都需要吃东西，具体吃什么，让子类去实现
    void eat();

    default void run(){
        System.out.println("我跑");
    }

    default void fly(){
        System.out.println("我飞");
    }
}

public class Main {
    public static void main(String[] args) {
        Bird bird = new Bird();
        bird.fly();

        Cat cat = new Cat();
        cat.run();
    }
}
```

在 JDK8 的集合中，就对 Collection 接口进行了拓展，如增加默认方法 stream() 等。既增强了集合的一些功能，而且也能向下兼容，不会对集合现有的继承体系产生影响。

![img](E:\学习笔记\mylearnnote\javaSE\JDK8\images\202009181945001.png)

## 2.2 接口静态方法

​	另外，在接口中也可以定义静态方法。这样，就可以直接通过接口名调用静态方法。（这也很正常，接口本来就不能实例化）

需要注意的是，不能通过实现类的对象去调用接口的静态方法。

```java
public interface MyStaticInterface {
    static void method(){
        System.out.println("这是接口的静态方法");
    }
}

public class MyStaticInterfaceImpl implements MyStaticInterface {

    public static void main(String[] args) {
        //直接通过接口名调用静态方法，不能通过实现类的对象调用
        MyStaticInterface.method();
    }
}
```

# 三、函数式接口

如果一个接口中只有一个抽象方法，则称其为函数式接口。可以使用 `@FunctionalInterface` 注解来检测一个接口是否为函数式接口。

JDK提供了常见的最简单的四种函数式接口：（必须掌握哦）

- Consumer，消费型接口。接收一个参数，没有返回值。其方法有：void accept(T t);
- Supplier，供给型接口。没有参数，带返回值。其方法：T get();
- Function<T, R>，函数型接口。接收一个参数，返回一个结果。其方法：R apply(T t);
- Predicate，断言型接口。接收一个参数，返回boolean值。其方法：boolean test(T t);

我这里举例了它们的使用方法，

```java
public class LambdaTest {
    @Test
    public void test2(){
        //打印传入的 msg
        printMsg((s)-> System.out.println(s),"听朋友说「烟雨星空」公众号不仅文章好看，还免费送程序员福利，我心动了");
    }

    public void printMsg(Consumer<String> consumer,String msg){
        //消费型，只有传入参数，没有返回值
        consumer.accept(msg);
    }

    @Test
    public void test3(){
        //返回一个 0~99 的随机数
        Integer content = getContent(() -> new Random().nextInt(100));
        System.out.println(content);
    }

    public Integer getContent(Supplier<Integer> supplier){
        //供给型，传入参数为空，带返回值
        return supplier.get();
    }

    @Test
    public void test4(){
        //传入一个字符串，然后把它都转换成大写字母。
        System.out.println(transfer((str) -> str.toUpperCase(), "My wechat : mistyskys"));
    }

    public String transfer(Function<String,String> func,String str){
        // 函数型，传入一个参数，对其进行处理之后，返回一个结果
        return func.apply(str);
    }

    @Test
    public void test5(){
        //定义一个list，用来做筛选
        ArrayList<String> list = new ArrayList<>();
        list.add("zhangsan");
        list.add("lisi");
        list.add("jerry");
        list.add("tom");
        //筛选出集合中，字符串长度大于 3 的，并加入到结果集。
        List<String> filterResult = filter((str) -> str.length() > 3, list);
        System.out.println(filterResult.toString());
    }

    public List<String> filter(Predicate<String> predicate, List<String> list){
        List<String> result = new ArrayList<>();
        for (String str : list) {
            //断言型，传入一个参数，并返回true或者false。
            //这里的逻辑是，若断言为真，则把当前的字符串加入到结果集中
            if(predicate.test(str)){
                result.add(str);
            }
        }
        return result;
    }
}
```

还有一些其他函数式接口，都在`java.util.function`包下，可以自行查看。使用方法都是一样的，不再赘述。

除此之外，JDK 中还有很多函数式接口，例如 `Comparator.java`。只要类上边看到了 `@FunctionalInterface` 这个注解，你都可以使用 lambda 表达式来简化写法。

# 四、方法引用

​	概念：方法引用是用来直接访问类或者实例的**已经存在的**方法或者构造方法。

​	这里强调一下**已经存在**的含义。因为，lambda表达式本质上就是一个匿名函数。我们知道，函数就是做逻辑处理的：拿一些数据，去做一些操作。

如果，我们发现有其他地方（类或者对象）已经存在了相同的逻辑处理方案，那么就可以引用它的方案，而不必重复写逻辑。这就是方法引用。

​	其实方法引用就是一个lambda表达式的另外一种更简洁的表达方式。也可以说是语法糖。

​	只不过，这里要求 lambda 表达式需要符合一定的要求。首先，方法体只有一行代码。其次，方法的实现已经存在。此时，就可以用方法引用替换 lambda 表达式。

方法引用的操作符为双冒号`::`。

下边就以最简单的一个我们非常常见的打印语句为例。

```java
//遍历数组里边的元素，并打印，用lambda表达式
String[] arr = new String[]{"zhangsan","lisi"};
Arrays.asList(arr).forEach((s)-> System.out.println(s));
```

可以发现，lambda 表达式只有一行代码，且方法体逻辑为打印字符串。而打印字符串的方案，在 System.out 对象中已经存在方法 println() 了。

所以，此处 lambda 表达式可以用方法引用替换。

```java
// 注意：方法引用中的方法名不可带括号。
Arrays.asList(arr).forEach(System.out::println);
```

方法引用有以下四种形式：

- 对象 :: 实例方法
- 类 :: 静态方法
- 类 :: 实例方法
- 类 :: new

下边举例说明：

```java
public class ReferTest {
    public static void main(String[] args) {
        //函数式接口的抽象方法的参数列表和返回值类型，必须与方法引用对应的方法参数列表和返回值类型保持一致(情况3除外，比较特殊)。
        //======= 1.对象::实例方法 =========
        // lambda 表达式
        Consumer consumer1 = (s) -> System.out.println(s);
        consumer1.accept("hello world");
        //方法引用。Consumer的accept方法，和System.out的println方法结构一样，
        //都是传入一个参数，无返回值。故可以用方法引用。
        Consumer consumer2 = System.out::println;
        consumer2.accept("hello java");

        //======= 2.类::静态方法 =========
        Integer[] arr = new Integer[]{12,20,15};
        List<Integer> list = Arrays.asList(arr);
        // lambda 表达式
        Comparator<Integer> com1 = (o1, o2) -> Integer.compare(o1, o2);
        Collections.sort(list,com1);
        //方法引用。Comparator的compare方法，和Integer的compare静态方法结构一样，
        //都是传入两个参数，返回一个int值，故可以用方法引用。
        Comparator<Integer> com2 = Integer::compare;
        Collections.sort(list,com2);

        //======= 3.类::实例方法 =========
        // lambda表达式
        Comparator<Integer> com3 = (o1, o2) -> o1.compareTo(o2);
        //方法引用。这种形式比较特殊，(o1, o2) -> o1.compareTo(o2) ，
        //当第一个参数o1为调用对象，且第二个参数o2为需要引用方法的参数时，才可用这种方式。
        Comparator<Integer> com4 = Integer::compareTo;

        //======= 4.类::new =========
        // lambda表达式
        Supplier<String> supplier1 = () -> new String();
        //方法引用。这个就比较简单了，就是类的构造器引用，一般用于创建对象。
        Supplier<String> supplier2 = String::new;
    }
}
```

题外话：方法引用，有时候不太好理解，让人感觉莫名其妙。所以，如果不熟悉的话，用 lambda 表达式完全没有问题。就是习惯的问题，多写就有感觉了。

# 五、Optional

Optional 类是一个容器类。在之前我们通常用 null 来表达一个值不存在，现在可以用 Optional 更好的表达值存在或者不存在。

这样的目的，主要就是为了防止出现空指针异常 NullPointerException 。

我们知道，像层级关系比较深的对象，中间的调用过程很容易出现空指针，如下代码。

```java
User user = new User()；
//中间过程，user对象或者address对象都有可能为空，从而产生空指针异常
String details = user.getAddress().getDetails();
```

其中，对象的关系如下，

```java
// 地址信息类
public class Address {
    private String province; //省
    private String city; //市
    private String county; //县
    private String details; //详细地址

    public String getProvince() {
        return province;
    }

    public void setProvince(String province) {
        this.province = province;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getCounty() {
        return county;
    }

    public void setCounty(String county) {
        this.county = county;
    }

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }
}

//用户类
public class User {
    private String name;
    private Address address;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Address getAddress() {
        return address;
    }

    public void setAddress(Address address) {
        this.address = address;
    }
}
```

在 Optional 类出现之前，为了防止空指针异常，可以这样做。(每一层都添加判空处理)

```java
private static String getUserAddr(User user){
    if(user != null){
        Address address = user.getAddress();
        if(address != null){
            return address.getDetails();
        }else {
            return "地址信息未填写";
        }
    }else {
        return "地址信息未填写";
    }
}
```

可以发现，代码冗长，还不利于维护，随着层级关系更深，将会变成灾难（是否依稀记得js的回调地狱）。

那么，有了 Optional 类，我们就可以写出更优雅的代码，并且防止空指针异常。（后边就填坑）

下面，就一起领略一下 Optional 的魅力吧！

### 创建 Optional 对象

实际上，Optional 是对原值（对象）的一层包装，我们看下 Optional 的源码就知道了。

它把真正需要操作的对象 T 封装成 value 属性。构造器私有化，并提供三种静态的创建 Optional 对象的方法。

```java
public final class Optional<T> {
    //EMPTY 代表一个值为空的 Optional 对象
    private static final Optional<?> EMPTY = new Optional<>();

    //用 value 来代表包装的实际值
    private final T value;

    //值为null的构造函数
    private Optional() {
        this.value = null;
    }

    //要求值不为null的构造函数，否则抛出空指针异常，见requireNonNull方法
    private Optional(T value) {
        this.value = Objects.requireNonNull(value);
    }
    
    /** 此为Objects类的requireNonNull方法
    public static <T> T requireNonNull(T obj) {
        if (obj == null)
            throw new NullPointerException();
        return obj;
    }
    */

    // 1. 创建一个值为空的 Optional 对象
    public static<T> Optional<T> empty() {
        @SuppressWarnings("unchecked")
        Optional<T> t = (Optional<T>) EMPTY;
        return t;
    }
    
    // 2. 创建一个值不为空的 Optional 对象
    public static <T> Optional<T> of(T value) {
        return new Optional<>(value);
    }

    // 3. 创建一个值可为空的 Optional 对象
    // 如果值 value 为空，则同1，若不为空，则同2
    public static <T> Optional<T> ofNullable(T value) {
        return value == null ? empty() : of(value);
    }
}
```

因此，当我们十分确定传入的user对象不为空时，可以用 Optional.of(user)方法。若不确定，则用 Optional.ofNullable(user),这样在后续的操作中可以避免空指针异常（后续map说明）。

### 常用方法

## 5.1 get方法

```java
public T get() {
    //如果值为null，则抛出异常，否则返回非空值value
    if (value == null) {
        throw new NoSuchElementException("No value present");
    }
    return value;
}
```

## 5.2 isPresent方法

```java
//判断值是否存在，若值不为空，则认为存在
public boolean isPresent() {
    return value != null;
}
```

看到这，不知道有没有小伙伴和我当初有一样的疑惑。既然有判空方法 isPresent，还有获取对象的 get 方法。那开头的那个坑，是不是就可以改写为如下，

```java
//注意此时user类型为Optional<User>
private static String getUserAddr(Optional<User> user){
    //如果user存在，则取address对象
    if(user.isPresent()){
        Address address = user.get().getAddress();
        //把address包装成Optional对象
        Optional<Address> addressOptional = Optional.ofNullable(address);
        //如果address存在，则取details地址信息
        if(addressOptional.isPresent()){
            return addressOptional.get().getDetails();
        }else {
            return "地址信息未填写";
        }
    }else{
        return "地址信息未填写";
    }
}
```

这样看起来，好像功能也实现了。但是，我们先不说代码并没有简洁（反而更复杂了），其实是陷入了一个怪圈了。

因为，`if(user.isPresent()){}`和手动判空处理 `if(user!=null){}`实质上是没有区别的。这就是受之前一直以来的代码思维限制了。

所以，我们不要手动调用 isPresent 方法 。

不要奇怪，isPresent 方法，其实是为了 Optional 中的其他方法服务的（如map方法），本意并不是为了让我们手动调用。你会在后续多个方法中，见到 isPresent 的身影。

## 5.3 ifPresent

```java
//传入一个消费型接口，当值存在时，才消费。
public void ifPresent(Consumer<? super T> consumer) {
    if (value != null)
        consumer.accept(value);
}
```

与 isPresent 方法不同， ifPresent 方法是我们推荐使用的。

如可以这样判空，

```java
Optional<User> user = Optional.ofNullable(new User());
user.ifPresent(System.out::println);
//不要用下边这种
if (user.isPresent()) {
  System.out.println(user.get());
}
```

## 5.4 orElse 和 orElseGet

```java
public T orElse(T other) {
    return value != null ? value : other;
}

public T orElseGet(Supplier<? extends T> other) {
    return value != null ? value : other.get();
}
```

这两个方法都是当值不存在时，用于返回一个默认值。如user对象为null时，返回默认值。

```java
@Test
public void test1(){
    User user = null;
    System.out.println("orElse调用");
    User user1 = Optional.ofNullable(user).orElse(createUser());
    System.out.println("orElseGet调用");
    User user2 = Optional.ofNullable(user).orElseGet(() -> createUser());
}

private User createUser() {
    //此处打印，是为了查看orElse和orElseGet的区别
    System.out.println("createUser...");
    return new User();
}
//打印结果
orElse调用
createUser...
orElseGet调用
createUser...
```

以上是user为null时，两个方法是没有区别的。因为都需要创建user对象作为默认值返回。

但是，当user对象不为null时，我们看下对比结果，

```
@Test
public void test2(){
    User user = new User();
    System.out.println("orElse调用");
    User user1 = Optional.ofNullable(user).orElse(createUser());
    System.out.println("orElseGet调用");
    User user2 = Optional.ofNullable(user).orElseGet(() -> createUser());
}  
//打印结果
orElse调用
createUser...
orElseGet调用
```

可以发现，当user对象不为null时，orElse依然会创建User对象，而orElseGet不会创建。

所以，当 orElse() 方法传入的参数需要创建对象或者比较耗时的操作时，建议用 orElseGet()

## 5.5 orElseThrow

当值为null，可以返回自定义异常。

```java
User user = null;
Optional.ofNullable(user).orElseThrow(IllegalAccessError::new);
```

若user对象为null，则抛出非法访问。

这样，可以有针对的对特定异常做一些其他处理。因为，会抛出哪些异常的情况，是我们可控的。

## 5.6 map

```java
public<U> Optional<U> map(Function<? super T, ? extends U> mapper) {
    Objects.requireNonNull(mapper);
    //看到没，map内部会先调用isPresent方法来做判空处理。
    //所以我们不要自己去调用isPresent方法
    if (!isPresent())
        return empty();
    else {
        return Optional.ofNullable(mapper.apply(value));
    }
}
```

map类似 Stream 的 map方法。处理完之后，返回的还是一个 Optional 对象，所以可以做链式调用。

```java
User user = new User();
String name = Optional.of(user).map(User::getName)
        .orElse("佚名");
System.out.println(name);
```

如上，取出user对象的name值，若name为空，返回一个默认值“佚名”（神奇的名字）。

这里，直接调用map方法，就不需要对user对象进行预先判空了。因为在map方法里边，会调用isPresent方法帮我们处理user为null的情况。

到这里，脑袋转圈快的小伙伴，是不是对开头的坑已经有启发了。

没错，我们可以通过 Optional 的链式调用，通过 map，orElse 等操作改写。如下，

```java
private static String getUserAddr1(Optional<User> user){
    //先获取address对象
    return user.map((u)->u.getAddress())
            //再获取details值，
            .map(e -> e.getDetails())
            //若detail为null，则返回一个默认值
            .orElse("地址信息未填写");
}
```

中间所有可能出现空指针的情况，Optional都会规避。因为 `value!=null`这个操作已经被封装了。而且在不同的处理阶段，Optional 会自动帮我们包装不同类型的值。

就像上边的操作，第一个map方法包装了User类型的user对象值，第二个map包装了String类型的details值，orElse 返回最终需要的字符串。

## 7 flatMap

```java
public<U> Optional<U> flatMap(Function<? super T, Optional<U>> mapper) {
    Objects.requireNonNull(mapper);
    if (!isPresent())
        return empty();
    else {
        return Objects.requireNonNull(mapper.apply(value));
    }
}
```

乍看这个方法和 map 没什么区别。其实，它们的区别就在于传入的 mapper参数的第二个泛型。

![img](data:image/gif;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAADUlEQVQImWNgYGBgAAAABQABh6FO1AAAAABJRU5ErkJggg==)map

![img](data:image/gif;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAADUlEQVQImWNgYGBgAAAABQABh6FO1AAAAABJRU5ErkJggg==)flatMap

map第二个泛型为`? extends U`，flatMap第二个泛型为`Optional<U>`。

所以，map方法在最后，用方法`Optional.ofNullable` 包装成了 Optional 。但是，flatMap就需要我们自己去包装 Optional 了。

下边就看下怎么操作 flatMap。

```java
@Test
public void test3(){
    User user = new User();
    String name = Optional.of(user).flatMap((u) -> this.getUserName(u))
        .orElse("佚名");
    System.out.println(name);
}

//把用户名包装成Optional<String>，作为 Function 接口的返回值，以适配flatMap
private Optional<String> getUserName(User user){
    return Optional.ofNullable(user.getName());
}
```

## 5.8 filter

```java
public Optional<T> filter(Predicate<? super T> predicate) {
    Objects.requireNonNull(predicate);
    if (!isPresent())
        return this;
    else
        return predicate.test(value) ? this : empty();
} 
```

见名知意，filter 是用来根据条件过滤的，如果符合条件，就返回当前 Optional 对象本身，否则返回一个值为 null的 Optional 对象。

如下，过滤姓名为空的 user。

```java
User user = new User();
//由于user没有设置 name，所以返回一个值为 null 的 optionalUser
Optional<User> optionalUser = Optional.of(user).filter((u) -> this.getUserName(u).isPresent());
//由于值为 null，所以get方法抛出异常 NoSuchElementException
optionalUser.get();
```

# 六、Stream API

首先，什么是 Stream 流？

流 （Stream） 和 Java 中的集合类似。但是集合中保存的数据，而流中保存的是，对集合或者数组中数据的操作。

之所以叫流，是因为它就像一个流水线一样。从原料经过 n 道加工程序之后，变成可用的成品。

![img](E:\学习笔记\mylearnnote\javaSE\JDK8\images\202009221020.png)

如果，你有了解过 Spark 里边的 Streaming，就会有一种特别熟悉的感觉。因为它们的思想和用法如此相似。

包括 lazy 思想，都是在需要计算结果的时候，才真正执行。类似 Spark Streaming 对 RDD 的操作，分为转换(transformation)和行动(action)。转换只是记录这些操作逻辑，只有行动的时候才会开始计算。

转换介绍：http://spark.apache.org/docs/latest/rdd-programming-guide.html#transformations

对应的，Stream API 对数据的操作，有中间操作和终止操作，只有在终止操作的时候才会执行计算。

所以，Stream 有如下特点，

- Stream 自己不保存数据。
- Stream 不会改变源对象，每次中间操作后都会产生一个新的 Stream。
- Stream 的操作是延迟的，中间操作只保存操作，不做计算。只有终止操作时才会计算结果。

那么问题来了，既然 Stream 是用来操作数据的。没有数据源，你怎么操作，因此还要有一个数据源。

于是，stream操作数据的三大步骤为：**数据源，中间操作，终止操作。**

## 6.1 数据源

流的源可以是一个数组，一个集合，一个生成器方法等等。

### 6.1.1 使用 Collection 接口中的 default 方法。

```java
default Stream<E> stream()  //返回一个顺序流
default Stream<E> parallelStream() //返回一个并行流
```

此处，我们也就明白了，为什么 JDK8 要引入默认方法了吧。

由于 Collection 集合父接口定义了这些默认方法，所以像 List，Set 这些子接口下的实现类都可以用这种方式生成一个 Stream 流。

```java
public class StreamTest {
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("zhangzan");
        list.add("lisi");
        list.add("wangwu");
        //顺序流
        Stream<String> stream = list.stream();
        //并行流
        Stream<String> parallelStream = list.parallelStream();
        //遍历元素
        stream.forEach(System.out::println);
    }
}
```

### 6..1.2  Arrays 的静态方法 stream()

```java
 static <T> Stream<T> stream(T[] array)
```

可以传入各种类型的数组，把它转化为流。如下，传入一个字符串数组。

```java
String[] arr = {"abc","aa","ef"};
Stream<String> stream1 = Arrays.stream(arr);
```

### 6.1.3 Stream接口的 of() ，generate()，iterate()方法

注意，of() 方法返回的是有限流，即元素个数是有限的，就是你传入的元素个数。

而 generate()，iterate() 这两个方法，是无限流，即元素个数是无限个。

使用方法如下，

```java
//of
Stream<Integer> stream2 = Stream.of(10, 20, 30, 40, 50);
stream.forEach(System.out::println);
//generate，每个元素都是0~99的随机数
Stream<Integer> generate = Stream.generate(() -> new Random().nextInt(100));
//iterate，从0开始迭代，每个元素依次增加2
Stream<Integer> iterate = Stream.iterate(0, x -> x + 2);
```

### 6.1.4 IntStream，LongStream，DoubleStream 的 of、range、rangeClosed 方法

它们的用法都是一样，不过是直接包装了一层。

实际，of()方法底层用的也是 Arrays.stream()方法。

以 IntStream 类为例，其他类似，

```java
IntStream intStream = IntStream.of(10, 20, 30);
//从0每次递增1，到10，包括0，但不包括10
IntStream rangeStream = IntStream.range(0, 10);
//从0每次递增1，到10，包括0和10
IntStream rangeClosed = IntStream.rangeClosed(0, 10);
```

## 6.2 中间操作

一个流可以有零个或者多个中间操作，每一个中间操作都会返回一个新的流，供下一个操作使用。

### 6.2.1 筛选与切片

常见的包括：

- filter
- limit
- skip
- distinct

用法如下：

```java
@Test
public void test1(){
    ArrayList<Employee> list = new ArrayList<>();
    list.add(new Employee("张三",3000));
    list.add(new Employee("李四",5000));
    list.add(new Employee("王五",4000));
    list.add(new Employee("赵六",4500));
    list.add(new Employee("赵六",4500));

    // filter，过滤出工资大于4000的员工
    list.stream()
        .filter((e) -> e.getSalary() > 4000)
        .forEach(System.out::println);

    System.out.println("===============");
    // limit，限定指定个数的元素
    list.stream()
        .limit(3)
        .forEach(System.out::println);

    System.out.println("===============");
    // skip，和 limit 正好相反，跳过前面指定个数的元素
    list.stream()
        .skip(3)
        .forEach(System.out::println);

    System.out.println("===============");
    // distinct，去重元素。注意自定义对象需要重写 equals 和 hashCode方法
    list.stream()
        .distinct()
        .forEach(System.out::println);
}
// 打印结果：
Employee{name='李四', salary=5000}
Employee{name='赵六', salary=4500}
Employee{name='赵六', salary=4500}
===============
Employee{name='张三', salary=3000}
Employee{name='李四', salary=5000}
Employee{name='王五', salary=4000}
===============
Employee{name='赵六', salary=4500}
Employee{name='赵六', salary=4500}
===============
Employee{name='张三', salary=3000}
Employee{name='李四', salary=5000}
Employee{name='王五', salary=4000}
Employee{name='赵六', salary=4500}
```

### 6.2.2 映射

主要是map，包括：

- map
- mapToInt
- mapToLong
- mapToDouble
- flatMap

用法如下：

```java
@Test
public void test2(){
    int[] arr = {10,20,30,40,50};
    // map，映射。每个元素都乘以2
    Arrays.stream(arr)
          .map(e -> e * 2)
          .forEach(System.out::println);

    System.out.println("===============");
    //mapToInt,mapToDouble,mapToLong 用法都一样，不同的是返回类型分别是
    //IntStream,DoubleStream,LongStream.
    Arrays.stream(arr)
          .mapToDouble(e -> e * 2 )
          .forEach(System.out::println);

    System.out.println("===============");
    Arrays.stream(arr)
          .flatMap(e -> IntStream.of(e * 2))
          .forEach(System.out::println);
}
//打印结果：
20
40
60
80
100
===============
20.0
40.0
60.0
80.0
100.0
===============
20
40
60
80
100
```

这里需要说明一下 map 和 flatMap。上边的例子看不出来它们的区别。因为测试数据比较简单，都是一维的。

其实，flatMap 可以把二维的集合映射成一维的。看起来，就像把二维集合压平似的。（ flat 的英文意思就是压平）

现在给出这样的数据，若想返回所有水果单词的所有字母（"appleorangebanana"），应该怎么做？

```java
String[] fruits = {"apple","orange","banana"};
```

先遍历 fruits 数组拿到每个单词；然后，对每个单词切分，切分后还是一个数组 。

注意，此时的数组是一个二维数组，形如 [["a","p","p","l","e"] , []，[]]。

所以需要进一步遍历，再遍历（遍历两次），如下

```java
String[] fruits = {"apple","orange","banana"};
Stream.of(fruits).map((s) -> Stream.of(s.split("")))
        .forEach(e -> e.forEach(System.out::print));
```

虽然也实现了需求，但是整个流程太复杂了，单 forEach 遍历就两次。

用 flatMap 可以简化这个过程，如下。其实，就是把中间的二维数组直接压平成一维的单个元素，减少遍历次数。

```java
Stream.of(fruits).map(s -> s.split(""))
                 .flatMap(e -> Stream.of(e))
                 .forEach(System.out::print);
```

还有一种写法，不用 map，直接 flatMap。

```java
Stream.of(fruits).flatMap(s -> Stream.of(s.split("")))
         .collect(Collectors.toList())
         .forEach(System.out::print);
```

### 6.2.3 排序

- sorted()
- sorted(Comparator<? super T> comparator)

排序有两个方法，一个是无参的，默认按照自然顺序。一个是带参的，可以指定比较器。

```java
@Test
public void test4(){
    String[] arr = {"abc","aa","ef"};
    //默认升序（字典升序）
    Stream.of(arr).sorted().forEach(System.out::println);
    System.out.println("=====");
    //自定义排序，字典降序
    Stream.of(arr).sorted((s1,s2) -> s2.compareTo(s1)).forEach(System.out::println);
} 
```

## 6.3 终止操作

**一个流只会有一个终止操作。Stream只有遇到终止操作，它的源才开始执行遍历操作。注意，在这之后，这个流就不能再使用了**。

### 6.3.1 查找与匹配

- allMatch(Predicate p)，传入一个断言型函数，检查是否匹配所有元素
- anyMatch( (Predicate p) )，检查是否匹配任意一个元素
- noneMatch(Predicate p)，检查是否没有匹配的元素，如果都不匹配，则返回 true
- findFirst()，返回第一个元素
- findAny()，返回任意一个元素
- count()，返回流中的元素总个数
- max(Comparator  c)，按给定的规则排序后，返回最大的元素
- min(Comparator c)，按给定的规则排序后，返回最小的元素
- forEach(Consumer c)，迭代遍历元素（内部迭代）

由于上边 API 过于简单，不再做例子。

### 6.3.2 规约

规约就是 reduce ，把数据集合到一起。相信你肯定听说过 hadoop 的 map-reduce ，思想是一样的。

这个方法着重说一下，比较常用，有三个重载方法。

#### 6.3.2.1 一个参数

```java
Optional<T> reduce(BinaryOperator<T> accumulator);
```

传入的是一个二元运算符，返回一个 Optional 对象。

我们需要看下 BinaryOperator 这个函数式接口的结构，不然后边就不懂了，也不知道怎么用。

```java
//BinaryOperator继承自 BiFunction<T,T,T>，我们发现它们的泛型类型都是T，完全相同
public interface BinaryOperator<T> extends BiFunction<T,T,T> {
}

public interface BiFunction<T, U, R> {
    //传入 T 和 U，返回类型 R ，这就说明它们的参数类型可以完全不相同，当然也可以完全相同
    //对应的它的子类 BinaryOperator 就是完全相同的
    R apply(T t, U u);
}
```

使用方式如下，

```java
Integer[] arr = {1,2,3,4,5,6};
Integer res1 = Stream.of(arr).reduce((x, y) -> x + y).get();
System.out.println(res1);
// 结果：21
```

它表达的意思是，反复合并计算。如上，就是先计算1和2的和，然后计算结果3再和下一个元素3求和，依次反复计算，直到最后一个元素。

#### 6.3.2.2 两个参数

```java
T reduce(T identity, BinaryOperator<T> accumulator);
```

传入两个参数，第一个参数代表初始值，第二个参数是二元运算符。返回的类型是 T ，而不是 Optional。

如下，给一个 10 的初始值，依次累加，

```java
Integer res2 = Stream.of(arr).reduce(10, (x, y) -> x + y);
System.out.println(res2);
// 结果：31
```

注意：accumulator 累加器函数需要满足结合律。如上，加法就满足结合律。

它的计算过程示意图可以用下图表示，

![](E:\学习笔记\mylearnnote\javaSE\JDK8\images\微信图片_20200922105921.jpg)

identity 先和 T1 做计算，返回值作为中间结果，参与下一次和 T2 计算，如此反复。

另外需要注意的时，源码中说明了一句，并不强制要求一定按顺序计算。

> ```java
> but is not constrained to execute sequentially.
> ```

也就是说，实际计算时有可能会和图中表示的计算顺序不太一样。比如 T1 先和 T3 运算，然后结果再和 T2 运算。

这也是为什么它要求函数符合结合律，因为交换元素顺序不能影响到最终的计算结果。

#### 6.3.2.3 三个参数

```java
<U> U reduce(U identity,
             BiFunction<U, ? super T, U> accumulator,
             BinaryOperator<U> combiner);
```

这个参数有三个，比较复杂。我们分析一下。

- U identity，这个是初始值。（但是，在并行计算中，和两个参数的 reduce 初始值含义不一样，一会儿说）x需要注意，初始值和规约函数的返回值类型一致都是 U。而 Stream 流中的元素类型是 T ，所以可以和 U 相同，也可以不相同。
- BiFunction<U, ? super T, U> accumulator，这是一个累加器。其类型是BiFunction，需要注意这个输入 U 于 T 类型的两个参数，返回类型是 U 。也就是说，输入的第一个参数和返回值类型一样，输入的第二个参数和 Stream 流中的元素类型一样。
- BinaryOperator<U> combiner，这是一个组合器。其类型是 BinaryOperator ，前面说过这个函数式接口，它是传入两个相同类型的参数，返回值类型也相同，都是 U 。需要注意的是，这个参数只有在 reduce 并行计算中才会生效。

因此，我们可以把 reduce 分为非并行和并行两种情况。

##### 6.3.2.3.1 非并行规约

非并行情况下，第三个参数不起作用，identity 代表的是初始值。

以下的计算，是初始化一个 list，并向其中添加流中的元素。

```java
Integer[] arr = {1,2,3,4,5,6};
ArrayList<Integer> res = Stream.of(arr).reduce(Lists.newArrayList(0),
                                               (l, e) -> {
                                                   l.add(e);
                                                   return l;
                                               },
                                               (l, c) -> {
                                                   //结果不会打印这句话，说明第三个参数没有起作用
                                                   System.out.println("combiner");
                                                   l.addAll(c);
                                                   return l;
                                               });
System.out.println(res);
// [0, 1, 2, 3, 4, 5, 6]
```

##### 6.3.2.3.2 并行规约

并行规约，用的是 fork-join 框架思想，分而治之。把一个大任务分成若干个子任务，然后再合并。

不了解 fork-join 的，可以看这篇文章介绍：[fork-join框架分析](https://mp.weixin.qq.com/s?__biz=MzI3MjY1MjQzNQ==&mid=2247483676&idx=1&sn=f95edb16eb909ab7061c4fa1004869db&scene=21#wechat_redirect)

所以，这里的累加器 accumulator 是用来计算每个子任务的。组合器 combiner 是用来把若干个子任务合并计算的。

下边用例子说明：

```java
Integer res4 = Stream.of(1,2,3,4).parallel().reduce(1,
                (s,e) -> s + e,
                (sum, s) -> sum + s);
System.out.println(res4); // 结果：14
```

奇了怪了，计算结果应该是 10 的，为什么是 14 呢。

这里就要说明，这个 identity 初始值了。它是在每次执行 combiner 的时候，都会把 identity 累加上。

具体执行几次 combiner  ，可以通过以下方式计算出来 。（ c 并不能代表有几个执行子任务）

```java
AtomicInteger c = new AtomicInteger(0);
Integer res4 = Stream.of(1,2,3,4).parallel().reduce(1,
        (s,e) -> s + e,
        (sum, s) -> {c.getAndIncrement(); return sum + s;});
System.out.println(c); //3
System.out.println(res4); //14
```

c 为 3 代表执行了 3 次 combiner  ，最后计算总结果时，还会再加一次初始值，所以结果为：

```java
(1+2+3+4) + (3+1) * 1 = 14
// 1+2+3+4 为正常非并行结算的和，3+1 为总共计算了几次初始值。
```

我们可以通过加大stream的数据量来验证猜想。从1 加到 100 。初始值为 2 。

```java
AtomicInteger count = new AtomicInteger(0);
int length = 100;
Integer[] arr1 = new Integer[length];
for (int i = 0; i < length; i++) {
    arr1[i] = i + 1;
}
Integer res5 = Stream.of(arr1).parallel().reduce(2,
                         (s,e) -> s + e,
                         (sum, s) -> {count.getAndIncrement(); return sum + s;});
System.out.println(count.get()); //15
System.out.println(res5); //5082 
```

即：

```java
(1+...+100) + (15+1) * 2 = 5082
```

**怎么正常使用？**

那么，问题就来了。这个并行计算不靠谱啊，都把计算结果计算错了。

这是为什么呢，是它的算法有问题么？

非也，其实是我们的用法姿势错了。可以看下源码中对 identity 的说明。

> ```
> This means that for all u, combiner(identity, u) is equal to u.
> ```

![img](E:\学习笔记\mylearnnote\javaSE\JDK8\images\202009221329.png)

意思是，需要每次 combiner 运算时，identity 的值保证 u == combiner(identity,u) 是一个恒等式。

那么，为了满足这个要求，此种情况只能让 identity = 0 。

故，改写程序如下，

```java
//其他都不变，只有 identity 由 2 改为 0
AtomicInteger count = new AtomicInteger(0);
int length = 100;
Integer[] arr1 = new Integer[length];
for (int i = 0; i < length; i++) {
    arr1[i] = i + 1;
}
Integer res5 = Stream.of(arr1).parallel().reduce(0,
                         (s,e) -> s + e,
                         (sum, s) -> {count.getAndIncrement(); return sum + s;});
System.out.println(count.get()); //15
System.out.println(res5); //5050 
```

当然，只要保证 identity 不影响这个恒等式就行。

比如，对于 set 集合会自动去重，这种情况下，也可以使用并行计算，

```java
//初始化一个set，然后把stream流的元素添加到set中，
//需要注意：用并行的方式，这个set集合必须是线程安全的。否则会报错ConcurrentModificationException
Set<Integer> res3 = Stream.of(1, 2, 3, 4).parallel().reduce(Collections.synchronizedSet(Sets.newHashSet(10),
                (l, e) -> {
                    l.add(e);
                    return l;
                },
                (l, c) -> {
                    l.addAll(c);
                    return l;
                });
System.out.println(res3);
```

##### 6.3.2.3.3 收集

收集操作，可以把流收集到 List，Set，Map等中。而且，Collectors 类中提供了很多静态方法，方便的创建收集器供我们使用。

这里举几个常用的即可。具体的 API 可以去看 Collectors  源码（基本涵盖了各种，最大值，最小值，计数，分组等功能。）。

```java
 @Test
public void test6() {
    ArrayList<Employee> list = new ArrayList<>();
    list.add(new Employee("张三", 3000));
    list.add(new Employee("李四", 5000));
    list.add(new Employee("王五", 4000));
    list.add(new Employee("赵六", 4500));

    //把所有员工的姓名收集到list中
    list.stream()
        .map(Employee::getName)
        .collect(Collectors.toList())
        .forEach(System.out::println);

    //求出所有员工的薪资平均值
    Double average = list.stream()
        .collect(Collectors.averagingDouble(Employee::getSalary));
    System.out.println(average);

}
```

# 七、日期时间新 API

JDK8 之前的时间 API 存在线程安全问题，并且设计混乱。因此，在 JDK8 就重新设计了一套 API。

如下，线程不安全的例子。

```java
@Test
public void test1() throws Exception{
    SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
    ExecutorService executorService = Executors.newFixedThreadPool(10);
    List<Future<Date>> list = new ArrayList<>();
    for (int i = 0; i < 10; i++) {
        Future<Date> future = executorService.submit(() -> sdf.parse("20200905"));
        list.add(future);
    }
    for (Future<Date> future : list) {
        System.out.println(future.get());
    }

}
```

多次运行，就会报错 java.lang.NumberFormatException 。

接下来，我们就学习下新的时间 API ，然后改写上边的程序。

## 7.1 LocalDate，LocalTime，LocalDateTime

它们都是不可变类，用法差不多。以 LocalDate 为例。

### 7.1.1 创建时间对象

- now ，静态方法，根据当前时间创建对象
- of，静态方法，根据指定日期、时间创建对象
- parse，静态方法，通过字符串指定日期

```java
LocalDate localDate1 = LocalDate.now();
System.out.println(localDate1);  //2020-09-05
LocalDate localDate2 = LocalDate.of(2020, 9, 5);
System.out.println(localDate2); //2020-09-05
LocalDate localDate3 = LocalDate.parse("2020-09-05");
System.out.println(localDate3); //2020-09-05
```

### 7.1.2 获取年月日周

- getYear，获取年
- getMonth ，获取月份，返回的是月份的枚举值
- getMonthValue，获取月份的数字（1-12）
- getDayOfYear，获取一年中的第几天（1-366）
- getDayOfMonth，获取一个月中的第几天（1-31）
- getDayOfWeek，获取一周的第几天，返回的是枚举值

```java
LocalDate currentDate = LocalDate.now();
System.out.println(currentDate.getYear()); //2020
System.out.println(currentDate.getMonth()); // SEPTEMBER
System.out.println(currentDate.getMonthValue()); //9
System.out.println(currentDate.getDayOfYear()); //249
System.out.println(currentDate.getDayOfMonth()); //5
System.out.println(currentDate.getDayOfWeek()); // SATURDAY
```

### 7.1.3 日期比较，前后或者相等

- isBefore ，第一个日期是否在第二个日期之前
- isAfter，是否在之后
- equals，日期是否相同
- isLeapYear，是否是闰年

它们都返回的是布尔值。

```java
LocalDate date1 = LocalDate.of(2020, 9, 5);
LocalDate date2 = LocalDate.of(2020, 9, 6);
System.out.println(date1.isBefore(date2)); //true
System.out.println(date1.isAfter(date2)); //false
System.out.println(date1.equals(date2)); //false
System.out.println(date1.isLeapYear()); //true
```

### 7.1.4 日期加减

- plusDays,  加几天
- plusWeeks, 加几周
- plusMonths,  加几个月
- plusYears，加几年

减法同理，

```java
LocalDate nowDate = LocalDate.now();
System.out.println(nowDate);  //2020-09-05
System.out.println(nowDate.plusDays(1)); //2020-09-06
System.out.println(nowDate.plusWeeks(1)); //2020-09-12
System.out.println(nowDate.plusMonths(1)); //2020-10-05
System.out.println(nowDate.plusYears(1)); //2021-09-05
```

## 7.2 时间戳 Instant

Instant 代表的是到从 UTC 时区 1970年1月1日0时0分0秒开始计算的时间戳。

```java
Instant now = Instant.now();
System.out.println(now.toString()); // 2020-09-05T14:11:07.074Z
System.out.println(now.toEpochMilli()); // 毫秒数， 1599315067074 
```

## 7.3 时间段 Duration

用于表示时间段 ，可以表示 LocalDateTime 和 Instant 之间的时间段，用 between 创建。

```java
LocalDateTime today = LocalDateTime.now(); //今天的日期时间
LocalDateTime tomorrow = today.plusDays(1); //明天
Duration duration = Duration.between(today, tomorrow); //第二个参数减去第一个参数的时间差
System.out.println(duration.toDays()); //总天数，1
System.out.println(duration.toHours()); //小时，24
System.out.println(duration.toMinutes()); //分钟，1440
System.out.println(duration.getSeconds()); //秒，86400
System.out.println(duration.toMillis()); //毫秒，86400000
System.out.println(duration.toNanos()); // 纳秒，86400000000000
```

## 7.4 日期段 Period

和时间段 Duration，但是 Period 只能精确到年月日。

有两种方式创建 Duration 。

```
LocalDate today = LocalDate.now(); //今天
LocalDate date = LocalDate.of(2020,10,1); //国庆节
//1. 用 between 创建 Period 对象
Period period = Period.between(today, date);
System.out.println(period); // P26D
//2. 用 of 创建 Period 对象
Period of = Period.of(2020, 9, 6);
System.out.println(of); // P2020Y9M6D
// 距离国庆节还有 0 年 0 月 26 天 
System.out.printf("距离国庆节还有 %d 年 %d 月 %d 天" , period.getYears(),period.getMonths(),period.getDays());
```

## 7.5 时区 ZoneId

ZoneId 表示不同的时区。

- getAvailableZoneIds() ，获取所有时区信息，大概40多个时区
- of(id)，根据时区id获得对应的 ZoneId 对象
- systemDefault，获取当前时区

```java
Set<String> availableZoneIds = ZoneId.getAvailableZoneIds();
availableZoneIds.forEach(System.out::println); //打印所有时区
ZoneId of = ZoneId.of("Asia/Shanghai");   //获取亚洲上海的时区对象
System.out.println(of);  
System.out.println(ZoneId.systemDefault()); //当前时区为：Asia/Shanghai
```

## 7.6 日期时间格式化

JDK1.8 提供了线程安全的日期格式化类 DateTimeFormatter。

```java
DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
// 1. 日期时间转化为字符串。有两种方式
String format = dtf.format(LocalDateTime.now());
System.out.println(format); // 2020-09-05 23:02:02
String format1 = LocalDateTime.now().format(dtf); //实际上调用的也是 DateTimeFormatter 类的format方法
System.out.println(format1); // 2020-09-05 23:02:02

// 2. 字符串转化为日期。有两种方式，需要注意，月和日位数要补全两位
//第一种方式用的是，DateTimeFormatter.ISO_LOCAL_DATE_TIME ，格式如下
LocalDateTime parse = LocalDateTime.parse("2020-09-05T00:00:00");
System.out.println(parse); // 2020-09-05T00:00
//第二种方式可以自定义格式
LocalDateTime parse1 = LocalDateTime.parse("2020-09-05 00:00:00", dtf);
System.out.println(parse1); // 2020-09-05T00:00
```

## 7.7 改为线程安全类

接下来，就可以把上边线程不安全的类改写为新的时间 API  。

```java
@Test
public void test8() throws Exception{
    // SimpleDateFormat 改为 DateTimeFormatter
    DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyyMMdd");
    ExecutorService executorService = Executors.newFixedThreadPool(10);
    // Date 改为 LocalDate
    List<Future<LocalDate>> list = new ArrayList<>();
    for (int i = 0; i < 10; i++) {
        //日期解析改为 LocalDate.parse("20200905",dtf)
        Future<LocalDate> future = executorService.submit(() -> LocalDate.parse("20200905",dtf));
        list.add(future);
    }
    for (Future<LocalDate> future : list) {
        System.out.println(future.get());
    }

}
```