#ifndef DATA_MANY
#define DATA_MANY


typedef PyObject* write_many_d(PyObject*, PyObject*, char*);
typedef PyObject* read_many_d(void***, char** seq_info, char* dir);

write_many_d write_cgr;
write_many_d write_voss;
write_many_d write_zcurve;
write_many_d write_liao;
write_many_d write_icgr;
write_many_d write_tetrahedron;

#endif // DATA_MANY