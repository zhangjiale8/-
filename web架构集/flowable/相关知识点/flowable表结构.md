# 1 flowable 数据库表（一共70张表）

## 1.1 Flowable数据库表命名规则

### 1.1.1  ACT_RE_*  

RE表示repository（存储）。

RepositoryService接口操作的表。带此前缀的表包含的是静态信息，如，流程定义，流程的资源（图片，规则等）。

### 1.1.2  ACT_RU_* 

RU表示runtime。（15张表）这是运行时的表存储着流程变量，用户任务，变量，职责（job）等运行时的数据。

flowable只存储实例执行期间的运行时数据，当流程实例结束时，将删除这些记录。这就保证了这些运行时的表小且快。

### 1.1.3  ACT_ID_* 

 ID表示identity(组织机构)。（9张表）这些表包含标识的信息，如用户，用户组，等等。

### 1.1.4  ACT_HI_* 

HI表示history。（10张表）就是这些表包含着历史的相关数据，如结束的流程实例，变量，任务，等等。

### 1.1.5  ACT_GE_* 

普通数据。（2张表）各种情况都使用的数据。

### 1.1.6   *_ DATABASECHANGELOG  

liuquibase的log表（4张表）

### 1.1.7  *_DATABASECHANGELOGLOCK  

liuquibase的log表（4张表）

* none: 不保存任何历史记录，可以提高系统性能；

* activity：保存所有的流程实例、任务、活动信息；

* audit：也是Activiti的默认级别，保存所有的流程实例、任务、活动、表单属性； 

* full：最完整的历史记录，除了包含audit级别的信息之外还能保存详细，例如：流程变量。

# 2 数据库表结构(经典的34张表)

## 2.1 通用数据库



| **数据表**       | **描述**                                             |
| ---------------- | ---------------------------------------------------- |
| ACT_GE_PROPERTY  | 属性表(保存流程引擎的kv键值属性)--PropertyEntityImpl |
| ACT_GE_BTYEARRAY | 资源表(存储流程定义相关的资源)--ByteArrayEntityImpl  |



## 2.2 **流程定义存储表**



| **数据表**        | **描述**                                                |
| ----------------- | ------------------------------------------------------- |
| ACT_RE_DEPLOYMENT | 流程部署表--DeploymentEntityImpl                        |
| ACT_RE_PROCDEF    | 流程定义信息表--ProcessDefinitionEntityImpl             |
| ACT_RE_MODEL      | 模型信息表(用于Web设计器)--ModelEntityImpl              |
| ACT_PROCDEF_INFO  | 流程定义动态改变信息表--ProcessDefinitionInfoEntityImpl |



## 2.3 **身份数据表**



| **据表**            | **描述**                               |
| ------------------- | -------------------------------------- |
| ACT_ID_USER         | 用户基本信息表--UserEntityImpl         |
| ACT_ID_INFO         | 用户扩展表--IdentityInfoEntityImpl     |
| ACT_ID_GROUP        | 群组表(用于Web设计器)--GroupEntityImpl |
| ACT_ID_MEMBERSHIP   | 用户与群主关系表--MemberShipEntityImpl |
| ACT_ID_BYTEARRAY    | 二进制数据表(flowable)--               |
| ACT_ID_PRIV         | 权限表(flowable)--                     |
| ACT_ID_PRIV_MAPPING | 用户或组权限关系表(flowable)--         |
| ACT_ID_PROPERTY     | 属性表(flowable)--                     |
| ACT_ID_TOKEN        | 系统登录日志表(flowable)--             |



## 2.4 **运行时流程数据表**



| **数据表**            | **描述**                                  |
| --------------------- | ----------------------------------------- |
| ACT_RU_EXECUTION      | 流程实例与分支执行表--ExecutionEntityImpl |
| ACT_RU_TASK           | 用户任务表--TaskEntityImpl                |
| ACT_RU_VARIABLE       | 变量信息--VariableInstanceEntityImpl      |
| ACT_RU_IDENTITYLINK   | 参与者相关信息表--IdentityLinkEntityImpl  |
| ACT_RU_EVENT_SUBSCR   | 事件订阅表--EventSubscriptionEntityImpl   |
| ACT_RU_JOB            | 作业表--JobEntityImpl                     |
| ACT_RU_TIMER_JOB      | 定时器表--TimerJobEntityImpl              |
| ACT_RU_SUSPENDED_JOB  | 暂停作业表--SuspendedJobEntityImpl        |
| ACT_RU_DEADLETTER_JOB | 死信表--DeadLetterJobEntityImpl           |
| ACT_RU_HISTORY_JOB    | 历史作业表(flowable)--                    |



## 2.5 **历史流程数据表**

| **数据表**          | **描述**                                                     |
| ------------------- | ------------------------------------------------------------ |
| ACT_HI_PROCINST     | 历史流程实例表--HistoricProcessInstanceEntityImpl            |
| ACT_HI_ACTINST      | 历史节点信息表--HistoricActivityInstanceEntityImpl           |
| ACT_HI_TASKINST     | 历史任务表--HistoricTaskInstanceEntityImpl（只记录usertask内容） |
| ACT_HI_VARINST      | 历史变量--HistoricVariableInstanceEntityImpl                 |
| ACT_HI_IDENTITYLINK | 历史参与者表--HistoricIdentityLinkEntityImpl                 |
| ACT_HI_DETAIL       | 历史的流程运行中的细节信息--HistoricDetailEntityImpl         |
| ACT_HI_ATTACHMENT   | 附件表--AttachmentEntityImpl                                 |
| ACT_HI_COMMENT      | 评论表--CommentEntityImpl                                    |
| ACT_EVT_LOG         | 事件日志表--EventLogEntryEntityImpl                          |



# 3 核心表

## 3.1 部署内容表：act_ge_bytearray

act_ge_bytearray（二进制文件）

| 字段           | 字段名称           | 字段默认值 | 是否允许为空 | 数据类型 | 字段长度   | 键                | 备注                                                         |
| -------------- | ------------------ | ---------- | ------------ | -------- | ---------- | ----------------- | ------------------------------------------------------------ |
| ID_            | 主键               |            | NO           | varchar  | 64         | PRI               |                                                              |
| REV_           | 版本号             | NULL       | YES          | int      | NULL       |                   | version                                                      |
| NAME_          | 名称               | NULL       | YES          | varchar  | 255        |                   | 部署的文件名称，如：mail.bpmn、mail.png 、mail.bpmn20.xml    |
| DEPLOYMENT_ID_ | 部署ID             | NULL       | YES          | varchar  | 64         | ACT_RE_DEPLOYMENT |                                                              |
| BYTES_         | 字节（二进制数据） | NULL       | YES          | longblob | 4294967295 |                   |                                                              |
| GENERATED_     | 是否系统生成       | NULL       | YES          | tinyint  | NULL       |                   | 0为用户上传， 1为系统自动生 成， 比如系统会 自动根据xml生 成png |



## 3.2 部署ID表：act_re_deployment



| **字段**     | **字段名称** | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键** | **备注** |
| ------------ | ------------ | -------------- | ---------------- | ------------ | ------------ | ------ | -------- |
| ID_          | 主键         |                | NO               | varchar      | 64           | PRI    |          |
| NAME_        | 名称         | NULL           | YES              | varchar      | 255          |        |          |
| CATEGORY_    | 分类         | NULL           | YES              | varchar      | 255          |        |          |
| TENANT_ID_   | 租户ID       |                | YES              | varchar      | 255          |        |          |
| DEPLOY_TIME_ | 部署时间     | NULL           | YES              | timestamp    | NULL         |        |          |

注：

1.　部署流程定义时需要被持久化保存下来的信息。

## 3.3 流程表：act_re_procdef



| **字段**                | **字段名称**     | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键** | **备注**                         |
| ----------------------- | ---------------- | -------------- | ---------------- | ------------ | ------------ | ------ | -------------------------------- |
| ID_                     | 主键             | NULL           | NO               | varchar      | 64           | PRI    |                                  |
| REV_                    | 版本号           | NULL           | YES              | int          | NULL         |        | version                          |
| CATEGORY_               | 分类             | NULL           | YES              | varchar      | 255          |        | 流程定义的Namespace就是类别      |
| NAME_                   | 名称             | NULL           | YES              | varchar      | 255          |        |                                  |
| KEY_                    | 标识             | NULL           | NO               | varchar      | 255          | MUL    |                                  |
| VERSION_                | 版本             | NULL           | NO               | int          | NULL         |        |                                  |
| DEPLOYMENT_ID_          | 部署ID           | NULL           | YES              | varchar      | 64           |        |                                  |
| RESOURCE_NAME_          | 资源名称         | NULL           | YES              | varchar      | 4000         |        | 流程bpmn文件名称                 |
| DGRM_RESOURCE_NAME_     | 图片资源名称     | NULL           | YES              | varchar      | 4000         |        |                                  |
| DESCRIPTION_            | 描述             | NULL           | YES              | varchar      | 4000         |        |                                  |
| HAS_START_FORM_KEY_     | 拥有开始表单标识 | NULL           | YES              | tinyint      | NULL         |        | start节点是否存在formKey 0否 1是 |
| HAS_GRAPHICAL_NOTATION_ | 拥有图形信息     | NULL           | YES              | tinyint      | NULL         |        |                                  |
| SUSPENSION_STATE_       | 挂起状态         | NULL           | YES              | int          | NULL         |        | 暂停状态 1激活 2暂停             |
| TENANT_ID_              | 租户ID           |                | YES              | varchar      | 255          |        |                                  |

注：
1.　业务流程定义数据表。此表和ACT_RE_DEPLOYMENT是多对一的关系，即，一个部署的bar包里可能包含多个流程定义文件，每个流程定义文件都会有一条记录在ACT_REPROCDEF表内，每个流程定义的数据，都会对于ACT_GE_BYTEARRAY表内的一个资源文件和PNG图片文件。和ACT_GE_BYTEARRAY的关联是通过程序用ACT_GE_BYTEARRAY.NAME与ACT_RE_PROCDEF.NAME_完成的，在数据库表结构中没有体现。


总结：

![img](https://img-blog.csdnimg.cn/20190812161051145.png)

流程文件部署主要涉及到3个表，分别是：ACT_GE_BYTEARRAY、ACT_RE_DEPLOYMENT、ACT_RE_PROCDEF。主要完成“部署包”-->“流程定义文件”-->“所有包内文件”的解析部署关系。从表结构中可以看出，流程定义的元素需要每次从数据库加载并解析，因为流程定义的元素没有转化成数据库表来完成，当然流程元素解析后是放在缓存中的。

## 3.4  **历史节点表：act_hi_actinst**



| **字段**           | **字段名称**         | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键** | **备注**                                |
| ------------------ | -------------------- | -------------- | ---------------- | ------------ | ------------ | ------ | --------------------------------------- |
| ID_                | 主键                 | NULL           | NO               | varchar      | 64           | PRI    |                                         |
| PROC_DEF_ID_       | 流程定义ID           | NULL           | NO               | varchar      | 64           |        |                                         |
| PROC_INST_ID_      | 流程实例ID           | NULL           | NO               | varchar      | 64           | MUL    |                                         |
| EXECUTION_ID_      | 执行实例ID           | NULL           | YES              | varchar      | 64           |        |                                         |
| ACT_ID_            | 节点ID               | NULL           | NO               | varchar      | 255          |        |                                         |
| TASK_ID_           | 任务ID               | NULL           | YES              | varchar      | 64           |        | 任务实例ID 其他节点类型实例ID在这里为空 |
| CALL_PROC_INST_ID_ | 调用外部的流程实例ID | NULL           | YES              | varchar      | 64           |        |                                         |
| ACT_NAME_          | 节点名称             | NULL           | YES              | varchar      | 255          |        |                                         |
| ACT_TYPE_          | 节点类型             | NULL           | NO               | varchar      | 255          |        | 如startEvent、userTask                  |
| ASSIGNEE_          | 签收人               | NULL           | YES              | varchar      | 255          |        | 经办人                                  |
| START_TIME_        | 开始时间             | NULL           | NO               | datetime     | NULL         | MUL    |                                         |
| END_TIME_          | 结束时间             | NULL           | YES              | datetime     | NULL         | MUL    |                                         |
| DURATION_          | 耗时                 | NULL           | YES              | bigint       | NULL         |        | 毫秒值                                  |
| TENANT_ID_         | 多租户               |                | YES              | varchar      | 255          |        |                                         |

注：

1.　历史活动信息。这里记录流程流转过的所有节点，与HI_TASKINST不同的是，taskinst只记录usertask内容。
2.　TENANT_ID 是后续才加入的多租户

## 3.5 **历史任务流程实例信息** ：act_hi_taskinst



| **字段**        | **字段名称**   | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键** | **备注**                               |
| --------------- | -------------- | -------------- | ---------------- | ------------ | ------------ | ------ | -------------------------------------- |
| ID_             | 主键           | NULL           | NO               | varchar      | 64           | PRI    |                                        |
| PROC_DEF_ID_    | 流程实例ID     | NULL           | YES              | varchar      | 64           |        |                                        |
| TASK_DEF_KEY_   | 任务节点定义ID | NULL           | YES              | varchar      | 255          |        | 任务定义标识（环节ID）                 |
| PROC_INST_ID_   | 流程实例ID     | NULL           | YES              | varchar      | 64           | MUL    |                                        |
| EXECUTION_ID_   | 执行实例ID     | NULL           | YES              | varchar      | 64           |        |                                        |
| NAME_           | 任务名称       | NULL           | YES              | varchar      | 255          |        |                                        |
| PARENT_TASK_ID_ | 父任务节点ID   | NULL           | YES              | varchar      | 64           |        |                                        |
| DESCRIPTION_    | 描述           | NULL           | YES              | varchar      | 4000         |        |                                        |
| OWNER_          | 被代理人       | NULL           | YES              | varchar      | 255          |        | 委托人（默认为空，只有在委托时才有值） |
| ASSIGNEE_       | 经办人         | NULL           | YES              | varchar      | 255          |        |                                        |
| START_TIME_     | 开始时间       | NULL           | NO               | datetime     | NULL         |        |                                        |
| CLAIM_TIME_     | 签收时间       | NULL           | YES              | datetime     | NULL         |        |                                        |
| END_TIME_       | 结束时间       | NULL           | YES              | datetime     | NULL         |        |                                        |
| DURATION_       | 耗时           | NULL           | YES              | bigint       | NULL         |        |                                        |
| DELETE_REASON_  | 删除原因       | NULL           | YES              | varchar      | 4000         |        | 删除原因(completed,deleted)            |
| PRIORITY_       | 优先级         | NULL           | YES              | int          | NULL         |        |                                        |
| DUE_DATE_       | 截止时间       | NULL           | YES              | datetime     | NULL         |        | 过期时间，表明任务应在多长时间内完成   |
| FORM_KEY_       | FORM表单的KEY  | NULL           | YES              | varchar      | 255          |        | desinger节点定义的form_key属性         |
| CATEGORY_       | 分类           | NULL           | YES              | varchar      | 255          |        |                                        |
| TENANT_ID_      | 租户ID         |                | YES              | varchar      | 255          |        |                                        |

注：

1.　历史任务实例表
2.　存放已经办理的任务。
3.　CATEGORY和TNANT_ID是后续版本才加进来的。

 注意：**act_hi_taskinst**只记录usertask内容。

## 3.6  **流程变量数据表：act_ru_variable**



| **字段**      | **字段名称** | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键**                  | **备注**                                                     |
| ------------- | ------------ | -------------- | ---------------- | ------------ | ------------ | ----------------------- | ------------------------------------------------------------ |
| ID_           | 主键         | NULL           | NO               | varchar      | 64           | PRI                     |                                                              |
| REV_          | 版本号       | NULL           | YES              | int          | NULL         |                         | version                                                      |
| TYPE_         | 类型         | NULL           | NO               | varchar      | 255          |                         | 见备注                                                       |
| NAME_         | 名称         | NULL           | NO               | varchar      | 255          |                         |                                                              |
| EXECUTION_ID_ | 执行实例ID   | NULL           | YES              | varchar      | 64           | MUL（ACT_RU_EXECUTION） |                                                              |
| PROC_INST_ID_ | 流程实例ID   | NULL           | YES              | varchar      | 64           | MUL（ACT_RU_EXECUTION） |                                                              |
| TASK_ID_      | 任务ID       | NULL           | YES              | varchar      | 64           | MUL（ACT_RU_TASK）      |                                                              |
| BYTEARRAY_ID_ | 资源ID       | NULL           | YES              | varchar      | 64           | MUL（ACT_GE_BYTEARRAY） |                                                              |
| DOUBLE_       | 浮点值       | NULL           | YES              | double       | NULL         |                         | 存储变量类型为Double                                         |
| LONG_         | 长整型       | NULL           | YES              | bigint       | NULL         |                         | 存储变量类型为long                                           |
| TEXT_         | 文本值       | NULL           | YES              | varchar      | 4000         |                         | 存储变量值类型为String 如此处存储持久化对象时，值jpa对象的class |
| TEXT2_        | 文本值       | NULL           | YES              | varchar      | 4000         |                         | 此处存储的是JPA持久化对象时，才会有值。此值为对象ID          |

注：
1.运行时流程变量数据表。
2.类型：jpa-entity、boolean、bytes、serializable(可序列化)、自定义type(根据你自身配置)、

 CustomVariableType、date、double、integer、long、null、short、string

## 3.7  **历史变量表：act_hi_varinst**



| **字段**           | **字段名称** | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键**           | **备注**                                                     |
| ------------------ | ------------ | -------------- | ---------------- | ------------ | ------------ | ---------------- | ------------------------------------------------------------ |
| ID_                | 主键         | NULL           | NO               | varchar      | 64           | PRI              |                                                              |
| PROC_INST_ID_      | 流程实例ID   | NULL           | YES              | varchar      | 64           | MUL              |                                                              |
| EXECUTION_ID_      | 执行实例ID   | NULL           | YES              | varchar      | 64           |                  |                                                              |
| TASK_ID_           | 任务ID       | NULL           | YES              | varchar      | 64           | MUL              |                                                              |
| NAME_              | 名称         | NULL           | NO               | varchar      | 255          | MUL              |                                                              |
| VAR_TYPE_          | 变量类型     | NULL           | YES              | varchar      | 100          |                  |                                                              |
| REV_               | 版本号       | NULL           | YES              | int          | NULL         |                  | version                                                      |
| BYTEARRAY_ID_      | 字节流ID     | NULL           | YES              | varchar      | 64           | ACT_GE_BYTEARRAY |                                                              |
| DOUBLE_            | 浮点值       | NULL           | YES              | double       | NULL         |                  | 存储DoubleType类型的数据                                     |
| LONG_              | 长整型       | NULL           | YES              | bigint       | NULL         |                  | 存储LongType类型的数据                                       |
| TEXT_              | 文本值       | NULL           | YES              | varchar      | 4000         |                  | 存储变量值类型为String，如此处存储持久化对象时，值jpa对象的class |
| TEXT2_             | 文本值       | NULL           | YES              | varchar      | 4000         |                  |                                                              |
| CREATE_TIME_       | 创建时间     | NULL           | YES              | datetime     | NULL         |                  |                                                              |
| LAST_UPDATED_TIME_ | 最后更新时间 | NULL           | YES              | datetime     | NULL         |                  |                                                              |

注：

1. 主要存放历史变量数据。

## 3.8  **流程实例历史：act_hi_procinst**



| **字段**                   | **字段名称** | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键** | **备注**               |
| -------------------------- | ------------ | -------------- | ---------------- | ------------ | ------------ | ------ | ---------------------- |
| ID_                        | 主键         | NULL           | NO               | varchar      | 64           | PRI    |                        |
| PROC_INST_ID_              | 流程实例ID   | NULL           | NO               | varchar      | 64           | UNI    |                        |
| BUSINESS_KEY_              | 业务标识     | NULL           | YES              | varchar      | 255          | MUL    | 业务主键，业务表单的ID |
| PROC_DEF_ID_               | 流程实例ID   | NULL           | NO               | varchar      | 64           |        |                        |
| START_TIME_                | 开始时间     | NULL           | NO               | datetime     | NULL         |        |                        |
| END_TIME_                  | 结束时间     | NULL           | YES              | datetime     | NULL         | MUL    |                        |
| DURATION_                  | 耗时         | NULL           | YES              | bigint       | NULL         |        |                        |
| START_USER_ID_             | 流程发起人ID | NULL           | YES              | varchar      | 255          |        |                        |
| START_ACT_ID_              | 开始节点ID   | NULL           | YES              | varchar      | 255          |        |                        |
| END_ACT_ID_                | 结束节点ID   | NULL           | YES              | varchar      | 255          |        |                        |
| SUPER_PROCESS_INSTANCE_ID_ | 父流程实例ID | NULL           | YES              | varchar      | 64           |        |                        |
| DELETE_REASON_             | 删除原因     | NULL           | YES              | varchar      | 4000         |        |                        |
| TENANT_ID_                 | 租户ID       |                | YES              | varchar      | 255          |        |                        |
| NAME_                      | 名称         | NULL           | YES              | varchar      | 255          |        |                        |

注：
1.核心表之一。
2.存放历史的流程实例。
3.设计历史流程实例表的初衷之一就是为了使得运行时库数据量尽可能小，效率最优。

## 3.9 **历史流程人员表:act_hi_identitylink**



| **字段**      | **字段名称** | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键** | **备注**                                                     |
| ------------- | ------------ | -------------- | ---------------- | ------------ | ------------ | ------ | ------------------------------------------------------------ |
| ID_           | 主键         |                | NO               | varchar      | 64           | PRI    |                                                              |
| GROUP_ID_     | 用户组ID     | NULL           | YES              | varchar      | 255          |        |                                                              |
| TYPE_         | 类型         | NULL           | YES              | varchar      | 255          |        | 类型，主要分为以下几种：assignee、candidate、owner、starter 、participant |
| USER_ID_      | 用户ID       | NULL           | YES              | varchar      | 255          | MUL    |                                                              |
| TASK_ID_      | 任务ID       | NULL           | YES              | varchar      | 64           | MUL    |                                                              |
| PROC_INST_ID_ | 流程实例ID   | NULL           | YES              | varchar      | 64           | MUL    |                                                              |

注：

1. 任务参与者数据表。主要存储当前节点参与者的信息。

**备注**：TYPE_ ：该关系数据的类型，当前提供了 个值 assignee、candidate和owner 表示流程数据的指派人（组〉、候选人（组）和拥有人

## 3.10  **运行时流程人员表:act_ru_identitylink**



| **字段**      | **字段名称** | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键**                  | **备注** |
| ------------- | ------------ | -------------- | ---------------- | ------------ | ------------ | ----------------------- | -------- |
| ID_           | 主键         |                | NO               | varchar      | 64           | PRI                     |          |
| REV_          | 版本号       | NULL           | YES              | int          | NULL         |                         | version  |
| GROUP_ID_     | 用户组ID     | NULL           | YES              | varchar      | 255          | MUL                     |          |
| TYPE_         | 类型         | NULL           | YES              | varchar      | 255          |                         |          |
| USER_ID_      | 用户ID       | NULL           | YES              | varchar      | 255          | MUL                     |          |
| TASK_ID_      | 任务ID       | NULL           | YES              | varchar      | 64           | MUL（ACT_RU_TASK）      |          |
| PROC_INST_ID_ | 流程实例ID   | NULL           | YES              | varchar      | 64           | MUL（ACT_RU_EXECUTION） |          |
| PROC_DEF_ID_  | 流程定义ID   | NULL           | YES              | varchar      | 64           | MUL(ACT_RE_PROCDEF)     |          |

注：
1.任务参与者数据表。主要存储当前节点参与者的信息。



## 3.11  **运行时任务节点表:act_ru_task**



| **字段**          | **字段名称** | **字段默认值** | **是否允许为空** | **数据类型** | **字段长度** | **键**                  | **备注**                               |
| ----------------- | ------------ | -------------- | ---------------- | ------------ | ------------ | ----------------------- | -------------------------------------- |
| ID_               | 主键         |                | NO               | varchar      | 64           | PRI                     |                                        |
| REV_              | 版本号       | NULL           | YES              | int          | NULL         |                         | version                                |
| EXECUTION_ID_     | 执行实例ID   | NULL           | YES              | varchar      | 64           | MUL（ACT_RU_EXECUTION） |                                        |
| PROC_INST_ID_     | 流程实例ID   | NULL           | YES              | varchar      | 64           | MUL（ACT_RU_EXECUTION） |                                        |
| PROC_DEF_ID_      | 流程定义ID   | NULL           | YES              | varchar      | 64           | MUL（ACT_RE_PROCDEF）   |                                        |
| NAME_             | 名称         | NULL           | YES              | varchar      | 255          |                         |                                        |
| PARENT_TASK_ID_   | 父任务ID     | NULL           | YES              | varchar      | 64           |                         |                                        |
| DESCRIPTION_      | 描述         | NULL           | YES              | varchar      | 4000         |                         |                                        |
| TASK_DEF_KEY_     | 人物定义标识 | NULL           | YES              | varchar      | 255          |                         |                                        |
| OWNER_            | 被代理人     | NULL           | YES              | varchar      | 255          |                         | （一般情况下为空，只有在委托时才有值） |
| ASSIGNEE_         | 经办人       | NULL           | YES              | varchar      | 255          |                         | 签收人或者委托人                       |
| DELEGATION_       | 委托状态     | NULL           | YES              | varchar      | 64           |                         | 委托状态 PENDING委托中，RESOLVED已处理 |
| PRIORITY_         | 优先级       | NULL           | YES              | int          | NUL          |                         |                                        |
| CREATE_TIME_      | 创建时间     | NULL           | YES              | timestamp    | NULL         | MUL                     |                                        |
| DUE_DATE_         | 截止时间     | NULL           | YES              | datetime     | NULL         |                         |                                        |
| CATEGORY_         | 分类         | NULL           | YES              | varchar      | 255          |                         |                                        |
| SUSPENSION_STATE_ | 挂起状态     | NULL           | YES              | int          | NULL         |                         | 暂停状态 1激活 2暂停                   |
| TENANT_ID_        | 租户ID       |                | YES              | varchar      | 255          |                         |                                        |
| FORM_KEY_         | 表单标识     | NULL           | YES              | varchar      | 255          |                         |                                        |

注：
1.运行时任务数据表



原文链接：https://blog.csdn.net/fwk19840301/article/details/100013577