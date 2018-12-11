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
    sym_ent_t e = sentry_find(s);
    printf("Symbol: %s, entry: %d\n", s.name, (int)e.id);
}


static void test_union_symbol_sets(void) {
    sym_ent_t syma[] = {{.id=100}};
    sym_ent_t sym2 = {.id=199};
    symt_list_t  * s = symbol_sets_create(syma, 1);
    symbol_sets_add(sym2, s);
    sym_ent_t symb[] = {{.id=101}};
    symt_list_t  * s2 = symbol_sets_create(symb, 1);
    symt_list_t  * s3 = union_symbol_sets(s, s2);

    print_symbol_sets("Union s and s2:", s3);
}

static void test_first_sets_proc(void) {
    sym_ent_t se = {.id=0};
    symt_list_t  * n = first_sets_proc(&se);

    print_symbol_sets("First sets proc 0:", n);
}

static void test_first_sets(void) {
    sym_ent_t se = {.id=0};
    symt_list_t  * n = first_sets(&se);
    print_symbol_sets("First sets proc 0:", n);
}

static void test_get_closure(void) {
    printf("Test get_closure:\n");
    sym_ent_t posit = {.id=0};
    symbol_t sym = symbol_create(Value, "$");
    sym_ent_t sentry = sentry_find(sym);
    pitem_t startitem = build_pitem_t(&Grammar[0], posit, sentry);
    pitem_list_t *start = PyMem_Calloc(1, sizeof(pitem_list_t));
    start->item = startitem;
    start->next = PyMem_Calloc(1, sizeof(pitem_list_t));
    closure_t *t = get_closure(start, 1);
    printf("length:%d\n", t->length);
    printf("eq_closure_t: %d\n", eq_closure_t(t, t));
    print_closure_t("closure_t:", t);
    sym_ent_t se = {.id=128};
    closure_t *t2 = goto_closure(t, se);
    print_closure_t("closure_t:\n", t2);
}

static void test_closure_collection(void) {
    clos_list_t * cc = closure_collection();
    //clos_list_t * c = cc;
    int length = 0;
    while (cc->next) {
        length += 1;
        cc = cc->next;
    }
    //print_collection_t(c);
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

