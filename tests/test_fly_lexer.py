from compfly.lexer import Token, load_lex, Lexer
import pytest


def test_start():
    print("\n----------Tokenizer------------------------------------------")


def test_Token():
    t = Token('a', 'b', 0, 5)
    print(t)


def test_load_lex():
    f = load_lex("compfly/gram/a.lexeme")
    print(f)


def test_tokenizer():
    lexer = Lexer()
    token_stream = list(lexer.tokenize('if ( 2 < 3 ) S1 else stmts'))
    print(token_stream)
    token_stream = list(lexer.tokenize('if ( 2 < 3 ) S1 \n else \n stmts'))
    print(token_stream)
    with pytest.raises(RuntimeError):
        token_stream = list(lexer.tokenize('if ( 2 < 3 ) 11a S1 \n else \n stmts'))
