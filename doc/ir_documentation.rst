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
* 模块标记元数据
    * Objective-C垃圾手机模块标记元数据
    * C类型宽度模块标记元数据
* 自动链接标记名字元数据
* ThinLTO概述
    * 模块路径概述条目
    * 全局值概述条目
        * 函数概述
        * 全局变量概述
        * 别名概述
        * 函数标记
        * 调用
        * 引用
        * 类型信息
            * 类型测试
            * 类型测试假定调用
            * 类型检查加载调用
            * 类型测试假定常量
            * 类型检查加载常量
    * 类型ID概述条目
* 内嵌全局变量
    * llvm.used
    * llvm.compiler.used
    * llvm.global_ctors
    * llvm.global_dtors
* 指令参考
    #. 终结指令
        #. ret
        #. br
        #. switch
        #. indirectbr
        #. invoke
        #. resume
        #. catchswitch
        #. catchret
        #. cleanupret
        #. unreachable
    #. 二元操作
        #. add
        #. fadd
        #. sub
        #. fsub
        #. mul
        #. fmul
        #. udiv
        #. sdiv
        #. fdiv
        #. urem
        #. srem
        #. frem
    #. 位宽度的二元操作
        #. shl
        #. lshl
        #. ashr
        #. and
        #. or
        #. xor
    #. 向量操作
        #. extractelements
        #. insertelement
        #. shuffleevector
    #. 聚类操作
        #. extractvalue
        #. insertvalue
    #. 内存存取和地址操作
        #. alloca
        #. load
        #. store
        #. fence
        #. cmpxchg
        #. atomicrmw
        #. getelementptr
    #. 转换操作
        #. trunc ... to
        #. zext ... to
        #. sext ... to
        #. fptrunc ... to
        #. fpext ... to
        #. fptoui ... to
        #. fptosi ... to
        #. uitofp ... to
        #. sitofp ... to
        #. ptrtoint ... to
        #. inttoptr ... to
        #. bitcast ... to
        #. addrspacecast ... to
    #. 其他操作
        #. icmp
        #. fcmp
        #. phi
        #. select
        #. call
        #. va_arg
        #. landingpad
        #. cleanuppad
* 内嵌函数
    #. 变量参数处理内嵌
        #. llvm.va_start
        #. llvm.va_end
        #. llvm.va_copy
    #. 精确垃圾收集内嵌
        #. 试验状态点内嵌
        #. llvm.gcroot
        #. llvm.gcread
        #. llvm.gcwrite
    #. 代码生成器内嵌
        #. llvm.returnaddress
        #. llvm.addressofreturnaddress
        #. llvm.frameaddress
        #. llvm.localescape和llvm.localrecover
        #. llvm.read_register和llvm.write_register
        #. llvm.stacksave
        #. llvm.stackrestore
        #. llvm.get.dynamic.area.offset
        #. llvm.prefetch
        #. llvm.pcmarker
        #. llvm.readcyclecounter
        #. llvm.clear_cache
        #. llvm.instrprof.increment
        #. llvm.instrprof.increment.step
        #. llvm.instrprof.value.profile
        #. llvm.thread.pointer
    #. C标准库内嵌
        #. llvm.memcpy
        #. llvm.memmove
        #. llvm.memset.*
        #. llvm.sqrt.*
        #. llvm.powi.*
        #. llvm.sin.*
        #. llvm.cos.*
        #. llvm.pow.*
        #. llvm.exp.*
        #. llvm.exp2.*
        #. llvm.log.*
        #. llvm.log10.*
        #. llvm.log2.*
        #. llvm.fma.*
        #. llvm.fabs.*
        #. llvm.minnum.*
        #. llvm.maxnum.*
        #. llvm.copysign.*
        #. llvm.floor.*
        #. llvm.ceil.*
        #. llvm.trunc.*
        #. llvm.rint.*
        #. llvm.nearbyint.*
        #. llvm.round.*
    #. 位操作内嵌
        #. llvm.bitreverse.*
        #. llvm.bswap.*
        #. llvm.ctpop.*
        #. llvm.ctlz.*
        #. llvm.cttz.*
        #. llvm.fshl.*
        #. llvm.fshr.*
    #. 带溢出的数学指令内嵌
        #. llvm.sadd.with.overflow.*
        #. llvm.uadd.with.overflow.*
        #. llvm.ssub.with.overflow.*
        #. llvm.usub.with.overflow.*
        #. llvm.smul.with.overflow.*
        #. llvm.umul.with.overflow.*
    #. 特定数学内嵌
        #. llvm.canonicalize.*
        #. llvm.fmuladd.*
    #. 试验性的向量递归内嵌
        #. llvm.experimental.vector.reduce.add.*
        #. llvm.experimental.vector.reduce.fadd.*
        #. llvm.experimental.vector.reduce.mul.*
        #. llvm.experimental.vector.reduce.fmul.*
        #. llvm.experimental.vector.reduce.and.*
        #. llvm.experimental.vector.reduce.or.*
        #. llvm.experimental.vector.reduce.xor.*
        #. llvm.experimental.vector.reduce.smax.*
        #. llvm.experimental.vector.reduce.smin.*
        #. llvm.experimental.vector.reduce.umin.*
        #. llvm.experimental.vector.reduce.fmax.*
        #. llvm.experimental.vector.reduce.fmin.*
    #. 半精度浮点数内嵌
        #. llvm.convert.to.fp16
        #. llvm.convert.from.fp16
    #. 调试器内嵌
    #. 例外处理内嵌
    #. 蹦床内嵌
        #. llvm.init.trampoline
        #. llvm.adjust.trampoline
    #. 装饰向量收集和分散内嵌
        #. llvm.masked.gather.*
        #. llvm.masked.scatter.*
    #. 装饰向量展开加载和压缩存储内嵌
        #. llvm.masked.expandload.*
        #. llvm.masked.compressstore.*
    #. 内存使用标记器
        #. llvm.lifetime.start
        #. llvm.lifetime.end
        #. llvm.invarient.start
        #. llvm.invarient.end
        #. llvm.launder.invarient.group
        #. llvm.strip.invarient.group
    #. 受限浮点内嵌
        #. llvm.experimental.constrained.fadd
        #. llvm.experimental.constrained.fsub
        #. llvm.experimental.constrained.fmul
        #. llvm.experimental.constrained.fdiv
        #. llvm.experimental.constrained.frem
        #. llvm.experimental.constrained.fma
        #. llvm.experimental.constrained.sqrt
        #. llvm.experimental.constrained.pow
        #. llvm.experimental.constrained.powi
        #. llvm.experimental.constrained.sin
        #. llvm.experimental.constrained.cos
        #. llvm.experimental.constrained.exp
        #. llvm.experimental.constrained.exp2
        #. llvm.experimental.constrained.log
        #. llvm.experimental.constrained.log10
        #. llvm.experimental.constrained.log2
        #. llvm.experimental.constrained.rint
        #. llvm.experimental.constrained.nearbyint
    #. 通用内嵌
        #. llvm.var.annotation
        #. llvm.var.annotation.*
        #. llvm.annotation.*
        #. llvm.codeview.annotation
        #. llvm.trap
        #. llvm.debugtrap
        #. llvm.stackprotector
        #. llvm.stackguard
        #. llvm.objectsize
        #. llvm.expect
        #. llvm.assume
        #. llvm.ssa_copy
        #. llvm.type.test
        #. llvm.type.checked.load
        #. llvm.donothing
        #. llvm.experimental.deoptimize
        #. llvm.experimental.guard
        #. llvm.load.relative
        #. llvm.sideeffect
    #. 栈映射内嵌
    #. 元素宽度原子内存内嵌
        #. llvm.memcpy.element.unordered.atomic
        #. llvm.memmove.element.unordered.atomic
        #. llvm.memset.element.unordered.atomic


概述
----------
