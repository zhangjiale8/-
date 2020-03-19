### ArrayList

完整源码：

```java
public class ArrayList<E> extends AbstractList<E>
        implements List<E>, RandomAccess, Cloneable, java.io.Serializable {

    //实现Serializable接口，生成的序列版本号：
    private static final long serialVersionUID = 8683452581122892189L;

    //ArrayList初始容量大小：在无参构造中不使用了
    private static final int DEFAULT_CAPACITY = 10;

    //空数组对象：初始化中默认赋值给elementData
    private static final Object[] EMPTY_ELEMENTDATA = {};

    //ArrayList中实际存储元素的数组：
    private transient Object[] elementData;

    //集合实际存储元素长度：
    private int size;

    //ArrayList有参构造：容量大小
    public ArrayList(int initialCapacity) {
        //即父类构造：protected AbstractList() {}空方法
        super();
        //如果传递的初始容量小于0 ，抛出异常
        if (initialCapacity < 0)
            throw new IllegalArgumentException("Illegal Capacity: "+ initialCapacity);
        //初始化数据：创建Object数组
        this.elementData = new Object[initialCapacity];
    }

    //ArrayList无参构造：
    public ArrayList() {
        //即父类构造：protected AbstractList() {}空方法
        super();
        //初始化数组：空数组，容量为0
        this.elementData = EMPTY_ELEMENTDATA;
    }

    //ArrayList有参构造：Java集合
    public ArrayList(Collection<? extends E> c) {
        //将集合转换为数组：
        elementData = c.toArray();
        //设置数组的长度：
        size = elementData.length;
        if (elementData.getClass() != Object[].class)
            elementData = Arrays.copyOf(elementData, size, Object[].class);
    }

    //将ArrayList的数组大小，变更为实际元素大小：
    public void trimToSize() {
        //操作数+1
        modCount++;
        //如果集合内元素的个数，小于数组的长度，那么将数组中空余元素删除
        if (size < elementData.length) {
            elementData = Arrays.copyOf(elementData, size);
        }
    }

    public void ensureCapacity(int minCapacity) {
        int minExpand = (elementData != EMPTY_ELEMENTDATA) ? 0 : DEFAULT_CAPACITY;
        if (minCapacity > minExpand) {
            ensureExplicitCapacity(minCapacity);
        }
    }

    //ArrayList集合内元素的个数：
    public int size() {
        return size;
    }

    //判断ArrayList集合元素是否为空：
    public boolean isEmpty() {
        return size == 0;
    }

    //判断ArrayList集合包含某个元素：
    public boolean contains(Object o) {
        //判断对象o在ArrayList中存在的角标位置
        return indexOf(o) >= 0;
    }

    //判断对象o在ArrayList中存在的角标位置：
    public int indexOf(Object o) {
        //如果o==null：
        if (o == null) {
            //遍历集合，判断哪个元素等于null，则返回对应角标
            for (int i = 0; i < size; i++)
                if (elementData[i]==null)
                    return i;
        } else {
            //同理：
            for (int i = 0; i < size; i++)
                if (o.equals(elementData[i]))
                    return i;
        }
        //如果不存在，则返回-1
        return -1;
    }

    //判断对象o在ArrayList中出现的最后一个位置：
    public int lastIndexOf(Object o) {
        //如果o==null：
        if (o == null) {
            //从集合最后一个元素开始遍历：
            for (int i = size-1; i >= 0; i--)
                if (elementData[i]==null)
                    return i;
        } else {
            //同理：
            for (int i = size-1; i >= 0; i--)
                if (o.equals(elementData[i]))
                    return i;
        }
        //如果不存在，则返回-1
        return -1;
    }

    //返回此ArrayList实例的 克隆对象：
    public Object clone() {
        try {
            java.util.ArrayList<E> v = (java.util.ArrayList<E>) super.clone();
            v.elementData = Arrays.copyOf(elementData, size);
            v.modCount = 0;
            return v;
        } catch (CloneNotSupportedException e) {
            throw new InternalError();
        }
    }

    //将ArrayList里面的元素赋值到一个数组中去 生成Object数组：
    public Object[] toArray() {
        return Arrays.copyOf(elementData, size);
    }

    //将ArrayList里面的元素赋值到一个数组中去，专成对应类型的数组：
    public <T> T[] toArray(T[] a) {
        if (a.length < size)
            return (T[]) Arrays.copyOf(elementData, size, a.getClass());
        System.arraycopy(elementData, 0, a, 0, size);
        if (a.length > size)
            a[size] = null;
        return a;
    }

    //获取数组index位置的元素：
    E elementData(int index) {
        return (E) elementData[index];
    }

    //获取index位置的元素
    public E get(int index) {
        //检查index是否合法：
        rangeCheck(index);
        //获取元素：
        return elementData(index);
    }

    //设置index位置的元素值了element，返回该位置的之前的值
    public E set(int index, E element) {
        //检查index是否合法：
        rangeCheck(index);
        //获取该index原来的元素：
        E oldValue = elementData(index);
        //替换成新的元素：
        elementData[index] = element;
        //返回旧的元素：
        return oldValue;
    }

    //添加元素e
    public boolean add(E e) {
        ensureCapacityInternal(size + 1);
        elementData[size++] = e;
        return true;
    }

    //在ArrayList的index位置，添加元素element
    public void add(int index, E element) {
        //判断index角标的合法性：
        rangeCheckForAdd(index);
        //判断是否需要扩容：传入当前元素大小+1
        ensureCapacityInternal(size + 1);
        System.arraycopy(elementData, index, elementData, index + 1, size - index);
        elementData[index] = element;
        size++;
    }

    //得到最小扩容量
    private void ensureCapacityInternal(int minCapacity) {
        //如果此时ArrayList是空数组,则将最小扩容大小设置为10：
        if (elementData == EMPTY_ELEMENTDATA) {
            minCapacity = Math.max(DEFAULT_CAPACITY, minCapacity);
        }
        //判断是否需要扩容：
        ensureExplicitCapacity(minCapacity);
    }

    //判断是否需要扩容
    private void ensureExplicitCapacity(int minCapacity) {
        //操作数+1
        modCount++;
        //判断最小扩容容量-数组大小是否大于0：
        if (minCapacity - elementData.length > 0)
            //扩容：
            grow(minCapacity);
    }

    //ArrayList最大容量：
    private static final int MAX_ARRAY_SIZE = Integer.MAX_VALUE - 8;

    //帮助ArrayList动态扩容的核心方法:
    private void grow(int minCapacity) {
        //获取现有数组大小：
        int oldCapacity = elementData.length;
        //位运算，得带新的数组容量大小，为原有的1.5倍：
        int newCapacity = oldCapacity + (oldCapacity >> 1);
        //如果新扩容的大小依旧小于传入的容量值，那么将传入的值设为新容器大小：
        if (newCapacity - minCapacity < 0)
            newCapacity = minCapacity;

        //如果新容器大小，大于ArrayList最大长度：
        if (newCapacity - MAX_ARRAY_SIZE > 0)
            //计算出最大容量值：
            newCapacity = hugeCapacity(minCapacity);
        //数组复制：
        elementData = Arrays.copyOf(elementData, newCapacity);
    }
    //计算ArrayList最大容量：
    private static int hugeCapacity(int minCapacity) {
        if (minCapacity < 0)
            throw new OutOfMemoryError();
        //如果新的容量大于MAX_ARRAY_SIZE。将会调用hugeCapacity将int的最大值赋给newCapacity:
        return (minCapacity > MAX_ARRAY_SIZE) ?
                Integer.MAX_VALUE :
                MAX_ARRAY_SIZE;
    }

    //在ArrayList的移除index位置的元素
    public E remove(int index) {
        //检查角标是否合法：不合法抛异常
        rangeCheck(index);
        //操作数+1：
        modCount++;
        //获取当前角标的value:
        E oldValue = elementData(index);
        //获取需要删除元素 到最后一个元素的长度，也就是删除元素后，后续元素移动的个数；
        int numMoved = size - index - 1;
        //如果移动元素个数大于0 ，也就是说删除的不是最后一个元素：
        if (numMoved > 0)
            // 将elementData数组index+1位置开始拷贝到elementData从index开始的空间
            System.arraycopy(elementData, index+1, elementData, index, numMoved);
        //size减1，并将最后一个元素置为null
        elementData[--size] = null;
        //返回被删除的元素：
        return oldValue;
    }

    //在ArrayList的移除对象为O的元素，不返回被删除的元素：
    public boolean remove(Object o) {
        //如果o==null，则遍历集合，判断哪个元素为null：
        if (o == null) {
            for (int index = 0; index < size; index++)
                if (elementData[index] == null) {
                    //快速删除，和前面的remove（index）一样的逻辑
                    fastRemove(index);
                    return true;
                }
        } else {
            //同理：
            for (int index = 0; index < size; index++)
                if (o.equals(elementData[index])) {
                    fastRemove(index);
                    return true;
                }
        }
        return false;
    }

    //快速删除：
    private void fastRemove(int index) {
        //操作数+1
        modCount++;
        //获取需要删除元素 到最后一个元素的长度，也就是删除元素后，后续元素移动的个数；
        int numMoved = size - index - 1;
        //如果移动元素个数大于0 ，也就是说删除的不是最后一个元素：
        if (numMoved > 0)
            // 将elementData数组index+1位置开始拷贝到elementData从index开始的空间
            System.arraycopy(elementData, index+1, elementData, index, numMoved);
        //size减1，并将最后一个元素置为null
        elementData[--size] = null;
    }

    //设置全部元素为null值，并设置size为0。
    public void clear() {
        modCount++;
        for (int i = 0; i < size; i++)
            elementData[i] = null;
        size = 0;
    }

    //序列化写入：
    private void writeObject(java.io.ObjectOutputStream s) throws java.io.IOException{
        int expectedModCount = modCount;
        s.defaultWriteObject();
        s.writeInt(size);
        for (int i=0; i<size; i++) {
            s.writeObject(elementData[i]);
        }
        if (modCount != expectedModCount) {
            throw new ConcurrentModificationException();
        }
    }

    // 序列化读取：
    private void readObject(java.io.ObjectInputStream s) throws java.io.IOException, ClassNotFoundException {
        elementData = EMPTY_ELEMENTDATA;
        s.defaultReadObject();
        s.readInt();
        if (size > 0) {
            ensureCapacityInternal(size);
            Object[] a = elementData;
            for (int i=0; i<size; i++) {
                a[i] = s.readObject();
            }
        }
    }

    //检查角标是否合法：不合法抛异常
    private void rangeCheck(int index) {
        if (index >= size)
            throw new IndexOutOfBoundsException(outOfBoundsMsg(index));
    }

    //返回一个Iterator对象，Itr为ArrayList的一个内部类，其实现了Iterator<E>接口
    public Iterator<E> iterator() {
        return new java.util.ArrayList.Itr();
    }

    //其中的Itr是实现了Iterator接口，同时重写了里面的hasNext()，next()，remove()等方法；
    private class Itr implements Iterator<E> {
        int cursor; //类似游标，指向迭代器下一个值的位置
        int lastRet = -1; //迭代器最后一次取出的元素的位置。
        int expectedModCount = modCount;//Itr初始化时候ArrayList的modCount的值。
        //modCount用于记录ArrayList内发生结构性改变的次数，
        // 而Itr每次进行next或remove的时候都会去检查expectedModCount值是否还和现在的modCount值，
        // 从而保证了迭代器和ArrayList内数据的一致性。

        //利用游标，与size之前的比较，判断迭代器是否还有下一个元素
        public boolean hasNext() {
            return cursor != size;
        }

        //迭代器获取下一个元素：
        public E next() {
            //检查modCount是否改变：
            checkForComodification();

            int i = cursor;

            //游标不会大于等于集合的长度：
            if (i >= size)
                throw new NoSuchElementException();

            Object[] elementData = java.util.ArrayList.this.elementData;
            //游标不会大于集合中数组的长度：
            if (i >= elementData.length)
                throw new ConcurrentModificationException();
            //游标+1
            cursor = i + 1;
            //取出元素：
            return (E) elementData[lastRet = i];
        }

        public void remove() {
            if (lastRet < 0)
                throw new IllegalStateException();
            //检查modCount是否改变：防止并发操作集合
            checkForComodification();
            try {
                //删除这个元素：
                java.util.ArrayList.this.remove(lastRet);
                //删除后，重置游标，和当前指向元素的角标 lastRet
                cursor = lastRet;
                lastRet = -1;
                //重置expectedModCount：
                expectedModCount = modCount;
            } catch (IndexOutOfBoundsException ex) {
                throw new ConcurrentModificationException();
            }
        }

        //并发检查：在Itr初始化时，将modCount赋值给了expectedModCount
        //如果后续modCount还有变化，则抛出异常，所以在迭代器迭代过程中，不能调List增删操作；
        final void checkForComodification() {
            if (modCount != expectedModCount)
                throw new ConcurrentModificationException();
        }
    }
}
```

### LinkedList

完整源码：



```java
public class LinkedList<E> extends AbstractSequentialList<E>
        implements List<E>, Deque<E>, Cloneable, java.io.Serializable {

    //LinkedList的元素个数：
    transient int size = 0;

    //LinkedList的头结点：Node内部类
    transient java.util.LinkedList.Node<E> first;

    //LinkedList尾结点：Node内部类
    transient java.util.LinkedList.Node<E> last;

    //空实现：
    public LinkedList() {
    }

    //调用添加方法：
    public LinkedList(Collection<? extends E> c) {
        this();
        addAll(c);
    }

    //LinkedList添加首结点 first：
    public void addFirst(E e) {
        linkFirst(e);
    }
    //first节点插入新元素：addFirst()调用
    private void linkFirst(E e) {
        //头结点：
        final java.util.LinkedList.Node<E> f = first;
        //创建一个新节点，并指向头结点f：
        final java.util.LinkedList.Node<E> newNode = new java.util.LinkedList.Node<>(null, e, f);
        //将新节点赋值给头几点：
        first = newNode;
        //如果头节点为null，则是第一个元素插入，将新节点也设置为尾结点；
        if (f == null)
            last = newNode;
        else
            //将之前的头结点的前指针指向新的结点：
            f.prev = newNode;
        //长度+1
        size++;
        //操作数+1
        modCount++;
    }

    //添加元素：添加到最后一个结点；
    public boolean add(E e) {
        linkLast(e);
        return true;
    }

    //添加最后一个结点 last：
    public void addLast(E e) {
        linkLast(e);
    }

    //last节点插入新元素：addLast()调用
    void linkLast(E e) {
        //将尾结点赋值个体L:
        final java.util.LinkedList.Node<E> l = last;
        //创建新的结点，将新节点的前指针指向l:
        final java.util.LinkedList.Node<E> newNode = new java.util.LinkedList.Node<>(l, e, null);
        //新节点置为尾结点：
        last = newNode;
        //如果尾结点l为null：则是空集合新插入
        if (l == null)
            //头结点也置为 新节点：
            first = newNode;
        else
            //l节点的后指针指向新节点：
            l.next = newNode;
        //长度+1
        size++;
        //操作数+1
        modCount++;
    }

    //向对应角标添加元素：
    public void add(int index, E element) {
        //检查传入的角标 是否正确：
        checkPositionIndex(index);
        //如果插入角标==集合长度，则插入到集合的最后面：
        if (index == size)
            linkLast(element);
        else
            //插入到对应角标的位置：获取此角标下的元素先
            linkBefore(element, node(index));
    }
    //在succ前插入 新元素e：
    void linkBefore(E e, java.util.LinkedList.Node<E> succ) {
        //获取被插入元素succ的前指针元素：
        final java.util.LinkedList.Node<E> pred = succ.prev;
        //创建新增元素节点，前指针 和 后指针分别指向对应元素：
        final java.util.LinkedList.Node<E> newNode = new java.util.LinkedList.Node<>(pred, e, succ);
        succ.prev = newNode;
        //succ的前指针元素可能为null，为null的话说明succ是头结点，则把新建立的结点置为头结点：
        if (pred == null)
            first = newNode;
        else
            //succ前指针不为null，则将前指针的结点的后指针指向新节点：
            pred.next = newNode;
        //长度+1
        size++;
        //操作数+1
        modCount++;
    }
    //移除首个结点：如果集合还没有元素则报错
    public E removeFirst() {
        final java.util.LinkedList.Node<E> f = first;
        //首节点为null，则抛出异常；
        if (f == null)
            throw new NoSuchElementException();
        return unlinkFirst(f);
    }

    //删除LinkedList的头结点：removeFirst()方法调用
    private E unlinkFirst(java.util.LinkedList.Node<E> f) {
        //f为头结点：获取头结点元素E
        final E element = f.item;
        //获取头结点的尾指针结点：
        final java.util.LinkedList.Node<E> next = f.next;
        //将头结点元素置为null：
        f.item = null;
        //头结点尾指针置为null：
        f.next = null;
        //将头结点的尾指针指向的结点next置为first
        first = next;
        //尾指针指向结点next为null的话，就将尾结点也置为null（LinkedList中只有一个元素时出现）
        if (next == null)
            last = null;
        else
            //将尾指针指向结点next的 前指针置为null；
            next.prev = null;
        // 长度减1
        size--;
        //操作数+1
        modCount++;
        //返回被删除的元素：
        return element;
    }

    //移除最后一个结点：如果集合还没有元素则报错
    public E removeLast() {
        //获取最后一个结点：
        final java.util.LinkedList.Node<E> l = last;
        if (l == null)
            throw new NoSuchElementException();
        //删除尾结点：
        return unlinkLast(l);
    }
    //删除LinkedList的尾结点：removeLast()方法调用
    private E unlinkLast(java.util.LinkedList.Node<E> l) {
        final E element = l.item;
        final java.util.LinkedList.Node<E> prev = l.prev;
        l.item = null;
        l.prev = null; // help GC
        last = prev;
        if (prev == null)
            first = null;
        else
            prev.next = null;
        size--;
        modCount++;
        return element;
    }

    //删除LinkedList中的元素，可以删除为null的元素，逐个遍历LinkedList的元素；
    //重复元素只删除第一个：
    public boolean remove(Object o) {
        //如果删除元素为null：
        if (o == null) {
            for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next) {
                if (x.item == null) {
                    unlink(x);
                    return true;
                }
            }
        } else {
            //如果删除元素不为null：
            for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next) {
                if (o.equals(x.item)) {
                    unlink(x);
                    return true;
                }
            }
        }
        return false;
    }
    //移除LinkedList结点：remove()方法中调用
    E unlink(java.util.LinkedList.Node<E> x) {
        //获取被删除结点的元素E：
        final E element = x.item;
        //获取被删除元素的后指针结点：
        final java.util.LinkedList.Node<E> next = x.next;
        //获取被删除元素的前指针结点：
        final java.util.LinkedList.Node<E> prev = x.prev;

        //被删除结点的 前结点为null的话：
        if (prev == null) {
            //将后指针指向的结点置为头结点
            first = next;
        } else {
            //前置结点的  尾结点指向被删除的next结点；
            prev.next = next;
            //被删除结点前指针置为null:
            x.prev = null;
        }
        //对尾结点同样处理：
        if (next == null) {
            last = prev;
        } else {
            next.prev = prev;
            x.next = null;
        }

        x.item = null;
        size--;
        modCount++;
        return element;
    }

    //得到首个结点：集合没有元素报错
    public E getFirst() {
        //获取first结点：
        final java.util.LinkedList.Node<E> f = first;
        if (f == null)
            throw new NoSuchElementException();
        return f.item;
    }

    //得到最后一个结点：集合没有元素报错
    public E getLast() {
        //获取last结点：
        final java.util.LinkedList.Node<E> l = last;
        if (l == null)
            throw new NoSuchElementException();
        return l.item;
    }

    //判断obj 是否存在：
    public boolean contains(Object o) {
        return indexOf(o) != -1;
    }
    //LinkedList长度：
    public int size() {
        return size;
    }

    //添加集合：从最后size所在的index开始：
    public boolean addAll(Collection<? extends E> c) {
        return addAll(size, c);
    }
    //LinkedList添加集合：
    public boolean addAll(int index, Collection<? extends E> c) {
        //检查角标是否正确：
        checkPositionIndex(index);
        Object[] a = c.toArray();
        int numNew = a.length;
        if (numNew == 0)
            return false;
        java.util.LinkedList.Node<E> pred, succ;
        if (index == size) {
            succ = null;
            pred = last;
        } else {
            succ = node(index);
            pred = succ.prev;
        }
        for (Object o : a) {
            E e = (E) o;
            java.util.LinkedList.Node<E> newNode = new java.util.LinkedList.Node<>(pred, e, null);
            if (pred == null)
                first = newNode;
            else
                pred.next = newNode;
            pred = newNode;
        }
        if (succ == null) {
            last = pred;
        } else {
            pred.next = succ;
            succ.prev = pred;
        }
        size += numNew;
        modCount++;
        return true;
    }

    //清空LinkedList：
    public void clear() {
        //遍历LinedList集合：
        for (java.util.LinkedList.Node<E> x = first; x != null; ) {
            //将每个结点的前指针 尾指针  元素都置为null：
            java.util.LinkedList.Node<E> next = x.next;
            x.item = null;
            x.next = null;
            x.prev = null;
            x = next;
        }
        //头尾结点 都置为null：
        first = last = null;
        //长度置为0
        size = 0;
        //操作数+1：
        modCount++;
    }

    //获取相应角标的元素：
    public E get(int index) {
        //检查角标是否正确：
        checkElementIndex(index);
        //获取角标所属结点的 元素值：
        return node(index).item;
    }

    //设置对应角标的元素：
    public E set(int index, E element) {
        checkElementIndex(index);
        java.util.LinkedList.Node<E> x = node(index);
        E oldVal = x.item;
        x.item = element;
        return oldVal;
    }

    //删除对应角标的元素：
    public E remove(int index) {
        checkElementIndex(index);
        return unlink(node(index));
    }

    //获取对应角标所属于的结点：
    java.util.LinkedList.Node<E> node(int index) {
        //位运算：如果位置索引小于列表长度的一半，从前面开始遍历；否则，从后面开始遍历；
        if (index < (size >> 1)) {
            java.util.LinkedList.Node<E> x = first;
            //从头结点开始遍历：遍历的长度就是index的长度，获取对应的index的元素
            for (int i = 0; i < index; i++)
                x = x.next;
            return x;
        } else {
            //从集合尾结点遍历：
            java.util.LinkedList.Node<E> x = last;
            //同样道理：
            for (int i = size - 1; i > index; i--)
                x = x.prev;
            return x;
        }
    }
    // 左移相当于*2，只是要注意边界问题。如char a = 65； a<<1 按照*2来算为130;
    // 但有符号char的取值范围-128~127，已经越界，多超出了3个数值，
    // 所以从-128算起的第三个数值-126才是a<<1的正确结果。
    //而右移相当于除以2，只是要注意移位比较多的时候结果会趋近去一个非常小的数，如上面结果中的-1，0。

    private boolean isElementIndex(int index) {
        return index >= 0 && index < size;
    }

    //判断传入的index是否正确：
    private boolean isPositionIndex(int index) {
        return index >= 0 && index <= size;
    }

    private String outOfBoundsMsg(int index) {
        return "Index: "+index+", Size: "+size;
    }

    private void checkElementIndex(int index) {
        if (!isElementIndex(index))
            throw new IndexOutOfBoundsException(outOfBoundsMsg(index));
    }

    //检查传入的角标 是否正确：
    private void checkPositionIndex(int index) {
        //必须大于0 ，并且不能大于当前size：
        if (!isPositionIndex(index))
            throw new IndexOutOfBoundsException(outOfBoundsMsg(index));
    }
    public int indexOf(Object o) {
        int index = 0;
        if (o == null) {
            for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next) {
                if (x.item == null)
                    return index;
                index++;
            }
        } else {
            for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next) {
                if (o.equals(x.item))
                    return index;
                index++;
            }
        }
        return -1;
    }
    public int lastIndexOf(Object o) {
        int index = size;
        if (o == null) {
            for (java.util.LinkedList.Node<E> x = last; x != null; x = x.prev) {
                index--;
                if (x.item == null)
                    return index;
            }
        } else {
            for (java.util.LinkedList.Node<E> x = last; x != null; x = x.prev) {
                index--;
                if (o.equals(x.item))
                    return index;
            }
        }
        return -1;
    }

    //获取第一个元素，不存在则抛异常
    public E element() {
        return getFirst();
    }

    //出队，获取第一个元素，不出队列，只是获取
    // 队列先进先出；不存在不抛异常，返回null
    public E peek() {
        //获取头结点：
        final java.util.LinkedList.Node<E> f = first;
        //存在获取头结点元素，不存在返回null
        return (f == null) ? null : f.item;
    }

    //出队，并移除第一个元素；不存在不抛异常。
    public E poll() {
        final java.util.LinkedList.Node<E> f = first;
        return (f == null) ? null : unlinkFirst(f);
    }

    //出队（删除第一个结点），如果不存在会抛出异常而不是返回null，存在的话会返回值并移除这个元素（节点）
    public E remove() {
        return removeFirst();
    }

    //入队(插入最后一个结点)从最后一个元素
    public boolean offer(E e) {
        return add(e);
    }

    //入队（插入头结点），始终返回true
    public boolean offerFirst(E e) {
        addFirst(e);
        return true;
    }

    //入队（插入尾结点），始终返回true
    public boolean offerLast(E e) {
        addLast(e);
        return true;
    }

    //出队（从前端），获得第一个元素，不存在会返回null，不会删除元素（节点）
    public E peekFirst() {
        final java.util.LinkedList.Node<E> f = first;
        return (f == null) ? null : f.item;
    }

    //出队（从后端），获得最后一个元素，不存在会返回null，不会删除元素（节点）
    public E peekLast() {
        final java.util.LinkedList.Node<E> l = last;
        return (l == null) ? null : l.item;
    }

    //出队（从前端），获得第一个元素，不存在会返回null，会删除元素（节点）
    public E pollFirst() {
        final java.util.LinkedList.Node<E> f = first;
        return (f == null) ? null : unlinkFirst(f);
    }

    //出队（从后端），获得最后一个元素，不存在会返回null，会删除元素（节点）
    public E pollLast() {
        final java.util.LinkedList.Node<E> l = last;
        return (l == null) ? null : unlinkLast(l);
    }

    //入栈，从前面添加  栈 后进先出
    public void push(E e) {
        addFirst(e);
    }

    //出栈，返回栈顶元素，从前面移除（会删除）
    public E pop() {
        return removeFirst();
    }

    //节点的数据结构，包含前后节点的引用和当前节点
    private static class Node<E> {
        //结点元素：
        E item;
        //结点后指针
        java.util.LinkedList.Node<E> next;
        //结点前指针
        java.util.LinkedList.Node<E> prev;

        Node(java.util.LinkedList.Node<E> prev, E element, java.util.LinkedList.Node<E> next) {
            this.item = element;
            this.next = next;
            this.prev = prev;
        }
    }
        
    //迭代器：
    public ListIterator<E> listIterator(int index) {
        checkPositionIndex(index);
        return new java.util.LinkedList.ListItr(index);
    }
    private class ListItr implements ListIterator<E> {
        private java.util.LinkedList.Node<E> lastReturned = null;
        private java.util.LinkedList.Node<E> next;
        private int nextIndex;
        private int expectedModCount = modCount;

        ListItr(int index) {
            next = (index == size) ? null : node(index);
            nextIndex = index;
        }

        public boolean hasNext() {
            return nextIndex < size;
        }

        public E next() {
            checkForComodification();
            if (!hasNext())
                throw new NoSuchElementException();

            lastReturned = next;
            next = next.next;
            nextIndex++;
            return lastReturned.item;
        }

        public boolean hasPrevious() {
            return nextIndex > 0;
        }

        public E previous() {
            checkForComodification();
            if (!hasPrevious())
                throw new NoSuchElementException();

            lastReturned = next = (next == null) ? last : next.prev;
            nextIndex--;
            return lastReturned.item;
        }

        public int nextIndex() {
            return nextIndex;
        }

        public int previousIndex() {
            return nextIndex - 1;
        }

        public void remove() {
            checkForComodification();
            if (lastReturned == null)
                throw new IllegalStateException();

            java.util.LinkedList.Node<E> lastNext = lastReturned.next;
            unlink(lastReturned);
            if (next == lastReturned)
                next = lastNext;
            else
                nextIndex--;
            lastReturned = null;
            expectedModCount++;
        }

        public void set(E e) {
            if (lastReturned == null)
                throw new IllegalStateException();
            checkForComodification();
            lastReturned.item = e;
        }

        public void add(E e) {
            checkForComodification();
            lastReturned = null;
            if (next == null)
                linkLast(e);
            else
                linkBefore(e, next);
            nextIndex++;
            expectedModCount++;
        }

        final void checkForComodification() {
            if (modCount != expectedModCount)
                throw new ConcurrentModificationException();
        }
    }
   
    private java.util.LinkedList<E> superClone() {
        try {
            return (java.util.LinkedList<E>) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new InternalError();
        }
    }

    public Object clone() {
        java.util.LinkedList<E> clone = superClone();
        clone.first = clone.last = null;
        clone.size = 0;
        clone.modCount = 0;
        for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next)
            clone.add(x.item);
        return clone;
    }

    public Object[] toArray() {
        Object[] result = new Object[size];
        int i = 0;
        for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next)
            result[i++] = x.item;
        return result;
    }
    @SuppressWarnings("unchecked")
    public <T> T[] toArray(T[] a) {
        if (a.length < size)
            a = (T[])java.lang.reflect.Array.newInstance(
                    a.getClass().getComponentType(), size);
        int i = 0;
        Object[] result = a;
        for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next)
            result[i++] = x.item;

        if (a.length > size)
            a[size] = null;

        return a;
    }

    private static final long serialVersionUID = 876323262645176354L;

    private void writeObject(java.io.ObjectOutputStream s)
            throws java.io.IOException {
        s.defaultWriteObject();

        s.writeInt(size);

        for (java.util.LinkedList.Node<E> x = first; x != null; x = x.next)
            s.writeObject(x.item);
    }
    @SuppressWarnings("unchecked")
    private void readObject(java.io.ObjectInputStream s)
            throws java.io.IOException, ClassNotFoundException {
        s.defaultReadObject();

        int size = s.readInt();

        for (int i = 0; i < size; i++)
            linkLast((E)s.readObject());
    }
}
```

