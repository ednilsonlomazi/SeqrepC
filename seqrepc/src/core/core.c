#include "../../core.h"
#include "../encoder/encoder.c"
#include "../data/data.c"
#include "./mps_struct.c"
#include "./hash_tables.c" 
 
PyObject* encode(char* raw_seq, char* mp_signature){
    if(mp_hash_table[0] != NULL){
        MpStruct* mps = mp_hash_table_lookup(mp_signature);
        if(mps != NULL){
            if(mps->one_d != NULL){
                return (*(mps->one_d->mp))(raw_seq);
            }
            return (*(mps->many_d->mp))(raw_seq); // mps->many_d->mp(raw_seq) // works too !!             
        }
        return NULL; // could be Py_None as well... however, with NULL the error message is much more clean
    }
    mp_hash_table_init();
    return encode(raw_seq, mp_signature);
}

PyObject* store(PyObject* seqs, PyObject* seqs_info, char* mapping_signature, char* dst){
    if(mp_hash_table[0] != NULL){
        MpStruct* mps = mp_hash_table_lookup(mapping_signature);
        if(mps != NULL){
            if(mps->one_d != NULL){
                return (*(mps->one_d->rws->write))(seqs, seqs_info, dst);
            }
            return (*(mps->many_d->rws->write))(seqs, seqs_info, dst);            
        }
        return NULL; 
    }
    mp_hash_table_init();
    return store(seqs, seqs_info, mapping_signature, dst);
}

PyObject* collect_encodings(char* mapping_signature, char* source){
    if(mp_hash_table[0] != NULL){
        MpStruct* mps = mp_hash_table_lookup(mapping_signature);
        if(mps != NULL){
            if(mps->one_d != NULL){
                return (*(mps->one_d->rws->read))(source);
            }
            return (*(mps->many_d->rws->read))(source);            
        }
        return NULL;
    }
    mp_hash_table_init();
    return collect_encodings(mapping_signature, source);
}
  
PyObject* collect_fasta(char* source){

    char* file_str = get_file_str(source);
    if(!file_str){
        return NULL;
    }

    PyObject* seqs_data = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* seqs_lines = NULL;

    const char* s = "\n";
    char* token = strtok(file_str, s);
    while(token != NULL){
        if(token[0] == '>'){
            if(seqs_lines != NULL){
                PyList_Append(seqs_data, seqs_lines);   
            }
            PyList_Append(seqs_info, PyUnicode_FromString(token));
            seqs_lines = PyList_New(0);
        }else{
            if(is_genomic_sequence(token) == false){
                Py_DECREF(seqs_data);
                Py_DECREF(seqs_info);
                if(!seqs_lines){
                    Py_DECREF(seqs_lines);
                }
                free(file_str);
                PyErr_SetString(PyExc_ValueError, "File is not on fasta format");
                return NULL;
            }
            PyList_Append(seqs_lines, PyUnicode_FromString(token));
        }

        if((token = strtok(NULL, s)) == NULL){
            PyList_Append(seqs_data, seqs_lines);
        }
    }
    
    if(file_str != NULL){
        free(file_str);
        file_str = NULL;
    }
    return Py_BuildValue("OO", seqs_data, seqs_info);
}

