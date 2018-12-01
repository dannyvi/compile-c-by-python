//
// Created by DannyV on 2018-11-28.
//

#ifndef COMPOST_SYNTAX_TABLE_H
#define COMPOST_SYNTAX_TABLE_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "symbol.h"

typedef union production {
    long double pnum;
    struct {
        symbol_entry body[14]; // body[0] is the head, body[1:14] is product
        symbol_entry dot;
        symbol_entry follow;
    } ;
} production, pitem;

typedef struct prod_list prod_list;
 struct prod_list {
    production current;
    prod_list *next;
} ;


extern int GrammarCount;
extern production *Grammar;

void Grammar_init(size_t size);

void Grammar_add(production);
void Grammar_print(void);

typedef struct goto_list {
    symbol_entry sym_index;             // goto closure by this sym_index;
    struct closure_t *closure;                 // goto closure;
    struct goto_list *next;                    // the next goto item.
} goto_list;

typedef struct closure_t {
    int label;
    //int length;
    //int goto_length;
    pitem *items;
    struct goto_list *go_to;
}closure_t;

typedef struct collection_chain {
    closure_t c;
    closure_t *next;
}collection_chain;

typedef struct symbol_sets symbol_sets;

struct symbol_sets {
    symbol_entry current;
    symbol_sets *next;
};

int entry_in_symbol_sets(symbol_entry, symbol_sets *);
void symbol_sets_link(symbol_sets *, symbol_sets *);
symbol_sets* union_symbol_sets(symbol_sets *seta, symbol_sets *setb);
void symbol_sets_add(symbol_entry sym, symbol_sets * sets);
symbol_sets * symbol_sets_create(symbol_entry syms[], size_t size);

prod_list * get_productions(symbol_entry *sym);
symbol_sets * first_sets(symbol_entry *);

#ifdef __cplusplus
}
#endif

#endif //COMPY_SYNTAX_TABLE_H
