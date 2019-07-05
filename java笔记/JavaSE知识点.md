# 1.java 概述

```
1991 年Sun公司的James Gosling等人开始开发名称为 Oak 的语言，希望用于控制嵌入在有线电视交换盒、PDA等的微处理器；
1994年将Oak语言更名为Java；
```

# 2.Java的三种技术架构（3个分支）

```
JAVAEE：Java Platform Enterprise Edition，开发企业环境下的应用程序，主要针对web程序开发；
JAVASE：Java Platform Standard Edition，完成桌面应用程序的开发，是其它两者的基础；
JAVAME：Java Platform Micro Edition，开发电子消费产品和嵌入式设备，如手机中的程序；
```

# 3. Java结构

```
JDK：Java Development Kit，java的开发和运行环境，java的开发工具和jre。
JRE：Java Runtime Environment，java程序的运行环境，java运行的所需的类库+JVM(java虚拟机)。
```

# 4.Java环境变量配置

```
让java jdk\bin目录下的工具，可以在任意目录下运行，原因是，将该工具所在目录告诉了系统，当使用该工具时，由系统帮我们去找指定的目录。
```

## 4.1 环境变量的配置

### 4.1.1 永久配置方式（系统变量）

JAVA_HOME=%安装路径%\Java\jdk  

path=%JAVA_HOME%\bin

### 4.1.2 临时配置方式（用户变量）

set path=%path%;C:\Program Files\Java\jdk\bin

```
特点：系统默认先去当前路径下找要执行的程序，如果没有，再去path中设置的路径下找。
```

## 4.2 classpath的配置

### 4.2.1 永久配置方式（系统变量）

classpath=.;c:\;e:\

### 4.2.2 临时配置方式（用户变量）

set classpath=.;c:\;e:\

```
注意：
在定义classpath环境变量时，需要注意的情况

如果没有定义环境变量classpath，java启动jvm后，会在当前目录下查找要运行的类文件；
如果指定了classpath，那么会在指定的目录下查找要运行的类文件。

还会在当前目录找吗？两种情况：

1）：如果classpath的值结尾处有分号，在具体路径中没有找到运行的类，会默认在当前目录再找一次。
2）：如果classpath的值结果出没有分号，在具体的路径中没有找到运行的类，不会再当前目录找。

一般不指定分号，如果没有在指定目录下找不到要运行的类文件，就报错，这样可以调试程序
```

# 5.javac命令和java命令

java分两部分：一个是编译，一个是运行

## 5.1 javac命令

```
负责的是编译的部分，当执行javac时，会启动java的编译器程序。对指定扩展名的.java文件进行编译。 生成了jvm可以识别的字节码文件。也就是class文件，也就是java的运行程序。
```

## 5.2 java命令

```
负责运行的部分.会启动jvm.加载运行时所需的类库,并对class文件进行执行.
```

```
注意： 一个文件要被执行,必须要有一个执行的起始点,这个起始点就是main函数.
```

# 6.关键字与标识符

## 6.1 关键字

其实就是某种语言赋予了特殊含义的单词

```java
abstract, assert,
boolean, break, byte,
case, catch, char, class, const, continue,
default, do, double,
else, enum, extends,
final, finally, float, for,
goto,
if, implements, import, instanceof, int, interface,
long,
native, new,
package, private, protected, public,
return,
short, static, strictfp, super, switch, synchronized,
this, throw, throws, transient, try,
void, volatile,
while
```

```
其中保留关键字为：goto, const
Java1.2添加的关键字：strictfp
Java1.4添加的关键字：assert
Java5.0添加的关键字：enum
```

## 6.2 Java保留字

```java
byValue,
cast, const,
false, future,
generic, goto
inner,
null，
operator, outer,
rest,
true,
var
```

## 6.3 标示符

在程序中自定义的名词。比如类名，变量名，函数名。包含 0-9、a-z、$、_ ；

```
注意：
1），数字不可以开头。
2），不可以使用关键字。
```

## 6.4 常量与变量

### 6.4.1 常量

在程序中的不会变化的数据。

### 6.4.2 变量

内存中的一个存储空间，用于存储常量数据。

方便于运算。因为有些数据不确定。所以确定该数据的名词和存储空间。

```
特点：变量空间可以重复使用。
什么时候定义变量？
只要是数据不确定的时候，就定义变量。
```

#### 6.4.2.1 变量空间的开辟需要什么要素呢？

```
1.这个空间要存储什么数据？数据类型。
2.这个空间叫什么名字啊？变量名称。
3.这个空间的第一次的数据是什么？ 变量的初始化值
```

#### 6.4.2.2 变量的作用域和生存期

```
变量的作用域：
    作用域从变量定义的位置开始，到该变量所在的那对大括号结束；
生命周期：
    变量从定义的位置开始就在内存中活了；
    变量到达它所在的作用域的时候就在内存中消失了；
```

# 7.数据类型

## 7.1 基本数据类型

```java
byte、short、int、long、float、double、char、boolean
```

# 7.2 引用数据类型

数组、类、接口

```
级别从低到高：byte,char,short(这三个平级)-->int-->float-->long-->double
自动类型转换：从低级别到高级别，系统自动转的；
强制类型转换：什么情况下使用?把一个高级别的数赋给一个别该数的级别低的变量；
```

# 8.运算符

## 8.1 算术运算符

```
+ - * / % ++,--
```

```
注：
%:任何整数模2不是0就是1，所以只要改变被模数就可以实现开关运算。
+:连接符。
```

## 8.2 赋值运算符

```
=  += -= *= /= %=
```

## 8.3 比较运算符

```
> 、 < 、 >= 、 <= 、== 、 !=
```

```
注意：
> 、 < 、 >= 、 <= 只支持左右两边操作数是数值类型
== 、 != 两边的操作数既可以是数值类型，也可以是引用类型
```

```
特点：该运算符的特点是：运算完的结果，要么是true，要么是false。
```

## 8.4 逻辑运算符

```
&  |  ^  !   &&   ||
```

```
注意：
逻辑运算符除了 !  外都是用于连接两个boolean类型表达式。
&: 只有两边都为true结果是true。否则就是false。
|:只要两边都为false结果是false，否则就是true
^:异或和或有点不一样。 两边结果一样，就为false。两边结果不一样，就为true.
& 和 &&区别：
& ：无论左边结果是什么，右边都参与运算。
&&:短路与，如果左边为false，那么右边不参数与运算。
| 和|| 区别：
|：两边都运算。
||：短路或，如果左边为true，那么右边不参与运算。
```

## 8.5 条件运算符（三元运算符）

```
 ? :
语法形式：布尔表达式 ？ 表达式1 ：表达式2
运算过程：如果布尔表达式的值为 true ，则返回 表达式1 的值，否则返回 表达式2 的值
```

## 8.6 位运算符

```
&  |  ^
<<  >>   >>>(无符号右移)
```

```java
练习1：对两个变量的数据进行互换。不需要第三方变量。
int a  = 3,b = 5;-->b = 3,a = 5;
a = a + b; a = 8;
b = a - b; b = 3;
a = a - b; a = 5;
a = a ^ b;//
b = a ^ b;//b = a ^ b ^ b = a
a = a ^ b;//a = a ^ b ^ a = b;

练习2：高效的算出 2*8
2*8 = 2<<3;
```

# 9.条件与循环语句

