from compire.lexer import Token
from .atoms import Term, Value, Null, Code
from .loader import load_grammar
from .table import gen_syntax_table


class State:
    def __init__(self, index, **properties):
        self.__dict__ = properties
        self.index = index

    def __str__(self):
        return f"‸{self.index}‸"

    def __repr__(self):
        return self.__str__()


class SDT:
    def __init__(self):
        self.syn_table = []
        self.grammar = None
        self.symbols = None
        self.stack = [State(0)]
        self.accept = False
        self.translation = ''
        self.env = {}

    def clear(self):
        self.stack = [State(0)]
        self.accept = False
        self.translation = ''

    def load_grammar(self, gram_filename):
        self.grammar, self.symbols, self.env = load_grammar(gram_filename)
        self.env.update({"Stack": self.stack})
        self.syn_table = gen_syntax_table(self.grammar, self.symbols)

    @classmethod
    def from_gram(cls, gram_filename):
        instance = cls()
        instance.load_grammar(gram_filename)
        return instance

    def get_action(self, stt, t):
        if isinstance(t, Token):
            try:
                a = self.syn_table[stt.index][self.symbols.index(Value(t.val))]
                return a
            except ValueError:
                a = self.syn_table[stt.index][self.symbols.index(Term(t.typ))]
                return a
        # t is a none_terminal NTerm instance
        else:
            return self.syn_table[stt.index][self.symbols.index(t)]

    def ahead(self, token):
        action = self.get_action(self.stack[-1], token)
        if action[0] == '$':
            self.accept = True   # success
            self.translation = self.env['code']
        # shift action push a current state into stack
        elif action[0] == 's':
            index = int(action[1:])
            self.shift(index, token)
        # reduce action reduct a production and push
        elif action[0] == 'r':
            # get the production in grammar
            number = int(action[1:])
            self.reduce(number, token)

            # reduce actions does not consume a token,
            # only when shifting, a token was consume and passed
            self.ahead(token)
        else:
            stk = f"state: {self.stack[-1]}\n"
            tk = f"token: {token.__str__()}\n"
            act = f"action: {action}\n"
            msg = f"{stk}{tk}{act}"
            raise SyntaxError(f"\nError: {msg}")

    def parse(self, token_stream):
        for t in token_stream:
            self.ahead(t)
        self.ahead(Token("$", "$", 0, 0))
        if self.accept:
            translation = self.translation
            self.clear()
            return translation, self.env

    def shift(self, index, token):
        state = State(index, **token.__dict__)
        self.stack.append(state)

    def reduce(self, number, token):
        production = self.grammar[number]

        head, body = production.head, production.body
        loc = {}
        if production.is_null():
            try:
                c = compile(head.source, "<string>", "exec")
            except SyntaxError as e:
                raise SyntaxError(f"{e.msg}\n{head.source}\n{token.__str__()}")
            self.env.update({"Stack": self.stack})
            stack = self.stack
            try:
                exec(c, self.env, loc)
            except AttributeError as a:
                raise AttributeError(a, head.source, stack[-1].__dict__, token)
        # pop the states of production body
        else:
            if isinstance(body[-1], Code):
                loc = self.stack[-1].__dict__.copy()
                loc.pop('index')
            else:
                loc = self.stack[-len(body)].__dict__.copy()
                loc.pop('index')
            for _ in body:
                self.stack.pop()
        # push the state of head GOTO(I,X)
        index = int(self.get_action(self.stack[-1], head))
        state = State(index, **loc)
        self.stack.append(state)
