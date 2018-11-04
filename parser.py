import queue
from typing import Set
from tokenizer import Token
import collections
import re

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



namespace = {}


def load_grammar(grammar_file="a.grammar"):

    n_terminals = []
    terminals = []
    term_values = []
    all_symbols = []
    grammar = []

    def strip_comments(code):
        code = str(code)
        return re.sub(r'(?m)^ *#.*\n?', '', code)

    def separate_productions(code):
        parts = r'(?s)(?P<NTerm>\w+)\s*:==\s*(?P<Units>.+?}})'
        tail  = r'\s*?(?:$|(?:\n\s*(?:(?=\w)|(?P<Epsilon>\|)\s*?\n)))'
        pattern = parts + tail
        productions = re.finditer(pattern, code)
        return list(productions)

    def get_none_terminals(production_list):
        # nonlocal n_terminals
        n_terms = []
        for p in production_list:
            nterm = NTerm(p['NTerm'], bool(p['Epsilon']))
            if nterm not in n_terms:
                n_terms.append(nterm)
            else:
                if nterm.nullable:
                    n_terms[n_terms.index(nterm)] = nterm
        return n_terms

    def grammar_unit_iter(grammar_code):
        # The order of spec is important,
        # or it will mistake taking :== or | as Term
        spec = [r"(?P<Produce>:==)",
                r"(?P<Seperate>\|)",
                r"(?P<Spaces>\s+)",
                r"(?P<quote>[\"'])(?P<Value>\S+)(?P=quote)",
                r"(?P<Term>\w+)",
                r"(?P<Rule>{{\w+}})",
                ]
        pattern = "|".join(spec)
        return re.finditer(pattern, grammar_code)

    def get_terminals_values(grammar_code, n_terms):
        term_values = []
        terminals = []
        for mo in grammar_unit_iter(grammar_code):
            kind = mo.lastgroup
            value = mo.group(kind)
            if kind == "Value":
                v = Value(value)
                if v not in term_values:
                    term_values.append(v)
            elif kind == "Term":
                if NTerm(value) not in n_terms:
                    v = Term(value)
                    if v not in terminals:
                        terminals.append(v)
            else:
                # ignore Produce Seperate Spaces and Rule
                pass
        return terminals, term_values

    def get_production(prod_iter, n_terms, terms, values):
        def get_n_term(value):
            return n_terms[n_terms.index(NTerm(value))]
        # P :== body {{rule}} | ...
        head = prod_iter.group("NTerm")
        units = prod_iter.group("Units")
        # 1. separate production body by '|'
        bodies = re.split(r"\|", units)
        productions = []
        for body in bodies:
            # 2. separate formula and rule
            rule = re.search(r'{{(\w+)}}', body).group(1)
            formula = re.sub(r'\s*{{(\w+)}}', '', body)
            # 3. get every symbol
            spec = [r"(?P<Spaces>\s+)",
                    r"(?P<quote>[\"'])(?P<Value>\S+)(?P=quote)",
                    r"(?P<Term>\w+)"]
            pattern = "|".join(spec)
            form_list = []
            for symbol in re.finditer(pattern, formula):
                kind = symbol.lastgroup
                value = symbol.group(kind)
                if kind == "Value":
                    form_list.append(Value(value))
                elif kind == "Term":
                    if NTerm(value) in n_terms:
                        t = n_terms[n_terms.index(NTerm(value))]
                        form_list.append(t)
                    else:  # Terminal
                        t = Term(value)
                        form_list.append(t)
                # others are omitted
            production = Production(get_n_term(head),
                                    tuple(form_list),
                                    namespace[rule])
            productions.append(production)
        return productions

    with open(grammar_file) as f:
        # 1. seperate file by  ----------------- seperate line
        raw_grammar, definitions = re.split(r"(?m)^[\s-]+[-]+[\s-]+$", f.read())

        # 2. augment syntax
        aug_grammar = 'startsup :== start "$" {{startsup}}\n' + raw_grammar
        aug_definitions = definitions + '\n\ndef startsup(f):\n    return f()'

        # 3. get definition funcs into global namespace
        exec(aug_definitions, namespace)

        # 4. strip comments
        clean_grammar = strip_comments(aug_grammar)

        # 5. get none terminals list
        prods = separate_productions(clean_grammar)
        n_terminals = get_none_terminals(prods)

        # 6. get terminals and terminal values list. And all symbols list
        terminals, term_values = get_terminals_values(clean_grammar, n_terminals)

        all_symbols =  term_values + terminals + n_terminals

        # 7. generate grammar list, contains production rules.
        #    Has to deal or productions and nullable productions.

        for prod in prods:
            p_list = get_production(prod, n_terminals, terminals, term_values)
            grammar.extend(p_list)

        return grammar, terminals, n_terminals, term_values, all_symbols


grammar, terminals, n_terminals, term_values, all_symbols = load_grammar()

# ------------------------------------------------------------------------------

class Item(object):
    """The Canonical LR(1) Item definition.

    :param head: str, the left part of production.
    :param body: str, the right part of production.
    :param dot: int, current position in the item.
    :param follow: str, possible input for the current configuration.
    """

    def __init__(self, head, body, dot, follow):
        self.head = head
        self.body = body
        self.pos = dot
        self.follow = follow

    def __str__(self):
        p = list(map(lambda x: x.__str__(), self.body))
        p.insert(self.pos, '◆')
        pr = ' '.join(p)
        return "[{}]  {} -> {}".format(self.follow, self.head, pr)

    def __repr__(self):
        return "<Item:{} >\n".format(self.__str__())

    def __eq__(self, other):
        if isinstance(other, Item):
            return ((self.head == other.head) and
                    (self.body == other.body) and
                    (self.pos == other.pos) and
                    (self.follow == other.follow))
        else:
            return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        return hash(self.__str__())


class Closure(object):
    def __init__(self, sets: Set[Item], label: int = None):
        self.label = label
        self.sets = sets
        self.goto = dict()  # type: dict[str, int]

    def __len__(self):
        return len(self.sets)

    def __iter__(self):
        return self.sets.__iter__()

    def __str__(self):
        return "\n".join([i.__str__() for i in self.sets])

    def __repr__(self):
        return "<Closure>:{}\n{}\n</Closure>\n".format(self.label,
                                                       self.__str__())

    def __eq__(self, other):
        return self.sets == other.sets

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        return hash(self.__str__())

    def __contains__(self, item):
        return item in self.sets


def isnterm(symbol):
    return symbol in n_terminals


def isterm(symbol):
    return symbol in terminals + term_values


def produce_epsilon(none_terminal):
    return 'EPSILON' in [i.body for i in grammar if i.head == none_terminal]


def first(symbol):
    """Return the first terminal sets that may occur in the Symbol."""
    first_sets = set()
    if isterm(symbol):
        return set([symbol])
    elif produce_epsilon(symbol):
        first_sets = first_sets.union(['EPSILON'])
    elif isnterm(symbol):
        for i in grammar:
            if i.head == symbol:
                # body = i.body
                epsilons = True
                current = 0
                while epsilons is True and current < len(i.body):
                    if i.body[current] != symbol:
                        first_sets = first_sets.union(first(i.body[current]))
                    if not produce_epsilon(i.body[current]):
                        epsilons = False
                    current += 1
    return first_sets


def firsts(suffix):
    if len(suffix) == 1:
        return first(suffix[0])
    else:
        if not produce_epsilon(suffix[0]):
            return first(suffix[0])
        else:
            return first(suffix[0]).union(firsts(suffix[1:]))


def get_closure(cl: Closure, label: int) -> Closure:
    """get all Item of a Closure from given Items, by adding implied Items.

    The implied Items are the productions of the None terminals after the
    current position, which put a dot on the head."""
    def get_body_nterm(item):
        pos, prod = (item.pos, item.body)
        if pos < len(prod):
            symbol = prod[pos]
            if isnterm(symbol):
                return symbol
        return None
    item_set = set()
    q = queue.Queue()
    for i in cl.sets:
        item_set.add(i)
        q.put(i)
    while not q.empty():
        item = q.get()
        symbol = get_body_nterm(item)
        if symbol:
            products = [i for i in grammar if i.head == symbol]
            suffix = item.body[item.pos+1:] + tuple([item.follow])
            termins = firsts(suffix)
            for product in products:
                for terminal in termins:
                    new_item = Item(symbol, product.body, 0, terminal)
                    if new_item not in item_set:
                        item_set.add(new_item)
                        q.put(new_item)
    c = Closure(item_set, label)
    return c


def goto(clos: Closure, tok_type) -> Closure:
    """a closure that could get from the current closure by input a letter.

    :param clos: the current closure.
    :param tok_type: the input letter.
    :return: Closure.
    """
    item_set = set()
    for item in clos.sets:
        dot, prod = (item.pos, item.body)
        if dot < len(prod) and prod[dot] == tok_type and \
                isinstance(prod[dot], type(tok_type)):
            new_item = Item(item.head,
                            item.body,
                            item.pos + 1,
                            item.follow)
            item_set.add(new_item)
    c = Closure(item_set)
    return get_closure(c, label=None)


def closure_groups():
    def find_label(closure, group):
        for i in group:
            if closure == i:
                return i.label
        return None
    group = set()
    label = 0
    start_item = Item(NTerm('startsup'), (NTerm('start'),), 0, Value('$'))
    start = get_closure(Closure({start_item}), label)
    q = queue.Queue()
    q.put(start)
    group.add(start)
    while not q.empty():
        c = q.get()
        for literal in all_symbols: # terminals + n_terminals:
            go_clos = goto(c, literal)
            if go_clos:
                if go_clos not in group:
                    label += 1
                    go_clos.label = label
                    q.put(go_clos)
                    group.add(go_clos)
                    c.goto[literal] = label
                    # print('add closure', go_clos)
                else:
                    go_label = find_label(go_clos, group)
                    if go_label:
                        c.goto[literal] = go_label
    return group


def get_states_map(closure_group):

    def get_prod_number(symbol, body):
        for num, prod in enumerate(grammar):
            if prod.head == symbol and prod.body == body:
                return num

    def get_state_map(closure):
        """ table row like all_symbols list state maps."""
        row = ["." for i in all_symbols]
        # None terminals GOTO action and Terminals shift action.
        for input, goto_label in closure.goto.items():
            row_pos = all_symbols.index(input)
            for item in closure:
                if item.pos < len(item.body):      # shape like [A -> ⍺.aβ b]
                    if item.body[item.pos] == input:
                        # None terminals GOTO state
                        if input in n_terminals:
                            row[row_pos] = str(goto_label)
                        # Terminals action shift state
                        elif input in terminals + term_values:
                            row[row_pos] = "s" + str(goto_label)
        # Terminals reduce action. shape like  [A -> ⍺.  a]
        for row_pos, input in enumerate(all_symbols):
            for item in closure:
                if item.pos == len(item.body) and \
                        item.follow == input and \
                        item.head.symbol != 'startsup':
                    p_num = get_prod_number(item.head, item.body)
                    # grammar.index(Production(item.symbol, item.body))
                    row[row_pos] = 'r' + str(p_num)
        # accept condition 'startsup -> start. , $'
        acc_item = Item(NTerm('startsup'), (NTerm('start'),), 1, Value('$'))
        if acc_item in closure:
            input = Value('$')
            row_pos = all_symbols.index(Value('$'))
            row[row_pos] = '$'
        return row

    state_map = [None for i in range(len(closure_group))]
    for closure in closure_group:
        row = get_state_map(closure)
        state_map[closure.label] = row
    return state_map


def generate_syntax_table():
    g = closure_groups()
    state_map = get_states_map(g)
    return state_map


# --------------------------------- SDT ----------------------------------------

class SDT:
    def __init__(self):
        self.syntax_table = generate_syntax_table()
        self.state_stack = [0]
        self.arg_stack = []
        self.accept = False
        self.translation = ''

    def get_action(self, stt, t):
        if isinstance(t, Token):
            try:
                return self.syntax_table[stt][all_symbols.index(Value(t.value))]
            except ValueError:
                return self.syntax_table[stt][all_symbols.index(Term(t.typ))]
        # t is a none_terminal NTerm instance
        else:
            return self.syntax_table[stt][all_symbols.index(t)]

    def ahead(self, token):
        action = self.get_action(self.state_stack[-1], token)
        # shift action push a current state into state_stack
        if action[0] == 's':
            current_state = int(action[1:])
            self.state_stack.append(current_state)
            self.push_arg(token)
        elif action[0] == '$':
            self.translation = grammar[0].rule(self.arg_stack[-1])
            self.accept = True   # success
        # reduce action reduct a production and push
        elif action[0] == 'r':
            # get the production in grammar
            number = int(action[1:])
            production = grammar[number]
            head, body, rule = production
            # pop the states of production body
            for _ in body:
                self.state_stack.pop()
            # push the state of head GOTO(I,X)
            state = self.get_action(self.state_stack[-1], head)
            self.state_stack.append(int(state))

            # translations
            args = []
            for _ in body:
                arg = self.arg_stack.pop()
                args.insert(0, arg)
            translation = rule(*args)
            self.arg_stack.append(translation)

            # reduce actions does not consume a token,
            # only when shifting, a token was consume and passed
            self.ahead(token)
        else:
            raise SyntaxError(f"Not a correct token '{token.__str__()}'.")

    def parse(self, token_stream):
        while True:
            try:
                token = next(token_stream)
                self.ahead(token)
            except StopIteration:
                # patch "$" in the end of token stream
                # to match the augmented grammar
                self.ahead(Token("$", "$", 0, 0))
                return self.translation

    def push_arg(self, token):
        if token.typ == 'C':
            token.code = lambda f_cond: 'Ccode Cfalse = {}'.format(f_cond)
        elif token.typ == 'S1':
            token.code = lambda : 'S1code'
        elif token.typ == 'stmts':
            token.code = lambda : 'stmtscode'
        self.arg_stack.append(token)


# ------------------------------------------------------------------------------


if __name__ == "__main__":
    from tokenizer import tokenizer

    #g = closure_groups()
    #_state_map = get_states_map(g)
    _state_map = generate_syntax_table()
    args = ''.join(list(map(lambda x: '{:'+str(max(5, len(x.__str__())+2))+'s}',
                            all_symbols)))
    s = "{:10s}" + args
    head = ['state', ] + list(all_symbols)
    print(s.format(*head))
    for j, i in enumerate(_state_map):
        _state = [str(j), ] + i
        print(s.format(*_state))

    # token_stream = tokenizer('int a;int b; float c;')
    token_stream = tokenizer('if (C) S1 else stmts')
    sdt = SDT()
    sdt.parse(token_stream)
    print(sdt.translation)
