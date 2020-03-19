# ConcurrentLinkedQueue实现原理

上文，笔者介绍了非阻塞队列的基础知识，对于其代表类ConcurrentLinkedQueue做了个简单阐述。

本篇，我们就继续对ConcurrentLinkedQueue进行学习，来看看ConcurrentLinkedQueue的底层实现！

## 1.1 链表结点

在ConcurrentLinkedQueue中，元素保存在结点中，对外以元素形式存在，对内则以结点形式存在。

每一个结点中，都有指向下一个结点的指针，依次向后排列，形成链表结构。

在ConcurrentLinkedQueue中，有一个内部类--Node，此类代表队列的结点。

在Node中，item表示元素，next为指向下一个元素的指针，并且都被volatitle所修饰。

之前，我们说了ConcurrentLinkedQueue是使用CAS来实现非阻塞入队出队。在Node结点中，我们也使用了CAS来实现结点的操作。

使用CAS来替换本结点中的元素，使用CAS来替换本结点中指向下一个元素的指针。

如果你对CAS的概念不太理解，建议可先去[CAS](https://www.jianshu.com/p/1309dd03f81a)进行学习；

在本篇幅中，我们不对CAS进行过多的z介绍！

```java
//单向链表中：结点对象Node：
private static class Node<E> {
    //链表中存储的元素：
    volatile E item;

    //本结点指向下一结点的引用：
    volatile Node<E> next;

    //结点构造：使用UNSAFE机制（CAS）实现元素存储
    Node(E item) {UNSAFE.putObject(this, itemOffset, item);}

    //替换本结点中的元素值：cmp是期望值，val是目标值。当本结点中元素的值等于cmp的时，则将其替换为val
    boolean casItem(E cmp, E val) {return UNSAFE.compareAndSwapObject(this, itemOffset, cmp, val);}

    //将本结点中指向下一个结点的引用指向自己
    void lazySetNext(Node<E> val) {UNSAFE.putOrderedObject(this, nextOffset, val);}

    //替换本结点中指向下一个结点的引用：cmp是期望值，val是目标值。当本结点中的指向下一个结点的引用等于cmp时，则将其替换为指向val
    boolean casNext(Node<E> cmp, Node<E> val) {return UNSAFE.compareAndSwapObject(this, nextOffset, cmp, val);}

    //JDK提供的Unsafe对象，底层CAS原理实现
    private static final sun.misc.Unsafe UNSAFE;
    
    private static final long itemOffset;
    
    private static final long nextOffset;

    static {
        try {
            UNSAFE = sun.misc.Unsafe.getUnsafe();
            Class k = Node.class;

            //结点中元素的起始地址偏移量：
            itemOffset = UNSAFE.objectFieldOffset
                (k.getDeclaredField("item"));
            
            //结点中指向下一个元素引用的起始地址偏移量：
            nextOffset = UNSAFE.objectFieldOffset
                (k.getDeclaredField("next"));
        } catch (Exception e) {
            throw new Error(e);
        }
    }
}
```

总体来说，在Node类中，元素的替换，指针的改变都是通过CAS来实现的。在方法中，如果执行成功则返回true,执行失败则返回false；

可能有的朋友对itemOffset、nextOffset不太理解，这块我给大家稍微做个解释！

其实，你可以理解为当一个对象创建后，JVM在内存中为这个对象分配了一片区域，该区域用来存储该类的一些信息，这些信息中就包括item、next等属性。而为了能更快的从内存中，对这些属性获取修改，我们就需要使用Unsafe类，该类可以帮助获取到这些属性所在内存中具体的位置，有了位置的信息，我们的程序就能更快的进行操作！

## 1.2 成员变量

在ConcurrentLinkedQueue中，head、tail属性就是队列中常见的头指针、尾指针。值得注意的是，head、tail属性都被volatitle所修饰。

**volatitlte是一个轻量级的同步机制，当有线程对其所修饰的属性进行更新时，被更新的值会立刻同步到内存中去，并且使其他cpu所缓存的值置为无效。当其他线程对该属性操作时，必须从主存中获取**。

此外，与Node类类似，在ConcurrentLinkedQueue中也包含了Unsafe类，以及headOffset--头结点偏移量，tailOffset--尾结点偏移量。

```java
//队列中头结点：
private transient volatile Node<E> head;

//队列中尾结点：
private transient volatile Node<E> tail;

private static final sun.misc.Unsafe UNSAFE;
private static final long headOffset;
private static final long tailOffset;

static {
    try {
        UNSAFE = sun.misc.Unsafe.getUnsafe();
        Class k =ConcurrentLinkedQueue.class;
        headOffset = UNSAFE.objectFieldOffset
                (k.getDeclaredField("head"));
        tailOffset = UNSAFE.objectFieldOffset
                (k.getDeclaredField("tail"));
    } catch (Exception e) {
        throw new Error(e);
    }
}
```

## 1.3 构造函数

在默认构造中，队列的头尾结点指针都指向同一个结点，并且结点元素为null；

```java
//默认构造，指定头尾结点元素为null：
public ConcurrentLinkedQueue() {
    head = tail = new Node<E>(null);
}
```

此时，队列结构，如图所示：

[图片上传失败...(image-24612f-1514418648920)]

## 1.4 入队

在ConcurrentLinkedQueue中，入队操作包含两种方法，一个是add(E e)，一个是offer(E e)。

add(E e)底层调用offer(E e)，所以我们主要说说offer(E e).

```java
//向队列尾部添加元素(底层调用offer):
public boolean add(E e) {
    return offer(e);
}

//入队：向队列尾部添加元素:
public boolean offer(E e) {
    //不能添加为空元素：抛异常
    checkNotNull(e);

    //创建新结点：
    final Node<E> newNode = new Node<E>(e);
    
    //p的类型为Node<E>(这块需要注意，不需要显式声明)
    for (Node<E> t = tail, p = t;;) {
        //获取链表中尾部结点的下一个结点：
        Node<E> q = p.next;
        
        //并判断下一个结点是否为null(正常情况下均为null)，为null则说明p是链表中的最后一个节点
        if (q == null) {------------------------⑴
            //将p节点中指向下一个结点的引用指向newNode节点（向链表中插入元素）
            if (p.casNext(null, newNode)) {
                if (p != t) 
                    casTail(t, newNode);  
                return true;
            }//CAS插入失败，则进入下次循环
            
        } else if (p == q){------------------------⑵
            p = (t != (t = tail)) ? t : head;
        
        } else {------------------------⑶
            p = (p != t && t != (t = tail)) ? t : q;
        }
    }
}
```

在offer(E e)的判断中，由于使用了三目运算符，导致可读性较差，对于有的朋友来说可能难以理解。

我们对其进行了优化，由三目运算符修改为if/else的形式：

p = (t != (t = tail)) ? t : head 替换为：



```bash
Node<E> tmp=t;
t = tail;
if (tmp==t) {
    p=head;
} else {
    p=t;
}
```

p = (p != t && t != (t = tail)) ? t : q 替换为：



```bash
if (p==t) {
    p = q;
} else {
    Node<E> tmp=t;
    t = tail;
    if (tmp==t) {
        p=q;
    } else {
        p=t;
    }
}
```

结合上面的源码，我们来具体说说入队的流程:

（1）当插入的元素为空时候，会抛出异常，禁止向队列中插入尾空元素；

创建插入元素的新结点newNode，从tail指针处遍历链表结构。

例如：

  向队列中插入第一个元素时，元素="1111"，tail=Node(null)、t=tail、p=tail、p.next=null、q=null。此处需要注意，由于是插入队列的第一个元素，所以需要回过去看下队列的默认构造是如何实现。

  q=null，进入判断条件，p.casNext(null,newNode)，调用p结点的cas方法，判断p结点的next属性是否为null，如果为null，则将next属性指向newNode结点。调用成功，返回true；调用失败，返回false。由于底层使用CAS实现，所以casNext()方法将是一个原子性操作。

  如果调用失败，则进行下一次循坏，直至插入成功为止。而调用成功，则进入if内部，判断p和t是否相同，此时是何含义呢？

  在ConcurrentLinkedQueue中，当插入一个结点时，并不会每插入一次都改变一次tail结点的指向，当我们发现p/t不同时，也就是说最后一个结点和tail结点不为同一个时，我们就需要调用casTail()方法，来修改tail结点的指向。

  例如，当我们向队列中，插入第一个元素时候，直至插入结束，我们也并没有修改tail结点的指向，当第二次插入时候会进行修改。

  下面，我们来看下第二个元素的插入情况，元素="2222"。

  同样，判断为null，创建新结点。进入第一次循环：tail=Node(null)、t=tail、p=tail、p.next=Node(1111)、q=Node(1111)。

  进入第一个判断q==null不成立，第二个判断p==q不成立，进入else：看上面的简化代码，发现此时p==t，所以将p=q，结束循环，进入下一次。

  进入第二次循环，t=tail，p=q=Node(1111)，p.next=null，q=null。进入第一个循环判断q=null成立，此时与第一次插入情况相同。插入完成后，判断p!=t，此时p=Node(1111)/t=tail，进入判断，调用casTail(t, newNode)，将tail指针指向newNode结点，至此插入成功，返回true。

  上面我们说到了⑴⑶两种情况，接下来我们说说⑶。什么情况下，回进入⑵的判断中呢？

  当我们再添加完首个元素后，立即进行出队操作，此时再去添加一个元素，那么就会在循环中直接进入⑵的判断中。此时需要结合出队代码一块学习。

  tail=Node(null)，t=tail，p=tail，p.next=p=Node(null)，q=p=Node(null)，也就是此时的tail节点元素为null，而指向下一个元素的指针也指向了自己，这是由于元素出队导致的。

  进入第二个循环p==q，回看上面的优化代码，得到p=head；开始第二次循环，head在出队时被设置成了指向第一次插入的元素(此时该元素的值为null,但结点依旧存在)。p.next=null，q=null，进入第一个判断p==null，并进入p!=t，重新设置tail指针。

说了很多，想必不少人已经看蒙了，下面我们用图片来进行下简单的描述！！！

[图片上传失败...(image-caac51-1514418648920)]

## 1.5 出队

```kotlin
//出队：移除队列中头结点中的元素
public E poll() {
    restartFromHead:
    for (;;) {
        //p的类型为Node<E>(这块需要注意，不需要显式声明)
        for (Node<E> h = head, p = h, q;;) {
            //头部结点的元素：
            E item = p.item;
            //如果p节点的元素不为空，使用CAS设置p节点引用的元素为null
            if (item != null && p.casItem(item, null)) {
                if (p != h) 
                    updateHead(h, ((q = p.next) != null) ? q : p);
                return item;
            } else if ((q = p.next) == null) {
                //如果p的下一个结点为null，则说明队列中没有元素，更新头结点
                updateHead(h, p);
                return null;
            } else if (p == q) {
                continue restartFromHead;
            } else {
                p = q;
            }
        }
    }
}
```

与入队流程相比，出队流程的操作也同样复杂，需要我们静下心来细细学习！！

我们假设，此时队列中已经存在了4个元素。如图：

[图片上传失败...(image-3ae987-1514418648920)]

**出队第一个元素**：

进入for循环：head=Node(null)，h=head，p=head，q=null；item=p.item=null；进行if判断，第一个判断不满足，第二个判断中将q进行了修改：q=p.next=Node(1111)，第三个判断p==q不满足，直接进入最后的else，将p=q=Node(1111);

开始第二次循环，item=p.item=1111，进入第一个判断p.casItem(item,null)，将p节点中的元素值1111置为null；进行判断p!=h，成立调用update(h,q)方法，将head指针指向Node(2222)处，并将原来head指向结点Node(null)的next属性指向自己；

[图片上传失败...(image-31a4da-1514418648920)]

**出队第二个元素：**

进入for循环：head=Node(2222)，h=head，p=head，q=null；item=p.item=2222；进行if判断，满足条件，进行p.casItem(item,null)，p=Node(null)--head=Node(null)；判断p!=h，此时结果为等于，则不修改head指针；

[图片上传失败...(image-a8b43c-1514418648920)]

**出队第三个元素：**

进入for循环：head=Node(null)，h=head，p=head，q=null；item=p.item=null；进行if判断，第一个判断不满足，第二个判断中将q进行了修改：q=p.next=Node(3333)，第三个判断p==q不满足，直接进入最后的else，将p=q=Node(3333);

开始第二次循环，item=p.item=3333，进入第一个判断p.casItem(item,null)，将p节点中的元素值3333置为null；进行判断p!=h，成立调用update(h,q)方法，将head指针指向Node(4444)处，并将原来head指向结点Node(null)的next属性指向自己；

[图片上传失败...(image-a82e19-1514418648920)]

**出队第四个元素：**

重复出队第二个元素的步骤，将第四个结点元素置为null；

[图片上传失败...(image-5157b1-1514418648920)]

通过上面5张图片，希望你能对ConcurrentLinkedQueue的出队流程有一个清晰的思路。

## 1.6 获取

```kotlin
//获取头部元素，不移除队列中头结点中的元素
public E peek() {
    restartFromHead:
    for (;;) {
        for (Node<E> h = head, p = h, q;;) {
            E item = p.item;
            if (item != null || (q = p.next) == null) {
                updateHead(h, p);
                return item;
            }
            else if (p == q)
                continue restartFromHead;
            else
                p = q;
        }
    }
}
```

peek()方法与poll()方法类似，返回的都是头结点中的元素。

但有一点不同的是，peek()方法并不会移除头结点中的元素，而poll()在改变head指向的同时还移除了头结点中的元素，将其置为null。


原文链接：https://www.jianshu.com/p/6b6521656b40
