LLVM 语言参考手册
================================

* `概述`_
* 简介
    - 良好构成
* 标识符
* 高阶结构
    #. 模块结构
    #. 链接类型
    #. 调用约定
    #. 可见类型
    #. DLL存储类
    #. 局部线程存储模型
    #. 运行时优先权定界符
    #. 结构类型
    #. 非整数指针类型
    #. 全局变量
    #. 函数
    #. 别名
    #. 函数别名
    #. 封装
    #. 命名元数据
    #. 参数属性
    #. 垃圾回收策略名
    #. 前缀数据
    #. 前置数据
    #. 自定函数
    #. 属性组
    #. 函数属性
    #. 全局属性
    #. 操作符绑定
        * 非优化操作符绑定
        * 函数接口操作符绑定
        * 垃圾传递操作绑定
    #. 模块级内联汇编
    #. 数据层
    #. 目标三元组
    #. 指针别名规则
    #. 可变内存存取
    #. 并发操作的内存模型
    #. 原子内存命令约束
    #. 浮点数环境
    #. 快速数学标记
    #. 使用列表命令指令
    #. 源文件名
* 类型系统
    #. 空类型
    #. 函数类型
    #. 一阶类型
        - 单独值类型
            * 整数类型
            * 浮点数类型
            * X86_mmx 类型
            * 指针类型
            * 向量类型
        - 标签类型
        - 记号类型
        - 元数据类型
        - 聚集类型
            * 序列类型
            * 结构类型
            * 透明结构类型
* 常量
    * 简单常量
    * 复杂常量
    * 全局变量和函数地址
    * 未定义值
    * 污染值
    * 基本块值
    * 常量表达式
* 其他值
    * 内联汇编表达式
        * 输出约束
        * 输入约束
        * 间接输入和输出
        * clobber约束
        * 受限代码
        * 支持的受限代码列表
    * 汇编模版参数修饰符
    * 内联汇编元数据
* 元数据
    * 元数据节点和字符串
        * 特定元数据节点
            * DICompileUnit
            * DIFile
            * DIBasicType
            * DISubroutineType
            * DIDerivedType
            * DICompositeType
            * DISubrange
            * DIEnumerator
            * DITemplateTypeParameter
            * DITemplateValueParameter
            * DINamespace
            * DIGlobalVariable
            * DISubprogram
            * DILexicalBlock
            * DILexicalBlockFile
            * DILocation
            * DILocalVariable
            * DIExpression
            * DIObjCProperty
            * DIImportedEntity
            * DIMacro
            * DIMacroFile
        * 'tbaa' 元数据
            * 语义
            * 表达
        * 'tbaa.struct' 元数据
        * 'noalias' 和 'alias.scope' 元数据
        * 'fpmath' 元数据
        * 'range' 元数据
        * 'absolute_symbol' 元数据
        * 'callees' 元数据
        * 'unpredictable' 元数据
        * 'llvm.loop'
        * 'llvm.loop.vectorize' 和 'llvm.loop.interleave'
        * 'llvm.loop.interleave.count' 元数据
        * 'llvm.loop.vectorize.enable' 元数据
        * 'llvm.loop.vectorize.width' 元数据
        * 'llvm.loop.unroll'
        * 'llvm.loop.unroll.count' 元数据
        * 'llvm.loop.unroll.disable' 元数据
        * 'llvm.loop.unroll.runtime.disable' 元数据
        * 'llvm.loop.unroll.enable' 元数据
        * 'llvm.loop.unroll.full' 元数据
        * 'llvm.loop.unroll_and_jam'
        * 'llvm.loop.unroll_and_jam.count' 元数据
        * 'llvm.loop.unroll_and_jam.disable' 元数据
        * 'llvm.loop.unroll_and_jam.enable' 元数据
        * 'llvm.loop.licm_versioning.disable' 元数据
        * 'llvm.loop.distribute.enable' 元数据
        * 'llvm.mem'
        * 'llvm.mem.parallel_loop_access' 元数据
        * 'irr_loop' 元数据
        * 'invariant.group' 元数据
        * 'type' 元数据
        * 'associated' 元数据
        * 'prof' 元数据

            * branch_weights
            * function_entry_count
            * VP







概述
----------
