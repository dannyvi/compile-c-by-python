//
// Created by DannyV on 2018-11-28.
//


#include <stdlib.h>
#include "syntax_table.h"

production *Grammar;
int GrammarCount = 0;


void Grammar_init(size_t size){
    Grammar = calloc(size, sizeof(production));
}

void Grammar_add(production prod){
    Grammar[GrammarCount] = prod;
    GrammarCount += 1;
}

void Grammar_print(void) {
    for (int i=0;i<GrammarCount;i++) {
        production p = Grammar[i];
        printf("Prd %d: ",i);
        for (int j=0;j<14;j++){
            if (!(p.body[j].entry == 0 && j>0 ))
            printf("%d ", p.body[j].entry);
        }
        printf("\n");
    }
}

int entry_in_symbol_sets(symbol_entry sym, symbol_sets *ss){
    symbol_sets *c = ss;
    do {
        if (c->current.entry == sym.entry){ return 1; }
        c = c->next;
    } while (c);
    return 0;
}

void symbol_sets_link(symbol_sets *seta, symbol_sets *setb){
    symbol_sets *c = seta;
    while (c->next) {
        c = c->next;
    }
    c->current = setb->current;
    c->next = setb->next;
}

symbol_sets* union_symbol_sets(symbol_sets *seta, symbol_sets *setb){
    while(entry_in_symbol_sets(setb->current, seta)){
        if (setb->next) {setb = setb->next;}
        else {return seta;}
    }
    symbol_sets *c = setb;
    while (c->next) {
        //printf("CURRENT: %d", c->current.entry);
        if (entry_in_symbol_sets(c->current, seta)) {
                c->current = c->next->current;
                free(c->next);
                c->next = c->next->next;
        }
        else {
            c = c->next;
        }

    }
    if (setb) {symbol_sets_link(seta, setb);}
    return seta;
}

void symbol_sets_add(symbol_entry sym, symbol_sets * sets){
    symbol_sets *s = sets;
    if (!s->next){
        s->current = sym;
        s->next = calloc(1, sizeof(symbol_sets));
    }
    else {
        while (s->next) {
            s = s->next;
        }
        s->current = sym;
        s->next = calloc(1, sizeof(symbol_sets));
    }
}
symbol_sets * new_symbol_sets(void) {
    symbol_sets *ss = calloc(1, sizeof(symbol_sets));
    return ss;
}
symbol_sets * symbol_sets_create(symbol_entry syms[], size_t size){
    symbol_sets *ss = calloc(1, sizeof(symbol_sets));
    symbol_sets *kk = ss;
    for (size_t i=0; i<size; i++){
        ss->current = syms[i];
        ss->next = calloc(1, sizeof(symbol_sets));
        ss = ss->next;
    }
    return kk;
}

void ss_print(char * header, symbol_sets * s) {
    symbol_sets *t = s;
    printf("\n%s:", header);
    while(t->next){
        printf("%d ", t->current.entry);
        t = t-> next;
    }
    printf("\n");
}

prod_list * get_productions(symbol_entry *sym){
    if (sym->flag!=NTerm){return NULL;}
    prod_list *pl = calloc(1, sizeof(prod_list));
    prod_list *result = pl;
    for (int i=0;i<GrammarCount;i++) {

        if (Grammar[i].body[0].entry==sym->entry) {
            pl->current = Grammar[i];
            pl->next = calloc(1, sizeof(prod_list));
            pl = pl->next;
        }
    }
    return result;
}

static symbol_sets * get_entry_headers(symbol_entry * sym) {
    prod_list * pl = get_productions(sym);
    symbol_sets *s = calloc(1, sizeof(symbol_sets));
    while (pl->next) {
        production p = pl->current;
        symbol_entry sentry = p.body[1];
        if (!s->next) {
            symbol_sets_add(sentry, s);
        } else {
            if (!entry_in_symbol_sets(sentry, s)){
                symbol_sets_add(sentry, s);
            }
        }
        pl = pl->next;
    }
    return s;
}

symbol_sets * first_sets(symbol_entry * sym){
    if (sym->flag != NTerm){
        symbol_sets * s = symbol_sets_create(sym, 1);
        return s;
    }
    else {
        symbol_sets *sets, *queue,  *terms;
        sets = new_symbol_sets();
        terms = new_symbol_sets();

        queue = symbol_sets_create(sym, 1);

        while (queue->next) {
            symbol_entry current = queue->current;
            if (!sets || !entry_in_symbol_sets(current, sets)) {
                symbol_sets_add(current, sets);
                if (current.flag!=NTerm){
                    if (!terms || !entry_in_symbol_sets(current, terms)){
                        symbol_sets_add(current, terms);
                    }
                } else {
                symbol_sets *headers = get_entry_headers(&current);
                while(headers->next){
                    if(!entry_in_symbol_sets(headers->current, sets)){
                        symbol_sets_add(headers->current, queue);
                    }
                    free(headers);
                    headers = headers->next;
                }}
            }
            free(queue);
            queue = queue->next;
        }
        return terms;
    }
}
