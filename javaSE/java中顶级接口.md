# 1. Iterable

`Iterable`接口 (`java.lang.Iterable`) 是Java集合的顶级接口之一。`Collection`接口继承`Iterable`，所以`Collection`的所有子类也实现了`Iterable`接口。

## 1.1 Iterable 接口只有一个方法

```java
public interface Iterable<T> {
  public Iterator<T> iterator();
}
```



## 1.2 一个实现`Iterable`接口的类可以使用新的for循环

```java 
List list = new ArrayList();
for(Object o : list){
//do something o;
}
```




