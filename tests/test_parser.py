from compire.parser import *
from compire.tokenizer import tokenizer


def test_start():
    deps = '-' * 50
    print("\n{}Parser{}".format(deps, deps))


def test_grammar_table():
    _state_map = generate_syntax_table()
    args = ''.join(list(map(lambda x: '{:'+str(max(5, len(x.__str__())+2))+'s}',
                            all_symbols)))
    s = "{:10s}" + args
    head = ['state', ] + list(all_symbols)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))


def test_if_else():
    token_stream = tokenizer('if (C) S1 else stmts')
    sdt = SDT()
    sdt.parse(token_stream)
    print(sdt.translation)
    assert sdt.translation


def test_declaration():
    token_stream = tokenizer('int a; int b; float c;')
    sdt = SDT()
    sdt.parse(token_stream)
    print(namespace['symbol_table'])
    assert namespace['symbol_table']