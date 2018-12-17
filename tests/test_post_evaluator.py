from compost.evaluator import Evaluator


def test_expression():

    print("\nparsing ---------- '\n")
    stream = 'int add11 (int a) { a + 3 }'
    ev = Evaluator()
    print(ev.evaluate(stream, optimize=True, llvmdump=True))
    print(ev.evaluate('int suba (int b) { 4 + 2}', llvmdump=True))
    print(
        f"""Evaluate add11(3) {ev.evaluate('add11(5)', optimize=True, llvmdump=True)}""")
