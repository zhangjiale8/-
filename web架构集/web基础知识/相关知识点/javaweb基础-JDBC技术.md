![](E:\学习笔记\web相关\web基础知识\image\JDBC技术Xmind.png)

# 一、概述:

## 1.1 定义

​	各个数据库厂商会遵循SUN的规范提供一套访问自己公司的数据库服务器的API出现。SUN提供的规范命名为JDBC，而各个厂商提供的，遵循了JDBC规范的，可以访问自己数据库的API被称之为驱动！

​	**JDBC是接口，而JDBC驱动才是接口的实现**，没有驱动无法完成数据库连接！每个数据库厂商都有自己的驱动，用来连接自己公司的数据库。

## 1.2 作用:

为多种关系数据库提供统一访问.

* **扩展:早期SUN公司提供的一套访问数据库的规范和协议标准.**

## 1.3 注意:

* 但是不同数据库提供不同的JDBC包.

* 不同数据库的JDBC包到对应数据库官网查找.

 

# 二、如何使用JDBC:

## 2.1  导入对应数据库的驱动包.mysql-connector-java-5.1.33-bin.jar

## 2.2 实现操作MySQL数据库的步骤:

（1）编写连接MySQL的四大参数.

（2）加载MySQL的驱动类.

（3）获取MySQL数据库的连接对象

（4）向MySQL数据库发送SQL语句.

（5）关闭MySQL数据库的相关连接.

 ![](E:\学习笔记\web相关\web基础知识\image\实现操作MySQL数据库的步骤.png) 

# 三、JDBC的核心类或对象:

## 3.1 DriverManager类:

​	**DriverManager类主要用于管理一组JDBC驱动程序的基本服务**，它提供了连接到数据库的一种方法。通过Class类的forName("com.mysql.jdbc.Driver")方法来加载数据库驱动程序，通过getConnection()方法获取连接数据库实例对象。

### 3.1.1作用:

​	管理一组 JDBC 驱动程序的基本服务.

### 3.1.2 常用方法:

* **registerDriver()方法与Class.forName()方法作用一致.**

### 3.1.3 问题:

#### 3.1.3.1 为什么使用Class.forName()方法?

 * 查看Driver类的源代码:

 java.sql.DriverManager.registerDriver(new Driver());

* 利用registerDriver()方法与底层代码冲突.

![](E:\学习笔记\web相关\web基础知识\image\利用registerDriver()方法与底层代码冲突.png)

#### 3.1.3.2 利用Class.forName()方法是否可以忽略? 

​	可以

  * **MySQL提供的驱动包底层自动加载驱动类**.

 * 注意:当前版本提供机制,其他版本不一定.

 * **建议:手动加载MySQL的驱动类**.

### 3.1.4 常见方法

* getConnection(String url)方法:获取数据库的连接对象. 

## 3.2  Connection类

### 3.2.1 作用:

​	用于连接MySQL数据库.

 ### 3.2.2 常用方法:

* createStatement():获取Statement对象.

* close():关闭连接.

## 3.3 Statement类

### 3.3.1 作用:

​	**用于向MySQL数据库发送SQL语句**.

### 3.3.2 常用方法:

* execute()方法:用于向MySQL数据库发送SQL语句.

* executeQuery()方法:执行查询语句.

* executeUpdate()方法:执行增删改语句.

* close()方法:关闭Statement.

* executeBatch()方法:批处理. 

## 3.4 ResultSet类:

### 3.4.1 概述:

* **将查询数据库表得到的结果,封装在一个具有行和列的表格中**.

* **结果集具有一个光标,默认指向第一行数据的上一行**.

### 3.4.2 常用方法: 

#### 3.4.2.1 移动光标方法:

* next()

     * first()

     * last()

     * previous()

     * relative(int rows)

     * absolute(int row)

 #### 3.4.2.2 获取字段值的方法:

* getXXX(int i):传递对应角标获取对应的字段值.(XXX表示类型)

* getXXX(String name):传递对应字段名获取对应的字段值.(XXX表示类型)

# 四、自定义JDBCUtils

![](E:\学习笔记\web相关\web基础知识\image\自定义JDBCUtils.png)




原文链接：https://blog.csdn.net/jinfulin/article/details/44875641