 synchronized和lock 都属于悲观锁，都是采取加锁的机制进行同步。

## 1.1 synchronized和lock的性能比较

   在JDK1.5中，synchronized是性能低效的。因为这是一个重量级操作，它对性能最大的影响是阻塞的是实现，挂起线程和恢复线程的操作都需要转入内核态中完成，这些操作给系统的并发性带来了很大的压力。相比之下使用Java提供的Lock对象，性能更高一些。在资源竞争不是很激烈的情况下，Synchronized的性能要优于ReetrantLock，但是在资源竞争很激烈的情况下，Synchronized的性能会下降几十倍，但是ReetrantLock的性能能维持常态；

  到了JDK1.6，发生了变化，对synchronize加入了很多优化措施，有自适应自旋，锁消除，锁粗化，轻量级锁，偏向锁等等。导致在JDK1.6上synchronize的性能并不比Lock差。官方也表示，他们也更支持synchronize，在未来的版本中还有优化余地，所以还是提倡在synchronized能实现需求的情况下，优先考虑使用synchronized来进行同步。

## 1.2 synchronized和lock的用法比较

  基本语法上，ReentrantLock与synchronized很相似，它们都具备一样的线程重入特性。synchronized是在JVM层面上实现的，不但可以通过一些监控工具监控synchronized的锁定，而且在代码执行时出现异常，JVM会自动释放锁定，但是使用Lock则不行，lock是通过代码实现的，要保证锁定一定会被释放，就必须将unLock()放到finally{}中。

  **ReentrantLock**相对**synchronized(**内置锁**)**而言，有以下三项不同：

 1.ReentrantLock 支持中断等待获取锁的线程：当持有锁的线程长期不释放锁时，正在等待的线程可以选择放弃等待，改为处理其他事情，它对处理执行时间非常上的同步块很有帮助。而在等待由synchronized产生的互斥锁时，会一直阻塞，是不能被中断的。

  2.synchronized 必须在获取锁的代码块中释放锁，但是ReentrantLock 可以更加灵活的选择何时去释放锁。

  3.ReentrantLock 可实现公平锁和不公平锁：多个线程在等待同一个锁时，必须按照申请锁的时间顺序排队等待，而非公平锁则不保证这点，在锁释放时，任何一个等待锁的线程都有机会获得锁。synchronized中的锁为非公平锁，ReentrantLock默认情况下也是非公平锁，但可以通过构造方法ReentrantLock（ture）来要求使用公平锁。

  4.ReentrantLock 可以绑定多个条件：一个ReentrantLock对象可以同时绑定多个Condition对象（条件变量或条件队列），而在synchronized中，锁对象的wait()和notify()或notifyAll()方法可以实现一个隐含条件，但如果要和多于一个的条件关联的时候，就不得不额外地添加一个锁，而ReentrantLock则无需这么做，只需要多次调用newCondition()（此为Lock接口中规定创建Condition监视器的方法）即可。而且我们还可以通过绑定Condition对象来判断当前线程通知的是哪些线程（即与Condition对象绑定在一起的相关线程）。synchronized使用object类中的监视器方法wait和notify，而且只能创建一个监视器队列，但是Lock接口可以创建多个Condition实例，然后调用await和singal来操作。

  ReentrantLock和synchronized 提供了相同的互斥性和内存可见性。在获取 ReentrantLock 时，有着与进入同步代码块相同的内存语义，在释放ReentrantLock 时，同样有着与退出代码块相同的内存语义。但是和synchronized 相比，ReentrantLock为处理锁的不可用性提供了更高的灵活性。灵活性更高，也可能更加危险，一旦忘记手动释放lock锁，可能会造成意想不到的后果，这也是ReentrantLock 不能完全替代 synchronized 的原因。

 Lock锁具体用法：

ReentrantLock获取锁定有三种方式：
    a) lock(), 如果获取了锁立即返回，如果别的线程持有锁，当前线程则一直处于休眠状态，直到获取锁。锁的释放使用unlock()方法。需要同步的代码写在加锁和释放锁的中间，可以灵活调整加锁和解锁方法的位置。

​    b) tryLock(), 如果获取了锁立即返回true，如果别的线程正持有锁，立即返回false；当前线程尝试获取锁，如果这一时刻没有被其他线程获取到，则成功获取并持有锁。如果这一时刻锁被其他线程获取到，当前线程可以选择继续等也可以选择不继续等，而synchronized锁是必须死等。

​    c)tryLock(long timeout,TimeUnit unit)， 如果获取了锁定立即返回true，如果别的线程正持有锁，会等待参数给定的时间，在等待的过程中，如果获取了锁定，就返回true，如果等待超时，返回false；
​    d) lockInterruptibly:如果获取了锁定立即返回，如果没有获取锁定，当前线程处于休眠状态，直到或者锁定，或者当前线程被别的线程中断。和lock()不同之处在于该方法可以响应中断，即线程在等待获取锁的过程中（还没获取）线程可调用interrupt()方法终止等待。

![img](https://oscimg.oschina.net/oscnet/548ca03aab22fa5ce87ae437cb408afe0b3.jpg)

**锁类型：**

可重入锁：在执行对象中所有同步方法不用再次获得锁。ReentrantLock和synchronized
可中断锁：在等待获取锁过程中可中断。ReentrantLock
公平锁： 按等待获取锁的线程的等待时间进行获取，等待时间长的具有优先获取锁权利。ReentrantLock
读写锁：对资源读取和写入的时候拆分为2部分处理，读的时候可以多线程一起读，写的时候必须同步地写。ReentrantReadWriteLock

 

**3.总结**

  **synchronized**： 在资源竞争不是很激烈的情况下，偶尔会有同步的情形下，synchronized是很合适的。原因在于，编译程序通常会尽可能的进行优化synchronize，另外可读性非常好。

  **ReentrantLock**: 提供了多样化的同步，比如有时间限制的同步，可以被Interrupt中断（synchronized的同步是不能Interrupt的）。在资源竞争不激烈的情形下，性能稍微比synchronized差点点。但是当同步非常激烈的时候，synchronized的性能一下子能下降好几十倍。而ReentrantLock确还能维持常态。

  **Atomic**: 不激烈情况下，性能比synchronized略逊，而激烈的时候，也能维持常态。激烈的时候，Atomic的性能会优于ReentrantLock一倍左右。但是其有一个缺点，就是只能同步一个值，一段代码中只能出现一个Atomic的变量，多于一个同步无效。因为它不能在多个Atomic之间同步。
  同步优先考虑synchronized，如果有特殊需要，再进一步优化。ReentrantLock和Atomic如果用的不好，不仅不能提高性能，还可能带来灾难。