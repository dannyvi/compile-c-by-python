//
// Created by DannyV on 2018-11-28.
//

#ifndef COMPOST_GRAMMAR_H
#define COMPOST_GRAMMAR_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "symbol.h"

typedef union production_t {
    __uint128_t pnum;
    struct {
        symbol_entry_t body[14]; // body[0] is the head, body[1:14] is product
        symbol_entry_t dot;
        symbol_entry_t follow;
    } ;
} production_t, pitem_t;

pitem_t build_pitem_t(production_t *prod, symbol_entry_t pos, symbol_entry_t follow);

typedef struct prod_list_t prod_list_t;
 struct prod_list_t {
    production_t current;
    prod_list_t *next;
} ;


extern int GrammarCount;
extern production_t *Grammar;

void Grammar_init(size_t size);

void Grammar_add(production_t);
void Grammar_print(void);

symbol_sets_t  * new_symbol_sets(void) ;
int entry_in_symbol_sets(symbol_entry_t, symbol_sets_t  *);
void symbol_sets_link(symbol_sets_t  *, symbol_sets_t  *);
symbol_sets_t * union_symbol_sets(symbol_sets_t  *seta, symbol_sets_t  *setb);
void symbol_sets_add(symbol_entry_t sym, symbol_sets_t  * sets);
symbol_sets_t  * symbol_sets_create(symbol_entry_t syms[], size_t size);
void print_symbol_sets(char * header, symbol_sets_t  * s);

prod_list_t * get_productions(symbol_entry_t *sym);

void print_pitem_t(pitem_t *item);
void print_pitem_t_str(pitem_t *item) ;

#ifdef __cplusplus
}
#endif

#endif //COMPY_SYNTAX_TABLE_H
