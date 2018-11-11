from compire.lexer import Token, load_lex, Lexer


def test_start():
    print("\n----------Tokenizer------------------------------------------")


def test_Token():
    t = Token('a', 'b', 0, 5)
    print(t)


def test_load_lex():
    f = load_lex("compire/gram/a.lexeme")
    print(f)


def test_tokenizer():
    lexer = Lexer()
    token_stream = list(lexer.tokenize('if ( 2 < 3 ) S1 else stmts'))
    print(token_stream)
