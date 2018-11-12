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
    #translation = parser.parse_stream('if (2<9) S2 else stmts')
    #print(translation[0])
    print('parsing -----if (2<9) S2 else stmts------- \n')
    translation = parser.parse_stream('if (2<9) S2 else stmts')
    print(translation[0])

    print('parsing -----if (2<9) S2 ------- ')
    translation = parser.parse_stream('if (2<9) S2 ')
    print(translation[0])

    print('parsing -----if (2<9) S2 else if (2<3) stmts else S1 ------- \n')
    translation = parser.parse_stream('if (2<9) S2 else if (2<3) stmts else S1')
    print(translation[0])

    print('parsing -----if (2<9) S2 else if (2<3) stmts ------- \n')
    translation = parser.parse_stream('if (2<9) S2 else if (2<3) stmts')
    print(translation[0])


def test_declaration():
    print("\nparsing ---------- int a; int b; float c;\n")
    parser = Parser()
    translation, env = parser.parse_stream('int a; int b; float c;')
    print(translation, env['symbol_table'])
    print("\nparsing ---------- int[4][3] a;\n")
    parser = Parser()
    translation, env = parser.parse_stream('int[4][3] a;')
    print(translation, env['symbol_table'])
    #print("\nrecord int[4][3] a;\n")
    # translation = parser.parse_stream('record { int[4][3] a; int k; float g;} s;')
    # print(translation[0])
