//
// Created by DannyV on 2018-11-28.
//

#ifndef COMPOST_SYMBOL_H
#define COMPOST_SYMBOL_H

#include <stdio.h>

typedef enum sym_type {NTerm=0, Term=2, Value=3} sym_type;

typedef struct symbol_t {
    sym_type type;
    char* name;
} symbol_t;

typedef union sym_ent_t {
    unsigned char id;
    struct {
        unsigned char index:6;   // the index in the symbol_table.
        unsigned char flag:2;  // symbol_t 0 is NTerm 2: Term, 3:Value.
    };
} sym_ent_t;


typedef struct symt_list_t  symt_list_t ;
struct symt_list_t  {
    sym_ent_t entry;
    symt_list_t  *next;
};


extern symt_list_t SymbolEntry;

int SymbolEntry_len(void);
void SymbolEntry_push(sym_ent_t);
void SymbolEntry_print(void);

typedef struct symbol_table {
    char name[64];
} symbol_table;

#define TBLEN 256
// 0-127, NTerm; 128-191, Term. 192-255, Value.
extern symbol_table SymbolTable[TBLEN];

symbol_t symbol_create(sym_type type, char* name);
sym_ent_t sentry_find(symbol_t);

void SymbolTable_add(symbol_t sym);

void build_symbol_table(symbol_t *symbols, size_t size);

void SymbolTable_print(void);
#endif //COMPY_SYMBOL_H
