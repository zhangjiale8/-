![DBUtils工具包Xmind](E:\学习笔记\web相关\web基础知识\image\DBUtils工具包Xmind.png)

# 一、概述:

## 1.1 定义:

用于封装操作数据库的增删改查.

## 1.2 特点:

（1）对于数据表的读操作,他可以把结果转换成List、Array、Set等java集合,便于程序员操作.

（2）对于数据表的写操作,也变得很简单(只需写sql语句).

（3）可以使用数据源,使用JNDI,数据库连接池等技术来优化性能.

# 二、常用类:

## 2.1 QueryRunner类:

### 2.1.1  构造函数:

* QueryRunner():默认无参构造.

* QueryRunner(DataSource ds):传递连接池的构造.

### 2.1.2  常用方法:

* query()方法:用于执行查询操作.

* query(Connection conn, String sql, ResultSetHandler<T> rsh, Object... params)

* query(String sql, ResultSetHandler<T> rsh, Object... params)

* update()方法:用于执行增删改操作.

* update(Connection conn, String sql, Object... params)

     * update(String sql, Object... params)

## 2.2 ResultSetHandler接口:

 handle(ResultSet rs)方法:

用于将ResultSet结果集类型进行转换.



# 三 、两种方式管理事务:

## 3.1 手动管理事务:

* QueryRunner()

* query(Connection conn, String sql, ResultSetHandler<T> rsh, Object... params)

* update(Connection conn, String sql, Object... params)

## 3.2 工具管理事务:

* QueryRunner(DataSource ds)

* query(String sql, ResultSetHandler<T> rsh, Object... params)

* update(String sql, Object... params)

# 四、ResultSethandler:

​	通过上述查询语句可以发现，每次去实现ResultSetHandler的方法非常麻烦。其实ResultSetHandler接口提供了九个实现类供使用，分别如下：

## 4.1 ArrayHandler:

**把结果集中的第一行数据转成对象数组.**

![](E:\学习笔记\web相关\web基础知识\image\ArrayHandler01.png)

## 4.2  ArrayListHandler:

**把结果集中的每一行数据都转成一个对象数组,再存放到List中**.

![](E:\学习笔记\web相关\web基础知识\image\ArrayListHandler01.png)

## 4.3 BeanHandler:

**将结果集中的第一行数据封装到一个对应的JavaBean实例中.**

![](E:\学习笔记\web相关\web基础知识\image\BeanHandler01.png)

## 4.4 BeanListHandler:

**将结果集中的每一行数据都封装到一个对应的JavaBean实例中,存放到List里.**

![](E:\学习笔记\web相关\web基础知识\image\BeanListHandler01.png)

## 4.5 MapHandler:

**将结果集中的第一行数据封装到一个Map里,key是列名,value就是对应的值.**

![](E:\学习笔记\web相关\web基础知识\image\MapHandler01.png)

## 4.6 MapListHandler:

**将结果集中的每一行数据都封装到一个Map里,然后再存放到List.**

![](E:\学习笔记\web相关\web基础知识\image\MapListHandler01.png)

## 4.7 ColumnListHandler:

**将结果集中某一列的数据存放到List中.**

![](E:\学习笔记\web相关\web基础知识\image\ColumnListHandler01.png)



## 4.8 KeyedHandler:

**将结果集中的每一行数据都封装到一个Map里,再把这些map再存到一个map里,其key为指定的**列.

![](E:\学习笔记\web相关\web基础知识\image\KeyedHandler01.png)

## 4.9 ScalarHandler:

**进行单值查询.** 


原文链接：https://blog.csdn.net/jinfulin/article/details/44875855