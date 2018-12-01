//
// Created by DannyV on 2018-11-28.
//

#ifndef COMPOST_SYMBOL_H
#define COMPOST_SYMBOL_H

#include <stdio.h>

typedef enum sym_type {NTerm=0, Term=2, Value=3} sym_type;

typedef struct symbol {
    sym_type type;
    char* name;
} symbol;

typedef union symbol_entry {
    unsigned char entry;
    struct {
        unsigned char index:6;   // the index in the symbol_table.
        unsigned char flag:2;  // symbol 0 is NTerm 2: Term, 3:Value.
    };
} symbol_entry;

typedef struct symbol_entry_list {
    symbol_entry s_entry;
    struct symbol_entry_list *next;
} symbol_entry_list;

extern symbol_entry_list SymbolEntry;

int SymbolEntry_len(void);
void SymbolEntry_push(symbol_entry);
void SymbolEntry_print(void);

typedef struct symbol_table {
    char name[64];
} symbol_table;

#define TBLEN 256
// 0-127, NTerm; 128-191, Term. 192-255, Value.
extern symbol_table SymbolTable[TBLEN];

symbol symbol_create(sym_type type, char* name);
symbol_entry sentry_find(symbol);

void SymbolTable_add(symbol sym);

void build_symbol_table(symbol *symbols, size_t size);

void SymbolTable_print(void);
#endif //COMPY_SYMBOL_H
