CHANGES
========

C扩展完成First   12-1-19
--------------------------------------------

Code变量字符串引用替换在loader进行完成   11-09-18
------------------------------------------------------------------

更改Production的基本构成。          11-09-18
----------------------------------------------------------------------

Production不需要Rule。


在语法分析表添加了空产生式的分析和规约 11-08-18
---------------------------------------------------------------
需要继续做规约时翻译。



插入代码之后的语法表规则          11-08-18
---------------------------------------------------------------

之前：

1.

代码块语法表：

- 每个代码块C创建为唯一非终结符，并导出产生式 C\ :sub:`x`\  -> ε

优化产生式分离的算法         11-08-18
--------------------------------------

1. 将中缀表达式替换为前缀表达式 :== head body
2. 每一行为一个产生式。
3. 第一个符号为 ``head`` ， 其他为 ``body`` 。

loader 消除空产生式          11-07-18
---------------------------------------

接受空产生式在语法规则的末尾， loader 可以识别，并在化简的时候将所有的空产生式消除掉。

parser 初始化 的几种选择
---------------------------------
#. 加载一个tokenizer::

    def __init__(gramfile, lexfile):
        self.grammar, self.symbols, self.namespace = load_grammar(gramfile)
        self.syn_table = gen_syntax_table(self.grammar, self.symbols)
        self.tokenize = tokenize(file?, load_lex(lexfile))

   Lexer 必须要加载 ``lex_file`` 才能 ``tokenize(stream)``

   同样， ``SDT`` 必须要加载 ``grammar_file`` 才能 ``parse``


parser 拆分为几个组件
---------------------------------

parser 由 基本元素，加载，语法表，和 翻译方案组成，对语法文件和源代码进行操作。
拆分为4个组件。

Grammar changes
-----------------

**添加grammar的 或 | 规则， 添加 空产生式的规则** ::

    pattern = r'(?s)(?P<NTerm>\w+)\s+:==\s*(?P<Body>.+?)[\s\n]*{{(?P<Def>.+?)}}'



样式:
``product :== body {{rule}}``

将变成 :
``product :== body {{rule}} | body {{rule}} | body {{rule}} | ...``

所以，pattern 的解析规则将拆解为几个步骤：

1.  分开头部 ``head`` 和体 ``units`` 。

    这个是对的::
        
        pattern = r'(?s)(?P<NTerm>\w+)\s*:==\s*(?P<Units>.+?}})\s*?(?:$|(?:\n\s*(?:(?=\w)|(?P<Epsilon>\|)\s*?\n)))'
        
    空产生式::
    
        pattern = r'(?s)(?P<NTerm>\w+)\s*:==\s*(?P<Units>.+?}}\s*?\n\s*(?:(?=\w)|(?:\|\s*?\n)))'
        
    分开::
    
        stmts      :== stmt                                 {{stmts2}}
        stmt       :== "if" "(" "C" ")"
                    "S1" "else"
                    "stmts"
                                           {{stmt1}} | "if" "("
                                           "C" ")" {{stmt3}}
        stmt       :== declare                              {{stmt2}}
                    | dec2          {{sss}}
                    |
        declare    :== type ID ";"                          {{declare}}
                    | ddd {{sp}}
        type       :== base                                 {{type1}}  
    

    以 ``}}\s*?\n\s*(?=\w)`` , ``}}`` 在行尾，空格和换行符。
     
2.  将 ``units`` 分成几个 ``unit`` 。
3.  将 ``unit`` 分成 ``body`` 和 ``rule`` 。
4.  用 ``head`` 跟每一个 ``body`` 和 ``rule`` 构建产生式列表 ``grammar element`` 。