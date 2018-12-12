from distutils.core import setup, Extension

setup(name='grtable',
      version='1.0',
      ext_modules=[Extension('grtable', ['_grtable/grtable.c',
                                         '_grtable/symbol.c',
                                         '_grtable/grammar.c',
                                         '_grtable/closure.c',
                                         '_grtable/collection.c',
                                         '_grtable/firstsets.c',
                                         '_grtable/statemap.c',
                                         ])]
      )
