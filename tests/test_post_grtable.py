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
    # print(all_symbols)
    #grtable._tests()
    i = grtable.init_symbols(NTerm, Term, Value, all_symbols)
    length = len(grammar)
    _grammar = list(map(lambda x: [x.head] + list(x.body), grammar))
    grtable.init_grammar(length)
    grtable.build_grammar(NTerm, Term, Value, _grammar)

#                            NTerm,
#                          Term,
#                          Value,
#                          [[NTerm("cast-expression"),
#                            Term("INTEGER_CONSTANT"),
#                            Value(",")],
#                           [NTerm("shift-expression"),
#                            Term("ASSIGN_OP"),
#                            NTerm("initializer-list"),
#                            Value(")")]])
#
    #print(i)

