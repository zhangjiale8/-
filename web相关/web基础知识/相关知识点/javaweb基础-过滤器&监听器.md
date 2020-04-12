![](E:\学习笔记\web相关\web基础知识\image\过滤器Xmind.png)

# 一、过滤器

## 1.1 作用:

用于过滤请求(Request)与响应(Response)的数据内容.

## 1.2 发展:

* Servlet 2.3版本出现Filter功能.

* Servlet 2.4版本对Filter进行补充.

* 目前主流版本为Servlet 2.5.

* 当前最新版本为Servlet 3.0.

 

# 二、使用Filter:

## 2.1 自定义过滤器,实现Filter接口,并且重写其提供的方法.

![](E:\学习笔记\web相关\web基础知识\image\自定义过滤器01.png)  

## 2.2 对web.xml文件进行相关配置:

![](E:\学习笔记\web相关\web基础知识\image\自定义过滤器02.png) 

## 2.3 注意:

* **使用<filter-name>标签定义的Filter名称是唯一的**. 

* **使用<url-pattern>标签定义映射路径允许配置多个,表示同时过滤多个资源(静态或动态)**.

# 三、生命周期: 

## 3.1构造函数:

* **用于Filter的实例化.**

* **在Filter的生命周期中只能执行一次.**

* 线程安全问题(单例多线程的)

## 3.2 init() 

* **用于Filter的必要初始化工作.**

* **在Filter的生命周期中只能执行一次.** 

## 3.3 doFilter()

* **用于Filter的过滤工作**.

* **在Filter的生命周期中执行多次(每次拦截每次执行).** 

## 3.4 destroy()

* **用于Filter的资源释放工作.**

* **在Filter的生命周期中只能执行一次.**

# 四、 过滤器链: 

## 4.1 什么叫做链:

​	**就是多个过滤器同时过滤同一个资源(静态或动态).**    


* **控制过滤器链中的过滤器谁先执行**:

* **通过web.xml文件中的<filter-mapping>标签出现的先后顺序.**

哪个Filter的<filter-mapping>标签先出现先执行,后出现后执行.

## 4.2 过滤器链执行的顺序:

* **如果不是过滤器链的最后一个过滤器,执行chain.doFilter()方法,是发送到下一个过滤器.**   

* **如果是过滤器链的最后一个过滤器,执行chain.doFilter()方法,是发送到对应Web资源.** 

## 4.3 Filter的映射配置:

### 4.3.1 配置方式:

* **完全匹配**:/servlet/test1

* **目录匹配**:/servlet/

* **扩展名匹配**:*.do

* **优先级由高到低:完全匹配 -> 目录匹配 -> 扩展名匹配**. 

![](E:\学习笔记\web相关\web基础知识\image\Filter的映射配置01.png)

### 4.3.2 过滤Servlet: 

如果需要拦截的是Servlet的话，有两种方式配置拦截路径：

* <url-pattern>Servlet的映射配置</url-pattern>

* <servlet-name>Servlet的名称</servlet-name>

例如:

使用<url-pattern>标签：<url-pattern>/hello</url-pattern>

使用<servlet-name>标签：<servlet-name>HelloServlet</servlet-name>

### 4.3.3 <dispatcher>标签:

**<dispatcher>标签配置到达Servlet的方法，有四种取值：REQUEST、FORWARD、INCLUDE和ERROR**。可以同时配置多个<dispatcher>标签，

**如果没有配置<dispatcher>标签，默认为REQUEST**。这四种取值的区别如下：

#### 4.3.3.1 REQUEST：

​	表示仅当直接请求Servlet时才生效。

#### 4.3.3.2 FORWARD：

​	表示仅当某Servlet通过FORWARD到该Servlet时才生效。

#### 4.3.3.3 INCLUDE：

​	JSP中可以通过<jsp:include>标签请求某Servlet或调用RequestDispatcher的forward()方法请求某Servlet，仅这种情况下有效。

#### 4.3.3.4 ERROR：

​	JSP中可以通过<%@ page errorPage="error.jsp">标签指定错误处理页面，仅这种情况下有效。

**<url-pattern>标签与<dispatcher>标签的关系是"且"的关系。只有满足<url-pattern>标签的条件，且满足<dispatcher>标签的条件时，当前过滤器才能生效。**

* 实际开发常用方式:

* REQUEST

* FORWARD

 

## 4.4 Filter的应用案例:


* 全站乱码问题.

* 自动登录案例.

* 禁用缓存案例.

* 权限管理案例 - 粗粒度权限管理.


原文链接：https://blog.csdn.net/jinfulin/article/details/44876015