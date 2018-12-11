//
//Created by DannyV on 2018-12-10.
//

#ifndef COMPOST_COLLECTION_H
#define COMPOST_COLLECTION_H


#ifdef __cplusplus
extern "C" {
#endif

#include "closure.h"

closure_t * goto_closure(closure_t *clos, sym_ent_t sentry);
int eq_closure_t(closure_t *a, closure_t *b);

typedef struct clos_list_t clos_list_t;
struct clos_list_t {
    closure_t c;
    clos_list_t *next;
};

clos_list_t * closure_collection(void);
PyObject * get_states_list(clos_list_t *c, Py_ssize_t length);

typedef char* action_t ;




#ifdef __cplusplus
}
#endif

#endif
