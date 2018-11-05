import queue
from typing import Set
from .types import NTerm, Term, Value, Null

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


def is_nterm(symbol):
    return isinstance(symbol, NTerm)


def is_term(symbol):
    return isinstance(symbol, Term) or isinstance(symbol, Value)


def nullable(none_terminal):
    try:
        return none_terminal.nullable
    except AttributeError:
        return False


def first(symbol, grammar):
    """Return the first terminal sets that may occur in the Symbol."""
    result = set()
    if is_term(symbol):
        return set([symbol])
    elif is_nterm(symbol):
        if nullable(symbol):
            result = result.union([Null()])
        for i in grammar:
            if i.head == symbol:
                epsilons = True
                current = 0
                while epsilons is True and current < len(i.body):
                    if i.body[current] != symbol:
                        result = result.union(first(i.body[current], grammar))
                    if not nullable(i.body[current]):
                        epsilons = False
                    current += 1
    return result


def firsts(suffix, grammar):
    if len(suffix) == 1:
        return first(suffix[0], grammar)
    else:
        if not nullable(suffix[0]):
            return first(suffix[0], grammar)
        else:
            return first(suffix[0], grammar).union(firsts(suffix[1:], grammar))


def get_closure(cl, grammar, label):
    """get all Item of a Closure from given Items, by adding implied Items.

    The implied Items are the productions of the None terminals after the
    current position, which put a dot on the head."""
    def get_body_nterm(item):
        pos, prod = (item.pos, item.body)
        if pos < len(prod):
            symbol = prod[pos]
            if is_nterm(symbol):
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
            termins = firsts(suffix, grammar)
            for product in products:
                for terminal in termins:
                    new_item = Item(symbol, product.body, 0, terminal)
                    if new_item not in item_set:
                        item_set.add(new_item)
                        q.put(new_item)
    c = Closure(item_set, label)
    return c


def goto(clos: Closure, token, grammar) -> Closure:
    """a closure that could get from the current closure by input a letter.

    :param clos: the current closure.
    :param token: the input letter.
    :return: Closure.
    """
    item_set = set()
    for item in clos.sets:
        dot, prod = (item.pos, item.body)
        if dot < len(prod) and prod[dot] == token and \
                isinstance(prod[dot], type(token)):
            new_item = Item(item.head,
                            item.body,
                            item.pos + 1,
                            item.follow)
            item_set.add(new_item)
    c = Closure(item_set)
    return get_closure(c, grammar, label=None)


def closure_groups(grammar, all_symbols):
    def find_label(closure, group):
        for i in group:
            if closure == i:
                return i.label
        return None
    group = set()
    label = 0
    start_item = Item(NTerm('startsup'), (NTerm('start'),), 0, Value('$'))
    start = get_closure(Closure({start_item}), grammar, label)
    q = queue.Queue()
    q.put(start)
    group.add(start)
    while not q.empty():
        c = q.get()
        for literal in all_symbols: # terminals + n_terminals:
            go_clos = goto(c, literal, grammar)
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


def get_states_map(closure_group, grammar, all_symbols):

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
                        if is_nterm(input):
                            row[row_pos] = str(goto_label)
                        # Terminals action shift state
                        elif is_term(input):
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


def gen_syntax_table(grammar, all_symbols):
    g = closure_groups(grammar, all_symbols)
    state_map = get_states_map(g, grammar, all_symbols)
    return state_map

