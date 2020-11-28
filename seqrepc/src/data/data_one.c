/* -  -  -  -  -  -  -  -  WRITE ROTINES  -  -  -  -  -  -  -   */
PyObject* write_eiip(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_float_segment);
}

PyObject* write_atomic(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_imaginary(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_complex_segment);
}

PyObject* write_dnawalk(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_real(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_float_segment);
}

PyObject* write_integer(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_binary2b(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_binary4b(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_paired_numeric(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_molecular_mass(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_one(seqs, seqs_info, dst, &write_int_segment);
}

/* -  -  -  -  -  -  -  -  READ ROTINES  -  -  -  -  -  -  -   */
PyObject* read_integer(char* source){
    return read_one(&read_int_segment, source);
}

PyObject* read_real(char* source){
    return read_one(&read_float_segment, source);
}

PyObject* read_dna_walk(char* source){
    return read_one(&read_int_segment, source);
}

PyObject* read_imaginary(char* source){
    return read_one(&read_float_segment, source);
}

PyObject* read_atomic(char* source){
    return read_one(&read_int_segment, source);
}

PyObject* read_eiip(char* source){
    return read_one(&read_float_segment, source);
}

PyObject* read_molecular_mass(char* source){
    return read_one(&read_int_segment, source);
}

PyObject* read_paired_numeric(char* source){
    return read_one(&read_int_segment, source);
}

PyObject* read_binary2b(char* source){
    return read_one(&read_int_segment, source);
}

PyObject* read_binary4b(char* source){
    return read_one(&read_int_segment, source);
}


