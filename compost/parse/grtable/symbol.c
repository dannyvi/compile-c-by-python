//
// Created by DannyV on 2018-11-28.
//

#include <stdlib.h>
#include <string.h>

#include "symbol.h"

symbol_table SymbolTable[TBLEN];
symbol_entry_list SymbolEntry={ 0, NULL };

symbol symbol_create(sym_type type, char* name) {
    symbol sym;
    sym.type = type;
    sym.name = name;
    return sym;
}

symbol_entry sentry_find(symbol sym){
    int len;
    if (sym.type==NTerm){len=128;}
    else {len=64;}
    int flag = sym.type << 6;
    //printf("Flag: %d\n", flag);
    for (int i=flag;i<TBLEN/2+flag;i++){
        char * name = SymbolTable[i].name;
        char * name2 = sym.name;
        int eq = 1;
        while(*name){
            if (*name!=*name2){
                eq = 0;
                break;
            }
            else {
                name +=  1;
                name2 += 1;}
        }
        if (eq)
        {
            symbol_entry e = {.entry=i};
            return e;
        }
    }
    symbol_entry n = {.entry=255};
    return n;
}

int SymbolEntry_len(void){
    if (!SymbolEntry.next) { return 0;}
    else {
        int n = 0;
        symbol_entry_list *count = &SymbolEntry;
        while (count->next) {
            n += 1;
            count = count->next;
        }
        return n;
    }
}

void SymbolEntry_push(symbol_entry entry) {
    if (!SymbolEntry.next) {
        symbol_entry_list *next = (symbol_entry_list *) calloc(1, sizeof(symbol_entry_list));
        SymbolEntry.next = next;
        SymbolEntry.s_entry = entry;
    }
    else {
        symbol_entry_list *n = &SymbolEntry;
        do {n = n->next;} while (n->next);
        n -> next = (symbol_entry_list *) calloc(1, sizeof(symbol_entry_list));
        n -> s_entry = entry;
    }
}

void SymbolEntry_print(void){
    if (!SymbolEntry.next){
        printf("Empty");
    }
    else {
        symbol_entry_list *e = &SymbolEntry;
        while (e->next) {
            printf("%d ", e->s_entry.entry);
            e = e->next;
        }
        printf("\n\n");
    }
}

void SymbolTable_add(symbol sym) {
    symbol_entry index;
    int len;
    if (sym.type==NTerm){len=128;}
    else {len=64;}
    int flag = sym.type << 6;         // The flag is the 1 bit of index.
    char * t = (char *) SymbolTable;
    for (int i=flag;i<len+flag;i++){
        if (!SymbolTable[i].name[0]){
            t += i * sizeof(symbol_table);
            strcpy(t, sym.name);
            index.entry = (unsigned short) i;
            SymbolEntry_push(index);
            return ;
        }
    }
}

void build_symbol_table(symbol * symbols, size_t size) {
    symbol * sym = symbols;
    for (int i=0;i<(int)size;i++){
        SymbolTable_add(*sym);
        sym += 1;
    }
}

void SymbolTable_print(void) {
    for (int i=0;i<256;i++) {
        if (SymbolTable[i].name[0]){
            char *type;
            if (i<128){type="NTerm";}
            else if (i<192){type="Term";}
            else {type="Value";}
            printf("%s %d : %s\n", type, i, SymbolTable[i].name);
        }
    }
}
