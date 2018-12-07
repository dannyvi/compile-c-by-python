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

symbol_sets_t  * first_sets_proc(symbol_entry_t *);

typedef symbol_entry_t ntfirsts[128];

extern ntfirsts NTFirst[128];

void init_NTFirst(void);
void NTFirst_print(void);

symbol_sets_t  * first_sets(symbol_entry_t *);

typedef struct closure_t closure_t;
typedef struct goto_list_t goto_list_t;
struct goto_list_t {
    symbol_entry_t sym_index;                     // goto closure by this sym_index;
    closure_t *closure;                  // goto closure;
    goto_list_t *next;                     // the next goto item.
};

typedef struct closure_list_t closure_list_t;

struct closure_list_t {
    pitem_t item;
    closure_list_t *next;
};

struct closure_t {
    int label;
    int length;
    pitem_t * items;
    goto_list_t *goto_list;
    goto_list_t *goto_tail;
    symbol_sets_t accept_symbols;
};

typedef struct clos_entry_t {
    symbol_entry_t nterm;
    symbol_entry_t follow;
} clos_entry_t;

typedef struct clos_entry_sets_t clos_entry_sets_t;
struct clos_entry_sets_t {
    clos_entry_t entry;
    clos_entry_sets_t *next;
};

closure_t * get_closure(closure_list_t * clist, int label);

closure_t * goto_closure(closure_t *clos, symbol_entry_t sentry);
void print_closure_t(char * message, closure_t * ct);
int eq_closure_t(closure_t *a, closure_t *b);

typedef struct col_chain_t col_chain_t;
struct col_chain_t {
    closure_t c;
    col_chain_t *next;
};

col_chain_t * closure_collection(void);

void print_collection_t(col_chain_t * c);

#define NTACT 0
#define REDUCE 1
#define SHIFT 2
#define ERROR 3
#define ACCEPT 4



typedef char* action_t ;


PyObject * get_states_list(col_chain_t *c, Py_ssize_t length);

#ifdef __cplusplus
}
#endif

#endif //COMPOST_CLOSURE_H
