import queue
from typing import Set

from .atoms import NTerm, Term, Value, Null


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
        return f"[{self.follow}]  {self.head} -> {pr}"

    def __repr__(self):
        return f"<Item:{self.__str__()} >\n"

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
        p = '-'*35+f'Closure:{self.label}'+'-'*35
        return f"\n{p}\n{self.__str__()}\n{p}\n"

    def __eq__(self, other):
        return self.sets == other.sets

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        return hash(self.__str__())

    def __contains__(self, item):
        return item in self.sets


def first(symbol, grammar):
    """Return the first terminal sets that may occur in the Symbol."""
    result = set()
    if isinstance(symbol, (Term, Value)):
        return set([symbol])
    elif isinstance(symbol, NTerm):
        if symbol.nullable:
            result = result.union([Null()])
        r = map(lambda x: x if i.head == symbol else set(), grammar)
        g = [x for x in grammar if x.head == symbol]
        for i in g:
            null, current = True, 0
            while null and current < len(i.body):
                sym = i.body[current]
                if sym != symbol:
                    result = result.union(first(sym, grammar))
                if not isinstance(sym, NTerm) or not sym.nullable:
                    null = False
                current += 1
    return result


def firsts(suffix, grammar):
    """Return the first terminal sets that may occur in the Formula body."""
    if len(suffix) == 1:
        return first(suffix[0], grammar)
    else:
        if isinstance(suffix[0], (Term, Value)) or suffix[0].nullable:
            return first(suffix[0], grammar)
        else:
            return first(suffix[0], grammar).union(firsts(suffix[1:], grammar))


def get_closure(cl, grammar, label):
    """get all Item of a Closure from given Items, by adding implied Items.

    The implied Items are the productions of the None terminals after the
    current position, which put a dot on the head."""
    itemset = set()
    q = queue.Queue()
    for i in cl.sets:
        itemset.add(i)
        q.put(i)
    while not q.empty():
        item = q.get()
        p, b = item.pos, item.body
        symbol = b[p] if p < len(b) and isinstance(b[p], NTerm) else None
        if symbol:
            prods = [i for i in grammar if i.head == symbol]
            suffix = item.body[item.pos+1:] + tuple([item.follow])
            terminals = firsts(suffix, grammar)
            for d in prods:
                for t in terminals:
                    newitem = Item(symbol, d.body, 0, t)
                    if newitem not in itemset:
                        itemset.add(newitem)
                        q.put(newitem)
    c = Closure(itemset, label)
    return c


def goto(clos: Closure, token, grammar) -> Closure:
    """a closure that could get from the current closure by input a letter.

    :param clos: the current closure.
    :param token: the input Symbol of NTerm, Term or Value.
    :param grammar: list of Production.
    :return: Closure.
    """
    itemset = set()
    for i in clos.sets:
        p, b = (i.pos, i.body)
        if p < len(b) and b[p] == token:
            newitem = Item(i.head, i.body, i.pos + 1, i.follow)
            itemset.add(newitem)
    c = Closure(itemset)
    return get_closure(c, grammar, label=None)


def closure_collection(grammar, symbols):
    collection = set()
    label = 0
    firstitem = Item(NTerm('startsup'), (NTerm('start'),), 0, Value('$'))
    start = get_closure(Closure({firstitem}), grammar, label)
    q = queue.Queue()
    q.put(start)
    collection.add(start)
    while not q.empty():
        c = q.get()
        for literal in symbols:
            goclos = goto(c, literal, grammar)
            if goclos:
                if goclos not in collection:
                    label += 1
                    goclos.label = label
                    q.put(goclos)
                    collection.add(goclos)
                    c.goto[literal] = label
                else:
                    golabl = [i.label for i in collection if i == goclos]
                    if golabl:
                        c.goto[literal] = golabl[0]
    return collection


def get_states_map(collection, grammar, symbols):

    def get_prod_number(symbol, body):
        for num, prod in enumerate(grammar):
            if prod.head == symbol and prod.body == body:
                return num

    def get_state_map(closure):
        """ table row like all_symbols list state maps."""
        row = ["." for i in symbols]
        for sym, labl in closure.goto.items():     # NTerm GOTO & Term shift act
            posit = symbols.index(sym)
            for item in closure:
                # shape like [A -> ⍺.aβ b]
                if item.pos < len(item.body) and item.body[item.pos] == sym:
                    if isinstance(sym, NTerm):            # Nterm GOTO state
                        row[posit] = str(labl)
                    elif isinstance(sym, (Term, Value)):  # Term shift act
                        row[posit] = "s" + str(labl)

        for posit, sym in enumerate(symbols):   # Term reduce act [A -> ⍺.  a]
            for item in closure:
                if item.pos == len(item.body) and \
                        item.follow == sym and \
                        item.head.symbol != 'startsup':
                    p_num = get_prod_number(item.head, item.body)
                    row[posit] = 'r' + str(p_num)
        # accept condition 'startsup -> start. , $'
        accitem = Item(NTerm('startsup'), (NTerm('start'),), 1, Value('$'))
        if accitem in closure:
            posit = symbols.index(Value('$'))
            row[posit] = '$'
        return row

    states = [None for i in range(len(collection))]
    for clos in collection:
        currow = get_state_map(clos)
        states[clos.label] = currow
    return states


def gen_syntax_table(grammar, symbols):
    g = closure_collection(grammar, symbols)
    states = get_states_map(g, grammar, symbols)
    return states

