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


int tests (void) {
    symbol sym[] = {{NTerm, "symbol1"},{NTerm, "symbol21"},
                    {Term, "terminal-symbol-1"},{Value, "terminal2"},
                    {Term, "terminal32456"}};
    build_symbol_table(sym, sizeof(sym)/sizeof(symbol));
    printf("%s\n%s\n%s\n%s\n%s\n", SymbolTable[0].name, SymbolTable[1].name,
           SymbolTable[128].name, SymbolTable[192].name, SymbolTable[129].name);
    SymbolEntry_print();

    printf("\nLen:%d\n", SymbolEntry_len());
    assert(SymbolTable[0].name[0]=='s');
    assert(SymbolTable[1].name[0]=='s');
    symbol_entry e = sentry_find(sym[4]);
    printf("Entry: %d\n", e.entry);

    //production p = production_build(sym, 5);
    //for (int i=0;i<5;i++){
    //    printf("%d ", p.body[i].entry);
    // }
    printf("\nCTESTS_END\n");
    return 0;
}

