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

