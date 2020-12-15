
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

PyObject* read_int_segment(char* line, unsigned encoded_seq_size) {
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
 
PyObject* read_float_segment(char* line, unsigned encoded_seq_size) {
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

void write_float_segment(FILE* file, PyObject* seq){
    Py_INCREF(seq);
	fprintf(file, "%f", PyFloat_AsDouble(PyTuple_GetItem(seq, 0)));
    for (int j = 1; j < PyTuple_Size(seq); ++j){
        fprintf(file, ",%f", PyFloat_AsDouble(PyTuple_GetItem(seq, j)));
    }
    fprintf(file, "\n");
    Py_DECREF(seq);
}
  
void write_int_segment(FILE* file, PyObject* seq){
    Py_INCREF(seq);
    fprintf(file, "%ld", PyLong_AsLong(PyTuple_GetItem(seq, 0)));
	for (int j = 1; j < PyTuple_Size(seq); ++j){
        fprintf(file, ",%ld", PyLong_AsLong(PyTuple_GetItem(seq, j)));
    }
    fprintf(file, "\n");
    Py_DECREF(seq);
}

void write_complex_segment(FILE* file, PyObject* seq){
    Py_INCREF(seq);
    Py_complex complex = PyComplex_AsCComplex(PyTuple_GetItem(seq, 0));
    fprintf(file, "%f,%f", complex.real, complex.imag);
	for (int j = 1; j < PyTuple_Size(seq); ++j){
		complex = PyComplex_AsCComplex(PyTuple_GetItem(seq, j));
        fprintf(file, ",%f,%f", complex.real, complex.imag);
    }
    fprintf(file, "\n");
    Py_DECREF(seq);
}

PyObject* read_many(SegmentReader* segment_reader, char* source){
    PyObject* seqs_encoded = PyList_New(0);
    PyObject* seq_encoded = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* pack = PyTuple_New(2);

    char* line_buf = NULL;
    size_t line_buf_size = 0;
    unsigned encoded_seq_size = 0;
    int line_size;
    
    FILE* fp = fopen(source, "r");
    if (!fp){
        Py_DECREF(seqs_encoded);
        Py_DECREF(seqs_info);
        Py_DECREF(seq_encoded);
        Py_DECREF(pack);
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

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
    PyObject* seqs_encoded = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* tuple = PyTuple_New(2);

    char* line_buf = NULL;
    size_t line_buf_size = 0;
    unsigned encoded_seq_size = 0;
    int line_size;
    
    FILE* fp = fopen(source, "r");
    if (!fp){
        Py_DECREF(seqs_encoded);
        Py_DECREF(seqs_info);
        Py_DECREF(tuple);
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

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
    Py_INCREF(seqs);
    Py_INCREF(seqs_info);
    FILE* fp = fopen(dst, "w+");
    
    if(!fp){
        Py_DECREF(seqs);
        Py_DECREF(seqs_info);
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

    for (int seq_id = 0; seq_id < PyTuple_Size(seqs); ++seq_id){
        PyObject* seq_encoded = PyTuple_GetItem(seqs, seq_id);
        PyObject* item_0 = PyTuple_GetItem(seq_encoded, 0);
        Py_INCREF(item_0);
        size_t seq_size = PyTuple_Size(item_0);
        fprintf(fp, "%s |%d\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)), seq_size);
        
        (*segment_writer)(fp, item_0);
        Py_DECREF(item_0);
        for (int i = 1; i < PyTuple_Size(seq_encoded); ++i){
            (*segment_writer)(fp, PyTuple_GetItem(seq_encoded, i));
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
    Py_INCREF(seqs);
    Py_INCREF(seqs_info);
    FILE* fp = fopen(dst, "w+");
    
    if(!fp){
        Py_DECREF(seqs);
        Py_DECREF(seqs_info);
        PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
        return NULL;
    }

    for (int seq_id = 0; seq_id < PyTuple_Size(seqs); ++seq_id){
        PyObject* item = PyTuple_GetItem(seqs, seq_id);
        Py_INCREF(item);
        size_t seq_size = PyTuple_Size(item);
        if(segment_writer == &write_complex_segment){
            seq_size *= 2;
        } 
        fprintf(fp, "%s |%d\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)), seq_size);
        (*segment_writer)(fp, item);
        fprintf(fp, "\n");
        Py_DECREF(item);    
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


