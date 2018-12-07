//
// Created by DannyV on 2018-11-28.
//

#include <stdlib.h>
#include <string.h>

#include "grammar.h"

production_t *Grammar;
int GrammarCount = 0;


void Grammar_init(size_t size){
    Grammar = calloc(size, sizeof(production_t));
}

void Grammar_add(production_t prod){
    Grammar[GrammarCount] = prod;
    GrammarCount += 1;
}

void Grammar_print(void) {
    printf("Grammar list: (from %s)\n", __FILE__);
    for (int i=0;i<GrammarCount;i++) {
        production_t p = Grammar[i];
        printf("Prd %d: ",i);
        for (int j=0;j<14;j++){
            if (!(p.body[j].entry == 0 && j>0 ))
            printf("%d ", p.body[j].entry);
        }
        printf("\n");
    }
    printf("\n\n");
}

int entry_in_symbol_sets(symbol_entry_t sym, symbol_sets_t  *ss){
    symbol_sets_t  *c = ss;
    do {
        if (c->current.entry == sym.entry){ return 1; }
        c = c->next;
    } while (c);
    return 0;
}

void symbol_sets_link(symbol_sets_t  *seta, symbol_sets_t  *setb){
    symbol_sets_t  *c = seta;
    while (c->next) {
        c = c->next;
    }
    c->current = setb->current;
    c->next = setb->next;
}

symbol_sets_t * union_symbol_sets(symbol_sets_t  *seta, symbol_sets_t  *setb){
    while(entry_in_symbol_sets(setb->current, seta)){
        if (setb->next) {setb = setb->next;}
        else {return seta;}
    }
    symbol_sets_t  *c = setb;
    while (c->next) {
        if (entry_in_symbol_sets(c->current, seta)) {
                c->current = c->next->current;
                c->next = c->next->next;
        }
        else {
            c = c->next;
        }

    }
    if (setb) {symbol_sets_link(seta, setb);}
    return seta;
}

void symbol_sets_add(symbol_entry_t sym, symbol_sets_t * sets){
    symbol_sets_t  *s = sets;
    if (!s->next){
        s->current = sym;
        s->next = calloc(1, sizeof(symbol_sets_t ));
    }
    else {
        while (s->next) {
            s = s->next;
        }
        s->current = sym;
        s->next = calloc(1, sizeof(symbol_sets_t ));
    }
}


symbol_sets_t  * new_symbol_sets(void) {
    symbol_sets_t  *ss = calloc(1, sizeof(symbol_sets_t ));
    return ss;
}

symbol_sets_t  * symbol_sets_create(symbol_entry_t syms[], size_t size){
    symbol_sets_t  *ss = calloc(1, sizeof(symbol_sets_t ));
    symbol_sets_t  *kk = ss;
    for (size_t i=0; i<size; i++){
        ss->current = syms[i];
        ss->next = calloc(1, sizeof(symbol_sets_t ));
        ss = ss->next;
    }
    return kk;
}

void print_symbol_sets(char * header, symbol_sets_t  * s) {
    symbol_sets_t  *t = s;
    printf("%s ", header);
    while(t->next){
        printf("%d ", t->current.entry);
        t = t-> next;
    }
    printf("\n");
}

prod_list_t * get_productions(symbol_entry_t *sym){
    if (sym->flag!=NTerm){return NULL;}
    prod_list_t *pl = calloc(1, sizeof(prod_list_t));
    prod_list_t *result = pl;
    for (int i=0;i<GrammarCount;i++) {

        if (Grammar[i].body[0].entry==sym->entry) {
            pl->current = Grammar[i];
            pl->next = calloc(1, sizeof(prod_list_t));
            pl = pl->next;
        }
    }
    return result;
}

pitem_t * build_pitem_t(production_t *prod, symbol_entry_t pos, symbol_entry_t follow) {
    pitem_t *p = calloc(1, sizeof(pitem_t));
    p->pnum = prod->pnum;
    p->dot = pos;
    p->follow = follow;
    return p;
}

void print_pitem_t(pitem_t *item) {
    __uint128_t g = item->pnum;
    printf ("0x%16llx%15llx  ", (uint64_t) (g >> 64), (uint64_t) g);
    printf("Pitem: ");
    for (int c =0; c<14; c++){
        if (!(item->body[c].entry == 0 && c>0)){
            printf("%-4d", item->body[c].entry);
        } else {printf("    ");}
    }
    printf(" | %d", item->dot.entry);
    printf(" | %d\n", item->follow.entry);
}

void print_pitem_t_str(pitem_t *item) {
    int c =0 ;
    printf("[%s] ", SymbolTable[(int)item->follow.entry].name);
    while (!(item->body[c].entry == 0 && c>0) ) {
        if (c==item->dot.entry+1){printf(". ");}
        printf("%s ", SymbolTable[(int)item->body[c].entry].name);
        if (c==0) {printf("-> ");}
        c += 1;
    }
    if (c==item->dot.entry+1){printf(" . ");}
    printf("\n");

}
