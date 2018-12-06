//
//  Created by DannyV on 2018/11/27.
//  Copyright © 2018 YuDan. All rights reserved.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "symbol.h"
#include "grammar.h"
#include "closure.h"

static int adds(int a, int b){
    if (a==1) {return adds(b,b);}
    else{return b+b;}
}

static void test_sentry_find(void) {
    char * name = "declaration-specifiers";
    symbol_t s = {.type=NTerm, .name=name};
    symbol_entry_t e = sentry_find(s);
    printf("Symbol: %s, entry: %d\n", s.name, (int)e.entry);
}


static void test_union_symbol_sets(void) {
    symbol_entry_t syma[] = {{.entry=100}};
    symbol_entry_t sym2 = {.entry=199};
    symbol_sets_t  * s = symbol_sets_create(syma, 1);
    symbol_sets_add(sym2, s);
    symbol_entry_t symb[] = {{.entry=101}};
    symbol_sets_t  * s2 = symbol_sets_create(symb, 1);
    symbol_sets_t  * s3 = union_symbol_sets(s, s2);

    print_symbol_sets("Union s and s2:", s3);
}

static void test_first_sets_proc(void) {
    symbol_entry_t se = {.entry=0};
    symbol_sets_t  * n = first_sets_proc(&se);

    print_symbol_sets("First sets proc 0:", n);
}

static void test_first_sets(void) {
    symbol_entry_t se = {.entry=0};
    symbol_sets_t  * n = first_sets(&se);
    print_symbol_sets("First sets proc 0:", n);
}

static void test_get_closure(void) {
    printf("Test get_closure:\n");
    symbol_entry_t posit = {.entry=0};
    symbol_t sym = symbol_create(Value, "$");
    symbol_entry_t sentry = sentry_find(sym);
    pitem_t *startitem = build_pitem_t(&Grammar[0], posit, sentry);
    closure_list_t *start = calloc(1, sizeof(closure_list_t));
    start->item = *startitem;
    start->next = calloc(1, sizeof(closure_list_t));
    closure_t *t = get_closure(start, 1);
    printf("length:%d\n", t->length);
    printf("eq_closure_t: %d\n", eq_closure_t(t, t));
    print_closure_t("closure_t:", t);
    symbol_entry_t se = {.entry=128};
    closure_t *t2 = goto_closure(t, se);
    print_closure_t("closure_t:\n", t2);
}

static void test_closure_collection(void) {
    col_chain_t * cc = closure_collection();
    col_chain_t * c = cc;
    int length = 0;
    while (cc->next) {
        length += 1;
        cc = cc->next;
    }
    printf("Length: %d\n",length);
}

int tests (void) {

    printf("%d\n", adds(1,3));

    test_sentry_find();

    test_union_symbol_sets();

    test_first_sets_proc();

    test_first_sets();

    test_get_closure();

    time_t start,end;
    time(&start);
    test_closure_collection();
    time(&end);

    printf("CTESTS_END: %lf seconds costs\n\n", difftime(end,start));

    return 0;
}

