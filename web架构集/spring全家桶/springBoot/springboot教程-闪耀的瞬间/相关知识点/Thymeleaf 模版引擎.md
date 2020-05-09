# 1.在上篇 控制器与页面 简单的介绍了怎么引入项目，怎么和控制器的action配合打开页面，本篇将分享它在项目中经常使用的场景

# 2.thymeleaf介绍

Thymeleaf 官网：www.thymeleaf.org，可下载操作手册
Thymeleaf 可以在有网络和无网络的环境下皆可运行，即它可以让美工在浏览器查看静态效果，也可以让程序员在服务器查看带数据的动态页面效果
html模板引擎，它可以完全替代 JSP，提供spring标准方言和一个与 SpringMVC 完美集成的可选模块，可以快速的实现表单绑定、属性编辑器、国际化等功能

# 3.在application.properties中，进行如下配置

```
# thymeleaf配置，开发环境不启用缓存，正式环境下请启用缓存，提高性能
spring.thymeleaf.cache=false
# thymeleaf对html元素格式要求严格，设置它的mode为HTML，忘记结束标签后不会报错
spring.thymeleaf.mode=HTML
```


springboot封装的thymeleaf默认是2.x版本，如果想使用最新的3.x版本可以在< properties >中配置版本

```
<properties>
   <thymeleaf.version>3.0.10.RELEASE</thymeleaf.version>
   <thymeleaf-layout-dialect.version>2.2.2</thymeleaf-layout-dialect.version>
</properties>

<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```


# 4.下面详细分享一些常用用法

请提前在项目resources目录下创建css、js文件夹，分别创建index.css，common.js文件，并在js文件夹下放入jquery.min.js，后面的html和模版需要用到

## 4.1 属性汇总

| **编号** | **属性**                                                     | **描述**                                                     | **示例**                                                     |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1        | th:text                                                      | 计算其值表达式并将结果设置为标签的标签体                     | <p th:text="${userName}">中国</p>，值为 null 为空时，整个标签不显示任何内容。 |
| 2        | th:utext                                                     | th:text 会对结果中的特殊字符转义，th:utext 不会转义，适合后端直接向前端输出 html 标签的内容 | <p th:utext="${userInfo}">中国</p>,，userInfo可以是html内容。 |
| 3        | th:attr                                                      | 为标签中的任意属性设置，可以一次设置多个属性                 | <a href="" th:attr="title='前往百度',href='http://baidu.com'">前往百度</a> |
| 4        | th:*                                                         | 为 html 指定的属性设值，一次设置一个                         | <a href="" th:title='前往百度' th:href="'http://baidu.com'">前往百度</a> |
| 5        | th:alt-title                                                 | 同时为 alt 与 title 属性赋值                                 | <a href="#" th:alt-title="'th:A-B'">th:A-B</a>               |
| 6        | th:lang-xmllang                                              | 同时为 lang 、xmllang 属性赋值                               | <head lang="en" th:lang-xmllang="en">                        |
| 7        | [th:fragment](https://blog.csdn.net/wangmx1993328/article/details/84747497) | 定义模板片段                                                 | <div th:fragment="copy">                                     |
| 8        | [ th:insert](https://blog.csdn.net/wangmx1993328/article/details/84747497) | 将被引用的模板片段插⼊到自己的标签体中                       | <div th:insert="~{footer :: copy}"></div>                    |
| 9        | [th:replace](https://blog.csdn.net/wangmx1993328/article/details/84747497) | 将被引用的模板片段替换掉自己                                 | <div th:replace="footer :: copy"></div>                      |
| 10       | [th:include](https://blog.csdn.net/wangmx1993328/article/details/84747497) | 类似于 th:insert，⽽不是插⼊⽚段，它只插⼊此⽚段的内容       | <div th:include="footer :: copy"></div>                      |
| 11       | [th:remove](https://blog.csdn.net/wangmx1993328/article/details/84747497) | 删除模板中的某些代码片段                                     | <tr th:remove="all">...                                      |
| 12       | [th:each](https://blog.csdn.net/wangmx1993328/article/details/84702386) | 迭代数据，如 数组、List、Map 等                              | <tr th:each="user : ${userList}">...                         |
| 13       | [th:if](https://blog.csdn.net/wangmx1993328/article/details/84702386) | 条件为 true 时,显示模板⽚段，否则不显示                      | <p th:if="${isMarry}">已婚1</p>                              |
| 14       | [th:unless](https://blog.csdn.net/wangmx1993328/article/details/84702386) | 条件为 false 时,显示模板⽚段，否则不显示                     | <p th:unless="!${isMarry}">已婚2</p>                         |
| 15       | [th:switch ](https://blog.csdn.net/wangmx1993328/article/details/84702386) | 与 Java 中的 switch 语句等效，有条件地显示匹配的内容         | <div th:switch="1">                                          |
| 16       | [th:case](https://blog.csdn.net/wangmx1993328/article/details/84702386) | 配合 th:switch 使用                                          | <div th:switch="1">    <p th:case="0">管理员</p>    <p th:case="1">操作员</p>    <p th:case="*">未知用户</p></div> |
| 17       | [th:with](https://blog.csdn.net/wangmx1993328/article/details/84766806) | 定义局部变量                                                 | <div th:with="userFirst=${userList[0]}">                     |
| 18       | [th:inline](https://blog.csdn.net/wangmx1993328/article/details/84783202) | 禁用内联表达式，内联js,内联css                               | <script type="text/javascript" th:inline="javascript">       |

## 4.2 使用模版：

​	定义公用头部css和尾部js引用，在其他页面中引用模版，更换样式时，只需更换模版中的引用即可
​    操作步骤：在resources—templates目录下创建一个template的文件夹，里面创建common.html文件，文件内容如下，以下有两种用法：

## 4.2.1 通过 th:fragment="模版名称" 定义一个模版

```html
<div th:fragment="header" >
    <link rel="stylesheet" th:href="@{/css/index.css}">
</div>	
```



### 4.2.2 通过 id标签 定义一个模版

```html
<div id="footer">
    <script type="text/javascript" th:src="@{/js/jquery.min.js}"></script>
    <script type="text/javascript" th:src="@{/js/common.js}"></script>
</div>
```


在需要引用头部、尾部的html文件中，使用 th:replace=“template/common :: header” 模版路径 :: 模版名称


```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>SpringBoot项目开发系列</title>

    <!-- 引用公用模版 -->
    <!-- 第一种用法，模版名::fragment名 -->
    <link th:replace="~{template/common :: header}" />
    <!-- 第二种用法，模版名::标签选择器 -->
    <script th:replace="~{template/common :: #footer}"></script>

</head>
<body>
    <div class="index_font">首页</div>
    <div class="index_font">SpringBoot项目开发系列</div>
	<!-- 通过引用模版，模版引用了index.css，本页面就可以直接使用 index_font -->
</body>
</html>
```


## 4.3 变量表达式: 

Spring EL表达式(在Spring术语中也叫model attributes)。如下所示

```html
直接 . 出后台返回对象属性       <span th:text="${user.name}">  
直接循环出后台返回数组-list属性  <ul><li th:each="user: ${users}" th:text="${user.name}"></li></ul>
可以写th:if 判断，             <div th:if="${user.age} > 20">我大于20啦</div>
th:unless与 if 相反            <div th:unless="${user.age} > 20">我还年轻</div>
```

# 5.贴下我的代码和运行效果，项目中常用的就这些

   

```java
@RequestMapping("/index")
    public String index(ModelMap model){
        List<User> list = new ArrayList<User>();
        for(int i=1 ; i < 10 ; i++){
            User user = new User();
            user.setId(i);
            user.setAge(19 + i);
            user.setName("zy" + i);
            list.add(user);
        }
		//在方法中使用ModelMap，然后把值返回到html页面
        model.addAttribute("user",list.get(0));
        model.addAttribute("users",list);
        return "index";//返回 tempaltes 下的 index.html
    }
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>SpringBoot项目开发系列</title>
    <link th:replace="template/common :: header" />
    <script th:replace="template/common :: footer"></script>
</head>
<body>
    <div class="index_font">首页</div>
    <div class="index_font">SpringBoot项目开发系列</div>

    <div class="index_font"></div>
    <div th:text="${user.name}"></div>
    <div th:if="${user.age} > 20">我大于20啦</div>
    <div th:unless="${user.age} > 20">我还年轻</div>

    <div class="index_font">---thymeleaf --each循环，一般table表格展示数据居多</div>
    <ul>
        <li th:each="user: ${users}" th:text="${user.name}"></li>
    </ul>
	<!-- 在javascript中获取 user、users这些对象，请使用th:inline="javascript"，否则取不到 -->
    <script type="text/javascript" th:inline="javascript">
        var user = [[${user}]];
        console.log(user);
        var users = [[${users}]];
        console.log(users);
    </script>
</body>
</html>
```

效果如下


还有字符串操作

判断是不是为空:null: 
<span th:if="${name} != null">不为空</span> 
<span th:if="${name1} == null">为空</span> 
判断是不是为空字符串: “” 
<span th:if="${#strings.isEmpty(name1)}">空的</span> 
判断是否相同： 
<span th:if="${name} eq 'jack'">相同于jack,</span> 
<span th:if="${name} eq 'ywj'">相同于ywj,</span> 
<span th:if="${name} ne 'jack'">不相同于jack,</span> 
不存在设置默认值： 
<span th:text="${name2} ?: '默认值'"></span> 
是否包含(分大小写): 
<span th:if="${#strings.contains(name,'ez')}">包ez</span> 
<span th:if="${#strings.contains(name,'y')}">包j</span> 
是否包含（不分大小写） 
<span th:if="${#strings.containsIgnoreCase(name,'y')}">包j</span> 
同理。。。下面的和JAVA的String基本一样。。。。不笔记解释，官网有

${#strings.startsWith(name,'o')} 
${#strings.endsWith(name, 'o')} 
${#strings.indexOf(name,frag)}// 下标 
${#strings.substring(name,3,5)}// 截取 
${#strings.substringAfter(name,prefix)}// 从 prefix之后的一位开始截取到最后,比如 (ywj,y) = wj, 如果是(abccdefg,c) = cdefg//里面有2个c,取的是第一个c 
${#strings.substringBefore(name,suffix)}// 同上，不过是往前截取 
${#strings.replace(name,'las','ler')}// 替换 
${#strings.prepend(str,prefix)}// 拼字字符串在str前面 
${#strings.append(str,suffix)}// 和上面相反，接在后面 
${#strings.toUpperCase(name)} 
${#strings.toLowerCase(name)} 
${#strings.trim(str)} 
${#strings.length(str)} 
${#strings.abbreviate(str,10)}// 我的理解是 str截取0-10位，后面的全部用…这个点代替，注意，最小是3位
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
thymeleaf还有很多其他 th标签 ，比如表单，url等，但我喜欢用原生的属性，ajax操作等
————————————————
版权声明：本文为CSDN博主「闪耀的瞬间」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/zhuyu19911016520/article/details/81154955