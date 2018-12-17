import os

from .lexer import Lexer
from .parse.sdt import SDT

gram_filename = os.path.dirname(
    os.path.abspath(__file__)) + '/gram/ansic.grammar'
lex_filename = os.path.dirname(os.path.abspath(__file__)) + '/gram/ansic.lexeme'


class Parser:
    def __init__(self, lexfp=lex_filename, gramfp=gram_filename):
        self.lexer = Lexer(lexfp)
        self.sdt = SDT.from_gram(gramfp)
        self.tokenize = self.lexer.tokenize
        self.parse_token = self.sdt.parse

    def parse_stream(self, stream):
        token_stream = self.tokenize(stream)
        translation, env = self.parse_token(token_stream)
        return translation, env
