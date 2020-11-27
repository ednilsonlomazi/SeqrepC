
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




#include "./data_one.c"
#include "./data_many.c"


