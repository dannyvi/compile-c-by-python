import re

from .atoms import Production, NTerm, Term, Value


def load_grammar(grammar_file):

    n_terminals = []
    terminals = []
    term_values = []
    all_symbols = []
    grammar = []
    namespace = {}

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

        # 3. get definition funcs into namespace
        exec(aug_definitions, namespace)

        # 4. strip comments
        clean_grammar = strip_comments(aug_grammar)

        # 5. get none terminals list
        prods = separate_productions(clean_grammar)
        n_terminals = get_none_terminals(prods)

        # 6. get terminals and terminal values list. And all symbols list
        terminals, term_values = get_terminals_values(clean_grammar, n_terminals)

        all_symbols = term_values + terminals + n_terminals

        # 7. generate grammar list, contains production rules.
        #    Has to deal or productions and nullable productions.

        for prod in prods:
            p_list = get_production(prod, n_terminals, terminals, term_values)
            grammar.extend(p_list)

        return grammar, all_symbols, namespace


