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
        sym_ent_t body[14]; // body[0] is the head, body[1:14] is product
        sym_ent_t dot;
        sym_ent_t follow;
    } ;
} production_t, pitem_t;

pitem_t build_pitem_t(production_t *prod, sym_ent_t pos, sym_ent_t follow);

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

symt_list_t  * new_symbol_sets(void) ;
int entry_in_symbol_sets(sym_ent_t, symt_list_t  *);
void symbol_sets_link(symt_list_t  *, symt_list_t  *);
symt_list_t * union_symbol_sets(symt_list_t  *seta, symt_list_t  *setb);
void symbol_sets_add(sym_ent_t sym, symt_list_t  * sets);
symt_list_t  * symbol_sets_create(sym_ent_t syms[], size_t size);
void print_symbol_sets(char * header, symt_list_t  * s);

prod_list_t * get_productions(sym_ent_t *sym);

void print_pitem_t(pitem_t *item);
void print_pitem_t_str(pitem_t *item) ;

#ifdef __cplusplus
}
#endif

#endif //COMPY_SYNTAX_TABLE_H
