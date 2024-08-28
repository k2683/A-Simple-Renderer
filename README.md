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
我们的模型是在他们自己的本地框架中创建的。它们进入到以世界坐标表示的场景中，从一个到另一个的转换是通过矩阵 Model 进行的。然后，我们想用相机（眼睛坐标）来表达它，这个转换叫做 View。然后，我们使用 Projection 矩阵对场景进行变形以创建透视变形，该矩阵将场景转换为clip coordinates。最后，我们绘制场景，将clip coordinates转换为屏幕坐标的矩阵称为 Viewport。
### Model变换
将物体从它自身的局部坐标系转换到世界坐标系。
### View变换
我们把摄像机放在(1, 1, 3)的位置。将物体进行平移和旋转的变换。

### Projection变换
用Perspective Projection
这部分和games101作业1的内容基本重合
[View the README file](https://github.com/k2683/Games101-Homework/blob/Homework1/README.md)

最后把标准化设备坐标系（NDC）转换为屏幕坐标系。
# 实现效果
![image](https://github.com/user-attachments/assets/8a5df9b1-af39-410e-9d02-88b8681bfa22)
