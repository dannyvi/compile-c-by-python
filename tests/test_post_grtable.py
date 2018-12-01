import os
import time
import grtable
from compost.parse.loader import load_grammar
from compost.parse.atoms import NTerm, Term, Value

gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/ansic.grammar'

lex_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/ansic.lexeme'

def test_nterms():
    print("test productions\n\n")
    grammar, all_symbols, env = load_grammar(gram_filename)
    grtable.init_class(NTerm, Term, Value)
    i = grtable.init_symbols(all_symbols)
    length = len(grammar)
    _grammar = list(map(lambda x: [x.head] + list(x.body), grammar))
    grtable.init_grammar(length)
    grtable.build_grammar(_grammar)
    grtable._tests()

