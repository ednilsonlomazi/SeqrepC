#ifndef DATA
#define DATA

typedef void SegmentWriter(FILE*, PyObject*);

SegmentWriter write_float_segment;
SegmentWriter write_int_segment;
SegmentWriter write_complex_segment;

#include "./data_one.h"
#include "./data_many.h"

#endif // DATA