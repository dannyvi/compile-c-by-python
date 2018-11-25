"""Loader do the preceding part of constructing a parser(syntax analyzer).

It read rules from a .grammar definition file, and execute a analyze procedure.

The procedure of loading is below:

1.  seperate file by  --------------- seperate line into **definitions** and
    **rules** part.
2.  augment syntax by adding ``startsup -> start "$"`` with an "$" as the end.
3.  get definition funcs in the **rule** part into namespace env.
4.  strip comments from the **definitions** part.
5.  separate the productions from **definition**.
6.  get none terminals by reading the head of the productions.
7.  get terminals and values by reading from the right part of the productions.
8.  generate grammar list.
9.  eliminating null productions.

The main function is ``load_grammar`` and it
returns a ``grammar list``, a ``symbol list``, and an ``env``.
"""
import re
from functools import reduce
from .atoms import Production, NTerm, Term, Value, Code, Null


def strip_comments(stream):
    """Strip comments, tail comments, but keep # in quotations."""
    switch = '\'"'
    quoted = False
    quotation = None
    triplet = 0
    mulline = False
    commented = False
    code = ''
    for num, i in enumerate(stream):
        if triplet:
            code += i
            triplet -= 1
            continue
        if i in switch:
            if not quoted:
                quoted = True
                quotation = i
                if stream[num+1] == stream[num+2] == i:
                    triplet = 2
                    mulline = True
            else:
                if i == quotation:
                    if mulline:
                        if stream[num+1] == stream[num+2] == i:
                            triplet = 2
                            mulline = False
                            quoted = False
                            quotation = None
                    else:
                        quoted = False
                        quotation = None
        elif i == '#':
            if not quoted:
                commented = True
        elif i == '\n' and commented and not mulline:
            commented = False
        if commented:
            code += ' '
        else:
            code += i
    return code


def get_none_terminals(prod_str_list):
    n_terms = []
    spec = re.compile(r"""(?s)^\s*?(?P<Head>\w+)     # head Nterm
                          .*?                  # any character
                          (?:(?P<Multi>(?:\|\s*{{.*?}}.*?{{.*?}}\s*)$)|
                          (?P<Nullable>(?:\|\s*|\|\s*{{.*?}}\s*)?$))""",
                      re.X)
    for p in prod_str_list:
        res = re.match(spec, p).groups()
        nterm = NTerm(res[0], bool(res[2]))
        if nterm not in n_terms:
            n_terms.append(nterm)
        else:
            if nterm.nullable:
                n_terms[n_terms.index(nterm)] = nterm
    return n_terms


def decompose_prod(prod, n_terms, values, terms, codes):
    """Decompose productions and return productions, terms, values and codes.

    Incrementally add productions, values, terms, and codes that are discovered
    in the prod parameter.

    :param prod: production with '|' which combined multi prods with one head.
    :param n_terms: a complete none terminal list
    :param values: the values list already occurs in the prev part.
    :param terms: the terms list already occurs in the prev part.
    :param codes: the codes list already occurs in the prev part.
    :return: a list of (productions, null_prods, values, terms, codes)
    """

    p = r"(?s)^\s*?(\w+)\s*(.*)$"
    h_str, units = re.match(p, prod).groups()
    head = n_terms[n_terms.index(NTerm(h_str))]
    bodies = re.split(r"\|", units)
    productions = []
    null_prods = []
    spec = [r"(?s){{\s*(?P<Code>.+?)\s*}}",
            r"(?P<Spaces>\s+)",
            r"(?P<quote>[\"'])(?P<Value>\S+)(?P=quote)",
            r"(?P<Term_NTerm>\w+)",
            ]
    pattern = "|".join(spec)
    for body in bodies:
        formlist = []
        for symbol in re.finditer(pattern, body):
            kind = symbol.lastgroup
            value = symbol.group(kind)
            if kind == "Value":
                v = Value(value)
                formlist.append(v)
                if v not in values:
                    values.append(v)
            elif kind == "Term_NTerm":
                if NTerm(value) in n_terms:
                    t = n_terms[n_terms.index(NTerm(value))]
                    formlist.append(t)
                else:
                    t = Term(value)
                    formlist.append(t)
                    if t not in terms:
                        terms.append(t)
            elif kind == "Code":
                t = Code(f"CD{str(len(codes))}", value)
                formlist.append(t)
                codes.append(t)
                nullprod = Production.cons(t, (Null(),))
                null_prods.append(nullprod)
        production = Production.cons(head, tuple(formlist))
        productions.append(production)
    return productions, null_prods, values, terms, codes


def eliminate_null_production(grammar):
    new_gram = []
    grams = list(map(lambda p: p.remove_null(), grammar))
    for i in grammar:
        prods = i.remove_null()
        for p in prods:
            if p not in new_gram:
                new_gram.append(p)
    return new_gram


def substitue_ref(production):
    p = production.production
    total = len(p)
    for num, atom in enumerate(p):
        if isinstance(atom, Code):
            startp = -num
            format_t = [f'Stack[{i}]' for i in range(startp, 0)]
            atom.source = atom.source.format(*format_t)


def load_grammar(grammar_file):
    """Read rules from grammar file, parse and return intermediates.

    For example::

        from compfly.parse.loader import load_grammar
        gram_file = "a.grammar"      # the file with correct path needed
        grammar, symbols, env = load_grammar(gram_file)

    :param grammar_file: grammar rules in \*.grammar file.
    :return: a tuple contains a grammar list, a symbols list, and an env.
    """

    grammar = []
    env = {}

    with open(grammar_file) as f:
        # 1. seperate file by  ----------------- seperate line
        raw_grammar, definitions = re.split(r"(?m)^[\s-]+[-]+[\s-]+$", f.read())

        # 2. augment syntax
        aug_grammar = 'startsup :== start "$" \n' + raw_grammar
        aug_definitions = definitions + '\n\ndef startsup(f):\n    return f()'

        # 3. get definition funcs into namespace
        exec(aug_definitions, env)

        # 4. strip comments
        pure_grammar = strip_comments(aug_grammar)

        # 5. get productions with | operators. alter to prefixed expression.
        prefixed = re.sub(r"(?m)^(\w+)(\s*?)(:==)", r"\3\2\1", pure_grammar)
        prods = [i for i in re.split(":==", prefixed) if i]

        # 6. get none terminals list
        n_terms = get_none_terminals(prods)

        # 7. get terminals and terminal values list. And all symbols list
        values, terms, codes, null_prod_list = [], [], [], []

        # 8. generate grammar list, contains production rules.
        for prod in prods:
            result = decompose_prod(prod, n_terms, values, terms, codes)
            p_list, n_list, values, terms, codes = result
            null_prod_list.extend(n_list)
            grammar.extend(p_list)
        grammar.extend(null_prod_list)

        symbols = [Null()] + values + terms + n_terms + codes

        # 9. eliminate null productions.
        new_grammar = eliminate_null_production(grammar)

        for i in new_grammar:
            substitue_ref(i)

        return new_grammar, symbols, env

