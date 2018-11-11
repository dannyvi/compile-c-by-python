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

    print('parsing -----if (2<9) S2 else if (2<3) stmts ------- \n')
    translation = parser.parse_stream('if (2<9) S2 else if (2<3) stmts')
    print(translation[0])



def test_declaration():
    print("\n")
    parser = Parser()
    translation = parser.parse_stream('int a; int b; float c;')
    print(translation[0])
    translation = parser.parse_stream('int[4][3] a;')
    print(translation[0])
