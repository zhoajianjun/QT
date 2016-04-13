#FramelessHelper 说明

FramelessHelper 类用于简化编写无边框窗口的过程. 封装了窗口拖动和窗口拉伸这部分比较麻烦的代码, 这样在编写无边框应用程序的时候, 只需要专注于 UI 外观的设计, 使其复杂度基本同常规的有边框程序相当.

## 1.引入 FramelessHelper 代码到项目中

把 src 文件夹中的 4个文件 `framelesshelper.h`, `framelesshelper.cpp`, `framelesshelperprivate.h` 和 `framelesshelperprivate.cpp` 复制/添加到你的项目中. 并在你相关的代码中加入头文件 `framelesshelper.h`.

**备注:** *`framelesshelper.h` 和 `framelesshelper.cpp` 为接口类, 如果只想使用这个类, 但不想关注实现细节, 则无需理会 `framelesshelperprivate.h` 和 `framelesshelperprivate.cpp` 中的内容(但是依旧需要在项目中添加这两个文件). 如果你想查看实现细节, 那么可以看看这两个文件中的源码.*

## 2.接口说明

### 2.1 构造函数 `FramelessHelper(QWidget *parent)`

parent: 需要通过这个参数来指定需要无边框化处理的 Widget.

调用该构造函数后, parent 指定的 Widget 即会变成无边框的 Widget. 注意 parent 指定的 Widget 应该是一个独立窗口, 而不是一个内嵌的子窗口, 即 isWindow() 返回值应该为 true, 否则的行为是未定义的.

通常在需要无边框话处理的 Widget 的构造函数中调用该构造函数, 代码如下:

``` C++
FramelessHelper *frameless = new FramelessHelper(this);
```

只需要这一行代码, 可以发现窗口原生的标题栏和边框都没了, 同时, 窗口四周可以通过鼠标缩放窗口了.

### 2.2 拖动窗口 `void addDragWidget(QWidget *widget)`

这个函数用来指定鼠标按住哪些 widget 后, 可以移动窗口. 如需指定多个 widget, 多次调用该函数即可.

### 2.3 边缘 widget 捕抓 `void addEdgeWidget(QWidget *widget)`

把鼠标放置在常规窗口最小化/最大化/关闭的顶部边缘处, 会发现焦点并不在按钮上, 而是鼠标指针变成了上下双箭头的形状, 这时按下鼠标, 可以移动鼠标来上下拉伸窗口. 这个函数就是提供这个功能的.

具体效果, 可以注意示例 demo1 中最小化按钮和其它按钮的区别.

### 2.4 常用按钮设置

`void setCloseButton(QPushButton *button, bool edgeResize = true);`

`void setMaximizedButton(QPushButton *button, bool edgeResize = true);`

`void setMinimizedButton(QPushButton *button, bool edgeResize = true);`

`void setRestoreButton(QPushButton *button, bool edgeResize = true);`

以上四个函数分别用来设置 关闭/最大化/最小化/还原 按钮. 第二个参数指定是否捕抓该按钮边缘. 即

``` C++
setXxxButton(button)
```

等效于

``` C++
setXxxButton(button, false);
addEdgeWidget(button)
```

### 2.5 设置边缘边距

即设置鼠标在这个边缘内, 鼠标会变成双箭头指针, 这是按下移动可改变窗口大小.

`void setResizeMargins(const QMargins &margins)` 通过 QMargins 来指定 左/上/右/下 边距.

`void setResizeMargins(int margin)` 如果4个边距相同, 则可调用这个函数.

如果未调用该函数, 则默认边距为 QMargins(5, 5, 5, 5);

如果不想通过鼠标改变窗口大小, 可以把边距设为 0;

## 3 其它

大家如有任何关于该类的问题, 可以直接发布讨论.
