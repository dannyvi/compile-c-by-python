from compire.parse.loader import *

code = """start       :== stmt                                {{start}}
stmt        :== declare                             {{stmt}}
declare     :== type ID ";"                         {{declare}} 
                |
type        :== base component                      {{type}}
base        :== "int" {{base}}
                    | "float"                     {{base}} 
component   :== "[" NUMBER "]" {{component}}
                 |        
"""

with open('tests/code_with_comments.py') as c:
    # 1. seperate file by  ----------------- seperate line
    raw_grammar = c.read()


def test_start():
    deps = '-' * 35
    print("\n{}grammar loader{}".format(deps, deps))


def test_strip_comments():
    print('\n')
    print(strip_comments(raw_grammar))


class TestClass:

    def test_separate_productions(self):
        print('\n')
        p = separate_productions(code)
        for i in p:
            print(i)

    def test_get_funcs(self):
        print('\n')
        plist = separate_productions(code)
        n_terms = get_none_terminals(plist)
        print(n_terms)
        terms, values = get_terminals_values(code, n_terms)
        print(terms)
        print(values)

        def f():
            pass
        env = {"start": f, "stmt": f, "declare": f, "type": f,
               "base": f, "component": f}
        gram = []
        for p in plist:
            nl = get_single_production(p, n_terms, env)
            assert nl
            for i in nl:
                gram.extend(nl)
                print(i)
        print("\n Remove Null productions")
        new_gram = eliminate_null_production(gram)
        for i in new_gram:
            print(i)

    def test_self_eliminate(self):
        def f():
            pass
        n = NTerm("comp", nullable=True)
        prod = Production(n,
                          (Value('['), Term('NUMBER'), Value(']'),n),
                          f)
        group = eliminate_null_production([prod])
        print(group)


