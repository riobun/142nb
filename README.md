# Honor of Kings
  TJ 2019 SSE final project

### 怎样更改
- 创建新的分支(branch)进行更改，在分支改好后，创建拉请求(pull request)，请求将更改合并到主支
- 每次commit仅包含一项功能的更改
- 在拉请求页面，得到另外两名队友的:+1:（输入: + 1 :）后，更改者将更改合并至主支
- 多写注释，为每一次更改写描述（目的与手段）

### 项目主要流程
- 设计游戏原型和脚本  
    界面草稿，游戏玩法
- 游戏工程创建和初始化  
    创建项目  
    多分辨率支持（需要资源图片）  
    通用类与基类维护  
    发布到GitHub  
- 创建Loading场景，Home场景（菜单）等  
- 游戏逻辑实现  
- 电脑AI
- 服务器与网络通信
    
### 可能的分工
- 美工和界面设计  
    资源图片，图片、纹理处理，Loading, Home, 设置、帮助场景设计  
- 游戏逻辑  
    用户事件处理，接触检测，电脑AI  
- 服务器和网络通信  
    实现联机  
- 没想好  
    
### 必须达成的代码规范
- 缩进4格（空格而非制表符），大括号换行，每行代码字符数不超过80
- 尽可能使用`const`和引用
- 命名统一遵循 [Google命名约定](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#)
- 其它规范也参照[Google代码规范](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/)，下面列举几条重要的：
  - 使用 #define 防止头文件被多重包含
  - 类  
    类定义以`private:`开始，后跟 `protected:`，最后是`public:`  
    不要定义隐式类型转换  
    使用组合往往比继承更合理  
    除了少数特定环境外，不要重载运算符  
    将所有数据成员声明为`private`,除非是`static` `const`类型成员  
  - 对迭代器和其它模板对象使用前缀形式(++i)的自增、自减运算符  
  - 仅使用C++风格类型转换，如`static_cast` `dynamic_cast`  

### 其它
- 在Issue中有一个专门分享参考资料的
- 注意说明文档中必须使用的C++特性

### 项目原始要求
- 服务端：联机，电脑AI
- 1v1地图
- 三种英雄，三种小兵
- 小兵、防御塔AI
- 金钱获取，经验、等级系统
- 装备系统，装备、战绩页面查看

进阶：（打勾的拟完成）
- 5v5地图
- 更多英雄类 ✔
- 三种野怪
- 聊天

- 使用单元测试、持续集成平台
- 使用断言 ✔
- 跨平台 ✔
- 使用boost库
- 设计模式 ✔
