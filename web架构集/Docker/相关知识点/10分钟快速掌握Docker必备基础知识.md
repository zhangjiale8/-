`Docker`是时下热门的容器技术，相信作为一名开发人员，你一定听说过或者使用过，很多人会把`Docker`理解为一个轻量级虚拟机，但其实`Docker`与虚拟机(`VM`)是两种不同的计算机虚拟化技术，也有很多人会觉得，有了虚拟机，那为什么还要使用`Docker`呢？

带着心里的一点点疑问，让我们一起来学习`Docker`吧。

# 1. 没有虚拟化技术的原始年代

我们仔细想想，在没有计算虚拟化技术的“远古”年代，如果我们要部署一个应用程序(`Application`)，一般的步骤是怎么样的？

第一步肯定是先要准备一台物理服务器，然后在物理服务器上安装一个操作系统(`Operating System`)，有了操作系统之后，便在操作系统上安装运行我们的应用程序，这个过程可以用下面的图来表示：



![img](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009242309.png)

**物理服务器部署应用示意图**

那么，这种方式有什么问题呢？其实，在物理机上部署应用有以下几个缺点：

- **部署非常慢**：因为我们得先准备硬件服务器，接着还要安装操作系统，然后再部署应用程序，而且应用程序还有很多的依赖软件，所以这个过程是比较慢的。
- **成本非常高**：主要是物理器成本太高，即使是部署一个简单的应用，也需要一台服务器。
- **资源浪费**：如果应用太简单，也容易浪费硬件资源，比如`CPU`和内存
- **迁移和扩展太慢**：如果需要迁移应用，或者扩展应用，都要再准备其他的物理服务器，过程很麻烦，也很慢。

那么有什么办法可以解决这些问题呢？答案便是虚拟化技术。

# 2. 使用虚拟机部署应用程序的年代

## 2.1 什么是虚拟化技术

​	谈到计算机的虚拟化技术，我们直接想到的便是虚拟机，虚拟机允许我们在一台物理计算机模拟出多台机器,简单地理解，虚拟化技术就是在一台物理计算机上，通过中间虚拟软件层`Hypervisor`隔离`CPU`、内存等硬件资源，虚拟出多台虚拟服务器，这样做的话，一台物理服务器便可以安装多个应用程序，达到资源利用的最大化，而且多个应用之间相互隔离，如下图所示：

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009250817.png)



**虚拟机上部署应用示意图**

## 2.2 虚拟机的优点

- 可以把资源分配到不同的虚拟机，达到硬件资源的最大化利用
- 与直接在物理机上部署应用，虚拟机更容易扩展应用。
- 云服务:通过虚拟机虚拟出不同的物理资源，可以快速搭建云服务。

## 2.3 虚拟机的不足之处

​	虚拟机的不足之处在于对物理服务器资源的消耗，当我们在物理服务器创建一台虚拟机时，便需要虚拟出一套硬件并在上面运行完整的操作系统，每台虚拟机都占用许多的服务器资源。

# 3. Docker是什么？

​	相对于虚拟机的笨重，`Docker`则更显得轻量化，因此不会占用太多的系统资源。

​	`Docker`是使用时下很火的`Golang`语言进行开发的，其技术核心是`Linux`内核的`Cgroup`,`Namespace`和`AUFS`类的`Union FS`等技术，这些技术都是`Linux`内核中早已存在很多年的技术，所以严格来说`Docker`并不是一个完全创新的技术，`Docker`通过这些底层的`Linux`技术，对`Linux`进程进行封装隔离，而被隔离的进程也被称为容器，完全独立于宿主机的进程。

所以`Docker`是容器技术的一种实现，也是操作系统层面的一种虚拟化，与虚拟机通过一套硬件再安装操作系统完全不同。

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\16c995c9dc77ca55.png)

## 3.1 Docker与虚拟机之间的比较

`Docker`是在操作系统进程层面的隔离，而虚拟机是在物理资源层面的隔离，两者完全不同，另外，我们也可以通过下面的一个比较，了解两者的根本性差异。

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\16ca2332d360ad57.png)

**容器与虚拟机的比较【摘自《Docker-从入门到实践》】**

从上面的容器与虚拟机的对比中，我们明白了容器技术的优势。

## 3.2 容器解决了开发与生产环境的问题

​	开发环境与生产环境折射的是开发人员与运维人员之间的矛盾，也许我们常常会听到开发人员对运维人员说的这样一句话：“在我的电脑运行没问题，怎么到了你那里就出问题了，肯定是你的问题”，而运维人员则认为是开发人员的问题。

​	开发人员需要在本机安装各种各样的测试环境，因此开发的项目需要软件越多，依赖越多，安装的环境也就越复杂。

​	同样的，运维人员需要为开发人员开发的项目提供生产环境，而运维人员除了应对软件之间的依赖，还需要考虑安装软件与硬件之间的兼容性问题。

​	就是这样，所以我们经常看到开发与运维相互甩锅，怎么解决这个问题呢？

​	容器就是一个不错的解决方案，容器能成为开发与运维之间沟通的语言，因为容器就像一个集装箱一样，提供了软件运行的最小化环境，将应用与其需要的环境一起打包成为镜像，便可以在开发与运维之间沟通与传输。

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\16ca334edabb10ce.png)

# 4. Docker的版本

​	`Docker`分为社区版(`CE`)和企业版(`EE`)两个版本，社区版本可以免费使用，而企业版则需要付费使用，对于我们个人开发者或小企业来说，一般是使用社区版的。

​	`Docker CE`有三个更新频道，分别为`stable`、`test`、`nightly`，`stable`是稳定版本，`test`是测试后的预发布版本，而`nightly`则是开发中准备在下一个版本正式发布的版本，我们可以根据自己的需求下载安装。

# 5. 如何安装Docker?

​	好了，通过前面的介绍，我们应该对`Docker`有了初步的了解，下面开始进入`Docker`的学习之旅了。

​	而学习`Docker`的第一步，从安装`Docker`运行环境开始，我们以`Docker`的社区版本(`CE`)安装为例。

`Docker`社区版本提供了`Mac OS`,`Microsoft Windows`和`Linux`(`Centos`,`Ubuntu`,`Fedora`,`Debian`)等操作系统的安装包，同时也支持在云服务器上的安装，比如`AWS Cloud`。

## 5.1 在Windows系统上安装

### 5.1.1 Docker Desktop for Windows

​	`Docker`为`Windows`提供了一个桌面应用程序管理的安装包(`Docker Desktop for Windows`)，不过对系统有以下几点要求：

1. 必须是`64`位`Windows10`专业版，企业版，教育版，构建在`15063`或更高版本，
2. 在`BIOS`中启用虚拟化。通常，默认情况下启用虚拟化。
3. 至少有`4GB`内存。
4. `CPU`支持`SLAT`。

如果操作系统满足上面的要求，则可以直接下载安装包直接安装，在安装成功后，`Docker`并不会自动启动，需要我们自己启动，我们可以在**开始**菜单中找到`Docker`，如下图，单击启动便可启动。

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\16c7f91f496b6eae.png)

### 5.1.2 Docker Toolbox

​	如果系统达不到上面的要求，比如说你用的是`Windows 7`操作系统，这时候要想使用`Docker`，便需要借助`Docker Toolbox`，`Docker Toolbox`是`Docker`提供的在比较旧的`Mac OS`,`Windows`操作系统上安装`Docker`环境的工具集。

`Docker Toolbox`包括`docker-cli(就是我们在终端使用的docker命令行工具)`，`docker-compose(多容器管理工具)`,`docker-mecahine`，`VirtualBox(虚拟机)`，`Kitematic(docker的GUI管理工具)`。

本质上使用`Docker Toolbox`安装`Docker`环境，实际上是在`VirtualBox`中创建一个`Linux`虚拟机，并在虚拟机上安装`Docker`。

另外，在安装过程中会开启`Windows`的`Hyper-V`模块(`Windows`操作系统实现虚拟化的一种技术)，这里面有个要注意的点是如果开启了`Hyper-V`，则`VirtualBox`不再生效了。

## 5.2 在Mac OS上安装

​	如同`Windows`操作系统一样，`Docker`为`Mac OS`也一样提供一个桌面应用程序(`Docker Desktop for Mac`)，比较简单，从`docker`官网上下载`Dokcer.dmg`安装，打开`Docker.dmg`，如下图所示：

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\16c6c5e3ba672c6c.png)

直接拖动`Docker`图标便完成了安装。

对于比较老的`Mac OS`操作系统，也可以像`Windows`一样，使用`Docker Toolbox`，这点可以参考上面的介绍。

在`Mac OS`上安装完成之后，在`Application`中找到`Docker`图标，双击打开便可以启动`Docker`了，如下：

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\16c9967232f77170.png)

## 5.3 在Linux上安装

在`Linux`操作系统上的安装，主要以`Centos7`为例，其他`Linux`系统的发行版本，如`Ubuntu`，`Debian`，`Fedora`等，可以自行查询`Docker`的[官方文档](https://docs.docker.com/)。

### 5.3.1 删除旧的docker版本

可能有些`Linux`预先安装`Docker`，但一般版本比较旧，所以可以先执行以下代码来删除旧版本的`Docker`。

```c
$ sudo dnf remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-selinux \
                  docker-engine-selinux \
                  docker-engine
```

### 5.3.2 指定安装版本

```c
$ sudo yum-config-manager \
    --add-repo \
    https://download.docker.com/linux/centos/docker-ce.repo
```

### 5.3.3 使用yum安装docker

```c
$ sudo yum install docker-ce docker-ce-cli containerd.io
```

### 5.3.4 启动docker服务器

```c
# 启动docker守护进程
$ sudo systemctl start docker
```

### 5.3.5 测试安装是否成功

通过上面几种方式安装了`Docker`之后，我们可以通过下面的方法来检测安装是否成功。

### 5.3.6 打印docker版本

```c
# 打印docker版本
$ docker version 
```

### 5.3.7 拉取镜像并运行容器

```c
# 拉取hello-world镜像
docker pull hello-world

# 使用hello-world运行一个容器
docker run hello-world
```

运行上面的命令之后，如果有如下图所示的输出结果，则说明安装已经成功了。

![](E:\学习笔记\mylearnnote\web架构集\Docker\images\16c7ed61a6c8637f.png)

# 6 Docker的基本概念

​	镜像(`Image`)、容器(`Container`)与仓库(`Repository`)，这三个是`docker`中最基本也是最核心的概念，对这三个概念的掌握与理解，是学习`docker`的关键。

## 6.1 镜像(Image)

	### 6.1.1 什么是`Docker`的镜像？

​	`Docker`本质上是一个运行在`Linux`操作系统上的应用，而`Linux`操作系统分为内核和用户空间，无论是`Centos`还是`Ubuntu`，都是在启动内核之后，通过挂载`Root`文件系统来提供用户空间的,**而Docker镜像就是一个Root文件系统**。

​	`Docker`镜像是一个特殊的文件系统，提供容器运行时所需的程序、库、资源、配置等文件，另外还包含了一些为运行时准备的一些配置参数（如匿名卷、环境变量、用户等）。

​	镜像是一个静态的概念，不包含任何动态数据，其内容在构建之后也不会被改变。

下面的命令是一些对镜像的基本操作，如下：

### 6.1.2 查看镜像列表

```
# 列出所有镜像
docker image ls
```

由于我们前面已经拉取了`hello-world`镜像，所以会输出下面的内容：

```
REPOSITORY                                      TAG                 IMAGE ID            CREATED             SIZE
hello-world                                     latest              fce289e99eb9        7 months ago        1.84kB
```

下面的命令也一样可以查看本地的镜像列表，而且写法更简洁。

```
# 列表所有镜像
docker images
```

##### 从仓库拉取镜像

前面我们已经演示过使用`docker pull`命令拉取了`hello-world`镜像了，当然使用`docker image pull`命令也是一样的。

一般默认是从`Docker Hub`上拉取镜像的，`Docker Hub`是`Docker`官方提供的镜像仓库服务(`Docker Registry`)，有大量官方或第三方镜像供我们使用，比如我们可以在命令行中输入下面的命令直接拉取一个`Centos`镜像：

```
docker pull centos
```

`docker pull`命令的完整写法如下：

```
docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
复制代码
```

拉取一个镜像，需要指定`Docker Registry`的地址和端口号，默认是`Docker Hub`，还需要指定仓库名和标签，仓库名和标签唯一确定一个镜像，而标签是可能省略，如果省略，则默认使用latest作为标签名，另外，仓库名则由作者名和软件名组成。

那么，我们上面使用`centos`，那是因为省略作者名，则作者名`library`,表示`Docker`官方的镜像，所以上面的命令等同于：

```
docker pull library/centos:latest
```

因此，如果拉取非官方的第三方镜像，则需要指定完整仓库名，如下：

```
docker pull mysql/mysql-server:latest
```

### 6.1.3 运行镜像

使用`docker run`命令，可以通过镜像创建一个容器，如下：

```
docker run -it centos /bin/bash
```

### 6.1.4 删除镜像

当本地有些镜像我们不需要时，那我们也可以删除该镜像，以节省存储空间，不过要注意，如果有使用该镜像创建的容器未删除，则不允许删除镜像。

```
# image_name表示镜像名，image_id表示镜像id
dockere image rm image_name/image_id
```

删除镜像的快捷命令：

```
docker rmi image_name/image_id
```

好了，关于`Docker`镜像的相关知识，我们就简单地介绍到这里，有机会的话，我们单独写一篇文章来谈谈，特别构建`Docker`镜像部分的相关知识，有必要深入再学习一下。

## 6.2 容器(Container)

`Docker`的镜像是用于生成容器的模板，镜像分层的，镜像与容器的关系，就是面向对象编程中类与对象的关系，我们定好每一个类，然后使用类创建对象，对应到`Docker`的使用上，则是构建好每一个镜像，然后使用镜像创建我们需要的容器。

### 6.2.1 启动和停止容器

启动容器有两种方式，一种是我们前面已经介绍过的，使用`docker run`命令通过镜像创建一个全新的容器，如下：

```
docker run hello-world
```

另外一种启动容器的方式就是启动一个已经停止运行的容器：

```
# container_id表示容器的id
docker start container_id
```

要停止正在运行的容器可以使用`docker container stop`或`docker stop`命令，如下：

```
# container_id表示容器的id
docker stop container_id
```

### 6.2.2 查看所有容器

如果要查看本地所有的容器，可以使用`docker container ls`命令：

```
# 查看所有容器
docker container ls
```

查看所有容器也有简洁的写法，如下：

```
# 查看所有容器
docker ps
```

### 6.2.3 删除容器

我们也可以使用`docker container rm`命令，或简洁的写法`docker rm`命令来删除容器，不过不允许删除正在运行的容器，因此如果要删除的话，就必须先停止容器，

```
# container_id表示容器id,通过docker ps可以看到容器id
$ docker rm container_id
```

当我们需要批量删除所有容器，可以用下面的命令：

```
# 删除所有容器
docker rm $(docker ps -q)
复制代码
# 删除所有退出的容器
docker container prune
```

### 6.2.4 进入容器

```
# 进入容器,container_id表示容器的id,command表示linux命令,如/bin/bash
docker exec -it container_id command
```

## 6.3 仓库(Repository)

​	在前面的例子中，我们使用两种方式构建镜像，构建完成之后，可以在本地运行镜像，生成容器，但如果在更多的服务器运行镜像呢？很明显，这时候我们需要一个可以让我们集中存储和分发镜像的服务，就像Github可以让我们自己存储和分发代码一样。

`Docker Hub`就是Docker提供用于存储和分布镜像的官方`Docker Registry`，也是默认的`Registry`，其网址为`https://hub.docker.com`，前面我们使用`docker pull`命令便从`Docker Hub`上拉取镜像。

`Docker Hub`有很多官方或其他开发提供的高质量镜像供我们使用，当然，如果要将我们自己构建的镜像上传到`Docker Hub`上，我们需要在`Docker Hub`上注册一个账号，然后把自己在本地构建的镜像发送到`Docker Hub`的仓库当中，`Docker Registry`包含很多个仓库，每个仓库对应多个标签，不同标签对应一个软件的不同版本。

# 7 Docker的组成与架构

在安装好并启动了`Docker`之后，我们可以使用在命令行中使用`docker`命令操作docker，比如我们使用如下命令打印`docker`的版本信息。

```
docker verion
```

其结果如下：



![img](https://user-gold-cdn.xitu.io/2019/8/11/16c7fb252c997020?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)



从上面的图中，我们看到打出了两个部分的信息：`Client`和`Server`。

这是因为`Docker`跟大部分服务端软件一样(如`MySQL`)，都是使用`C/S`的架构模型，也就是通过客户端调用服务器，只是我们现在刚好服务端和客户端都在同一台机器上而已。

因此，我们可以使用下面的图来表示`Docker`的架构，`DOCKER_HOST`是`Docker server`，而Clinet便是我们在命令中使用`docker`命令。



![img](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009250933.png)



#### Docker Engine

`docker server`为客户端提供了容器、镜像、数据卷、网络管理等功能，其实，这些功能都是由`Docker Engine`来实现的。

1. `dockerd`:服务器守护进程。
2. `Client docker Cli`：命令行接口
3. `REST API`：除了cli命令行接口，也可以通过`REST API`调用`docker`

下面是`Docker Engine`的示例图：



![img](E:\学习笔记\mylearnnote\web架构集\Docker\images\202009250934.png)

# 8.小结

​	作为一名开发人员，在学习或开发过程中，总需要安装各种各样的开发环境，另外，一个技术团队在开发项目的过程，也常常需要统一开发环境，这样可能避免环境不一致引发的一些问题。

​	虽然使用虚拟机可以解决上面的问题，但虚拟机太重，对宿主机资源消耗太大，而作为轻量级容器技术，`Docker`可以简单轻松地解决上述问题，让开发环境的安装以及应用的部署变得非常简单，而且使用`Docker`，比在虚拟机安装操作系统，要简单得多。





原文链接：https://juejin.im/post/6844903918372143112