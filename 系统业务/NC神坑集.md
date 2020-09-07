# 1.1 根据打补丁的目录，确定用友NC是否需要重新部署

$nchome\modules\uap\classes 此目录是nc服务器端需要的nc资源类。如果补丁需要打到该目录只需要重起应用，不需要重新部署。

$nchome\modules\uap\client 此目录是nc客户端需要的nc类。如果补丁需要打到该目录只需要重起应用，不需要重新部署。

$nchome\modules\uap\META-INF\classes此目录是ejb所需要的接口类，此目录下如果打补丁则需要重新部署ejb。

$nchome\webapps\nc_web下面的补丁不用部署,只需要重新启动中间件。

# 1.2 NC V6 安装目录各文件夹作用描述

**ant**：存放Apache Ant，用来执行EJB的构建。

**bin:** 存放nc部署和系统监控等命令。configsys.log部署日志（包含NC中间件、WAS中间件等部署信息）以及NC_Client文件夹，包含手动生成的NC客户端。

ejb: 按模块分子目录存放各个模块所使用的EJB，由构建工具维护。

ejbXMLs：存放需要独立事务的EJB的部署描述符,里面的xml文件都是开发配置的服务或特殊ejb，由构建工具维护。

framework：存放UAP框架/基础代码,为中间件提供服务/信息配置。

DBTrans：数据传输。

**ierp/bin****：**存放NC配置文件。目录下包括account.xml（帐套信息）、langconfig.xml（语言信息）、prop.xml（中间件机群、数据源信息）、servicerun.xml（后台注册服务信息）、systemconfig.xml（登陆模式和登陆保持信息）等。

**dist:** 存放在ncSysConfig.bat生成的代码及配置文件,该信息在使用WAS中间件时,需要部署到WAS中。在生成ejb后这个目录下应该存在一个nc.ear的文件,检查部署是否成功的时候可以看这个目录下的该文件内容是否跟was的”%WAS_HOME%\profiles\AppSrv01\installedApps\XXXXCell01\nc60.ear”这个目录下的内容一致。

initdatarule: 初始化NC数据的一些规则。

lib：NC在使用中用到的相关外部类文件（NC中间件使用该包下的数据库驱动）。

middleware：存放NC中间件等代码。

**modules**：按模块分子目录存放各个模块的代码。分public，client和private。每个模块由相应的产品组负责。此目录下还存放EJB代理，不过EJB代理由构建工具维护。

**nclogs**：NC日志文件。

**ncscirpt**：按模块分子目录存放各个模块的数据库建库脚本和初始化数据脚本。

**nmc**: nc性能监控、性能分析、系统管理工具

resources：存放资源文件，如图片和多语言资源。

ufjdk：存放JDK。

pfxx: 外部交换平台的配置文件。

update：存放补丁代码、升级所使用的升级代码和数据库脚本，按版本号分目录存放。

**webapps/ne_web:** 存放NC的web应用。 Client 目录存放两个重要文件：

jre-6u29-windows-i586-s.exe和NC_Login_v6.jar(供用户登陆用)

Driver: 数据库的驱动程序(供WAS、WLS使用).

langlib: 多语言资源文件。

# 1.3 eclipse 导入.class文件

eclipse下导入。class文件的具体步骤，希望对同道中人有所帮助！ 建工程-〉右键src file folder-〉config build path-〉libiraray-〉add extendal class folder-〉导入你的。class文件 （for eclipse 3.4） 对使用eclipse3.3的用户没有add extendal class folder 这个button，选择add class folder-> new folder-> 输入foldername-〉右键fn（前面你新建的foldername），import-〉导入你的。class文件 对于myeclipse同3.4

# 1.4 java 将class打包成jar包

一、进入到java jdk安装目录（用cmd命令进入）

c:
cd C:\Program Files\Java\jdk1.8.0_45\bin

二、运行打包命令（将D盘下com中的class 打包成xynet-auth.jar）

jar cvf D:\xynet-auth.jar D:\com



# 1.5 把java的class文件打成jar包的步骤
现在我的文件夹的目录在：

C:\Users\linsenq\Desktop\cglibjar 

我要把位于这个目录下的所有文件夹以及这个文件夹下的.class文件打成jar包

第一步：用win+R 打开cmd 把目录切换至C:\Users\linsenq\Desktop\cglibjar 

第二步：执行命令：jar   cvf spring-objenesis-repack-2.6.jar *    

这里面的spring-objenesis-repack-2.6.jar是为这个jar包取得名字。