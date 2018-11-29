import os
from compost.parse.atoms import *
from compost.parse.loader import load_grammar
from compost.parse.table import closure_collection, gen_syntax_table
from compost.parse.sdt import SDT
from compost.lexer import Lexer
import time
#from compost.parser import Parser


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

def test_productions():
    print("test productions\n\n")
    t = time.time()
    a = load_grammar(gram_filename)
    grammar, all_symbols, env = a
    g = closure_collection(grammar, all_symbols)
    #for num in range(len(g)):
    #    clos = [i for i in g if i.label == num][0]
    #    print(clos.label, len(clos))
    num = len(g)
    print(num)
    for n, i in enumerate(grammar):
        body = i.body #('{} \n'*len(i.body)).format(*i.body)
        # if isinstance()
        print(f"{n} {i.head} -> {body} ")
    now = time.time() - t
    print(now)


def test_grammars():
    print("\n")
    t = time.time()
    a = load_grammar(gram_filename)
    grammar, syms, env = a
    _state_map = gen_syntax_table(grammar, syms)
    s = "{:6s}" + ''.join(map(lambda x: '{:'+str(max(4, len(x)))+'s}', syms))
    head = ['state', ] + list(syms)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))
    now = time.time() - t
    print(now)

#def test_expression():
#    parser = Parser(lex_filename, gram_filename)