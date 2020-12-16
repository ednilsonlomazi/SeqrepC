#define PY_SSIZE_T_CLEAN 
#include <Python.h>
#include "./core/core.c"        
                      
static PyObject* method_collect_fasta(PyObject *self, PyObject *args) {
    
    char* source = NULL; 
    
    if(!PyArg_ParseTuple(args, "s", &source)) return NULL; 
    return collect_fasta(source);
                      
}                      
                       
static PyObject* method_collect_encodings(PyObject *self, PyObject *args) {
     
    char* mapping_signature = NULL;
    char* source = NULL; 
    
    if(!PyArg_ParseTuple(args, "ss", &mapping_signature, &source)) return NULL;
    return collect_encodings(mapping_signature, source);
               
}   
                                         
static PyObject* method_store(PyObject *self, PyObject *args) {
    
    char* mapping_signature = NULL; 
    char* dst = NULL;          
    
    PyObject* seqs;  
    PyObject* seqs_info; 
    
    if(!PyArg_ParseTuple(args, "OOss", &seqs, &seqs_info, &mapping_signature, &dst)) return NULL;
    Py_INCREF(seqs);
    Py_INCREF(seqs_info);
    PyObject* result = store(seqs, seqs_info, mapping_signature, dst);
    Py_DECREF(seqs);
    Py_DECREF(seqs_info);
    return result;
              
}  
  
static PyObject* method_encode(PyObject *self, PyObject *args) {
    
	char* raw_seq = NULL;	
	char* mapping_signature = NULL;

    if(!PyArg_ParseTuple(args, "ss", &mapping_signature, &raw_seq)) return NULL;
    return encode(raw_seq, mapping_signature);

} 
            
static PyMethodDef SeqrepC_Methods[] = {
    {"encode", method_encode, METH_VARARGS, "Method to convert genomic sequence to numerical sequence"},
    {"store", method_store, METH_VARARGS, "Method to store numerical sequences"},
    {"collect_encodings", method_collect_encodings, METH_VARARGS, "Method to collect numerical sequences"},
    {"collect_fasta", method_collect_fasta, METH_VARARGS, "Method to collect genomic sequences"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef seqrepc = {
    PyModuleDef_HEAD_INIT,
    "seqrepc",
    "SeqrepC is a module for fundamental operations related to numerical representations of genomic sequences.",
    -1,
    SeqrepC_Methods
};

PyMODINIT_FUNC PyInit_seqrepc(void) {
    return PyModule_Create(&seqrepc);
}
