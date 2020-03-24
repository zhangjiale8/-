## 1.1 抽象（abstract）的使用

　　当父类的某些方法不确定时，可以用abstract关键字来修饰该方法[抽象方法]，用abstract来修饰该类[抽象类]。

　　我们都知道，父类是将子类所共同拥有的属性和方法进行抽取，这些属性和方法中，有的是已经明确实现了的，有的还无法确定，那么我们就可以将其定义成抽象，在后日子类进行重用，进行具体化。这样，抽象类也就诞生了。

　　例如，定义了“动物”父类，其中“动物名称”和“动物年龄”属性已经明确了，但是“动物叫”的方法没有明确，此时就可以将“动物叫”定义为抽象方法。

　　**所以，抽象类是为了把相同的但不确定的东西的提取出来，为了以后的重用。定义成抽象类的目的，就是为了在子类中实现抽象类。** 

```java
package javastudy;

public class AbstractDemo1 {

    public static void main(String[] args) {
        // TODO Auto-generated method stub

    }
}

// 这就是一个抽象类
abstract class Animal {
    String name;
    int age;

    // 动物会叫
    public abstract void cry(); // 不确定动物怎么叫的。定义成抽象方法，来解决父类方法的不确定性。抽象方法在父类中不能实现，所以没有函数体。但在后续在继承时，要具体实现此方法。
}

// 抽象类可以被继承
// 当继承的父类是抽象类时，需要将抽象类中的所有抽象方法全部实现。
class cat extends Animal {
    // 实现父类的cry抽象方法
    public void cry() {
        System.out.println("猫叫:");

    }
}
```

 ## 1.2 用abstract修饰的类，即抽象类；用abstract修饰的方法，即抽象方法。

 

## 1.3 抽象方法不能有方法主体。

格式如下：

```
abstract void xxx();
```

## 1.4 抽象类不能被实例化。

​	因为抽象类中方法未具体化，这是一种不完整的类，所以直接实例化也就没有意义了。

## 1.5 抽象类中不一定要包含abstract方法。

​	也就是了，抽象中可以没有abstract方法。

## 1.6 一旦类中包含了abstract方法，那类该类必须声明为abstract类。