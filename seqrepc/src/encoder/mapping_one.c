PyObject* binary_4b(char* raw_seq){
	size_t seq_size = strlen(raw_seq);
	PyObject* tuple = PyTuple_New(4*seq_size);
	short int x, y, z, t;

	for (int i = 0; i < seq_size; ++i){
		char base = raw_seq[i];
		switch(base){
			case 'A': x = 1; y = z = t = 0;
			break;
			case 'T': y = 1; x = z = t = 0;
			break;
			case 'C': t = 1; x = y = z = 0;
			break;
			case 'G': z = 1; x = y = t = 0;
			break;
			default: PyErr_SetString(PyExc_KeyError, "Sequence is not complete"); return NULL;
		}
		PyTuple_SetItem(tuple, i*4, PyLong_FromLong(x));
		PyTuple_SetItem(tuple, 1 + i*4, PyLong_FromLong(y));
		PyTuple_SetItem(tuple, 2 + i*4, PyLong_FromLong(z));
		PyTuple_SetItem(tuple, 3 + i*4, PyLong_FromLong(t));
	}
	return tuple;
}

PyObject* binary_2b(char* raw_seq){
	size_t seq_size = strlen(raw_seq);
	PyObject* tuple = PyTuple_New(2*seq_size);
	short int x, y;

	for (int i = 0; i < seq_size; ++i){
		char base = raw_seq[i];
		switch(base){
			case 'A': x = y = 0;
			break;
			case 'T': x = 0; y = 1;
			break;
			case 'C': x = y = 1;
			break;
			case 'G': x = 1; y = 0;
			break;
			default: PyErr_SetString(PyExc_KeyError, "Sequence is not complete"); return NULL;
		}
		PyTuple_SetItem(tuple, i*2, PyLong_FromLong(x));
		PyTuple_SetItem(tuple, 1 + i*2, PyLong_FromLong(y));
	}
	return tuple;
}
  
PyObject* dna_walk(char* raw_seq){
	size_t seq_size = strlen(raw_seq);
	PyObject* tuple = PyTuple_New(seq_size);
	long int last_value = 0;
	char base = raw_seq[0];
	
	for (int i = 0; i < seq_size; ++i){
		base = raw_seq[i];
		if(base == 'A' || base == 'G') last_value -= 1;
		else{
			if(base == 'T' || base == 'C' || base == 'U') last_value += 1;
			else{
				PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
				return NULL;
			}
		}	
		PyTuple_SetItem(tuple, i, PyLong_FromLong(last_value));	
	}
	return tuple;
}


PyObject* nucleotide_mapping(char* raw_seq, PyObject* mapping_values){
	size_t seq_size = strlen(raw_seq);
	PyObject* tuple = PyTuple_New(seq_size);
	for (int i = 0; i < seq_size; ++i){
		char base = raw_seq[i];
		switch(base){
			case 'A': PyTuple_SetItem(tuple, i, PyTuple_GetItem(mapping_values, 0)); 
			break;
			case 'T': PyTuple_SetItem(tuple, i, PyTuple_GetItem(mapping_values, 1));
			break;
			case 'C': PyTuple_SetItem(tuple, i, PyTuple_GetItem(mapping_values, 2));
			break;
			case 'G': PyTuple_SetItem(tuple, i, PyTuple_GetItem(mapping_values, 3));
			break;
			default: PyErr_SetString(PyExc_KeyError, "Sequence is not complete"); return NULL;
		}
	}
	return tuple;
}

PyObject* int_nucleotide_mapping(char* raw_seq, int* mapping_values){
	size_t seq_size = strlen(raw_seq);
	PyObject* tuple = PyTuple_New(seq_size);
	for (int i = 0; i < seq_size; ++i){
		char base = raw_seq[i];
		switch(base){
			case 'A': PyTuple_SetItem(tuple, i, PyLong_FromLong(mapping_values[0])); 
			break;
			case 'T': PyTuple_SetItem(tuple, i, PyLong_FromLong(mapping_values[1]));
			break;
			case 'C': PyTuple_SetItem(tuple, i, PyLong_FromLong(mapping_values[2]));
			break;
			case 'G': PyTuple_SetItem(tuple, i, PyLong_FromLong(mapping_values[3]));
			break;
			default: PyErr_SetString(PyExc_KeyError, "Sequence is not complete"); return NULL;
		}
	}
	return tuple;
}

PyObject* double_nucleotide_mapping(char* raw_seq, double* mapping_values){
	size_t seq_size = strlen(raw_seq);
	PyObject* tuple = PyTuple_New(seq_size);
	for (int i = 0; i < seq_size; ++i){
		char base = raw_seq[i];
		switch(base){
			case 'A': PyTuple_SetItem(tuple, i, PyFloat_FromDouble(mapping_values[0])); 
			break;
			case 'T': PyTuple_SetItem(tuple, i, PyFloat_FromDouble(mapping_values[1]));
			break;
			case 'C': PyTuple_SetItem(tuple, i, PyFloat_FromDouble(mapping_values[2]));
			break;
			case 'G': PyTuple_SetItem(tuple, i, PyFloat_FromDouble(mapping_values[3]));
			break;
			default: PyErr_SetString(PyExc_KeyError, "Sequence is not complete"); return NULL;
		}
	}
	return tuple;
}

PyObject* complex_nucleotide_mapping(char* raw_seq, Py_complex* mapping_values){
	size_t seq_size = strlen(raw_seq);
	PyObject* tuple = PyTuple_New(seq_size);
	for (int i = 0; i < seq_size; ++i){
		char base = raw_seq[i];
		switch(base){
			case 'A': PyTuple_SetItem(tuple, i, PyComplex_FromDoubles(mapping_values[0].real, mapping_values[0].imag)); 
			break;
			case 'T': PyTuple_SetItem(tuple, i, PyComplex_FromDoubles(mapping_values[1].real, mapping_values[1].imag));
			break;
			case 'C': PyTuple_SetItem(tuple, i, PyComplex_FromDoubles(mapping_values[2].real, mapping_values[2].imag));
			break;
			case 'G': PyTuple_SetItem(tuple, i, PyComplex_FromDoubles(mapping_values[3].real, mapping_values[3].imag));
			break;
			default: PyErr_SetString(PyExc_KeyError, "Sequence is not complete"); return NULL;
		}
	}
	return tuple;
}

PyObject* atomic(char* raw_seq){
	int mapping_values[] = {70, 66, 58, 78};
	return int_nucleotide_mapping(raw_seq, mapping_values);
}

PyObject* molecular_mass(char* raw_seq){
	int mapping_values[] = {134, 125, 110, 150};
	return int_nucleotide_mapping(raw_seq, mapping_values);
}

PyObject* eiip(char* raw_seq){
	double mapping_values[] = {0.1260, 0.1335, 1340, 0.0806};
	return double_nucleotide_mapping(raw_seq, mapping_values);
}

PyObject* imaginary(char* raw_seq){
	Py_complex mapping_values[] = {
		{.real = 1.0, .imag = 1.0},
		{.real = 1.0, .imag = -1.0},
		{.real = -1.0, .imag = 1.0},
		{.real = -1.0, .imag = -1.0},
	};
	return complex_nucleotide_mapping(raw_seq, mapping_values);
}

PyObject* paired_numeric(char* raw_seq){
	int mapping_values[] = {1,1,-1,-1};
	return int_nucleotide_mapping(raw_seq, mapping_values);
}

PyObject* integer(char* raw_seq){
	int mapping_values[] = {2,0,1,3};
	return int_nucleotide_mapping(raw_seq, mapping_values);
}

PyObject* real(char* raw_seq){
	double mapping_values[] = {-1.5, 1.5, 0.5, -0.5};
	return double_nucleotide_mapping(raw_seq, mapping_values);
}
