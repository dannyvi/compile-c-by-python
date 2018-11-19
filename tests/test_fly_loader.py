from compfly.parse.loader import *
import os

code = """start       :== stmt                                {{start}}
stmt        :== declare                             {{stmt}}
declare     :== type ID ";"                         {{declare}} 
type        :== base component                      {{type}}
base        :== "int" {{base}}
                    | "float"                     {{base}} 
component   :== "[" NUMBER "]" {{component}}
                 |        
"""

with open('tests/code_with_comments') as c:
    # 1. seperate file by  ----------------- seperate line
    raw_grammar = c.read()


def test_start():
    deps = '-' * 35
    print("\n{}grammar loader{}".format(deps, deps))


def test_strip_comments():
    print('\n')
    print(strip_comments(raw_grammar))


class TestClass:

    def test_get_funcs(self):
        print('\n')
        prefixed = re.sub(r"(?m)^(\w+)(\s*?)(:==)", r"\3\2\1", code)
        plist = [i for i in re.split(":==", prefixed) if i]

        n_terms = get_none_terminals(plist)
        print(n_terms)
        terms, values, codes = [], [], []

        def f():
            pass
        env = {"start": f, "stmt": f, "declare": f, "type": f,
               "base": f, "component": f}
        gram = []
        for p in plist:
            nl = decompose_prod(p, n_terms, terms, values, codes)
            assert nl
            for i in nl:
                gram.extend(nl)
                print(i)
        print("\n Remove Null productions")

    def test_self_eliminate(self):
        def f():
            pass
        n = NTerm("comp", nullable=True)
        prod = Production.cons(n, (Value('['), Term('NUMBER'), Value(']'), n))
        group = eliminate_null_production([prod])
        print(group)


def test_a_grammar():
    gram_filename = os.path.dirname(
        os.path.dirname(
            os.path.abspath(__file__))) + '/compfly/gram/a.grammar'
    grammar, syms, env = load_grammar(gram_filename)
    for i in grammar:
        print(i)
    print(syms)
