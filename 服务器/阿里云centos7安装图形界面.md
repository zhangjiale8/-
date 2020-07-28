CentOS 7 系统下，本文以 MATE 桌面环境安装进行安装配置说明：

  登录服务器，执行如下指令安装桌面环境：

  \# 先安装 MATE Desktop
  yum groups install "MATE Desktop"

  命令输入之后，会列出一大堆文字的，然后显示这个y/d/n，输入y，按回车下载安装；
  安装完成，显示下面图片complete


  \#安装好 MATE Desktop 后，再安装 X Window System。
  yum groups install "X Window System"

  命令输入之后，会列出一大堆文字的，然后显示这个y/d/n，输入y，按回车下载安装；


  安装完成


  设置默认通过桌面环境启动服务器：

  systemctl set-default graphical.target

  systemctl set-default multi-user.target //设置成命令模式

  systemctl set-default graphical.target //设置成图形模式
  安装完成后，通过 reboot 等指令重启服务器，或者在 ECS 服务器控制台重启服务器。

选择第一个，按回车
  通过 管理终端 连接服务器，验证测试安装情况。在ECS控制台，用管理终端登录服务器，查看安装好的桌面。