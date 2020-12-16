#ifndef DATA_H
#define DATA_H 

typedef void SegmentWriter(FILE*, PyObject*, size_t);
typedef PyObject* SegmentReader(char*, unsigned);
typedef PyObject* EncodedSeqsReader(char*);

PyObject* collect_raw_data(char* source);

SegmentWriter write_float_segment;
SegmentWriter write_int_segment;
SegmentWriter write_complex_segment;

SegmentReader read_float_segment;
SegmentReader read_int_segment;



#include "./data_one.h"
#include "./data_many.h"

#endif // DATA_H