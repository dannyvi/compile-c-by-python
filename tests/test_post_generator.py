from compost.parser import Parser
from compost.generator import LLVMCodeGenerator
import os
import pytest


gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compfly/gram/a.grammar'


def test_expression():
    parser = Parser()

    print("\nparsing ---------- '\n")
    stream = '2 + 3'
    ast, symbol_table = parser.parse_stream(stream)
    generator = LLVMCodeGenerator()
    generator.generate_code(ast)
    print(str(self.generator.module))