#  一、一般问题 

## 1.1 不同版本的 Spring Framework 有哪些主要功能？

 Version Feature 

Spring 2.5 发布于 2007 年。这是第一个支持注解的版本。 

Spring 3.0 发布于 2009 年。它完全利用了 Java5 中的改进，并为 JEE6 提供了支 持。 

Spring 4.0 发布于 2013 年。这是第一个完全支持 JAVA8 的版本。

## 1.2 什么是 Spring Framework？

​	 Spring 是 一 个 开 源 应 用 框 架 ， 旨 在 降 低 应 用 程 序 开 发 的 复 杂 度 。 它 是 轻 量 级 、 松 散 耦 合 的 。 它 具 有 分 层 体 系 结 构 ， 允 许 用 户 选 择 组 件 ， 同 时 还 为 J2EE 应 用 程 序 开 发 提 供 了 一 个 有 凝 聚 力 的 框 架 。 它 可 以 集 成 其 他 框 架 ， 如 Structs、Hibernate、 EJB 等 ， 所 以 又 称 为 框 架 的 框 架 。 

## 1.3 列举 Spring Framework 的优点。 

​	由 于 Spring Frameworks 的 分 层 架 构 ， 用 户 可 以 自 由 选 择 自 己 需 要 的 组 件 。 Spring Framework 支 持 POJO(Plain Old Java Object) 编 程 ， 从 而 具 备 持 续 集 成 和 可 测 试 性 。 由 于 依 赖 注 入 和 控 制 反 转 ， JDBC 得 以 简 化 。 它 是 开 源 免 费 的 。 

## 1.4、Spring Framework 有哪些不同的功能？

* 轻 量 级 - Spring 在 代 码 量 和 透 明 度 方 面 都 很 轻 便 。 
* IOC - 控 制 反 转 
* AOP - 面 向 切 面 编 程 可 以 将 应 用 业 务 逻 辑 和 系 统 服 务 分 离 ， 以 实 现 高 内 聚 。
*  容 器 - Spring 负 责 创 建 和 管 理 对 象 （ Bean） 的 生 命 周 期 和 配 置 。
*  MVC - 对 web 应 用 提 供 了 高 度 可 配 置 性 ， 其 他 框 架 的 集 成 也 十 分 方 便 。 
* 事 务 管 理 - 提 供 了 用 于 事 务 管 理 的 通 用 抽象 层 。Spring 的 事 务 支 持 也 可 用 于 容 器 较 少 的 环 境 。 
* JDBC 异 常 - Spring 的 JDBC 抽 象 层 提 供 了 一 个 异 常 层 次 结 构 ， 简 化 了 错 误 处 理 策 略 。 

## 1.5 Spring Framework 中有多少个模块，它们分别是什么？

![image-20201025171743639](E:\学习笔记\mylearnnote\web架构集\spring全家桶\springFramework\image\image-20201025171743639.png)

* Spring 核 心 容 器 – 该 层 基 本 上 是 Spring Framework 的 核 心 。 它 包 含 以 下 模 块 ： 

Spring Core 

Spring Bean 

SpEL (Spring Expression Language) 

Spring Context 

* 数 据 访 问 /集 成 – 该 层 提 供 与 数 据 库 交 互 的 支 持 。 它 包 含 以 下 模 块 ： 

JDBC (Java DataBase Connectivity) 

ORM (Object Relational Mapping) 

OXM (Object XML Mappers)

JMS (Java Messaging Service) 

Transaction 

* Web – 该 层 提 供 了 创 建 Web 应 用 程 序 的 支 持 。 它 包 含 以 下 模 块 ： 

Web 

Web – Servlet 

Web – Socket 

Web – Portlet 

* AOP 该层支持面向切面编程 

* Instrumentation 该层为类检测和类加载器实现提供支持。 

* Test 该层为使用 JUnit 和 TestNG 进行测试提供支持。 

几 个 杂 项 模 块 :

* Messaging – 该 模 块 为 STOMP 提 供 支 持 。 它 还 支 持 注 解 编 程 模 型 ， 该 模 型 用 于 从 WebSocket 客 户 端 路 由 和 处 理 STOMP 消 息 。 

* Aspects – 该 模 块 为 与 AspectJ 的 集 成 提 供 支 持 。 

## 1.6 什么是 Spring 配置文件？

 	Spring 配 置 文 件 是 XML 文 件 。 该 文 件 主 要 包 含 类 信 息 。 它 描 述 了 这 些 类 是 如 何 配 置 以 及 相 互 引 入 的 。 但 是 ， XML 配 置 文 件 冗 长 且 更 加 干 净 。 如 果 没 有 正 确 规 划 和 编 写 ， 那 么 在 大 项 目 中 管 理 变 得 非 常 困 难 。 

## 1.7 Spring 应用程序有哪些不同组件？ 

​	Spring 应 用 一 般 有 以 下 组 件 ： 

* 接口 - 定义功能。 
* Bean 类 - 它包含属性，setter 和 getter 方法，函数等。 
* Spring 面向切面编程（AOP） - 提供面向切面编程的功能。 
* Bean 配置文件 - 包含类的信息以及如何配置它们。 
* 用户程序 - 它使用接口。 

## 1.8 使用 Spring 有哪些方式？ 

使 用 Spring 有 以 下 方 式 ： 

* 作为一个成熟的 Spring Web 应用程序。
* 作为第三方 Web 框架，使用 Spring Frameworks 中间层。 
* 用于远程使用。 
* 作为企业级 Java Bean，它可以包装现有的 POJO（Plain Old Java Objects）。 

# 二、依赖注入（Ioc） 

## 2.1 什么是 Spring IOC 容器？ 

​	Spring 框 架 的 核 心 是 Spring 容 器 。 容 器 创 建 对 象 ， 将 它 们 装 配 在 一 起 ， 配 置 它 们 并管 理 它们 的 完整 生 命周 期 。Spring 容 器 使 用 依 赖 注 入 来 管 理 组 成 应 用 程 序 的 组 件 。 容 器 通 过 读 取 提 供 的 配 置 元 数 据 来 接 收 对 象 进 行 实 例 化 ， 配 置 和 组 装 的 指 令 。 该 元 数 据 可 以 通 过 XML，Java 注 解 或 Java 代 码 提 供 。 

![image-20201025215620732](E:\学习笔记\mylearnnote\web架构集\spring全家桶\springFramework\image\image-20201025215620732.png)



## 2.2 什么是依赖注入？

​	在 依 赖 注 入 中 ， 您 不 必 创 建 对 象 ， 但 必 须 描 述 如 何 创 建 它 们 。 您 不 是 直 接 在 代 码 中 将 组 件 和 服 务 连 接 在 一 起 ， 而 是 描 述 配 置 文 件 中 哪 些 组 件 需 要 哪 些 服 务 。 由 IoC 容 器 将 它 们 装 配 在 一 起 。 

## 2.3 可以通过多少种方式完成依赖注入？ 

​	通 常 ， 依 赖 注 入 可 以 通 过 三 种 方 式 完 成 ， 即 ： 

* 构造函数注入

* setter 注入

* 接口注入

   在 Spring Framework 中 ， 仅 使 用 构 造 函 数 和 setter 注 入 。 

## 2.4 区分构造函数注入和 setter 注入



| 构造函数注入               | setter 注入                |
| -------------------------- | -------------------------- |
| 没有部分注入               | 有部分注入                 |
| 不会覆盖 setter 属性       | 会覆盖 setter 属性         |
| 任意修改都会创建一个新实例 | 任意修改不会创建一个新实例 |
| 适用于设置很多属性         | 适用于设置少量属性         |

## 2.5 spring 中有多少种 IOC 容器？

* BeanFactory - BeanFactory 就 像 一 个 包 含 bean 集 合 的 工 厂 类 。 它 会 在 客 户 端 要 求 时 实 例 化 bean。
*  ApplicationContext - ApplicationContext 接 口 扩 展 了 BeanFactory 接口。它 在 BeanFactory 基 础 上 提 供 了 一 些 额 外 的 功 能 。 

## 2.6 区分 BeanFactory 和 ApplicationContext

​	

| BeanFactory                | ApplicationContext       |
| -------------------------- | ------------------------ |
| 它使用懒加载               | 它使用即时加载           |
| 它使用语法显式提供资源对象 | 它自己创建和管理资源对象 |
| 不支持国际化               | 支持国际化               |
| 不支持基于依赖的注解       | 支持基于依赖的注解       |

## 2.7 列举 IoC 的一些好处

​	IoC 的 一 些 好 处 是 ： 

	* 它将最小化应用程序中的代码量。 
	* 它将使您的应用程序易于测试，因为它不需要单元测试用例中的任何单例 或 JNDI 查找机制。 
	* 它以最小的影响和最少的侵入机制促进松耦合。 
	* 它支持即时的实例化和延迟加载服务。 

## 2.8 Spring IoC 的实现机制

​	Spring 中 的 IoC 的 实 现 原 理 就 是 工 厂 模 式 加 反 射 机 制 。 

示 例 ： 

```java
interface Fruit {
        public abstract void eat();
    }

    class Apple implements Fruit {
        public void eat() {
            System.out.println("Apple");
        }
    }

    class Orange implements Fruit {
        public void eat() {
            System.out.println("Orange");
        }
    }

    class Factory {
        public static Fruit getInstance(String ClassName) {
            Fruit f = null;
            try {
                f = (Fruit) Class.forName(ClassName).newInstance();
            } catch (Exception e) {
                e.printStackTrace();
            }
            return f;
        }
    }

    class Client {
        public static void main(String[] a) {
            Fruit f = Factory.getInstance("io.github.dunwu.spring.Apple");
            if (f != null) {
                f.eat();
            }
        }
    }
```



# 三、Beans 

## 3.1 什么是 spring bean？

* 它们是构成用户应用程序主干的对象。 Bean 由 Spring IoC 容器管理。 
* 它们由 Spring IoC 容器实例化，配置，装配和管理。 Bean 是基于用户提供给容器的配置元数据创建。 

## 3.2 spring 提供了哪些配置方式？

## 3.2.1 基 于 xml 配 置

​	bean 所 需 的 依 赖 项 和 服 务 在 XML 格 式 的 配 置 文 件 中 指 定 。 这 些 配 置 文 件 通 常 包 含 许 多 bean 定 义 和 特 定 于 应 用 程 序 的 配 置 选 项 。 它 们 通 常 以 bean 标 签 开 头 。 例 如 ：

```xml
 <bean id="studentbean" class="org.edureka.firstSpring.StudentBean">
     <property name="name" value="Edureka"></property> 
</bean>
```

### 3.2.2  基 于 注 解 配 置  

​	您 可 以 通 过 在 相 关 的 类 ， 方 法 或 字 段 声 明 上 使 用 注 解 ， 将 bean 配 置 为 组 件 类 本 身 ， 而 不 是 使 用 XML 来 描 述 bean 装 配 。 默 认 情 况 下 ， Spring 容 器 中 未 打 开 注 解 装 配 。 因 此 ， 您 需 要 在 使 用 它 之 前 在 Spring 配 置 文 件 中 启 用 它 。 例 如 ：

```xml
<beans> 
	<context:annotation-config/> <!-- bean definitions go here --> 
</beans> 
```

### 3.2.3 基 于 Java API 配 置 

​	Spring 的 Java 配 置 是 通 过 使 用 @Bean 和 @Configuration 来 实 现 。 

* @Bean 注 解 扮 演 与 <bean/> 元 素 相 同 的 角 色 。 
* @Configuration 类 允 许 通 过 简 单 地 调 用 同 一 个 类 中 的 其 他 @Bean 方 法 来 定 义 bean 间 依 赖 关 系 。 例 如 ：

```java
@Configuration
    public class StudentConfig {
        @Bean
        public StudentBean myStudent() {
            return new StudentBean();
        }
    }
```

## 3.3 spring 支持集中 bean scope？ 

​	Spring bean 支 持 5 种 scope： 

* Singleton - 每 个 Spring IoC 容 器 仅 有 一 个 单 实 例 。 

* Prototype - 每 次 请 求 都 会 产 生 一 个 新 的 实 例 。 

* Request - 每 一 次 HTTP 请 求 都 会 产 生 一 个 新 的 实 例 ， 并 且 该 bean 仅 在 当 前 HTTP 请 求 内 有 效 。 

* Session - 每 一 次 HTTP 请 求 都 会 产 生 一 个 新 的 bean， 同时 该 bean 仅 在 当 前 HTTP session 内 有 效 。 

* Global-session - 类 似 于 标 准 的 HTTP Session 作 用 域 ， 不 过 它 仅 仅 在 基 于 portlet 的 web 应 用 中 才 有 意 义 。 

  ​	Portlet 规 范 定 义 了 全 局 Session 的 概 念 ， 它 被 所 有 构 成 某 个 portlet web 应 用 的 各 种 不 同 的 portlet 所 共 享 。 在 global session 作 用 域 中 定 义 的 bean 被 限 定 于 全 局 portlet Session 的 生 命 周 期 范 围 内 。 如 果 你 在 web 中 使 用 global session 作 用 域 来 标 识 bean，那么 web 会 自 动 当 成 session 类 型 来 使 用 。 仅 当 用 户 使 用 支 持 Web 的 ApplicationContext 时 ， 最 后 三 个 才 可 用 。

   

## 3.4 spring bean 容器的生命周期是什么样的？

​	spring bean 容 器 的 生 命 周 期 流 程 如 下 ： 

* Spring 容 器 根 据 配 置 中 的 bean 定 义 中 实 例 化 bean。
* Spring 使 用 依 赖 注 入 填 充 所 有 属 性 ， 如 bean 中 所 定 义 的 配 置 。 
* 如 果 bean 实 现 BeanNameAware 接 口 ， 则 工 厂 通 过 传 递 bean 的 ID 来 调 用 setBeanName()。
* 如果 bean 实 现 BeanFactoryAware 接 口 ， 工 厂 通 过 传 递 自 身 的 实 例 来 调 用 setBeanFactory()。
* 如果存在与 bean 关 联 的 任 何 BeanPostProcessors，则调用 preProcessBeforeInitialization() 方 法 。
*  如 果 为 bean 指 定 了 init 方 法 （ <bean> 的 init-method 属 性 ） ， 那 么 将 调 用 它 。
* 最 后 ， 如 果 存 在 与 bean 关 联 的 任 何 BeanPostProcessors，则将调用 postProcessAfterInitialization() 方 法 。 
*  如 果 bean 实 现 DisposableBean 接 口 ， 当 spring 容 器 关 闭 时 ， 会 调 用 destory()。
* 如果为 bean 指 定 了 destroy 方法（ <bean> 的 destroy-method 属性），那么将 调 用 它 。 

## 3.5 什么是 spring 的内部 bean？ 

​	只 有 将 bean 用 作 另 一 个 bean 的 属 性 时 ， 才 能 将 bean 声 明 为 内 部 bean。 为 了 定 义 bean，Spring 的 基 于 XML 的 配 置 元 数 据 在 <property> 或 <constructor-arg> 中 提 供 了 <bean> 元 素 的 使 用 。 内 部 bean 总 是 匿 名 的 ， 它 们 总 是 作 为 原 型 。 例 如 ， 假 设 我 们 有 一 个 Student 类 ， 其 中 引 用 了 Person 类 。 这 里 我 们 将 只 创 建 一 个 Person 类 实 例 并 在 Student 中 使 用 它 。 

Student.java

```java
public class Student {
        private Person person; //Setters and Getters
    }

    public class Person {
        private String name;
        private String address; //Setters and Getters }
    }
```

bean.xml

```xml
<bean id=“StudentBean" class="com.edureka.Student">
    <property name="person"> <!--This is inner bean -->
        <bean class="com.edureka.Person">
        <property name="name" value=“Scott"></property>
    	<property name="address" value=“Bangalore"></property> 
     	</bean> 
    </property> 
</bean>
```



## 3.6 什么是 spring 装配

​	当 bean 在 Spring 容 器 中 组 合 在 一 起 时 ， 它 被 称 为 装 配 或 bean 装配。Spring 容 器 需 要 知 道 需 要 什 么 bean 以 及 容 器 应 该 如 何 使 用 依 赖 注 入 来 将 bean 绑 定 在 一 起 ， 同 时 装 配 bean。 

## 3.7 自动装配有哪些方式？
​	Spring 容 器 能 够 自 动 装 配 bean。 也 就 是 说 ， 可 以 通 过 检 查 BeanFactory 的 内 容 让 Spring 自 动 解 析 bean 的 协 作 者 。 

自 动 装 配 的 不 同 模 式 ： 

* no - 这 是 默 认 设 置 ， 表 示 没 有 自 动 装 配 。 应 使 用 显 式 bean 引 用 进 行 装 配 。 
* byName - 它 根 据 bean 的 名 称 注 入 对 象 依 赖 项 。 它 匹 配 并 装 配 其 属 性 与 XML 文 件 中 由 相 同 名 称 定 义 的 bean。
* byType - 它 根 据 类 型 注 入 对 象 依 赖 项 。 如 果 属 性 的 类 型 与 XML 文 件 中 的 一 个 bean 名 称 匹 配 ， 则 匹 配 并 装 配 属 性 。 
* 构 造 函 数 - 它 通 过 调 用 类 的 构 造 函 数 来 注 入 依 赖 项 。 它 有 大 量 的 参 数 。 
* autodetect - 首 先 容 器 尝 试 通 过 构 造 函 数 使 用 autowire 装配，如果不能，则尝试通过 byType 自 动 装 配 。 

## 3.8 自动装配有什么局限？ 

* 覆 盖 的 可 能 性 - 您 始 终 可 以 使 用 <constructor-arg> 和 <property> 设 置 指 定 依 赖 项 ， 这 将 覆 盖 自 动 装 配 。 
* 基 本 元 数 据 类 型 - 简 单 属 性 （ 如 原 数 据 类 型 ， 字 符 串 和 类 ） 无 法 自 动 装 配 。 
* 令 人 困 惑 的 性 质 - 总 是 喜 欢 使 用 明 确 的 装 配 ， 因 为 自 动 装 配 不 太 精 确 。 

# 四、注解 

## 4.1 什么是基于注解的容器配置

​	 不 使 用 XML 来 描 述 bean 装 配 ， 开 发 人 员 通 过 在 相 关 的 类 ， 方 法 或 字 段 声 明 上 使 用 注 解 将 配 置 移 动 到 组 件 类 本 身 。 它 可 以 作 为 XML 设 置 的 替 代 方 案 。 例 如 ： Spring 的 Java 配 置 是 通 过 使 用 @Bean 和 @Configuration 来 实 现 。
​	@Bean 注 解 扮 演 与 元 素 相 同 的 角 色 。 @Configuration 类 允 许 通 过 简 单 地 调 用 同 一 个 类 中 的 其 他 @Bean 方 法 来 定 义 bean 间 依 赖 关 系 。 例 如 ： 

```java
@Configuration 
    public class StudentConfig {
        @Bean 
        public StudentBean myStudent() {
            return new StudentBean(); 
        } 
    }
```



## 4.2 如何在 spring 中启动注解装配？ 

​	默 认情 况 下， Spring 容 器 中 未 打 开 注 解 装 配 。 因 此 ， 要 使 用 基 于 注 解 装 配 ， 我 们 必 须 通 过 配 置 <context：annotation-config/> 元 素 在 Spring 配 置 文 件 中 启 用 它 。 

## 4.3 @Component, @Controller, @Repository, @Service 有何区别？

* @Component ： 这 将 java 类 标 记 为 bean。 它 是 任 何 Spring 管 理 组 件 的 通 用 构 造 型 。 spring 的 组 件 扫 描 机 制 现 在 可 以 将 其 拾 取 并 将 其 拉 入 应 用 程 序 环 境 中 。 
* @Controller ： 这 将 一 个 类 标 记 为 Spring Web MVC 控 制 器 。 标 有 它 的 Bean 会 自 动 导 入 到 IoC 容 器 中 。 
* @Service ： 此 注 解 是 组 件 注 解 的 特 化 。 它 不 会 对 @Component 注 解 提 供 任 何 其 他 行 为 。 您 可 以 在 服 务 层 类 中 使 用@Service 而 不 是 @Component， 因 为 它 以 更 好 的 方 式 指 定 了 意 图 。 
* @Repository ： 这 个 注 解 是 具 有 类 似 用 途 和 功 能 的 @Component 注 解 的 特 化 。 它 为 DAO 提 供 了 额 外 的 好 处 。 它 将 DAO 导 入 IoC 容 器 ， 并 使 未 经 检 查 的 异 常 有 资 格 转 换 为 Spring DataAccessException。 

## 4.4 @Required 注解有什么用？ 

​	@Required 应 用 于 bean 属 性 setter 方 法 。 此 注 解 仅 指 示 必 须 在 配 置 时 使 用 bean 定 义 中 的 显 式 属 性 值 或 使 用 自 动 装 配 填 充 受 影 响 的 bean 属 性 。 如 果 尚 未 填 充 受 影 响 的 bean 属 性 ， 则 容 器 将 抛 出 BeanInitializationException。 示 例 ： 

```java
public class Employee {
        private String name;

        @Required
        public void setName(String name) {
            this.name = name;
        }

        public string getName() {
            return name;
        }
    }
```



## 4.5 @Autowired 注解有什么用？

​	@Autowired 可 以 更 准 确 地 控 制 应 该 在 何 处 以 及 如 何 进 行 自 动 装 配 。 此 注 解 用 于 在 setter 方 法 ， 构 造 函 数 ， 具 有 任 意 名 称 或 多 个 参 数 的 属 性 或 方 法 上 自 动 装 配 bean。 默 认 情 况 下 ， 它 是 类 型 驱 动 的 注 入 。

```java
public class Employee {
        private String name;

        @Autowired
        public void setName(String name) {
            this.name = name;
        }

        public string getName() {
            return name;
        }
    }
```



## 4.6 @Qualifier 注解有什么用？

 	当 您 创 建 多 个 相 同 类 型 的 bean 并 希 望 仅 使 用 属 性 装 配 其 中 一 个 bean 时，您可 以 使 用 @Qualifier 注 解 和 @Autowired 通 过 指 定 应 该 装 配 哪 个 确 切 的 bean 来 消 除 歧 义 。 例 如 ， 这 里 我 们 分 别 有 两 个 类 ， Employee 和 EmpAccount。在 EmpAccount 中 ， 使 用 @Qualifier 指 定 了 必 须 装 配 id 为 emp1 的 bean。 

Employee.java

```java
public class Employee {
        private String name;

        @Autowired
        public void setName(String name) {
            this.name = name;
        }

        public string getName() {
            return name;
        }
    }
```

EmpAccount.java

```java
public class EmpAccount {
        private Employee emp;

        @Autowired
        @Qualifier(emp1)
        public void showName() {
            System.out.println(“Employee name : ”+emp.getName);
        }
    }
```



## 4.7 @RequestMapping 注解有什么用？

​	@RequestMapping 注 解 用 于 将 特 定 HTTP 请 求 方 法 映 射 到 将 处 理 相 应 请 求 的 控 制 器 中 的 特 定 类 /方 法 。 此 注 释 可 应 用 于 两 个 级 别 ： 

* 类 级 别 ： 映 射 请 求 的 URL 
* 方 法 级 别 ： 映 射 URL 以 及 HTTP 请 求 方 法 

# 五、数据访问 

## 5.1 spring DAO 有什么用？

​	Spring DAO 使 得 JDBC，Hibernate 或 JDO 这 样 的 数 据 访 问 技 术 更 容 易 以 一 种 统 一 的 方 式 工 作 。 这 使 得 用 户 容 易 在 持 久 性 技 术 之 间 切 换 。 它 还 允 许 您 在 编 写 代 码 时 ， 无 需 考 虑 捕 获 每 种 技 术 不 同 的 异 常 。

## 5.2 列举 Spring DAO 抛出的异常

 ![image-20201026122912466](E:\学习笔记\mylearnnote\web架构集\spring全家桶\springFramework\image\image-20201026122912466.png)

## 5.3 spring JDBC API 中存在哪些类？

* JdbcTemplate 
* SimpleJdbcTemplate 
* NamedParameterJdbcTemplate 
* SimpleJdbcInsert
* SimpleJdbcCall 

## 5.4 使用 Spring 访问 Hibernate 的方法有哪些？

​	我 们 可 以 通 过 两 种 方 式 使 用 Spring 访 问 Hibernate： 

* 使 用 Hibernate 模 板 和 回 调 进 行 控 制 反 转 
* 扩 展 HibernateDAOSupport 并 应 用 AOP 拦 截 器 节 点 

## 5.5 列举 spring 支持的事务管理类型

 Spring 支 持 两 种 类 型 的 事 务 管 理 ： 

* 程 序 化 事 务 管 理 ： 在 此 过 程 中 ， 在 编 程 的 帮 助 下 管 理 事 务 。 它 为 您 提 供 极 大 的 灵 活 性 ， 但 维 护 起 来 非 常 困 难 。
*  声 明 式 事 务 管 理 ： 在 此 ， 事 务 管 理 与 业 务 代 码 分 离 。 仅 使 用 注 解 或 基 于 XML 的 配 置 来 管 理 事 务 。 

## 5.6 spring 支持哪些 ORM 框架

* Hibernate 
* iBatis 
* JPA 
* JDO 
* OJB

# 六、AOP

## 6.1 什么是 AOP？

​	 AOP(Aspect-Oriented Programming), 即 面 向 切 面 编 程 , 它 与 OOP( Object-Oriented Programming, 面 向 对 象 编 程 ) 相 辅 相 成 , 提 供 了 与 OOP 不 同 的 抽 象 软 件 结 构 的 视 角 . 在 OOP 中 , 我 们 以 类 (class)作 为 我 们 的 基 本 单 元 , 而 AOP 中 的 基 本 单 元 是 Aspect(切面) 

## 6.2 什么是 Aspect？

​	 aspect 由 pointcount 和 advice 组 成 , 它 既 包 含 了 横 切 逻 辑 的 定 义 , 也 包 括 了 连 接 点 的 定 义 . Spring AOP 就 是 负 责 实 施 切 面 的 框 架 , 它 将 切 面 所 定 义 的 横 切 逻 辑 编 织 到 切 面 所 指 定 的 连 接 点 中 . AOP 的 工 作 重 心 在 于 如 何 将 增 强 编 织 目 标 对 象 的 连 接 点 上 , 这 里 包 含 两 个 工 作 :

* 如 何 通 过 pointcut 和 advice 定 位 到 特 定 的 joinpoint 上 

*  如 何 在 advice 中 编 写 切 面 代 码 .可 以 简 单 地 认 为 , 使 用 @Aspect 注 解 的 类 就 是 切 面 . 

  ![image-20201026123802886](E:\学习笔记\mylearnnote\web架构集\spring全家桶\springFramework\image\image-20201026123802886.png)

## 6.3 什么是切点（JoinPoint）

​	 程 序 运 行 中 的 一 些 时 间 点 , 例 如 一 个 方 法 的 执 行 , 或 者 是 一 个 异 常 的 处 理 . 在 Spring AOP 中 , join point 总 是 方 法 的 执 行 点 。 

## 6.4 什么是通知（Advice）？ 

​	特 定 JoinPoint 处 的 Aspect 所 采 取 的 动 作 称 为 Advice。Spring AOP 使 用 一 个 Advice 作 为 拦 截 器 ， 在 JoinPoint “周 围 ”维 护 一 系 列 的 拦 截 器 。

## 6.5 有哪些类型的通知（Advice）？

* Before - 这些类型的 Advice 在 joinpoint 方法之前执行，并使用 @Before 注解标记进行配置。 
* After Returning - 这些类型的 Advice 在连接点方法正常执行后执 行，并使用@AfterReturning 注解标记进行配置。 
* After Throwing - 这些类型的 Advice 仅在 joinpoint 方法通过抛出 异常退出并使用 @AfterThrowing 注解标记配置时执行。 
* After (finally) - 这些类型的 Advice 在连接点方法之后执行，无论方 法退出是正常还是异常返回，并使用 @After 注解标记进行配置。 
* Around - 这些类型的 Advice 在连接点之前和之后执行，并使用 @Around 注解标记进行配置。 

## 6.6 指出在 spring aop 中 concern 和 cross-cutting concern 的不同之处

​	concern 是 我 们 想 要 在 应 用 程 序 的 特 定 模 块 中 定 义 的 行 为 。 它 可 以 定 义 为 我 们 想 要 实 现 的 功 能 。 

​	cross-cutting concern 是 一 个 适 用 于 整 个 应 用 的 行 为 ， 这 会 影 响 整 个 应 用 程 序 。 例 如 ， 日 志 记 录 ， 安 全 性 和 数 据 传 输 是 应 用 程 序 几 乎 每 个 模 块 都 需 要 关 注 的 问 题 ， 因 此 它 们 是 跨 领 域 的 问 题 。 

## 6.7 AOP 有哪些实现方式？

实 现 AOP 的 技 术 ， 主 要 分 为 两 大 类 ：

### 6.7.1 静 态 代 理

​	 指 使 用 AOP 框 架 提 供 的 命 令 进 行 编 译 ， 从 而 在 编 译 阶 段 就 可 生 成 AOP 代 理 类 ， 因 此 也 称 为 编 译 时 增 强 ； 

	* 编译时编织（特殊编译器实现） 
	* 类加载时编织（特殊的类加载器实现）。 

### 6.7.2 动 态 代 理

​	 在 运 行 时 在 内 存 中 “临 时 ”生 成 AOP 动 态 代 理 类 ， 因 此 也 被 称 为 运 行 时 增 强 。 

* JDK 动态代理 
* CGLIB 

## 6.8 Spring AOP and AspectJ AOP 有什么区别？

	* Spring AOP 基 于 动 态 代 理 方 式 实 现 ； AspectJ 基 于 静 态 代 理 方 式 实 现 。 
	* Spring AOP 仅 支 持 方 法 级 别 的 PointCut； AspectJ 提供 了 完全 的 AOP 支 持 ， 它 还 支 持 属 性 级 别 的 PointCut。 

## 6.9 如何理解 Spring 中的代理？

​	将 Advice 应 用 于 目 标 对 象 后 创 建 的 对 象 称 为 代 理 。 在 客 户 端 对 象 的 情 况 下 ， 目 标 对 象 和 代 理 对 象 是 相 同 的 。
​	Advice + Target Object = Proxy 

## 6.10 什么是编织（Weaving）？ 

​	为 了 创 建 一 个 advice 对 象 而 链 接 一 个 aspect 和 其 它 应 用 类 型 或 对 象 ， 称 为 编 织（Weaving）。在 Spring AOP 中 ， 编 织 在 运 行 时 执 行 。 请 参 考 下 图 ： 

![image-20201026174220589](E:\学习笔记\mylearnnote\web架构集\spring全家桶\springFramework\image\image-20201026174220589.png)

# 7 MVC

## 7.1 Spring MVC 框架有什么用？ 

​	Spring Web MVC 框 架 提 供 模 型 -视 图 -控 制 器 架 构 和 随 时 可 用 的 组 件 ， 用 于 开 发 灵 活 且 松 散 耦 合 的 Web 应 用 程 序 。 MVC 模 式 有 助 于 分 离 应 用 程 序 的 不 同 方 面 ， 如 输 入 逻 辑 ， 业 务 逻 辑 和 UI 逻 辑 ， 同 时 在 所 有 这 些 元 素 之 间 提 供 松 散 耦 合 。 

## 7.2 描述一下 DispatcherServlet 的工作流程

 DispatcherServlet 的 工 作 流 程 可 以 用 一 幅 图 来 说 明 ：

![image-20201026174616101](E:\学习笔记\mylearnnote\web架构集\spring全家桶\springFramework\image\image-20201026174616101.png)

*  向 服 务 器 发 送 HTTP 请 求 ， 请 求 被 前 端 控 制 器 DispatcherServlet 捕 获 。
* DispatcherServlet 根 据 -servlet.xml 中 的 配 置 对 请 求 的 URL 进 行 解 析 ， 得 到 请 求 资 源 标 识 符 （ URI） 。 然 后 根 据 该 URI，调用 HandlerMapping 获 得 该 Handler 配 置 的 所 有 相 关 的 对 象 （ 包 括 Handler 对 象 以 及 Handler 对 象 对 应 的 拦 截 器 ） ， 最 后 以 HandlerExecutionChain 对 象 的 形 式 返 回 。
* DispatcherServlet 根 据 获 得 的 Handler， 选 择 一 个 合 适 的 HandlerAdapter。（附注：如果成功获得 HandlerAdapter 后，此时将开始 执 行 拦 截 器 的 preHandler(...)方法）。
* 提 取 Request 中 的 模 型 数 据 ， 填 充 Handler 入 参 ， 开 始 执 行 Handler （ Controller)。 在 填 充 Handler 的 入 参 过 程 中 ， 根 据 你 的 配 置 ， Spring 将 帮 你 做 一 些 额 外 的 工 作 ：
  * HttpMessageConveter：将请求消息（如 Json、xml 等数据）转换 成一个对象，将对象转换为指定的响应信息。 
  * 数据转换：对请求消息进行数据转换。如 String 转换成 Integer、 Double 等。 
  * 数据根式化：对请求消息进行数据格式化。如将字符串转换成格式化数字 或格式化日期等。
  * 数据验证：验证数据的有效性（长度、格式等），验证结果存储到 BindingResult 或 Error 中。
* Handler(Controller)执行完成后，向 DispatcherServlet 返 回 一 个 ModelAndView 对 象 ；
* 根据返回的 ModelAndView，选择一个适合的 ViewResolver（ 必 须 是 已 经 注 册 到 Spring 容 器 中 的 ViewResolver)返 回 给 DispatcherServlet。
* ViewResolver 结 合 Model 和 View， 来 渲 染 视 图 。
* 视 图 负 责 将 渲 染 结 果 返 回 给 客 户 端 。 

## 7.3 介绍一下 WebApplicationContext 

​	WebApplicationContext 是 ApplicationContext 的 扩 展 .它 具 有 Web 应 用 程 序 所 需 的 一 些 额 外 功 能 。 它 与 普 通 的 ApplicationContext 在 解 析 主 题 和 决 定 与 哪 个 servlet 关 联 的 能 力 方 面 有 所 不 同 。 英 文 原 文 链 接 ： https://www.edureka.co/blog/interview-questions/spring-interview-questions/

