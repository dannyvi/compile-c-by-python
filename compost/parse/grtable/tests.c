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
#include "grammar.h"
#include "closure.h"

static int adds(int a, int b){
    if (a==1) {return adds(b,b);}
    else{return b+b;}
}

static void test_union_symbol_sets(void) {
    symbol_entry syma[] = {{.entry=100}};
    symbol_entry sym2 = {.entry=199};
    symbol_sets * s = symbol_sets_create(syma, 1);
    symbol_sets_add(sym2, s);
    symbol_entry symb[] = {{.entry=101}};
    symbol_sets * s2 = symbol_sets_create(symb, 1);
    symbol_sets * s3 = union_symbol_sets(s, s2);

    print_symbol_sets("Union s and s2:", s3);
}

static void test_first_sets_proc(void) {
    symbol_entry se = {.entry=12};
    symbol_sets * n = first_sets_proc(&se);

    print_symbol_sets("First sets proc 12:", n);
}

static void test_first_sets(void) {
    symbol_entry se = {.entry=12};
    symbol_sets * n = first_sets(&se);
    print_symbol_sets("First sets proc 12:", n);
}

int tests (void) {

    printf("%d\n", adds(1,3));

    test_union_symbol_sets();

    test_first_sets_proc();

    init_NTFirst();

    NTFirst_print();

    test_first_sets();

    printf("CTESTS_END\n\n");

    return 0;
}

