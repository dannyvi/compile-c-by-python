"""Tokenizer.

Could parse:

::

    etc

"""

import re
import collections

Token = collections.namedtuple('Token', ['typ', 'value', 'line', 'column'])

def tokenizer(code):
    keywords = {'if', 'else'}
    token_specification = [
        ('NUMBER',  r'\d+(\.\d*)?'),  # Integer or decimal number
        ('ASSIGN',  r'='),           # Assignment operator
        # (';',     r';'),            # Statement terminator
        ('NODE', r'S1|S2|C'),
        ('ID',      r'[A-Za-z]+'),    # Identifiers
        ('DELIMITER',      r'[(),;]'),      # DELIMITER
        ('NEWLINE', r'\n'),           # Line endings
        ('SKIP',    r'[ \t]+'),       # Skip over spaces and tabs
        ('MISMATCH',r'.'),            # Any other character
    ]
    tok_regex = '|'.join('(?P<%s>%s)' % pair for pair in token_specification)
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

