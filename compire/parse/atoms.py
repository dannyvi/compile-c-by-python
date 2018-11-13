import collections
import itertools
import re


class Symbol:
    def __init__(self, symbol):
        self.symbol = symbol

    def __repr__(self):
        return self.__str__()

    def __format__(self, format_spec):
        return format(self.__str__(), format_spec)

    def __eq__(self, other):
        return self.symbol == other.symbol and type(self) == type(other)

    def __len__(self):
        return len(self.__str__())

    def __hash__(self):
        return hash(self.__str__())


class NTerm(Symbol):
    def __init__(self, symbol, nullable=False):
        self.symbol = symbol
        self.nullable = nullable

    def __str__(self):
        if self.nullable:
            return f"¡{self.symbol}¡"
        else:
            return f"⋮{self.symbol}⋮"

    def nulloff(self):
        self.nullable = False
        return self


class Term(Symbol):
    def __str__(self):
        return f"∶{self.symbol}∶"


class Value(Symbol):
    def __str__(self):
        return f"⋅{self.symbol}⋅"


class Null(Symbol):
    def __init__(self, symbol="ε"):
        super(Null, self).__init__(symbol)

    def __str__(self):
        return f"ε"


class Code(NTerm):
    def __init__(self, symbol, source):
        # n = len(code_obj_list)
        # symbol = f"Cd{n}"
        # code_obj_list.append(symbol)
        super(Code, self).__init__(symbol, nullable=True)
        t = re.sub(r"[\t ]+", " ", source)
        t2 = re.sub(r", ?\n", ",", t)
        self.source = re.sub(r";?\s*\n+\s*", ";", t2)

    def __str__(self):
        # return f"♮{self.source}♮"
        return f"♮{self.symbol}♮"


class Production:
    def __init__(self, ptuple):
        self.production = ptuple

    @property
    def head(self):
        return self.production[0]

    @property
    def body(self):
        return self.production[1:]

    @classmethod
    def cons(cls, head, body):
        return cls((head,)+body)

    def __iter__(self):
        return iter(self.production)

    def __eq__(self, other):
        return self.production == other.production

    def __str__(self):
        g = ' '.join(["{}"] * len(self.body))
        s = g.format(*self.body)
        return f"<{self.head} -> {s}>"

    def __repr__(self):
        return self.__str__()

    def __hash__(self):
        return hash(self.__str__())

    def remove_null(self):
        body_full = map(lambda x: (NTerm(x.symbol), None) if
                        isinstance(x, NTerm) and
                        not isinstance(x, Code) and
                        x.nullable else (x, ),
                        self.body)
        body = itertools.product(*body_full)
        productions = []
        for i in body:
            b = tuple(filter(None, i))
            if b:
                if isinstance(self.head, Code):
                    p = Production.cons(self.head, b)
                else:
                    p = Production.cons(NTerm(self.head.symbol), b)
                productions.append(p)
        return productions

    def is_null(self):
        return self.body == (Null(),)