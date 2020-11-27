#ifndef DATA_ONE
#define DATA_ONE

typedef PyObject* write_one_d(PyObject*, PyObject*, char*);
typedef bool read_one_d(void);

write_one_d write_atomic;
write_one_d write_binary2b;
write_one_d write_binary4b;
write_one_d write_dnawalk;
write_one_d write_eiip;
write_one_d write_imaginary;
write_one_d write_real;
write_one_d write_integer;
write_one_d write_paired_numeric;
write_one_d write_molecular_mass;


#endif // DATA_ONE