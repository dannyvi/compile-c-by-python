词法器和翻译的联动
=================

需要判断的语素:

    值
    终结符号（词法单元）
    非终结符号
    
采用的机制...

* Value(value)
* Terminal(token)
* None_Terminal(Production_symbol)

包装各个构成元素。

构成Item的元素要变化，所以构建表的模块需要重写。

解析规则
---------

### **词法单元解析** ：

1. 文件名后缀 .lexeme
2. lexer读取解析文件并生成tokenizer。
3. tokenizer 可以解析源文件为词法单元。
4. 解析文件格式：
    * token_name := pattern
    * token_name是词法单元名。
    * pattern 是正则样式。
    * 每一行是一个词法单元类。
    
    ```prod
    NUMBER := r'\d+(\.\d*)?' # comments
 
    # comments and inline comments
    
    # empty lines accepted
    ```
    
5. pattern 在解析时 用 r'pattern'
    
### **语法单元解析** ：

1. 文件名后缀 .gram
2. 文件构成：

    ```
    productions

    --- 
    
    rules
    ```

    productions 是产生式定义区域。

    rules 是规则定义区域， 规则可以在产生式区中引用。

3. 产生式：

    ```
    none_terminal :== none_terminal 
                      terminal "value"  {{rule}}
    ```

4. 产生式的体由三个元素类和一个规则类构成：

    - none_terminal
    - terminal
    - value
    - rule (后缀规则， 由``{{ }}``包裹)

5. 符号解析的过程：
    
    1. 三个类分别是 Nterm, Term, Value。
    2. parser 从语法规则的产生式部分中获取所有的符号。
    3. 产生式的全部头部，是 none_terminal。
    4. 产生式体中的其他未被引号包括的符号，是词法单元，在分析时取token的type。
    5. 产生式体中被引号包括的符号，是词法单元的值，在分析的时候取token的value。

    ```
    p = NTerm("A")
    print(p)
    
    out[]: <A>
 
    t = Term("T")
    print(t)
    
    out[]: (T)
    
    v = Value("v")
    print(v)
    
    out[]: "v"
    ```

6. 规则解析的过程：

    1. 规则由python函数组成，一般是嵌套形式。
        ```python
        def stmt(*body):
           def callback(*args):
               body
               ...
               return value
           return callback
 
        ```
        其中 `stmt` 是语句的名字，在产生式规则区可以引用。 `*body` 是产生式规则体内的参
        数个数。这个函数返回一个回调函数， 这个回调函数是用来放入继承属性的。因为分析器
        是LR(1)规约，所以不能预先判定规约时会用哪一个产生式，就使用回调函数的形式，在非
        终结符被规约时，进行延迟调用。
    2. 装入一个命名空间 `namespace` 里
    
7. 产生式和规则函数组成命名元组`Prod`，装入到grammar列表。