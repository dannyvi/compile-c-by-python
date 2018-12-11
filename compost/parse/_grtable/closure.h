//
// Created by DannyV on 2018-12-1.
//

#ifndef COMPOST_CLOSURE_H
#define COMPOST_CLOSURE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "symbol.h"
#include "grammar.h"
#include "Python.h"

#define NONE_LABEL 100000000


pitem_t build_pitem_t(prod_t *prod, sym_ent_t pos, sym_ent_t follow) ;


typedef struct closure_t closure_t;
typedef struct goto_list_t goto_list_t;

struct closure_t {
    int label;
    int length;
    pitem_t * items;
    goto_list_t *goto_list;
    goto_list_t *goto_tail;
    sym_ent_list_t * accept_symbols;
};

struct goto_list_t {
    sym_ent_t sym_index;                     // goto closure by this sym_index;
    closure_t closure;                  // goto closure;
    goto_list_t *next;                     // the next goto item.
};

void PyMem_Free_goto_list(goto_list_t *lst);
void PyMem_Free_sym_ent_list(sym_ent_list_t *sets);


typedef struct nterm_follow_t {
    sym_ent_t nterm;
    sym_ent_t follow;
} nterm_follow_t;

typedef struct nf_list_t nf_list_t;
struct nf_list_t {
    nterm_follow_t entry;
    nf_list_t *next;
};

closure_t * get_closure(pitem_list_t * clist, int label);

void add_cl(pitem_t itm, pitem_list_t *clp) ;


#ifdef __cplusplus
}
#endif

#endif //COMPOST_CLOSURE_H
