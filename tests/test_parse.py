from compire.parse.loader import load_grammar
from compire.parse.table import closure_collection, gen_syntax_table
from compire.parse.sdt import SDT
from compire.lexer import Lexer
import os

lexer = Lexer()

gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compire/gram/a.grammar'


def test_start():
    deps = '-' * 50
    print("\n{}Parse{}".format(deps, deps))


def test_productions():
    print("test productions\n\n")
    a = load_grammar(gram_filename)
    grammar, all_symbols, env = a
    for i in grammar:
        body = ('{} '*len(i.body)).format(*i.body)
        print(f"{i.head} -> {body}  ---{i.rule.__name__}---")
    g = closure_collection(grammar, all_symbols)
    print(g)


def test_grammars():
    print("\n")
    a = load_grammar(gram_filename)
    grammar, all_symbols, env = a
    _state_map = gen_syntax_table(grammar, all_symbols)
    args = ''.join(list(map(lambda x: '{:'+str(max(5, len(x.__str__())+2))+'s}',
                            all_symbols)))
    s = "{:10s}" + args
    head = ['state', ] + list(all_symbols)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))


def test_if_else():
    print("\n")
    token_stream = lexer.tokenize('if (C) S1 else stmts')
    sdt = SDT.from_gram(gram_filename)
    sdt.parse(token_stream)
    print(sdt.translation)


def test_declaration():
    print("\n")
    token_stream = lexer.tokenize('int a; int b; float c;')
    sdt = SDT.from_gram(gram_filename)
    sdt.parse(token_stream)
    #print(namespace['symbol_table'])
    #assert namespace['symbol_table']