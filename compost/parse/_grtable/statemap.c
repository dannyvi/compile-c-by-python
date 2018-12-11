#include <stdlib.h>
#include "Python.h"

#include "statemap.h"
#include "collection.h"

static size_t get_prod_number(pitem_t *item){
    prod_t p = *item;
    p.dot.index = 0;
    p.follow.index=0;
    for (size_t i=0; i<GramCount; i++) {
        if (p.pnum==GramTable[i].pnum){return i;}
    }
    //never reach here;
    return -1;
}

void write_list_line(closure_t *clos, PyObject *list){
    char action[8] = {0};
    int golabel, strlen;

    // shift action
    goto_t *golist = clos->gotos;
    if (clos->goto_cnt) {
        for (int i = 0; i<clos->goto_cnt; i++){
            sym_ent_t posit = golist->entry;
            golabel = golist->closure->label;
            strlen = snprintf(NULL, 0, "%d", golabel);
            posit.type == NTERM ? snprintf(action, strlen+1, "%d", golabel) :
                                  snprintf(action, strlen+2, "s%d", golabel);
            PyObject * list_item = Py_BuildValue("s", action);
            PyList_SetItem(list, SymEntPosit[posit.index].index, list_item);
        }
    }

    // reduce action
    sym_ent_t startp = {.type=VALUE};
    sym_ent_t accept_entry = get_sym_ent(startp, "$");
    pitem_t acc_item = {.body={{0}, {1}}, .dot={1}, .follow=accept_entry};
    pitem_t *pitem = clos->items;
    for (int i = 0; i < clos->itm_cnt; i++, pitem++) {
        if (acc_item.pnum == pitem->pnum){
            snprintf(action, 2, "%s", "$");
            PyObject *list_item = Py_BuildValue("s", action);
            PyList_SetItem(list, SymEntPosit[pitem->follow.index].index, list_item);
        }
        else {
            int plen = 0;
            while(pitem->body[plen].index || plen==0) {plen += 1;}
            if (pitem->dot.index == plen-1) {
                int number = get_prod_number(pitem);
                strlen = snprintf(NULL, 0, "%d", number);
                snprintf(action, strlen+2, "r%d", number);
                PyObject *list_item = Py_BuildValue("s", action);
                PyList_SetItem(list, SymEntPosit[pitem->follow.index].index, list_item);
            }
        }
    }
}

PyObject * get_states_list(collection_t * coln){
    char action[8] = ".";
    clos_list_t * clist = coln->clist;
    PyObject * result = PyList_New(coln->length);
    for (Py_ssize_t i = 0; i < coln->length; i++){
        PyObject * line = PyList_New(SymCount);
        for (Py_ssize_t j = 0; j < SymCount; j++){
            PyObject * elem = Py_BuildValue("s", action);
            PyList_SetItem(line, j, elem);
        }
        PyList_SetItem(result, i, line);
    }

    while (clist->next) {
        closure_t * clos = &(clist->clos);
        PyObject * item = PyList_GetItem(result, clos->label);
        write_list_line(clos, item);
        clist = clist->next;
    }

    destroy_clos_list(clist);
    return result;
}
