**java赋值是复制对象引用**，如果我们想要得到一个对象的副本，使用赋值操作是无法达到目的的：

```java
@Test
public void testassign(){
  Person p1=new Person();
  p1.setAge(31);
  p1.setName("Peter");

  Person p2=p1;
  System.out.println(p1==p2);//true
}
```

如果创建一个对象的新的副本，也就是说他们的初始状态完全一样，但以后可以改变各自的状态，而互不影响，就需要用到java中对象的复制，如原生的clone()方法。

## 1.1 如何进行对象克隆

Object对象有个clone()方法，实现了对象中各个属性的复制，但它的可见范围是protected的，所以实体类使用克隆的前提是：

**① 实现Cloneable接口，这是一个标记接口，自身没有方法。** 
**② 覆盖clone()方法，可见性提升为public。**

```java
@Data
public class Person implements Cloneable {
    private String name;
    private Integer age;
    private Address address;
    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}

@Test
public void testShallowCopy() throws Exception{
  Person p1=new Person();
  p1.setAge(31);
  p1.setName("Peter");

  Person p2=(Person) p1.clone();
  System.out.println(p1==p2);//false
  p2.setName("Jacky");
  System.out.println("p1="+p1);//p1=Person [name=Peter, age=31]
  System.out.println("p2="+p2);//p2=Person [name=Jacky, age=31]
}
```

该测试用例只有两个基本类型的成员，测试达到目的了。

事情貌似没有这么简单，为Person增加一个Address类的成员：

```java
@Data
public class Address {
    private String type;
    private String value;
}
```

再来测试，问题来了。

```java
@Test
public void testShallowCopy() throws Exception{
  Address address=new Address();
  address.setType("Home");
  address.setValue("北京");

  Person p1=new Person();
  p1.setAge(31);
  p1.setName("Peter");
  p1.setAddress(address);

  Person p2=(Person) p1.clone();
  System.out.println(p1==p2);//false

  p2.getAddress().setType("Office");
  System.out.println("p1="+p1);
  System.out.println("p2="+p2);
}
```

查看输出：

```
false
p1=Person(name=Peter, age=31, address=Address(type=Office, value=北京))
p2=Person(name=Peter, age=31, address=Address(type=Office, value=北京))
```

遇到了点麻烦，只修改了p2的地址类型，两个地址类型都变成了Office。

## 1.2 浅拷贝和深拷贝

前面实例中是浅拷贝和深拷贝的典型用例。

**浅拷贝**：**被复制对象的所有值属性都含有与原来对象的相同，而所有的对象引用属性仍然指向原来的对象**。

**深拷贝**：**在浅拷贝的基础上，所有引用其他对象的变量也进行了clone，并指向被复制过的新对象**。

也就是说，一个**默认的clone()方法实现机制，仍然是赋值**。

**如果一个被复制的属性都是基本类型，那么只需要实现当前类的cloneable机制就可以了，此为浅拷贝**。

**如果被复制对象的属性包含其他实体类对象引用，那么这些实体类对象都需要实现cloneable接口并覆盖clone()方法**。

```java
@Data
public class Address implements Cloneable {
    private String type;
    private String value;

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}
```

**这样还不够，Person的clone()需要显式地clone其引用成员**。

```java
@Data
public class Person implements Cloneable {
    private String name;
    private Integer age;
    private Address address;
    @Override
    protected Object clone() throws CloneNotSupportedException {
        Object obj=super.clone();
        Address a=((Person)obj).getAddress();
        ((Person)obj).setAddress((Address) a.clone());
        return obj;
    }
}
```

重新跑前面的测试用例：

```
false
p1=Person(name=Peter, age=31, address=Address(type=Home, value=北京))
p2=Person(name=Peter, age=31, address=Address(type=Office, value=北京))
```

## 1.3 clone方式深拷贝小结

① **如果有一个非原生成员，如自定义对象的成员**，那么就需要：

- 该成员实现Cloneable接口并覆盖clone()方法，不要忘记提升为public可见。
- 同时，**修改被复制类的clone()方法，增加成员的克隆逻辑**。

② **如果被复制对象不是直接继承Object，中间还有其它继承层次，每一层super类都需要实现Cloneable接口并覆盖clone()方法**。

与对象成员不同，继承关系中的clone不需要被复制类的clone()做多余的工作。

一句话来说，**如果实现完整的深拷贝，需要被复制对象的继承链、引用链上的每一个对象都实现克隆机制**。

前面的实例还可以接受，如果有N个对象成员，有M层继承关系，就会很麻烦。

##1.4 利用序列化实现深拷贝

clone机制不是强类型的限制，比如实现了Cloneable并没有强制继承链上的对象也实现；也没有强制要求覆盖clone()方法。因此编码过程中比较容易忽略其中一个环节，对于复杂的项目排查就是困难了。

要寻找可靠的，简单的方法，序列化就是一种途径。

- **被复制对象的继承链、引用链上的每一个对象都实现java.io.Serializable接口。这个比较简单，不需要实现任何方法，serialVersionID的要求不强制**，对深拷贝来说没毛病。
- **实现自己的deepClone方法，将this写入流，再读出来。俗称：冷冻-解冻**。

```java
@Data
public class Person implements Serializable {
    private String name;
    private Integer age;
    private Address address;
    public Person deepClone() {
        Person p2=null;
        Person p1=this;
        PipedOutputStream out=new PipedOutputStream();
        PipedInputStream in=new PipedInputStream();
        try {
            in.connect(out);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try(ObjectOutputStream bo=new ObjectOutputStream(out);
                ObjectInputStream bi=new ObjectInputStream(in);) {
            bo.writeObject(p1);
            p2=(Person) bi.readObject();

        } catch (Exception e) {
            e.printStackTrace();
        }
        return p2;
    }
}
```

## 1.5 原型工厂类

为了便于测试，也节省篇幅，封装一个工厂类。

公平起见，避免某些工具库使用缓存机制，使用原型方式工厂。

```java
public class PersonFactory{
    public static Person newPrototypeInstance(){
        Address address = new Address();
        address.setType("Home");
        address.setValue("北京");

        Person p1 = new Person();
        p1.setAddress(address);
        p1.setAge(31);
        p1.setName("Peter");
        return p1;
    }
}
```

## 1.6 利用Dozer拷贝对象

Dozer是一个Bean处理类库。

maven依赖

```xml
<dependency>
  <groupId>net.sf.dozer</groupId>
  <artifactId>dozer</artifactId>
  <version>5.5.1</version>
</dependency>
```

测试用例：

```java
@Data
public class Person {
    private String name;
    private Integer age;
    private Address address;

    @Test
    public void testDozer() {
    Person p1=PersonFactory.newPrototypeInstance();
        Mapper mapper = new DozerBeanMapper();
        Person p2 = mapper.map(p1, Person.class);
        p2.getAddress().setType("Office");
        System.out.println("p1=" + p1);
        System.out.println("p2=" + p2);
    }
}

@Data
public class Address {
    private String type;
    private String value;
}
```

输出：

```
p1=Person(name=Peter, age=31, address=Address(type=Home, value=北京))
p2=Person(name=Peter, age=31, address=Address(type=Office, value=北京))
```

注意：在万次测试中dozer有一个很严重的问题，如果DozerBeanMapper对象在for循环中创建，效率（dozer:7358）降低近10倍。由于DozerBeanMapper是线程安全的，所以不应该每次都创建新的实例。可以自带的单例工厂DozerBeanMapperSingletonWrapper来创建mapper，或集成到spring中。

还有更暴力的，创建一个People类：

```java
@Data
public class People {
    private String name;
    private String age;//这里已经不是Integer了
    private Address address;

    @Test
    public void testDozer() {
    Person p1=PersonFactory.newPrototypeInstance();
        Mapper mapper = new DozerBeanMapper();
        People p2 = mapper.map(p1, People.class);
        p2.getAddress().setType("Office");
        System.out.println("p1=" + p1);
        System.out.println("p2=" + p2);
    }
}
```

只要属性名相同，干~

继续蹂躏：

```java
@Data
public class People {
    private String name;
    private String age;
    private Map<String,String> address;//��

    @Test
    public void testDozer() {
    Person p1=PersonFactory.newPrototypeInstance();
        Mapper mapper = new DozerBeanMapper();
        People p2 = mapper.map(p1, People.class);
        p2.getAddress().put("type", "Office");
        System.out.println("p1=" + p1);
        System.out.println("p2=" + p2);
    }
}
```

## 1.7 利用Commons-BeanUtils复制对象

maven依赖

```xml
<dependency>
  <groupId>commons-beanutils</groupId>
  <artifactId>commons-beanutils</artifactId>
  <version>1.9.3</version>
</dependency>
```

测试用例：

```java
@Data
public class Person {
    private String name;
    private String age;
    private Address address;

    @Test
    public void testCommonsBeanUtils(){
    Person p1=PersonFactory.newPrototypeInstance();
        try {
            Person p2=(Person) BeanUtils.cloneBean(p1);
            System.out.println("p1=" + p1);
            p2.getAddress().setType("Office");
            System.out.println("p2=" + p2);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

## 1.8 利用cglib复制对象

maven依赖：

```xml
<dependency>
  <groupId>cglib</groupId>
  <artifactId>cglib</artifactId>
  <version>3.2.4</version>
</dependency>
```

测试用例：

```java
@Test
public void testCglib(){
  Person p1=PersonFactory.newPrototypeInstance();
  BeanCopier beanCopier=BeanCopier.create(Person.class, Person.class, false);
  Person p2=new Person();
  beanCopier.copy(p1, p2,null);
  p2.getAddress().setType("Office");
  System.out.println("p1=" + p1);
  System.out.println("p2=" + p2);
}
```

结果大跌眼镜，cglib这么牛x，居然是浅拷贝。不过cglib提供了扩展能力：

```java
@Test
public void testCglib(){
  Person p1=PersonFactory.newPrototypeInstance();
  BeanCopier beanCopier=BeanCopier.create(Person.class, Person.class, true);
  Person p2=new Person();
  beanCopier.copy(p1, p2, new Converter(){
    @Override
    public Object convert(Object value, Class target, Object context) {
      if(target.isSynthetic()){
        BeanCopier.create(target, target, true).copy(value, value, this);
      }
      return value;
    }
  });
  p2.getAddress().setType("Office");
  System.out.println("p1=" + p1);
  System.out.println("p2=" + p2);
}
```

## 1.9 Orika复制对象

orika的作用不仅仅在于处理bean拷贝，更擅长各种类型之间的转换。

maven依赖：

```xml
<dependency>
  <groupId>ma.glasnost.orika</groupId>
  <artifactId>orika-core</artifactId>
  <version>1.5.0</version>
</dependency>
</dependencies>
```

测试用例：

```java
@Test
public void testOrika() {
  MapperFactory mapperFactory = new DefaultMapperFactory.Builder().build();

  mapperFactory.classMap(Person.class, Person.class)
  .byDefault()
  .register();
  ConverterFactory converterFactory = mapperFactory.getConverterFactory();
  MapperFacade mapper = mapperFactory.getMapperFacade();

  Person p1=PersonFactory.newPrototypeInstance();
  Person p2 = mapper.map(p1, Person.class);
  System.out.println("p1=" + p1);
  p2.getAddress().setType("Office");
  System.out.println("p2=" + p2);
}
```

## 1.10 Spring BeanUtils复制对象

给Spring个面子，貌似它不支持深拷贝。

```java
Person p1=PersonFactory.newPrototypeInstance();
Person p2 = new Person();
Person p2 = (Person) BeanUtils.cloneBean(p1);
//BeanUtils.copyProperties(p2, p1);//这个更没戏
```

##1.11 深拷贝性能对比

```java
@Test
public void testBatchDozer(){
  Long start=System.currentTimeMillis();
  Mapper mapper = new DozerBeanMapper();
  for(int i=0;i<10000;i++){
    Person p1=PersonFactory.newPrototypeInstance();
    Person p2 = mapper.map(p1, Person.class);
  }
  System.out.println("dozer:"+(System.currentTimeMillis()-start));
  //dozer:721
}
@Test
public void testBatchBeanUtils(){
  Long start=System.currentTimeMillis();
  for(int i=0;i<10000;i++){
    Person p1=PersonFactory.newPrototypeInstance();
    try {
      Person p2=(Person) BeanUtils.cloneBean(p1);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
  System.out.println("commons-beanutils:"+(System.currentTimeMillis()-start));
  //commons-beanutils：229
}
@Test
public void testBatchCglib(){
  Long start=System.currentTimeMillis();
  for(int i=0;i<10000;i++){
    Person p1=PersonFactory.newPrototypeInstance();
    BeanCopier beanCopier=BeanCopier.create(Person.class, Person.class, true);
    Person p2=new Person();
    beanCopier.copy(p1, p2, new Converter(){
      @Override
      public Object convert(Object value, Class target, Object context) {
        if(target.isSynthetic()){
          BeanCopier.create(target, target, true).copy(value, value, this);
        }
        return value;
      }
    });
  }
  System.out.println("cglib:"+(System.currentTimeMillis()-start));
  //cglib:133
}
@Test
public void testBatchSerial(){
  Long start=System.currentTimeMillis();
  for(int i=0;i<10000;i++){
    Person p1=PersonFactory.newPrototypeInstance();
    Person p2=p1.deepClone();
  }
  System.out.println("serializable:"+(System.currentTimeMillis()-start));
  //serializable:687
}
@Test
public void testBatchOrika() {
  MapperFactory mapperFactory = new DefaultMapperFactory.Builder().build();

  mapperFactory.classMap(Person.class, Person.class)
  .field("name", "name")
  .byDefault()
  .register();
  ConverterFactory converterFactory = mapperFactory.getConverterFactory();
  MapperFacade mapper = mapperFactory.getMapperFacade();

  Long start=System.currentTimeMillis();
  for(int i=0;i<10000;i++){
    Person p1=PersonFactory.newPrototypeInstance();
    Person p2 = mapper.map(p1, Person.class);
  }
  System.out.println("orika:"+(System.currentTimeMillis()-start));
  //orika:83
}

@Test
public void testBatchClone(){
  Long start=System.currentTimeMillis();
  for(int i=0;i<10000;i++){
    Person p1=PersonFactory.newPrototypeInstance();
    try {
      Person p2=(Person) p1.clone();
    } catch (CloneNotSupportedException e) {
      e.printStackTrace();
    }
  }
  System.out.println("clone:"+(System.currentTimeMillis()-start));
  //clone:8
}
```

性能比较：

```
//dozer:721
//commons-beanutils：229
//cglib:133
//serializable:687
//orika:83
//clone:8
```

## 1.12 深拷贝总结

原生的clone效率无疑是最高的，用脚趾头都能想到。

偶尔用一次，用哪个都问题都不大。

一般性能要求稍高的应用场景，cglib和orika完全可以接受。

另外一个考虑的因素，如果项目已经引入了某个依赖，就用那个依赖来做吧，没必要再引入一个第三方依赖。