//
// Created by DannyV on 2018-12-1.
//

#ifndef COMPOST_GRTABLE_H
#define COMPOST_GRTABLE_H

#ifdef __cplusplus
extern "C" {
#endif


extern PyObject *classNT, *classT, *classV;


symbol_t pyobj_build_symbol(PyObject *instance) ;

production_t* pyobj_build_production_t(PyObject *prod );

#ifdef __cplusplus
}
#endif

#endif //COMPOST_CLOSURE_H
