- 使用 Windows 系统的电脑

  1、下载安装 Windows SSH 和 Telnet 客户端工具 Putty。[下载Putty](http://www.putty.org/)

  2、用户名：root，Host：49.232.191.12

  3、按照 Putty 使用帮助进行登录。[Putty 密码方式使用帮助](https://cloud.tencent.com/doc/product/213/2029)

- 使用 Linux/Mac OS X 系统的电脑（使用密码登录）

  1、打开 SSH 客户端（Mac可使用系统自带的终端）

  2、输入ssh -q -l root -p 22 49.232.191.12

  3、输入 CVM 实例密码进行登录。

- 使用 Linux/Mac OS X 系统的电脑（使用密钥登录）

  1、打开 SSH 客户端（Mac可使用系统自带的终端）。

  2、查找您云服务器关联的 SSH 密钥文件本地存放地址。

  3、您的密钥必须不公开可见，SSH 才能工作。请使用此命令：chmod 400 [密钥文件路径]。

  4、输入命令：ssh [-i 密钥文件路径] root@49.232.191.12。