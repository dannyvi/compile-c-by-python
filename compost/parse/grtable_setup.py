from distutils.core import setup, Extension

setup(name='grtable',
      version='1.0',
      ext_modules=[Extension('grtable', ['grtable/grtable.c',
                                         'grtable/symbol.c',
                                         'grtable/syntax_table.c',
                                         'grtable/tests.c'])])