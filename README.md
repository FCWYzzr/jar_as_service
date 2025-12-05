# JarAsService 项目

## 项目概述

JarAsService 是一个将 JAR 文件作为 Windows 托盘应用程序运行的工具。它允许用户将 Java 应用程序作为托盘应用程序运行。

## 项目功能

- 将同目录下的第一个 JAR 文件作为 Windows 托盘应用程序运行。
- 点击托盘图标关闭服务。
- 自动检测并使用 `JAVA_HOME` 环境变量中的 Java 运行时。


## 使用 CLion 构建和安装

1. 打开CLion并选择`File -> Open`，然后导航到项目的根目录并打开`CMakeLists.txt`文件。
2. 确保你已经配置了C++23 MSVC编译器支持。
3. 在CLion的终端中运行以下命令来安装依赖项：
   ```sh
   git submodule update --init --recursive
   ```
4. 在CLion中构建项目：选择`Build -> Build Project`。

## 依赖项

- [f-lib](https://github.com/FCWYzzr/f-lib)：现代C++的辅助设施。
- C++23 编译器支持。
- Windows SDK。
