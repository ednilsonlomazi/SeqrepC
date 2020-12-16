#ifndef DATA_MANY_H
#define DATA_MANY_H 


typedef PyObject* write_many_d(PyObject*, PyObject*, char*);

write_many_d write_cgr;
write_many_d write_voss;
write_many_d write_zcurve;
write_many_d write_liao;
write_many_d write_icgr;
write_many_d write_tetrahedron;

EncodedSeqsReader read_cgr;
EncodedSeqsReader read_voss;
EncodedSeqsReader read_zcurve;
EncodedSeqsReader read_liao;
EncodedSeqsReader read_icgr;
EncodedSeqsReader read_tetrahedron;

#endif // DATA_MANY_H