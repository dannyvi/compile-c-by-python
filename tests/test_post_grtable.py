import os

from compost.parse.loader import load_grammar
from compost.parse.table import *

gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/ansic.grammar'

lex_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/ansic.lexeme'

def test_grammars():
    print("\n")
    a = load_grammar(gram_filename)
    grammar, syms, env = a
    _state_map = gen_syntax_table(grammar, syms)
    s = "{:5s}" + ''.join(map(lambda x: '{:5s}', syms))
    head = ['state', ] + list(map(lambda x: x.__str__()[:4], syms))
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))

    print(f"Length:{len(_state_map)}")
