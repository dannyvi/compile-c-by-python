import os

from compost.parse.loader import load_grammar
from compost.parse.table import *

gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/a.grammar'

lex_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/ansic.lexeme'


# def test_nterms():
#    print("test productions\n\n")
#    grammar, all_symbols, env = load_grammar(gram_filename)
#    grtable.init_class(NTerm, Term, Value)
#    i = grtable.init_symbols(all_symbols)
#    length = len(grammar)
#    _grammar = list(map(lambda x: [x.head] + list(x.body), grammar))
#    _grammar[0].pop()
#    grtable.init_grammar(length)
#    grtable.build_grammar(_grammar)
#    # grtable._tests()
#    _state_map = grtable.gen_syntax_table()
#    # print(_state_map)
#    s = "{:5s}" + ''.join(map(lambda x: '{:5s}', all_symbols))
#    head = ['state', ] + list(all_symbols)
#    print(s.format(*head))
#    for j, i in enumerate(_state_map):
#        _state = [str(j), ] + i
#        print(s.format(*_state))


def test_grammars():
    print("\n")
    a = load_grammar(gram_filename)
    grammar, syms, env = a
    _state_map = gen_syntax_table(grammar, syms)
    s = "{:5s}" + ''.join(map(lambda x: '{:5s}', syms))
    head = ['state', ] + list(syms)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))

#def test_nterms():
#    print("test productions\n\n")
#    grammar, all_symbols, env = load_grammar(gram_filename)
#    _state_map = grtable.gen_syntax_table()
#    s = "{:5s}" + ''.join(map(lambda x: '{:5s}', all_symbols))
#    head = ['state', ] + list(all_symbols)
#    print(s.format(*head))
#    for j, i in enumerate(_state_map):
#        _state = [str(j), ] + i
#        print(s.format(*_state))
