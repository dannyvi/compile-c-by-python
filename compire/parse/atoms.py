import collections
import itertools

# code_obj_list = []

class Symbol:
    def __init__(self, symbol):
        self.symbol = symbol

    def __repr__(self):
        return self.__str__()

    def __format__(self, format_spec):
        return format(self.__str__(), format_spec)

    def __eq__(self, other):
        return self.symbol == other.symbol and type(self) == type(other)

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
    def __init__(self, symbol, code):
        # n = len(code_obj_list)
        # symbol = f"Cd{n}"
        # code_obj_list.append(symbol)
        super(Code, self).__init__(symbol, nullable=True)
        self.code = code

    def __str__(self):
        return f"♮{self.symbol}♮"


class Production:
    def __init__(self, head, body, rule):
        self.head, self.body, self.rule = head, body, rule

    def __iter__(self):
        return iter((self.head, self.body, self.rule))

    def __eq__(self, other):
        return self.head == other.head and self.body == other.body

    def __str__(self):
        g = "{} " * len(self.body)
        s = g.format(*self.body)
        return f"<{self.head} -> {s} {self.rule.__name__}(...)>"

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
                    p = Production(self.head, b, self.rule)
                else:
                    p = Production(NTerm(self.head.symbol), b, self.rule)
                productions.append(p)
        return productions
