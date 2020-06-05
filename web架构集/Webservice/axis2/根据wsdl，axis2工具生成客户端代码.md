**根据wsdl，axis2工具生成客户端代码**

**步骤：**

1，下载axis2版本http://axis.apache.org/axis2/java/core/download.html

2，下载完成后解压，设置环境变量，加入AXIS2_HOME=<Axis2客户端安装目录>，path中追加;%AXIS2_HOME%\bin  

3，打开命令行，进入bin目录下，执行命令：

```java
${installdir}>WSDL2Java -uri http://192.168.52.80:8080/test/webservices/XyzqTokenSrv?wsdl -p com.pcm.framework.utils -d adb -s
```

-d 指定数据绑定方式

-p 指定包名

-o 指定代码生成的目录，指定的目录就生成在当前目录下，**windows下指定绝对路径不生效(如：d:/temp)**

或者

创建一个新的XyzqTokenSrv.bat文件内容为：

```java
wsdl2java.bat -uri http://192.168.52.80:8080/test/webservices/XyzqTokenSrv?wsdl
```

生成的代码则存储在axis2-1.6.1\bin\src下，

一般会生成2个文件：XyzqTokenSrvCallbackHandler.java、XyzqTokenSrvStub.java

4，把生成的文件拷贝到工程；

5，代码调用客户端：

```java
XyzqOrgSrvStub stub = new XyzqOrgSrvStub(); 
//获取条数 
XyzqOrgSrvStub.GetPersonCountResponse personCount = stub.getPersonCount(); 
XyzqOrgSrvStub.CountResponse countRes = personCount.get_return(); 
count = countRes.getCount();
```