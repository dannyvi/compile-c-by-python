//
// Created by DannyV on 2018-12-1.
//

#include <stdlib.h>
#include "Python.h"

#include "symbol.h"
#include "grammar.h"
#include "firstsets.h"
#include "closure.h"


pitem_t build_pitem_t(prod_t *prod, sym_ent_t pos, sym_ent_t follow) {
    pitem_t p ;
    p.pnum = prod->pnum;
    p.dot = pos;
    p.follow = follow;
    return p;
}


int item_in_closure(pitem_t item, pitem_list_t * set){
    pitem_list_t *l = set;
    while (l->next) {
        if (item.pnum==l->item.pnum) {return 1;}
        l = l->next;
    }
    return 0;
}

void add_cl(pitem_t itm, pitem_list_t *clp) {
    clp->item = itm;
    clp->next = PyMem_Calloc(1, sizeof(pitem_list_t));
}


int cmpfunc (const void * a, const void * b) {
   if ( ((pitem_t*)a)->pnum > ((pitem_t*)b)->pnum ) {return 1;}
   else {return -1;}
}

nterm_follow_t new_clos_entry(sym_ent_t nterm, sym_ent_t follow) {
    nterm_follow_t c_ent;
    c_ent.nterm = nterm;
    c_ent.follow = follow;
    return c_ent;
}

int entry_in_clos_sets(nterm_follow_t l, nf_list_t  *c){
    while (c)
    {
        if (c->entry.nterm.index == l.nterm.index &&
            c->entry.follow.index== l.follow.index){ return 1; }
        c = c->next;
    };
    return 0;
}


void clos_entry_sets_add(nterm_follow_t sym, nf_list_t * s){
    if (!s->next){
        s->entry = sym;
        s->next = PyMem_Calloc(1, sizeof(sym_ent_list_t ));
    }
    else {
        while (s->next) {
            s = s->next;
        }
        s->entry = sym;
        s->next = PyMem_Calloc(1, sizeof(sym_ent_list_t ));
    }
}

static void PyMem_Free_closure_list(pitem_list_t* cl){
    pitem_list_t * exchg;
    while((exchg=cl)!=NULL) {
        cl = cl->next;
        PyMem_Free(exchg);
    }
}

static closure_t * build_closure(pitem_list_t *set, int label, int length, sym_ent_list_t *accept_symbols) {
    closure_t *t = PyMem_Calloc(1, sizeof(closure_t));

    t->label = label;
    t->length = length;
    t->items = PyMem_Calloc(length, sizeof(pitem_t));
    pitem_t *pp = t->items;
    while (set->next) {
        *pp = set->item;
        pp += 1;
        set = set->next;
    }
    mergesort(t->items, length, sizeof(pitem_t), cmpfunc);
    t->accept_symbols = accept_symbols;
    return t;
}

closure_t * get_closure(pitem_list_t * clist, int label) {
    pitem_list_t *queue, *set, *qp, *countq, *cp, *curr;
    sym_ent_list_t *accept_symbols = new_sym_ent_list();
    nf_list_t *added = PyMem_Calloc(1, sizeof(nf_list_t));
    cp = clist;
    queue = PyMem_Calloc(1, sizeof(pitem_list_t));
    set = queue; //PyMem_Calloc(1, sizeof(pitem_list_t));
    qp = queue;
    int length = 0;
    while (cp->next) {
        add_cl(cp->item, qp);
        qp = qp->next;
        length += 1;
        cp = cp->next;
    }

    PyMem_Free_closure_list(clist);
    countq = queue;
    while (countq->next) {
        pitem_t item = countq->item;
        sym_ent_t sentry =item.body[(int)item.dot.index+1];
        //add accept input symbols.
        if (!entry_in_sym_ent_list(sentry, accept_symbols)){
            sym_ent_list_add(sentry, accept_symbols);
        }

        //add productions.
        if (sentry.index && sentry.type==NTERM) {
            sym_ent_t suffix;
            if(item.body[(int)(item.dot.index + 2)].index){
                suffix = item.body[(int)(item.dot.index + 2)];
            } else {
                suffix = item.follow;
            }
            sym_ent_list_t  *tms = get_first_sets(&suffix);
            sym_ent_list_t  *itert, *frtms;
            sym_ent_t posit;
            posit.index = 0;
            itert = tms;
            while (itert->next) {
                nterm_follow_t c_ent = new_clos_entry(sentry, itert->entry);
                if (!entry_in_clos_sets(c_ent, added)){
                    clos_entry_sets_add(c_ent, added);
                    pitem_list_t *prods = get_productions(&sentry);
                    pitem_list_t *frprd, *chgfr;
                    frprd = prods;
                    while(prods->next) {
                        pitem_t newitem = build_pitem_t(&(prods->item), posit, itert->entry);
                        //if (!item_in_closure(newitem, set)) {
                            add_cl(newitem, qp);
                            qp = qp->next;
                            length += 1;
                        //}
                        prods = prods->next;
                    }
                    // PyMem_Free productions chain;
                    while((chgfr=frprd)!=NULL){
                        frprd = frprd->next;
                        PyMem_Free(chgfr);
                    }
                    prods=chgfr=frprd=NULL;
                }
                itert = itert->next;
            }
            // PyMem_Free terminals chain;
            while((frtms=tms)!=NULL){
                tms = tms->next;
                PyMem_Free(frtms);
            }
            tms=frtms=itert=NULL;
        }
        countq = countq->next;
    }

    closure_t *t = build_closure(set, label, length, accept_symbols);

    while ((curr = queue) != NULL) {
        queue = queue->next;
        PyMem_Free (curr);
    }
    queue=set=qp=countq=cp=curr=NULL;

    nf_list_t *fradded ;
    while((fradded=added)!=NULL){
        added = added->next;
        PyMem_Free(fradded);
    }

    return t;
}

