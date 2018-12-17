import os
import time

from compost.parse.atoms import *
from compost.parse.loader import load_grammar
from compost.parse.table import gen_syntax_table

gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/ansic.grammar'

lex_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/ansic.lexeme'

def test_nterms():
    print("test productions\n\n")
    t = time.time()
    a = load_grammar(gram_filename)
    grammar, all_symbols, env = a
    print(all_symbols)
    print(len(all_symbols))
    print(len(list(filter(lambda x: isinstance(x, NTerm), all_symbols))))
    print(len(list(filter(lambda x: isinstance(x, Term), all_symbols))))
    print(len(list(filter(lambda x: isinstance(x, Value), all_symbols))))


def test_grammars():
    print("\n")
    t = time.time()
    a = load_grammar(gram_filename)
    grammar, syms, env = a
    _state_map = gen_syntax_table(grammar, syms)
    s = "{:6s}" + ''.join(map(lambda x: '{:5s}', syms))
    head = ['state', ] + list(syms)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))
    now = time.time() - t
    print(now)
