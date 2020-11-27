
PyObject* write_many(PyObject* seqs, PyObject* seqs_info, char* dst, SegmentWriter* segment_writer){
    
    FILE *fp;
    fp = fopen(dst, "w+");

    for (int seq_id = 0; seq_id < PyTuple_Size(seqs); ++seq_id){
        PyObject* seq_encoded = PyTuple_GetItem(seqs, seq_id);
        fprintf(fp, "%s\n", PyBytes_AsString(PyTuple_GetItem(seqs_info, seq_id)));
        for (int i = 0; i < PyTuple_Size(seq_encoded); ++i){
        	(*segment_writer)(fp, PyTuple_GetItem(seq_encoded, i));
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return Py_True;
}

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
