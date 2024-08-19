# 如何使用

## 环境配置
确保您的开发环境支持C++标准库，并能够处理TGA文件格式。您可以使用任何支持C++的IDE或编译器。

## 编译与运行
需要绘制的obj文件放于obj文件夹下
make
./main
绘制线条完成的tga图片在output文件夹下生成

## Bresenham画线算法

### 概述

Bresenham的直线算法是一种高效的方法，适用于在像素网格中绘制直线。此算法特别适合于计算机图形领域，能够在整数精度下精确且快速地确定哪些像素最适合表示直线。

### 算法过程

#### 初始参数

直线的起点和终点分别为 `(x0, y0)` 和 `(x1, y1)`。计算两点之间的差值：

- `dx = x1 - x0`
- `dy = y1 - y0`

设置初始决策参数 `p = 2*dy - dx`，用于决定绘制过程中的像素选择。

#### 步进方向

根据起点和终点的相对位置确定 x 和 y 的增加或减少方向。整个算法过程中，x 的增加是一定的，而 y 的增加取决于斜率和决策参数。

#### 迭代绘制像素

从 `x0` 开始到 `x1`，执行以下操作：

- 绘制当前像素 `(x, y)`
- 更新决策参数 `p`：
  - 如果 `p < 0`，则 `p` 更新为 `p + 2*dy`
  - 否则，`p` 更新为 `p + 2*(dy - dx)` 并且 `y` 增加一步

重复以上过程，直到到达 `(x1, y1)`。

### 算法原理
