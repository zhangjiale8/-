# 1.1 基本介绍

（1）Object是所有类的父类，任何类都默认继承Object。
（2）Object是类层次结构的根类。每个类都使用Object作为超类。所有对象(包括数组)都实现这个类的所有方法。

## 1.1.1 源码

```java
public class Object {
	private static native void registerNatives();
    /*对象初始化时自动调用此方法*/
    static {
        registerNatives();
    }
    /*返回此Object的运行时类*/
    public final native Class<?> getClass();
    /*
    hashCode的常规协定是：
    1.在java应用程序执行期间,在对同一对象多次调用hashCode()方法时,必须一致地返回相同的整数,前提是将对象进行equals比较时所用的信息没有被修改。从某一应用程序的一次执行到同一应用程序的另一次执行,该整数无需保持一致。
    2.如果根据equals(object)方法,两个对象是相等的,那么对这两个对象中的每个对象调用hashCode方法都必须生成相同的整数结果。
    3.如果根据equals(java.lang.Object)方法,两个对象不相等,那么对这两个对象中的任一对象上调用hashCode()方法不要求一定生成不同的整数结果。但是,程序员应该意识到,为不相等的对象生成不同整数结果可以提高哈希表的性能。
    */
    public native int hashCode();
    /*比较对象的内存地址,跟String.equals方法不同,它比较的只是对象的值*/
    public boolean equals(Object obj) {
        return (this == obj);
    }
    /*本地clone方法,用于对象的复制*/
    protected native Object clone() throws CloneNotSupportedException;
    /*
    返回该对象的字符串表示,非常重要的方法
    getClass().getName();获取字节码文件的对应全路径名例如java.lang.Object
    Integer.toHexString(hashCode());将哈希值转成16进制数格式的字符串。
    */
    public String toString() {
        return getClass().getName() + "@" + Integer.toHexString(hashCode());
    }
    /*唤醒在此对象监视器上等待的单个线程*/
    public final native void notify();
    /*唤醒在此对象监视器上等待的所有线程*/
    public final native void notifyAll();
    /*
    在其他线程调用此对象的notify()方法或notifyAll()方法前,导致当前线程等待。换句话说,此方法的行为就好像它仅执行wait(0)调用一样。
    当前线程必须拥有此对象监视器。该线程发布对此监视器的所有权并等待,直到其他线程通过调用notify方法或notifyAll方法通知在此对象的监视器上等待的线程醒来,然后该线程将等到重新获得对监视器的所有权后才能继续执行。
    */
    public final native void wait(long timeout) throws InterruptedException;
    /*在其他线程调用此对象的notify()方法或notifyAll()方法,或者超过指定的时间量前,导致当前线程等待*/
    public final void wait(long timeout, int nanos) throws InterruptedException {
        if (timeout < 0) {
            throw new IllegalArgumentException("timeout value is negative");
        }

        if (nanos < 0 || nanos > 999999) {
            throw new IllegalArgumentException(
                                "nanosecond timeout value out of range");
        }

        if (nanos > 0) {
            timeout++;
        }

        wait(timeout);
    }

    public final void wait() throws InterruptedException {
        wait(0);
    }


    /*当垃圾回收期确定不存在对该对象的更多引用时,由对象的垃圾回收器调用此方法。*/
    protected void finalize() throws Throwable { }
}
```

**注：String中equals方法**

```java
public boolean equals(Object anObject) {
    if (this == anObject) {
        return true;
    }
    if (anObject instanceof String) {
        String anotherString = (String)anObject;
        int n = value.length;
        if (n == anotherString.value.length) {
            char v1[] = value;
            char v2[] = anotherString.value;
            int i = 0;
            while (n-- != 0) {
                if (v1[i] != v2[i])
                    return false;
                i++;
            }
            return true;
        }
    }
    return false;
}
```

# 1.2 构造方法
 	源码中并没有Object的构造方法，但是，同样的，编译器在编译期间会给Object（事实上，所有的Java类，只要类中没有构造方法，编译器都会默认的给一个空构造方法，若已有构造方法，则不会添加）一个默认的空的构造方法。

# 1.3 对象相等判断方法： equals

 equals() 的作用是 **用来判断两个对象是否相等**。

 equals() 定义在JDK的Object.java中。

 **通过判断两个对象的地址是否相等(即，是否是同一个对象)来区分它们是否相等。**

源码如下：

```java
 public boolean equals(Object obj) {
 return (this == obj);
 }
```



​	既然Object.java中定义了equals()方法，这就意味着所有的Java类都实现了equals()方法，所有的类都可以通过equals()

比较两个对象是否相等。

​	 但是，**使用默认的“equals()”方法，等价于“==”方法**。因此，我们通常会重写equals()方法：**若两个对象的内容相等，则equals()方法返回true；否则，返回fasle**。

​	原则上或者说语义上，设计上目的，equals的作用意义，是用来比较两个对象是否相等，这里是我们通常理解的相等：

**即两个对象其内容是否相等（相同）**。

​	而程序上来看，这里的作用是判断两个对象是否是同一个对象，**即比较其内存地址**；

​	如果想比较两个对象是否是同一个对象（这里是说两个引用是否指向同一个对象），直接用==比较即可（==比较的就是对象的内存地址）。

​	 **默认的equals实现，比较的是两对象内存地址，即，若子类不重写equals方法，其作用等同于==**。

## 1.3.1 根据“类是否覆盖equals()方法”，将它分为2类。

（1）若某个类没有覆盖equals()方法，当它的通过equals()比较两个对象时，实际上是比较两个对象是不是同一个对象。这时，等价于通过“==”去比较这两个对象。

（2）我们可以覆盖类的equals()方法，来让equals()通过其它方式比较两个对象是否相等。通常的做法是：若两个对象的内容相等，则equals()方法返回true；否则，返回fasle。

​	**我们很大部分时间都是进行两个对象的比较，这个时候Object的equals()方法就局限了，所以才会有String这些类对equals方法的改写，依次类推Double、Integer、Math。。。。等等这些类都是重写了equals()方法的，从而进行的是内容的比较**。

```java
class Student
{
    String name;
    int age;
    public Student(String name,int age)
    {
        this.name=name;
        this.age=age;
    }
}

public class Text{
    public static void main(String[] args)
    {
        Student s1 = new Student("Mary",21);
        Student s2 = new Student("Mary",21);
        System.out.println(s1.equals(s2));//输出一个boolean值
        System.out.println(s1.equals(s2)?"s1和s2是同一个人":"s1和s2不是同一个人");//?:条件运算符
    }
}

输出结果：
s1和s2不是同一个人
```

很明显输出的结果是错误的，因为equals()方法比较的是两个对象的地址，所以必须重写方法才能到达目的。

```java
//重写父类（Object类）中的equals方法
public boolean equals(Object o)
{
    boolean temp = true;
    Student s1 = this;
    if(o instanceof Object)
    {
        Student s2 = (Student)o;
        if(!(s1.name.equals(s2.name)&&s1.age==s2.age))
        {
            temp = false;
        }
    }
    else
    {
        temp = false;
    }
    return temp;//返回一个布尔值
}
```

上面的是书上的例子，不太好理解，我自己编了一个equals()方法，简单但不知道对不对：

```java
 class Student
  {
      String name;
      int age;
      //重写父类（Object类）中的equals方法
      public boolean equals()
      {
          boolean temp;
          Student s1 = new Student();
         s1.name="张三";s1.age=12;
         Student s2 = new Student();
         s2.name="张三";s2.age=12;
         if((s1.name.equals(s2.name))&&(s1.age==s2.age))
         {
             temp = true;
         }
         else
         {
             temp = false;
         }
         return temp;
     }
 }
 
 public class Text{
     public static void main(String[] args)
     {
         Student s3 = new Student();
         System.out.println(s3.equals()?"是同一人":"不是同一人");
     }
 }

```

# 1.4 对象签名：hashCode
 	**hashCode() 的作用是获取哈希码，也称为散列码；它实际上是返回一个int整数。这个哈希码的作用是确定该对象在哈希表中的索引位置**。（该方法用来返回其所在对象的**物理地址（哈希码值）**，常会和equals方法同时重写，确保相等的两个对象拥有相等的.hashCode）

 	hashCode() 定义在JDK的Object.java中，这就意味着Java中的任何类都包含有hashCode() 函数。

 	虽然，**每个Java类都包含hashCode() 函数。但是，仅仅当创建并某个“类的散列表”(关于“散列表”见下面说明)时，该类的hashCode() 才有用(作用是：确定该类的每一个对象在散列表中的位置**；**其它情况下(例如，创建类的单个对象，或者创建类的对象数组等等)，类的hashCode() 没有作用**。

## 1.4.1  散列表

 	散列表，指的是：**Java集合中本质是散列表的类，如HashMap，Hashtable，HashSet**。

​	也就是说：**hashCode() 在散列表中才有用，在其它情况下没用。在散列表中hashCode() 的作用是获取对象的散列码，进而确定该对象在散列表中的位置**。

## 1.4.2 hashCode()和equal()

​	**hashCode()方法和equal()方法的作用其实一样，在Java里都是用来对比两个对象是否相等一致**；

### 1.4.2.1 equal()既然已经能实现对比的功能了，为什么还要hashCode()呢？

​	因为**重写的equal（）里一般比较的比较全面比较复杂，这样效率就比较低，而利用hashCode()进行对比，则只要生成一个hash值进行比较就可以了，效率很高**；

### 1.4.2.2 hashCode()既然效率这么高为什么还要equal()呢？

​	因为**hashCode()并不是完全可靠，有时候不同的对象他们生成的hashcode也会一样（生成hash值得公式可能存在的问题），所以hashCode()只能说是大部分时候可靠，并不是绝对可靠**，所以我们可以得出：

（1）**equal()相等的两个对象他们的hashCode()肯定相等，也就是用equal()对比是绝对可靠的**。

（2）**hashCode()相等的两个对象他们的equal()不一定相等，也就是hashCode()不是绝对可靠的**。

​	**所有对于需要大量并且快速的对比的话如果都用equal()去做显然效率太低，所以解决方式是，每当需要对比的时候，首先用hashCode()去对比，如果hashCode()不一样，则表示这两个对象肯定不相等（也就是不必再用equal()去再对比了）,如果hashCode()相同，此时再对比他们的equal()，如果equal()也相同，则表示这两个对象是真的相同了，这样既能大大提高了效率也保证了对比的绝对正确性！**

 	**这种大量的并且快速的对象对比一般使用的hash容器中，比如hashset,hashmap,hashtable等等，比如hashset里要求对象不能重复，则他内部必然要对添加进去的每个对象进行对比，而他的对比规则就是像上面说的那样，先hashCode()，如果hashCode()相同，再用equal()验证，如果hashCode()都不同，则肯定不同，这样对比的效率就很高了**。
 	**然而hashCode()和equal()一样都是基本类Object里的方法，而和equal()一样，Object里hashCode()里面只是返回当前对象的地址，如果是这样的话，那么我们相同的一个类，new两个对象，由于他们在内存里的地址不同，则他们的hashCode（）不同，所以这显然不是我们想要的，所以我们必须重写我们类的hashCode()方法，即一个类，在hashCode()里面返回唯一的一个hash值**。

```java
class Student
{
    String name;
    int age;
    //重写父类（Object类）中的equals方法
    public boolean equals()
    {
        boolean temp;
        Student s1 = new Student();
        s1.name="张三";s1.age=12;
        Student s2 = new Student();
        s2.name="张三";s2.age=12;
        System.out.println("s1的哈希码："+s1.hashCode());
        System.out.println("s2的哈希码："+s2.hashCode());
        if((s1.name.equals(s2.name))&&(s1.age==s2.age))
        {
            temp = true;
        }
        else
        {
            temp = false;
        }
        return temp;
    }
    //重写hashCode()方法
    public int hashCode()
    {
        return age*(name.hashCode());
    }
}

public class Text{
    public static void main(String[] args)
    {
        Student s3 = new Student();
        System.out.println(s3.equals()?"s1和s2是同一人":"s1和s2不是同一人");
    }
}

运行结果：
s1的哈希码：9298668

s2的哈希码：9298668

s1和s2是同一人
```



# 1.5 **取得对象信息的方法：toString()**

该方法在打印对象时被调用，将对象信息变为字符串返回，默认输出对象地址。

```java
class Student
{
    String name = "Mary";
    int age = 21;
}

public class Text{
    public static void main(String[] args)
    {
        Student s = new Student();
        System.out.println("姓名："+s.name+"，年龄："+s.age);//输出对象属性
        System.out.println(s);//直接输出对象信息
        System.out.println(s.toString());//调用父类方法输出对象信息
    }
}

运行结果：
    
姓名：Mary，年龄：21

ClassNotes.Student@15db9742

ClassNotes.Student@15db9742
```

上述结果看出编译器默认调用toString()方法输出对象，但输出的是对象的地址，我们并不能看懂它的意思。那么就要通过重写Object类的toString()方法来输出对象属性信息。

```java
class Student
{
    String name = "Mary";
    int age = 21;
    public String toString()
    {
        return "姓名："+name+"，年龄："+age;
    }
}
```





原文链接：https://www.jianshu.com/p/629b047f6cbe


