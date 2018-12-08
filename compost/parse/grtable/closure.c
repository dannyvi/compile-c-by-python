//
// Created by DannyV on 2018-12-1.
//

#include <stdlib.h>
#include "symbol.h"
#include "grammar.h"
#include "closure.h"

#include "Python.h"

ntfirsts NTFirst[128];

static symbol_sets_t  * get_entry_headers(symbol_entry_t * sym) {
    prod_list_t * pl = get_productions(sym);
    symbol_sets_t  *s = calloc(1, sizeof(symbol_sets_t ));
    while (pl->next) {
        production_t p = pl->current;
        symbol_entry_t sentry = p.body[1];
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

symbol_sets_t  * first_sets_proc(symbol_entry_t * sym) {
    if (sym->flag != NTerm){
        symbol_sets_t  * s = symbol_sets_create(sym, 1);
        return s;
    }
    else {
        symbol_sets_t  *sets, *queue,  *terms;
        sets = new_symbol_sets();
        terms = new_symbol_sets();

        queue = symbol_sets_create(sym, 1);

        while (queue->next) {
            symbol_entry_t current = queue->entry;
            if (!sets->next || !entry_in_symbol_sets(current, sets)) {
                symbol_sets_add(current, sets);
                if (current.flag!=NTerm){
                    if (!terms || !entry_in_symbol_sets(current, terms)){
                        symbol_sets_add(current, terms);
                    }
                }
                else {
                    symbol_sets_t  *headers = get_entry_headers(&current);
                    while(headers->next){
                        if(!entry_in_symbol_sets(headers->entry, sets)){
                            symbol_sets_add(headers->entry, queue);
                        }
                        headers = headers->next;
                    }
                }
            }
            queue = queue->next;
        }
        return terms;
    }
}

void init_NTFirst(void) {
    symbol_entry_t * sentry = calloc(1, sizeof(symbol_entry_t)) ;
    symbol_sets_t  * set, *frset;
    ntfirsts * flist;
    for (int i=0;i<128;i++) {
        if (SymbolTable[i].name[0]!=0 ){
            sentry->id = i;
            flist = &NTFirst[i];
            set = first_sets_proc(sentry);
            frset = set;
            int counter = 0;

            while (set->next) {
                *((symbol_entry_t *)flist+counter*sizeof(symbol_entry_t)) = set->entry;
                counter += 1;
                set = set->next;
            }
            free_symbol_sets(frset);
        }
    }
}

void NTFirst_print(void) {
    symbol_entry_t *flist;
    printf("First sets from %s\n", __FILE__);
    for (int i=0; i<128; i++) {
        flist = (symbol_entry_t *)&NTFirst[i];
        if ((flist)->id){
            int counter = 0;
            printf("Firsts %d: ", i);
            while (  (flist+counter*sizeof(symbol_entry_t))->id ) {
                printf("%d ", (flist+counter*sizeof(symbol_entry_t))->id );
                counter += 1;
            }
            printf("\n");
        }
    }
}

symbol_sets_t  * first_sets(symbol_entry_t * sym){
    if (sym->flag != NTerm){
        symbol_sets_t  * s = symbol_sets_create(sym, 1);
        return s;
    }
    else {
        int entry = (int) sym->id;
        int counter = 0;
        symbol_sets_t  *set = calloc(1,sizeof(symbol_sets_t ));
        symbol_sets_t  *sp = set;
        while (NTFirst[entry][counter].id){
            sp->entry = NTFirst[entry][counter];
            sp->next = calloc(1, sizeof(symbol_sets_t ));
            sp = sp->next;
            counter += 1;
        }
        return set;
    }
}

int item_in_closure(pitem_t item, closure_list_t * set){
    closure_list_t *l = set;
    while (l->next) {
        if (item.pnum==l->item.pnum) {return 1;}
        l = l->next;
    }
    return 0;
}

static void add_cl(pitem_t itm, closure_list_t *clp) {
    clp->item = itm;
    clp->next = calloc(1, sizeof(closure_list_t));
}

void print_closure_list_t(char * message, closure_list_t * clist) {
    closure_list_t * cl = clist;
    printf("%s", message);
    while (cl->next) {
        print_pitem_t(&cl->item);
        cl = cl->next;
    }
    printf("\n");
}

void print_closure_t(char * message, closure_t * ct) {
    printf("%s\n", message);
    if (ct->length==0){
        printf("EMPTY\n");
        return ;
    }
    pitem_t * p = ct->items;
    for (int i=0;i<ct->length;i++,p++){
        print_pitem_t(p);
    }
    printf("\n");
}

void print_closure_str(char * message, closure_t * ct) {
    printf("%s\n", message);
    if (ct->length==0){
        printf("EMPTY\n");
        return ;
    }
    pitem_t * p = ct->items;
    for (int i=0;i<ct->length;i++,p++){
        print_pitem_t_str(p);
    }
    printf("\n");
}

int cmpfunc (const void * a, const void * b) {
   if ( ((pitem_t*)a)->pnum > ((pitem_t*)b)->pnum ) {return 1;}
   else {return -1;}
}


clos_entry_t new_clos_entry(symbol_entry_t nterm, symbol_entry_t follow) {
    clos_entry_t c_ent;
    c_ent.nterm = nterm;
    c_ent.follow = follow;
    return c_ent;
}

int entry_in_clos_sets(clos_entry_t l, clos_entry_sets_t  *c){
    while (c)
    {
        if (c->entry.nterm.id == l.nterm.id &&
            c->entry.follow.id== l.follow.id){ return 1; }
        c = c->next;
    };
    return 0;
}


void clos_entry_sets_add(clos_entry_t sym, clos_entry_sets_t * s){
    if (!s->next){
        s->entry = sym;
        s->next = calloc(1, sizeof(symbol_sets_t ));
    }
    else {
        while (s->next) {
            s = s->next;
        }
        s->entry = sym;
        s->next = calloc(1, sizeof(symbol_sets_t ));
    }
}

static void free_closure_list(closure_list_t* cl){
    closure_list_t * exchg;
    while((exchg=cl)!=NULL) {
        cl = cl->next;
        free(exchg);
    }
}

static closure_t * build_closure(closure_list_t *set, int label, int length, symbol_sets_t *accept_symbols) {
    closure_t *t = calloc(1, sizeof(closure_t));

    t->label = label;
    t->length = length;
    t->items = calloc(length, sizeof(pitem_t));
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

closure_t * get_closure(closure_list_t * clist, int label) {
    closure_list_t *queue, *set, *qp, *countq, *cp, *curr;
    symbol_sets_t *accept_symbols = new_symbol_sets();
    clos_entry_sets_t *added = calloc(1, sizeof(clos_entry_sets_t));
    cp = clist;
    queue = calloc(1, sizeof(closure_list_t));
    set = queue; //calloc(1, sizeof(closure_list_t));
    qp = queue;
    int length = 0;
    while (cp->next) {
        add_cl(cp->item, qp);
        qp = qp->next;
        length += 1;
        cp = cp->next;
    }

    free_closure_list(clist);
    countq = queue;
    while (countq->next) {
        pitem_t item = countq->item;
        symbol_entry_t sentry =item.body[(int)item.dot.id+1];
        //add accept input symbols.
        if (!entry_in_symbol_sets(sentry, accept_symbols)){
            symbol_sets_add(sentry, accept_symbols);
        }
        //add productions.
        if (sentry.id && sentry.flag==NTerm) {
            symbol_entry_t suffix;
            if(item.body[(int)(item.dot.id + 2)].id){
                suffix = item.body[(int)(item.dot.id + 2)];
            } else {
                suffix = item.follow;
            }
            symbol_sets_t  *tms = first_sets(&suffix);
            symbol_sets_t  *itert, *frtms;
            symbol_entry_t posit;
            posit.id = 0;
            itert = tms;
            while (itert->next) {
                clos_entry_t c_ent = new_clos_entry(sentry, itert->entry);
                if (!entry_in_clos_sets(c_ent, added)){
                    clos_entry_sets_add(c_ent, added);
                    prod_list_t *prods = get_productions(&sentry);
                    prod_list_t *frprd, *chgfr;
                    frprd = prods;
                    while(prods->next) {
                        pitem_t newitem = build_pitem_t(&(prods->current), posit, itert->entry);
                        if (!item_in_closure(newitem, set)) {
                            add_cl(newitem, qp);
                            qp = qp->next;
                            length += 1;
                        }
                        prods = prods->next;
                    }
                    // free productions chain;
                    while((chgfr=frprd)!=NULL){
                        frprd = frprd->next;
                        free(chgfr);
                    }
                    prods=chgfr=frprd=NULL;
                }
                itert = itert->next;
            }
            // free terminals chain;
            while((frtms=tms)!=NULL){
                tms = tms->next;
                free(frtms);
            }
            tms=frtms=itert=NULL;
        }
        countq = countq->next;
    }

    closure_t *t = build_closure(set, label, length, accept_symbols);

    while ((curr = queue) != NULL) {
        queue = queue->next;
        free (curr);
    }
    queue=set=qp=countq=cp=curr=NULL;

    clos_entry_sets_t *fradded ;
    while((fradded=added)!=NULL){
        added = added->next;
        free(fradded);
    }

    return t;
}

int eq_closure_t(closure_t *a, closure_t *b) {
    if (a->length != b->length) {return 0;}
    pitem_t *ai = a->items;
    pitem_t *bi = b->items;
    for (int i=0;i<a->length; i++) {
        if (ai->pnum!=bi->pnum) {return 0;}
        ai += 1;
        bi += 1;
    }
    return 1;
}

/*
int closure_in_collection(closure_t *clos, col_chain_t *collection){
    col_chain_t *cc = collection;
    if (!cc->next){return -1;}
    while(cc->next){
        if (eq_closure_t(clos, &cc->c)){return cc->c.label;}
        cc = cc->next;
    }
    return -1;
}*/

closure_t ret_closure_in_collection(closure_t *clos, col_chain_t *collection){
    col_chain_t *cc = collection;
    closure_t ret;
    ret.label=-1;
    if (!cc->next){return ret;}
    while(cc->next){
        if (eq_closure_t(clos, &cc->c)){return cc->c;}
        cc = cc->next;
    }
    return ret;
}

closure_t * goto_closure(closure_t *clos, symbol_entry_t sentry) {
    closure_list_t *ss = calloc(1, sizeof(closure_list_t));
    closure_list_t *set = ss;
    pitem_t *ptm = clos->items;
    for (int i=0; i<clos->length; i++,ptm++) {
        int pos = (int)(ptm->dot.id);
        if(ptm->body[pos+1].id==sentry.id && sentry.id!=0){
            symbol_entry_t ent = {.id=pos+1};
            pitem_t newitem = build_pitem_t(ptm, ent, ptm->follow);
            add_cl(newitem, set);
            set = set->next;
        }
    }
    if (!ss->next) {
        closure_t * t = calloc(1, sizeof(closure_t));
        t->length= 0 ;
        t->items = NULL;
        return t;
    } else {
        return get_closure(ss, NONE_LABEL);
    }
}

static void add_clos(closure_t *t, col_chain_t *coll){
    coll->c = *t;
    coll->next = calloc(1, sizeof(col_chain_t));
}

static int has_in_goto_list(closure_t *clos, closure_t *goclos, symbol_entry_t * ent){
    if (!clos->goto_list) {return 0;}
    goto_list_t *g = clos->goto_list;
    while (g->next) {
        if (g->sym_index.id==ent->id && eq_closure_t(&g->closure, goclos)) {return 1;}
        g = g->next;
    }
    return 0;
}

static void add_goto_list(closure_t *clos, closure_t goclos, symbol_entry_t * ent){
    //not initialized condition
    if (!clos->goto_list) {
        goto_list_t *g = calloc(1, sizeof(goto_list_t));
        g->sym_index = *ent;
        g->closure = goclos;
        g->next = calloc(1, sizeof(goto_list_t));
        clos->goto_list = g;
        clos->goto_tail = g->next;
    }
    else {  // closure already has at least 1 goto target.
        if (!has_in_goto_list(clos, &goclos, ent)){
            goto_list_t *g = clos->goto_tail;
            g->sym_index = *ent;
            g->closure = goclos;
            g->next = calloc(1, sizeof(goto_list_t));
            clos->goto_tail = g->next;
        }
    }
}

col_chain_t * closure_collection(void) {
    int label = 0;
    col_chain_t * queue = calloc(1, sizeof(col_chain_t));
    col_chain_t * collection = queue;
    col_chain_t *qp, *countq;
    qp = queue;
    countq = queue;

    int length = 0;
    symbol_entry_t posit = {.id=0};
    symbol_t sym = symbol_create(Value, "$");
    symbol_entry_t sentry = sentry_find(sym);
    pitem_t startitem = build_pitem_t(&Grammar[0], posit, sentry);
    closure_list_t *start = calloc(1, sizeof(closure_list_t));
    start->item = startitem;
    start->next = calloc(1, sizeof(closure_list_t));
    closure_t *t = get_closure(start, label);

    add_clos(t, qp);

    qp = qp->next;

    length += 1;

    while (countq->next){

        closure_t *clos = &(countq->c);
        symbol_sets_t *ent = clos->accept_symbols;
        while(ent->next) {
            closure_t *goclos = goto_closure(clos, ent->entry);
            if (goclos->length>0) {
                //int golbl = closure_in_collection(goclos, collection);
                closure_t retclos = ret_closure_in_collection(goclos, collection);
                if (retclos.label == -1){
                    label += 1;
                    goclos->label=label;
                    add_clos(goclos, qp);

                    qp = qp->next;

                    length += 1;
                    add_goto_list(clos, *goclos, &ent->entry);
                }
                else {
                    //goclos->label=golbl;
                    add_goto_list(clos, retclos, &ent->entry);
                    symbol_sets_t *frsmb, *syms;
                    syms = goclos->accept_symbols;
                    while((frsmb=syms)!= NULL){
                        syms = syms->next;
                        free(frsmb);
                    }
                    frsmb = syms = NULL;
                    free(goclos->items);
                    free(goclos);
                    goclos = NULL;
                }
            }
            else {
                free(goclos);
                goclos=NULL;
            }
            ent = ent->next;
        }

        countq = countq->next;
    }
    //printf("Closure Collections: %d\n", length);

    return collection;
}

void print_collection_t(col_chain_t * c) {
    int counter = 0;
    while (c->next) {
        printf("Closure %d", c->c.label);
        print_closure_str(":",&c->c);
        c = c->next;
        counter += 1;
    }
    printf("Length: %d\n", counter);
}

int get_prod_number(pitem_t *item){
    production_t p = *item;
    p.dot.id = 0;
    p.follow.id=0;
    for (int i=0; i<GrammarCount; i++) {
        if (p.pnum==Grammar[i].pnum){return i;}
    }
    //never reach here;
    return -1;
}

static unsigned char SymbolAntiMap[256];

void init_anti_map(void) {
    unsigned char * anti_map = SymbolAntiMap;
    memset(anti_map, 0, 256);
    symbol_sets_t * se = &SymbolEntry;
    int counter = 0;
    while (se->next) {
        anti_map[se->entry.id] = counter;
        counter += 1;
        se = se->next;
    }
}


void write_list_line(closure_t *clos, PyObject *list) {
    action_t action = malloc(8*sizeof(char));
    int golabel, strlen;
    // shift actions
    goto_list_t *golist = clos->goto_list;
    if (golist) {
        while (golist->next){
            symbol_entry_t posit = golist->sym_index;
            golabel = golist->closure.label;
            strlen = snprintf( NULL, 0, "%d", golabel );
            posit.flag==NTerm ? snprintf( action, strlen + 1, "%d", golabel ) :
                                snprintf( action, strlen + 2, "s%d", golabel );
            PyObject * listitem = Py_BuildValue("s", action);
            PyList_SetItem(list, SymbolAntiMap[posit.id], listitem);
            golist = golist->next;
        }
    }
    // check reduce action in closure items;
    symbol_entry_t accept_entry = sentry_find(symbol_create(Value, "$"));
    pitem_t acc_item = {.body={{0},{1}}, .dot={1}, .follow=accept_entry};
    pitem_t *pitem = clos->items;
    for (int i=0; i<clos->length; i++,pitem++){
        if (acc_item.pnum == pitem->pnum){
            snprintf(action, 2, "%s", "$");
            PyObject * listitem = Py_BuildValue("s", action);
            PyList_SetItem(list, SymbolAntiMap[accept_entry.id], listitem);
        }
        else{
            int plen = 0;
            while(pitem->body[plen].id || plen==0){
                plen += 1;
            }
            if (pitem->dot.id == plen-1) {
                int number = get_prod_number(pitem);
                strlen = snprintf( NULL, 0, "%d", number );
                snprintf(action, strlen+2, "r%d", number);
                PyObject * listitem = Py_BuildValue("s", action);
                PyList_SetItem(list, SymbolAntiMap[pitem->follow.id], listitem);
            }
        }
    }
    free(action);
    action = NULL;
}

PyObject * get_states_list(col_chain_t *c, Py_ssize_t length) {
    col_chain_t *fr, *frxcg;
    fr=c;
    PyObject * result;
    init_anti_map();
    int sym_size = SymbolEntry_len();
    //use 8 chars for every action string.
    action_t action = malloc(8*sizeof(char));
    action = ".";

    // pass 1, initialize every element to error
    result = PyList_New(length);
    for (Py_ssize_t i=0; i<length; i++) {
        PyObject * line = PyList_New(sym_size);
        for (Py_ssize_t j=0; j<sym_size; j++){
            PyObject * elem = Py_BuildValue("s", action);
            PyList_SetItem(line, j, elem);
        }
        PyList_SetItem(result, i, line);
    }
    // pass 2, fill lines in closures of col_chain.
    while (c->next) {
        closure_t *clos = &(c->c);
        PyObject *item = PyList_GetItem(result, clos->label);
        write_list_line(clos, item);
        c=c->next;
    }

    while ((frxcg=fr)!=NULL){
        fr = fr->next;
        free(frxcg->c.items);
        free_goto_list(frxcg->c.goto_list);
        free_symbol_sets(frxcg->c.accept_symbols);
        free(frxcg);
    }

    return result;
}

void free_goto_list(goto_list_t *lst){
    goto_list_t *xcg;
    while ((xcg=lst)!=NULL) {
        lst = lst->next;
        free(xcg);
    }
}

void free_symbol_sets(symbol_sets_t *sets){
    symbol_sets_t *xcg;
    while((xcg=sets)!=NULL){
        sets = sets->next;
        free(xcg);
    }
}