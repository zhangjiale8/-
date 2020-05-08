# final, finally, finalize的区别

## 1.1 final

### 1.1.1 final：修饰符（关键字）有三种用法：

 （1）**如果一个类被声明为final，意味着它不能再派生出新的子类，即不能被继承，因此它和abstract是反义词**。当我们需要让一个类永远不被继承，此时就可以用final修饰，但要注意：**final类中所有的成员方法都会隐式的定义为final方法**。

（2）**将变量声明为final，可以保证它们在使用中不被改变，被声明为final 的变量必须在声明时给定初值，而在以后的引用中只能读取不可修改**。
 	**当final修饰一个基本数据类型时，表示该基本数据类型的值一旦在初始化后便不能发生变化**；**如果final修饰一个引用类型时，则在对其初始化之后便不能再让其指向其他对象了，但该引用所指向的对象的内容是可以发生变化的**。本质上是一回事，因为引用的值是一个地址，final要求该值，即地址的值不发生变化。　
 　**final修饰一个成员变量（属性），必须要显示初始化**。这里有两种初始化方式，**一种是在变量声明的时候初始化；第二种方法是在声明变量的时候不赋初值，但是要在这个变量所在的类的所有的构造函数中对这个变量赋初值**。
 　**当函数的参数类型声明为final时，说明该参数是只读型的**。即你可以读取使用该参数，但是无法改变该参数的值。
 　**注意：**
 　在java中，String被设计成final类，那为什么平时使用时，String的值可以被改变呢？
 　**字符串常量池是Java堆内存中一个特殊的存储区域，当我们建立一个String对象时，假设常量池不存在该字符串，则创建一个，若存在则直接引用已经存在的字符串**。当我们对String对象值改变的时候，例如 String a="A"; a="B" 。a是String对象的一个引用（我们这里所说的String对象其实是指字符串常量），当执行a=“B”时，并不是原本String对象("A")发生改变，而是创建一个新的对象("B")，令a引用它。

（3）**被声明为final 的方法也同样只能使用，不能在子类中被重写**。

### 1.1.2 使用final方法的原因主要有两个：
 　(a) **把方法锁定，以防止继承类对其进行更改**。
 　(b) **效率**，在早期的java版本中，会将final方法转为内嵌调用。但若方法过于庞大，可能在性能上不会有多大提升。因此在最近版本中，不需要final方法进行这些优化了。
 final方法意味着“**最后的、最终的**”含义，即此方法不能被重写。
 注意：若**父类中final方法的访问权限为private，将导致子类中不能直接继承该方法**。因此，此时可以在子类中定义相同方法名的函数，此时不会与重写final矛盾，而是在子类中重新地定义了新方法。

```java
class A{
    private final void getName(){
    }
}
public class B extends A{
    public void getName(){
    }
    public static void main(String[]args){
        System.out.println("OK");
    }
}
```

## 1.2 finally

​	**finally作为异常处理的一部分，它只能用在try/catch语句中，并且附带一个语句块**，表示这段语句**最终一定会被执行**（**不管有没有抛出异常，只要JVM不关闭，与finally对应的try语句块得到执行的情况下，都能执行**）。经常被用在需要释放外部资源的情况下。

### 1.2.1 finally 语句块没有执行的情况：

 （1）**在 try 语句块中执行System.exit (0) 语句，终止Java 虚拟机的运行**。
 （2）**当一个线程在执行 try 语句块或者 catch 语句块时被打断（interrupted）或者被终止（killed），与其相对应的 finally 语句块可能不会执行**。
 （3）**极端情况，就是在线程运行 try 语句块或者 catch 语句块时，突然死机或者断电，finally 语句块肯定不会执行了**。

## 1.3 finalize

​	**finalize()是在java.lang.Object里定义的，也就是说每一个对象都有这么个方法**。J**ava中允许使用finalize() 方法在垃圾收集器将对象从内存中清除出去之前做必要的清理工作**。这个方法是由**垃圾收集器在销毁对象时调用的，通过重写finalize() 方法可以整理系统资源或者执行其他清理工作**。
 	这个方法在gc启动，该对象被回收的时候被调用。其实gc可以回收大部分的对象（凡是new出来的对象，gc都能搞定，一般情况下我们又不会用new以外的方式去创建对象），所以一般是不需要程序员去实现finalize的。
 **特殊情况下，需要程序员实现finalize，当对象被回收的时候释放一些资源**，比如：一个socket链接，在对象初始化时创建，整个生命周期内有效，那么就需要实现finalize，关闭这个链接。
 使用finalize还需要注意一个事，调用**super.finalize()**;
 一个对象的finalize()方法只会被调用一次，而且finalize()被调用不意味着gc会立即回收该对象，所以有可能调用finalize()后，该对象又不需要被回收了，然后到了真正要被回收的时候，因为前面调用过一次，所以不会调用finalize()，产生问题。 所以，推荐不要使用finalize()方法，它跟析构函数不一样。

## 1.4 易错点：
 ### 1.4.1 

![img](\java笔记\反射\image\final&finally&finalize易错点01.png)

**int x被修饰成final，意味着x不能在addOne method中被修改。所以编译报错**。

### 1.4.2

```java
public class QAQ {
public static void main(String[] args) {
        Tha o = new Tha();
        new QAQ().addOne(o);
    }
    public void addOne(final Tha o) {
        o.i++;
    }
}
```



```cpp
public class Tha {
    public int i;
}
```

答案: 正确。在addOne method中，参数o被修饰成final。如果在addOne method里我们修改了o的reference
 (比如: o = new Tha();)，那么如同上例这题也是错的。但这里修改的是o的member vairable
 (成员变量)，而o的reference并没有改变。

原文链接：https://www.jianshu.com/p/c133d4392954
