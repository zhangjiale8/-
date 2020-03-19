# 1.1 Deque源码（基于JDK1.7.0_45）

我们来看看Deque源码，在Queue基础上，又增加了哪些功能？

**Deque接口，是一个实现了双端队列数据结构的队列，即在头尾都可进行删除和新增操作**；

```java
//接口Deuque:
public interface Deque<E> extends Queue<E> {

    //将指定元素添加到双端队列的头部（如果队列满了，则抛出异常）
    void addFirst(E e);

    //将指定元素添加到双端队列的头部（如果队列满了，则返回fasle）
    boolean offerFirst(E e);

    //将指定元素添加到双端队列的尾部（如果队列满了，则抛出异常）
    void addLast(E e);

    //将指定元素添加到双端队列的尾部（如果队列满了，则返回fasle）
    boolean offerLast(E e);

    //获取并删除该双端队列的第一个元素（如果双端队列为空，则抛出异常）
    E removeFirst();

    //获取并删除双端队列的第一个元素（如果双端队列为空，则返回null）
    E pollFirst();

    //获取并删除该双端队列的最后一个元素（如果双端队列为空，则抛出异常）
    E removeLast();

    //获取并删除该双端队列的最后一个元素（如果双端队列为空，则返回null）
    E pollLast();

    //获取但不删除双端队列的第一个元素（如果双端队列为空，则抛出异常）
    E getFirst();

    //获取但不删除双端队列的第一个元素（如果双端队列为空，则返回null）
    E peekFirst();

    //获取但不删除双端队列的最后一个元素（如果双端队列为空，则抛出异常）
    E getLast();

    //获取但不删除双端队列的最后一个元素（如果双端队列为空，则返回null）
    E peekLast();

    //删除该双端队列的第一次出现的元素o
    boolean removeFirstOccurrence(Object o);

    //删除该双端队列的最后一次出现的元素o
    boolean removeLastOccurrence(Object o);

    //与Queue同理：
    boolean add(E e);
    //与Queue同理：
    boolean offer(E e);
    //与Queue同理：
    E remove();
    //与Queue同理：
    E poll();
    //与Queue同理：
    E element();
    //与Queue同理：
    E peek();
    //与Queue同理：
    boolean remove(Object o);

    模拟数据结构--栈-将元素压入栈顶（向栈顶添加元素）
    void push(E e);

    模拟数据结构--栈-将元素移出栈顶（从栈顶删除元素）
    E pop();

    boolean contains(Object o);

    public int size();

    Iterator<E> iterator();

    Iterator<E> descendingIterator();
}
```

Deque(Double ended queue)，双端队列的缩写。一般队列是能在队头获取(删除)元素，在队尾添加元素，即只有一个进入端，一个输出端。而在Deque中，实现了两个进入端、两个输出端--即可在头部输出也可输入，即可在尾部输出也可在尾部输入。

Deque继承了Queue的所有方法，自然可以当做队列来使用，依旧保持着“**先进先出**”的本质，在队头移除元素，在队尾添加元素；

但是，**Deque还可以被当做“栈”来使用，即“后进先出”**，**添加元素、删除元素都在队头进行；主要通过push（）、pop（）两个方法来实现**；

通过上面的框架图，可以清楚的看出，Deque接口主要有2个实现类，分别为ArrayDeque、LinkedList;

不过，还有一个并发实现类LinkedBlockingDeque，待我们下一篇幅在做介绍；

LinkedList不用多说，在之前List讲解中已做过介绍，感兴趣的朋友可以去学习下。

本篇主要讲解ArrayDeque，通过名字可以看出，它底层数据结构由数组实现，既然是数组，想必也会实现自动扩容的机制！

# 1.2 ArrayDeque源码（基于JDK1.7.0_45）

值得一提的是，Java中有一个类叫做Stack，该类实现了栈结构。但是，Java已经不提倡Stack来实现栈结构，而是建议使用ArrayDeque类；

来自Stack类描述：

```kotlin
A more complete and consistent set of LIFO stack operations is 
provided by the {@link Deque} interface and its implementations, which 
should be used in preference to this class.  For example: 
Deque<Integer> stack = new ArrayDeque<Integer>();}</pre>    
@author  Jonathan Payne 
@since   JDK1.0
```

在看源码前，先给大家介绍下ArrayDeque到底如何添加元素、删除元素的？这样更有利于各位的理解！

在ArrayDeque中主要分为几类方法：

## 1.2.1 添加：双端队列（头尾都可以增加元素）

（1）插入到队列头部：addFirst--offerFirst--将新增元素插入到数组的最大角标处，依次递减；

（2）插入到队列尾部：addLast--offerLast--将新增元素插入到数组的0角标处，依次递增；

![img](image\双端队列增加元素01.png)

![img](image\双端队列增加元素02.png)

## 1.2.2 删除：

（1）删除队列头部第一个元素：removeFirst--pollFirst--将元素移除，移除此时head处的元素；

（2）删除队列尾部最后一个元素：removeLast--pollLast--将元素移除，移除此时tail处的元素；

![img](image\双端队列删除元素01.png)

![img](image\双端队列删除元素02.png)

## 1.2.3 获取：

（1）获取队列头部第一个元素：getFirst--peekFirst     

（2）获取队列尾部最后一个元素：getLast--peekLast

以上方法，在理解时候，切不可将队列的头尾理解成数组的头、尾。队列的头尾值得是head、tail指针；

## 1.2.4 ArrayDeque主要源码：（进行了删减）

### 1.2.4.1 ArrayDeque成员变量和构造方法：

```java
public class ArrayDeque<E> extends AbstractCollection<E>
        implements Deque<E>, Cloneable, Serializable {

    //底层数据结构实现---数组[]
    private transient E[] elements;

    //队列头指针：默认为0
    private transient int head;

    //队列尾指针：默认为0
    private transient int tail;

    //最小初始化容量值：
    private static final int MIN_INITIAL_CAPACITY = 8;

    //扩大数组的长度：扩大为原有长度的2倍；
    private void doubleCapacity() {
        //assert断言修饰符--只有当head==tail时候才会进行扩容操作；
        //(前提是assert开启，否则assert修饰符无效)
        assert head == tail;
        int p = head;
        int n = elements.length;
        int r = n - p; // number of elements to the right of p
        int newCapacity = n << 1;
        if (newCapacity < 0)
            throw new IllegalStateException("Sorry, deque too big");
        Object[] a = new Object[newCapacity];
        //连续调用2次的目的，是为了把原数组中所有的元素全部复制到新数组中(看图说话)
        System.arraycopy(elements, p, a, 0, r);
        System.arraycopy(elements, 0, a, r, p);
        elements = (E[])a;
        head = 0;
        tail = n;
    }

    //默认构造函数：队列的长度默认为16
    public ArrayDeque() {
        elements = (E[]) new Object[16];
    }

    //可设置队列大小的构造函数：
    public ArrayDeque(int numElements) {
        allocateElements(numElements);
    }

    //带集合的构造函数：
    public ArrayDeque(Collection<? extends E> c) {
        allocateElements(c.size());
        addAll(c);
    }

}
```

### 1.2.4.2 ArrayDeque添加元素：

```java
//向队列的头部插入元素：初始时从数组的最大角标处插入；
    public void addFirst(E e) {
        //插入元素不能为null:
        if (e == null)
            throw new NullPointerException();
        //计算插入的角标：  head = （head-1 与运算 数组长度-1）
        elements[head = (head - 1) & (elements.length - 1)] = e;
        //如果头尾指针相同，则进行扩容操作：
        if (head == tail)
            doubleCapacity();
    }

    //向队列的头部插入元素：底层调用addFirst(E e)
    public boolean offerFirst(E e) {
        addFirst(e);
        return true;
    }

    //向队列的末端插入元素：初始时从数组角标为0处插入；
    public void addLast(E e) {
        //插入元素不能为null:
        if (e == null)
            throw new NullPointerException();
        //插入数组中，位置就是尾指针的值；
        elements[tail] = e;
        //判断是否需要进行扩容操作:(tail+1 位运算 数组长度-1)是否与head的值相等
        if ( (tail = (tail + 1) & (elements.length - 1)) == head)
            //扩容操作：
            doubleCapacity();
    }

    //向队列的末端插入元素：底层调用addLast(E e)
    public boolean offerLast(E e) {
        addLast(e);
        return true;
    }
```

### 1.2.4.3ArrayDeque删除元素：

```java
    //移除队列中第一个元素：移除数组中head指针所指向的元素；
    public E removeFirst() {
        E x = pollFirst();
        //如果队列中没有元素，则抛出异常
        if (x == null)
            throw new NoSuchElementException();
        return x;
    }

    //移除队列头中的元素，实际就是移除数组中head指针所指向的元素；
    public E pollFirst() {
        //获取头指针：
        int h = head;
        //获取头指针所处的数组角标元素：
        E result = elements[h]; // Element is null if deque empty
        //如果头指针为null，说明队列中没有元素存在，直接返回；
        if (result == null)
            return null;
        //将头指针所指向数组角标置为null：
        elements[h] = null;     // Must null out slot
        //修改头指针大小 = 头指针+1 & 数组长度-1
        //实际上是将现有头指针+1。
        head = (h + 1) & (elements.length - 1);
        //返回被删除的对象：
        return result;
    }

    //移除队列中最后一个元素：移除数组中tail指针所指向的元素；
    public E removeLast() {
        E x = pollLast();
        //如果队列中没有元素，则抛出异常
        if (x == null)
            throw new NoSuchElementException();
        return x;
    }

    //移除队列尾中的元素，实际就是移除数组中tail指针所指向的元素；
    public E pollLast() {
        //获取要移除元素的数组角标：如果tail为0，则计算出的t值为数组的最大角标（首尾相连了）
        int t = (tail - 1) & (elements.length - 1);
        //获取要移除的数组元素：
        E result = elements[t];
        //如果为null，则直接返回；
        if (result == null)
            return null;
        //将对应数组角标的元素置为null：
        elements[t] = null;
        //修改tail指针的值：
        tail = t;
        return result;
    }
```

### 1.2.4.4 ArrayDeque获取元素：

```csharp
    //得到队列中的第一个元素，也就是头指针所指向的元素；
    public E getFirst() {
        E x = elements[head];
        //为空的话，抛出异常；
        if (x == null)
            throw new NoSuchElementException();
        return x;
    }

    //得到队列中的第一个元素，队列空的话返回null
    public E peekFirst() {
        return elements[head]; // elements[head] is null if deque empty
    }

    //得到队列中的最后一个元素，也就是尾指针所指向的元素；
    public E getLast() {
        E x = elements[(tail - 1) & (elements.length - 1)];
        if (x == null)
            throw new NoSuchElementException();
        return x;
    }

    //得到队列中的最后一个元素，队列空的话返回null
    public E peekLast() {
        return elements[(tail - 1) & (elements.length - 1)];
    }
```

### 1.2.4.5 ArrayDeque实现队列的方法：

```java
    //队列方法：
    //向队列中添加元素：添加到队列头部
    public boolean add(E e) {
        addLast(e);
        return true;
    }

    //向队列中添加元素：添加到队列末尾
    public boolean offer(E e) {
        return offerLast(e);
    }

    //移除队列中元素，移除队列头部元素，为null抛出异常；
    public E remove() {
        return removeFirst();
    }

    //移除队列中元素，移除队列头部元素，可以为null；
    public E poll() {
        return pollFirst();
    }

    //获取队列头部的元素：如果为null抛出异常；
    public E element() {
        return getFirst();
    }

    //获取队列头部的元素：如果为null，就返回；
    public E peek() {
        return peekFirst();
    }
```

### 1.2.4.6 ArrayDeque实现栈的方法：

```cpp
    //栈方法：
    //向栈顶压入对象：向数组最大角标处插入对象；
    public void push(E e) {
        addFirst(e);
    }

    //将栈顶对象出栈，移除head指针所属的元素；
    public E pop() {
        return removeFirst();
    }
```

此外，ArrayDeque利用了push/pop方法，实现了栈结构，栈是一种“后进先出”的数据模型。

在ArrayDeque中，底层主要利用addFirst/removeFirst实现元素的出栈和入栈操作；

# 1.3 LinkedList源码（基于JDK1.7.0_45）

LinkedList即有List集合方法，又有Deque集合方法。

具体解析，请参考笔者之前的文章。