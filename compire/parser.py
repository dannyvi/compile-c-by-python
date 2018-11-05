from .parse import SDT


gram_filename = os.path.dirname(os.path.abspath(__file__)) + '/gram/a.grammar'



sdt = SDT.from_gram(gram_filename)
