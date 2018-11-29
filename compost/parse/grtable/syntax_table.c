//
// Created by DannyV on 2018-11-28.
//


#include <stdlib.h>
#include "syntax_table.h"

production *Grammar;
int GrammarCount = 0;

/*production production_build(symbol* prod, size_t size) {
    symbol_entry s_prod[size];
    for (int i=0;i<(int)size;i++){
        symbol_entry n = sentry_find(prod[i]);
        s_prod[i] = n;
    }
    production p = {.pnum=*(long double *)s_prod};
    return p;
}*/

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
            if (p.body[j].entry != 0)
            printf("%d ", p.body[j].entry);
        }
        printf("\n");
    }
}
