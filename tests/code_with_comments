Symbol = collections.namedtuple("Symbol", ["name", "type", "width"])


def start(stmts_cb):
    '''abc #kkkk
    ssmm
    :param stmts_cb:  # tail comments in triple
    :return:
    '''
    def callback():
        return stmts_cb()
    return callback


def stmts1(sts, st):
    """documentation
    # comments in triple
    """
    def callback():
        d = 'azz3##baa'    #  tail comments2
    # one line comments
    return callback

