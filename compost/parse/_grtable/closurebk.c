//
//Created by DannyV on 2018-12-10.
//

#include <stdlib.h>

#include "symbol.h"
#include "firstsets.h"
#include "closure.h"
#include "Python.h"

static int cmpfunc (const void * a, const void * b) {
   if ( ((pitem_t*)a)->pnum > ((pitem_t*)b)->pnum ) {return 1;}
   else {return -1;}
}

closure_t * build_closure(pitem_list_t * item_list, size_t itm_cnt,
                          sym_ent_t * accepts, size_t acc_cnt)
{
    closure_t * closure = (closure_t *) PyMem_Calloc(1, sizeof(closure_t));

    closure->itm_cnt = itm_cnt;
    closure->acc_cnt = acc_cnt;
    closure->goto_cnt = 0;

    closure->items = (pitem_t *) PyMem_Calloc(itm_cnt, sizeof(pitem_t));
    //closure->gotos = (goto_t *) PyMem_Calloc(1, sizeof(goto_t));
    closure->accepts = (sym_ent_t *) PyMem_Calloc(acc_cnt, sizeof(sym_ent_t));
    //memcpy(closure->items, items, itm_cnt*sizeof(pitem_t));
    //memcpy(closure->accepts, accepts, acc_cnt*sizeof(sym_ent_t));
    for (int i=0;i<acc_cnt;i++){
        closure->accepts[i] = accepts[i];
    }
    pitem_t * ptr = closure->items;
    while (item_list->next){
        *ptr = item_list->item;
        ptr += 1;
        item_list = item_list->next;
    }
    mergesort(closure->items, itm_cnt, sizeof(pitem_t), cmpfunc);

    return closure;
}

void destroy_closure(closure_t * closure){
    if (closure->items){
        PyMem_Free(closure->items);
        closure->items = NULL;
    }
    if (closure->gotos) {
        PyMem_Free(closure->gotos);
        closure->gotos = NULL;
    }
    if (closure->accepts){
        PyMem_Free(closure->accepts);
        closure->accepts = NULL;
    }
    PyMem_Free(closure);
}

pitem_t build_pitem(prod_t prod, sym_ent_t pos, sym_ent_t follow) {
    pitem_t p ;
    p.pnum = prod.pnum;
    p.dot = pos;
    p.follow = follow;
    return p;
}

pitem_list_t * new_pitem_list(void){
    pitem_list_t * new = (pitem_list_t *)PyMem_Calloc(1, sizeof(pitem_list_t));
    return new;
}

void append_pitem(pitem_t item, pitem_list_t ** tail){
    (*tail)->item = item;
    (*tail)->next = (pitem_list_t *)PyMem_Calloc(1, sizeof(pitem_list_t));
    (*tail) = (*tail)->next;
}

static void destroy_pitem_list(pitem_list_t * plist){
    pitem_list_t * tmp;
    while((tmp=plist)!=NULL){
        plist = plist->next;
        PyMem_Free(tmp);
    }
}

static int accepted_symbol(sym_ent_t ent, sym_ent_t * acceptp){
    for (int i=0; i<SymCount; i++) {
        if (acceptp[i].index == ent.index){ return 1;}
    }
    return 0;
}

static void append_nf_parse(sym_ent_t nterm, sym_ent_t follow, nf_list_t **tail){
    (*tail)->nterm = nterm;
    (*tail)->follow = follow;
    nf_list_t * p = (nf_list_t *) PyMem_Calloc(1, sizeof(nf_list_t));
    //nf_list_t * p = (nf_list_t *) PyMem_Calloc(1, sizeof(nf_list_t));
    if (!p) {printf("No mem");}
    (*tail)->next = p;
}

static int nf_parsed(sym_ent_t nterm, sym_ent_t follow, nf_list_t * nf_parse){
    while (nf_parse->next) {
        if (nterm.index == nf_parse->nterm.index &&
            follow.index == nf_parse->follow.index) { return 1; }
        nf_parse = nf_parse->next;
    }
    printf("----- %d %d\n", nterm.index, follow.index);
    append_nf_parse(nterm, follow, &nf_parse);
    return 0;
}



static void destroy_nf_parse(nf_list_t *nf_parse){
    nf_list_t * tmp;
    while((tmp=nf_parse)!=NULL){
        nf_parse = nf_parse->next;
        PyMem_Free(tmp);
    }
}

closure_t * get_closure(pitem_list_t * items){
    int itm_cnt = 0, acc_cnt = 0;
    sym_ent_t accepts[SymCount];

    //    memset(gotos, 0, SymCount*sizeof(goto_t));
    memset(accepts, 0, SymCount*sizeof(sym_ent_t));

    /* for (int i=0; i<SymCount;i++){               // init internal space.
        gotos[i].entry.index=0;
        gotos[i].closure = NULL;
        accepts[i].index = 0;
    } */

    nf_list_t * nf_parse = (nf_list_t *) PyMem_Calloc(1, sizeof(nf_list_t));
    //nf_list_t * nf_tail = nf_parse;

    //pitem_list_t * items = new_pitem_list();        // init closure items list.
    pitem_list_t * qiter = items, * qtail = items;
    while(qtail->next){
        //append_pitem(start_items->item, qtail);
        qtail = qtail->next;
        itm_cnt += 1;
    }

    while (qiter->next) {
        pitem_t item = qiter->item;
        sym_ent_t entry = item.body[item.dot.index+1];
        if (!accepted_symbol(entry, &accepts)) {
            accepts[acc_cnt] = entry;
            acc_cnt += 1;
        }
        if (entry.index && entry.type == NTERM){
            sym_ent_t suffix = item.body[item.dot.index + 2].index ?
                               item.body[item.dot.index + 2] : item.follow ;
            firsts_t firsts = {{0}};
            get_first_sets(suffix, &firsts);
            int fst_cnt = 0;
            sym_ent_t posit = {{0}};
            while (firsts[fst_cnt].index){
                printf("entry:%d first:%d nterm:%d follow:%d ", entry.index,
                        firsts[fst_cnt].index, nf_parse->nterm.index,
                        nf_parse->follow.index);
                if (!nf_parsed(entry, firsts[fst_cnt], nf_parse)){
                    for (size_t i=0;i<GramCount;i++){
                        if (GramTable[i].body[0].index==entry.index){
                            pitem_t newitem = build_pitem(GramTable[i], posit,
                                                          firsts[fst_cnt]);
                            append_pitem(newitem, &qtail);
                            //qtail = qtail->next;
                            itm_cnt += 1;
                        }
                    }
                }
                fst_cnt += 1;
            }
        }
        qiter = qiter->next;
    }
    closure_t * result = build_closure(items, itm_cnt, &accepts, acc_cnt);
    destroy_nf_parse(nf_parse);
    destroy_pitem_list(items);
    return result;
}
