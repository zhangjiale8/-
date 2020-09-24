# 1、请解释一下什么是Nginx?

​	Nginx是一个web服务器和反向代理服务器，用于HTTP、HTTPS、SMTP、POP3和IMAP协议。

# 2、请列举Nginx的一些特性。

Nginx服务器的特性包括：
	反向代理/L7负载均衡器
	嵌入式Perl解释器
	动态二进制升级
	可用于重新编写URL，具有非常好的PCRE支持

# 3、请列举Nginx和Apache 之间的不同点

![](E:\学习笔记\mylearnnote\web架构集\Nginx\images\202004031585916513147466.jpg)

​	轻量级，同样起 web 服务，Nginx 比 Apache 占用更少的内存及资源。
​	抗并发，Nginx 处理请求是异步非阻塞的，而 Apache 则是阻塞型的，在高并发下 Nginx 能保持低资源低消耗高性能。
最核心的**区别在于 Apache 是同步多进程模型，一个连接对应一个进程；Nginx 是异步的，多个连接（万级别）可以对应一个进程。**
**Nginx 高度模块化的设计，编写模块相对简单**。

# 4、请解释Nginx如何处理HTTP请求。

​	Nginx使用反应器模式。主事件循环等待操作系统发出准备事件的信号，这样数据就可以从套接字读取，在该实例中读取到缓冲区并进行处理。单个线程可以提供数万个并发连接。

# 5、在Nginx中，如何使用未定义的服务器名称来阻止处理请求?

​	只需将请求删除的服务器就可以定义为：
​	Server {

​	listen 80;

​	server_name “ “ ;

​	return 444;
​	}
这里，服务器名被保留为一个空字符串，它将在没有“主机”头字段的情况下匹配请求，而一个特殊的Nginx的非标准代码444被返回，从而终止连接。

# 6、 使用“反向代理服务器”的优点是什么?

​	反向代理服务器可以隐藏源服务器的存在和特征。它充当互联网云和web服务器之间的中间层。这对于安全方面来说是很好的，特别是当您使用web托管服务时。

# 7、请列举Nginx服务器的最佳用途。

​	Nginx服务器的最佳用法是在网络上部署动态HTTP内容，使用SCGI、WSGI应用程序服务器、用于脚本的FastCGI处理程序。它还可以作为负载均衡器。

# 8、请解释Nginx服务器上的Master和Worker进程分别是什么?

​	Master进程：读取及评估配置和维持
​	Worker进程：处理请求

# 9、请解释你如何通过不同于80的端口开启Nginx?

​	为了通过一个不同的端口开启Nginx，你必须进入/etc/Nginx/sites-enabled/，如果这是默认文件，那么你必须打开名为“default”的文件。编辑文件，并放置在你想要的端口：
​	Like server { listen 81; }

# 10、请解释是否有可能将Nginx的错误替换为502错误、503?

​	502 =错误网关
​	503 =服务器超载
有可能，但是您可以确保fastcgi_intercept_errors被设置为ON，并使用错误页面指令。
Location / {fastcgi_pass 127.0.01:9001;fastcgi_intercept_errors on;error_page 502 =503/error_page.html;#…}

# 11、在Nginx中，解释如何在URL中保留双斜线?

​	要在URL中保留双斜线，就必须使用merge_slashes_off;
​	语法:merge_slashes [on/off]
​	默认值: merge_slashes on
​	环境: http，server

# 12、请解释ngx_http_upstream_module的作用是什么?

​	ngx_http_upstream_module用于定义可通过fastcgi传递、proxy传递、uwsgi传递、memcached传递和scgi传递指令来引用的服务器组。

# 13、请解释什么是C10K问题?

​	C10K问题是指无法同时处理大量客户端(10,000)的网络套接字。

# 14、请陈述stub_status和sub_filter指令的作用是什么?

​	Stub_status指令：该指令用于了解Nginx当前状态的当前状态，如当前的活动连接，接受和处理当前读/写/等待连接的总数
​	Sub_filter指令：它用于搜索和替换响应中的内容，并快速修复陈旧的数据

# 15、解释Nginx是否支持将请求压缩到上游?

​	您可以使用Nginx模块gunzip将请求压缩到上游。gunzip模块是一个过滤器，它可以对不支持“gzip”编码方法的客户机或服务器使用“内容编码:gzip”来解压缩响应。

# 16、解释如何在Nginx中获得当前的时间?

​	要获得Nginx的当前时间，必须使用SSI模块、$date_gmt和$date_local的变量。
​	Proxy_set_header THE-TIME $date_gmt;

# 17、用Nginx服务器解释-s的目的是什么?

​	用于运行Nginx -s参数的可执行文件。

# 18、解释如何在Nginx服务器上添加模块?

​	在编译过程中，必须选择Nginx模块，因为Nginx不支持模块的运行时间选择。