#include <stdlib.h>
#include "symbol.h"
#include "grammar.h"
#include "closure.h"

ntfirsts NTFirst[128];

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

symbol_sets * first_sets_proc(symbol_entry * sym){
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

void init_NTFirst(void) {
    symbol_entry * sentry = calloc(1, sizeof(symbol_entry)) ;
    symbol_sets * set;
    ntfirsts * flist;
    for (int i=0;i<128;i++) {
        if (SymbolTable[i].name[1]!=0){
            sentry->entry = i;
            flist = &NTFirst[i];
            set = first_sets_proc(sentry);
            int counter = 0;
            while (set->next) {
                *((symbol_entry *)flist+counter*sizeof(symbol_entry)) = set->current;
                counter += 1;
                set = set->next;
            }
        }
    }
}

void NTFirst_print(void) {
    ntfirsts *flist;
    printf("First sets from %s\n", __FILE__);
    for (int i=0; i<128; i++) {
        flist = &NTFirst[i];
        if (((symbol_entry *)flist)->entry){
            int counter = 0;
            printf("Fists %d: ", i);
            while ( ((symbol_entry *)flist+counter*sizeof(symbol_entry))->entry ) {
                printf("%d ", ((symbol_entry *)flist+counter*sizeof(symbol_entry))->entry );
                counter += 1;
            }
            printf("\n");
        }
    }
}


symbol_sets * first_sets(symbol_entry * sym){
    if (sym->flag != NTerm){
        symbol_sets * s = symbol_sets_create(sym, 1);
        return s;
    }
    else {
        int entry = (int) sym->entry;
        //ntfirsts f = NTFirst[entry];
        int counter = 0;
        symbol_sets *set = calloc(1,sizeof(symbol_sets));
        symbol_sets *sp = set;
        while (NTFirst[entry][counter].entry){
            sp->current = NTFirst[entry][counter];
            sp->next = calloc(1, sizeof(symbol_sets));
            sp = sp->next;
            counter += 1;
        }
        return set;
    }}
