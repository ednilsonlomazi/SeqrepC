
int get_seq_size(char* line){
    const char* separator = "|";
    char* last_token = NULL;
    char* token = strtok(line, separator);
    while(token != NULL) {
        last_token = token;
        token = strtok(NULL, separator);
    }
    return atoi(last_token);
} 

PyObject* read_int_segment(char* line, unsigned encoded_seq_size){
    PyObject* axis = PyTuple_New(encoded_seq_size);
    const char* separator = ",";
    char* token = strtok(line, separator);
    int i = 0;
    while(token != NULL){
        PyTuple_SetItem(axis, i, PyLong_FromString(token, &token, 10));
        ++i;
        token = strtok(NULL, separator);
    }
    return axis;
}
 
PyObject* read_float_segment(char* line, unsigned encoded_seq_size){
    PyObject* axis = PyTuple_New(encoded_seq_size);
    const char* separator = ",";
    char* token = strtok(line, separator);
    int i = 0; 
    while(token != NULL){
        PyTuple_SetItem(axis, i, PyFloat_FromString(PyUnicode_FromString(token)));
        ++i;
        token = strtok(NULL, separator);
    }
    return axis;
}

void write_float_segment(FILE* file, PyObject* seq, size_t seq_size){
    Py_INCREF(seq);
	fprintf(file, "%f", PyFloat_AsDouble(PyTuple_GetItem(seq, 0)));
    for (int j = 1; j < seq_size; ++j){
        fprintf(file, ",%f", PyFloat_AsDouble(PyTuple_GetItem(seq, j)));
    }
    fprintf(file, "\n");
    Py_DECREF(seq);
}
  
void write_int_segment(FILE* file, PyObject* seq, size_t seq_size){
    Py_INCREF(seq);
    fprintf(file, "%ld", PyLong_AsLong(PyTuple_GetItem(seq, 0)));
	for (int j = 1; j < seq_size; ++j){
        fprintf(file, ",%ld", PyLong_AsLong(PyTuple_GetItem(seq, j)));
    }
    fprintf(file, "\n");
    Py_DECREF(seq);
}

void write_complex_segment(FILE* file, PyObject* seq, size_t seq_size){
    Py_INCREF(seq);
    Py_complex complex = PyComplex_AsCComplex(PyTuple_GetItem(seq, 0));
    fprintf(file, "%f,%f", complex.real, complex.imag);
	seq_size = seq_size/2;
    for (int j = 1; j < seq_size; ++j){
		complex = PyComplex_AsCComplex(PyTuple_GetItem(seq, j));
        fprintf(file, ",%f,%f", complex.real, complex.imag);
    }
    fprintf(file, "\n");
    Py_DECREF(seq);
}

PyObject* read_many(SegmentReader* segment_reader, char* source){
    
    FILE* fp = fopen(source, "r");
    if (!fp){
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

    char* line_buf = NULL;
    size_t line_buf_size = 0;
    unsigned encoded_seq_size = 0;
    int line_size;

    PyObject* seqs_encoded = PyList_New(0);
    PyObject* seq_encoded = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* pack = PyTuple_New(2);

    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size > 0){
        if(line_size > 1){
            if(line_buf[0] != '>'){
                while(line_size > 1){
                    PyList_Append(seq_encoded, segment_reader(line_buf, encoded_seq_size));
                    line_size = getline(&line_buf, &line_buf_size, fp);
                }
                PyList_Append(seqs_encoded, seq_encoded);
                seq_encoded = PyList_New(0);                    
            }else{
                PyList_Append(seqs_info, PyUnicode_FromString(line_buf));
                encoded_seq_size = get_seq_size(line_buf);
            }
        }
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    if(fp != NULL){
        fclose(fp);
    }
    PyTuple_SetItem(pack, 0, seqs_encoded);
    PyTuple_SetItem(pack, 1, seqs_info);
    return pack;
}

PyObject* read_one(SegmentReader* segment_reader, char* source){
    
    FILE* fp = fopen(source, "r");
    if (!fp){
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

    char* line_buf = NULL;
    size_t line_buf_size = 0;
    unsigned encoded_seq_size = 0;
    int line_size;

    PyObject* seqs_encoded = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* tuple = PyTuple_New(2);

    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size > 0){
        if(line_size > 1){
            if(line_buf[0] != '>'){ 
                PyList_Append(seqs_encoded, segment_reader(line_buf, encoded_seq_size));
            }else{
                PyList_Append(seqs_info, PyUnicode_FromString(line_buf));
                encoded_seq_size = get_seq_size(line_buf);
            }
        }
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    if(fp != NULL){
        fclose(fp);
        fp = NULL;
    }
    PyTuple_SetItem(tuple, 0, seqs_encoded);
    PyTuple_SetItem(tuple, 1, seqs_info);
    return tuple;
}

PyObject* write_many(PyObject* seqs, PyObject* seqs_info, char* dst, SegmentWriter* segment_writer){

    FILE* fp = fopen(dst, "w+");
    if(!fp){
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

    Py_INCREF(seqs);
    Py_INCREF(seqs_info);
    
    size_t num_seqs = PyTuple_Size(seqs);
    for (int seq_id = 0; seq_id < num_seqs; ++seq_id){
        PyObject* seq_encoded = PyTuple_GetItem(seqs, seq_id);
        PyObject* axis_0 = PyTuple_GetItem(seq_encoded, 0);
        
        Py_INCREF(axis_0);
        size_t seq_size = PyTuple_Size(axis_0);
        fprintf(fp, "%s |%d\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)), seq_size);
        
        (*segment_writer)(fp, axis_0, seq_size);
        Py_DECREF(axis_0);
        size_t dim = PyTuple_Size(seq_encoded);
        for (int i = 1; i < dim; ++i){
            (*segment_writer)(fp, PyTuple_GetItem(seq_encoded, i), seq_size);
        }
        fprintf(fp, "\n");
    }
    if(fp != NULL){
        fclose(fp);
        fp = NULL;
    }
    Py_DECREF(seqs);
    Py_DECREF(seqs_info);
    Py_RETURN_TRUE; // #define Py_RETURN_TRUE return Py_INCREF(Py_True), Py_True
} 

PyObject* write_one(PyObject* seqs, PyObject* seqs_info, char* dst, SegmentWriter* segment_writer){

    FILE* fp = fopen(dst, "w+");
    if(!fp){
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

    Py_INCREF(seqs);
    Py_INCREF(seqs_info);

    for (int seq_id = 0; seq_id < PyTuple_Size(seqs); ++seq_id){
        PyObject* seq_encoded = PyTuple_GetItem(seqs, seq_id);
        Py_INCREF(seq_encoded);
        size_t seq_size = PyTuple_Size(seq_encoded);
        if(segment_writer == &write_complex_segment){
            seq_size *= 2;
        } 
        fprintf(fp, "%s |%d\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)), seq_size);
        (*segment_writer)(fp, seq_encoded, seq_size);
        fprintf(fp, "\n");
        Py_DECREF(seq_encoded);    
    } 
    if(fp != NULL){
        fclose(fp);
        fp = NULL;
    }
    Py_DECREF(seqs);
    Py_DECREF(seqs_info);
    Py_RETURN_TRUE; // #define Py_RETURN_TRUE return Py_INCREF(Py_True), Py_True
}



#include "./raw_data.c"
#include "./data_one.c"
#include "./data_many.c"


