
PyObject* write_one(PyObject* seqs, PyObject* seqs_info, char* dst, SegmentWriter* segment_writer){
    FILE *fp;
    fp = fopen(dst, "w+");
    for (int seq_id = 0; seq_id < PyTuple_Size(seqs); ++seq_id){ 
        fprintf(fp, "%s\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)));
        (*segment_writer)(fp, PyTuple_GetItem(seqs, seq_id));
        fprintf(fp, "\n");    
    } 
    fclose(fp);
    return Py_True;
}


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



