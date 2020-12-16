#ifndef DATA_ONE_H
#define DATA_ONE_H

typedef PyObject* write_one_d(PyObject*, PyObject*, char*);

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

EncodedSeqsReader read_atomic;
EncodedSeqsReader read_binary2b;
EncodedSeqsReader read_binary4b;
EncodedSeqsReader read_dnawalk;
EncodedSeqsReader read_eiip;
EncodedSeqsReader read_imaginary;
EncodedSeqsReader read_real;
EncodedSeqsReader read_integer;
EncodedSeqsReader read_paired_numeric;
EncodedSeqsReader read_molecular_mass;


#endif // DATA_ONE_H