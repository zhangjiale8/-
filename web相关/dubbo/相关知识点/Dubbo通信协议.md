​	Dubbo支持的通信协议：dubbo://（推荐）、rmi://、hessian://、http://、webservice://、thrift://、memcached://、redis://、rest://

### 1. Dubbo

`Dubbo`协议为默认协议，采用单一长连接和NIO异步通信，基于`Hessian`作为序列化协议。适合于小数据量（每次请求在100kb以内）大并发的服务调用，以及服务消费者机器数远大于服务提供者机器数的情况。

Dubbo缺省协议不适合传送大数据量的服务，比如传文件，传视频等，除非请求量很低。

- 连接个数：单连接
- 连接方式：长连接
- 传输协议：TCP
- 传输方式：NIO 异步传输
- 序列化：Hessian 二进制序列化
- 适用范围：传入传出参数数据包较小（建议小于100K），消费者比提供者个数多，单一消费者无法压满提供者，尽量不要用 dubbo 协议传输大文件或超大字符串。
- 适用场景：常规远程服务方法调用

### 2. RMI

`RMI`协议采用 JDK 标准的`java.rmi.*`实现，采用阻塞式短连接和JDK标准序列化方式。如果正在使用RMI提供服务给外部访问 ，同时应用里依赖了老的`common-collections`包的情况下，存在反序列化安全风险。

- 连接个数：多连接
- 连接方式：短连接
- 传输协议：TCP
- 传输方式：同步传输
- 序列化：Java 标准二进制序列化
- 适用范围：传入传出参数数据包大小混合，消费者与提供者个数差不多，可传文件。
- 适用场景：常规远程服务方法调用，与原生RMI服务互操作

### 3. Hessian

`Hessian`协议用于集成Hessian的服务，Hessian底层采用HTTP通信，使用Servlet 暴露服务，Dubbo缺省内嵌Jetty作为服务器实现。

Dubbo的Hessian协议可以和原生Hessian服务互操作，提供者用Dubbo的Hessian协议暴露服务，消费者直接用标准Hessian接口调用；或提供者用标准Hessian暴露服务，消费方用Dubbo的Hessian协议调用。

- 连接个数：多连接
- 连接方式：短连接
- 传输协议：HTTP
- 传输方式：同步传输
- 序列化：Hessian二进制序列化
- 适用范围：传入传出参数数据包较大，提供者比消费者个数多，提供者压力较大，可传文件。
- 适用场景：页面传输，文件传输，或与原生Hessian服务互操作

**数据类型：**

- 原始二进制数据
- boolean
- 64-bit date（64 位毫秒值的日期）
- 64-bit double
- 32-bit int
- 64-bit long
- null
- UTF-8编码的string

**递归类型：**

- list for lists and arrays
- map for maps and dictionaries
- object for objects

### 4. HTTP

使用Json序列化，基于HTTP表单的远程调用协议。

- 连接个数：多连接
- 连接方式：短连接
- 传输协议：HTTP
- 传输方式：同步传输
- 序列化：表单序列化
- 适用范围：传入传出参数数据包大小混合，提供者比消费者个数多，可用浏览器查看，可用表单或URL传入参数，暂不支持传文件。
- 适用场景：需同时给应用程序和浏览器JS使用的服务。

### 5. WebService

基于`WebService`的远程调用协议，可以和原生WebService服务互操作，提供者用Dubbo的WebService协议暴露服务，消费者直接用标准WebService接口调用；或提供方用标准WebService暴露服务，消费方用Dubbo的WebService协议调用。

- 连接个数：多连接
- 连接方式：短连接
- 传输协议：HTTP
- 传输方式：同步传输
- 序列化：`SOAP`文本序列化
- 适用场景：系统集成，跨语言调用。

### 6. Thrift

当前Dubbo支持的Thrift协议是在原生协议的基础上添加了一些额外的头信息，比如 `service name`，`magic number`等。Dubbo使用Thrift协议同样需要使用Thrift的`IDL`编译生成相应的Java代码。



作者：窜天猴Plus
链接：https://www.jianshu.com/p/eb4960467e00
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。