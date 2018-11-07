from compire.parser import Parser
import os


gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compire/gram/a.grammar'


def test_start():
    deps = '-' * 50
    print("\n{}Front End{}".format(deps, deps))


def test_if_else():
    print("\n")
    parser = Parser()
    translation = parser.parse_stream('if (C) S1 else stmts')
    print(translation[0])


def test_declaration():
    print("\n")
    parser = Parser()
    translation = parser.parse_stream('int a; int b; float c;')
    print(translation[0])
