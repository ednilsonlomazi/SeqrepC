PyObject* binary_4b(char* raw_seq, unsigned seq_size){
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

PyObject* binary_2b(char* raw_seq, unsigned seq_size){
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

PyObject* dna_walk(char* raw_seq, unsigned seq_size){
	PyObject* tuple = PyTuple_New(seq_size);
	long int last_value;
	char base = raw_seq[0];

	if(base == 'A' || base == 'G') last_value = -1;
	else{
		if(base == 'T' || base == 'C' || base == 'U') last_value = 1;
		else{
			PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
			return NULL;
		}
	}

	PyTuple_SetItem(tuple, 0, PyLong_FromLong(last_value));	
	
	for (int i = 1; i < seq_size; ++i){
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
 
PyObject* nucleotide_mapping(char* raw_seq, unsigned int seq_size, PyObject* mapping_values){
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

PyObject* atomic(char* raw_seq, unsigned seq_size){
	PyObject* mapping_values = PyTuple_New(4);
	
	PyTuple_SetItem(mapping_values, 0, PyLong_FromLong(70));
	PyTuple_SetItem(mapping_values, 1, PyLong_FromLong(66));
	PyTuple_SetItem(mapping_values, 2, PyLong_FromLong(58));
	PyTuple_SetItem(mapping_values, 3, PyLong_FromLong(78));
	
	return nucleotide_mapping(raw_seq, seq_size, mapping_values);
}

PyObject* molecular_mass(char* raw_seq, unsigned seq_size){
	PyObject* mapping_values = PyTuple_New(4);
	
	PyTuple_SetItem(mapping_values, 0, PyLong_FromLong(134));
	PyTuple_SetItem(mapping_values, 1, PyLong_FromLong(125));
	PyTuple_SetItem(mapping_values, 2, PyLong_FromLong(110));
	PyTuple_SetItem(mapping_values, 3, PyLong_FromLong(150));
	
	return nucleotide_mapping(raw_seq, seq_size, mapping_values);
}

PyObject* eiip(char* raw_seq, unsigned seq_size){
	PyObject* mapping_values = PyTuple_New(4);
	
	PyTuple_SetItem(mapping_values, 0, PyFloat_FromDouble(0.1260));
	PyTuple_SetItem(mapping_values, 1, PyFloat_FromDouble(0.1335));
	PyTuple_SetItem(mapping_values, 2, PyFloat_FromDouble(0.1340));
	PyTuple_SetItem(mapping_values, 3, PyFloat_FromDouble(0.0806));
	
	return nucleotide_mapping(raw_seq, seq_size, mapping_values);
}

PyObject* imaginary(char* raw_seq, unsigned seq_size){
	PyObject* mapping_values = PyTuple_New(4);
	
	PyTuple_SetItem(mapping_values, 0, PyComplex_FromDoubles(1.0, 1.0));
	PyTuple_SetItem(mapping_values, 1, PyComplex_FromDoubles(1.0, -1.0));
	PyTuple_SetItem(mapping_values, 2, PyComplex_FromDoubles(-1.0, 1.0));
	PyTuple_SetItem(mapping_values, 3, PyComplex_FromDoubles(-1.0, -1.0));
	
	return nucleotide_mapping(raw_seq, seq_size, mapping_values);
}

PyObject* paired_numeric(char* raw_seq, unsigned seq_size){
	PyObject* mapping_values = PyTuple_New(4);
	
	PyTuple_SetItem(mapping_values, 0, PyLong_FromLong(1));
	PyTuple_SetItem(mapping_values, 1, PyLong_FromLong(1));
	PyTuple_SetItem(mapping_values, 2, PyLong_FromLong(-1));
	PyTuple_SetItem(mapping_values, 3, PyLong_FromLong(-1));
	
	return nucleotide_mapping(raw_seq, seq_size, mapping_values);
}

PyObject* integer(char* raw_seq, unsigned seq_size){
	PyObject* mapping_values = PyTuple_New(4);
	
	PyTuple_SetItem(mapping_values, 0, PyLong_FromLong(2));
	PyTuple_SetItem(mapping_values, 1, PyLong_FromLong(0));
	PyTuple_SetItem(mapping_values, 2, PyLong_FromLong(1));
	PyTuple_SetItem(mapping_values, 3, PyLong_FromLong(3));
	
	return nucleotide_mapping(raw_seq, seq_size, mapping_values);
}

PyObject* real(char* raw_seq, unsigned seq_size){
	PyObject* mapping_values = PyTuple_New(4);
	
	PyTuple_SetItem(mapping_values, 0, PyFloat_FromDouble(-1.5));
	PyTuple_SetItem(mapping_values, 1, PyFloat_FromDouble(1.5));
	PyTuple_SetItem(mapping_values, 2, PyFloat_FromDouble(0.5));
	PyTuple_SetItem(mapping_values, 3, PyFloat_FromDouble(-0.5));
	
	return nucleotide_mapping(raw_seq, seq_size, mapping_values);
}
