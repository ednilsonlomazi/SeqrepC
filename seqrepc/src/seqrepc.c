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
    return store(seqs, seqs_info, mapping_signature, dst);
              
}
  
static PyObject* method_encode(PyObject *self, PyObject *args) {
    
    unsigned int seq_size;
	char* raw_seq = NULL;	
	char* mapping_signature = NULL;

    if(!PyArg_ParseTuple(args, "ssi", &mapping_signature, &raw_seq, &seq_size)) return NULL;
    return encode(raw_seq, seq_size, mapping_signature);

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
    "Python interface for seqrepc C module",
    -1,
    SeqrepC_Methods
};

PyMODINIT_FUNC PyInit_seqrepc(void) {
    return PyModule_Create(&seqrepc);
}
