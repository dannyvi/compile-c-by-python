#include "Python.h"

//#include "symbol.h"
//#include "gramma.h"
#include "closure.h"
#include "collection.h"

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


closure_t ret_closure_in_collection(closure_t *clos, clos_list_t *collection){
    clos_list_t *cc = collection;
    closure_t ret;
    ret.label=-1;
    if (!cc->next){return ret;}
    while(cc->next){
        if (eq_closure_t(clos, &cc->c)){return cc->c;}
        cc = cc->next;
    }
    return ret;
}

closure_t * goto_closure(closure_t *clos, sym_ent_t sentry) {
    pitem_list_t *ss = PyMem_Calloc(1, sizeof(pitem_list_t));
    pitem_list_t *set = ss;
    pitem_t *ptm = clos->items;
    for (int i=0; i<clos->length; i++,ptm++) {
        int pos = (int)(ptm->dot.index);
        if(ptm->body[pos+1].index==sentry.index && sentry.index!=0){
            sym_ent_t ent = {.index=pos+1};
            pitem_t newitem = build_pitem_t(ptm, ent, ptm->follow);
            add_cl(newitem, set);
            set = set->next;
        }
    }
    if (!ss->next) {
        closure_t * t = PyMem_Calloc(1, sizeof(closure_t));
        t->length= 0 ;
        t->items = NULL;
        return t;
    } else {
        return get_closure(ss, NONE_LABEL);
    }
}

static void add_clos(closure_t *t, clos_list_t *coll){
    coll->c = *t;
    coll->next = PyMem_Calloc(1, sizeof(clos_list_t));
}

static int has_in_goto_list(closure_t *clos, closure_t *goclos, sym_ent_t * ent){
    if (!clos->goto_list) {return 0;}
    goto_list_t *g = clos->goto_list;
    while (g->next) {
        if (g->sym_index.index==ent->index && eq_closure_t(&g->closure, goclos)) {return 1;}
        g = g->next;
    }
    return 0;
}

static void add_goto_list(closure_t *clos, closure_t goclos, sym_ent_t * ent){
    //not initialized condition
    if (!clos->goto_list) {
        goto_list_t *g = PyMem_Calloc(1, sizeof(goto_list_t));
        g->sym_index = *ent;
        g->closure = goclos;
        g->next = PyMem_Calloc(1, sizeof(goto_list_t));
        clos->goto_list = g;
        clos->goto_tail = g->next;
    }
    else {  // closure already has at least 1 goto target.
        if (!has_in_goto_list(clos, &goclos, ent)){
            goto_list_t *g = clos->goto_tail;
            g->sym_index = *ent;
            g->closure = goclos;
            g->next = PyMem_Calloc(1, sizeof(goto_list_t));
            clos->goto_tail = g->next;
        }
    }
}

clos_list_t * closure_collection(void) {
    int label = 0;
    clos_list_t * queue = PyMem_Calloc(1, sizeof(clos_list_t));
    clos_list_t * collection = queue;
    clos_list_t *qp, *countq;
    qp = queue;
    countq = queue;

    int length = 0;
    sym_ent_t posit = {.index=0};
    //symbol_t sym = symbol_create(Value, "$");
    sym_ent_t startp={.type=VALUE};
    sym_ent_t sentry = get_sym_ent(startp, "$");
    //sym_ent_t sentry = sentry_find(sym);
    pitem_t startitem = build_pitem_t(&GramTable[0], posit, sentry);
    pitem_list_t *start = PyMem_Calloc(1, sizeof(pitem_list_t));
    start->item = startitem;
    start->next = PyMem_Calloc(1, sizeof(pitem_list_t));
    closure_t *t = get_closure(start, label);

    add_clos(t, qp);

    qp = qp->next;

    length += 1;

    while (countq->next){

        closure_t *clos = &(countq->c);
        sym_ent_list_t *ent = clos->accept_symbols;
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
                    sym_ent_list_t *frsmb, *syms;
                    syms = goclos->accept_symbols;
                    while((frsmb=syms)!= NULL){
                        syms = syms->next;
                        PyMem_Free(frsmb);
                    }
                    frsmb = syms = NULL;
                    PyMem_Free(goclos->items);
                    PyMem_Free(goclos);
                    goclos = NULL;
                }
            }
            else {
                PyMem_Free(goclos);
                goclos=NULL;
            }
            ent = ent->next;
        }

        countq = countq->next;
    }
    return collection;
}


int get_prod_number(pitem_t *item){
    prod_t p = *item;
    p.dot.index = 0;
    p.follow.index=0;
    for (size_t i=0; i<GramCount; i++) {
        if (p.pnum==GramTable[i].pnum){return (int)i;}
    }
    //never reach here;
    return -1;
}

void write_list_line(closure_t *clos, PyObject *list) {
    action_t action = malloc(8*sizeof(char));
    int golabel, strlen;
    // shift actions
    goto_list_t *golist = clos->goto_list;
    if (golist) {
        while (golist->next){
            sym_ent_t posit = golist->sym_index;
            golabel = golist->closure.label;
            strlen = snprintf( NULL, 0, "%d", golabel );
            posit.type==NTERM ? snprintf( action, strlen + 1, "%d", golabel ) :
                                snprintf( action, strlen + 2, "s%d", golabel );
            PyObject * listitem = Py_BuildValue("s", action);
            PyList_SetItem(list, SymEntPosit[posit.index].index, listitem);
            golist = golist->next;
        }
    }
    // check reduce action in closure items;
    sym_ent_t startp={.type=VALUE};
    sym_ent_t accept_entry = get_sym_ent(startp, "$");
    //sym_ent_t accept_entry = sentry_find(symbol_create(Value, "$"));
    pitem_t acc_item = {.body={{0},{1}}, .dot={1}, .follow=accept_entry};
    pitem_t *pitem = clos->items;
    for (int i=0; i<clos->length; i++,pitem++){
        if (acc_item.pnum == pitem->pnum){
            snprintf(action, 2, "%s", "$");
            PyObject * listitem = Py_BuildValue("s", action);
            PyList_SetItem(list, SymEntPosit[accept_entry.index].index, listitem);
        }
        else{
            int plen = 0;
            while(pitem->body[plen].index || plen==0){
                plen += 1;
            }
            if (pitem->dot.index == plen-1) {
                int number = get_prod_number(pitem);
                strlen = snprintf( NULL, 0, "%d", number );
                snprintf(action, strlen+2, "r%d", number);
                PyObject * listitem = Py_BuildValue("s", action);
                PyList_SetItem(list, SymEntPosit[pitem->follow.index].index, listitem);
            }
        }
    }
    PyMem_Free(action);
    action = NULL;
}

PyObject * get_states_list(clos_list_t *c, Py_ssize_t length) {
    clos_list_t *fr, *frxcg;
    fr=c;
    PyObject * result;
    //init_anti_map();
    int sym_size = SymCount;
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
        PyMem_Free(frxcg->c.items);
        PyMem_Free_goto_list(frxcg->c.goto_list);
        PyMem_Free_sym_ent_list(frxcg->c.accept_symbols);
        PyMem_Free(frxcg);
    }

    return result;
}

void PyMem_Free_goto_list(goto_list_t *lst){
    goto_list_t *xcg;
    while ((xcg=lst)!=NULL) {
        lst = lst->next;
        PyMem_Free(xcg);
    }
}

void PyMem_Free_sym_ent_list(sym_ent_list_t *sets){
    sym_ent_list_t *xcg;
    while((xcg=sets)!=NULL){
        sets = sets->next;
        PyMem_Free(xcg);
    }
}

