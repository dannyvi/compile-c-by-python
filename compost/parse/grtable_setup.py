from distutils.core import setup, Extension

setup(name='grtable',
      version='1.0',
      ext_modules=[Extension('grtable', ['grtable/grtable.c',
                                         'grtable/symbol.c',
                                         'grtable/grammar.c',
                                         'grtable/closure.c',
                                         'grtable/tests.c'])]
      )