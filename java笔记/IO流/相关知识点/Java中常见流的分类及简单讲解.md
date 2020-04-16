# 1 流分类



![img](\java笔记\IO流\image\流的分类01.png)

**流在Java中是指计算中流动的缓冲区。**

**从外部设备流向中央处理器的数据流成为“输入流”，反之成为“输出流”。**

## 1.1 字符流和字节流的主要区别：

 1.字节流读取的时候，读到一个字节就返回一个字节；字符流使用了字节流读到一个或多个字节（中文对应的字节数是两个，在UTF-8码表中是3个字节）时。先去查指定的编码表，将查到的字符返回。

 2.字节流可以处理所有类型数据，如：图片，MP3，AVI视频文件，而字符流只能处理字符数据。只要是处理纯文本数据，就要优先考虑使用字符流，除此之外都用字节流。

# 2 字节流：

## 2.1 字节输入流类：FileInputStream、BufferedInputStream和DataInputStream

### 2.1.1 FileInputStream:

​	此类用于从本地文件系统中读取文件内容。

#### 2.1.1.1 构造方法：

·FileInputStream(File file):打开一个到实际文件的连接来创建一个FileInputStream，该文件通过文件系统中的File对象file指定。

·FileInputStream(String name):打开一个到实际文件的连接来创建一个FileInputStream，该文件通过文件系统中的路径名name指定。

#### 2.1.1.2 常用方法：

·int available():返回下一次对此输入流调用的方法不受阻塞地从此输入流读取（或跳过）的估计剩余字节数。

·void close():关闭此文件输入流并释放与该流关联的所有系统资源。

### 2.1.2 BufferedInputStream：

​	此类本身带有一个缓冲区，在读取数据时，先放到缓冲区中，可以减少对数据源的访问，提高运行的效率。**

#### 2.1.2.1 构造方法：

·BufferedInputStream(InputStream in):创建一个BufferedInputStream并保存其参数，即输入流in，以便将来使用。

·BufferedInputStream(InputStream in,int size):创建一个具有指定缓冲区大小的BufferedInputStream并保存其参数，即输入流in，以便将来使用。

#### 2.1.2.2 常用方法：

·int available():返回下一次对此输入流调用的方法不受阻塞地从此输入流读取（或跳过）的估计剩余字节数。

·void close():关闭此输入流并释放与该流关联的所有系统资源。

·int read():从输入流中读取数据的下一个字节。

·int read(byte[] b,int off,int len):从此字节输入流中给定偏移量处开始将各字节读取到指定的byte数组中。

### 2.1.3 DataInputStream:

**该类提供一些基于多字节读取方法，从而可以读取基本数据类型的数据。**

#### 2.1.3.1 构造方法：

·DataInputStream(InputStream in):使用指定的底层InputStream创建一个DataInputStream。

#### 2.1.3.2 常用方法：

·int read(byte[] b):从包含的输入流中读取一定数量的字节，并将它们存储到缓冲区数组b中。

·int read(byte[] b,int off,int len):从包含的输入流中将最多len个字节读入一个byte数组中。

## 2.2 字节输出流类：FileOutputStream、BufferedOutputStream和DataOutputStream

**FileOutputStream:此类用于从本地文件系统的文件中写入数据。**

构造方法：

·FileOutputStream(File file):创建一个向指定File对象表示的文件中写入数据的文件输出流。

·FileOutputStream(String name):创建一个向具有指定名称的文件中写入数据的输出文件流。

常用方法：

·void close():关闭此文件输出流并释放与此流有关的所有系统资源。

·FileDescriptor getFD():返回与此流有关的文件描述符。

·void write(byte[] b):将b.length个字节从指定byte数组写入此文件输出流中。

·void write(byte[] b,int off,int len):将指定byte数组中从偏移量off开始的len个字节写入此文件输出流。

·void write(int b):将指定字节写入此文件输出流。

**BufferedOutputStream:此类本身带有一个缓冲区，在写入数据时，先放到缓冲区中，实现缓冲的数据流。**

构造方法：

·BufferedOutputStream(OutputStream out):创建一个新的缓冲输出流，来将数据写入指定的底层输入流。

·BufferedOutputStream(OutputStream out,int size):创建一个新的缓冲输出流，来将具有指定缓冲区大小的数据写入指定的底层输出流。

常用方法：

·void flush():刷新此缓冲的输出流。

·void write(byte[] b,int off,int len):将指定byte数组中从偏移量off开始的len个字节写入此缓冲的输出流。

·void write(int b):将指定的字节写入此缓冲的输出流。

**DataOutputStream(OutputStream out):创建一个新的数据输出流，将数据写入指定基础输出流。**

常用方法：

·void flush():清空此数据输出流。

·int size()：返回计数器written的当前值，即到目前为止写入此数据输出流的字节数。

·void write(byte[] b,int off,int len):将指定byte数组中从偏移量off开始的len个字节写入基础输出流。

·void write(int b):将指定字节（参数b的八个低位）写入基础输出流。

# 3 字符流：

**FileReader:用来读取字符文件的便捷类。此类的构造方法假定默认字符编码和默认字节缓冲区大小都是适当的。**

构造方法：

·FileReader(File file):在给定从中读取数据的File的情况下创建一个新的FileReader。

·FileReader(String fileName):在给定从中读取数据的文件名的情况下创建一个新的FileReader。

**BufferedReader类是Reader类的子类，为Reader对象添加字符缓冲器，为数据输入分配内存存储空间，存取数据更为有效。**

构造方法：

·BufferedReader(Reader in):创建一个使用默认大小输入缓冲区的缓冲字符输入流。

·BufferedReader(Reader in,int sz):创建一个使用指定大小输入缓冲区的缓冲字符输入流。

操作方法：

·void close():关闭该流并释放与之关联的所有资源。

·void mark(int readAheadLimit):标记流中的当前为止。

·boolean markSupported();判断此流是否支持mark()操作。

·int read():读取单个字符。

·int read(char[] cbuf,int off,int len):将字符读入数组的某一部分。

·String readLine():读取一个文本行。

·boolean ready():判断此流是否已准备好被读取。

·void reset():将流重置到最新的标记。

·long skip(long n):跳过字符。

**FileWriter:用来写入字符文件的便捷类，可用于写入字符流。**

构造方法：

·FileWriter(File file):根据给定的File对象构造一个FileWriter对象。

·FileWriter(String filename):根据给定的文件名构造一个FileWriter对象。

**BufferedWriter:将文本写入字符输出流，缓冲各个字符，从而提供单个字符、数组和字符串的高效写入。**

 

 

Java输入/输出流体系中常用的流分类（表内容来自java疯狂讲义）

注：下表中带下划线的是抽象类，不能创建对象。粗体部分是节点流，其他就是常用的处理流。

| 流分类           | 使用分类                 | 字节输入流             | 字节输出流           | 字符输入流          | 字符输出流     |
| ---------------- | ------------------------ | ---------------------- | -------------------- | ------------------- | -------------- |
|                  | 抽象基类                 | *InputStream*          | *OutputStream*       | *Reader*            | *Writer*       |
| 节点流           | 访问文件                 | **FileInputStream**    | **FileOutStream**    | **FileReader**      | **FileWriter** |
| 访问数值         | **ByteArrayInputStream** | **ByteArrayOutStream** | **CharArrayReader**  | **CharArrayWriter** |                |
| 访问管道         | **PipedInputStream**     | **PipedOutStream**     | **PipedReader**      | **PipedWriter**     |                |
| 访问字符串       |                          |                        | **StringReader**     | **StringWriter**    |                |
| 处理流           | 缓冲流                   | BufferedInputStream    | BufferedOutputStream | BufferedReader      | BufferedWriter |
| 转换流           |                          |                        | InputStreamReader    | OutputStreamWriter  |                |
| 对象流           | ObjectInputStream        | ObjectOutputStream     |                      |                     |                |
| 抽象基类（过滤） | *FilterInputStream*      | *FilterOutputStream*   | *FilterReader*       | *FilterWriter*      |                |
| 打印流           |                          | PrintStream            |                      | PrintWriter         |                |
| 推回输入流       | PushbackInputStream      |                        | PushbackReader       |                     |                |
| 特殊流           | DataInputStream          | DataOutputStream       |                      |                     |                |

# 4 总结：

1.Java IO是采用的是装饰模式，即采用**处理流**来包装**节点流**的方式，来达到代码通用性。

2.处理流和节点流的区分方法，**节点流**在新建时需要一个数据源（文件、网络）作为参数，而**处理流**需要一个节点流作为参数。

3.**处理流**的作用就是提高代码通用性，编写代码的便捷性，提高性能。

4.**节点流**都是对应抽象基类的实现类，它们都实现了抽象基类的基础读写方法。其中read（）方法如果返回-1，代表已经读到数据源末尾。