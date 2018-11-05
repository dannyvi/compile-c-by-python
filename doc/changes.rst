CHANGES
========

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