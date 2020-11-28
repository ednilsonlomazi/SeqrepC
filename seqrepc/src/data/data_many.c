/* -  -  -  -  -  WRITE ROTINES  -  -  -  -  -   */
PyObject* write_voss(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_many(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_cgr(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_many(seqs, seqs_info, dst, &write_float_segment);
}

PyObject* write_icgr(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_many(seqs, seqs_info, dst, &write_int_segment);
}

PyObject* write_zcurve(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_many(seqs, seqs_info, dst, &write_float_segment);
}

PyObject* write_liao(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_many(seqs, seqs_info, dst, &write_float_segment);
}

PyObject* write_tetrahedron(PyObject* seqs, PyObject* seqs_info, char* dst){
    return write_many(seqs, seqs_info, dst, &write_float_segment);
}

/* -  -  -  -  -  READ ROTINES  -  -  -  -  -   */

PyObject* read_cgr(char* source){
	return read_many(&read_float_segment, source);
}

PyObject* read_voss(char* source){
	return read_many(&read_int_segment, source);
}

PyObject* read_zcurve(char* source){
	return read_many(&read_float_segment, source);
}

PyObject* read_icgr(char* source){
	return read_many(&read_int_segment, source);
}

PyObject* read_tetrahedron(char* source){
	return read_many(&read_float_segment, source);
}

PyObject* read_liao(char* source){
	return read_many(&read_float_segment, source);
}