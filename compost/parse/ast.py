class Node:
    pass


class Expr(Node):
    pass


class Number(Expr):
    def __init__(self, val):
        self.val = val


class Variable(Expr):
    def __init__(self, name):
        self.name = name


class Decl(Expr):
    def __init__(self, typ, name):
        self.typ = typ
        self.name = name


class Binary(Expr):
    def __init__(self, op, lhs, rhs):
        self.op = op
        self.lhs = lhs
        self.rhs = rhs


class Call(Expr):
    def __init__(self, callee, args):
        self.callee = callee
        self.args = args


class Prototype(Node):
    def __init__(self, typ, name, args):
        self.typ = typ
        self.name = name
        self.args = args


class Function(Node):
    def __init__(self, proto, body):
        self.proto = proto
        self.body = body

    _anonymous_function_counter = 0

    @classmethod
    def create_anonymous(cls, typ, expr):
        cls._anonymous_function_counter += 1
        return cls(
            Prototype(typ,
                      '_anon{0}'.format(cls._anonymous_function_counter),
                      []),
            expr
        )

    def is_anonymous(self):
        return self.proto.name.startswith('_anon')
