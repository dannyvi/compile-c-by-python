from compire.parser import Parser
import os
import pytest


gram_filename = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__))) + '/compire/gram/a.grammar'


def test_start():
    deps = '-' * 50
    print("\n{}Front End{}".format(deps, deps))


def test_if_else():
    print("\n")
    parser = Parser()
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

    print('parsing -----if ...................\n')
    stream = ''' if ( 10 < 9) S2 else if ( 6 < 3 ) S1 else 
                 if (3 < 9) stmts else S2'''
    translation = parser.parse_stream(stream)
    print(translation[0])


def test_declaration():
    print("\nparsing ---------- int a; \n")
    parser = Parser()
    translation, symbol_table = parser.parse_stream('int a; ')
    print(translation, symbol_table)

    print("\nparsing ---------- int a; int b; float c;\n")
    translation, symbol_table = parser.parse_stream('int a; int b; float c;')
    print(translation, symbol_table)

    print("\nparsing ---------- int[3] a;\n")
    translation, symbol_table = parser.parse_stream('int[3] a;')
    print(translation, symbol_table)

    print("\nparsing ---------- int[3][4] a;\n")
    translation, symbol_table = parser.parse_stream('int[3][4] a;')
    print(translation, symbol_table)

    print("\nparsing ---------- int[2][2][2][2] a;\n")
    translation, symbol_table = parser.parse_stream('int[2][2][2][2] a;')
    print(translation, symbol_table)

    print(f"\nparsing {'-'*20} record {{ int[4] a; int k; float g;}} s; int...")
    stream = 'record {int[4] a;int k;float g;} s;int z;float[5] p; int[2][3] c;'
    translation, symbol_table = parser.parse_stream(stream)
    print(translation, symbol_table)

    print("\nparsing ---------- int b; int c; c=8; b = c + 5 + 7; \n")
    stream = 'int b; int c; c=8; b = c + 5 + 7;'
    translation, symbol_table = parser.parse_stream(stream)
    print(translation, symbol_table)

    print("\nparsing ---------- int[5] b; b[1] = 100; int[3][4] '\n")
    stream = 'int[5] b; b[1] = 100; int[3][4] k; k[2][1] = 30;'
    translation, symbol_table = parser.parse_stream(stream)
    print(translation, symbol_table)

    print("\nparsing ----------int[5][4][3][2] a; a[3][2][2][1] = 10;\n")
    stream = 'int[5][4][3][2] a; a[3][2][2][1] = 10;'
    translation, symbol_table = parser.parse_stream(stream)
    print(translation, symbol_table)


def test_expression():
    parser = Parser()

    print("\nparsing ---------- int[3][4] k; k[2][1] = k[1][1]; '\n")
    stream = 'int[3][4] k; k[2][1] = k[1][1];'
    translation, symbol_table = parser.parse_stream(stream)
    print(translation, symbol_table)

    print("\nparsing ---------- int b; int[3][5] k; int[6] m; b = k[2][1] + m[3];'\n")
    stream = 'int b; int[3][5] k; int[6] m; b = k[2][1] + m[3]; '
    translation, symbol_table = parser.parse_stream(stream)
    print(translation, symbol_table)

    print("\nparsing ---------- Error '\n")
    stream = ' int[3][5] k; int[6] m; b = k[2][1] + m[3]; '
    with pytest.raises(KeyError):
        translation, symbol_table = parser.parse_stream(stream)


def test_while():
    parser = Parser()

    print("\nparsing ---------- while ( 2 < 9 ) { int a; a = 2+4; }")
    stream = "while ( 2 < 9 ) { int a; a = 2+4; }"
    translation, symbol_table = parser.parse_stream(stream)
    print(translation, symbol_table)