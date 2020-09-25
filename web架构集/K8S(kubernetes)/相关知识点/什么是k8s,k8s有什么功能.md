# 1. 什么是k8s

k8s全称kubernetes，k8s是一个docker集群的管理工具

# 2. k8s的核心功能



```undefined
自愈: 重新启动失败的容器，在节点不可用时，替换和重新调度节点上的容器，对用户定义的健康检查不响应的容器会被中止，并且在容器准备好服务之前不会把其向客户端广播。
弹性伸缩: 通过监控容器的cpu的负载值,如果这个平均高于80%,增加容器的数量,如果这个平均低于10%,减少容器的数量
服务的自动发现和负载均衡: 不需要修改您的应用程序来使用不熟悉的服务发现机制，Kubernetes 为容器提供了自己的 IP 地址和一组容器的单个 DNS 名称，并可以在它们之间进行负载均衡。
滚动升级和一键回滚: Kubernetes 逐渐部署对应用程序或其配置的更改，同时监视应用程序运行状况，以确保它不会同时终止所有实例。 如果出现问题，Kubernetes会为您恢复更改，利用日益增长的部署解决方案的生态系统。
```

# 3. k8s的历史

```css
2014年 docker容器编排工具，立项
2015年7月 发布kubernetes 1.0, 加入cncf
2016年，kubernetes干掉两个对手，docker swarm，mesos 1.2版
2017年
2018年 k8s 从cncf基金会 毕业
2019年： 1.13, 1.14 ，1.15
cncf cloud native compute foundation
kubernetes （k8s）: 希腊语 舵手，领航 容器编排领域，
谷歌16年容器使用经验，borg容器管理平台，使用golang重构borg，kubernetes
```

# 4. k8s的安装

```css
yum安装 1.5 最容易安装成功，最适合学习的
源码编译安装---难度最大 可以安装最新版
二进制安装---步骤繁琐 可以安装最新版 shell,ansible,saltstack
kubeadm 安装最容易, 网络 可以安装最新版
minikube 适合开发人员体验k8s, 网络
```

# 5. k8s的应用场景

```tex
k8s最适合跑微服务项目!
```

# 6. k8s常用的资源

## 6.1 创建pod资源

```bash
k8s yaml的主要组成
apiVersion: v1  api版本
kind: pod   资源类型
metadata:   属性
spec:       详细

k8s_pod.yaml
apiVersion: v1
kind: Pod
metadata:
 name: nginx
 labels:
 app: web
spec:
 containers:
 - name: nginx
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80

pod资源:至少由两个容器组成,pod基础容器和业务容器组成
pod配置文件2：
apiVersion: v1
kind: Pod
metadata:
 name: test
 labels:
 app: web
spec:
 containers:
 - name: nginx
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80
 - name: busybox
 image: 10.0.0.11:5000/busybox:latest
 command: ["sleep","10000"]

pod是k8s最小的资源单位
```

## 6.2 ReplicationController资源

```yaml
rc:保证指定数量的pod始终存活,rc通过标签选择器来关联pod
k8s资源的常见操作:  
kubectl create -f xxx.yaml  
kubectl get pod|rc  
kubectl describe pod nginx  
kubectl delete pod nginx 
或者
kubectl delete -f xxx.yaml  
kubectl edit pod nginx

创建一个rc
apiVersion: v1
kind: ReplicationController
metadata:
 name: nginx
spec:
 replicas: 5
 selector:
 app: myweb
 template:
 metadata:
 labels:
 app: myweb
 spec:
 containers:
 - name: myweb
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80

rc的滚动升级  新建一个nginx-rc1.15.yaml
升级  kubectl rolling-update nginx -f nginx-rc1.15.yaml --update-period=10s
回滚  kubectl rolling-update nginx2 -f nginx-rc.yaml --update-period=1s
```

## 6.3 service资源

```bash
service帮助pod暴露端口
创建一个service
apiVersion: v1
kind: Service
metadata:
 name: myweb
spec:
 type: NodePort  #ClusterIP
 ports:
 - port: 80          #clusterIP
 nodePort: 30000   #nodeport
 targetPort: 80    #podport
 selector:
 app: myweb2

修改nodePort范围
vim  /etc/kubernetes/apiserver
KUBE_API_ARGS="--service-node-port-range=3000-50000"</pre>
service默认使用iptables来实现负载均衡, k8s 1.8新版本中推荐使用lvs(四层负载均衡)
```

## 6.4 deployment资源

```bash
有rc在滚动升级之后,会造成服务访问中断,于是k8s引入了deployment资源
创建deployment
apiVersion: extensions/v1beta1
kind: Deployment
metadata:
 name: nginx-deployment
spec:
 replicas: 3
 template:
 metadata:
 labels:
 app: nginx
 spec:
 containers:
 - name: nginx
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80
 resources:
 limits:
 cpu: 100m
 requests:
 cpu: 100m
deployment升级和回滚
命令行创建deployment
kubectl run nginx --image=10.0.0.11:5000/nginx:1.13 --replicas=3 --record
命令行升级版本
kubectl set image deploy nginx nginx=10.0.0.11:5000/nginx:1.15
查看deployment所有历史版本
kubectl rollout history deployment nginx
deployment回滚到上一个版本
kubectl rollout undo deployment nginx
deployment回滚到指定版本
kubectl rollout undo deployment nginx --to-revision=2
```

## 6.5 tomcat+mysql练习

```undefined
在k8s中容器之间相互访问,通过VIP地址!
```

# 7. k8s的附加组件

## 7.1 dns服务

```csharp
安装dns服务
1:下载dns_docker镜像包
wget [http://192.168.12.201/docker_image/docker_k8s_dns.tar.gz](http://192.168.12.201/docker_image/docker_k8s_dns.tar.gz)
2:导入dns_docker镜像包(node2节点)
3:修改skydns-rc.yaml
spec:
 nodeSelector:
 kubernetes.io/hostname: 10.0.0.13
 containers:

4:创建dns服务

kubectl create -f skydns-rc.yaml

5:检查

kubectl get all --namespace=kube-system

6:修改所有node节点kubelet的配置文件

vim /etc/kubernetes/kubelet

KUBELET_ARGS="--cluster_dns=10.254.230.254 --cluster_domain=cluster.local"

systemctl restart kubelet
```

## 7.2 namespace命令空间

```cpp
namespace做资源隔离
```

## 7.3 健康检查

### 7.3.1 探针的种类



```undefined
livenessProbe：健康状态检查，周期性检查服务是否存活，检查结果失败，将重启容器
readinessProbe：可用性检查，周期性检查服务是否可用，不可用将从service的endpoints中移除
```

#### 4.3.2 探针的检测方法



```bash
*   exec：执行一段命令
*   httpGet：检测某个 http 请求的返回状态码
*   tcpSocket：测试某个端口是否能够连接
```

#### 4.3.3 liveness探针的exec使用



```bash
vi  nginx_pod_exec.yaml 
apiVersion: v1
kind: Pod
metadata:
 name: exec
spec:
 containers:
 - name: nginx
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80
 args:
 - /bin/sh
 - -c
 - touch /tmp/healthy; sleep 30; rm -rf /tmp/healthy; sleep 600
 livenessProbe:
 exec:
 command:
 - cat
 - /tmp/healthy
 initialDelaySeconds: 5
 periodSeconds: 5
```

#### 4.3.4 liveness探针的httpGet使用



```undefined
vi   nginx_pod_httpGet.yaml 
apiVersion: v1
kind: Pod
metadata:
 name: httpget
spec:
 containers:
 - name: nginx
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80
 livenessProbe:
 httpGet:
 path: /index.html
 port: 80
 initialDelaySeconds: 3
 periodSeconds: 3
```

#### 4.3.5 liveness探针的tcpSocket使用



```undefined
vi   nginx_pod_tcpSocket.yaml
apiVersion: v1
kind: Pod
metadata:
 name: tcpSocket
spec:
 containers:
 - name: nginx
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80
 livenessProbe:
 tcpSocket:
 port: 80
 initialDelaySeconds: 3
 periodSeconds: 3
```

#### 4.3.6 readiness探针的httpGet使用



```cpp
vi   nginx-rc-httpGet.yaml
apiVersion: v1
kind: ReplicationController
metadata:
 name: readiness
spec:
 replicas: 2
 selector:
 app: readiness
 template:
 metadata:
 labels:
 app: readiness
 spec:
 containers:
 - name: readiness
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80
 readinessProbe:
 httpGet:
 path: /qiangge.html
 port: 80
 initialDelaySeconds: 3
 periodSeconds: 3
```

### 4.4 dashboard服务



```cpp
1:上传并导入镜像,打标签
2:创建dashborad的deployment和service
3:访问[http://10.0.0.11:8080/ui/](http://10.0.0.11:8080/ui/)
```

### 4.5 通过apiservicer反向代理访问service



```bash
第一种：NodePort类型 
type: NodePort
 ports:
 - port: 80
 targetPort: 80
 nodePort: 30008

第二种：ClusterIP类型
 type: ClusterIP
 ports:
 - port: 80
 targetPort: 80</pre>
```

## 5: k8s弹性伸缩



```undefined
k8s弹性伸缩,需要附加插件heapster监控
```

### 5.1 安装heapster监控



```bash
1:上传并导入镜像,打标签

ls *.tar.gz  for n in `ls *.tar.gz`;do docker load -i $n ;done  docker tag docker.io/kubernetes/heapster_grafana:v2.6.0 10.0.0.11:5000/heapster_grafana:v2.6.0  docker tag docker.io/kubernetes/heapster_influxdb:v0.5 10.0.0.11:5000/heapster_influxdb:v0.5  docker tag docker.io/kubernetes/heapster:canary 10.0.0.11:5000/heapster:canary

2:上传配置文件,kubectl create -f .

3:打开dashboard验证
```

### 5.2 弹性伸缩



```swift
1:修改rc的配置文件
containers:
 - name: myweb
 image: 10.0.0.11:5000/nginx:1.13
 ports:
 - containerPort: 80
 resources:
 limits:
 cpu: 100m
 requests:
 cpu: 100m
2:创建弹性伸缩规则
kubectl autoscale -n qiangge replicationcontroller myweb --max=8 --min=1 --cpu-percent=8
3:测试
ab -n 1000000 -c 40 [http://172.16.28.6/index.html](http://172.16.28.6/index.html)
ab -n 300000 -c 100 [http://172.16.23.14/index.html](http://172.16.23.14/index.html)
```

扩容截图

![img](https:////upload-images.jianshu.io/upload_images/16861561-c919323e826d14e1.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

![img](https:////upload-images.jianshu.io/upload_images/16861561-f0a00385cb701b39.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

缩容:

![img](https:////upload-images.jianshu.io/upload_images/16861561-96c109ffacaed9c5.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

![img](https:////upload-images.jianshu.io/upload_images/16861561-6db61c748b0d21d4.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

![img](https:////upload-images.jianshu.io/upload_images/16861561-315ca8cd2a27afec.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

### 6:持久化存储



```cpp
pv: persistent volume 全局的资源 pv，node
pvc: persistent volume claim 局部的资源（namespace）pod，rc，svc
```

### 6.1:安装nfs服务端(10.0.0.11)



```kotlin
yum install nfs-utils.x86_64 -y (所有节点)
mkdir /data 
vim /etc/exports 
/data 10.0.0.0/24(rw,async,no_root_squash,no_all_squash) 
systemctl start rpcbind 
systemctl start nfs
```

### 6.2:在node节点安装nfs客户端



```css
yum install nfs-utils.x86_64 -y 
showmount -e 10.0.0.11
```

### 6.3:创建pv和pvc



```undefined
上传yaml配置文件,创建pv和pvc
```

### 6.4:创建mysql-rc,pod模板里使用volume



```csharp
volumeMounts: 
- name: mysql 
  mountPath: /var/lib/mysql 
volumes: 
- name: mysql 
  persistentVolumeClaim: 
      claimName: tomcat-mysql
```

### 6.5: 验证持久化



```cpp
验证方法1:删除mysql的pod,数据库不丢
kubectl delete pod mysql-gt054
验证方法2:查看nfs服务端,是否有mysql的数据文件
```

![img](https:////upload-images.jianshu.io/upload_images/16861561-ecb949e2448166a9.png?imageMogr2/auto-orient/strip|imageView2/2/w/831/format/webp)

image.png

### 6.6: 分布式存储glusterfs

![img](https:////upload-images.jianshu.io/upload_images/16861561-b33d1a638b7f75a8.png?imageMogr2/auto-orient/strip|imageView2/2/w/829/format/webp)

image.png

- a: 什么是glusterfs



```undefined
Glusterfs是一个开源分布式文件系统，具有强大的横向扩展能力，可支持数PB存储容量和数千客户端，通过网络互
联成一个并行的网络文件系统。具有可扩展性、高性能、高可用性等特点。
```

- b: 安装glusterf



```bash
所有节点： 
yum install centos-release-gluster -y 
yum install glusterfs-server -y 
systemctl start glusterd.service 
systemctl enable glusterd.service 
mkdir -p /gfs/test1 
mkdir -p /gfs/test2
```

- c: 添加存储资源池



```cpp
master节点： 
gluster pool list 
gluster peer probe k8s-node1 
gluster peer probe k8s-node2 
gluster pool list
```

- d: glusterfs卷管理



```csharp
创建分布式复制卷 
gluster volume create qiangge replica 2 k8s-master:/gfs/test1 k8s-master:/gfs/test2 k8s- node1:/gfs/test1 k8s-node1:/gfs/test2 force 
启动卷 
gluster volume start qiangge 
查看卷 
gluster volume info qiangge 
挂载卷 
[root@glusterfs01 ~]# mount -t glusterfs 10.0.0.14:/qiangge /mnt
[root@glusterfs01 ~]# df -h
Filesystem          Size  Used Avail Use% Mounted on
/dev/sda2            48G  1.8G   47G   4% /
/dev/sdb             10G   33M   10G   1% /gfs/test1
/dev/sdc             10G   33M   10G   1% /gfs/test2
10.0.0.14:/qiangge   30G  404M   30G   2% /mnt
```

- e: 分布式复制卷讲解

![img](https:////upload-images.jianshu.io/upload_images/16861561-7050aa54a45aadcd.png?imageMogr2/auto-orient/strip|imageView2/2/w/837/format/webp)

image.png

- f: 分布式复制卷扩容



```csharp
扩容前查看容量： 
df -h 
扩容命令： 
gluster volume add-brick qiangge k8s-node2:/gfs/test1 k8s-node2:/gfs/test2 force 
扩容后查看容量: 
[root@glusterfs01 ~]# df -h
Filesystem          Size  Used Avail Use% Mounted on
/dev/sda2            48G  1.8G   47G   4% /
/dev/sdb             10G   33M   10G   1% /gfs/test1
/dev/sdc             10G   33M   10G   1% /gfs/test2
10.0.0.14:/qiangge   30G  404M   30G   2% /mnt
```

### 6.7   k8s 对接glusterfs存储

- a：创建endpoint



```css
vi  glusterfs-ep.yaml
apiVersion: v1
kind: Endpoints
metadata:
  name: glusterfs
  namespace: default
subsets:
- addresses:
  - ip: 10.0.0.11
  - ip: 10.0.0.12
  - ip: 10.0.0.13
  ports:
  - port: 49152
    protocol: TCP
```

- b:  创建service



```tsx
vi  glusterfs-svc.yaml
apiVersion: v1
kind: Service
metadata:
  name: glusterfs
  namespace: default
spec:
  ports:
  - port: 49152
    protocol: TCP
    targetPort: 49152
  sessionAffinity: None
  type: ClusterIP
```

- c: 创建gluster类型pv



```bash
apiVersion: v1
kind: PersistentVolume
metadata:
  name: gluster
  labels:
    type: glusterfs
spec:
  capacity:
    storage: 50Gi
  accessModes:
    - ReadWriteMany
  glusterfs:
    endpoints: "glusterfs"
    path: "qiangge"
    readOnly: false
```

- d:  创建pvc



```bash
vim gluster_pvc.yaml
kind: PersistentVolumeClaim
apiVersion: v1
metadata:
  name: gluster
spec:
  selector:
    matchLabels:
      type: glusterfs
  accessModes:
    - ReadWriteMany
  resources:
    requests:
      storage: 10Gi
```

- e：在pod中使用gluster



```jsx
vi  nginx_pod.yaml
…… 
volumeMounts:
        - name: nfs-vol2
          mountPath: /usr/share/nginx/html
      volumes:
      - name: nfs-vol2
        persistentVolumeClaim:
          claimName: gluster
```

### 7:与jenkins集成实现ci/cd

## 

| ip地址    | 服务                       | 内存 |
| --------- | -------------------------- | ---- |
| 10.0.0.11 | kube-apiserver   8080      | 1G   |
| 10.0.0.14 | jenkins(tomcat + jdk) 8080 | 1G   |
| 10.0.0.15 | gitlab 8080,80             | 2G   |

### 7.1: 安装gitlab并上传代码



```csharp
#a:安装
wget https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el7/gitlab-ce-11.9.11-ce.0.el7.x86_64.rpm
yum localinstall gitlab-ce-11.9.11-ce.0.el7.x86_64.rpm -y
#b:配置
vim /etc/gitlab/gitlab.rb
external_url 'http://10.0.0.15'
prometheus_monitoring['enable'] = false
#c:应用并启动服务
gitlab-ctl reconfigure

#使用浏览器访问http://10.0.0.15,修改root用户密码,创建project
#上传代码到git仓库
cd /srv/
rz -E
unzip xiaoniaofeifei.zip 
rm -fr xiaoniaofeifei.zip 

git config --global user.name "Administrator"
git config --global user.email "admin@example.com"
git init
git remote add origin http://10.0.0.15/root/xiaoniao.git
git add .
git commit -m "Initial commit"
git push -u origin master
mv xiaoniaofeifei.zip /srv/

1.Git global setup
git config --global user.name "Administrator"
git config --global user.email "admin@example.com"

2.Create a new repository
git clone http://10.0.0.15/root/xiaoniao.git
cd xiaoniao
touch README.md
git add README.md
git commit -m "add README"
git push -u origin master

3.Existing folder
cd existing_folder
git init
git remote add origin http://10.0.0.15/root/xiaoniao.git
git add .
git commit -m "Initial commit"
git push -u origin master

4.Existing Git repository
cd existing_repo
git remote rename origin old-origin
git remote add origin http://10.0.0.15/root/xiaoniao.git
git push -u origin --all
git push -u origin --tags
```

### 7.2 安装jenkins,并自动构建docker镜像

1:安装jenkins



```bash
cd /opt/
rz -E
rpm -ivh jdk-8u102-linux-x64.rpm 
mkdir /app
tar xf apache-tomcat-8.0.27.tar.gz -C /app
rm -fr /app/apache-tomcat-8.0.27/webapps/*
cp jenkins.war /app/apache-tomcat-8.0.27/webapps/ROOT.war
tar xf jenkin-data.tar.gz -C /root
/app/apache-tomcat-8.0.27/bin/startup.sh 
netstat -lntup
```

2:访问jenkins



```ruby
访问[http://10.0.0.14:8080/,](http://10.0.0.14:8080/,)默认账号密码admin:123456
```

3:配置jenkins拉取gitlab代码凭据
 a:在jenkins上生成秘钥对



```undefined
ssh-keygen -t rsa
```

b:复制公钥粘贴gitlab上

![img](https:////upload-images.jianshu.io/upload_images/16861561-d14d9415bd15ee7f.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

c:jenkins上创建全局凭据

![img](https:////upload-images.jianshu.io/upload_images/16861561-072a86a95faed2e2.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

4:拉取代码测试

![img](https:////upload-images.jianshu.io/upload_images/16861561-784009e2eb992bab.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

5:编写dockerfile并测试



```csharp
vim dockerfile
FROM 10.0.0.11:5000/nginx:1.13
add .  /usr/share/nginx/html
#添加docker build构建时不add的文件
vim  .dockerignore
dockerfile

docker build -t xiaoniao:v1 .
docker run -d -p 88:80 xiaoniao:v1
```

打开浏览器测试访问xiaoniaofeifei的项目

![img](https:////upload-images.jianshu.io/upload_images/16861561-49de478af4d4eef4.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

6:上传dockerfile和.dockerignore到私有仓库



```csharp
git add docker  .dockerignore
git commit -m "fisrt commit"
git push -u origin master
```

![img](https:////upload-images.jianshu.io/upload_images/16861561-b24b1a42443a57d4.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

7:点击jenkins立即构建,自动构建docker镜像并上传到私有仓库
 修改jenkins 工程配置

![img](https:////upload-images.jianshu.io/upload_images/16861561-77f204b64662348f.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png



```bash
docker  build  -t  10.0.0.11:5000/test:v$BUILD_ID  .
docker  push 10.0.0.11:5000/test:v$BUILD_ID
```

7.3  jenkins自动部署应用到k8s



```bash
kubectl -s 10.0.0.11:8080  get nodes

shell
if [ -f /tmp/xiaoniao.lock ];then
    docker  build  -t  10.0.0.11:5000/xiaoniao:v$BUILD_ID  .
    docker  push 10.0.0.11:5000/xiaoniao:v$BUILD_ID
    kubectl -s 10.0.0.11:8080 set image  -n xiaoniao deploy xiaoniao xiaoniao=10.0.0.11:5000/xiaoniao:v$BUILD_ID
    echo "更新成功"
else
    docker  build  -t  10.0.0.11:5000/xiaoniao:v$BUILD_ID  .
    docker  push 10.0.0.11:5000/xiaoniao:v$BUILD_ID
    kubectl  -s 10.0.0.11:8080  create  namespace  xiaoniao
    kubectl  -s 10.0.0.11:8080  run   xiaoniao  -n xiaoniao  --image=10.0.0.11:5000/xiaoniao:v$BUILD_ID --replicas=3 --record
    kubectl  -s 10.0.0.11:8080   expose -n xiaoniao deployment xiaoniao --port=80 --type=NodePort
    port=`kubectl -s 10.0.0.11:8080  get svc -n xiaoniao|grep -oP '(?<=80:)\d+'`
    echo "你的项目地址访问是http://10.0.0.13:$port"
    touch /tmp/xiaoniao.lock
fi
```

![img](https:////upload-images.jianshu.io/upload_images/16861561-7cbf650a0adccd00.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

jenkins一键回滚



```css
kubectl  -s 10.0.0.11:8080 rollout undo -n xiaoniao  deployment xiaoniao
```

![img](https:////upload-images.jianshu.io/upload_images/16861561-89137cc105be4c7c.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

image.png

![img](https:////upload-images.jianshu.io/upload_images/16861561-d2eaed8a6539edfa.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)





原文链接：https://www.jianshu.com/p/707c8ebb8616

