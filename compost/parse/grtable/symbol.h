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

typedef union symbol_entry_t {
    unsigned char id;
    struct {
        unsigned char index:6;   // the index in the symbol_table.
        unsigned char flag:2;  // symbol_t 0 is NTerm 2: Term, 3:Value.
    };
} symbol_entry_t;


typedef struct symbol_sets_t  symbol_sets_t ;
struct symbol_sets_t  {
    symbol_entry_t entry;
    symbol_sets_t  *next;
};


extern symbol_sets_t SymbolEntry;

int SymbolEntry_len(void);
void SymbolEntry_push(symbol_entry_t);
void SymbolEntry_print(void);

typedef struct symbol_table {
    char name[64];
} symbol_table;

#define TBLEN 256
// 0-127, NTerm; 128-191, Term. 192-255, Value.
extern symbol_table SymbolTable[TBLEN];

symbol_t symbol_create(sym_type type, char* name);
symbol_entry_t sentry_find(symbol_t);

void SymbolTable_add(symbol_t sym);

void build_symbol_table(symbol_t *symbols, size_t size);

void SymbolTable_print(void);
#endif //COMPY_SYMBOL_H
