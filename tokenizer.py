"""Tokenizer.

Could parse:

::

    etc

"""

import re
import collections

Token = collections.namedtuple('Token', ['typ', 'value', 'line', 'column'])


def load_lex(lex_file):

    def strip_comments(code):
        code = str(code)
        return re.sub(r'(?m)^ *#.*\n?', '', code)

    def eval_spec(t):
        return t[0], eval(t[1])

    with open(lex_file, 'r') as f:
        line = [strip_comments(i) for i in f.read().splitlines()
                if strip_comments(i)]
        token_spec = list(map(lambda x: eval_spec(re.split("\s*:=\s*", x)),
                              line))
        return token_spec


def tokenizer(code, token_specification=load_lex('a.lexeme')):
    keywords = {'if', 'else'}
    tok_regex = '|'.join('(?P<%s>%s)' % pair for
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
            if kind == 'ID' and value in keywords:
                kind = value
            if kind == 'NODE':
                kind = value
            column = mo.start() - line_start
            yield Token(kind, value, line_num, column)
