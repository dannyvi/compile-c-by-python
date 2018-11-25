#from compost.parser import Parser
#from compost.generator import LLVMCodeGenerator
from compost.evaluator import Evaluator
import os
import pytest


def test_expression():

    print("\nparsing ---------- '\n")
    stream = 'int add11 (int a) { a + 3 }'
    ev = Evaluator()
    print(ev.evaluate(stream, optimize=True, llvmdump=True))
    print(ev.evaluate('int suba (int b) { 4 + 2}', llvmdump=True))
    print(f"""Evaluate add11(3) {ev.evaluate('add11(3)')}""")
    #ast, symbol_table = parser.parse_stream(stream)
    #generator = LLVMCodeGenerator()
    #generator.generate_code(ast)
    #print(str(generator.module))