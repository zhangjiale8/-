# 一、JVM优化及面试热点分析

## 1.1 java背景回顾

### 1.1.1 概述

```
java不仅仅是一门编程语言，还是一个由一系列计算机软件和规范形成的技术体系，这个技术体系提供了完整的用于软件开发和跨平台部署的支持环境，并广发应用于嵌入式系统、移动终端、企业的服务器、大型机等各种场合。时至今日，Java技术体系已经吸引了1000多万软件开发者，这是全球最大的软件开发团队。使用Java的设备多达几十亿台，Oracle的最新官网显示目前活跃的JVM虚拟机在450亿+.
```

TIOBE 编程语言排行榜是一个比较权威的编程语言使用情况统计机构。今年8月份，TIOBE更新了最新的全球编程语言排行榜。数据显示，长期以来稳居第一的Java，依旧霸占排行榜第一位。

![image-20201103163113636](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201103163113636.png)

```
Java能获得如此广泛的认可，除了它拥有一门结构严谨、面向对象的编程语言之外，还有许多不可忽视的优点：

1. 摆脱了硬件平台的束缚，实现一次编写 到处运行的理想
2. 提供了相对安全的内存管理和访问机制，避免了绝大部分的内存泄漏
3. 实现了热点代码检测和运行时编译及优化，使得java应用能随着运行时间的增加而获得更高的性能
4. 有着良好的生态环境，还有这无数商业机构和开源社区的第三方类库来帮助它实现各种各样的功能

作为一名java程序员，我们是很幸福的，在编写程序时可以尽情发挥Java的各种优势，但与此同时我们也应该去了解和思考下Java技术体系中这些技术特性是如何实现的。认识这些技术运作的本质，是自己思考程序该怎么写更高一些的基础和前提，而且在市场竞争日益激烈的今天，你对基础和底层了解的多少，也是面试官衡量一个程序员是否合格的一个标准！
```

### 1.1.2 小结

* 跨平台，编写一次代码，到处运行
* 它由C++演变来的，底层就是C++/C代码。
* 有完善的生态。其他的语言都在借鉴java，其实一句话：我走过的老路，你一定要走一遍。

## 1.2 java技术体系

Sun公司定义的传统java技术体系主要有以下几部分组成:

```
Java 程序设计语言
Java虚拟机
Class文件格式
JavaAPI类库
第三方类库
```

我们可以把Java程序设计语言、Java虚拟机、JavaAPI类库 统称为JDK (JavaDevelopment Kit), JDK是用于支持Java程序开发的最小环境。

![image-20201103163645940](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201103163645940.png)

* 面试题：jdk jre 和jvm的关系

```
JDK: java development kit, java开发工具包，用来开发Java程序的，针对java开发者。
JRE: java runtime environment, java运行时环境，针对java用户
JVM: java virtual machine，java虚拟机 用来解释执行字节码文件(class文件)的。
```

以上是按照各个组成部分的功能来进行划分的，如果按照技术所服务的领域来划分，Java的技术体系可以分为4个平台：

Java Card:
支持一些Java小程序,运行在小型内存设备上的平台(如:智能卡 sim卡 提款卡)
Java ME: --jvm
支持Java程序运行在移动终端(机顶盒、移动电话和PDA) 上的平台
Java SE:
支持面向桌面级应用的Java平台，提供了完整的Java核心API， 以前叫做J2SE
Java EE:
支持使用多层架构的企业级应用的Java平台，除了提供Java SE API之外 还对其做了大量的扩充。以前叫做J2EE

## 1.3 java发展史

```
\# JAVA 1.0 ,代号Oak（橡树）
于1996-01-23发行

\# JAVA 1.1
1997-02-19发行,主要更新内容:
1.引入JDBC
2.添加内部类支持
3.引入JAVA BEAN
4.引入RMI
5.引入反射

\# JAVA 1.2, 代号Playground（操场）
1998-12-8发行，主要更新内容：
1.引入集合框架
2.对字符串常量做内存映射
3.引入JIT（Just In Time）编译器
4.引入打包文件数字签名
5.引入控制授权访问系统资源策略工具
6.引入JFC（Java Foundation Classes），包括Swing1.0，拖放
和Java2D类库
7.引入Java插件
8.JDBC中引入可滚动结果集，BLOB,CLOB,批量更新和用户自定义类型
9.Applet中添加声音支持

\# JAVA1.3，代号Kestrel（红隼）
2000-5-8发布，主要更新内容：
1.引入Java Sound API
2.引入jar文件索引
3.对Java各方面多了大量优化和增强
4.Java Platform Debugger Architecture用于 Java 调式的平台。

\# JAVA 1.4，代号Merlin（隼）
2004-2-6发布（首次在JCP下发行），主要更新内容：
1.添加XML处理
2.添加Java打印服务（Java Print Service API）
3.引入Logging API
4.引入Java Web Start
5.引入JDBC 3.0 API
6.引入断言
7.引入Preferences API
8.引入链式异常处理
9.支持IPV6
10.支持正则表达式
11.引入Image I/O API
12.NIO，非阻塞的 IO，优化 Java 的 IO 读取。

\# JDK 5.0，代号Tiger（老虎），有重大改动
2004-9-30发布，主要更新内容：
1.引入泛型
2.For-Each循环 增强循环，可使用迭代方式
3.自动装箱与自动拆箱
4.引入类型安全的枚举
5.引入可变参数
6.添加静态引入
7.引入注解
8.引入Instrumentation
9.提供了 java.util.concurrent 并发包。

\# JDK 6，代号Mustang（野马）
2006-12-11发布，主要更新内容：
1.引入了一个支持脚本引擎的新框架（基于 Mozilla Rhino 的
JavaScript 脚本引擎）
2.UI的增强
3.对WebService支持的增强（JAX-WS2.0 和 JAXB2.0）
4.引入JDBC4.0API
5.引入Java Compiler API
6.通用的Annotations支持

\# JDK 7，代号Dolphin（海豚）
2011-07-28发布，这是sun被oracle收购（2009年4月）后的第一个版
本，主要更新内容：
1.switch语句块中允许以字符串作为分支条件
2.在创建泛型对象时应用类型推断,比如你之前版本使用泛型类型时这样写ArrayList<User> userList= new ArrayList<User>();，这个版本只需要这样写ArrayList<User> userList= new ArrayList<>();，也即是后面一个尖括号内的类型，JVM 帮我们自动类型判断补全了。
3.在一个语句块中捕获多种异常
4.添加try-with-resources语法支持，使用文件操作后不用再显示执行close了。
5.支持动态语言
6.JSR203, NIO.2,AIO,新I/O文件系统，增加多重文件的支持、文件原始数据和符号链接,支持ZIP文件操作
7.JDBC规范版本升级为JDBC4.1
8.引入Fork/Join框架，用于并行执行任务
9.支持带下划线的数值，如 int a = 100000000;，0 太多不便于人阅读，这个版本支持这样写 int a =100_000_000，这样就对数值一目了然了。
10.Swing组件增强（JLayer,Nimbus Look Feel…）参考

\# JDK 8 (长版本)
2014-3-19发布，oracle原计划2013年发布，由于安全性问题两次跳票，是自JAVA5以来最具革命性的版本，主要更新内容：
1.接口改进，接口居然可以定义默认方法实现和静态方法了。
2.引入函数式接口
3.引入Lambda表达式
4.引入全新的Stream API，提供了对值流进行函数式操作。
5.引入新的Date-Time API
6.引入新的JavaScrpit引擎Nashorn
7.引入Base64类库
8.引入并发数组（parallel）
9.添加新的Java工具：jjs、jdeps
10.JavaFX，一种用在桌面开发领域的技术
11.静态链接 JNI 程序库

\# JDK 9
2017-9-21发布
1.模块化（jiqsaw）
2.交互式命令行（JShell）
3.默认垃圾回收期切换为G14.进程操作改进
5.竞争锁性能优化
6.分段代码缓存
7.优化字符串占用空间

\# JDK 10
2018-3-21发布
1.JEP286，var 局部变量类型推断。
2.JEP296，将原来用 Mercurial 管理的众多 JDK 仓库代码，合并到一个仓库中，简化开发和管理过程。
3.JEP304，统一的垃圾回收接口。
4.JEP307，G1 垃圾回收器的并行完整垃圾回收，实现并行性来改善最坏情况下的延迟。
5.JEP310，应用程序类数据 (AppCDS) 共享，通过跨进程共享通用类元数据来减少内存占用空间，和减少启动时间。
6.JEP312，ThreadLocal 握手交互。在不进入到全局 JVM 安全点(Safepoint) 的情况下，对线程执行回调。优化可以只停止单个线程，而不是停全部线程或一个都不停。
7.JEP313，移除 JDK 中附带的 javah 工具。可以使用 javac -h代替。
8.JEP314，使用附加的 Unicode 语言标记扩展。
9.JEP317，能将堆内存占用分配给用户指定的备用内存设备。
10.JEP317，使用 Graal 基于 Java 的编译器，可以预先把 Java代码编译成本地代码来提升效能。
11.JEP318，在 OpenJDK 中提供一组默认的根证书颁发机构证书。开源目前 Oracle 提供的的 Java SE 的根证书，这样 OpenJDK 对开发人员使用起来更方便。
12.JEP322，基于时间定义的发布版本，即上述提到的发布周期。版本号为\$FEATURE.\$INTERIM.\$UPDATE.\$PATCH，分别是大版本，中间版本，升级包和补丁版本。

\# JDK 11
2018-9-25发布
官网公开的 17 个 JEP（JDK Enhancement Proposal 特性增强提议）：
1.JEP181: Nest-Based Access Control（基于嵌套的访问控制）
2.JEP309: Dynamic Class-File Constants（动态的类文件常量）
3.JEP315: Improve Aarch64 Intrinsics（改进 Aarch64Intrinsics）
4.JEP318: Epsilon: A No-Op Garbage Collector（Epsilon垃圾回收器，又被称为”No-Op（无操作）”回收器）
5.JEP320: Remove the Java EE and CORBA Modules（移除Java EE 和 CORBA 模块，JavaFX 也已被移除）
6.JEP321: HTTP Client (Standard)
7.JEP323: Local-Variable Syntax for Lambda Parameters（用于 Lambda 参数的局部变量语法）
8.JEP324: Key Agreement with Curve25519 and Curve448（采用 Curve25519 和 Curve448 算法实现的密钥协议）
9.JEP327: Unicode 10
10.JEP328: Flight Recorder（飞行记录仪）
11.JEP329: ChaCha20 and Poly1305 Cryptographic Algorithms（实现 ChaCha20 和 Poly1305 加密算法）
12.JEP330: Launch Single-File Source-Code Programs（启动单个 Java 源代码文件的程序）
13.JEP331: Low-Overhead Heap Profiling（低开销的堆分配采样方法）
14.JEP332: Transport Layer Security (TLS) 1.3（对 TLS1.3 的支持）
15.JEP333: ZGC: A Scalable Low-Latency Garbage Collector (Experimental)（ZGC：可伸缩的低延迟垃圾回收器，处于实验性阶段）
16.JEP335: Deprecate the Nashorn JavaScript Engine（弃用 Nashorn JavaScript 引擎）
17.JEP336: Deprecate the Pack200 Tools and API（弃用Pack200 工具及其 API）

\# JDK 12
2019-3-19发布
1.JEP189:Shenandoah: A Low-Pause-Time Garbage
Collector (Experimental)
2.JEP230:Microbenchmark Suite
3.JEP325:Switch Expressions (Preview)
4.JEP334:JVM Constants API
5.JEP340:One AArch64 Port, Not Two
6.JEP341:Default CDS Archives
7.JEP344:Abortable Mixed Collections for G1
8.JEP346:Promptly Return Unused Committed Memory fromG1

\# JDK 13
2019-9-17 发布
1.JEP350:Dynamic CDS Archives
2.JEP351:ZGC: Uncommit Unused Memory
3.JEP353:Reimplement the Legacy Socket API
4.JEP354:Switch Expressions
5.JEP355:Text Blocks

\# JDK 14
正在开发阶段，预计解决的任务。
2019/12/12 Rampdown Phase One (fork from main line)
2020/01/16 Rampdown Phase Two
2020/02/06 Initial Release Candidate
2020/02/20 Final Release Candidate
2020/03/17 General Availability

```

## 1.4 java虚拟机发展史

​	上面我们从整个Java技术的角度观察了Java技术的发展，接下来我们在看看Java虚拟机的发展史，提到Java虚拟机很多人都会想到 Sun公司的HotSpot虚拟机，但实际上JVM的实现还有很多

Sun classic/Exact VM

```
Sun Classic VM的技术可能很原始，而且这款虚拟机的使命也早已终结。但仅凭它"世界上第一款商用Java虚拟机"的头衔就应该被我们所记住。

Exact VM在第一代虚拟机的基础上做了大量优化，在JDK1.2中使用，但只存在了很短的时间就被更优秀的HotSpot VM所取代。
```

Sun HotSpot VM

```
它是Sun JDK和Open JDK中所带的虚拟机，也是目前使用范围最广的Java虚拟机。这款虚拟机是在1997年收购获得，并经过不断优化继承了Java前两任虚拟机的优点也有自己的优势。 在2006年 JavaOne大会上，Sun公司宣布最终会把Java开源，在接下来的一年java在GPL协议下公开源码，在此基础上建立了OpenJDK.
```

Sun Mobile-Embedded VM/ Meta-Circular VM

```
Sun公司所研发的虚拟机可不仅前面介绍的服务器、桌面领域的虚拟机，面对移动端和嵌入式市场 也创建了对应的虚拟机
```

BEA JRockit / IBM J9 VM

```
前面介绍了Sun公司的各种虚拟机，除了Sun公司外，其他组织、公司也研发过不少虚拟机实现，其中规模最大的就属BEA 和 IBM公司。

JRockit 和 J9 都是号称世界上最快的虚拟机，J9 主要用于运行IBM旗下的java产品，功能和产品方向与HotSpot虚拟机类似。而JRockit 主要专注于服务器端应用，JRockit的垃圾收集器在众多Java虚拟机实现中也一直处于领先水平。

不过2008~2009 BEA 和 Sun相继被Oracle公司收购，Oracle一下就掌握了世界上最先进的两款虚拟机，并在后续对两款虚拟机进行整合，将JRockit的优秀特质移植到HotSpot虚拟机中。
```

## 1.5 JVM组成

```
类加载器（ClassLoader）
运行时数据区（Runtime Data Area） （堆、栈）
执行引擎（Execution Engine） c++/C
本地库接口（Native Interface）
```

![image-20201103172653602](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201103172653602.png)

* 首先通过java的文件通过编译以后会生产类，通过过类加载器（ClassLoader）会把 Java 代码转换成字节码。
* 运行时数据区（Runtime Data Area）再把字节码加载到内存中，而字节码文件只是 JVM 的一套指令集规范，并不 能直接交给底层操作系统去执行。
* 因此需要特定的命令解析器执行引擎（Execution Engine），
* 将字节码翻译成底层系统指令，再交由 CPU 去执行，而这个过程中需要调用其他语言的本地库接口（Native Interface）来实现整个程序的功能

## 1.6 java自动内存管理机制-运行时数据区域

### 1.6.1 概述

​	对于Java程序员来说，在虚拟机自动内存管理机制的帮助下，不再需要为每一个new的操作去写对应的内存管理操作，不容器出现内存泄漏和内存溢出问题，由虚拟机管理内存一切都看起来很美好。不过，也正是因为我们把内存控制的权利交给了虚拟机，一旦出现内存泄漏和溢出方面的问题，如果不了解虚拟机是怎么样使用内存的，那么排查错误将会变得特别的困难。 所以，接下来我们要一层一层接下内存管理机制的面试来了解它究竟是怎样实现的。

​	Java虚拟机在执行Java程序的过程中会把它所管理的内存划分为若干个不同的数据区域。这些区域都有各自的用途，以及创建和销毁的时间。根据1.7java虚拟机规范,jvm在运行时主要分为以下几个运行时内存区域：

![image-20201103181116064](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201103181116064.png)



#### 1.6.1.1 线程共享区（堆）
* 方法区(元数据空间)（）
* java堆（Heap）（创建的对象实例都存放在java堆中）

#### 1.6.1.2 线程独占区（栈）

（执行的方法和调用底层native方法都在这个区执行。）

* java虚拟机栈
* 本地方法栈
* 程序计算器

​	如果我们开发过程中，只要执行一个方法，发起一个请求，最终都是开辟一个线程去执行，这个时候就在为没个线程都创建一个虚拟机栈，本地方法
栈，程序计数器 来调度和共享堆区的数据，然后GC也不停的回收内存空间。

![image-20201103181513905](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201103181513905.png)

* 如果这个时候我们的计算机是4核4G内存的，就会同事开启四个线程去执行请求和业务。如果四个CPU都在运行其他的线程就只能挂起等待，
  争抢CPU资源。
* 如果是你1核的单CPU，只会一次性执行一个线程，其他的线程就会就造成线程争抢的问题。
* 在每次线程执行代码的过程中，每个线程JVM怎么知自己线程在执行代码执行到哪行了，这个时候就需要一个程序计数器来判断我当前线程执行到哪行了，如果我当前线程争抢到执行cpu的执行权力的时候，我可以接着上次执行的位置继续执行。就好比：**这个时候有三个人（A,B,C）在做事，但是做事都需要通过一个一个主教练（CPU）的指令才做事，如果这个A抢到资源，那么A开始做事，如果这个时候是一个单核的那么B和C就需要等，如果是多核可以并行一起执行，但是执行过程中，我A做事情做到哪里了，就需要一个东西进行计数，因为可能A做了一半，主教练就把CPU执行权力给B，就会造成A没办法知道我上次执行的位置，所以需要一个计数器，在JVM这种为每个线程制定的计数器叫：程序计数器** ，

### 1.6.2 java自动内存管理机制-运行时数据区域- 程序计数器

```
	线程私有。可看作是当前线程所执行的字节码的行号指示器，字节码解释器的工作是通过改变这个计数值来读取下一条要执行的字节码指令。多线程是通过线程轮流切换并分配处理器执行时间来实现的，任何一个时刻，一个内核只能执行一条线程中的指令。为了线程切换后能恢复到正确的执行位置，每条线程都需要一个独立的程序计数器。这就是一开始说的“线程私有”。如果线程正在执行的方法是Java方法，计数器记录的是虚拟机字节码的指令地址；如果是Native方法，计数器值为空。
```

程序计数器是唯一一个在Java虚拟机规范中没有规定OOM(OutOfMemoryError)情况的区域。

### 1.6.3 java自动内存管理机制-Java虚拟机栈

​	在java中执行某个方法的调用，就是栈调用的过程，这个时候我们会把方法中的变量和结果都放入到Java栈中，我们称之为入栈，入下图:

代码如下：

```java
package com.aicode.classloaderdemo.chapter01;
public class chapter01 {
    public int save(String name){
        int a = 100;
        int b = 100;
        return 0;
    }
    public static void main(String[] args){
        new chapter01().save("zhagnsan");
    }
}
```

如图：

![image-20201103182356816](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201103182356816.png)

当执行完毕以后：就会把栈帧从栈中移除，获取返回的结果，继续执行main，执行完毕释放栈，GC开始回收。

```
线程私有，生命周期和线程相同。Java虚拟机栈描述的是Java方法的内存模型：每个方法在执行时都会创建一个栈帧，存储**局部变量表、操作数栈、动态链接、方法出口信息**，每一个方法从调用到结束，就对应这一个栈帧在虚拟机栈中的进栈和出栈过程。局部变量表保存了各种基本数据类型（int、double、char、byte等）、对象引用（不是对象本身）和returnAddress类型（指向了一条字节码地址）。

栈的空间大小设置： -Xss 为jvm启动的每个线程分配的内存大小
```

* 线程请求的栈深度大于虚拟机所允许的深度，抛出StackOverflowError；
* 虚拟机栈扩展时无法申请到足够的内存，抛出OutOfMemoryError

#### 1.6.3.1 StackOverflowError

```java
/**
* 栈超出最大深度：StackOverflowError
OutOfMemoryError（代码谨慎使用，会引起电脑卡死 ）
* VM args: -Xss128k
**/
public class StackSOF {
    private int stackLength = 1;
    public void stackLeak(){
        stackLength++;
        stackLeak();
    }
    public static void main(String[] args) {
        StackSOF stackSOF = new StackSOF();
        try {
            stackSOF.stackLeak();
        } catch (Throwable e) {
            System.out.println("当前栈深度:" +
                    stackSOF.stackLength);
            e.printStackTrace();
        }
    }
}
```

```
java.lang.StackOverflowError
当前栈深度:30170
at cn.itcast.jvm.StackSOF.stackLeak(StackSOF.java:11)
at cn.itcast.jvm.StackSOF.stackLeak(StackSOF.java:11)
方法递归调用，造成深度过深，产生异常
```

#### 1.6.3.2 OutOfMemoryError（代码谨慎使用，会引起电脑卡死 ）

```java
/**
 * 栈内存溢出： OOM
 * VM Args: -Xss2m
 **/
public class StackOOM {
    private void dontStop(){
        while (true){
        }
    }
    public void stackLeakByThread(){
        while(true){
            Thread t = new Thread(new Runnable() {
                public void run() {
                    dontStop();
                }
            });
            t.start();
        }
    }
    public static void main(String[] args) {
        StackOOM stackOOM = new StackOOM();
        stackOOM.stackLeakByThread();
    }
}
```

```
Exception in thread "main"
java.lang.OutOfMemoryError:unable to create new native thread
```

​	单线程下栈的内存出现问题了，都是报StackOverflow的异常，只有在多线程的情况下，当新创建线程无法在分配到新的栈内存资源时，会报内存溢出。

#### 1.6.3.3 小结

执行java的方法过程其实就是：java本地栈中出栈和入栈的过程。
栈的空间大小设置： -Xss 为jvm启动的每个线程分配的内存大小

![image-20201104090320769](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104090320769.png)

### 1.6.4 java自动内存管理机制-本地方法栈

​	上述虚拟机栈为JVM执行Java方法服务，本地方法则为执行Native服务。其他和虚拟机栈类似，也会抛出 StackOverflowError、OutOfMemoryError。

​	但是虽然本地方法栈不是用java编写的，但是原理和java虚拟机栈执行是一样的，也是栈帧出栈和入栈的过程。那么那些方法才是本地方法呢？在java中我们的定义父类或者说超类： Object 如下：

```java
package java.lang;
public class Object {
    private static native void registerNatives();
    static {
        registerNatives();
    }
    public final native Class<?> getClass();
    public native int hashCode();
    public boolean equals(Object obj) {
        return (this == obj);
    }
    protected native Object clone() throws
            CloneNotSupportedException;
    public String toString() {
        return getClass().getName() + "@" +
                Integer.toHexString(hashCode());
    }
    public final native void notify();
    public final native void notifyAll();
    public final native void wait(long timeout) throws
            InterruptedException;
    public final void wait(long timeout, int nanos)
            throws InterruptedException {
    }
    public final void wait() throws
            InterruptedException {
        wait(0);
    }
    protected void finalize() throws Throwable { }
}
```

* 面试题

```
下面不属于Object类中方法的是: 
hashCode()
finally() （x）
wait()
toString()
```

### 1.6.5 java自动内存管理机制-Java堆

​	常说的“栈内存”、“堆内存”，其中前者指的是虚拟机栈，后者说的就是Java堆了。**Java堆是被线程共享的**。在虚拟机启动时被创建。**Java堆是Java虚拟机所管理的内存中最大的一块**。Java堆的作用是存放对象实例，Java堆可以处于物理上不连续的内存空间中，**只要求逻辑上连续即可**。

​	Java堆是：**垃圾收集器管理的主要区域**，因此很多时候也被称作"**GC堆**",从内存回收的角度看，现在收集器都基本采用**分代回收**的算法 所以Java堆呢。还可以细分为：**新生代、老年代**。 在细致一点的有：**Eden空间、From Survivor空间、To Survivor空间**。 默认的，**新生代 ( Young ) 与老年代 (Old ) 的比例的值为 1:2**

![image-20201104091453816](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104091453816.png)

堆的空间大小设置：

```
-Xms java堆启动时内存
-Xmx java堆可扩展的最大内存
```

* 内存泄漏：Memory Leak 一个无用的对象，应该被回收，却因为某种原因一直未被回收
* 内存溢出：Memory Overflow 对象确实都应该活着，这个时候内存不够用了

#### 1.6.5.1 案例：

```java
package com.aicode.classloaderdemo.chapter01;
import java.util.ArrayList;
import java.util.List;
/**
 * 堆内存溢出演示
 * VM Args: -Xms20m -Xmx20m -
 XX:+HeapDumpOnOutOfMemoryError
 * VM Args -Xms20m 初始化堆内存大小
 * -Xmx20m 堆最大内存大小
 **/
public class HeapOOM {
    public static void main(String[] args) throws
            InterruptedException {
        List<byte[]> list = new ArrayList<>();
        int i=0;
        while (true){
            list.add(new byte[1024]);
        }
    }
}
```

```
java.lang.OutOfMemoryError: Java heap space
Dumping heap to java_pid156408.hprof ...
Heap dump file created [20850769 bytes in 0.035 secs]
Exception in thread "main" java.lang.OutOfMemoryError:
Java heap space at com.aicode.classloaderdemo.chapter01.HeapOOM.main(HeapOOM.java:15)
*** java.lang.instrument ASSERTION FAILED ***:
"!errorOutstanding" with message can't create byte arrau at JPLISAgent.c line: 813
```

![image-20201104092311582](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104092311582.png)

#### 1.6.5.2 小结

* 堆区存储的都是对象
* 也是我们gc 回收的重要区域
* 如果出现内存泄漏和内存溢出，可以通过调整堆区的大小来扩容，

```
-Xms java堆启动时内存
-Xmx java堆可扩展的最大内存
```

​	比如如果你在启动一个springboot项目的时候，出现内存溢出的现象，也就是出现java.lang.OutOfMemoryError: Java heap space ，你可以在启动的时候配置堆的内存大小。

* 查看默认的堆内存大小如下命令

```
> java -XX:+PrintFlagsFinal -version |findstr /i
"HeapSize PerSize ThreadStackSize"
```

也就是在我的笔记本上默认的MaxHeapSize 是4253024256/1024/1024/1024=3.96G., 初始堆大小是InitialHeapSize 266338304 /1024/1024=254M

![image-20201104092743096](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104092743096.png)

```
> java -XX:+PrintCommandLineFlags 1 -version
```

![image-20201104094741261](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104094741261.png)

```
java -jar springboot.jar -Xms20m -Xmx20m -XX:+HeapDumpOnOutOfMemoryError
```

### 1.6.6  java自动内存管理机制-方法区

​	也被称为永久代，在jdk1.8中称之为：元数据空间,是线程共享的区域。存储已被虚拟机加载的**类信息、常量、静态变量、即使编译器编译后的代码等数据**。方法区无法满足内存分配需求时，抛出OutOfMemoryError。JVM规范被没要求这个区域需要实现垃圾收集，因为这个区域回收主要针对的是类和常量池的信息回收，回收结果往往难以令人满意。
​	运行时常量池：是方法区的一部分。Java语言不要求常量只能在编译期产生，换言之，在运行期间也能将新的常量放入。
​	方法区空间大小设置： -XX:PermSize -XX:MaxPermSize
​	1.8之后设置： -XX:MetaspaceSize -XX:MaxMetaspaceSize

​	如果我们无限的增加类，或者加载的类过多，可能就会造成这块的内存不够，就会出现内存溢出的现象。比如在springboot和spring中依赖的jar包过多，可能会引发这块的区域不够，我们就需要调整大小，如果没有出现的情况下不建议去调整。

#### 1.6.6.1 OutOfMemoryError

```xml
<dependency>
    <groupId>cglib</groupId>
    <artifactId>cglib</artifactId>
    <version>3.3.0</version>
</dependency>
```

利用cglib不停的死循环产生代理类的方式，让方法区爆掉：

```Java
package com.aicode.classloaderdemo.chapter01;
import net.sf.cglib.proxy.Enhancer;
import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;
import java.lang.reflect.Method;
/**
 * 方法区 OOM
 * VM Args: -XX:PermSize10m -XX:MaxPermSize10m 1.8移
 除永生代之前
 * VM Args:-XX:MetaspaceSize=10m -
 XX:MaxMetaspaceSize=10m ---1.8和之后的配置
 **/
public class PermOOM {
    public static void main(final String[] args) {
        while (true){
            Enhancer enhancer = new Enhancer();
            enhancer.setSuperclass(PermOOM.class);
            enhancer.setUseCache(false);
            enhancer.setCallback(new MethodInterceptor() {
                 public Object intercept(Object o,Method method, Object[] objects, MethodProxy methodProxy) throws Throwable {
                     return methodProxy.invoke(o,args);
                 }
             });
            enhancer.create();
        }
    }
}
```

```
Exception in thread "main" java.lang.OutOfMemoryError:Metaspace
at java.lang.Class.forName0(Native Method)
at java.lang.Class.forName(Class.java:348)
at net.sf.cglib.core.ReflectUtils.defineClass(ReflectUtils.java:386)
at net.sf.cglib.core.AbstractClassGenerator.create(AbstractClassGenerator.java:219)
at net.sf.cglib.proxy.Enhancer.createHelper(Enhancer.java:377)
at net.sf.cglib.proxy.Enhancer.create(Enhancer.java:285)
at cn.itcast.jvm.PermOOM.main(PermOOM.java:24)
Process finished with exit code 1
```

​	Cglib动态代理可以动态创建代理类，这些代理类的Class会动态的加载入内存中，存入到方法区。所以当我们把方法区内存调小后便可能会产生方法区内存溢出,1.8之前的JDK我们可以称方法区为永久代 :PermSpace 1.8之后方法区改为MetaSpace 元空间。

#### 1.6.6.2 小结

​	如果没有出现 Caused by: java.lang.OutOfMemoryError:Metaspace 这种错误，各位不要优化。

* 这个配置在我开发里会配置到吗？
  一般不会。我就 怕大家和昨天学习索引优化一样，我是不是要优化一下才显得我很厉害。千万不要这样奇怪的想法，一定是出现对应异常或者问题以后我们才会优化。

* 如果出现了异常怎么去配置呢？

  比如springboot项目：

以jar发布：

```
java -jar springboot.jar -XX:MetaspaceSize=100m -XX:MaxMetaspaceSize=100m
```

是war发布：

```
在tomcat 中去配置的catalina.sh配置
```



# 二、 JVM类加载机制

## 2.1 JVM类加载机制 - 类加载的生命周期

### 2.1.1 概述

​	java的class类文件实际上是二进制（字节码）文件格式，class文件中包含了java虚拟机指令集和符号表以及若干其他辅助信息。实际上虚拟机载入和执行同一种平台无关的字节码（class文件），实现了平台无关性。

![image-20201104101547695](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104101547695.png)

​	而java的类加载机制指的是虚拟机把描述类的数据从Class文件加载到内存，并对数据进行校验、转换解析和初始化，最终形成可以被虚拟机直接使用的Java类型。

在Java的语言中，**类型的加载、连接和初始化过程都是在程序运行期间完成的**

指的是类从被加载到虚拟机内存开始，到卸载出内存为止,一共要经历7个阶段：

![image-20201104102221441](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104102221441.png)

## 2.2 类加载器-ClassLoader

### 2.2.1 目标

明白和了解类加载器的加载过程和运行流程

### 2.2.2  分析

​	类加载器负责装入类，搜索网络，jar、zip、文件夹、二进制数据、内存等制定位置的类资源。一个java程序运行，最少有三个类加载器实例，负责不同类的加载。“将class文件加载进JVM的方法区，并在方法区中创建一个java.lang.Class对象作为外界访问这个类的接口。”实现这一动作的代码模块称为类加载器。

### 2.2.3 案例

**类和类加载器:**

​	对于任意一个类，都需要由加载它的类加载器和这个类本身一同确立其在虚拟机中的唯一性。 通俗点说： 比较两个类是否“相等”，只有在这两个类是由同一个类加载器加载的前提下才用意义，否则，即使这两个类来源于同一个Class文件，被同一个虚拟机加载，只要加载它们的类加载器不同，那这两个类就必定不相等。这里的“相等” 包括： Class对象的 equals() 方法、isInstance()方法，也包括 instanceof关键字。

```java
package com.aicode.classloaderdemo.chapter01;
import java.io.IOException;
import java.io.InputStream;
    /**
     * 使用自定义类加载器加载Class对象
     * 系统默认类加载器加载Class 对象
     * 属于两个不同的类
     **/
public class ClassLoaderTest1 {
    public static void main(String[] args) throws
            Exception{
		// 自定义 类加载器
        ClassLoader myLoader = new ClassLoader() {
            @Override
            public Class<?> loadClass(String name)
                    throws ClassNotFoundException {
                try {
                    String fileName =
                        name.substring(name.lastIndexOf(".")+1) + ".class";
                    InputStream in =
                            getClass().getResourceAsStream(fileName);
                    if(in == null){
                        return super.loadClass(name);
                    }
                    byte[] b = new byte[in.available()];
                    in.read(b);
                    return defineClass(name,b,0,b.length);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return super.loadClass(name);
            }
        };
	//使用自定义类加载器加载出来的Class对象
        Class c1 = myLoader.loadClass("com.aicode.classloaderdemo.chapter01.ClassLoaderTest1");
	//使用系统默认的类加载器加载出来的Class对象
        Class c2 = ClassLoaderTest1.class;
        System.out.println(c1.getClassLoader());
        System.out.println(c2.getClassLoader());
	//结果为false
        System.out.println(c1==c2);
    }
}
```

运行结果如下：

```
com.aicode.classloaderdemo.chapter01.ClassLoaderTest1$1@2f0e140b
sun.misc.Launcher$AppClassLoader@18b4aac2
false
```

### 2.2.4 小结

* 可以得出结论，即使是同一个类，用不同的加载器去加载类，出现两个class不一致的情况。
* 所有的加载器都存放在： sun.misc.Launcher 包下

## 2.3 类加载器-ClassLoader类加载器的分类

### 2.3.1 目标

掌握类加载器的分类和它们具体的含义

### 2.3.2 分析

![image-20201104132152742](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104132152742.png)

代码如下：

```java
package com.aicode.classloaderdemo.chapter01;
public class ClassLoaderView {
    public static void main(String[] args) throws
            Exception{
// 加载核心的类加载器
        System.out.println("核心类库加载器：" +
                ClassLoaderView.class.getClassLoader().loadClass(Strin
                        g.class.getName()).getClassLoader());
// 加载拓展类库加载器
        System.out.println("拓展类库加载器：" +
                ClassLoaderView.class.getClassLoader().loadClass("com.
                        sun.nio.zipfs.ZipInfo").getClassLoader());
// 加载应用程序加载器
                        System.out.println("应用程序加载器：" +
                                ClassLoaderView.class.getClassLoader());
// 双亲委派模型 Parents Delegation Model
        System.out.println("应用程序加载器的父类"
                +ClassLoaderView.class.getClassLoader().getParent());
        System.out.println("应用程序加载器的父类的父类"
                        +ClassLoaderView.class.getClassLoader().getParent().ge
                tParent());
        System.out.println(System.getProperty("java.class.pat
                h"));
    }
}
```

## 2.4 类加载器-启动类加载器-BootStrapClassLoader
### 2.4.1 目标

掌握核心加载器

### 2.4.2 分析

​	启动类加载器-BootStrap ClassLoader,又称根加载器

* 每次执行 java 命令时都会使用该加载器为虚拟机加载核心类。
* 该加载器是由 native code 实现，而不是 Java 代码，加载类的路径为<JAVA_HOME>/jre/lib。
* 特别的 <JAVA_HOME>/jre/lib/rt.jar 中包含了 sun.misc.Launcher 类，而 sun.misc.Launcher ExtClassLoader和sun.misc.Launcher AppClassLoader 都是 sun.misc.Launcher的内部类，所以拓展类加载器和系统类加载器都是由启动类加载器加载的。

疑问：什么是核心类

​	其实就是我们每天在开发的使用java.lang，java.util，等这些包下的类。而这个类都是存放在jre/lib/rt.jar 中

​	先定位String.class 这个类

* 查看某个类：

![image-20201104132946561](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104132946561.png)

* 查看类所在位置

![image-20201104133028160](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104133028160.png)

* 定位jar包所在位置

![image-20201104133114559](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104133114559.png)

* 最后展示如下：

![image-20201104133219503](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104133219503.png)

### 2.4.3 小结

疑虑：为什么要学习和掌握这个知识点呢？

​	告诉我们我们在开发java项目的时候，我们虽然使用的开发工具是idea或eclicpse。在开发工具中已经帮我们提供了一个java的环境，这样我们就可以直接开发和使用了，我们在开发过程中之所以能直接去调用java提供的核心类库（java.lang、java.io等）。是因为我们在启动和运行项目的时候，java提供的类加载器会自动去找到这些jar包，并且把我们当前项目的java文件进行编译一起编译到jvm中。

## 2.5 类加载器-扩展类加载器(ExtensionClassLoader)

### 2.5.1 目标

* 用于加载拓展库中的类。拓展库路径为<JAVA_HOME>/jre/lib/ext/。
* 实现类为 sun.misc.Launcher$ExtClassLoader。

![image-20201104134147173](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104134147173.png)

### 2.5.2 分析源码

```java
private static File[] getExtDirs() {
    String var0 =
            System.getProperty("java.ext.dirs");
    File[] var1;
    if (var0 != null) {
        StringTokenizer var2 = new StringTokenizer(var0, File.pathSeparator);
        int var3 = var2.countTokens();
        var1 = new File[var3];
        for(int var4 = 0; var4 < var3; ++var4)
        {
            var1[var4] = new File(var2.nextToken());
        }
    } else {
        var1 = new File[0];
    }
    return var1;
}
```

可以去打印

```java
System.out.println(System.getProperty("java.ext.dirs"));
```

结果如下：

```
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext;C:\Windows\Sun\Java\lib\ext
```

### 2.5.3 小结

​	扩展性的包，都属于java第三方依赖的jar,这个扩展包是实际的开发中可以删除，它都属于实验性阶段。并没有纳入到java的开发标准中。本人怀疑：就是oracle的jdk的开发团队也在学习别人好的东西，但是又怕忘记所以把他放入到了ext中，用于后记的升级和开发维护中。

## 2.6 类加载器-应用程序加载器-AppClassLoader

### 2.6.1 目标

掌握和了解应用程序加载

### 2.6.2 分析

![image-20201104140129249](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104140129249.png)

打印：

```java
System.out.println(System.getProperty("java.class.path"));
```

结果如下：

```java
==============================AppLoader默认加载器ext包======================
C:\Program Files\Java\jdk1.8.0_211\jre\lib\charsets.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\deploy.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\accessbridge-64.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\cldrdata.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\dnsns.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\jaccess.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\jfxrt.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\localedata.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\nashorn.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\sunec.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\sunjce_provider.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\sunmscapi.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\sunpkcs11.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\ext\zipfs.jar;
==============================AppLoader默认加载器核心lib包======================
C:\Program Files\Java\jdk1.8.0_211\jre\lib\javaws.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\jce.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\jfr.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\jfxswt.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\jsse.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\managementagent.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\plugin.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\resources.jar;
C:\Program Files\Java\jdk1.8.0_211\jre\lib\rt.jar;
===============================java项目编译的class文件目录===========================
C:\czbk\备课\07-高级架构师就业加强课-88888888888888\05_Jvm优化及面试热点深入解析\代码\classloaderdemo\target\classes;
===========================项目依赖的mavenjar包==============================
C:\respository\org\springframework\boot\spring-bootstarter\2.2.1.RELEASE\spring-boot-starter-2.2.1.RELEASE.jar;
C:\respository\org\springframework\boot\springboot\2.2.1.RELEASE\spring-boot-2.2.1.RELEASE.jar;
C:\respository\org\springframework\springcontext\5.2.1.RELEASE\spring-context-5.2.1.RELEASE.jar;
C:\respository\org\springframework\springaop\5.2.1.RELEASE\spring-aop-5.2.1.RELEASE.jar;
C:\respository\org\springframework\springbeans\5.2.1.RELEASE\spring-beans-5.2.1.RELEASE.jar;
C:\respository\org\springframework\springexpression\5.2.1.RELEASE\spring-expression-5.2.1.RELEASE.jar;
C:\respository\org\springframework\boot\spring-bootautoconfigure\2.2.1.RELEASE\spring-boot-autoconfigure-2.2.1.RELEASE.jar;
C:\respository\org\springframework\boot\spring-bootstarter-logging\2.2.1.RELEASE\spring-boot-starterlogging-2.2.1.RELEASE.jar;
C:\respository\ch\qos\logback\logbackclassic\1.2.3\logback-classic-1.2.3.jar;
C:\respository\ch\qos\logback\logbackcore\1.2.3\logback-core-1.2.3.jar;
C:\respository\org\apache\logging\log4j\log4j-toslf4j\2.12.1\log4j-to-slf4j-2.12.1.jar;
C:\respository\org\apache\logging\log4j\log4japi\2.12.1\log4j-api-2.12.1.jar;
C:\respository\org\slf4j\jul-to-slf4j\1.7.29\jul-toslf4j-1.7.29.jar;
C:\respository\jakarta\annotation\jakarta.annotationapi\1.3.5\jakarta.annotation-api-1.3.5.jar;
C:\respository\org\springframework\springcore\5.2.1.RELEASE\spring-core-5.2.1.RELEASE.jar;
C:\respository\org\springframework\springjcl\5.2.1.RELEASE\spring-jcl-5.2.1.RELEASE.jar;
C:\respository\org\yaml\snakeyaml\1.25\snakeyaml-1.25.jar;
C:\respository\org\slf4j\slf4j-api\1.7.29\slf4j-api-1.7.29.jar;
C:\tools\idea\IntelliJ IDEA 2019.1.3\lib\idea_rt.jar
```

### 2.6.3 小结

​	从上面打印的结果可以清晰的看到：应用程序app加载器，可以很清楚的看到我们java项目整个加载和过程是什么样子的。我们的编写的类和用maven依赖的jar包是如何加入到jvm虚拟机的。

## 2.7 类加载器-JVM如何知道我们的类在何方

### 2.7.1 目标

掌握JVM如何知道我们的类在何方

### 2.7.2  分析

class信息存放在不同的位置，桌面的jar，项目bin目录，target目录等等

### 2.7.3 步骤

* 查看openjdk源代码，sun.misc.Launcher.AppClassLoader
* 读取java.class.path配置，指定去那些地址加载类资源
* 验证过程： 利用jps、jcmd两个命令

jps：查看本机java进程

代码

```java
package com.aicode.classloaderdemo.chapter01;
public class Main {
    public static void main(String[] args) throws
            Exception{
        System.out.println("Hello world....");
        System.in.read();
    }
}
```

![image-20201104141244079](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104141244079.png)

​	这个命令其实还发非常有用处，在实际的应用开发和生产中，有些时候我们不知道当前项目经常出现端口被占用的问题，可以通过jps来查看是否还有java程序正在运行，如果有可以执行命令taskkill /PID 309184 /F

![image-20201104141507577](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104141507577.png)

查看运行时配置：jcm 进程号 VM.system_properties

![image-20201104141559059](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104141559059.png)

jcmd help

```c
Usage: jcmd <pid | main class> <command
...|PerfCounter.print|-f file>
or: jcmd -l
or: jcmd -h
command must be a valid jcmd command for the
selected jvm.
Use the command "help" to see which commands are
available.
If the pid is 0, commands will be sent to all Java
processes.
The main class argument will be used to match
(either partially
or fully) the class used to start Java.
If no options are given, lists Java processes (same
as -p).
PerfCounter.print display the counters exposed by
this process
-f read and execute commands from the file
-l list JVM processes on the local machine
-h this help
```

使用方式如下：

```c
# 格式 jcmd pid help
>jcmd 307512 help
307512:
The following commands are available:
JFR.stop
JFR.start
JFR.dump
JFR.check
VM.native_memory
VM.check_commercial_features
VM.unlock_commercial_features
ManagementAgent.stop
ManagementAgent.start_local
ManagementAgent.start
VM.classloader_stats
GC.rotate_log
Thread.print
GC.class_stats
GC.class_histogram
GC.heap_dump
GC.finalizer_info
GC.heap_info
GC.run_finalization
GC.run
VM.uptime
VM.dynlibs
VM.flags
VM.system_properties
VM.command_line
VM.version
help
```

使用如下：

```C
> jcmd 307512 VM.system_properties
#Mon Dec 02 10:02:57 CST 2019
java.runtime.name=Java(TM) SE Runtime Environment
sun.boot.library.path=C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\bin
java.vm.version=25.211-b12
java.vm.vendor=Oracle Corporation
java.vendor.url=http\://java.oracle.com/
path.separator=;
java.vm.name=Java HotSpot(TM) 64-Bit Server VM
file.encoding.pkg=sun.io
user.script=user.country=CN
sun.java.launcher=SUN_STANDARD
sun.os.patch.level=
java.vm.specification.name=Java Virtual Machine
Specification
user.dir=C\:\\czbk\\\u5907\u8BFE\\07-
\u9AD8\u7EA7\u67B6\u6784\u5E08\u5C31\u4E1A\u52A0\u5F3
A\u8BFE-88888888888888\\05_Jvm\u4F18\u5316\u53CA\u9
762\u8BD5\u70ED\u70B9\u6DF1\u5165\u89E3\u6790\\\u4EE3
\u7801\\classloader-demo
java.runtime.version=1.8.0_211-b12
java.awt.graphicsenv=sun.awt.Win32GraphicsEnvironment
java.endorsed.dirs=C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\endorsed
os.arch=amd64
java.io.tmpdir=C\:\\Users\\86150\\AppData\\Local\\Tem
p\\
line.separator=\r\n
java.vm.specification.vendor=Oracle Corporation
user.variant=
os.name=Windows 10
sun.jnu.encoding=GBK
java.library.path=C\:\\Program
Files\\Java\\jdk1.8.0_211\\bin;C\:\\Windows\\Sun\\Jav
a\\bin;C\:\\Windows\\system32;C\:\\Windows;C\:\\tools
\\id
ea\\IntelliJ IDEA
2019.1.3\\jre64\\\\bin;C\:\\tools\\idea\\IntelliJ
IDEA 2019.1.3\\jre64\\\\bin\\server;C\:\\Xshell
6\\;C\:\\Program Files (x
86)\\Intel\\Intel(R) Management Engine
Components\\iCLS\\;C\:\\Program
Files\\Intel\\Intel(R) Management Engine
Components\\iCLS\\;C\:\\Windo
ws\\system32;C\:\\Windows;C\:\\Windows\\System32\\Wbe
m;C\:\\Windows\\System32\\WindowsPowerShell\\v1.0\\;C
\:\\Windows\\System32\\OpenSSH\\;C\
:\\Program Files (x86)\\Intel\\Intel(R) Management
Engine Components\\DAL;C\:\\Program
Files\\Intel\\Intel(R) Management Engine
Components\\DAL;C\:\\Program Files (x86)\\Intel\\Intel(R)
Management Engine Components\\IPT;C\:\\Program
Files\\Intel\\Intel(R) Management Engine Componen
ts\\IPT;C\:\\Program Files (x86)\\NVIDIA
Corporation\\PhysX\\Common;C\:\\Program Files\\NVIDIA
Corporation\\NVIDIA NvDLISR;C\:\\Program Files
\\Java\\jdk1.8.0_211\\bin;C\:\\Program
Files\\Redis\\;C\:\\tools\\apache-maven-
3.6.1\\bin;C\:\\Users\\86150\\TortoiseSVN\\bin;C\:\\P
rogram Fi
les\\erl10.0.1\\bin;C\:\\tools\\rabbitmq_server-
3.7.7\\sbin;C\:\\Program Files\\nodejs\\;C\:\\Program
Files\\Git\\cmd;C\:\\Program Files\\Tor
toiseGit2\\bin;C\:\\Users\\86150\\AppData\\Local\\Mic
rosoft\\WindowsApps;C\:\\Users\\86150\\AppData\\Local
\\Pandoc\\;C\:\\Users\\86150\\AppDa
ta\\Local\\Programs\\Microsoft VS
Code\\bin;C\:\\Users\\86150\\AppData\\Roaming\\npm;C\
:\\Program Files\\nodejs;;.
java.specification.name=Java Platform API
Specification
java.class.version=52.0
sun.management.compiler=HotSpot 64-Bit Tiered
Compilers
os.version=10.0
user.home=C\:\\Users\\86150
user.timezone=Asia/Shanghai
java.awt.printerjob=sun.awt.windows.WPrinterJob
file.encoding=UTF-8
java.specification.version=1.8
java.class.path=C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\charsets.jar;C\:
\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\deploy.jar;C
\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\accessbridge-
64.jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\cldrdata.jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\dnsns.jar;C
\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\jaccess.jar
;C\:\\Pr
ogram
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\jfxrt.jar;C
\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\localedata.
jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\nashorn.jar
;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\sunec.jar;C
\:\\Program Files\\Ja
va\\jdk1.8.0_211\\jre\\lib\\ext\\sunjce_provider.jar;
C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\sunmscapi.jar;C\:\\Program Files\
\Java\\jdk1.8.0_211\\jre\\lib\\ext\\sunpkcs11.jar;C\:
\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext\\zipfs.jar;C
\:\\Program Files\\Java\\
jdk1.8.0_211\\jre\\lib\\javaws.jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\jce.jar;C\:\\Pro
gram Files\\Java\\jdk1.8.0_211\\jre\\lib
\\jfr.jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\jfxswt.jar;C\:\\
Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\jsse.jar;C\:\\Pr
ogra
m Files\\Java\\jdk1.8.0_211\\jre\\lib\\managementagent.
jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\plugin.jar;C\:\\
Program Files\\
Java\\jdk1.8.0_211\\jre\\lib\\resources.jar;C\:\\Prog
ram Files\\Java\\jdk1.8.0_211\\jre\\lib\\rt.jar;
==========================这里加载的
=============================
C\:\\czbk\\\u5907\u8BFE\\07-\u9AD8\u7EA7\u67B6\u6784\u5E08\u5C31\u4E1A\u52A0\u5F3A\u8BFE-
88888888888888\\05_Jvm\u4F18\u5316\u53CA\u9762\u8BD5\
u70ED\u70B9\u6DF1\u5165\u89E3\u6790\\\u
4EE3\u7801\\classloader-demo\\target\\classes;
C\:\\respository\\org\\springframework\\boot\\springboot-
starter\\2.2.1.RELEASE\\spring-boot-s
tarter-
2.2.1.RELEASE.jar;C\:\\respository\\org\\springframew
ork\\boot\\spring-boot\\2.2.1.RELEASE\\spring-boot-
2.2.1.RELEASE.jar;C\:\\resposi
tory\\org\\springframework\\springcontext\\
5.2.1.RELEASE\\spring-context-
5.2.1.RELEASE.jar;C\:\\respository\\org\\springframew
ork\\spring-ao
p\\5.2.1.RELEASE\\spring-aop-
5.2.1.RELEASE.jar;C\:\\respository\\org\\springframew
ork\\spring-beans\\5.2.1.RELEASE\\spring-beans-
5.2.1.RELEAS
E.jar;C\:\\respository\\org\\springframework\\springexpression\\
5.2.1.RELEASE\\spring-expression-
5.2.1.RELEASE.jar;C\:\\respository\\org\\sp
ringframework\\boot\\spring-bootautoconfigure\\
2.2.1.RELEASE\\spring-bootautoconfigure-
2.2.1.RELEASE.jar;C\:\\respository\\org\\springframe
work\\boot\\spring-boot-starterlogging\\
2.2.1.RELEASE\\spring-boot-starter-logging-
2.2.1.RELEASE.jar;C\:\\respository\\ch\\qos\\logback\
\log
back-classic\\1.2.3\\logback-classic-
1.2.3.jar;C\:\\respository\\ch\\qos\\logback\\logback
-core\\1.2.3\\logback-core-1.2.3.jar;C\:\\resposito
ry\\org\\apache\\logging\\log4j\\log4j-toslf4j\\
2.12.1\\log4j-to-slf4j-
2.12.1.jar;C\:\\respository\\org\\apache\\logging\\lo
g4j\\log4j-api\\2.12.1\\log4j-api-
2.12.1.jar;C\:\\respository\\org\\slf4j\\jul-toslf4j\\
1.7.29\\jul-to-slf4j-
1.7.29.jar;C\:\\respository\\jakarta\\annotatio
n\\jakarta.annotation-api\\1.3.5\\jakarta.annotationapi-
1.3.5.jar;C\:\\respository\\org\\springframework\\spr
ing-core\\5.2.1.RELEASE\\spring
-core-
5.2.1.RELEASE.jar;C\:\\respository\\org\\springframew
ork\\spring-jcl\\5.2.1.RELEASE\\spring-jcl-
5.2.1.RELEASE.jar;C\:\\respository\\org
\\yaml\\snakeyaml\\1.25\\snakeyaml-
1.25.jar;C\:\\respository\\org\\slf4j\\slf4japi\\
1.7.29\\slf4j-api-
1.7.29.jar;C\:\\tools\\idea\\IntelliJ
IDEA 2019.1.3\\lib\\idea_rt.jar
user.name=86150
java.vm.specification.version=1.8
sun.java.command=com.aicode.classloaderdemo.chapter01
.Main
java.home=C\:\\Program Files\\Java\\jdk1.8.0_211\\jre
sun.arch.data.model=64
user.language=zh
java.specification.vendor=Oracle Corporation
awt.toolkit=sun.awt.windows.WToolkit
java.vm.info=mixed mode
java.version=1.8.0_211
java.ext.dirs=C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\ext;C\:\\Windows
\\Sun\\Java\\lib\\ext
sun.boot.class.path=C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\resources.jar;C\
:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\rt.jar;
C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\sunrsasign.jar;C
\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\jsse.jar;C\:\\Pr
ogram Files\\Java\\jdk1.8.0_211\\jre\\lib\\jce.jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\lib\\charsets.jar;C\:
\\Program Files\\Java\\jdk1.8.0_21
1\\jre\\lib\\jfr.jar;C\:\\Program
Files\\Java\\jdk1.8.0_211\\jre\\classes
java.vendor=Oracle Corporation
file.separator=\\
java.vendor.url.bug=http\://bugreport.sun.com/bugrepo
rt/
sun.io.unicode.encoding=UnicodeLittle
sun.cpu.endian=little
sun.desktop=windows
sun.cpu.isalist=amd64
    
```

## 2.8 类加载器-类不会重复加载

### 2.8.1 目标

验证类会不会重复加载

### 2.8.2 分析

* 类的唯一性：同一个类加载器，类名一样，代表是同一个类。
* 识别方式：ClassLoader Instance id + packagename + className
* 验证方式：使用类加载器，对同一个class类的不同斑斑，进行多次加载，检查是否会加载到最新的代码。

### 2.8.3 代码

* 在磁盘目录下新建一个c://test/HelloService.java

```java
public class HelloService {
    public static String value = getValue();
    static{
        System.out.println("*************** static
                area code");
    }
    public static String getValue(){
        System.out.println("************** static
                method");
        return "success";
    }
    public void test(){
        System.out.println("hello 1111111111" +
value);
    }
}
```

* 然后进行编译javac HelloService.java

```
> javac com/aicode/HelloService.java
```

![image-20201104143052033](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104143052033.png)

* 生成 HelloService.class 文件即可。

* 自定义类加载器

```java
package com.aicode.classloaderdemo.chapter01;
import java.net.URL;
import java.net.URLClassLoader;
public class LoadTest {
    public static void main(String[] args) throws
            Exception{
        URL url = new URL("file:C:\\test\\");//jvm需要
        加载的类存放的位置
//定义一个父加载器
        URLClassLoader classLoader = new
                URLClassLoader(new URL[]{url});
//创建一个新的类加载器
        while (true){
// 1：这里并不会去执行静态成员的加载，只会做静态成员的存储和划分
            Class clz =
                    classLoader.loadClass("HelloService");
            System.out.println("HelloService 使用的类加载
                    器是：" +clz.getClassLoader());
// 2：通过反射实例化对象,真正的执行在创建对象的时候静态成员会执行和初始化
                    Object newIntance = clz.newInstance();
            Object test =
                    clz.getMethod("test").invoke(newIntance);
            Thread.sleep(3000);
        }
    }
}
```

![image-20201104143400333](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104143400333.png)

* 这个时候如果我们去修改了，然后重新编译一下，看是否能够自动加载我们的类呢？如下：

![image-20201104143450806](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104143450806.png)

* 然后重新编译javac HelloService.java 你会发现并没有去加载类信息。

![image-20201104143713612](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104143713612.png)

* 如果你重新运行以后即可加载修改的信息

![image-20201104143753139](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104143753139.png)

### 2.8.4 小结

* 可以看出来java的代码是基于编译和运行的机制，都是通过类加载器去加载和装配的
* 通过上面的例子也可以告诉我们，我们在平时的开发中，为什么修改了java的类、修改了配置文件都需要重新启动的原因，因为修改了类它并不会重新把修改和编译好的class重新调用类加载器去执行。如果你要实现热部署的功能可以把类加载器放入到死循环中，每次保证类加载是全新的即可：代码如下：

```java
package com.aicode.classloaderdemo.chapter01;
import java.net.URL;
import java.net.URLClassLoader;
public class LoadTest {
    public static void main(String[] args) throws
            Exception{
        URL url = new URL("file:C:\\test\\");//jvm需要加载的类存放的位置
//创建一个新的类加载器
        while (true){
//定义一个父加载器
            URLClassLoader classLoader = new
                    URLClassLoader(new URL[]{url});
// 1：这里并不会去执行静态成员的加载，只会做静态成员的存储和划分
            Class clz =
                    classLoader.loadClass("HelloService");
            System.out.println("HelloService 使用的类
                    加载器是：" +clz.getClassLoader());
// 2：通过反射实例化对象,真正的执行在创建对象的时候静态成员会执行和初始化
                    Object newIntance = clz.newInstance();
            Object test =
                    clz.getMethod("test").invoke(newIntance);
            Thread.sleep(3000);
        }
    }
}
```

![image-20201104144036012](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104144036012.png)

## 2.9 类加载器-类的卸载

### 2.9.1 目录

掌握类的卸载

### 2.9.2 分析

卸载类必须满足两个条件：

* 该class所有的实例都已经被GC
* 加载该类的ClassLoader实例已经被GC。
* 在jvm的启动项里增加命令参数： -verbose:class 参数，输出类加载和卸载的日志信息

### 2.9.3 代码

```java 
package com.aicode.classloaderdemo.chapter01;
import java.net.URL;
import java.net.URLClassLoader;
public class LoadTest {
    public static void main(String[] args) throws
            Exception{
        URL url = new URL("file:C:\\test\\");//jvm需要加载的类存放的位置
//创建一个新的类加载器
        URLClassLoader classLoader = new
                URLClassLoader(new URL[]{url});
        while (true){
            if(classLoader==null)break;
// 1：这里并不会去执行静态成员的加载，只会做静态成员的存储和划分
            Class clz =
                    classLoader.loadClass("HelloService");
            System.out.println("HelloService 使用的类加载
                    器是：" +clz.getClassLoader());
// 2：通过反射实例化对象,真正的执行在创建对象的时候静态成员会执行和初始化
                    Object newIntance = clz.newInstance();
            Object test =
                    clz.getMethod("test").invoke(newIntance);
            Thread.sleep(3000);
//GC
            classLoader = null;
            newIntance = null;
        }
        System.gc();
        Thread.sleep(10000);
    }
}
```

* 增加启动运行的参数 -verbose:class

![image-20201104144426916](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104144426916.png)

* 查看日志如下：

```
[Unloading class HelloService 0x00000007c0061028]
[Loaded java.lang.Shutdown from C:\Program Files\Java\jdk1.8.0_211\jre\lib\rt.jar]
[Loaded java.lang.Shutdown$Lock from C:\Program Files\Java\jdk1.8.0_211\jre\lib\rt.jar]
```

### 2.9.4 小结

* 静态代码块执行，并不会在类加载器加载的时候执行，而是在创建第一次实例对象的时候才会去执行。
* 并且gc并不需要我们自己去控制和调用，jvm会自动维护一个垃圾回收的机制。

## 2.10 类加载器-双亲委派模型

### 2.10.1 目标

掌握和了解类加载器的双亲委派模型

### 2.10.2 基本概念

​	如果一个类加载器收到了加载类的请求，它首先将请求交由父类加载器加载；若父类加载器加载失败，当前类加载器才会自己加载类。

![image-20201104144751385](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104144751385.png)

### 2.10.3 作用

* 像java.lang.Object这些存放在rt.jar中的类，无论使用哪个类加载器加载，最终都会委派给最顶端的启动类加载器加载，从而使得不同加载器加载的Object类都是同一个。
* 为了避免重复加载，由下到上逐级委托，由上到下逐级查找
* 首先不会自己去尝试加载类，而是把这个请求委派给父加载器去完成，每一次层级的加载器都是如此，因此所有的类加载器请求都会传给上层的启动类加载器。
* 只有当父加载器反馈自己无法完成该加载请求时，子加载器才会尝试自己去加载。

也称之为： **败家子模型**

**双亲委派模型的代码在java.lang.ClassLoader类中的loadClass函数中实现：**

```java
package com.aicode.classloaderdemo.chapter01;
import java.net.URL;
import java.net.URLClassLoader;
public class LoadTest {
    public static void main(String[] args) throws
            Exception{
        URL url = new URL("file:C:\\test\\");//jvm需要加载的类存放的位置
//创建一个新的类加载器
        URLClassLoader parentLoader = new
                URLClassLoader(new URL[]{url});
        while (true){
//创建一个新的类加载器
            URLClassLoader classLoader = new
                    URLClassLoader(new URL[]{url},parentLoader);
// 1：这里并不会去执行静态成员的加载，只会做静态成员的存储和划分
            Class clz =
                    classLoader.loadClass("HelloService");
            System.out.println("HelloService 使用的类加载
                    器是：" +clz.getClassLoader());
// 2：通过反射实例化对象,真正的执行在创建对象的时候静态成员会执行和初始化
                    Object newIntance = clz.newInstance();
            Object test =
                    clz.getMethod("test").invoke(newIntance);
            Thread.sleep(3000);
//GC
            classLoader = null;
            newIntance = null;
        }
    }
}
```

## 2.10.4 小结

* 这个时候可以清晰看到，如果去修改了HelloService的信息，并不会重新加载信息。

![image-20201104145553106](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104145553106.png)

* 其实这样设计的目的和含义就是：去收集父加载的核心信息，把核心的一些jar和类信息全部加载到jvm中。直接全部加载完毕为止以后，然后在查找对应的自己的加载器去执行你的程序。
* 目的是：类加载器之间不存在父类子类的关系，“双亲” 只是一种翻译，而用逻辑逻辑上的上下级关系，责任划分的关系。也是为了安全性去考虑。比如核心类库中的String.class ，如果去修改的话是有风险的。
* 如果我们不指定parentLoader 默认也会去加载AppClassLoader加载器。

# 三、java自动内存管理机制

## 3.1 自动垃圾收集

自动垃圾收集：是查看堆内存，识别正在使用那些对象以及那些对象未被删除以及删除未使用对象的过程。

* 使用中的对象或引用的对象意味着：程序的某些部分仍然维护指向该对象的指针。
* 程序的任何部分都不再引用未使用的对象或未引用的对象，因此可以回收未引用对象使用的内存

像C这样的编程语言中，分配和释放内存是一个手动的过程，在java中，解除分配内存的过程是由垃圾收集器自动处理。

## 3.2 如何确定内存需要被回收 -- 标记

该过程的第一步成为：标记。这是垃圾收集器识别哪些内存正在使用而哪些不在使用的地方。

![image-20201104152451616](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104152451616.png)

比喻：就好比搞卫生一样，垃圾收集器就好比清洁阿姨 ，她在搞卫生的时候会去标记哪些地方比较脏就会去清理。垃圾收集器也是一样的原理。这种性能会较差而且会造成连续的内存空间浪费，所以在一些商业的虚拟机里已经不在使用了。

### 3.2.1 不同类型判断内存的方式：

* 对象回收 -- 引用计数器 。java默认情况下没有采用引起计数器的方式，因为会存在循环引入的问题。

* 对象回收 --- 可达性分析简单来说，将对象及其引用关系看做一个图，选定活动的对象作为GC Roots ;

然后跟踪引用链条，如果一个对象和GC Roots之间不可达，也就是不存在引用，那么即可认定为可回收对象。什么样子的对象可以作为GcRoot对象：

![image-20201104152846231](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104152846231.png)

![image-20201104152919738](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104152919738.png)

整个执行的过程如下：

![image-20201104153011315](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104153011315.png)

### 3.2.2 GC Root的对象

* 虚拟机栈中正在引用的对象
* 本地方法栈中正在引用的对象
* 静态属性应用的对象
* 方法区常量引用的对象

你可以理解成为：一个方法执行的时候，会开启一个线程去执行该方法。这个时候就可以当做一个GC Root, 它会自动去收集该方法中所有的对象的引用关系，变成一个树结构，当执行完毕一会就自动删除GC Root.先所有的对象会自动全部释放。

## 3.3 垃圾收集器与内存分配策略

### 3.3.1 目标

掌握和了解GC的引用类型

### 3.3.2 概述

​	说起垃圾收集（Garbage Clollection , GC）,大家肯定都不陌生，目前内存的动态分配与内存回收技术已经非常成熟，那么我们为什么还要去了解GC和内存分配呢?原因很简单：当需要排查各种内存溢出、内存泄漏问题时，当垃圾收集成为系统达到更高并发量的瓶颈时。 我们就需要对这些自动化的技术实施必要的监控和条件。

​	在我们的java运行时内存当中，程序计数器、Java虚拟机栈、本地方法栈 3个区域都是随线程生而生，随线程灭而灭，因此这个区域的内存分配和回收都具备了确定性，所以在这几个区域不需要太多的考虑垃圾回收问题，因为方法结束了，内存自然就回收了。但Java堆不一样，它是所有线程共享的区域，我们只有在程序处于运行期间时才能知道会创建哪些对象，这个区域的内存分配和内存回收都是动态的，所以垃圾收集器主要关注的就是这部分的内存。

关于回收的知识点，我们会从以下几方面去讲解：
* 什么样的对象需要回收
* 垃圾收集的算法（如何回收）
* 垃圾收集器（谁来回收）
* 内存分配与回收策略（回收细节）

### 3.3.3 对象已死吗

​	在Java堆中存放着Java世界中几乎所有的对象实例，垃圾收集器在对堆进行回收前，第一件事情就是要确定这些对象之中哪些还存活着，哪些已经死去（即不可能在被任何途径使用的对象）。

如何判断对象是否死亡，主要有两种算法： **引用计数法**和**可达性分析算法**

**主流的商业虚拟机基本使用的是 可达性分析算法**

### 3.3.4 分析

​	无论是通过引用计数算法判断对象的引用数量，还是通过可达性分析判断对象的引用链是否可达，判断对象的存货都与引用有关，在JDK1.2之后，java对引用进行了细分，用于描述一些特殊的对象，如： 当内存空间还足够时，就保留在内存之中，如果内存空间在进行垃圾收集后还是很紧张则抛弃这些对象，所以java又对引用进行了一系列的划分： **强引用、软引用、弱引用、虚引用**

### 3.3.5 引用类型

* 强引用（StrongRefercence）:最常见的普通对象引用，只要还有强引用指向一个对象，就不会回收。就比如你 new了一个对象。

```Java
Java中默认声明的就是强引用，比如：
Object obj = new Object(); //只要obj还指向Object对象，
Object对象就不会被回收
obj = null; //手动置null
只要强引用存在，垃圾回收器将永远不会回收被引用的对象，哪怕内存不
足时，JVM也会直接抛出OutOfMemoryError，不会去回收。如果想中
断强引用与对象之间的联系，可以显示的将强引用赋值为null，这样一
来，JVM就可以适时的回收对象了
```

* 软引用（SoftRefercence） JVM认为内存不足时，才会去试图回收软引用执行的对象。（缓存常见）软引用是用来描述一些非必需但仍有用的对象。在内存足够的时候，软引用对象不会被回收，只有在内存不足时，系统则会回收软引用对象，如果回收了软引用对象之后仍然没有足够的内存，才会抛出内存溢出异常。这种特性常常被用来实现缓存技术，比如网页缓存，图片缓存等。

```Java
public class TestOOM {
    private static List<Object> list = new
            ArrayList<>();
    public static void main(String[] args) {
        testSoftReference();
    }
    private static void testSoftReference() {
        for (int i = 0; i < 10; i++) {
            byte[] buff = new byte[1024 * 1024];
            SoftReference<byte[]> sr = new
                    SoftReference<>(buff);
            list.add(sr);
        }
        System.gc(); //主动通知垃圾回收
        for(int i=0; i < list.size(); i++){
            Object obj = ((SoftReference)
                    list.get(i)).get();
            System.out.println(obj);
        }
    }
}
```

* 弱引用（WeakRefercence）虽然是引用，但随时可能被回收掉。弱引用的引用强度比软引用要更弱一些，无论内存是否足够，只要 JVM 开始进行垃圾回收那些被弱引用关联的对象都会被回收。在 JDK1.2 之后，用 java.lang.ref.WeakReference 来表示弱引用。我们以与软引用同样的方式来测试一下弱引用：

```Java
private static void testWeakReference() {
    for (int i = 0; i < 10; i++) {
        byte[] buff = new byte[1024 * 1024];
        WeakReference<byte[]> sr = new
                WeakReference<>(buff);
        list.add(sr);
    }
    System.gc(); //主动通知垃圾回收
    for(int i=0; i < list.size(); i++){
        Object obj = ((WeakReference)
                list.get(i)).get();
        System.out.println(obj);
    }
}
```

* 虚引用（PhantomRefercence）不能通过它方为对象，供了对象被finalize以后，执行指定逻辑的机制(Cleaner)。虚引用是最弱的一种引用关系，如果一个对象仅持有虚引用，那么它就和没有任何引用一样，它随时可能会被回收，在 JDK1.2 之后，用 PhantomReference 类来表示，通过查看这个类的源码，发现它只有一个构造函数和一个 get() 方法，而且它的 get() 方法仅仅是返回一个null，也就是说将永远无法通过虚引用来获取对象，虚引用必须要和ReferenceQueue 引用队列一起使用。

### 3.3.6 可达性分析算法和级别

* 强可达 ：一个对象可以有一个或多个线程可以不通过各种引用访问的情况。
* 软可达：就是当我妈只能通过软引用才能方为到对象的状态。
* 弱可达：只能通过弱引用访问时的状态，当弱引用被清除的时候，就复合销毁条件
* 幻象可达：不存在其他引用，并且finalize过了，只有幻想引用指向这个对象。
* 不可达：意味着对象可以被清除了。

​	基本思路：通过系列的称为 GC Roots 的对象作为起始点，从这些节点开始向下搜索，搜索走过的路径成为引用连，当一个对象到GC Roots没有任何引用链相连时，则证明此对象是不可达的，会被判断为可回收的对象。

​	如图: 对象5,6,7 虽然互相有关联，但是他们到GC Roots是不可达的，所以它们会被判定为可回收的对象。

![image-20201104155923190](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104155923190.png)

## 3.4 垃圾收集算法

### 3.4.1 标记-清除算法

​	标记—清除算法是最基础的收集算法，过程分为标记和清除两个阶段，首先标记出需要回收的对象，之后由虚拟机统一回收已标记的对象。这种算
法的主要不足有两个：

* 效率问题，标记和清除的效率都不高；
* 空间问题，对象被回收之后会产生大量不连续的内存碎片，当需要分配较大对象时，由于找不到合适的空闲内存而不得不再次触发垃圾回收动作。

![image-20201104160147312](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104160147312.png)

​	用标记清除的问题就是：清除以后的内存空间是不连续的。如果要存储大新的对象的时候，找不到合适的内存空间，而再次启发垃圾回收扫描。

### 3.4.2 复制算法

​	为了解决效率问题，复制算法出现了。算法的基本思路是：

* 将内存划分为大小相等的两部分，每次只使用其中一半，当第一块内存用完了，就把存活的对象复制到另一块内存上，
* 然后清除剩余可回收的对象，这样就解决了内存碎片问题。我们只需要移动堆顶指针，按顺序分配内存即可，简单高效。但是算法的缺点也很明显：
  * 它浪费了一半的内存，这太要命了。
  * 如果对象的存活率很高，我们可以极端一点，假设是100%存活，那么我们需要将所有对象都复制一遍，并将所有引用地址重置一遍。复制这一工作所花费的时间，在对象存活率达到一定程度时，将会变的不可忽视。

![image-20201104160505133](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104160505133.png)

#### 3.4.2.1 应用场景分析：

​	这种收集算法经常被采用到新生代，因为新生代中的对象 绝大部分都是 **朝生夕死**。

#### 3.4.2.2 步骤和过程

HotSpot默认的空间比例是 8:1

​	所以并不需要按照1：1的比例来划分内存空间，而是将内存分为一块较大的Eden空间和两块较小的Survivor空间，每次使用Eden和其中一块Survivor。当回收时，将Eden和Survivor中还存活着的对象一次性的复制到另外一块Survivor空间上，最后清理Eden和刚才用过的Survivor空间。
如图：

![image-20201104160944559](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104160944559.png)

### 3.4.3 标记-整理算法

根据老年代的特点，有人提出了另一种改进后的“标记—清除”算法：标记—整理算法。

* 标记：它的第一个阶段与标记/清除算法是一模一样的，均是遍历GC Roots，然后将存活的对象标记。
* 整理：移动所有存活的对象，且按照内存地址次序依次排列，然后将末端内存地址以后的内存全部回收。因此，第二阶段才称为整理阶段。

![image-20201104161323651](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104161323651.png)



​	可以看到，标记的存活对象将会被整理，按照内存地址依次排列，而未被标记的内存会被清理掉。如此一来，当我们需要给新对象分配内存时，JVM只需要持有一个内存的起始地址即可，这比维护一个空闲列表显然少了许多开销。不难看出，标记/整理算法不仅可以弥补标记/清除算法当中，内存区域分散的缺点，也消除复制算法当中，内存减半的高额代价，可谓是一举两得。

### 3.4.4 分代收集算法

​	根据对象的存活周期，将内存划分为几个区域，不同区域采用合适的垃圾收集算法。

​	新对象会分配到Eden，如果超过-XX:+PretenureSizeThreshold：设置大对象直接进入老年代的阈值。

​	现代商业虚拟机垃圾收集大多采用分代收集算法。主要思路是根据对象存活生命周期的不同将内存划分为几块。一般是把Java堆分为新生代和老年代，然后根据各个年代的特点采用最合适的收集算法。

* 新生代中，对象的存活率比较低，所以选用复制算法，
* 老年代中对象存活率高且没有额外空间对它进行分配担保，所以使用“标记-清除”或“标记-整理”算法进行回收。

![image-20201104163038245](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104163038245.png)

* Eden代表是：新生代
* s0代表：新手代-s0
* s1代表：新手代-s1
* old Memory：老年代
* s0:s1:Eden：它们之间的比例是：1:1:8
* 新生代:老年代的比例是：1:2

解说

初始状态

![image-20201104164138155](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104164138155.png)

* 默认情况下，我们的创建的对象是在Eden区去存放。如果这个时候内存空间不足，jvm会开始进行标记哪些对象可以被回收，那么对象不被回收，就会把不需要被回收的对象从eden区移动到s0或者s1中，当然也可能是老年代中区。(**分配担保： 我们没办法保证每次回收都只有不多于10%的对象存活，当Survivor空间不够时，需要依赖其他内存（这里指老年代）进行分配担保**)

采用的算法是：**复制算法**。并且累加1

![image-20201104164423275](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104164423275.png)

这个时候就会把不可以使用的对象进行回收即可。

* 随着程序的运行，又会去生成一些新的对象和新的垃圾。这个时候新生代-s0可能内存空间也会存在需要回收的垃圾，也会出现存满的情况，也会启动垃圾回收机制进行回收。

![image-20201104164623445](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104164623445.png)

* 老年代的存活对象，并且做内存**标记清理和标记整理**算法
  * 如果一个对象一直存活，并且移动的累加次数大于某个阈值的时候，就会进入到老年代。因为在对象的移动过程中，新生代的s1也会存满，它接下来就会把存活的对象复制到老年代中去。
  * 或者是新生代内存不够的时候也会直接复制到老年代去。
  * 或者一个大对象创建的时候也会直接进入到老年代

![image-20201104164940948](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104164940948.png)

## 3.5 垃圾收集器

如果说收集算法是内存回收的方法论，那么垃圾收集器就是内存回收的具体实现。下图是HotSpot虚拟机所包含的所有垃圾收集器：

![image-20201104165124218](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104165124218.png)

​	从JDK3(1.3)开始，HotSpot团队一直努力朝着高效收集、减少停顿(STW:Stop The World)的方向努力，也贡献了从串行到CMS乃至最新的G1在内的一系列优秀的垃圾收集器。上图展示了JDK的垃圾回收大家庭，以及相互之间的组合关系。

​	STW:Stop The World 是指由于虚拟机在后台发起垃圾收集时，会暂停所有其他的用户工作线程，造成用户应用暂时性停止。从JDK1.3开始，HotSpot虚拟机开发团队一直为消除或者减少工作线程因为内存回收而导致停顿而努力着。用户线程的停顿时间不短缩短，但仍无法完全消除。

下面就几种典型的组合应用进行简单的介绍：

### 3.5.1 串行收集器

![image-20201104165407171](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104165407171.png)



**串行收集器组合 Serial + Serial Old**

​	串行收集器是最基本、发展时间最长、久经考验的垃圾收集器，也是client模式下的默认收集器配置。

​	串行收集器采用单线程stop-the-world的方式进行收集。当内存不足时，串行GC设置停顿标识，待所有线程都进入安全点(Safepoint)时，应用线程暂停，串行GC开始工作，采用单线程方式回收空间并整理内存。单线程也意味着复杂度更低、占用内存更少，但同时也意味着不能有效利用多核优势。事实上，串行收集器特别适合堆内存不高、单核甚至双核CPU的场合。

​	开启选项：-XX:+UseSerialGC

​	就好比以前的一个电动车一样，充电中就不能使用。充电完成才可以使用。现在的电脑都是属于多核的CPU。这个时候串行的收集就有点不适用了。

### 3.5.2 并行收集器

![image-20201104170136441](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104170136441.png)

**并行收集器组合 Parallel Scavenge + Parallel Old**

​	并行收集器是以关注吞吐量为目标的垃圾收集器，也是server模式下的默认收集器配置，对吞吐量的关注主要体现在年轻代Parallel Scavenge收集器上。

​	并行收集器与串行收集器工作模式相似，都是stop-the-world方式，只是暂停时并行地进行垃圾收集。**年轻代采用复制算法，老年代采用标记-整理**，在回收的同时还会对内存进行压缩。关注吞吐量主要指年轻代的ParallelScavenge收集器，通过两个目标参数-XX:MaxGCPauseMills和-XX:GCTimeRatio，调整新生代空间大小，来降低GC触发的频率。并行收集器适合对吞吐量要求远远高于延迟要求的场景，并且在满足最差延时的情况下，并行收集器将提供最佳的吞吐量。

开启选项：**-XX:+UseParallelGC或-XX:+UseParallelOldGC(可互相激活)**

### 3.5.3 并发清除收集器

​	并发标记清除(CMS)是以关注延迟为目标、十分优秀的垃圾回收算法，开启后，**年轻代使用STW式的并行收集，老年代回收采用CMS进行垃圾回收**，对延迟的关注也主要体现在老年代CMS上。

​	年轻代ParNew与并行收集器类似，而老年代CMS每个收集周期都要经历：初始标记、并发标记、重新标记、并发清除。其中，初始标记以STW的方式标记所有的根对象；并发标记则同应用线程一起并行，标记出根对象的可达路径；在进行垃圾回收前，CMS再以一个STW进行重新标记，标记那些由mutator线程(指引起数据变化的线程，即应用线程)修改而可能错过的可达对象；最后得到的不可达对象将在并发清除阶段进行回收。值得注意的是，初始标记和重新标记都已优化为多线程执行。CMS非常适合堆内存大、CPU核数多的服务器端应用，也是G1出现之前大型应用的首选收集器。

​	**专为老年代设计的收集算法，基于一种：标记-清除（Mark-Sweep）算法，设计目标就是进来减少停顿的时间。采用的标记清除算法，存在着内存碎片化的问题，长时间运行等情况下发送full gc，导致恶劣的停顿。CMS会占用更多的CPU资源，并和用户线程争抢。为了减少停顿时间，这一点对于互联网web等对时间敏感的系统非常重要，一直到尽头，仍然有很多系统使用CMSGC。**

![image-20201104171404269](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104171404269.png)

**并发标记清除收集器组合 ParNew + CMS + Serial Old**

**但是CMS并不完美，它有以下缺点：**

​	由于并发进行，CMS在收集与应用线程会同时会增加对堆内存的占用，也就是说，CMS必须要在老年代堆内存用尽之前完成垃圾回收，否则CMS回收失败时，将触发担保机制，串行老年代收集器将会以STW的方式进行一次GC，从而造成较大停顿时间；

​	标记清除算法无法整理空间碎片，老年代空间会随着应用时长被逐步耗尽，最后将不得不通过担保机制对堆内存进行压缩。CMS也提供了参数

-XX:CMSFullGCsBeForeCompaction(默认0，即每次都进行内存整理)来指定多少次CMS收集之后，进行一次压缩的Full GC。

​	开启选项：-XX:+UseConcMarkSweepGC

### 3.5.4 Garbage First (G1)

​	G1(Garbage First)垃圾收集器是当今垃圾回收技术最前沿的成果之一。早在JDK7就已加入JVM的收集器大家庭中，成为HotSpot重点发展的垃圾回收技术。同优秀的CMS垃圾回收器一样，G1也是关注最小时延的垃圾回收器，也同样适合大尺寸堆内存的垃圾收集，官方也推荐使用G1来代替选择CMS。G1最大的特点是引入分区的思路，弱化了分代的概念，合理利用垃圾收集各个周期的资源，解决了其他收集器甚至CMS的众多缺陷。

![image-20201104172004161](E:\学习笔记\mylearnnote\javaSE\JVM\images\image-20201104172004161.png)

