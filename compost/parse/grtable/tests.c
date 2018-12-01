//
//  tests.c
//  ctest
//
//  Created by DannyV on 2018/11/27.
//  Copyright © 2018 YuDan. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "symbol.h"
#include "syntax_table.h"

int adds(int a, int b){
    if (a==1) {return adds(b,b);}
    else{return b+b;}
}

int tests (void) {

    printf("%d", adds(1,3));
    symbol_entry syma[] = {{.entry=100}};
    symbol_entry sym2 = {.entry=199};
    symbol_sets * s = symbol_sets_create(syma, 1);
    symbol_sets_add(sym2, s);
    symbol_entry symb[] = {{.entry=101}};
    symbol_sets * s2 = symbol_sets_create(symb, 1);
    symbol_sets * s3 = union_symbol_sets(s, s2);
    symbol_entry se = {.entry=12};
    symbol_sets * n = first_sets(&se);

    while(n->next) {
        printf("sets: %d\n", n->current.entry);
        n = n->next;
    }

    printf("\nCTESTS_END\n\n");
    return 0;
}

