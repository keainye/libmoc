# mocutils

mocutils (mo-crystal utils) 是魔晶工作室内部的工具库。

## 安装

Linux

```shell
sudo make install
# 如果需要
make clean
```

## 目前已实现

**channel**

简易的 gochannel，可以阻塞地等待数据。

```c++
moc::channel<bool> c;
c < true;
bool recv;
c > recv;
```

**byte**

将 byte 数组进行了一些初步的封装，支持拼接、裁切，字符串转换等。还支持以流的形式读出其中的数据。

**strings**

一些字符串处理函数。
