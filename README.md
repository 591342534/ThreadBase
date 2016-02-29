# ThreadBase
在进行程序开发时，不可避免会创建线程，新建线程就要处理线程同步，线程安全退出等相关问题。这是一个封装好的创建工作线程的基类, 封装了和业务无关的线程逻辑， 使用非常方便.

使用时，只需从CTheardBase派生一个类CWorkThread，重载OnThreadFunc()函数，把用把需要在工作线程做的业务逻辑在OnThreadFunc()函数中实现就可以。
外面使用时，只用创建一个CWorkThread对象，
调用Start()函数来启动线程，
IsRun()来判断显示是否执行完成
Stop()来安全退出线程。

在实现OnThreadFunc()函数时，用m_hStopEvent这个事件来判断外面已经结束线程，如果m_hStopEvent被设置，则应该立刻从OnThreadFunc()函数退出，让工作线程结束。

开发多线程程序时，不要直接杀线程，这样会造成未知的后果，也不要让线程变为野线程。最好的方法就是从线程函数安全退出。
