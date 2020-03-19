Java语言的关键字，变量修饰符，如果用transient声明一个实例变量，当对象存储时，它的值不需要维持。换句话来说就是，用transient关键字标记的成员变量不参与序列化过程。

作用：
        Java的serialization提供了一种持久化对象实例的机制。当持久化对象时，可能有一个特殊的对象数据成员，我们不想用serialization机制来保存它。为了在一个特定对象的一个域上关闭serialization，可以在这个域前加上关键字transient。当一个对象被序列化的时候，transient型变量的值不包括在序列化的表示中，然而非transient型的变量是被包括进去的。


编码试验加以证明：

1.自定义类（为了方便，我直接在main方法所在类中添加的一个静态属性类，或者叫成员类）

```java
public static class TransientTest implements Serializable{
    private static final long serialVersionUID = 233858934995755239L;
    private String name1;
    private transient String name2;
	public TransientTest(String name1,String name2){
		this.name1 = name1;
		this.name2 = name2;
	}
	public String toString(){
		return String.format("TransientTest.toString(): name1=%s,name2=%s", name1,name2);
	}
}
```
2.写一个测试方法	

```java
public static void testTransient(){
String name1="常规属性",name2="transient修饰的属性";
TransientTest test = new TransientTest(name1, name2);
System.out.println("序列化前："+test.toString());
ObjectOutputStream outStream;
ObjectInputStream inStream;
String filePath = "D:/test/object/TransientTest.obj";
try {
		outStream = new ObjectOutputStream(new FileOutputStream(filePath));
		outStream.writeObject(test);	
		inStream = new ObjectInputStream(new FileInputStream(filePath));
		TransientTest readObject = (TransientTest)inStream.readObject();
		System.out.println("序列化后："+readObject.toString());
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (ClassNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
}
```
3.在main方法中执行，然后可以看到得到的结果为

![](image\transient关键字序列化前后01.png)

印证了上面所讲的“用transient关键字标记的成员变量不参与序列化过程”。

用二进制查看器打开这个文件也可以看到，数据中只有name1，没有name2。（请忽略乱码问题，这个不是重点哈。）

![](image\transient关键字序列化前后02.png)

延伸：

在查看JDK源码的时候会发现很多地方都会加上transient关键字来修饰一些属性，那究竟是出于什么考虑才这么做呢？

我觉得，应该是为了节约磁盘空间，避免造成不必要的浪费吧。

以ArrayList中的 transient Object[] elementData 为例，这个成员变量的注释为：

![](image\transient关键字01.png)

翻译出来就是：

/ * *

*存储ArrayList元素的数组缓冲区。

* ArrayList的容量是这个数组缓冲区的长度。任何

*带有elementData的空ArrayList == DEFAULTCAPACITY_EMPTY_ELEMENTDATA

*当添加第一个元素时，将被扩展到DEFAULT_CAPACITY。

**/

这个缓冲区的容量实际上并不是ArrayList的容量，因为其实际上会预留一些空间，当空间不足时还会扩容，为减少浪费，因此在序列化时不会按照默认算法将这个成员变量写入磁盘。而是写了个writeObject方法，序列化时会调用这个方法将其持久化，在反序列化是，调用readObject，将其恢复出来。

这2个方法为：

![](image\ArrayList持久化01.png)

![](image\ArrayList持久化02.png)

参考ArrayList，在上面的TransientTest中添加2个方法，见代码：

```java
public static class TransientTest implements Serializable{
private static final long serialVersionUID = 233858934995755239L;
private String name1;
private transient String name2;
	public TransientTest(String name1,String name2){
		this.name1 = name1;
		this.name2 = name2;
	}
	public String toString(){
		return String.format("TransientTest.toString(): name1=%s,name2=%s", name1,name2);
	}
 
	private void writeObject(java.io.ObjectOutputStream s) throws java.io.IOException {
		s.defaultWriteObject();
		s.writeObject(name2);
	}
	private void readObject(java.io.ObjectInputStream s) throws java.io.IOException, ClassNotFoundException {
		s.defaultReadObject();
		name2=String.valueOf(s.readObject());
	}
}
```
然后在main方法中执行testTransient()，此时得到的结果是：

![](image\transient关键字序列化前后03.png)

## transient使用小结

1）一旦变量被transient修饰，变量将不再是对象持久化的一部分，该变量内容在序列化后无法获得访问。

2）transient关键字只能修饰变量，而不能修饰方法和类。注意，本地变量是不能被transient关键字修饰的。变量如果是用户自定义类变量，则该类需要实现Serializable接口。

3）被transient关键字修饰的变量不再能被序列化，一个静态变量不管是否被transient修饰，均不能被序列化。

第三点可能有些人很迷惑，因为发现在User类中的username字段前加上static关键字后，程序运行结果依然不变，即static类型的username也读出来为“Alexia”了，这不与第三点说的矛盾吗？实际上是这样的：第三点确实没错（一个静态变量不管是否被transient修饰，均不能被序列化），反序列化后类中static型变量username的值为当前JVM中对应static变量的值，这个值是JVM中的不是反序列化得出的，下面我来证明：



![img](image\static变量序列化01.png)

运行结果为：



![img](image\static变量序列化02.png)

这说明反序列化后类中static型变量username的值为当前JVM中对应static变量的值，为修改后jmwang，而不是序列化时的值Alexia。

 **transient使用细节——被transient关键字修饰的变量真的不能被序列化吗？**



![img](image\transient关键字02.png)

运行结果是： 是的，我将会被序列化，不管我是否被transient关键字修饰

这是为什么呢，不是说类的变量被transient关键字修饰以后将不能序列化了吗？

我们知道在Java中，**对象的序列化可以通过实现两种接口来实现**，若实现的是Serializable接口，则所有的序列化将会自动进行，

**若实现的是Externalizable接口，则没有任何东西可以自动序列化，需要在writeExternal方法中进行手工指定所要序列化的变量，这与是否被transient修饰无关。**

因此第二个例子输出的是变量content初始化的内容，而不是null。