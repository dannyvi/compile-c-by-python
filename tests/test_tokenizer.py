from tokenizer import Token, load_lex, tokenizer


def test_start():
    print("\n----------Tokenizer------------------------------------------")


def test_Token():
    t = Token('a', 'b', 0, 5)
    print(t)


def test_load_lex():
    f = load_lex()
    print(f)


def test_tokenizer():
    token_stream = list(tokenizer('if (C) S1 else stmts'))
    print(token_stream)
