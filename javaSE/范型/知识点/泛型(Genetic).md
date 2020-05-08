# 泛型(Genetic)

​	jdk5以前，对象保存到集合中就会失去其特性，取出时通常要程序员手工进行类型的强制转换，这样不可避免就会引发程序的一些安全性问题。jdk5中的泛型允许程序员在编写集合代码时，就限制集合的处理类型，从而把原来程序运行时可能发生问题，转变为编译时的问题，以此提高程序的可读性和稳定性（尤其在大型程序中更为突出）。
**使用泛型时，泛型类型必须为引用类型，不能是基本数据类型**。
**注意**：泛型是提供给javac编译器使用的，它用于限定集合的输入类型，让编译器在源代码级别上，就挡住向集合中插入非法数据。但**编译器编译完带有泛型的Java程序后，生成的class文件中将不再带有泛型信息，以此使程序运行效率不受到影响，这个过程称之为“擦除”**。

泛型的基本术语，以ArrayList<E>为例:<>念**typeof**

- ArrayList<E>中的**E称为类型参数变量**
- ArrayList<Integer>中**的Integer称为实际类型参数**
- **整个ArrayList<E>称为泛型类型**
- **整个ArrayList<Integer>称为参数化的类型**(ParameterizedType)

**用泛型时，如果两边都使用到泛型时，两边的泛型必须要一样。 只用一边也可以**。如：

![img](\java笔记\范型\image\范型01.png)

**我们定义泛型类，泛型方法，泛型接口的时候经常会碰见很多不同的通配符T，E，K，V等等，这些通配符表示什么意思呢？**
这几个其实没什么区别，只不过是一个约定好的代码，也就是说使用大写字母A、B、C、D......X、Y、Z定义的，就都是泛型，把T换成A也一样，这里T只是名字上的意义而已。将T换成了A，在执行效果上是没有任何区别的，只不过我们约定好了**T代表type**，所以按照规范来增加了代码的可读性。如果要定义三个或三个以上的泛型参数可以使用T1, T2, ..., Tn。

- **？ 表示不确定的Java类型**
- **T (type) 表示具体的一个Java类型**
- **K V (key value) 分别代表Java键值中的Key Value**
- **E (element) 代表Element**

## 1.1 List<T>，List<Object>，List<?>区别

- ArrayList<T> al=new ArrayList<T>(); 指定集合元素**只能是T类型**
- ArrayList<?> al=new ArrayList<?>(); 集合元素可以是**任意类型**。这种没有意义，一般是方法中，只是为了说明用法
- ArrayList<? extends E> al=new ArrayList<? extends E>();
  泛型的限定：
  **? extends E: 接收E类型或者E的子类型**。
  **? super E: 接收E类型或者E的父类型**

### 1.1.1 注意：

（1）**Object和T不同点在于，Object是一个实打实的类，并没有泛指谁，而 T 可以泛指Object**。
比方public void printList(List<T> list){}方法中可以传入List<Object> list类型参数，也可以传入List<String> list类型参数，但是public void printList(List<Object> list){}就只可以传入List<Object> list类型参数，因为Object类型并没有泛指谁，是一个确定的类型。

（2）?和T区别：**? 是一个不确定类，? 和T都表示不确定的类型**。但**如果是T的话，函数里面可以对T进行操作**

​	比方 T zoo = getZoo()，而不能用? zoo = getZoo()。

## 1.2 T，Class，Class区别
​	**T是一种具体的类**。例如String，List，Map......等等，这些都是属于具体的类，这个比较好理解。
Class是什么呢，**Class也是一个类**，但Class是存放上面String，List，Map......类信息的一个类，有点抽象，我们一步一步来看 。

### 1.2.1 如何获取到Class类，有三种方式：

（1）调用 Object 类的 getClass()方法来得到Class对象，这也是最常见的产生Class对象的方法。例如：

```cpp
List list = null;
Class clazz = list.getClass();
```

（2）使用Class类的中静态forName()方法获得与字符串对应的Class对象。例如：

```bash
Class clazz = Class.forName("com.sxy.Teacher");
```

（3）如果T是一个Java类型，那么T.class就代表了匹配的类对象。



```csharp
Class clazz = List.class;  
```

## 1.3 Class<T>和Class<?>适用于什么时候呢？

使用Class<T>和Class<?>**多发生在反射场景下**。如果不使用泛型，反射创建一个类如下：

```bash
Teacher t = (Teacher) Class.forName("com.sxy.Teacher").newInstance();
```

**需要强转，如果反射的类型不是Teacher类，就会报java.lang.ClassCastException错误。但是使用Class<T>泛型后，不用强转了**。

## 1.4 **Class<T>和Class<?>什么区别呢？**

（1）Class<T>在实例化的时候，T要替换成具体类；

（2）Class<?>它是个通配泛型，?可以代表任何类型，**主要用于声明时的限制情况**。

例如可以声明一个：

```php
public Class<?> clazz;
```

而以下的声明却不可以，因为T需要指定类型：

```php
public Class<T> clazz;
```

**所以当不知道声明什么类型的Class的时候可以定义一个Class<?>。Class<?>可以用于参数类型定义，方法返回值定义等**。