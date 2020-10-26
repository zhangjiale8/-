# 1 什么是 spring?

​	Spring 是 个 java 企 业 级 应 用 的 开 源 开 发 框 架 。 Spring 主 要 用 来 开 发 Java 应 用 ， 但 是 有 些 扩 展 是 针 对 构 建 J2EE 平 台 的 web 应用。Spring 框 架 目 标 是 简 化 Java 企 业 级 应 用 开 发 ， 并 通 过 POJO 为 基 础 的 编 程 模 型 促 进 良 好 的 编 程 习 惯 。

# 2  使用 Spring 框架的好处是什么？ 

* 轻量：Spring 是轻量的，基本的版本大约 2MB。 
* 控制反转：Spring 通过控制反转实现了松散耦合，对象们给出它们的依 赖，而不是创建或查找依赖的对象们。 
* 面向切面的编程(AOP)：Spring 支持面向切面的编程，并且把应用业务 逻辑和系统服务分开。 
* 容器：Spring 包含并管理应用中对象的生命周期和配置。 
* MVC 框架：Spring 的 WEB 框架是个精心设计的框架，是 Web 框架的 一个很好的替代品。
* 事务管理：Spring 提供一个持续的事务管理接口，可以扩展到上至本地 事务下至全局事务（JTA）。 
* 异常处理：Spring 提供方便的 API 把具体技术相关的异常（比如由 JDBC， Hibernate or JDO 抛出的）转化为一致的 unchecked 异常。 

# 3 Spring 由哪些模块组成?

以 下 是 Spring 框 架 的 基 本 模 块 ：

* Core module 
* Bean module 
* Context module 
* Expression Language module 
* JDBC module 
* ORM module 
* OXM module 
* Java Messaging Service(JMS) module 
* Transaction module 
* Web module 
* Web-Servlet module 
* Web-Struts module 
* Web-Portlet module 

# 4 核心容器（应用上下文) 模块

​	 这 是 基 本 的 Spring 模 块 ， 提 供 spring 框 架的 基 础功 能 ， BeanFactory 是 任 何 以 spring 为基础的应用的核心。Spring 框 架 建 立 在 此 模 块 之 上 ， 它 使 Spring 成 为 一 个 容 器 。 

# 5 BeanFactory – BeanFactory 实现举例

​	Bean 工 厂 是 工 厂 模 式 的 一 个 实 现 ， 提 供 了 控 制 反 转 功 能 ， 用 来 把 应 用 的 配 置 和 依 赖 从 正 真 的 应 用 代 码 中 分 离 。 

​	最 常 用 的 BeanFactory 实 现 是 XmlBeanFactory 类 。

# 6 XMLBeanFactory 

​	最 常 用 的 就 是 org.springframework.beans.factory.xml.XmlBeanFactory ， 它 根 据 XML 文 件 中 的 定 义 加 载 beans。该容器从 XML 文 件 读 取 配 置 元 数 据 并 用 它 去 创 建 一 个 完 全 配 置 的 系 统 或 应 用 。 

# 7 解释 AOP 模块

​	AOP 模 块 用 于 发 给 我 们 的 Spring 应 用 做 面 向 切 面 的 开 发 ， 很 多 支 持 由 AOP 联 盟 提 供 ， 这 样 就 确 保 了 Spring 和 其 他 AOP 框 架 的 共 通 性 。 这 个 模 块 将 元 数 据 编 程 引 入 Spring。 

# 8 解释 JDBC 抽象和 DAO 模块 

​	通 过 使 用 JDBC 抽 象 和 DAO 模 块 ， 保 证 数 据 库 代 码 的 简 洁 ， 并 能 避 免 数 据 库 资 源 错 误 关 闭 导 致 的 问 题 ， 它 在 各 种 不 同 的 数 据 库 的 错 误 信 息 之 上 ， 提 供 了 一 个 统 一 的 异 常 访 问 层 。 它 还 利 用 Spring 的 AOP 模 块 给 Spring 应 用 中 的 对 象 提 供 事 务 管 理 服 务 。 

# 9 解释对象/关系映射集成模块  

​	Spring 通 过 提 供 ORM 模块，支持我们在直接 JDBC 之 上 使 用 一 个 对 象 /关 系 映 射 映射(ORM)工具，Spring 支 持 集 成 主 流 的 ORM 框架，如 Hiberate,JDO 和 iBATIS SQL Maps。Spring 的 事 务 管 理 同 样 支 持 以 上 所 有 ORM 框 架 及 JDBC。 

# 10 解释 WEB 模块

​	Spring 的 WEB 模 块 是 构 建 在 application context 模 块 基 础 之 上 ， 提 供 一 个 适 合 web 应 用 的 上 下 文 。 这 个 模 块 也 包 括 支 持 多 种 面 向 web 的任务，如透明地处理 多 个 文 件 上 传 请 求 和 程 序 级 请 求 参 数 的 绑 定 到 你 的 业 务 对 象 。 它 也 有 对 Jakarta Struts 的 支 持 。 

# 11 Spring 配置文件

​	 Spring 配 置 文 件 是 个 XML 文 件 ， 这 个 文 件 包 含 了 类 信 息 ， 描 述 了 如 何 配 置 它 们 ， 以 及 如 何 相 互 调 用 。 

# 12 什么是 Spring IOC 容器？ 

​	Spring IOC 负 责 创 建 对 象 ， 管 理 对 象 （ 通 过 依 赖 注 入 （ DI） ， 装 配 对 象 ， 配 置 对 象 ， 并 且 管 理 这 些 对 象 的 整 个 生 命 周 期 。 

# 13 IOC 的优点是什么？ 

​	IOC 或 依 赖 注 入 把 应 用 的 代 码 量 降 到 最 低 。 它 使 应 用 容 易 测 试 ， 单 元 测 试 不 再 需 要 单 例 和 JNDI 查 找 机 制 。 最 小 的 代 价 和 最 小 的 侵 入 性 使 松 散 耦 合 得 以 实 现 。 IOC 容 器 支 持 加 载 服 务 时 的 饿 汉 式 初 始 化 和 懒 加 载 。 

# 14 ApplicationContext 通常的实现是什么?

* FileSystemXmlApplicationContext ：此容器从一个 XML 文件中加 载 beans 的定义，XML Bean 配置文件的全路径名必须提供给它的构造函数。
* ClassPathXmlApplicationContext：此容器也从一个 XML 文件中加 载 beans 的定义，这里，你需要正确设置 classpath 因为这个容器将在 classpath 里找 bean 配置。 
* WebXmlApplicationContext：此容器加载一个 XML 文件，此文件定 义了一个 WEB 应用的所有 bean。 

# 15 Bean 工厂和 Application contexts 有什么区别？ 

​	Application contexts 提 供 一 种 方 法 处 理 文 本 消 息 ， 一 个 通 常 的 做 法 是 加 载 文 件 资 源 （ 比 如 镜 像 ） ， 它 们 可 以 向 注 册 为 监 听 器 的 bean 发 布 事 件 。 另 外 ， 在 容 器 或 容 器 内 的 对 象 上 执 行 的 那 些 不 得 不 由 bean 工 厂 以 程 序 化 方 式 处 理 的 操 作 ， 可 以 在 Application contexts 中 以 声 明 的 方 式 处 理 。 Application contexts 实 现 了 MessageSource 接 口 ， 该 接 口 的 实 现 以 可 插 拔 的 方 式 提 供 获 取 本 地 化 消 息 的 方 法 。 

# 16 一个 Spring 的应用看起来象什么？

 * 一个定义了一些功能的接口。 
 * 这实现包括属性，它的 Setter ， getter 方法和函数等。 
 * Spring AOP。 
 * Spring 的 XML 配置文件。 
 * 使用以上功能的客户端程序。 
 * 依赖注入 

# 17 什么是 Spring 的依赖注入？

​	依 赖 注 入 ， 是 IOC 的 一 个 方 面 ， 是 个 通 常 的 概 念 ， 它 有 多 种 解 释 。 这 概 念 是 说 你 不 用 创 建 对 象 ， 而 只 需 要 描 述 它 如 何 被 创 建 。 你 不 在 代 码 里 直 接 组 装 你 的 组 件 和 服 务 ， 但 是 要 在 配 置 文 件 里 描 述 哪 些 组 件 需 要 哪 些 服 务 ， 之 后 一 个 容 器 （ IOC 容 器 ） 负 责 把 他 们 组 装 起 来 。 

# 19 有哪些不同类型的 IOC（依赖注入）方式？

* 构造器依赖注入：构造器依赖注入通过容器触发一个类的构造器来实现 的，该类有一系列参数，每个参数代表一个对其他类的依赖。 
* Setter 方法注入：Setter 方法注入是容器通过调用无参构造器或无参 static 工厂 方法实例化 bean 之后，调用该 bean 的 setter 方法，即实现了基 于 setter 的依赖注入。 

# 20 哪种依赖注入方式你建议使用，构造器注入，还是 Setter 方法注入？

​	 你 两 种 依 赖 方 式 都 可 以 使 用 ， 构 造 器 注 入 和 Setter 方 法 注 入 。 最 好 的 解 决 方 案 是 用 构 造 器 参 数 实 现 强 制 依 赖 ， setter 方 法 实 现 可 选 依 赖 。 

# 21 什么是 Spring beans?

​	Spring beans 是 那 些 形 成 Spring 应 用 的 主 干 的 java 对 象 。 它 们 被 Spring IOC 容 器 初 始 化 ， 装 配 ， 和 管 理 。 这 些 beans 通 过 容 器 中 配 置 的 元 数 据 创 建 。 比 如 ， 以 XML 文 件 中 的 形 式 定 义 。 Spring 框 架 定 义 的 beans 都 是 单 件 beans。在 bean tag 中 有 个 属 性 ” singleton”， 如果 它 被赋 为 TRUE，bean 就 是 单 件 ， 否 则 就 是 一 个 prototype bean。 默认 是 TRUE， 所 以 所 有 在 Spring 框 架 中 的 beans 缺 省 都 是 单 件 。 

# 22 一个 Spring Bean 定义 包含什么？

​	 一 个 Spring Bean 的 定 义 包 含 容 器 必 知 的 所 有 配 置 元 数 据 ， 包 括 如 何 创 建 一 个 bean， 它 的 生 命 周 期 详 情 及 它 的 依 赖 。 

# 23 如何给 Spring 容器提供配置元数据? 

​	这 里 有 三 种 重 要 的 方 法 给 Spring 容 器 提 供 配 置 元 数 据 。 

* XML 配 置 文 件 。 
* 基 于 注 解 的 配 置 。 
* 基 于 java 的 配 置 。 

# 24 你怎样定义类的作用域?

 	当 定 义 一 个 在 Spring 里 ， 我 们 还 能 给 这 个 bean 声 明 一 个 作 用 域 。 它 可 以 通 过 bean 定 义 中 的 scope 属性来定义。如，当 Spring 要 在 需 要 的 时 候 每 次 生 产 一 个 新 的 bean 实例，bean 的 scope 属 性 被 指 定 为 prototype。另一方面，一个 bean每 次 使 用 的 时 候 必 须 返 回 同 一 个 实 例 ， 这 个 bean 的 scope 属 性 必 须 设 为 singleton。 

# 25 解释 Spring 支持的几种 bean 的作用域 

​	Spring 框 架 支 持 以 下 五 种 bean 的 作 用 域 ： 

* singleton : bean 在每个 Spring ioc 容器中只有一个实例。 

* prototype：一个 bean 的定义可以有多个实例。 

* request：每次 http 请求都会创建一个 bean，该作用域仅在基于 web 的 Spring ApplicationContext 情形下有效。 

* session：在一个 HTTP Session 中，一个 bean 定义对应一个实例。该 作用域仅在基于 web 的 Spring ApplicationContext 情形下有效。 

* global-session：在一个全局的 HTTP Session 中，一个 bean 定义对应 一个实例。该作用域仅在基于 web 的 Spring ApplicationContext 情形下有效。 

  

  缺 省 的 Spring bean 的 作 用 域 是 Singleton. 

# 26 Spring 框架中的单例 bean 是线程安全的吗?

​	 不，Spring 框 架 中 的 单 例 bean 不 是 线 程 安 全 的 。 

# 27 解释 Spring 框架中 bean 的生命周期 

* Spring 容器 从 XML 文件中读取 bean 的定义，并实例化 bean。 
* Spring 根据 bean 的定义填充所有的属性。
* 如果 bean 实现了 BeanNameAware 接口，Spring 传递 bean 的 ID 到 setBeanName 方法。
* 如果 Bean 实现了 BeanFactoryAware 接口， Spring 传递 beanfactory 给 setBeanFactory 方法。 
* 如果有任何与 bean 相关联的 BeanPostProcessors，Spring 会在 postProcesserBeforeInitialization()方法内调用它们。 
* 如果 bean 实现 IntializingBean 了，调用它的 afterPropertySet 方法， 如果 bean 声明了初始化方法，调用此初始化方法。 
* 如果有 BeanPostProcessors 和 bean 关联，这些 bean 的 postProcessAfterInitialization() 方法将被调用。 
* 如果 bean 实现了 DisposableBean，它将调用 destroy()方法。 

# 28 哪些是重要的 bean 生命周期方法？你能重载它们吗？

 	有 两 个 重 要 的 bean 生 命 周 期 方 法 ， 第 一 个 是 setup ， 它 是 在 容 器 加 载 bean 的 时 候 被 调 用 。 第 二 个 方 法 是 teardown 它 是 在 容 器 卸 载 类 的 时 候 被 调 用 。 

​	The bean 标 签有 两 个重 要 的属 性 （ init-method 和 destroy-method）。用它们 你 可 以 自 己 定 制 初 始 化 和 注 销 方 法 。 它 们 也 有 相 应 的 注 解 （ @PostConstruct 和 @PreDestroy）。 

# 29 什么是 Spring 的内部 bean？ 

​	当 一 个 bean 仅 被 用 作 另 一 个 bean 的 属 性 时 ， 它 能 被 声 明 为 一 个 内 部 bean，为 了 定 义 inner bean，在 Spring 的 基 于 XML 的 配 置 元 数 据 中 ， 可 以 在 或 元 素 内 使 用 元 素 ， 内 部 bean 通 常 是 匿 名 的 ， 它 们 的 Scope 一 般 是 prototype。 

# 30 在 Spring 中如何注入一个 java 集合？
​	Spring 提 供 以 下 几 种 集 合 的 配 置 元 素 ： 

* 类型用于注入一列值，允许有相同的值。
*  类型用于注入一组值，不允许有相同的值。 
* 类型用于注入一组键值对，键和值都可以为任意类型。 
* 类型用于注入一组键值对，键和值都只能为 String 类型。 

# 31 什么是 bean 装配? 

​	装配，或 bean 装 配 是 指 在 Spring 容 器 中 把 bean 组 装 到 一 起 ， 前 提 是 容 器 需 要 知 道 bean 的 依 赖 关 系 ， 如 何 通 过 依 赖 注 入 来 把 它 们 装 配 到 一 起 。 

# 32 什么是 bean 的自动装配？ 

​	Spring 容 器 能 够 自 动 装 配 相 互 合 作 的 bean， 这 意 味 着 容 器 不 需 要 和 配 置 ， 能 通 过 Bean 工 厂 自 动 处 理 bean 之 间 的 协 作 。 

# 33 解释不同方式的自动装配  

​	有 五 种 自 动 装 配 的 方 式 ， 可 以 用 来 指 导 Spring 容 器 用 自 动 装 配 方 式 来 进 行 依 赖 注 入 。 

* no：默认的方式是不进行自动装配，通过显式设置 ref 属性来进行装配。
* byName：通过参数名 自动装配，Spring 容器在配置文件中发现 bean 的 autowire 属性被设置成 byname，之后容器试图匹配、装配和该 bean 的属 性具有相同名字的 bean。 
* byType：通过参数类型自动装配，Spring 容器在配置文件中发现 bean 的 autowire 属性被设置成 byType，之后容器试图匹配、装配和该 bean 的属 性具有相同类型的 bean。如果有多个 bean 符合条件，则抛出错误。 
* constructor：这个方式类似于 byType， 但是要提供给构造器参数，如 果没有确定的带参数的构造器参数类型，将会抛出异常。 
* autodetect：首先尝试使用 constructor 来自动装配，如果无法工作， 则使用 byType 方式。 

# 34 自动装配有哪些局限性 ? 

​	自 动 装 配 的 局 限 性 是 ： 

* 重写：你仍需用 和 配置来定义依赖，意味着总要重写自动装配。 
* 基本数据类型：你不能自动装配简单的属性，如基本数据类型，String 字符串，和类。 
* 模糊特性：自动装配不如显式装配精确，如果有可能，建议使用显式装配。 

# 35 你可以在 Spring 中注入一个 null 和一个空字符串吗？ 

可 以 。 Spring 注解

# 36 什么是基于 Java 的 Spring 注解配置? 给一些注解的例子.

​	基 于 Java 的 配 置 ， 允 许 你 在 少 量 的 Java 注 解 的 帮 助 下 ， 进 行 你 的 大 部 分 Spring 配 置 而 非 通 过 XML 文 件 。 

​	以 @Configuration 注 解 为 例 ， 它 用 来 标 记 类 可 以 当 做 一 个 bean 的 定 义 ， 被 Spring IOC 容 器 使 用 。 另 一 个 例 子 是 @Bean 注 解 ， 它 表 示 此 方 法 将 要 返 回 一 个 对 象 ， 作 为 一 个 bean 注 册 进 Spring 应 用 上 下 文 。 

# 37 什么是基于注解的容器配置? 

​	相 对 于 XML 文 件 ， 注 解 型 的 配 置 依 赖 于 通 过 字 节 码 元 数 据 装 配 组 件 ， 而 非 尖 括 号 的 声 明 。 开 发 者 通 过 在 相 应 的 类 ， 方 法 或 属 性 上 使 用 注 解 的 方 式 ， 直 接 组 件 类 中 进 行 配 置 ， 而 不 是 使 用 xml 表 述 bean 的 装 配 关 系 。 

# 38 怎样开启注解装配？ 

​	注 解 装 配 在 默 认 情 况 下 是 不 开 启 的 ， 为 了 使 用 注 解 装 配 ， 我 们 必 须 在 Spring 配 置 文 件 中 配 置 context:annotation-config/元 素 。 

# 39 @Required 注解

​	 这 个 注 解 表 明 bean 的 属 性 必 须 在 配 置 的 时 候 设 置 ， 通 过 一 个 bean 定 义 的 显 式 的 属 性 值 或 通 过 自 动 装 配 ， 若 @Required 注 解 的 bean 属 性 未 被 设 置 ， 容 器 将 抛 出 BeanInitializationException。

# 40 @Autowired 注解

​	 @Autowired 注 解 提 供 了 更 细 粒 度 的 控 制 ， 包 括 在 何 处 以 及 如 何 完 成 自 动 装 配 。 它的用法和@Required 一样，修饰 setter 方 法 、 构 造 器 、 属 性 或 者 具 有 任 意 名 称 和 /或 多 个 参 数 的 PN 方 法 。

# 41 @Qualifier 注解

 	当 有 多 个 相 同 类 型 的 bean 却 只 有 一 个 需 要 自 动 装 配 时 ， 将 @Qualifier 注 解 和 @Autowire 注 解 结 合 使 用 以 消 除 这 种 混 淆 ， 指 定 需 要 装 配 的 确 切 的 bean。 

# 42 在 Spring 框架中如何更有效地使用 JDBC? 

​	使 用 SpringJDBC 框 架 ， 资 源 管 理 和 错 误 处 理 的 代 价 都 会 被 减 轻 。 所 以 开 发 者 只 需 写 statements 和 queries 从数据存取数据，JDBC 也 可 以 在 Spring 框 架 提 供 的 模 板 类 的 帮 助 下 更 有 效 地 被 使 用 ， 这 个 模 板 叫 JdbcTemplate （ 例 子 见 这 里 here） 

# 43 JdbcTemplate 

​	JdbcTemplate 类 提 供 了 很 多 便 利 的 方 法 解 决 诸 如 把 数 据 库 数 据 转 变 成 基 本 数 据 类 型 或 对 象 ， 执 行 写 好 的 或 可 调 用 的 数 据 库 操 作 语 句 ， 提 供 自 定 义 的 数 据 错 误 处 理 。

# 44 Spring 对 DAO 的支持 

​	Spring 对 数 据 访 问 对 象 （ DAO） 的 支 持 旨 在 简 化 它 和 数 据 访 问 技 术 如 JDBC， Hibernate or JDO 结 合 使 用 。 这 使 我 们 可 以 方 便 切 换 持 久 层 。 编 码 时 也 不 用 担 心 会 捕 获 每 种 技 术 特 有 的 异 常 。 

# 45 使用 Spring 通过什么方式访问 Hibernate? 

​	在 Spring 中 有 两 种 方 式 访 问 Hibernate： 

* 控制反转 Hibernate Template 和 Callback。 
* 继承 HibernateDAOSupport 提供一个 AOP 拦截器。 

# 46 Spring 支持的 ORM 

​	Spring 支 持 以 下 ORM： 

* Hibernate 
* iBatis 
* JPA (Java Persistence API) 
* TopLink 
* JDO (Java Data Objects) 
* OJB

# 47 如何通过 HibernateDaoSupport 将 Spring 和 Hibernate 结合起来？ 

​	用 Spring 的 SessionFactory 调 用 LocalSessionFactory。集成过程分三步： 

* 配置 the Hibernate SessionFactory。 
* 继承 HibernateDaoSupport 实现一个 DAO。 
* 在 AOP 支持的事务中装配。 

# 48 Spring 支持的事务管理类型

​	Spring 支 持 两 种 类 型 的 事 务 管 理 ： 

* 编程式事务管理：这意味你通过编程的方式管理事务，给你带来极大的灵 活性，但是难维护。
* 声明式事务管理：这意味着你可以将业务代码和事务管理分离，你只需用 注解和 XML 配置来管理事务。 

# 49 Spring 框架的事务管理有哪些优点？ 

* 它为不同的事务 API 如 JTA，JDBC，Hibernate，JPA 和 JDO，提供 一个不变的编程模式。 
* 它为编程式事务管理提供了一套简单的 API 而不是一些复杂的事务 API 如
* 它支持声明式事务管理。 
* 它和 Spring 各种数据访问抽象层很好得集成。 

# 50 你更倾向用那种事务管理类型？ 

​	大 多 数 Spring 框 架 的 用 户 选 择 声 明 式 事 务 管 理 ， 因 为 它 对 应 用 代 码 的 影 响 最 小 ， 因 此 更 符 合 一 个 无 侵 入 的 轻 量 级 容 器 的 思 想 。 声 明 式 事 务 管 理 要 优 于 编 程 式 事 务 管 理 ， 虽 然 比 编 程 式 事 务 管 理 （ 这 种 方 式 允 许 你 通 过 代 码 控 制 事 务 ） 少 了 一 点 灵 活 性 。

# 51 解释 AOP 

​	面 向 切 面 的 编 程 ， 或 AOP， 是 一 种 编 程 技 术 ， 允 许 程 序 模 块 化 横 向 切 割 关 注 点 ， 或 横 切 典 型 的 责 任 划 分 ， 如 日 志 和 事 务 管 理 。 

# 52 Aspect 切面 

​	AOP 核 心 就 是 切 面 ， 它 将 多 个 类 的 通 用 行 为 封 装 成 可 重 用 的 模 块 ， 该 模 块 含 有 一 组 API 提 供 横 切 功 能 。 比 如 ， 一 个 日 志 模 块 可 以 被 称 作 日 志 的 AOP 切 面 。 根 据 需 求 的 不 同 ， 一 个 应 用 程 序 可 以 有 若 干 切 面 。 在 Spring AOP 中 ， 切 面 通 过 带 有 @Aspect 注 解 的 类 实 现 。 

# 53 在 Spring AOP 中，关注点和横切关注的区别是什么？

​	关 注 点 是 应 用 中 一 个 模 块 的 行 为 ， 一 个 关 注 点 可 能 会 被 定 义 成 一 个 我 们 想 实 现 的 一 个 功 能 。 

​	横 切 关 注 点 是 一 个 关 注 点 ， 此 关 注 点 是 整 个 应 用 都 会 使 用 的 功 能 ， 并 影 响 整 个 应 用 ， 比 如 日 志 ， 安 全 和 数 据 传 输 ， 几 乎 应 用 的 每 个 模 块 都 需 要 的 功 能 。 因 此 这 些 都 属 于 横 切 关 注 点 。 

# 54 连接点 

​	连 接点 代 表 一 个 应 用 程 序 的 某 个 位 置 ， 在 这 个 位 置 我 们 可 以 插 入 一 个 AOP 切 面 ， 它 实 际 上 是 个 应 用 程 序 执 行 Spring AOP 的 位 置 。

 # 55 通知 

​	通 知 是 个 在 方 法 执 行 前 或 执 行 后 要 做 的 动 作 ， 实 际 上 是 程 序 执 行 时 要 通 过 SpringAOP 框 架 触 发 的 代 码 段 。 

​	Spring 切 面 可 以 应 用 五 种 类 型 的 通 知 ： 

* before：前置通知，在一个方法执行前被调用。 
* after: 在方法执行之后调用的通知，无论方法执行是否成功。 
* after-returning: 仅当方法成功完成后执行的通知。 
* after-throwing: 在方法抛出异常退出时执行的通知。 
* around: 在方法执行之前和之后调用的通知。 

# 56 切点

​	切 入 点 是 一 个 或 一 组 连 接 点 ， 通 知 将 在 这 些 位 置 执 行 。 可 以 通 过 表 达 式 或 匹 配 的 方 式 指 明 切 入 点 。 

# 57 什么是引入? 

​	引 入 允 许 我 们 在 已 存 在 的 类 中 增 加 新 的 方 法 和 属 性 。 

# 58 什么是目标对象? 

​	被 一 个 或 者 多 个 切 面 所 通 知 的 对 象 。 它 通 常 是 一 个 代 理 对 象 。 也 指 被 通 知 （advised）对象。 

# 59 什么是代理? 

​	代 理 是 通 知 目 标 对 象 后 创 建 的 对 象 。 从 客 户 端 的 角 度 看 ， 代 理 对 象 和 目 标 对 象 是 一 样 的 。 

# 60 有几种不同类型的自动代理？ 

	* BeanNameAutoProxyCreator 
	* DefaultAdvisorAutoProxyCreator 
	* Metadata autoproxying 

# 61 什么是织入。什么是织入应用的不同点？
​	织 入 是 将 切 面 和 到 其 他 应 用 类 型 或 对 象 连 接 或 创 建 一 个 被 通 知 对 象 的 过 程 。 织 入 可 以 在 编 译 时 ， 加 载 时 ， 或 运 行 时 完 成 。 

# 62 解释基于 XML Schema 方式的切面实现 

​	在 这 种 情 况 下 ， 切 面 由 常 规 类 以 及 基 于 XML 的 配 置 实 现 。 

# 63 解释基于注解的切面实现 

​	在 这 种 情 况 下 (基 于 @AspectJ 的 实 现 )， 涉 及 到 的 切 面 声 明 的 风 格 与 带 有 java5 标 注 的 普 通 java 类 一 致 。

# 64 什么是 Spring 的 MVC 框架？ 

​	Spring 配 备 构 建 Web 应 用 的 全 功 能 MVC 框架。Spring 可 以 很 便 捷 地 和 其 他 MVC 框架集成，如 Struts，Spring 的 MVC 框 架 用 控 制 反 转 把 业 务 对 象 和 控 制 逻 辑 清 晰 地 隔 离 。 它 也 允 许 以 声 明 的 方 式 把 请 求 参 数 和 业 务 对 象 绑 定 。 

# 65 DispatcherServlet 

​	Spring 的 MVC 框 架 是 围 绕 DispatcherServlet 来设计的，它用来处理所有的 HTTP 请 求 和 响 应 。

# 66 WebApplicationContext 

​	WebApplicationContext 继 承 了 ApplicationContext 并 增 加 了 一 些 WEB 应 用 必 备 的 特 有 功 能 ，它 不 同 于 一 般 的 ApplicationContext ，因 为 它 能 处 理 主 题 ， 并 找 到 被 关 联 的 servlet。 

# 67 什么是 Spring MVC 框架的控制器？ 

​	控 制 器 提 供 一 个 访 问 应 用 程 序 的 行 为 ， 此 行 为 通 常 通 过 服 务 接 口 实 现 。 控 制 器 解 析 用 户 输 入 并 将 其 转 换 为 一 个 由 视 图 呈 现 给 用 户 的 模 型 。Spring 用 一 个 非 常 抽 象 的 方 式 实 现 了 一 个 控 制 层 ， 允 许 用 户 创 建 多 种 用 途 的 控 制 器 。 

# 68 @Controller 注解 

​	该 注 解 表 明 该 类 扮 演 控 制 器 的 角 色 ，Spring 不 需 要 你 继 承 任 何 其 他 控 制 器 基 类 或 引 用 Servlet API。 

# 69 @RequestMapping 注解 

​	该 注 解 是 用 来 映 射 一 个 URL 到 一 个 类 或 一 个 特 定 的 方 处 理 法 上 。