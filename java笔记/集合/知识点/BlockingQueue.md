# BlockingQueue

BlockingQueue是一个接口，是所有阻塞队列的父类，定义了阻塞队列的主要操作方法。

```java
public interface BlockingQueue<E> extends Queue<E> {
    
    boolean add(E e);

    boolean offer(E e);

    void put(E e) throws InterruptedException;

    boolean offer(E e, long timeout, TimeUnit unit) throws InterruptedException;

    E take() throws InterruptedException;

    E poll(long timeout, TimeUnit unit) throws InterruptedException;

    int remainingCapacity();

    boolean remove(Object o);

    public boolean contains(Object o);

    int drainTo(Collection<? super E> c);

    int drainTo(Collection<? super E> c, int maxElements);
}
```

## 1.1 添加方法：

add：插入元素，如果队列满了，抛出异常(底层调用offer方法)；

put：插入元素，如果队列满了，就等待；

offer：插入元素，如果队列满了，就直接返回false；

## 1.2 获取方法：

element(继承父类)：如果队列为空，直接抛出异常(底层调用peek方法)；

peek(继承父类)：如果队列为空，则返回null；

## 1.3 移除方法：

remove：移除对应元素，如果队列为空，则返回false;

take：移除元素，如果队列为空，则一直等待；

poll：移除元素，如果队列为空，则返回null；

## 1.4 BloeckingQueue成员：

![img](image\BloeckingQueue成员01.png)




原文链接：https://www.jianshu.com/p/57904839507f
