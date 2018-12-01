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

symbol_sets * first_sets_proc(symbol_entry *);

// the first symbol list of NTerm;
//typedef struct ntfirsts {
//    symbol_entry list[128];
//} ntfirsts;

typedef symbol_entry ntfirsts[128];

extern ntfirsts NTFirst[128];

void init_NTFirst(void);
void NTFirst_print(void);

symbol_sets * first_sets(symbol_entry *);

typedef struct goto_list {
    symbol_entry sym_index;                     // goto closure by this sym_index;
    struct closure_t *closure;                  // goto closure;
    struct goto_list *next;                     // the next goto item.
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

#ifdef __cplusplus
}
#endif

#endif //COMPOST_CLOSURE_H