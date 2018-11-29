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

//typedef unsigned char entry_select;

typedef union production {
    long double pnum;
    struct {
        symbol_entry body[14]; // body[0] is the head, body[1:14] is product
        symbol_entry dot;
        symbol_entry follow;
    } ;
} production, item;

//production production_build(symbol*, size_t);

extern int GrammarCount;
extern production *Grammar;

void Grammar_init(size_t size);
//void Grammar_build(production *, size_t);
void Grammar_add(production);
void Grammar_print(void);

struct goto_list {
    unsigned char sym_index;
    struct collection_t *collection;
    struct goto_list *next;
};

struct collection_t {
    int label;
    item *items;
    struct goto_list *go_to;
};

struct collection_set {
    struct collection_t c;
    struct collection_t *next;
};

#ifdef __cplusplus
}
#endif

#endif //COMPY_SYNTAX_TABLE_H
