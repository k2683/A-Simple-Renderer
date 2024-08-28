# 如何使用

## 环境配置
确保您的开发环境支持C++标准库，并能够处理TGA文件格式。您可以使用任何支持C++的IDE或编译器。

## 编译与运行
需要绘制的obj文件放于obj文件夹下
```
make
./main your_model.obj
```
render完成的tga图片在output文件夹下生成

## 渲染过程
与之前逐像素渲染的过程有较大差别

### 1.vertex shader
对每个顶点进行变换，依次应用模型视图矩阵和投影矩阵，将顶点从模型空间变换到裁剪空间。

计算并存储与顶点相关的插值变量（如法线、纹理坐标等），供后续片段着色器使用。

输出变换后的裁剪空间坐标。
### 2.rasterize
将三角形顶点从裁剪空间变换到屏幕空间

通过计算三角形顶点的最小和最大x、y值，确定屏幕上该三角形所覆盖的像素区域。

对包围盒中的每个像素进行重心坐标计算，根据重心坐标判断像素是否在三角形内部。

如果在三角形内部，则进行深度测试（比较深度缓冲区的值与当前片段的深度）。
### 3.fragment shader
插值三角形顶点的法线、纹理坐标等属性。

进行phong shading计算，确定当前像素的颜色。

如果片段没有被丢弃，并且通过了深度测试，则将颜色值写入目标图像，将深度值写入深度缓冲区。

至于实现的细节部分比如phong shading的计算，uv的读取以及向量的变换原理可以参考[games101的作业3](https://github.com/k2683/Games101-Homework/edit/Homework3/README.md)
# 实现效果
![image](https://github.com/user-attachments/assets/df723608-d5b2-4494-8e99-43678c87ae6d)

<img width="389" alt="image" src="https://github.com/user-attachments/assets/096f2fe0-0344-4fb5-a8e3-b12d0a7aa937">

