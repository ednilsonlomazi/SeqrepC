
PyObject* cgr(char* raw_seq, unsigned seq_size){

	PyObject* tuple_x = PyTuple_New(seq_size + 1);
	PyObject* tuple_y = PyTuple_New(seq_size + 1);
	PyObject* tuple = PyTuple_New(2);

	char base;
	double last_x = 0.5;
	double last_y = 0.5;
	
	PyTuple_SetItem(tuple_x, 0, PyFloat_FromDouble(last_x));
	PyTuple_SetItem(tuple_y, 0, PyFloat_FromDouble(last_y));
	
	for (int i = 0; i < seq_size; ++i){ 

		base = raw_seq[i]; // [0, N-1]
		
		if(base == 'T' || base == 'U') last_x += 1;
		else{
			if(base == 'C') last_y += 1;
			else{
				if(base == 'G'){
					last_x += 1;
					last_y += 1;
				}else{
					if(base != 'A'){
						PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
						return NULL;
					}
				};	
			}	
		}
		
		last_x *= 0.5;
		last_y *= 0.5;
		PyTuple_SetItem(tuple_x, i+1, PyFloat_FromDouble(last_x)); // [1, N]
		PyTuple_SetItem(tuple_y, i+1, PyFloat_FromDouble(last_y)); // [1, N]	
	}
	
	PyTuple_SetItem(tuple, 0, tuple_x);
	PyTuple_SetItem(tuple, 1, tuple_y);
	
	return tuple;
}

PyObject* zcurve(char* raw_seq, unsigned seq_size){
	PyObject* tuple_x = PyTuple_New(seq_size+1);
	PyObject* tuple_y = PyTuple_New(seq_size+1);
	PyObject* tuple_z = PyTuple_New(seq_size+1);
	PyObject* tuple = PyTuple_New(3);

	long int count_a, count_t, count_c, count_g;
	count_a = count_t = count_c = count_g = 0;
	long double x, y, z;

	PyTuple_SetItem(tuple_x, 0, PyLong_FromLong(0));
	PyTuple_SetItem(tuple_y, 0, PyLong_FromLong(0));
	PyTuple_SetItem(tuple_z, 0, PyLong_FromLong(0));

	for (int i = 0; i < seq_size; ++i){
		if(raw_seq[i] == 'A') count_a++;
		else{
			if(raw_seq[i] == 'T') count_t++;
			else{
				if(raw_seq[i] == 'C') count_c++;
				else{
					if(raw_seq[i] == 'G') count_g++;
					else{
						PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
						return NULL;
					}
				}
			}
		}

		x = (count_a + count_g) - (count_c + count_t);
		y = (count_a + count_c) - (count_g + count_t);
		z = (count_a + count_t) - (count_g + count_c);
		
		PyTuple_SetItem(tuple_x, i+1, PyFloat_FromDouble(x));
		PyTuple_SetItem(tuple_y, i+1, PyFloat_FromDouble(y));
		PyTuple_SetItem(tuple_z, i+1, PyFloat_FromDouble(z));
	}
	PyTuple_SetItem(tuple, 0, tuple_x);
	PyTuple_SetItem(tuple, 1, tuple_y);
	PyTuple_SetItem(tuple, 2, tuple_z);

	return tuple;

}

PyObject* icgr(char* raw_seq, unsigned seq_size){

	PyObject* tuple_x = PyTuple_New(seq_size);
	PyObject* tuple_y = PyTuple_New(seq_size);
	PyObject* tuple = PyTuple_New(2);

	char base;
	long long int last_x = 1; // SEE IF THE USER IS USING C99 for suport long long int
	long long int last_y = 1;

	if(raw_seq[0]=='T' || raw_seq[0]=='U') last_x = -1;
	else{
		if(raw_seq[0]=='C') last_x = last_y = -1;
		else{
			if(raw_seq[0]=='G') last_y = -1;
			else{
				PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
				return NULL;
			}
		}
	}
	
	PyTuple_SetItem(tuple_x, 0, PyFloat_FromDouble(last_x));
	PyTuple_SetItem(tuple_y, 0, PyFloat_FromDouble(last_y));
	
	for (int i = 1; i < seq_size; ++i){ 

		base = raw_seq[i]; // [1, N-1]
		
		if(base == 'A'){
			last_x += pow(2, i);
			last_y += pow(2, i);
		}else{
			if(base == 'T' || base == 'U'){
				last_x -= pow(2, i);
				last_y += pow(2, i);
			}else{
				if(base == 'C'){
					last_x -= pow(2, i);
					last_y -= pow(2, i);
				}else{
					if(base=='G'){
						last_x += pow(2, i);
						last_y -= pow(2, i);	
					}else{
						PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
						return NULL;			
					}
				}
			}
		}
		
		PyTuple_SetItem(tuple_x, i, PyFloat_FromDouble(last_x)); // [1, N-1]
		PyTuple_SetItem(tuple_y, i, PyFloat_FromDouble(last_y)); // [1, N-1]	
	}
	
	PyTuple_SetItem(tuple, 0, tuple_x);
	PyTuple_SetItem(tuple, 1, tuple_y);
	
	return tuple;
}

PyObject* liao(char* raw_seq, unsigned seq_size){
	const double m = 3.0/4.0, sqrt_n = sqrt(0.5);

	PyObject* tuple_x = PyTuple_New(seq_size+1);
	PyObject* tuple_y = PyTuple_New(seq_size+1);
	PyObject* tuple = PyTuple_New(2);

	long int count_a, count_t, count_c, count_g;
	count_a = count_t = count_c = count_g = 0;
	long double x, y;

	PyTuple_SetItem(tuple_x, 0, PyLong_FromLong(0));
	PyTuple_SetItem(tuple_y, 0, PyLong_FromLong(0));

	for (int i = 0; i < seq_size; ++i){
		if(raw_seq[i] == 'A') count_a++;
		else{
			if(raw_seq[i] == 'T') count_t++;
			else{
				if(raw_seq[i] == 'C') count_c++;
				else{
					if(raw_seq[i] == 'G') count_g++;
					else{
						PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
						return NULL;
					}
				}
			}
		}

		x = m*(count_a + count_t) + sqrt_n*(count_g + count_c);
		y = m*(count_c - count_g) + sqrt_n*(count_t - count_a);
		
		PyTuple_SetItem(tuple_x, i+1, PyFloat_FromDouble(x));
		PyTuple_SetItem(tuple_y, i+1, PyFloat_FromDouble(y));
	}
	
	PyTuple_SetItem(tuple, 0, tuple_x);
	PyTuple_SetItem(tuple, 1, tuple_y);

	return tuple;

}


PyObject* tetrahedron(char* raw_seq, unsigned seq_size){
	// Mendizabal-Ruiz et al. (2017) On DNA numerical representations for genomic similarity computation

	PyObject* tuple_x = PyTuple_New(seq_size);
	PyObject* tuple_y = PyTuple_New(seq_size);
	PyObject* tuple_z = PyTuple_New(seq_size);
	PyObject* tuple = PyTuple_New(3);
	char base;

	for (int i = 0; i < seq_size; ++i){
		base = raw_seq[i];

		// a 'for structure' inside each condition would be a more clean way, but, i think that the processor will not like that... i guess...
		// imagine a seq_size like 3 Milion. 3 Milions of for just for 3 iterations... 
		if(base == 'A'){ 
				PyTuple_SetItem(tuple_x, i, PyFloat_FromDouble(0.0));
				PyTuple_SetItem(tuple_y, i, PyFloat_FromDouble(0.0));
				PyTuple_SetItem(tuple_z, i, PyFloat_FromDouble(1.0));
			}else{
				if(base == 'T'){
					PyTuple_SetItem(tuple_x, i, PyFloat_FromDouble((2*sqrt(2))/3.0));
					PyTuple_SetItem(tuple_y, i, PyFloat_FromDouble(0.0));
					PyTuple_SetItem(tuple_z, i, PyFloat_FromDouble(-1.0/3.0));
				}else{
					if(base == 'C'){
						PyTuple_SetItem(tuple_x, i, PyFloat_FromDouble(-sqrt(2)/3.0));
						PyTuple_SetItem(tuple_y, i, PyFloat_FromDouble(sqrt(6)/3.0));
						PyTuple_SetItem(tuple_z, i, PyFloat_FromDouble(-1.0/3.0));
					}else{
						if(base == 'G'){
							PyTuple_SetItem(tuple_x, i, PyFloat_FromDouble(-sqrt(2)/3.0));
							PyTuple_SetItem(tuple_y, i, PyFloat_FromDouble(-sqrt(6)/3.0));
							PyTuple_SetItem(tuple_z, i, PyFloat_FromDouble(-1.0/3.0));
						}else{
							PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
							return NULL;
						}
					}
				}	
			}

	}
	
	PyTuple_SetItem(tuple, 0, tuple_x);
	PyTuple_SetItem(tuple, 1, tuple_y);
	PyTuple_SetItem(tuple, 2, tuple_z);

	return tuple;
	
}

PyObject* voss(char* raw_seq, unsigned seq_size){
	PyObject* tuple_a = PyTuple_New(seq_size);
	PyObject* tuple_t = PyTuple_New(seq_size);
	PyObject* tuple_c = PyTuple_New(seq_size);
	PyObject* tuple_g = PyTuple_New(seq_size);
	PyObject* tuple = PyTuple_New(4);

	for (int i = 0; i < seq_size; ++i){ 
		if(raw_seq[i]=='A'){
			PyTuple_SetItem(tuple_a, i, PyLong_FromLong(1));
			PyTuple_SetItem(tuple_t, i, PyLong_FromLong(0));
			PyTuple_SetItem(tuple_c, i, PyLong_FromLong(0));
			PyTuple_SetItem(tuple_g, i, PyLong_FromLong(0));
		}else{
			if(raw_seq[i]=='T'){
				PyTuple_SetItem(tuple_a, i, PyLong_FromLong(0));
				PyTuple_SetItem(tuple_t, i, PyLong_FromLong(1));
				PyTuple_SetItem(tuple_c, i, PyLong_FromLong(0));
				PyTuple_SetItem(tuple_g, i, PyLong_FromLong(0));
			}else{
				if(raw_seq[i]=='C'){
					PyTuple_SetItem(tuple_a, i, PyLong_FromLong(0));
					PyTuple_SetItem(tuple_t, i, PyLong_FromLong(0));
					PyTuple_SetItem(tuple_c, i, PyLong_FromLong(1));
					PyTuple_SetItem(tuple_g, i, PyLong_FromLong(0));
				}else{
					if(raw_seq[i]=='G'){
						PyTuple_SetItem(tuple_a, i, PyLong_FromLong(0));
						PyTuple_SetItem(tuple_t, i, PyLong_FromLong(0));
						PyTuple_SetItem(tuple_c, i, PyLong_FromLong(0));
						PyTuple_SetItem(tuple_g, i, PyLong_FromLong(1));
					}else{
						PyErr_SetString(PyExc_KeyError, "Sequence is not complete");
						return NULL;
					}
				}
			}	
		}	
	}

	PyTuple_SetItem(tuple, 0, tuple_a);
	PyTuple_SetItem(tuple, 1, tuple_t);
	PyTuple_SetItem(tuple, 2, tuple_c);
	PyTuple_SetItem(tuple, 3, tuple_g);

	return tuple;

}

