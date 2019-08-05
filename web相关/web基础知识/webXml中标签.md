# 1. display-name

```
<display-name></display-name>  
WEB应用的名字
```

# 2. description

```
<description></description> 
WEB应用的描述   
```

# 3. welcome-file-list

```
<welcome-file-list></welcome-file-list> 
指示服务器在收到引用一个目录名而不是文件名的URL时，使用哪个文件(其实就是欢迎界面或者说入口界面一般为index.*)   

```

# 4. context-param

```
<context-param></context-param> 
context-param元素声明应用范围内的初始化参数

  <!-- 指定spring配置文件位置 -->    
   <context-param>    
      <param-name>contextConfigLocation</param-name>    
      <param-value>    
       <!--加载多个spring配置文件 -->    
        /WEB-INF/applicationContext.xml, /WEB-INF/action-servlet.xml    
      </param-value>    
   </context-param>  
```



```
<filter></filter> 
过滤器将一个名字与一个实现javax.servlet.Filter接口的类相关联    
<filter-mapping></filter-mapping> 
一旦命名了一个过滤器，就要利用filter-mapping元素把它与一个或多个servlet或JSP页面相关联
```

