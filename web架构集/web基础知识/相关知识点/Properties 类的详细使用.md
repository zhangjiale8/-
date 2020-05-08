# 一.Properties 类

​	Properties 类位于 java.util.Properties ，是Java 语言的配置文件所使用的类， Xxx.properties 为Java 语言常见的配置文件，如数据库的配置 jdbc.properties, 系统参数配置 system.properties。 这里，讲解一下Properties 类的具体使用。

​	Properties类继承自Hashtable类并且实现了Map接口，也是使用一种键值对的形式来保存属性集。不过Properties有特殊的地方，就是它的键和值都是字符串类型。以key=value 的 键值对的形式进行存储值。 key值不能重复。

![](\web相关\web基础知识\image\Properties类型层次结构.png)

​	继承了Hashtable 类，以Map 的形式进行放置值， put(key,value) get(key)

## 1.1 主要方法:

这里只讲解一些常用的形式。

![](\web相关\web基础知识\image\Properties主要方法01.png)

# 二. 打印 JVM 参数
JVM 中可以获取Properties, 来打印输出 JVM 所了解的属性值。
用list() 方法，打印到控制台。

```java
@Test
	public void printTest(){
		Properties properties=System.getProperties();
		properties.list(System.out);
	}
```


常见的有:

![](\web相关\web基础知识\image\JVM参数常见01.png)

# 三.打印自定义.properties 文件中的值
在src 目录下，放置 jdbc.properties 文件，是数据库的配置文件。

```properties
jdbc.driver=com.mysql.jdbc.Driver
jdbc.url=jdbc:mysql://localhost:3306/mybatis?characterEncoding=utf8
jdbc.username=root
jdbc.password=abc123

```

## 3.1 list 输出到控制台 用绝对路径加载

```java
@Test
	public void name1Test(){
		try{
			Properties properties=new Properties();
			//用的是磁盘符的绝对路径 
			InputStream input=new BufferedInputStream(new 		FileInputStream("D:\workspace\JavaLearn\src\jdbc.properties"));
			properties.load(input);
			properties.list(System.out);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
```


url 被截取了。

![](\web相关\web基础知识\image\ist 输出到控制台用绝对路径加载01.png)

## 3.2 propertyNames 输出 getClass() 加载

```java
@Test
	public void name2Test(){
		try{
			Properties properties=new Properties();  // 用/文件名， / 表示根目录
			InputStream input=PropertiesTest.class.getClass().getResourceAsStream("/jdbc.properties");
			properties.load(input);
			Enumeration<String> names=(Enumeration<String>) properties.propertyNames();
			while(names.hasMoreElements()){
				//这是key值
				String key=names.nextElement();
				String value=properties.getProperty(key);
				System.out.println(key+"="+value);
			}
		}catch(Exception e){
			e.printStackTrace();
		}
	}
```

![](\web相关\web基础知识\image\propertyNames01.png)

## 3.3 stringPropertyNames 输出 getClassLoader 加载 (推荐)
			

```java
@Test
	public void name3Test(){
		try{
			Properties properties=new Properties();
			//直接写src 类路径下的文件名
			InputStream 	input=PropertiesTest.class.getClassLoader().getResourceAsStream("jdbc.properties");
			properties.load(input);
		//把key值转换成set 的形式，遍历set
		Set<String> names=properties.stringPropertyNames();
		Iterator<String> iterator=names.iterator();
		while(iterator.hasNext()){
			String key=iterator.next();
			String value=properties.getProperty(key);
			System.out.println(key+"="+value);
		}
		
	}catch(Exception e){
		e.printStackTrace();
	}
}
```
![](\web相关\web基础知识\image\stringPropertyNames01.png)

# 四. 获取值 getProperties
			

```java
@Test
	public void name3Test(){
		try{
			Properties properties=new Properties();
			InputStream input=PropertiesTest.class.getClassLoader().getResourceAsStream("jdbc.properties");
			properties.load(input);
			//String value=properties.getProperty("jdbc.url");
			String value=properties.getProperty("jdbc.url1","没有该key值");
			System.out.println("输出值:"+value);	
	}catch(Exception e){
		e.printStackTrace();
	}
}
```
输出时，getProperty() 有当前的key值，则输出Key值对应的value 值。
如果没有key值，则输出 null 值。
后面可以跟 default 值，如果没有该值，则输出设置的默认值。

![](\web相关\web基础知识\image\getProperties01.png)

# 五. 写入到Properties 文件

## 5.1 普通写入，中文时乱码

```java
@Test
	public void writeTest(){
		try{
			Properties properties=new Properties();
			InputStream input=PropertiesTest.class.getClassLoader().getResourceAsStream("jdbc.properties");
			properties.load(input);
//多添加几个值。
		properties.setProperty("name","两个蝴蝶飞");
		properties.setProperty("sex","男");

		//properties.put("name","两个蝴蝶飞");  可以用继承Hashtable 的put 方法写入值
		// properties.put("sex","男");
		
		//将添加的值，连同以前的值一起写入 新的属性文件里面。
		OutputStream out=new FileOutputStream("D:\\jdbc.properties");
		properties.store(out,"填充数据");
		
	}catch(Exception e){
		e.printStackTrace();
	}
}
```
![](\web相关\web基础知识\image\普通写入，中文时乱码01.png)

## 5.2 解决乱码写入的问题
在构建输入流和输出流时，指定编码格式， 编码的格式相同。 如均是 utf-8的形式。


			

```java
@Test
	public void write2Test(){
		try{
			Properties properties=new Properties();
			//用绝对路径
			InputStream input=new BufferedInputStream(new FileInputStream("D:\workspace\JavaLearn\src\jdbc.properties"));
			properties.load(new InputStreamReader(input,"utf-8"));
				//多添加几个值。
			properties.setProperty("name","两个蝴蝶飞");
			properties.setProperty("sex","男");
OutputStream output=new FileOutputStream("D:\\jdbc.properties");
		OutputStreamWriter out=new OutputStreamWriter(output,"utf-8");
		properties.store(out,"填充数据");
		
	}catch(Exception e){
		e.printStackTrace();
	}
}
```

测试运行之后:

![](\web相关\web基础知识\image\解决乱码写入的问题01.png)

这样便解决了乱码的问题。

# 六 . 加载和导出到 xml 配置文件
## 6.1 导出到 .xml 配置文件 storeToXML
将Properties 类中定义的属性，导出成 .xml 的形式.


			

```java
@Test
	public void xmlWriteTest(){
		try{
        //处理成编码样式。
        Properties properties=new Properties();
		//多添加几个值。
		properties.setProperty("name","两个蝴蝶飞");
		properties.setProperty("sex","男");
		OutputStream output=new FileOutputStream("D:\\jdbc.xml");
		//编码设置成utf-8的形式。 
		properties.storeToXML(output,"填充到xml","utf-8");
		
	}catch(Exception e){
		e.printStackTrace();
	}
}
```

测试结果为:

![](\web相关\web基础知识\image\导出到配置文件storeToXML01.png)

用 <entry> 节点 key为属性， 后面跟值来进行输入。
可按照这种形式，继续添加。

## 6.2 导出XML 配置文件 loadFromXML


			

```java  
@Test
public void xmlReadTest(){
try{
	Properties properties=new Properties();
	InputStream input=new BufferedInputStream(new FileInputStream("D:\jdbc.xml"));
	properties.loadFromXML(input);
	properties.list(System.out);
}catch(Exception e){
		e.printStackTrace();
	}
}
```
![](\web相关\web基础知识\image\导出XML配置文件loadFromXML01.png)

这就是Properties 类的常见用法 。



原文链接：https://blog.csdn.net/yjltx1234csdn/article/details/93769032