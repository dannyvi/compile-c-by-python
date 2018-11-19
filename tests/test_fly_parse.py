from compfly.parse.loader import load_grammar
from compfly.parse.table import closure_collection, gen_syntax_table
from compfly.parse.sdt import SDT
from compfly.lexer import Lexer
from compfly.parse import Code
import os
import pytest

lexer = Lexer()

gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compfly/gram/a.grammar'


def test_start():
    deps = '-' * 50
    print("\n{}Parse{}".format(deps, deps))


def test_productions():
    print("test productions\n\n")
    a = load_grammar(gram_filename)
    grammar, all_symbols, env = a
    g = closure_collection(grammar, all_symbols)
    for num in range(len(g)):
        clos = [i for i in g if i.label == num][0]
        print(clos.__repr__())
    for n, i in enumerate(grammar):
        body = ('{} '*len(i.body)).format(*i.body)
        # if isinstance()
        print(f"{n} {i.head} -> {body} {i.head.source if isinstance(i.head, Code) else ''}")


def test_grammars():
    print("\n")
    a = load_grammar(gram_filename)
    grammar, syms, env = a
    _state_map = gen_syntax_table(grammar, syms)
    s = "{:6s}" + ''.join(map(lambda x: '{:'+str(max(4, len(x)))+'s}', syms))
    head = ['state', ] + list(syms)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))


def test_error():
    print(f"testing-error{'.'*60}\n")
    token_stream = lexer.tokenize('if (2 < 3 S1 else S2 int a; \n int b;')
    sdt = SDT.from_gram(gram_filename)
    with pytest.raises(SyntaxError):
        t, e = sdt.parse(token_stream)


def test_if_else():
    print(f"testing-if-else{'.'*60}\n")
    token_stream = lexer.tokenize('if (2 < 3) S1 else S2 int a; int b;')
    sdt = SDT.from_gram(gram_filename)
    t, e = sdt.parse(token_stream)
    print("translations\n")
    print(t)


def test_declaration():
    print("\n")
    token_stream = lexer.tokenize('int a; int b; float c; if (2 < 3) S1 else S2 ')
    sdt = SDT.from_gram(gram_filename)
    t,e = sdt.parse(token_stream)
    print(t)

