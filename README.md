# 项目简介
这是一个从零开始搭建的基础渲染器项目。除了使用 [tinyrender](https://github.com/ssloy/tinyrenderer) 提供的 tgaimage.h 和 tgaimage.cpp 文件来读取图片外，项目的其余部分均为手动实现。这是一个非常适合深入理解渲染管线的实践项目。

OpenGL 的渲染管线可以概述如下：
![image](https://github.com/user-attachments/assets/745f8c4f-0c20-474d-ab1f-ed01d139904c)
这个项目实现了渲染的核心部分，包括vertex shader rasterizer 和fragment shader

每个分支的 README 文件中详细解释了实现的原理和细节，便于逐步学习和掌握。

当然它作为一个简单的渲染器还有很多可以优化的地方。比如阴影的区域的渲染可以多加一个通道从光源出发渲染得到阴影图，用阴影图乘以shading得到的模型来实现阴影。但本项目的目的在于实现主要的渲染过程，因此对于此类细节和提升部分暂时省略。
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

# 实现效果
![image](https://github.com/user-attachments/assets/251791fd-444c-4b42-af47-f0ea693bf899)
![image](https://github.com/user-attachments/assets/7acbe656-5c52-406a-87ae-b1b68823f513)
