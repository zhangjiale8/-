# 简介

这两天工作中要用到Activiti，就简单学习了下，做一个记录，好脑子不如烂笔头，记下来牢靠些，来吧，话不多说，一个字：**干**。

# Activiti是什么，为什么要用它

Activiti项目是一项新的基于Apache许可的开源BPM平台，从基础开始构建，旨在提供支持新的BPMN 2.0标准，包括支持对象管理组（OMG），可以定义流程、执行流程并以不同方式对其实现运行。（巴拉巴拉一大堆，其实我也没听懂）。

还是用自己的化总结下吧。

其实就是一个工作审批流，在我们日常生活中，审批是非常常见的，加班打车，需要把发票贴到报销单，然后提交给组长，组长审批完毕，提交给部门主管，部门主管审核完毕，给财务部门，财务部分审核完毕，给你银行卡打钱，一个审批的流程结束了。

其实可以理解为审批流就是一个载体（火车），它不管你是什么业务数据（人还是货物），它能驱动业务向前发展（目的地）。

# Activiti 生成表

既然它能管理我们的审批，肯定要存储数据，数据库表是必不可少的，所以我们先建下表。
 新建一个SpringBoot 项目

#### Pom.xml 文件

```
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.glj</groupId>
  <artifactId>activiti-create-table</artifactId>
  <version>0.0.1-SNAPSHOT</version>
  <packaging>jar</packaging>
  
  <parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>2.0.4.RELEASE</version>
    <relativePath/> <!-- lookup parent from repository -->
</parent>
  
  
 <dependencies>
 
 <dependency>
    <groupId>org.activiti</groupId>
    <artifactId>activiti-spring-boot-starter-basic</artifactId>
    <version>6.0.0</version>
</dependency>

<!-- mybatis -->
<dependency>
    <groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>1.3.2</version>
</dependency>

<!--swagger --> 
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger2</artifactId>
    <version>2.8.0</version>
</dependency>
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger-ui</artifactId>
    <version>2.8.0</version>
</dependency>
<!-- mysql -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <scope>runtime</scope>
</dependency>

 </dependencies>
</project>
```

#### application.properties

```
server.port=8080
spring.datasource.driver-class-name=com.mysql.jdbc.Driver
spring.datasource.url=jdbc:mysql://localhost:3306/db_activiti?autoReconnect=true&characterEncoding=utf8&useSSL=false
spring.datasource.username=root
spring.datasource.password=root
mybatis.mapper-locations=classpath:mapper/*.xml
mybatis.type-aliases-package=com.glj.model
spring.activiti.check-process-definitions=false
```

#### 项目入口类

```
package com.glj;

import org.activiti.spring.boot.SecurityAutoConfiguration;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@ComponentScan(basePackages = {"com.glj"})
@MapperScan(basePackages = {"com.glj"})
@SpringBootApplication(exclude = SecurityAutoConfiguration.class)
public class ActivitiApplication {

    public static void main(String[] args) {
        SpringApplication.run(ActivitiApplication.class, args);

    }

}
```

运行后，生成28张表

![img](//upload-images.jianshu.io/upload_images/16004177-9e4bbba5f396e133.png?imageMogr2/auto-orient/strip|imageView2/2/w/300/format/webp)

image.png

#### 表说明

表名默认以“ACT_”开头,并且表名的第二部分用两个字母表明表的用例，而这个用例也基本上跟Service API匹配。

ACT_GE_* : “GE”代表“General”（通用），用在各种情况下；

ACT_HI_* : “HI”代表“History”（历史），这些表中保存的都是历史数据，比如执行过的流程实例、变量、任务，等等。Activit默认提供了4种历史级别：

ACT_ID_* : “ID”代表“Identity”（身份），这些表中保存的都是身份信息，如用户和组以及两者之间的关系。如果Activiti被集成在某一系统当中的话，这些表可以不用，可以直接使用现有系统中的用户或组信息；

ACT_RE_* : “RE”代表“Repository”（仓库），这些表中保存一些‘静态’信息，如流程定义和流程资源（如图片、规则等）；

ACT_RU_* : “RU”代表“Runtime”（运行时），这些表中保存一些流程实例、用户任务、变量等的运行时数据。Activiti只保存流程实例在执行过程中的运行时数据，并且当流程结束后会立即移除这些数据，这是为了保证运行时表尽量的小并运行的足够快；

| 表分类       | 表名称                | 表含义                        |
| ------------ | --------------------- | ----------------------------- |
|              | act_evt_log           | 事件处理日志表                |
| 一般数据     | act_ge_bytearray      | 通用的流程定义和流程资源      |
|              | act_ge_property       | 系统相关属性                  |
| 流程历史记录 | act_hi_actinst        | 历史的流程实例                |
|              | act_hi_attachment     | 历史的流程附件                |
|              | act_hi_comment        | 历史的说明性信息              |
|              | act_hi_detail         | 历史的流程运行中的细节信息    |
|              | act_hi_identitylink   | 历史的流程运行过程中用户关系  |
|              | act_hi_procinst       | 历史的流程实例                |
|              | act_hi_taskinst       | 历史的任务实例                |
|              | act_hi_varinst        | 历史的流程运行中的变量信息    |
| 用户用户组表 | act_id_group          | 身份信息-组信息               |
|              | act_id_info           | 身份信息-组信息               |
|              | act_id_membership     | 身份信息-用户和组关系的中间表 |
|              | act_id_user           | 身份信息-用户信息             |
|              | act_procdef_info      | 死信任务                      |
| 流程定义表   | act_re_deployment     | 部署单元信息                  |
|              | act_re_model          | 模型信息                      |
|              | act_re_procdef        | 已部署的流程定义              |
| 运行实例表   | act_ru_deadletter_job | 执行失败任务表                |
|              | act_ru_event_subscr   | 运行时事件                    |
|              | act_ru_execution      | 运行时流程执行实例            |
|              | act_ru_identitylink   | 运行时用户关系信息            |
|              | act_ru_job            | 运行时作业                    |
|              | act_ru_suspended_job  | 运行时暂停任务                |
|              | act_ru_task           | 运行时任务                    |
|              | act_ru_timer_job      | 运行时定时任务                |
|              | act_ru_variable       | 运行时变量表                  |

具体的表结构及详细介绍可参考[
 Activiti数据库表结构](https://links.jianshu.com/go?to=https%3A%2F%2Fblog.csdn.net%2Fhj7jay%2Farticle%2Fdetails%2F51302829) 里面有详细的每个表介绍。

#### 流程概念和术语

(1) 一个ProcessDefinition代表的业务流程。它用于定义流程中不同步骤的结构和行为。

(2) 部署流程定义意味着将流程定义加载到Activiti数据库中。

(3) 流程定义主要由BPMN 2.0标准定义,也可以使用Java代码定义它们，定义的所有术语也可用作Java类。

(4) 一旦我们开始运行流程定义，就可以称为一个流程process。

(5) processInstance是ProcessDefinition一个执行实例。

(6) 一个StartEvent与每一个业务流程有关，它表示该流程的切入点，同样，有一个EndEvent表示流程的结束。我们可以定义这些事件的条件。

(7) 开始和结束之间的所有步骤（或元素）称为任务，任务可以是各种类型的。最常用的任务是UserTasks和ServiceTasks。

顾名思义，UserTasks需要由用户手动执行，另一方面，ServiceTasks配置了一段代码，每当执行到达这段代码时，代码将被执行。

SequenceFlows用来连接任务，我们可以通过它将源元素和目标元素连接起来定义一个SequenceFlows；同样，我们还可以在SequenceFlow上定义条件，这样能在流程中创建条件路径。

有了流程定义，我们可以使用Activiti提供的服务功能进行流程运行。

#### Activiti提供的服务

RepositoryService帮助我们实现流程定义的部署。此服务会处理与流程定义相关的静态数据。
 RuntimeService管理 ProcessInstances（当前正在运行的流程）以及流程变量
 TaskService会跟踪 UserTasks，需要由用户手动执行的任务是Activiti API的核心。我们可以使用此服务创建任务，声明并完成任务，分配任务的受让人等。
 FormService是一项可选服务，它用于定义中开始表单和任务表单。
 IdentityService管理用户和组。
 HistoryService会跟踪Activiti Engine的历史记录。我们还可以设置不同的历史级别。
 ManagementService与元数据相关，在创建应用程序时通常不需要。
 DynamicBpmnService帮助我们在不重新部署的情况下更改流程中的任何内容。

# IDE 安装插件

由于我用的是eclipse，所以目前只说下再eclipse中是怎么添加Activiti插件的。
 打开Eclipse -> Help -> Install New SoftWare-> Add
 然后按照如下对话框输入：
 Name:   Activiti Designer
 Location: [http://activiti.org/designer/update/](https://links.jianshu.com/go?to=http%3A%2F%2Factiviti.org%2Fdesigner%2Fupdate%2F)

![img](//upload-images.jianshu.io/upload_images/16004177-cc3bd783bb407e1c.png?imageMogr2/auto-orient/strip|imageView2/2/w/489/format/webp)

image.png

输入完成后，单击OK按钮等待下载完成后安装。安装完成后在菜单选项中会出现activiti的目录选项。

 

![img](//upload-images.jianshu.io/upload_images/16004177-3895c9ac143946db.png?imageMogr2/auto-orient/strip|imageView2/2/w/507/format/webp)

image.png

#### 设置eclipse activit插件的画流程图 选项

打开菜单Windows --> Preferences --> Activiti -->Save 下流程图片的生成方式

 

![img](//upload-images.jianshu.io/upload_images/16004177-9de75b96777fd51e.png?imageMogr2/auto-orient/strip|imageView2/2/w/804/format/webp)

image.png

 

勾选上Create process definition image when saving  the diagram操作，勾选上这个操作后在画流程图后保存eclipse会自动生成对应的流程图片。

# 结束语

现在表也建立好了，开发环境也好了，接下来就是设计审批模板，然后就可以发起一个审批任务了

 

 

原文链接：<https://www.jianshu.com/p/aadbfd0e37b0> 

 

 