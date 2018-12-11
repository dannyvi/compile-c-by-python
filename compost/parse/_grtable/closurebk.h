//
//Created by DannyV on 2018-12-10.
//

#ifndef COMPOST_CLOSURE_H
#define COMPOST_CLOSURE_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "symbol.h"
#include "grammar.h"


#define NONE_LABEL 100000000


typedef struct pitem_list_t pitem_list_t;

struct pitem_list_t{
    pitem_t item;
    pitem_list_t * next;
};

typedef struct closure_t closure_t;
typedef struct goto_t goto_t;

struct closure_t {
    int label;
    pitem_t * items;
    goto_t * gotos;
    sym_ent_t * accepts;
    size_t itm_cnt;
    size_t goto_cnt;
    size_t acc_cnt;
};

struct goto_t {
    sym_ent_t entry;
    closure_t * closure;
};

typedef struct clos_list_t  clos_list_t;
struct clos_list_t {
    closure_t clos;
    clos_list_t * next;
};

typedef struct nf_list_t nf_list_t;

struct nf_list_t {
    sym_ent_t nterm;
    sym_ent_t follow;
    nf_list_t * next;
};

pitem_list_t * new_pitem_list(void);
pitem_t build_pitem(prod_t prod, sym_ent_t pos, sym_ent_t follow);
void append_pitem(pitem_t item, pitem_list_t ** tail);

closure_t * get_closure(pitem_list_t * items);
void destroy_closure(closure_t * closure);

#ifdef __cplusplus
}
#endif

#endif
