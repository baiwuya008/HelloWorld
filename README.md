
# DA项目应用文档

 仓库地址：
**gittest@192.168.12.170:/home/gittest/repositories/st-a5/okl-qt-app.git**

## 架构分析

- OklMain.pro
- 头文件
	- Src
		- Application
			- Avin
			- BlurTooth
			- Ipod
			- Launcher
			- MultiMedia
			- Radio
			- Setting
			- SystemUi
			- AllApplication.h
		- CommonUserWidget
			- BmpButton.h
			- BmpWidget.h
			- CustomItemDelegate.h
			- CustomScrollBar.h
			- MessageBox.h
			- Slier.h
			- TextWidget.h
			- UserInterfaceUtillty.h
		- Framework
			- Base
				- Audio
				- Core
					- activity.h
					- application.h
					- apptype.h
					- context.h
					- message.h
					- service.h
					- simulation.h
				- Vide
			- View
				- toast.h
		- Simulation
			- simulation.h
	- configuration.h
	- mainwindow.h
- 源文件
	- Src
		- 同上.cpp
	- main.cpp
	- mainwindow.cpp
- 资源


**整个项目秉承着Android的设计理念，有Context，Activity,Service，BrocastReceiver等系统组件**

- Application
	- 应用代码
- CommonUserWidget
	- 通用组件
- Framework
	- 中间件
- Simulation
	- 模拟器

**其中几个通用的核心类**

- mainwindow.cpp
	- 配置窗口大小
- configuration.h
	- 相关配置常量
- Framwwork/
	- 系统核心组件，如Toast
- AppType
	- App类型


**深入组件中，我们可以查看Activity**

- mpContentView  
	- 记录parent
- mState
	- 记录声明周期
- Q_D 
	- 二进制兼容

**Activity对外公开的方法**

- onCreate
	- 创建
- onStart
	- 开始
- onResume
	- 运行
- onPause
	- 暂停
- onStop
	- 停止
- onDestroy
	- 销毁
- onBackPressed
	- 按了返回按钮
- onLanguageChanged
	- 语言改变
- onReceiveBroadcast
	- 广播接收器
- onReceiveCmd
	- 命令接收

**Application对外公开的方法**

- setWindowWidget
	- 设置窗口组件
- callBackPressed
	- 返回键按下监听
- callLanguageChanged
	- 语音切换监听
- startApplication
	- 启动App
- sendBroadcast
	- 发送广播
- onReceiveBroadcast
	- 广播接收器
- sendCmdTo
- onReceiveCmd

**相关技巧**

- 启动一个App
	- q->startApplication(Apptype);

- 如何新建一个App
	- 1.创建在对应的目录下Src/Application/xxApp 并且继承Activity
	- 2.在AllApplication.h中插入你的头文件
	- 3.你创建的头文件插入
		- include "Src/Framework/Base/Core/activity.h"
	- 4.AppType中增加你的Type
	- 5.在application.cpp中insert



