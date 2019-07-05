# 1. 配置自己的身份

```tex
git config --global user.name "名字"

git config --global user.email "邮箱地址"
```

# 2.创建代码仓库

```
git init
```

# 3.提交本地代码

```
git add . 提交所有

git add +文件名 提交单个文件

git commit -m "First commit"

这里要在-m参数后面加上提交参数，很重要，不然会被认为不合法不能提交.
```

# 4.本地仓库与远程仓库关联

```
git remote add origin https://github.com/zhangjiale8/mylearnnote.git
```

# 5.推送/提交到远程某个分支

```
 git push -u origin master
 远程库是空的，我们第一次推送master分支时，加上了-u参数，Git不但会把本地的master分支内容推送的远程新的master分支，还会把本地的master分支和远程的master分支关联起来，在以后的推送或者拉取时就可以简化命令
 
 git push origin master
 本地master分支的最新修改推送至GitHub
```

# 6. git克隆远程仓库内容

```
 git clone https://github.com/zhangjiale8/mylearnnote.git
```

# 7.获取远程库与本地同步

```
git pull
以在你的工作目录中 获取（fetch） 并 合并（merge） 远端的改动。
要合并其他分支到你的当前分支（例如 master），执行：
git merge <branch>
两种情况下，git 都会尝试去自动合并改动。不幸的是，自动合并并非次次都能成功，并可能导致 冲突（conflicts）。 

```

# 8.文件版本库中的文件状态

```
git status
```

# 9.对比文件修改前和修改后的变化

```
git diff
```

# 10.新增文件

```
git add .

git commit -m "add new data"

git push -u origin master
```

# 11.删除文件

```
git rm -r  '需要删除的文件夹'

git  commit -m "delete data"

git push -u origin master
```

