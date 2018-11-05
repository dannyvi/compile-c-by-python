from compire.parse.loader import load_grammar
from compire.parse.table import closure_groups, gen_syntax_table
from compire.parse.sdt import SDT
from compire.tokenizer import tokenizer
import os


gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compire/gram/nullable.grammar'


def test_start():
    deps = '-' * 50
    print("\n{}Nullable declarations{}".format(deps, deps))


def test_productions():
    print("test productions\n\n")
    a = load_grammar(gram_filename)
    grammar, all_symbols = a
    print(grammar)
    g = closure_groups(grammar, all_symbols)
    print(g)


def test_grammars():
    print("\n")
    a = load_grammar(gram_filename)
    grammar, all_symbols = a
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
    sdt = SDT.from_gram(gram_filename)
    t = tokenizer("int[5] a;")
    print(list(t))

    token_stream = tokenizer("int[5] a;")

    sdt.parse(token_stream)
