from .sdt import SDT


def flatten_grammar(grammar):
    return list(map(lambda x: [x.head] + list(x.body), grammar))
