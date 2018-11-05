import collections

Production = collections.namedtuple("Production", ["head", "body", "rule"])

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
        return f"<{self.symbol}>"


class Term(Symbol):
    def __str__(self):
        return f"[{self.symbol}]"


class Value(Symbol):
    def __str__(self):
        return f"⋅{self.symbol}⋅"


class Null(Symbol):
    def __init__(self, symbol=None):
        super(Null, self).__init__(symbol)
    def __str__(self):
        return f"ε"
