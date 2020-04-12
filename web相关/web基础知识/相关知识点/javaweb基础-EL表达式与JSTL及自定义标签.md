![](E:\学习笔记\web相关\web基础知识\image\EL表达式与JSTL及自定义标签Xmind.png)

# 一、EL表达式

## 1.1 EL简介

**Expression Language。它不是一种语言，只是一个表达式**。

用于将数据显示到JSP上。它的出现是替代java表达式的，从jsp2.0开始。

特点就是简单易用：

### 1.1.1 java表达式

```jsp
<%List<Book> list = new ArrayList();%>

<%=list.get(0).getBookName() %>

```

### 1.1.2 EL表达式：

```jsp
![EL表达式获取数据01](E:\学习笔记\web相关\web基础知识\image\EL表达式获取数据01.png)${list[0].bookname}E 
```

## 1.2 EL表达式基本语法

${表达式}

**注意：EL表达式是从四大域对象中获取数据（application,session,request,pagecontext);**

**细节：EL表达式中没有空指针异常，没有数组下标越界，没有字符串拼接。**

## 1.3 EL表达式的数据获取

  ### 1.3.1获取数据

![](E:\学习笔记\web相关\web基础知识\image\EL表达式获取数据01.png)

![](E:\学习笔记\web相关\web基础知识\image\EL表达式获取数据02.png)

  ### 1.3.2 EL运算符

![](E:\学习笔记\web相关\web基础知识\image\EL运算符01.png)

![](E:\学习笔记\web相关\web基础知识\image\EL运算符02.png)  

#### 1.3.2.1 empty运算符：

  判断一个字符串是否为""或其他对象是否为null，同时还能判断集合中是否有元素。

 ![](E:\学习笔记\web相关\web基础知识\image\empty运算符.png) 

#### 1.3.2.2三元运算符：

![](E:\学习笔记\web相关\web基础知识\image\三元运算符.png)

 ## 1.4 EL中的隐式对象（共11个）

| EL中的隐式对象   | 类型                          | 对应JSP隐式对象 | 备注                                    |
| ---------------- | ----------------------------- | --------------- | --------------------------------------- |
| PageContext      | Javax.serlvet.jsp.PageContext | PageContext     | 完全一样                                |
| ApplicationScope | Java.util.Map                 | 没有            | 应用层范围                              |
| SessionScope     | Java.util.Map                 | 没有            | 会话范围                                |
| RequestScope     | Java.util.Map                 | 没有            | 请求范围                                |
| PageScope        | Java.util.Map                 | 没有            | 页面层范围                              |
| Header           | Java.util.Map                 | 没有            | 请求消息头key，值是value（一个）        |
| HeaderValues     | Java.util.Map                 | 没有            | 请求消息头key，值是数组（一个头多个值） |
| Param            | Java.util.Map                 | 没有            | 请求参数key，值是value（一个）          |
| ParamValues      | Java.util.Map                 | 没有            | 请求参数key，值是数组（一个名称多个值） |
| InitParam        | Java.util.Map                 | 没有            | 全局参数，key是参数名称，value是参数值  |
| Cookie           | Java.util.Map                 | 没有            | Key是cookie的名称，value是cookie对象    |

![](E:\学习笔记\web相关\web基础知识\image\EL中的隐式对象01.png)      

## 1.5 EL表达式定义和使用函数

​    **EL不支持字符串操作**。

## 1.5.1 定义和使用函数的四步： 

a.写一个普通的java类

（注意，普通Java类实现功能的方法必须是静态的，因为**EL只能调用静态的方法**）

 ![](E:\学习笔记\web相关\web基础知识\image\写一个普通的java类.png)    

b.在WEB-INF下创建一个xml，文件的扩展名为.tld

 ![](E:\学习笔记\web相关\web基础知识\image\tld文件编写01.png)         

c.在jsp中使用taglib指令引入

 ![](E:\学习笔记\web相关\web基础知识\image\taglib指令引入01.png)

d.在jsp中使用

 ![](E:\学习笔记\web相关\web基础知识\image\jsp中使用01.png)

![](E:\学习笔记\web相关\web基础知识\image\jsp中使用02.png)        

# 二、JSTL 

## 2.1 JSTL简介 

​    JSP Standard Tag Libary：**JSP中标准的标签库**。

​    **该标签库是由Apache实现的。**

​    **导入jar包：JavaEE的jar包中包含**。

## 2.2 JSTL的组成

 **Core：核心标签库。通用逻辑处理**

**Fmt：国际化有关。**

**Functions：EL函数**

**SQL：操作数据库。不用**

**XML：操作XML。不用**

## 2.3 JSTL的Core

| 分类 | 功能分类   | 标签名称                                   |
| ---- | ---------- | ------------------------------------------ |
|      | 表达式操作 | out  set  remove  catch                    |
|      | 流程控制   | if  choose  when  otherwise                |
|      | 迭代操作   | forEach  forTokens                         |
|      | URL操作    | import  param  url  param  redirect  param |

详情请参考【CORE核心标签.doc】

## 2.4 JSTL的Functions介绍

 使用taglib指令导入：详情请看【第18章JSTL Functions标签库.doc】

  fn:contains函数：用于判断在源字符串中是否包含目标字符串。

  fn:containsIgnoreCase函数：用于判断在源字符串中是否包含目标字符串，并且在判断时忽略大小写。

  fn:startsWith函数：用于判断源字符串是否以指定的目标字符串开头。

  fn:endsWith函数：用于判断源字符串是否以指定的目标字符串结尾。

  fn:indexOf函数：用于在源字符串中查找目标字符串，并返回源字符串中最先与目标字符串匹配的第一个字符的索引。

  fn:replace函数：用于把源字符串中的一部分替换为另外的字符串，并返回替换后的字符串。

  fn:substring函数：用于获取源字符串中的特定子字符串。

  fn:substringBefore函数：用于获取源字符串中指定子字符串之前的子字符串。

  fn:substringAfter函数：用于获取源字符串中指定子字符串之后的子字符串

  fn:split函数：用于将源字符串拆分为一个字符串数组。

  fn:join函数：用于将源字符串数组中的所有字符串连接为一个字符串。

  fn:toLowerCase函数：用于将源字符串中的所有字符改为小写。

  fn:toUpperCase函数：用于将源字符串中的所有字符改为大写。

  fn:trim函数：用于将源字符串中的开头和末尾的空格删除。

  fn:escapeXml函数：用于将源字符串中的字符"<"、">"、"""和"&"等转换为转义字符。

  fn:length函数：用于返回字符串中的字符的个数，或者集合和数组的元素的个数

# 三、自定义标签

## 3.1 自定义标签的作用 

​      **自定义Jsp中的程序处理，替换掉JSP中的Java脚本**。

## 3.2 自定义标签的编写步骤

 	**实现标签自定义需要实现javax.servlet.jsp.tagext.SimpleTag或者继承javax.servlet.jsp.tagext.SimpleTagSupport**

 ### 3.2.1 javax.servlet.jsp.tagext.SimpleTag中的方法：

```java
void doTag():遇到自定义标签时由服务器调用执行。

JspTag getParent():得到父标签的引用。

void setJspBody(JspFragment jsp):由服务器调用，传入JSP的片段

void setJspContext(JspContext jc):由服务器调用，传入当前页面的PageContext

void setParent(JspTag parent):由服务器调用，传入他的父标签

```

### 3.2.2 第一步:写一个类继承SimpleTagSupport

![](E:\学习笔记\web相关\web基础知识\image\写一个类继承SimpleTagSupport01.png) 

### 3.2.3 第二步：创建一个.tld的xml文件在里面配置tag的信息。

![](E:\学习笔记\web相关\web基础知识\image\创建一个.tld的xml文件在里面配置tag的信息.png)

### 3.2.4 第三步：在jsp中引入自定义标签

![](E:\学习笔记\web相关\web基础知识\image\在jsp中引入自定义标签01.png)

## 3.3 自定义标签的作用4个

### 3.3.1 控制主体内容是否显示。

 ![](E:\学习笔记\web相关\web基础知识\image\控制主体内容是否显示.png)         

### 3.3.2 控制结束标签后的JSP内容不执行。

![](E:\学习笔记\web相关\web基础知识\image\控制结束标签后的JSP内容不执行01.png) 

![](E:\学习笔记\web相关\web基础知识\image\控制结束标签后的JSP内容不执行02.png)        

### 3.3.3 控制主体内容重复执行。

![](E:\学习笔记\web相关\web基础知识\image\控制主体内容重复执行01.png)

 ![](E:\学习笔记\web相关\web基础知识\image\控制主体内容重复执行02.png)

 ![](E:\学习笔记\web相关\web基础知识\image\控制主体内容重复执行03.png)

### 3.3.4 改变主体内容后再输出。

![](E:\学习笔记\web相关\web基础知识\image\改变主体内容后再输出01.png)

 

![](E:\学习笔记\web相关\web基础知识\image\改变主体内容后再输出02.png)      

 ![](E:\学习笔记\web相关\web基础知识\image\改变主体内容后再输出03.png)

![](E:\学习笔记\web相关\web基础知识\image\改变主体内容后再输出04.png)      

## 3.4 自定义标签配置的body-cotent说明

  4自定义标签配置的body-cotent说明

### 3.4.1 <body-content>取值：

JSP：jsp中能出现啥，标签主体内容就能出现啥。给传统标签用的。简单标签一用就报错。

empty：没有主体内容。简单和传统标签都能用。

scriptless：给简单标签用的，说明主体内容是非脚本。

tagdependent：把主体内容的EL表达式当做普通字符串对待。

## 3.5 自定义标签的案例

  5自定义标签的案例

 ### 3.5.1 模拟for

![](E:\学习笔记\web相关\web基础知识\image\模拟for01.png) 

​      ![](E:\学习笔记\web相关\web基础知识\image\模拟for02.png)

 ![](E:\学习笔记\web相关\web基础知识\image\模拟for03.png)

 

原文链接：https://blog.csdn.net/jinfulin/article/details/44683647