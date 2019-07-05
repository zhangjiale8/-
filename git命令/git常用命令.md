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

测试