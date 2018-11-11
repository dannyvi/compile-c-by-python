from compire.parse.atoms import Production, NTerm, Term, Value


def rule():
    return None


def test_production():
    print("\n")
    head = NTerm("A", nullable=True)
    body = (NTerm("nt", nullable=True),
            Term("t"),
            Value("v"),
            NTerm("nt2"),
            NTerm("nt3", nullable=True)
            )
    p = Production.cons(head, body)
    print(p)
    for i in p.remove_null():
        print(i)




