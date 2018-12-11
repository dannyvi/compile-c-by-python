//
// Created by DannyV on 2018-11-28.
//

#include <stdlib.h>
#include <string.h>
#include "Python.h"
#include "grammar.h"

production_t *Grammar;
int GrammarCount = 0;


void Grammar_init(size_t size){
    Grammar = PyMem_Calloc(size, sizeof(production_t));
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
            if (!(p.body[j].id == 0 && j>0 ))
            printf("%d ", p.body[j].id);
        }
        printf("\n");
    }
    printf("\n\n");
}

int entry_in_symbol_sets(sym_ent_t sym, symt_list_t  *ss){
    symt_list_t  *c = ss;
    do {
        if (c->entry.id == sym.id){ return 1; }
        c = c->next;
    } while (c);
    return 0;
}

void symbol_sets_link(symt_list_t  *seta, symt_list_t  *setb){
    symt_list_t  *c = seta;
    while (c->next) {
        c = c->next;
    }
    c->entry = setb->entry;
    c->next = setb->next;
}

symt_list_t * union_symbol_sets(symt_list_t  *seta, symt_list_t  *setb){
    while(entry_in_symbol_sets(setb->entry, seta)){
        if (setb->next) {setb = setb->next;}
        else {return seta;}
    }
    symt_list_t  *c = setb;
    while (c->next) {
        if (entry_in_symbol_sets(c->entry, seta)) {
                c->entry = c->next->entry;
                c->next = c->next->next;
        }
        else {
            c = c->next;
        }

    }
    if (setb) {symbol_sets_link(seta, setb);}
    return seta;
}

void symbol_sets_add(sym_ent_t sym, symt_list_t * sets){
    symt_list_t  *s = sets;
    if (!s->next){
        s->entry = sym;
        s->next = PyMem_Calloc(1, sizeof(symt_list_t ));
    }
    else {
        while (s->next) {
            s = s->next;
        }
        s->entry = sym;
        s->next = PyMem_Calloc(1, sizeof(symt_list_t ));
    }
}


symt_list_t  * new_symbol_sets(void) {
    symt_list_t  *ss = PyMem_Calloc(1, sizeof(symt_list_t ));
    return ss;
}

symt_list_t  * symbol_sets_create(sym_ent_t syms[], size_t size){
    symt_list_t  *ss = PyMem_Calloc(1, sizeof(symt_list_t ));
    symt_list_t  *kk = ss;
    for (size_t i=0; i<size; i++){
        ss->entry = syms[i];
        ss->next = PyMem_Calloc(1, sizeof(symt_list_t ));
        ss = ss->next;
    }
    return kk;
}

void print_symbol_sets(char * header, symt_list_t  * s) {
    symt_list_t  *t = s;
    printf("%s ", header);
    while(t->next){
        printf("%d ", t->entry.id);
        t = t-> next;
    }
    printf("\n");
}

prod_list_t * get_productions(sym_ent_t *sym){
    if (sym->flag!=NTerm){return NULL;}
    prod_list_t *pl = PyMem_Calloc(1, sizeof(prod_list_t));
    prod_list_t *result = pl;
    for (int i=0;i<GrammarCount;i++) {

        if (Grammar[i].body[0].id==sym->id) {
            pl->current = Grammar[i];
            pl->next = PyMem_Calloc(1, sizeof(prod_list_t));
            pl = pl->next;
        }
    }
    return result;
}

pitem_t build_pitem_t(production_t *prod, sym_ent_t pos, sym_ent_t follow) {
    pitem_t p ;
    p.pnum = prod->pnum;
    p.dot = pos;
    p.follow = follow;
    return p;
}

void print_pitem_t(pitem_t *item) {
    __uint128_t g = item->pnum;
    printf ("Pitem(0x%16llx%15llx): ", (uint64_t) (g >> 64), (uint64_t) g);
    for (int c =0; c<14; c++){
        if (!(item->body[c].id == 0 && c>0)){
            printf("%-4d", item->body[c].id);
        } else {printf("    ");}
    }
    printf(" | %d", item->dot.id);
    printf(" | %d\n", item->follow.id);
}

void print_pitem_t_str(pitem_t *item) {
    int c =0 ;
    printf("[%s] ", SymbolTable[(int)item->follow.id].name);
    while (!(item->body[c].id == 0 && c>0) ) {
        if (c==item->dot.id+1){printf(". ");}
        printf("%s ", SymbolTable[(int)item->body[c].id].name);
        if (c==0) {printf("-> ");}
        c += 1;
    }
    if (c==item->dot.id+1){printf(" . ");}
    printf("\n");

}
