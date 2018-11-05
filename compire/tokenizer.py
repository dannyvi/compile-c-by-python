"""Tokenizer.

Could parse:

::

    etc

"""

import re
import collections
import os


lex_filename = os.path.dirname(os.path.abspath(__file__)) + '/gram/a.lexeme'


class Token:
    def __init__(self, typ, value, line, column):
        self.typ = typ
        self.value = value
        self.line = line
        self.column = column

    def __str__(self):
        l,m,n,o = [self.typ, self.value, self.line, self.column]
        return f'<Token: {l} {m} {n}:{o}>'

    def __repr__(self):
        return self.__str__()


def load_lex(lex_file=lex_filename):

    def strip_comments(code):
        code = str(code)
        return re.sub(r'(?m)^ *#.*\n?', '', code)

    def eval_spec(t):
        return t[0], eval(t[1])

    with open(lex_file, 'r') as f:
        line = [strip_comments(i) for i in f.read().splitlines()
                if strip_comments(i)]
        # print(line)
        tokens = list(map(lambda x: eval_spec(re.split(r"\s*:=\s*", x)), line))
        return tokens


def tokenizer(code, token_specification=load_lex(lex_filename)):
    tok_regex = '|'.join(r'(?P<%s>%s)' % pair for
                         pair in token_specification)
    line_num = 1
    line_start = 0
    for mo in re.finditer(tok_regex, code):
        kind = mo.lastgroup
        value = mo.group(kind)
        if kind == 'NEWLINE':
            line_start = mo.end()
            line_num += 1
        elif kind == 'SKIP':
            pass
        elif kind == 'MISMATCH':
            raise RuntimeError(f'{value!r} unexpected on line {line_num}')
        else:
            if kind == 'NODE':
                kind = value
            column = mo.start() - line_start
            yield Token(kind, value, line_num, column)
