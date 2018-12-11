#include <libgen.h>

#include "Python.h"

#include "test.h"
#include "symbol.h"
#include "grammar.h"
#include "firstsets.h"
#include "closure.h"
//#include "collection.h"

void initialize(void) {
    char  *basepath = dirname(dirname(dirname(dirname(dirname(__FILE__)))));

    char *venv = ":/Users/yudan/.virtualenvs/compile-c-by-python/lib/python3.7/site-packages";
    char * new_str ;
    if((new_str = malloc(strlen(basepath)+strlen(venv)+1)) != NULL){
        new_str[0] = '\0';
        strcat(new_str,basepath);
        strcat(new_str,venv);
    } else {
        fprintf(stderr,"malloc failed!\n");
        // exit?
    }
    printf("PATH: %s\n", new_str);
    setenv("PYTHONPATH",new_str,1);

    PyObject *pName, *pModule, *pDict, *NT, *T, *V, *args, *self;

    Py_Initialize();

    pName = PyUnicode_FromString((char*)"compost.parse.atoms");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);

    NT = PyDict_GetItemString(pDict, (char *)"NTerm");
    T = PyDict_GetItemString(pDict, (char *)"Term");
    V = PyDict_GetItemString(pDict, (char *)"Value");

    pName = PyUnicode_FromString((char*)"compost.parse.loader");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);

    PyObject * load_grammar = PyDict_GetItemString(pDict, (char *)"load_grammar");

    char *filepath = basepath;
    char *filena = strcat(filepath, "/compost/gram/ansic.grammar");

    PyObject *listobj, *grmmr, *symbs;
    if (PyCallable_Check(load_grammar))
    {
        listobj=PyObject_CallFunction(load_grammar,"s", filena);
        PyErr_Print();
        grmmr = PyTuple_GetItem(listobj, 0);
        PyErr_Print();
        symbs = PyTuple_GetItem(listobj, 1);
        PyErr_Print();

        pName = PyUnicode_FromString((char*)"compost.parse");
        pModule = PyImport_Import(pName);
        pDict = PyModule_GetDict(pModule);
        PyObject * flat_grammar = PyDict_GetItemString(pDict, (char *)"flatten_grammar");

        PyObject *grm = PyObject_CallFunction(flat_grammar, "O", grmmr);


        self = Py_None;
        args = Py_BuildValue("OOOOO", NT, T, V, symbs, grm);
        PyObject *tb = grtable_gen_syntax_table(self, args);
        /*
        PyObject* repr = PyObject_Repr(tb);
        PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
        const char *bytes = PyBytes_AS_STRING(str);
        */

        //printf("REPR: %s\n", bytes);
    }
    else {
        PyErr_Print();
    }

    // Finish the Python Interpreter

    //Py_DECREF(pModule);
    //Py_DECREF(pName);
    //Py_Finalize();

    //return 0;

}

void display_symbol_spaces(void){
    printf("\n");
    printf("-------------------------------Symbols------------------------------\n");
    for (int i=0;i<256;i++){
        if (SymTable[i][0]){
            printf("%d: %s\n", i, SymTable[i]);
        }
    }
    printf("-------------------------------Symbol Entries-----------------------\n");
    for (int i=0;i<SymCount;i++){
        printf("%d:%d, ", i, SymIndex[i].index);
    }
    printf("\n");
    printf("---------------------Symbol Entry Position----------------------\n");
    for (int i=0;i<256;i++){
        if (SymEntPosit[i].index!=0 || i==0){
            printf("%d:%d ", i, SymEntPosit[i].index);
        }
    }
    printf("\n");
}

void display_item(prod_t prd, int prd_or_item, int ent_or_str){
    // if prd_or_item was set 0, is a production , 1 is an item
    __uint128_t g = prd.pnum;
    printf ("(0x%16llx%15llx): ", (uint64_t) (g >> 64), (uint64_t) g);
    for (int i=0;i<14;i++){
        if (!(prd.body[i].index == 0 && i>0)){
            if (ent_or_str){
                printf(i==0?"%s -> ":"%s ", SymTable[prd.body[i].index]);
            }
            else {
                printf(i==0?"%3d -> ":"%-4d", prd.body[i].index);
            }
        }
    }
    if (prd_or_item==1){
        printf(" | %-4d | %-4d", prd.dot.index, prd.follow.index);
    }
    printf("\n");
}

void display_grammar(void){
    printf("---------------------------GrammarTable---------------------- \n");
    for (size_t i=0;i<GramCount;i++){
        display_item(GramTable[i], 0, 1);
    }
}

void display_first_list(size_t s, firsts_t f) {
    int counter = 0;
    if (!f[0].index) {return;}
    printf("%ld : ", s);
    while (f[counter].index){

        printf("%-4d", f[counter].index);
        counter += 1;
    }
    printf("\n");
}

void display_first_sets(void) {
    printf("---------------------------FirstSets---------------------- \n");
    for (size_t i=0; i<NTSIZE; i++){
        display_first_list(i, NTFirst[i]);
    }
}



int main (void) {

    initialize();
    display_symbol_spaces();
    display_grammar();
    display_first_sets();
    //firsts_t n = {{0}};
    //sym_ent_t s = {.index=3};
    //get_first_sets(s, &n);
    //display_first_list(s.index, n);
    //closure_t *t = get_start_closure();
    //display_closure(t);
    //sym_ent_t k = {.index=128};
    //closure_t *g = goto_closure(t, k);
    //display_closure(g);
    //collection_t c = closure_collection();
    clos_list_t * cc = closure_collection();
    //clos_list_t * c = cc;
    int length = 0;
    while (cc->next) {
        length += 1;
        cc = cc->next;
    }
    //print_collection_t(c);
    printf("Length: %d\n",length);



    return 0;
}
