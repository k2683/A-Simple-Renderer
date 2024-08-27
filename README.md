# 如何使用

## 环境配置
确保您的开发环境支持C++标准库，并能够处理TGA文件格式。您可以使用任何支持C++的IDE或编译器。

## 编译与运行
需要绘制的obj文件放于obj文件夹下
```
make

./main
```
render完成的tga图片在output文件夹下生成

## render过程
在逐像素render和Z buffer的过程外加上了MVP变换

## MVP变换
### Model变换
将物体从它自身的局部坐标系转换到世界坐标系。
### View变换
我们把摄像机放在(1, 1, 3)的位置。通过移动物体而不是摄像机的方式来实现摄像机的朝向。

### Projection变换
用Perspective Projection
这部分和games101作业1的内容基本重合
[View the README file](https://github.com/k2683/Games101-Homework/blob/Homework1/README.md)

最后把标准化设备坐标系（NDC）转换为屏幕坐标系。
