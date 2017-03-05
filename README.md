# ImagePlayer

[![](https://img.shields.io/badge/author-TongxinV-green.svg)](https://github.com/TongxinV)
[![GitHub issues](https://img.shields.io/github/issues/TongxinV/ImagePlayer.svg)](https://github.com/TongxinV/ImagePlayer/issues)

> 图片编解码

### Environment
```cc
Arch：s5pv210 cortex-A8
OS：linux2.6.35
```

### software development process

```c
环境搭建和基础环境确认
framebuffer设置及常见功能添加
BMP 图像数据catch |- 色序转变 -|- 显示
JPEG库的移植和使用 |- 阅读文档 -|- 显示
PNG.库的移植和使用 |- 阅读文档 -|- 显示
图片管理器简单实现
实现触摸翻页
```

### Summary


```
    合理运用指针 -|- 结构体指针的运用 
    程序模块化编程 -|- 程序框架构思
    功能模块内部细分基本实现接口以便于扩展
    解决程序BUG
```

#### Version Update

    使用内核链表管理图片（旧管理方式位于分支manage-pic-array）

----
author：@TongxinV
