from compost.parser import Parser
from compost.generator import LLVMCodeGenerator
import os
import pytest
import llvmlite.ir as ir

gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compost/gram/a.grammar'


def test_expression():
    parser = Parser()

    print("\nparsing ---------- '\n")
    stream = 'int main (int a) { 3 + 1 }'
    ast, symbol_table = parser.parse_stream(stream)
    generator = LLVMCodeGenerator()
    generator.generate_code(ast)
    print(str(generator.module))
    ir.LiteralStructType()