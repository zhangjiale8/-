![](\web相关\web基础知识\image\serverlet01.png)

# 一、Servlet概述

  ## 1.1 Servlet是什么？

​    是sun公司提供一套规范，用于**接受客户浏览器发出的请求，响应给客户浏览器。是运行在服务端一个小程序**。

## 1.2 Servlet入门：

Servlet是一个接口，要想实现Servlet功能必须实现该接口或者继承该接口的实现类。

​    已知实现类：GenericServlet

​    Servlet接口中的方法：

​    **init（ServletConfig) 初始化**

​    **service(ServletRequest,ServletResponse) 核心方法**

​    **destroy() 销毁**

# 二、Servlet编码步骤

主要目的：为了了解Servlet从无到有，到能运行访问的一个过程

## 2.1 第一步：编写

编写FirstServlet实现Servlet接口或者继承GenericServlet

![](\web相关\web基础知识\image\serverlet02.png)

## 2.2 第二步：编译    

编译FirstServlet

直接用javac命令编译servlet会有问题，需要设置classpath，加入servlet-api.jar

该jar存在于tomcat/lib/

![](\web相关\web基础知识\image\serverlet03.png)

## 2.3 第三步：配置

配置Servlet，使其生效

​	 配置Servlet，是针对应用而言的，在web.xml中配置

注意：web.xml文件必须另存为UTF-8格式编码的

![](\web相关\web基础知识\image\serverlet04.png)

 ## 2.4 第四步：部署 

​	部署到Tomcat，访问http://localhost:8080/firstservlet/FirstServlet

​	![](\web相关\web基础知识\image\serverlet05.png)

  明确 规范（sun） 服务器（tomcat） 我们的应用之间的关系  

![](\web相关\web基础知识\image\serverlet06.png)      

# 三、Servlet执行过程

​	客户浏览器——Tomcat服务器——应用——应用的配置（web.xml）——Servlet——Servlet执行完成响应客户浏览器


​    ![](\web相关\web基础知识\image\serverlet07.png)

# 四、Servlet编码方式

（1）继承GenericServlet类，是javax.servlet包下的一个抽象类

​	案例：ServletDemo1 了解创建一个Servlet是两步，第一步建类，第二部映射

（2）继承HttpServlet类，是javax.servlet.http包下面的一个抽象类，是GenericServlet的子类。

注意：（重要）我们在继承HttpServlet时，只需要覆盖doxxx的方法，常用就是doGet和doPost，不要覆盖service。

案例：ServletDemo2 继承自HttpServlet的ServletDemo2的查找顺序


![](\web相关\web基础知识\image\Httpserverlet01.png)        

![](\web相关\web基础知识\image\Httpserverlet02.png)

![](\web相关\web基础知识\image\Httpserverlet03.png)

# 五、Servlet生命周期

  出生——活着——死亡，从生到死的一个过程（人有，内存中的对象也有）

  出生：请求到达Servlet时，对象就创建出来，并且初始化成功。只出生一次，就放到内存中。

  活着：服务器提供服务的整个过程中，该对象一直存在，每次只是方法service方法。

  死亡：当服务停止时，或者服务器挂机时，对象消亡。

  **单例模式：只有一个对象实例。Servlet就是单例的，只有一个实例**。

![](\web相关\web基础知识\image\Httpserverlet04.png)

![](\web相关\web基础知识\image\Httpserverlet05.png)

# 六、Servlet线程安全

 Servlet不是线程安全的。      

![](\web相关\web基础知识\image\Httpserverlet06.png)  

注意：在Servlet中尽量避免使用全局变量，但不是绝对。请参看HttpServlet的service(HttpServletRequest,HttpServletRequest)方法。

# 七、Servlet注意事项

## 7.1 映射方式:

​    方式1：**通配符+固定结尾格式 *.do**

​    方式2：**/开头+通配符       /servlet/***

​    方式3：**指名道姓   （最常用）   /servlet/ServletDemo**   

​    方式1和方式2之间是有一定的区别：就是**优先级的问题**。

​    **方式3的优先级最高，其次是以/开头的，最后才是*.do方式**。

  ## 7.2 多路径映射：

​    url-pattern可以映射多个地址


​     ![](\web相关\web基础知识\image\路径配置01.png)       

## 7.3 配置启动服务时，自动创建servlet

load-on-startup元素标记容器

是否在启动的时候就加载这个servlet(实例化并调用其init()方法)。      

使用：<load-on-startup>**启动顺序，必须是正整数，且不能重复**</load-on-startup>来设置服务器启动时创建servlet对象

![](\web相关\web基础知识\image\路径配置02.png)    

## 7.4 默认Servlet

​    **当我们访问的资源，在web.xml中找不到对应的映射时，这个时候会去找默认的Servlet，该Servlet由服务器提供，Tomcat服务器的默认Servlet在**：

  apache-tomcat-7.0.57-src.zip\apache-tomcat-7.0.57-src\java\org\apache\catalina\servlets

  一切都是Servlet。

# 八、Servlet参数配置：ServletConfig

 ## 8.1 ServletConfig 是什么？

​    它是**Servlet的配置参数对象，每个Servlet都一个自己的ServletConfig**

  ## 8.2 ServletConfig 怎么获取？

​    由服务器容器提供，我们直接使用即可。每次覆盖init方法的时候，注意：覆盖的是没有参数的init方法。

  ## 8.3 如何配置ServletConfig参数？

 <init-param>

​      <param-name></param-name>

​      <param-value></param-value>

</inti-param>

​    要写在<servlet>元素内



   ## 8.4 如何使用ServletConfig得到配置好的参数         

![](\web相关\web基础知识\image\ServletConfig01.png)


![](\web相关\web基础知识\image\ServletConfig02.png)        

# 九、ServletContext

 ## 9.1 ServletContext是什么？

​	它是**应用的全局上下文对象，每个应用只有一个ServletContext对象**。

​	每个应用都可以有多个Servlet，多个Servlet之间的通信就是通过ServletContext对象获取。

 ## 9.2 如何获取ServletContext？

![](\web相关\web基础知识\image\ServletContext01.png)             

 ## 9.3 ServletContext 生命周期

​    出生——活着——死亡

​    出生： **应用一加载，该对象就被创建出来了**。**只有一个实例对象**。

​       **(Servlet和ServletContext都是单例的)**

​    活着：只要应用一直提供服务，该对象就一直存在。

​    死亡：**应用被卸载（或者服务器挂了），该对象消亡**。

  ## 9.4 域对象的概念

​    该对象有一个作用域（就是使用的范围），是**web应用中最大的作用域，叫application域**。**每个应用只有一个application域**。    

如何往域中存放参数及如何获取域中的参数

![](\web相关\web基础知识\image\application域01.png)

![](\web相关\web基础知识\image\application域02.png)

## 9.5 如何获取全局参数

  针对ServletContext配置的参数就是全局参数

![](\web相关\web基础知识\image\ServletContext配置全局参数01.png)  

![](\web相关\web基础知识\image\ServletContext配置全局参数02.png)



### 9.5.1 Servlet类视图全图：

![](\web相关\web基础知识\image\serverlet全类图01.png)

## 9.6 ServletContext的一些细节 

### 9.6.1 请求转发（基于ServletContext）

​    请求转发是服务器的行为，服务器内部自己去请求下一个地址，浏览器地址栏不会发生变化。     

![](\web相关\web基础知识\image\请求转发（基于ServletContext）01.png)

### 9.6.2 使用ServletContext获取文件路径，实现下载

 使用的方法是context.getRealPath();

![](\web相关\web基础知识\image\使用ServletContext获取文件路径，实现下载01.png)



### 9.6.3 3 读取配置文件的各种方式(.properties)

​      InputStream

​      ResourceBundle

​      ClassLoader            

原文链接：https://blog.csdn.net/jinfulin/article/details/44549573