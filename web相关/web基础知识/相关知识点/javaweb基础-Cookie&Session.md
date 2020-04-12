

![](E:\学习笔记\web相关\web基础知识\image\Cookie&SessionXmind.png)

# 一、会话管理技术概述

## 1.1 什么是会话？

​     这里的会话指的是**web开发中的一次通话过程，当打开浏览器，访问网站地址后，会话开始，当关闭浏览器（或者到了过期时间），会话结束**。

​    例如：我们去网吧上网，在吧台拿到用户名和密码，然后找机器登录，这时候机器就认识了我们，我们就可以开始上网，这就相当于我们开启了一次上网的会话，当我们点击结束下机（或者遇到关机重启），或者上网时间到了，这时候机器就不再认识我们，那么就叫会话结束。

## 1.2 会话管理技术能做什么？

​	**共享同一个客户浏览器多个请求中数据**，例如购物车。（简单权限过滤） 

# 二、客户端会话管理技术（Cookie）：

## 2.1 什么是Cookie？

​	它是**客户端浏览器的缓存文件**，里面记录了客户浏览器访问网站的一些内容。它也是**Http协议请求和响应消息头的一部分**。（回顾http协议）

## 2.2 Cookie能做什么？

​	能保存客户浏览器访问网站的相关内容（**需要服务器开启Cookie**）。**从而在每次访问需要同一个内容时，先从本地缓存获取，使资源共享，并且提高效率**。

​    **Cookie有大小，个数限制。每个网站最多只能存20个cookie，且大小不能超过4kb**。**(32bit不能超过4096MB)同时，所有网站的cookie总数不超过300个**。

## 2.3 Cookie中的属性

    ### 2.3.1 属性： 

**name：必要属性，cookie的名称。**

**value：必要属性，cookie的值（不能是中文）**

 ### 2.3.2 可选属性

 path：**cookie的  路径**（重要）

domain：**cookie的域名（重要），相当于访问的网站（localhost）**

maxAge：**cookie的生存时间（相当于生命周期的活着）（比较重要）**，当删除cookie时，设置该值为0。

 **当不设置该值时，使用的是浏览器的内存，当关闭浏览器之后，cookie将丢失。设置了此值，就会保存成缓存文件（值必须是大于0的,以秒为单位）**。

**version：cookie的版本号。（不重要）**

 **comment：cookie的说明。（不重要）**

 ## 2.4 在web应用中如何设置和获取Cookie

```java
//定义一个Cookie
Cookie cookie = new Cookie(cookieName,cookieValue);
//HttpServletRequest 获取 Cookie
Cookie[] cookies = request.getCookies();//该方法返回的是一个数组。（为什么是数组呢，方便，可以直接拿到与该请求相关的所有cookie)
//HttpServletResponse 添加Cookie
response.addCookie(cookie);
//添加一个cookie，其实就是添加一个响应消息头
response.setHeader("Set-Cookie"，"name=value;path=;maxage=;domain=");//(为什么没有set方法，原因是set就会把之前的覆盖，所以每次都是添加）。

//如何确定一个唯一的cookie：cookieName+cookiePath+cookieDomain
//定位一个cookie是由cookie的名称和路径，主机（访问的资源)三部分组成

```

 ## 2.5 掌握Cookie的案例：

​    A：**使用Cookie技术获取最后访问时间(清除Cookie，设置maxAge(0));**

​    B：**Cookie的Path（必须搞明白，什么时候浏览器带给服务器，什么时候不带）**

​    C：**记录用户登录时的登录名**

​    D：**记录浏览顺序**

 

# 三、服务端会话管理技术（HttpSession）：

## 3.1 什么是HttpSession

​	它是**一个服务端会话对象，存储用户的会话数据。**

## 3.2 获取session的两种方式

### 3.2.1 方式一：request:getSession(); 

执行过程如下：

 ![](E:\学习笔记\web相关\web基础知识\image\获取session的两种方式01.png) 

### 3.2.2 方式二：request.getSession(boolean b);

![](E:\学习笔记\web相关\web基础知识\image\获取session的两种方式02.png)

 #### 3.2.2.1 常用的几个方法：

```java
void setAttribute(String key,Object value);

Object getAttribute(String key);

void removeAttribute(String key);

String getId();

```

**HttpSession的invalidate方法：作用是使session立即失效**。

**设置HttpSession的过期时间，Tomcat的默认过期时间是30分钟**。

## 3.3 HttpSession的生命周期

​    **出生——活着——死亡**

​    **出生：调用getSession方法后会话开始**

​    **活着：只要没有关闭会话（关闭浏览器）或者调用立即失效方法。或者服务器意外，HttpSession一直存在**

​    **死亡：调用立即失效方法invalidate，到了过期时间，关闭会话，服务器意外。**

## 3.4 域对象（三缺一了）

​    **HttpSession：也是一个域对象，它比application域范围小，比request域范围大**     

![](E:\学习笔记\web相关\web基础知识\image\域对象01.png)

## 3.5 三个案例

​    A 简单购物车实现

​    B 防止表单重复提交

​    C 完成用户登录，记录用户名和密码

## 3.6 客户端禁用Cookie后会话数据的保持

​    方式1：使用文字提示。163邮箱就是使用的这种方式。

​    方式2：URL重写。

​        解释：当禁用了cookie之后，客户端永远都不会带Cookie到服务器。

​        解决：我们自己给他带上，把URL重新写。 拼上一个JSESSIONID=session的ID。使用的是response.encodeURL()

​        原来：http://localhost:8080/servletdemo/ServletDemo1

​        重写后：http://localhost:8080/servletdemo/ServletDemo1;JSESSIONID=123

​        **注意：要重写必须全都重写，忘了一个，session中的数据就全部丢失。**

​		**因为不带cookie了，所以每次都是创建一个新的session**。

## 3.7 HttpSession对象的状态

### 3.7.1 什么是持久态

​	**把长时间不用，但还不到过期时间的HttpSession进行序列化，写到磁盘上**。

 **我们把HttpSession持久态也叫做钝化。（与钝化想反的，我们叫活化。）**

### 3.7.2 什么时候使用持久化

​      **第一种情况：当访问量很大时，服务器会根据getLastAccessTime来进行排序，对长时间不用，但是还没到过期时间的HttpSession进行持久化**。

​      **第二种情况：当服务器进行重启的时候，为了保持客户HttpSession中的数据，也要对HttpSession进行持久化**

### 3.7.3 注意：

​	**HttpSession的持久化由服务器来负责管理，我们不用关心**。

 **只有实现了序列化接口的类才能被序列化，否则不行**。



原文链接：https://blog.csdn.net/jinfulin/article/details/44683615