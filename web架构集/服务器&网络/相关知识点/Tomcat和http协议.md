# 1.Tomcat

## 1.1 web概述

### 1.1.1 静态资源

**在不同时间或者使用不同角色访问的资源，看到的内容是一样的（一成不变的），这种资源就称为静态资源**。例如：html,css,js,image等等。 

### 1.1.2 动态资源：

**可交互的**，**在不同时间或使用不同角色访问的资源，看到的内容是不一样的**。例如：jsp,asp,php等等。

 ## 1.2  Tomcat简介

### 1.2.1 javaee规范

13个规范，JCP制定的，**jsp/servlet,jdbc,jaxp,jta,jpa,jndi,jmf,EJB**

 ### 1.2.2 常见服务器介绍

WebLogic

WebSphereAS    

JBOSS

Tomcat

### 1. 2.3 Tomcat下载和安装

### 1.2.4 Tomcat各版本所需支持

### 1.2.5 Tomcat目录详解

bin    二进制目录

conf    tomcat配置文件目录

lib    tomcat运行时所需jar包

logs    tomcat运行时日志

temp    tomcat临时文件目录

webapps    tomcat默认应用目录

work    tomcat工作目录

### 1.2.6 Tomcat启动服务

startup.bat/shutdown.bat

startup.sh/shutdown.sh

Window系统下用.bat

### 1.2.7 Tomcat启动遇到的问题和解决办法

#### 1.2.7.1 启动一闪而过

 原因：没有配置JAVA_HOME环境

#### 1.2.7.2 Address already in use: JVM_Bind

  原因：端口被占用

  解决办法有两种

（1）结束别人

使用netstat -a -o找到进程id（pid），在任务管理器中结束掉该进程。

（2）修改自己

修改的是Tomcat\conf\server.xml

#### 1.2.7.3 启动时报很多异常，但是可以正常启动

原因：是应用中抛出的异常，不影响服务器启动，可以重新解压一个新的tomcat来解决。

#### 1.2.7.4 其他问题

具体分析

 ## 1.3 javaweb工程

### 1.3.1 javaweb工程目录详解

webDemo(我的web工程名称)

​	资源(html，css，js)

​	WEB-INF

​		classes        java编译的class文件

 		lib        jar包

​	 	web.xml    web应用的配置文件

### 1.3.2 创建javaweb工程

手动创建

使用MyEclipse创建

### 1.3.3 部署javaweb工程

手动部署：将工程（应用）直接拷贝到tomcat\webapps目录中

使用MyEclipse部署

打成war包：首先将应用打成war。然后将war包拷贝到tomcat\webapps

jar -cvf appname.war .

## 1.4  Tomcat配置

### 1.4.1 Tomcat的主配置文件

 tomcat\conf\server.xml

### 1.4.2 配置虚拟目录

配置的是Context，两种方式

（1）在<Host>里添加一个<Context path="" docBase=""/>元素

path：访问地址**URI**。

docBase：**访问资源磁盘物理地址。**


（2）在conf\catalina\localhost目录中写一个独立的xml文件。

xml的文件名可以起任意名称但不能是中文的。建议与应用同名。

### 1.4.3 配置虚拟主机

配置的是Host

  在<Engine>元素中添加<Host name="" appBase="" unpackWARs="" autoDeploy=""/>

  name：虚拟主机名称

  appBase：主机的目录。相当于webapps。

  unpackWARs：是否自动解压war包。

  autoDeploy：是否自动发布。

### 1.4.4 配置默认端口，默认应用，默认主页

#### 1.4.4.1 配置默认端口：

(目录：tomcat/conf/server.xml)

<Connector port="8080" protocol="HTTP/1.1" connectionTimeout="20000" redirectPort="8443" />

#### 1.4.4.2 配置默认应用：

​      第一种：将应用名称该ROOT。部署到tomcat下。

​      第二种：写一个独立的xml文件，文件名称是ROOT.xml。

​		(目录：tomcat\conf\Catalina\localhost\ROOT.xml)

#### 1.4.4.3 配置默认主页：

​      默认主页是针对应用而说的。所以修改的是web.xml

​      在web.xml中添加

​      <welcome-file-list>

​        <welcome-file>1.htm</welcome-file>

​        //可以写多个

​      </welcome-file-list>

 

# 2. HTTP

## 2.1 HTTP是什么？

Hyper Text Transfer Protocol 超文本传输协议，传输超文本。

WEB浏览器与WEB服务器之间的一问一答的交互过程必须遵循一定的规则，这个规则就是HTTP协议。

 这个规则又称为**问答机制/握手机制**。

## 2.2 HTTP的版本

​    1.0版本和1.1版本的区别:1.0一次连接一次收发，1.1一次连接多次收发请求。

​    1.3 特殊说明：

​    当浏览器看到<img><script><link>标签时会自动发出请求。

 ## 2.3 HTTP组成部分

  ### 2.3.1 请求部分

​    请求行：永远位于请求的第一行

​    请求消息头：是从第二行开始到第一个空行结束。

​    请求的正文：从第一个空行后开始，到正文的结束。

### 2.3.2 响应部分

响应行：永远位于响应的第一行。

响应消息头：是从第二行开始到第一个空行结束。

响应的正文：从第一个空行后开始，到正文的结束。和我们在浏览器上右键查看源文件看到的内容是一样的。

 ### 2.3.3 请求部分详解

  #### 2.3.3.1 请求行：

   GET /myapp/2.html HTTP/1.1

   GET：

​    请求的方式。常用的有GET，POST。

​    GET方式：**不安全，内容在地址栏中显示，长度有限制**。

​    POST方式：**相对安全，在地址栏中不显示，长度相对没有限制**。 

   /myapp/2.html：请求资源的URI。

   HTTP/1.1 ： 使用的协议和协议的版本。

#### 2.3.3.2 请求消息头：

​    当看见Accept时，就表示客户浏览器告诉服务器的暗语。

​    Accept：

​      **告知服务器，客户浏览器支持的MIME类型**。

​    Accept-Encoding：

​      告知服务器，客户浏览器所支持的**压缩编码格式。最常用的就是GZIP压缩**。

​    Accept-Language：

​      **告知服务器，客户浏览器所支持的语言**。例如：zh_CN,en_US等。

​    Referer：

​      **告诉服务器，当前请求的来源**。（该请求是从哪里来的）

​      **如果当前请求没有来源的话（例如从地址栏输入）则不会有这个头**。

​      作用1：投放广告。

​      作用2：防盗链。

​    Content-Type：

​      **请求正文的MIME类型**。

​    Content-Length：

​      **请求正文的长度**。

​    User-Agent：

​      **客户浏览器信息**。

​    Connection: Keep-Alive

​      **连接状态：保持连接**。

​    If-Modified-Since：

​      **客户浏览器缓存资源的最后更新时间**。

​    Cookie：

​      **会话管理有关。非常重要**(*****)

  #### 2.3.3.3 请求的正文：

​    **GET方式没有请求的正文。POST方式有请求的正文**。

​    只有有name属性的表单输入域的内容才会被提交。

​    当enctype取默认值的时候：

​      enctype的默认值：application/x-www-form-urlencoded

​      请求的正文的体现形式是key=value&key=value。

​      username=test&password=123

​    当enctype取值为multipart/form-data时：（文件上传时候用）

​      请求的正文就变成了：

​      Content-Disposition: form-data; name="username"

​		Content-Disposition: form-data; name="password"

### 2.3.4 响应部分详解

  #### 2.3.4.1 响应行

​    HTTP/1.1 200 OK

​    HTTP/1.1：

​      **使用的协议和版本**。

​    200：

​      **响应状态码**。

​    OK：

​      **响应状态码描述**。

    #### 2.3.4.2 常用状态码说明：(需要记住)

​    **200     全部都OK**

​    **302/307     请求重定向**。（请求重定向：是客户浏览器行为，发出了两次请求。地址栏会发生变化。）

​    **304     使用本地缓存**。（当本地缓存资源没有发生变化时）

​    **404     找不到资源**

​    **500     服务器内部错误**

#### 2.3.4.3 响应消息头：

​    Location：

​      **请求重定向的地址，常与302/307配合使用**。

​    Server：

​      **服务器相关信息**。

​    Content-Type：

​      **告知客户浏览器，响应正文的MIME类型**。

​    Content-Length：

​      **告知客户浏览器，响应正文的长度**。

​    Content-Encoding：

​      **告知客户浏览器，响应正文的压缩编码格式。常用的就是GZIP压缩**。

​    Content-Language：

​      **告知客户浏览器，响应正文的语言字符集**。例如：zh_CN,en_US等。

​    Content-Disposition：

​      **告知客户浏览器，以下载的方式打开**。

​    Refresh：

​      **定时刷新**。

​    Last-Modified：

​      **服务器上的资源最后更新时间**。

​    Set-Cookie：

​      **会话管理相关**，非常重要。（*****）

​    **当写成如下形式时，就表示不要缓存。永远不会看到304状态码**。

​    Expires:-1

​    Catch-Control: no-catch(1.1)//针对http协议1.1版本

​    Pragma:no-catch(1.0)//针对http协议1.0版本

  #### 2.3.4.4 响应的正文：

​    就和我们在浏览器上右键查看源文件所看到的内容是一样的。

​    <html>

​       <head>

​        <link rel="stylesheet" href="css.css" type="text/css">

                <script type="text/javascript" src="demo.js"></script>

​       </head>

​       <body>

                <img src="1.jpg" />

​       </body>

​    </html>



 



### 2.3.5 请求消息头和响应消息头之间的共性：

​    **头名称首字母大写，多个单词每个单词的首字母都大写**。

​    **多个单词用-分隔**

​    **名称和值之间用:分隔**

​    **值和:之间有一个空格**

​    **多个值之间用,分隔**

​    **和值之间也有一个空格**

​    **两个头之间用回车分隔**



原文链接：https://blog.csdn.net/jinfulin/article/details/44549361