# 缺点：

  1、单个缓存数据有限制，每次最大为1M

  2、key限制为250byte

  3、不支持数据持久化

  4、无安全支持

  5、过期超时时间限制

 

 

  缓存限制：

  单个缓存限制，默认最大的为1M，当单次存储的数据超过1M时，会存储不到缓存中

  当存储的数据大于1M，可以考虑在客户端将数据拆分，分别进行存储

 

 key限制：

  memcached是根据key-value来进行存储数据的，key默认长度不能超过250byte

  key的长度不要太长，key太长会浪费内存和带宽

  key要求只要不重复就可以

  key不能为空格和[控制字符](http://baike.baidu.com/link?url=AV3IP7yVoGdiuKvFvK0tOg1g2P1hnc00w8y3qSVoCsxlNAfwxIQl_XsSMLmAuypjor4z3muE_pt3QeQBp0eX2K)（点击了解控制字符）

 

 不支持数据持久化：

  一旦服务器重启或服务器故障，memcached中的数据就会全部丢失

 

 无安全支持：

  memcached的本身没有权限认证机制，用户不要用户名和密码，只要在客户端中代码中连接上就可以连接到

  服务端，直接从缓存章读取数据。

  解决方案：

​    将memcached安装在防火墙之后（如图）

  ![img](http://img.blog.csdn.net/20160224155327665?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

 

 过期超时时间限制：

   Expiration times can be set from 0, meaning "never expire", to 30 days. Any time higher than

  30 days is interpreted as a unix timestamp date.

  过期超时时间的设置可以为0-30天，当为0时，即设置为“永不过期”。任何超过30天的时间被解释为一个

  Unix时间戳

 

# 总结：

  memcached的这些缺点正是我们在应用中必须注意的问题，当我们注意到这些问题的时候就能在项目中发挥

  它的巨大作用，让我们的用户能够有更好的用户体验，当然还有很多问题我们已经解决，比如数据持久化我

  们可以采用代理和集群来解决，这些正在努力中。。。 