# mocutils

mocutils (mo-crystal utils) 是魔晶工作室内部的工具库。

## 安装

Linux

```shell
sudo make install
# 如果需要
make clean
```

Windows

```shell
# 管理员模式下
make install
# 如果需要
make clean
```

## 目前已实现

**channel**

功能和 gochannel 完全相同的 channel 工具。

channel 分为无缓冲区（nbchannel）和有缓冲区（bchannel）两种，都是继承自 channel 抽象类。

nbchannel 在管道另一端有等待者的情况下不会阻塞，会直接传输数据；在管道另一端没有等待者的情况下会阻塞，直到对端出现进程，才解除阻塞，传输数据。

bchannel 的功能和用法与 nbchannel 相似。不同之处在于，bchannel 的缓冲区可以容纳本次操作时，不会阻塞。

程序员应当使用 make 宏创建 channel 对象，使用 makeptr 宏创建其指针。这些宏会依据参数，判断程序员需要哪种 channel。当参数仅指定数据 type 时，会返回无缓冲区管道；参数为数据 type & 容量（数字）时，会返回有缓冲区管道。

定义局部变量时，可以使用 auto 关键字来兼容两种 channel；定义参数时，可以使用 channel& 或 channel* 来兼容两种 channel。这么做可以屏蔽两种 channel 的语法差异，代码看起来会比较和谐。

关于使用 channel 进行数据传输，可以参考如下代码

```c++
auto c0 = make(channel, int);         // 无缓冲区 channel (nbchannel)
auto c1 = make(channel, int, 3);      // 有缓冲区 channel (bchannel)
auto c2 = makeptr(channel, int);      // 无缓冲区 channel (nbchannel) 的指针，用完需要 delete
auto c3 = makeptr(channel, int, 3);   // 有缓冲区 channel (bchannel) 的指针，用完需要 delete

int recv;
c0 << 1;    // 传入数据
            // 单线程程序会在此卡死，因为此时无缓冲区管道不可能等到另一个进程取走数据
c0 >> recv; // 取出数据。原理同上
c1 << 1;    // 传入数据。缓冲区未满时不会阻塞
c1 >> recv; // 取出数据，原理同上

// 以下为指针操作，功能和原理同上
*c2 << 1;
*c2 >> recv;
*c3 << 1;
*c3 >> recv;

delete c2;
delete c3;
```

**byte**

将 byte 数组进行了一些初步的封装，支持拼接、裁切，字符串转换等。还支持以流的形式读出其中的数据。

**strings**

一些字符串处理函数。
