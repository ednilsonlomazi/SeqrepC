
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
	fprintf(file, "%f", PyFloat_AsDouble(PyTuple_GetItem(seq, 0)));
    for (int j = 1; j < PyTuple_Size(seq); ++j){
        fprintf(file, ",%f", PyFloat_AsDouble(PyTuple_GetItem(seq, j)));
    }
    fprintf(file, "\n");
}
 
void write_int_segment(FILE* file, PyObject* seq){
    fprintf(file, "%ld", PyLong_AsLong(PyTuple_GetItem(seq, 0)));
	for (int j = 1; j < PyTuple_Size(seq); ++j){
        fprintf(file, ",%ld", PyLong_AsLong(PyTuple_GetItem(seq, j)));
    }
    fprintf(file, "\n");
}

void write_complex_segment(FILE* file, PyObject* seq){
    Py_complex complex = PyComplex_AsCComplex(PyTuple_GetItem(seq, 0));
    fprintf(file, "%f,%f", complex.real, complex.imag);
	for (int j = 1; j < PyTuple_Size(seq); ++j){
		complex = PyComplex_AsCComplex(PyTuple_GetItem(seq, j));
        fprintf(file, ",%f,%f", complex.real, complex.imag);
    }
    fprintf(file, "\n");
}

PyObject* read_many(SegmentReader* segment_reader, char* source){
    PyObject* seqs_encoded = PyList_New(0);
    PyObject* seq_encoded = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* read_pack = PyTuple_New(2);


    char* line_buf = NULL;
    size_t line_buf_size = 0;
    unsigned encoded_seq_size = 0;
    int line_size;
    
    FILE* fp = fopen(source, "r");
    if (!fp){
        fprintf(stderr, "Error opening file '%s'\n", source);
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
    fclose(fp);
    PyTuple_SetItem(read_pack, 0, seqs_encoded);
    PyTuple_SetItem(read_pack, 1, seqs_info);
    return read_pack;
}

PyObject* read_one(SegmentReader* segment_reader, char* source){
    PyObject* seqs_encoded = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* read_pack = PyTuple_New(2);

    char* line_buf = NULL;
    size_t line_buf_size = 0;
    unsigned encoded_seq_size = 0;
    int line_size;
    
    FILE* fp = fopen(source, "r");
    if (!fp){
        fprintf(stderr, "Error opening file '%s'\n", source);
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
    fclose(fp);
    PyTuple_SetItem(read_pack, 0, seqs_encoded);
    PyTuple_SetItem(read_pack, 1, seqs_info);
    return read_pack;
}

PyObject* write_many(PyObject* seqs, PyObject* seqs_info, char* dst, SegmentWriter* segment_writer){
    
    FILE* fp;
    fp = fopen(dst, "w+");
    
    for (int seq_id = 0; seq_id < PyTuple_Size(seqs); ++seq_id){
        PyObject* seq_encoded = PyTuple_GetItem(seqs, seq_id);
        PyObject* item_0 = PyTuple_GetItem(seq_encoded, 0);
        size_t seq_size = PyTuple_Size(item_0);
        fprintf(fp, "%s |%d\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)), seq_size);
        
        (*segment_writer)(fp, item_0);
        for (int i = 1; i < PyTuple_Size(seq_encoded); ++i){
            (*segment_writer)(fp, PyTuple_GetItem(seq_encoded, i));
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return Py_True;
}

PyObject* write_one(PyObject* seqs, PyObject* seqs_info, char* dst, SegmentWriter* segment_writer){
    FILE* fp;
    fp = fopen(dst, "w+");
    
    for (int seq_id = 0; seq_id < PyTuple_Size(seqs); ++seq_id){
        PyObject* item = PyTuple_GetItem(seqs, seq_id);
        size_t seq_size = PyTuple_Size(item);
        if(segment_writer == &write_complex_segment){
            seq_size *= 2;
        } 
        fprintf(fp, "%s |%d\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)), seq_size);
        (*segment_writer)(fp, item);
        fprintf(fp, "\n");    
    } 
    fclose(fp);
    return Py_True;
}



#include "./raw_data.c"
#include "./data_one.c"
#include "./data_many.c"


