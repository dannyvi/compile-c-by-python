import os

from compfly.parse.loader import load_grammar
from compfly.parse.table import closure_collection, gen_syntax_table
from compfly.parser import Parser

gram_filename = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                             'nullable.grammar')


def test_start():
    deps = '-' * 50
    print("\n{}Nullable declarations{}".format(deps, deps))


def test_productions():
    print("test productions\n\n")
    a = load_grammar(gram_filename)
    grammar, all_symbols, env = a
    for n, i in enumerate(grammar):
        body = ('{} '*len(i.body)).format(*i.body)
        print(f"{n} {i.head} -> {body}")


def test_grammars():
    print("\n")
    a = load_grammar(gram_filename)
    grammar, all_symbols, env = a
    # print(all_symbols)
    g = closure_collection(grammar, all_symbols)
    for num in range(len(g)):
        clos = [i for i in g if i.label == num][0]
        print(clos.__repr__())
    _state_map = gen_syntax_table(grammar, all_symbols)
    args = ''.join(list(map(lambda x: '{:'+str(max(5, len(x.__str__())+2))+'s}',
                            all_symbols)))
    s = "{:10s}" + args
    head = ['state', ] + list(all_symbols)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))


def test_reduction():
    print("\n")
    parser = Parser(gramfp=gram_filename)
    t = parser.tokenize("int[5] a;")
    print(list(t))
    translation, symbol_table = parser.parse_stream('int[5] a;')
    print(symbol_table)
    translation, symbol_table = parser.parse_stream('int[5][3] a;')
    print(symbol_table)
    translation, symbol_table = parser.parse_stream('s[5][3]')
    print(symbol_table)
