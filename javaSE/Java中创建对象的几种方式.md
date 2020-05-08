# 1.Java中创建对象的五种方式

作为java开发人员，开发过程中会创建很多对象，现在开发过程一般通过依赖注入的方式（如：Spring去创建对象）创建管理对象。除此之外，还有很多创建对象的方法：使用New关键字、使用Class类的newInstance方法、使用Constructor类的newInstance方法、使用Clone方法、使用反序列化。

## 1.1  使用new关键字

使用new关键字创建，对象是我们最常见的也是最简单的创建对象的方式，通过这种方式我们还可以调用任意的构造函数（无参的和有参的）。比如：Student student = new Student();

```
缺点：
使用new创建对象会增加耦合度。无论使用什么框架，都要减少new的使用以降低耦合度。
```

```java
/**
 * @ClassName: Hello
 * @Description: 待创建的类
 * @author: yunche
 * @date: 2018/08/24
 */
public class Hello
{
    public void sayWorld()
    {
        System.out.println("Hello world!");
    }

}
/*
 * @ClassName: NewClass
 * @Description: 使用new关键字创建对象
 * @author: yunche
 * @date: 2018/08/24
 */
public class NewClass
{
    public static void main(String[] args)
    {
        Hello h = new Hello();
        h.sayWorld();
    }
}
```

## 1.2使用Class类的newInstance方法

使用Class类的newInstance方法创建对象，这个newInstance方法调用**无参的构造器**创建对象。

```java
Student student2 = (Student)Class.forName("根路径.Student").newInstance();　
或者：
Student stu = Student.class.newInstance();
```

```java
/**
 * @ClassName: NewClass
 * @Description: 使用Class类的newInstance方法
 * @author: yunche
 * @date: 2018/08/24
 */
public class NewClass
{
    public static void main(String[] args)
    {
        try
        {
           Class heroClass = Class.forName("yunche.test.Hello");
           Hello h =(Hello) heroClass.newInstance();
           h.sayWorld();
        }
        catch (ClassNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IllegalAccessException e)
        {
            e.printStackTrace();
        }
        catch (InstantiationException e)
        {
            e.printStackTrace();
        }

    }
}
```

## 1.3 使用Constructor类的newInstance方法

此方法和Class类的newInstance方法很像，java.lang.relect.Constructor类里也有一个newInstance方法可以创建对象。我们可以通过这个newInstance方法调用**有参数的和私有的构造函数**。

```java
如： 
Constructor<Student> constructor = Student.class.getInstance(); 
Student stu = constructor.newInstance();　
```

```java
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

/**
 * @ClassName: NewClass
 * @Description: 使用Constructor类的newInstance方法
 * @author: yunche
 * @date: 2018/08/24
 */
public class NewClass
{
    public static void main(String[] args)
    {
        try
        {
            //获取类对象
           Class heroClass = Class.forName("yunche.test.Hello");

           //获取构造器
           Constructor constructor = heroClass.getConstructor();
           Hello h =(Hello) constructor.newInstance();
           h.sayWorld();
        }
        catch (NoSuchMethodException e)
        {
            e.printStackTrace();
        }
        catch (InvocationTargetException e)
        {
            e.printStackTrace();
        }
        catch (IllegalAccessException e)
        {
            e.printStackTrace();
        }
        catch (InstantiationException e)
        {
            e.printStackTrace();
        }
        catch (ClassNotFoundException e)
        {
            e.printStackTrace();
        }

    }
}
```

```
两种newInstance方法的区别：
这两种newInstance的方法就是大家所说的反射，事实上Class的newInstance方法内部调用Constructor的newInstance方法。这也是众多框架Spring、Hibernate、Struts等使用后者的原因。
```

## 1.4 使用Clone的方法

无论何时我们调用一个对象的clone方法，JVM就会创建一个新的对象，将前面的对象的内容全部拷贝进去，用clone方法创建对象并不会调用任何构造函数。要使用clone方法，我们必须先实现Cloneable接口并实现其定义的clone方法。

clone时，需要已经有一个分配了内存的源对象，创建新对象时，首先应该分配一个和源对象一样大的内存空间。要调用clone方法需要实现*Cloneable*接口，由于clone方法是protected的，所以修改源对象。

```java
Student stu2 = <Student>stu.clone();
```

```java
/**
 * @ClassName: Hello
 * @Description: 待创建的类
 * @author: yunche
 * @date: 2018/08/24
 */
public class Hello implements Cloneable
{
    public void sayWorld()
    {
        System.out.println("Hello world!");

    }

    public static void main(String[] args)
    {
        Hello h1 = new Hello();
        try
        {
            Hello h2 = (Hello)h1.clone();
            h2.sayWorld();
        }
        catch (CloneNotSupportedException e)
        {
            e.printStackTrace();
        }
    }
}
```

## 1.5  使用反序列化

使用反序列化，当我们序列化和反序列化一个对象，JVM会给我们创建一个单独的对象，**在反序列化时，JVM创建对象并不会调用任何构造函数**。为了反序列化一个对象，我们需要让我们的类实现Serializable接口。

使用序列化时，要**实现Serializable接口**，将一个对象序列化到磁盘上，而采用反序列化可以将磁盘上的对象信息转化到内存中。

```java
ObjectInputStream in = new ObjectInputStream (new FileInputStream("data.obj")); 
Student stu3 = (Student)in.readObject();
```

```java
import java.io.*;

/**
 * @ClassName: Serialize
 * @Description: 序列化与反序列化对象
 * @author: yunche
 * @date: 2018/08/24
 */
public class Serialize
{
    public static void main(String[] args)
    {
        Hello h = new Hello();

        //准备一个文件用于存储该对象的信息
        File f = new File("hello.obj");

        try(FileOutputStream fos = new FileOutputStream(f);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            FileInputStream fis = new FileInputStream(f);
            ObjectInputStream ois = new ObjectInputStream(fis)
            )
        {
            //序列化对象，写入到磁盘中
            oos.writeObject(h);
            //反序列化对象
            Hello newHello = (Hello)ois.readObject();

            //测试方法
            newHello.sayWorld();
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        catch (ClassNotFoundException e)
        {
            e.printStackTrace();
        }
    }
}
```

# 2. 总结

**除了使用new关键字之外的其他方法全部都是转变为invokevirtual（创建对象的直接方法），使用被new的方式转变为两个调用，new和invokespecial（构造函数调用）**。

