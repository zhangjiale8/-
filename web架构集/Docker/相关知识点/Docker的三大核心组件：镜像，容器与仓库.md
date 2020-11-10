`镜像(Image)`，`容器(Container)`，`仓库(Repository)`是我们常说的`Docker`的三大组件，其实我们在上一篇文章[《10分钟快速掌握Docker必备基础知识》](https://juejin.im/post/6844903918372143112)已经有简单地了解过三大组件的知识，但是并没有很详细地讲解，所以在这篇文章中，我们就来一起详细地探索一番吧。

# 1. 镜像(Image)

## 1.1 什么是`Docker`镜像？

​	简单地理解，`Docker镜像`就是一个`Linux`的文件系统(`Root FileSystem`)，这个文件系统里面包含可以运行在`Linux内核`的程序以及相应的数据。

**谈到这里，我们可能需要先补充一点与`Linux`操作系统相关的知识：**

> 一般而言， `Linux`分为两个部分：`Linux内核(Linux Kernel)`与`用户空间`，而真正的`Linux操作系统`，是指`Linux内核`，我们常用的`Ubuntu`,`Centos`等操作系统其实是不同厂商在`Linux内核`基础上添加自己的软件与工具集(`tools`)形成的发布版本(`Linux Distribution`)。

​	因此，我们也可以把镜像看成是上面所说的`用户空间`，当`Docker`通过镜像创建一个容器时，就是将镜像定义好的`用户空间`作为独立隔离的进程运行在宿主机的`Linux内核`之上。

这里要强调一下镜像的两个特征：

1. 镜像是分层(`Layer`)的：即一个镜像可以多个中间层组成，多个镜像可以共享同一中间层，我们也可以通过在镜像添加多一层来生成一个新的镜像。
2. 镜像是只读的(`read-only`)：镜像在构建完成之后，便不可以再修改，而上面我们所说的添加一层构建新的镜像，这中间实际是通过创建一个临时的容器，在容器上增加或删除文件，从而形成新的镜像，因为容器是可以动态改变的。

通过下面的示意图，我可以更好地理解`Docker镜像`与`Linux`的关系：



![img](https://user-gold-cdn.xitu.io/2019/9/7/16d0c272ef8e8adb?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

## 1.2 操作镜像的命令

`Docker`中与镜像操作相关的命令都在`docker image`这条子命令下，通过`docker image --help`这条命令，可以看到`docker image`子命令的详细文档，如下：

```
Usage:  docker image COMMAND

Manage images

Commands:
  build       Build an image from a Dockerfile(构建镜像的命令)
  history     Show the history of an image(显示镜像构建历史过程)
  import      Import the contents from a tarball to create a filesystem image(导入一个由容器导出的镜像)
  inspect     Display detailed information on one or more images(显示一个镜像的详细信息)
  load        Load an image from a tar archive or STDIN(从一个文件或标准输入流中导入镜像)
  ls          List images(查看镜像列表)
  prune       Remove unused images(删除虚悬镜像)
  pull        Pull an image or a repository from a registry(从仓库拉取镜像)
  push        Push an image or a repository to a registry(推送镜像到仓库)
  rm          Remove one or more images(删除镜像)
  save        Save one or more images to a tar archive (streamed to STDOUT by default)(保存镜像到文件)
  tag         Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE(给镜像打标签)
```

## 1.3 获取镜像

​	在安装了`Docker`之后，我们本地并没有任何镜像，当然我们可以自己构建，不过更方便还是从`Docker`官方提供的仓库服务`Docker Hub`上拉取官方或第三方已经构建好的镜像。

拉取镜像可以使用`docker image pull`，其格式如下：

```
docker image pull [OPTIONS] NAME[:TAG|@DIGEST]
```

当然，`docker image pull`有更简洁的用法：如：

```
docker pull [OPTIONS] NAME[:TAG|@DIGEST]
```

​	要拉取镜像，需要指定`Docker Registry`的URL和端口号，默认是`Docker Hub`，另外还需要指定`仓库名`和标签，仓库名和标签唯一确定一个镜像，而标签是可能省略，如果省略，则默认使用`latest`作为标签名，而仓库名则由作者名和软件名组成。

所以，在省略了那么参数后，比如我们想拉取`centos`镜像，可以使用下面简单的命令从`Docker Hub`上拉到：

```
$ docker pull centos
```

## 1.4 查看本地镜像

通过上面的方法我们将镜像拉取到了本地，那要如何查看本地有哪些镜像呢？通过下面的命令我们可以查看本地的全部镜像：

```
$ docker image ls
```

当然`Docker`提供了更简洁的写法，如下：

```
$ docker images
```

### 1.4.1 虚悬镜像

我们知道`Docker`镜像名由`仓库名`和`标签`组成，但有时候我们会看到仓库名和标签皆为`<none>`的镜像，我们称为这种镜像为`虚悬镜像`，如下图所示：



![img](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009250945.png)



`虚悬镜像`一般是当我们使用`docker pull`拉取最新镜像时，生成的新的镜像，所以`仓库名`和`标签`给了新的镜像，旧的镜像仓库和标签则被取消，成为`虚悬镜像`。

我们可以使用下面的语句打印所有的`虚悬镜像`：

```
$ docker image ls -f dangling=true
```

一般的虚悬镜像已经没有什么作用了，所以可以清理掉的，下面的命令可以清除所有的虚悬镜像：

```
$ docker image prune
```

不过，如果我们想保留一些有用的虚拟镜像时，可以使用`docker tag`命令重新给镜像起个仓库名和标签：

```
$ docker tag 621d57f27e93 "test:1.0"
```

## 1.5 镜像导出与导入

​	如果想与别人共享某个镜像，除了从镜像服务仓库中`pull`镜像和把镜像`push`到仓库上去之外，其实我们还可以将本地构建好的镜像直接导出并保存为文件发送给别人，如下：

```
$ docker image save -o /tmp/test_image.tar.gz centos:latest
```

而当你拿到别人导出的镜像文件，你可以使用`docker load`命令把镜像加载到本地的`Docker`镜像列表中，如下：

```
$ docker load < /tmp/test_image.tar.gz
```

## 1.6 删除本地镜像

​	要删除一个或多个本地的镜像，可以使用下面的命令:

```
docker image rm [option] IMAGE1,IMAGE2,...IMAGEn
```

也可以使用更简洁的方式，如：

```
docker rmi  [option]  IMAGE1,IMAGE2,...IMAGEn
```

可以使用镜像的长id、镜像短id、镜像摘要以及镜像名称来删除镜像，如下

```
$ docker rmi f7302e4ab3a8
```

一般更常用镜像的短id,如：

```
$ docker rmi f7302
```

使用镜像的摘要也可以删除镜像，镜像的摘要可以使用下面的命令查询:

```
$ docker image ls --digests
```

当然我们想要清除本地全部镜像时，可以使用下面的命令，不过一般不建议使用。

```
$ docker rmi $(docker images -qa)
```

另外，一般如果镜像已经被使用来创建容器，使用上面的命令删除会报下面的错误，告诉我们该镜像已经被使用，不允许删除。

```
Error response from daemon: conflict: unable to remove repository reference "mysql:5.7" (must force) - container ccd406c07a78 is using its referenced image e1e1680ac726
```

对于已经被用于创建容器的镜像，删除方法有两种，一种是先把容器删除，再删除镜像，另一种则只需要在删除镜像的命令中跟一个`-f`参数便可，如：

```
$ docker rim -f f7302
```

## 1.7 使用docker commit构建镜像

​	上面的例子都是直接使用官方提供的镜像，其实，除了从官方仓库或其他镜像仓库拉取别人构建好的镜像外，我们也可以构建自己的镜像，一般有以下两种构建方式。

使用`docker commit`命令，我们可以将修改过的容器重新提交为一个镜像，如：

```
$ docker commit conntaner_id my-hello:1.0
```

使用这种方式构建的镜像，我们称为**黑箱镜像**，就是一个黑箱子一样，别人并不知道我们对容器做了哪些修改和操作，所以会对其安全性有所质疑。

所以不推荐使用这种方式构建镜像，下面我们介绍一种更加通用且方便的方式。

## 1.8 使用`Dockerfile`构建镜像

​	一般推荐编写`Dockerfile`来构建一种镜像，`Docker Hub`上的镜像都是采用这种方式构建的，采用这种方式的好处就是，我们不用把镜像分发给别人，而只是把`Dockerfile`和相应需要写入镜像的资料发给别人，别人也能自己构建镜像，安全透明。

### 1.8.1 编写一个简单的Got程序

```
package main
import "fmt"

func main(){
    fmt.Println("Hello Go")
}
```

将`Go`程序编译为可执行程序，如：

```
$ go build hello.go
```

### 1.8.2 编写`Dockerfile`文件

下面我们编写一个简单的`Dockerfile`文件，构建自己的第一个镜像，如下：

```
# 从一个空白的镜像开始
FROM stratch
ADD hello /
# 执行
CMD /hello
```

### 1.8.3 开始构建镜像

编写好`Dockerfile`文件后，需要使用`docker build`命令进行构建，`docker build`命令的格式如下：

```
$ docker build [OPTIONS] PATH | URL | -
# 注意最后的点(.)表示当前目录，即Dockerfile所在的目录
$ docker build -t "hello-go:1.0" .
```

上面只是简单演示了使用`Dockerfile`文件如何构建镜像，关于`Dockerfile`，还有许多更加深入地用法，我们之后有机再谈。

# 2. 容器(Container)

​	容器与镜像的关系，就如同面向编程中对象与类之间的关系。

​	因为容器是通过镜像来创建的，所以必须先有镜像才能创建容器，而生成的容器是一个独立于宿主机的隔离进程，并且有属于容器自己的网络和命名空间。

我们前面介绍过，镜像由多个中间层(layer)组成，生成的镜像是只读的，但容器却是可读可写的，这是因为容器是在镜像上面添一层读写层(writer/read layer)来实现的，如下图所示：



![img](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009251010.png)

## 2.1 操作容器的相关命令

```
Usage:  docker container COMMAND

Manage containers

Commands:
  attach      Attach local standard input, output, and error streams to a runnin                                                                                             g container
  commit      Create a new image from a container's changes(把容器保存为镜像)
  cp          Copy files/folders between a container and the local filesystem
  create      Create a new container(创建一个新的容器)
  diff        Inspect changes to files or directories on a container's filesyste                                                                                             m
  exec        Run a command in a running container(在一个运行的容器中执行命令)
  export      Export a container's filesystem as a tar archive
  inspect     Display detailed information on one or more containers
  kill        Kill one or more running containers(杀死一个或多个正在运行的容器)
  logs        Fetch the logs of a container
  ls          List containers(显示本地容器列表)
  pause       Pause all processes within one or more containers
  port        List port mappings or a specific mapping for the container
  prune       Remove all stopped containers
  rename      Rename a container(重命名容器)
  restart     Restart one or more containers(重启一个或多个容器)
  rm          Remove one or more containers(删除一个或多个容器)
  run         Run a command in a new container(运行一个新的容器)
  start       Start one or more stopped containers
  stats       Display a live stream of container(s) resource usage statistics
  stop        Stop one or more running containers(停止一个或多个容器)
  top         Display the running processes of a container
  unpause     Unpause all processes within one or more containers
  update      Update configuration of one or more containers
  wait        Block until one or more containers stop, then print their exit codes
复制代码
```

## 2.2 启动容器

启动容器有几种不同的方式，最常用的方法是使用`docker run`命令可以通过镜像创建一个容器，如：

```
# /bin/bash表示运行容器后要执行的命令
$ docker run -it centos /bin/bash
```

`docker run`命令有一些比较常用的参数，比如容器是一种提供服务的守护进程，那么通常需要开放端口供外部访问，如：

```
$ docker run -p 80:80 nginx
```

也可以为容器指定一个名称，如：

```
$ docker run -p 80:80 --name webserver nginx
```

另外一种则是使用`docker start`命令重新启动已经停止运行的容器，如：

```
# container_id表示容器的id
$ docker start container_id
```

而对于正在运行的容器，也可以通过`docker restart`命令重新启动，如：

```
# container_id表示容器的id
$ docker restart container_id
```

## 2.3 查看本地容器列表

运行容器后，我们可以通过下面的命令查看本地所有容器：

```
$ docker container ls
```

不过`docker container ls`也简洁的写法：

```
$ docker ps
```

上面命令执行结果如下：

```
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS                               NAMES
f4f184f5ffb9        redis:latest        "docker-entrypoint.s…"   6 seconds ago       Up 4 seconds        0.0.0.0:6379->6379/tcp              myredis
f7d970e7d4ce        mysql:5.7           "docker-entrypoint.s…"   7 seconds ago       Up 5 seconds        0.0.0.0:3306->3306/tcp, 33060/tcp   docker-mysql
```

上面的命令只会显示正在运行的容器，如果要显示全部容器，包含退出执行的，可以加参数`-a`，如：

```
$ docker ps -a
```

有时候，我们只想查到容器的id,可以用下面的命令：

```
$ docker ps -aq
```

执行结果

```
f4f184f5ffb9
f7d970e7d4ce
```

## 2.4 停止容器

对于已经不需要的容器，可以使用`docker stop`命令停止其运行，如：

```
$ docker stop container_id1，container_id2...
```

批量停止容器，如：

```
$ docker stop $(docker ps -qa)
```

## 2.5 容器的三种运行模式

概括而言，`Docker`容器大体上有三种运行模式，如下：

### 2.5.1 运行后退出

下面语句创建的容器，在运行后会退出。

```
$ docker run centos echo "hellowrold"
```

### 2.5.2 常驻内存，就是守护进程的模式

如果容器中运行一个守护进程，则容器会一直处于运行状态，如：

```
$ docker run -d -p 80:80 nginx
```

### 2.5.3 交互式

我们也可以在运行容器时，直接与容器交互。

```
$ docker run -it centos /bin/bash
```

## 2.6 删除容器

```
$ docker container rm container_id
```

删除容器的命令也有简洁的写法，如下：

```
$ docker rm container_id
```

也可以像上面批量停止容器一样，我们也可以批量删除容器，如：

```
$ docker rm $(docker ps -qa)
```

## 2.7 进入容器

对于正在运行的容器，我们也可以通过`docker exec`命令再次进入容器，如：

```
$ docker exec -it f4f184f5ffb9 /bin/bash
```

需要指定容器的id或name，上面的命令我们用的是id。

## 2.8 导出容器为镜像

```
$ docker export -o ./image.tar.gz f4f184f5ffb9
```

将容器导出后，我们可以另外一台有安装`Docker`的电脑中将文件包导入成为镜像，如：

```
$ docker import image.tar.gz
```

上面讲的是容器的概念和一些常用的命令，关于容器，还可以设置数据卷和网络空间，这些我们有机会后面再谈。

# 3. 仓库(Repository)

​	仓库(`Repository`)是集中存储镜像的地方，这里有个概念要区分一下，那就是仓库与仓库服务器(`Registry`)是两回事，像我们上面说的`Docker Hub`，就是`Docker`官方提供的一个仓库服务器，不过其实有时候我们不太需要太过区分这两个概念。

## 3.1 公共仓库

​	公共仓库一般是指`Docker Hub`，前面我们已经多次介绍如何从`Docker Hub`获取镜像，除了获取镜像外，我们也可以将自己构建的镜像存放到`Docker Hub`，这样，别人也可以使用我们构建的镜像。

不过要将镜像上传到`Docker Hub`，必须先在`Docker`的官方网站上注册一个账号，注册界面如下，按要求填写必要的信息就可以注册了，很简单的。



![img](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009251019.png)



注册好了之后，可以在本地使用命令登录到`Dokcer Hub`了，过程如下：

```
# 在命令行中输入
$ docker login
```



![img](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009251020.png)



在输入账号密码登录到`Docker Hub`之后，便可以使用`docker push`命令把镜像推送到`Docker Hub`。

```
$ docker push test:1.0
```

## 3.2 私有仓库

​	有时候自己部门内部有一些镜像要共享时，如果直接导出镜像拿给别人又比较麻烦，使用像`Docker Hub`这样的公共仓库又不是很方便，这时候我们可以自己搭建属于自己的私有仓库服务，用于存储和分布我们的镜像。

`Docker`官方提供了`registry`这个镜像，可以用于搭建私有仓库服务，我们把镜像拉到本地之后，用下面命令创建该镜像的容器便可以搭建一个仓库服务，如下：

```
$ docker run -d -p 5000:5000 --restart=always --name registry registry
```

假设我们把一台IP为`192.168.0.100`的服务器作为仓库服务，并运行上面的语句，那么我们可以下面的语句重新构建上面的镜像，如：

```
$ docker build -t "192.168.0.100/hello-go:1.0" .
```

然后使用下面的语句推送到自己的私有仓库服务器：

```
$ docker push 192.168.0.100/hello-word:1.0
```

# 4. 小结

​	镜像是静态的概念，构建完成之后便不能再修改，而容器则是一个动态的概念，使用`Docker`可以简单轻松地创建或删除容器，镜像与容器的关系，就如同面向对象编程中的类与对象的关系，而仓库则是存储和分发镜像的地方。


原文链接：https://juejin.im/post/6844903938030845966
