# 一、概述

​	为什么会有面向切面编程(AOP)？Java是面向对象程序设计(OOP)的，但它有一些弊端。比如当要为多个不具有担当关系的工具引入一个公共举动，例如日志、权限验证、事务等功能时，只能在每个工具里引用公共举动。如果这样做不便于维护，并且有大量相同的代码。AOP面向方面编程基于[IOC]，是对OOP的有益补充。AOP是一种思想，不同的厂商或企业可能有不同的实现方式，为了更好的应用AOP技术，技术专家们成立了AOP联盟来探讨AOP的标准化，AOP联盟定义的AOP体系结构把与AOP相关的概念大致分为由高到低、从使用到实现的三层关系，AOP联盟定义的AOP体系结构如下图：

![img](\web相关\spring\image\springAop体系架构图01.jpg)

在AOP联盟定义的AOP体系结构下有很多的实现者，例如：AspectJ、JBoss AOP、AspectWerkz、Spring AOP等。Spring AOP就是在此标准下产生的。

要想理解Spring AOP，先理解代理模式。
 代理模式的定义：**为其他对象提供一种代理以控制对这个对象的访问**。在某些情况下，一个对象不适合或者不能直接引用另一个对象，而代理对象可以在客户端和目标对象之间起到中介的作用。比如A对象要做一件事情，在没有代理前，自己来做；在对 A 代理后，由 A 的代理类 B 来做。代理其实是在原实例前后加了一层处理，这也是 AOP 的初级轮廓。

# 二、代理模式的原理及实践

代理模式又分为**静态代理、动态代理**。

## 2.1 静态代理原理及实践

静态代理模式：说白了，就是在程序运行前就已经存在代理类的字节码文件，代理类和原始类的关系在运行前就已经确定。代码如下：

### 2.1.1 接口：

```csharp
public interface IUserDao {
    void save();
    void find();
}
```

### 2.1.2 目标对象：

```java
class UserDao implements IUserDao{
    @Override
    public void save() {
        System.out.println("模拟：保存用户！");
    }
    @Override
    public void find() {
        System.out.println("模拟：查询用户");
    }
}
```

### 2.1.3 静态代理特点：

1. 目标对象必须要实现接口
2. 代理对象，要实现与目标对象一样的接口

```java
class UserDaoProxy implements IUserDao{
    // 代理对象，需要维护一个目标对象
    private IUserDao target = new UserDao();
    @Override
    public void save() {
        System.out.println("代理操作： 开启事务...");
        target.save(); // 执行目标对象的方法
        System.out.println("代理操作：提交事务...");
    }
    @Override
    public void find() {
        target.find();
    }
}
```

​	静态代理保证了业务类只需要关注逻辑本身，代理对象的一个接口只需要服务于一种类型的对象。如果要代理的方法很多，势必要为每一种方法都进行代理。再者，如果增加一个方法，除了实现类需要实现这个方法外，所有的代理类也要实现此方法。增加了代码的维护成本。那么要如何解决呢？答案是使用动态代理。

## 2.2 动态代理原理及实践

动态代理模式：动态代理类的源码是在程序运行期间，通过 JVM [反射]等机制动态生成。代理类和委托类的关系是运行时才确定的。实例如下：

### 2.2.1 接口：

```csharp
public interface IUserDao {
    void save();
    void find();
}
```

### 2.2.2 目标对象：

```java
class UserDao implements IUserDao{
    @Override
    public void save() {
        System.out.println("模拟： 保存用户！");
    }
    @Override
    public void find() {
        System.out.println("查询");
    }
}
```

### 2.2.3 动态代理：代理工厂，给多个目标对象生成代理对象

```tsx
class ProxyFactory {
    // 接收一个目标对象
    private Object target;
    public ProxyFactory(Object target) {
        this.target = target;
    }
    // 返回对目标对象(target)代理后的对象(proxy)
    public Object getProxyInstance() {
        Object proxy = Proxy.newProxyInstance(
                               // 目标对象使用的类加载器
                target.getClass().getClassLoader(),
                               // 目标对象实现的所有接口 
                target.getClass().getInterfaces(), 
                              // 执行代理对象方法时候触发
                new InvocationHandler() { 
                    @Override
                    public Object invoke(Object proxy, Method method, Object[] args)
                            throws Throwable {
                        // 获取当前执行的方法的方法名
                        String methodName = method.getName();
                        // 方法返回值
                        Object result = null;
                        if ("find".equals(methodName)) {
                            // 直接调用目标对象方法
                            result = method.invoke(target, args);
                        } else {
                            System.out.println("开启事务...");
                            // 执行目标对象方法
                            result = method.invoke(target, args);
                            System.out.println("提交事务...");
                        }
                        return result;
                    }
                }
                );
        return proxy;
    }
}
```



```cpp
IUserDao proxy = (IUserDao)new ProxyFactory(target).getProxyInstance();
```

其实是 JDK 动态生成了一个类去实现接口，隐藏了这个过程：

```dart
class $jdkProxy implements IUserDao{}
```

使用 JDK 生成的动态代理的前提是目标类必须有实现的接口。但这里又引入一个问题，如果某个类没有实现接口，就不能使用 JDK 动态代理。所以 CGLIB 代理就是解决这个问题的。

CGLIB 是以动态生成的子类继承目标的方式实现，在运行期动态的在内存中构建一个子类，如下：
 CGLIB 使用的前提是目标类不能是 final 修饰的。因为 final 修饰的类不能被继承。

现在，我们可以看看 AOP 的定义：面向切面编程，核心原理是使用动态代理模式在方法执行前后或出现异常时加入相关逻辑。

### 2.2.4 通过定义和前面代码可以发现3点：

1. **AOP 是基于动态代理模式**。
2. **AOP 是方法级别的**。
3. **AOP 可以分离业务代码和关注点代码**（重复代码）。在执行业务代码时，动态的注入关注点代码。切面就是关注点代码形成的类。

# 三、Spring AOP原理及实战

​	Spring 框架把JDK 代理和 CGLIB 代理两种动态代理在底层都集成了进去，开发者无需担心自己去实现动态生成代理。那么，Spring是如何生成代理对象的？

1. 创建容器对象的时候，根据切入点表达式拦截的类，生成代理对象。

2. 如果目标对象有实现接口，使用 JDK 代理。如果目标对象没有实现接口，则使用 CGLIB 代理。然后从容器获取代理后的对象，在运行期植入“切面”类的方法。通过查看 Spring 源码，我们在 DefaultAopProxyFactory 类中，找到这样一段话。

   ![img](\web相关\spring\image\DefaultAopProxyFactory01.jpg)

简单的从字面意思看出：如果有接口，则使用 JDK 代理；反之使用 CGLIB 。这刚好印证了前文所阐述的内容。Spring AOP 综合两种代理方式的使用前提有会如下结论：**如果目标类没有实现接口，且 class 为 final 修饰的，则不能进行 Spring AOP 编程**。

知道了原理，现在我们将自己手动实现 Spring 的 AOP：

 ## 3.1 接口：

```csharp
public interface IUserDao {
    void save();
}
```

## 3.2 用于测试 CGLIB 动态代理：

```csharp
class OrderDao {
    public void save() {
        //int i =1/0; 用于测试异常通知
        System.out.println("保存订单...");
    }
}
```

## 3.3 用于测试 JDK 动态代理：

```java
class UserDao implements IUserDao {
    public void save() {
        //int i =1/0; 用于测试异常通知
        System.out.println("保存用户...");
    }
}
```

## 3.4 切面类：

```csharp
class TransactionAop {
    public void beginTransaction() {
        System.out.println("[前置通知] 开启事务..");
    }
    public void commit() {
        System.out.println("[后置通知] 提交事务..");
    }
    public void afterReturing() {
        System.out.println("[返回后通知]");
    }
    public void afterThrowing() {
        System.out.println("[异常通知]");
    }
    public void arroud(ProceedingJoinPoint pjp) throws Throwable {
        System.out.println("[环绕前：]");
        pjp.proceed(); // 执行目标方法
        System.out.println("[环绕后：]");
    }
}
```

## 3.5 Spring 的 XML 配置文件：

```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
xmlns:context="http://www.springframework.org/schema/context"
    xmlns:aop="http://www.springframework.org/schema/aop"
    xsi:schemaLocation="
http://www.springframework.org/schema/beans
    http://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
            http://www.springframework.org/schema/context/spring-context.xsd
                http://www.springframework.org/schema/aop
                http://www.springframework.org/schema/aop/spring-aop.xsd">

    <!-- dao实例加入容器 -->
    <bean id="userDao" class="test.spring_aop_anno.UserDao"></bean>

    <!-- dao实例加入容器 -->
    <bean id="orderDao" class="test.spring_aop_anno.OrderDao"></bean>

    <!-- 实例化切面类 -->
    <bean id="transactionAop" class="test.spring_aop_anno.TransactionAop"></bean>

    <!-- Aop相关配置 -->
    <aop:config>
        <!-- 切入点表达式定义 -->
        <aop:pointcut expression="execution(* test.spring_aop_anno.*Dao.*(..))"
            id="transactionPointcut" />

        <!-- 切面配置 -->
        <aop:aspect ref="transactionAop">

            <!-- 【环绕通知】 -->
            <aop:around method="arroud" pointcut-ref="transactionPointcut" />

            <!-- 【前置通知】 在目标方法之前执行 -->
            <aop:before method="beginTransaction" pointcut-ref="transactionPointcut"/>

            <!-- 【后置通知】 -->
            <aop:after method="commit" pointcut-ref="transactionPointcut" />

            <!-- 【返回后通知】 -->
            <aop:after-returning method="afterReturing"
                pointcut-ref="transactionPointcut" />

            <!-- 异常通知 -->
            <aop:after-throwing method="afterThrowing"
                pointcut-ref="transactionPointcut" />

        </aop:aspect>
    </aop:config>
</beans>
```

切入点表达式不在这里介绍。参考 Spring AOP 切入点表达式。

# 四、Spring AOP 应用场景

1. [Spring声明式事务]管理配置；
2. Controller层的参数校验；
3. 使用 Spring AOP 实现 MySQL 数据库读写分离案例分析；
4. 在执行方法前，判断是否具有权限，Authentication权限检查；
5. 对部分函数的调用进行日志记录：监控部分重要函数，若抛出指定的异常，可以以短信或邮件方式通知相关人员；
6. 信息过滤，页面转发等等功能。
    Caching 缓存
    Context passing 内容传递
    Error handling 错误处理
    Lazy loading　延迟加载
    Debugging　　调试
    logging, tracing, profiling and monitoring　日志记录，跟踪，优化，校准
    Performance optimization　性能优化，效率检查
    Persistence　　持久化
    Resource pooling　资源池
    Synchronization　同步
    Transactions 事务管理
    另外Filter的实现和struts2的拦截器的实现都是AOP思想的体现。

Spring不尝试提供最为完善的AOP实现，它更侧重于提供一种和Spring IOC容器整个的AOP实现，用于解决实际的问题，在Spring中无缝的整合了Spring AOP、Spring IOC和AspectJ。

当然，Spring AOP的内容不仅仅有这些！例如：我们在使用Spring AOP的时候只是简单的配置一下（通过XML或注解进行配置），Spring AOP在内部ProxyFactory 来创建代理对象，然后调用我们的目标方法。

最后补充一下！动态代理或者设计模式重要吗？很重要！Spring AOP用到了动态代理，Spring事务管理用到了动态代理，MyBatis数据库连接池用到了动态代理，MyBatis创建Mapper用到了动态代理等等！

1. **AOP面向方面编程基于IoC，是对OOP的有益补充**。
2. **AOP利用一种称为“横切”的技术，剖解开封装的对象内部，并将那些影响了多个类的公共行为封装到一个可重用模块，并将其名为“Aspect”**，即方面。所谓“方面”，简单地说，就是将那些与业务无关，却为业务模块所共同调用的逻辑或责任封装起来，比如日志记录，便于减少系统的重复代码，降低模块间的耦合度，并有利于未来的可操作性和可维护性。
3. **AOP代表的是一个横向的关 系，将“对象”比作一个空心的圆柱体，其中封装的是对象的属性和行为；则面向方面编程的方法，就是将这个圆柱体以切面形式剖开，选择性的提供业务逻辑**。而剖开的切面，也就是所谓的“方面”了。然后它又以巧夺天工的妙手将这些剖开的切面复原，不留痕迹，但完成了效果。
4. **实现AOP的技术，主要分为两大类：一是采用动态代理技术，利用截取消息的方式，对该消息进行装饰，以取代原有对象行为的执行；二是采用静态织入的方式，引入特定的语法创建“方面”，从而使得编译器可以在编译期间织入有关“方面”的代码**。
5. **Spring实现AOP：JDK动态代理和CGLIB代理。JDK动态代理：其代理对象必须是某个接口的实现，它是通过在运行期间创建一个接口的实现类来完成对目标对象的代理；其核心的两个类是InvocationHandler和Proxy。 CGLIB代理：实现原理类似于JDK动态代理，只是它在运行期间生成的代理对象是针对目标类扩展的子类。CGLIB是高效的代码生成包，底层是依靠ASM（开源的java字节码编辑类库）操作字节码实现的，性能比JDK强；需要引入包asm.jar和cglib.jar。     使用AspectJ注入式切面和@AspectJ注解驱动的切面实际上底层也是通过动态代理实现的**。


原文链接：https://www.jianshu.com/p/0ce892b5ae5e