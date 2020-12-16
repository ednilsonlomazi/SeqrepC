#ifndef ENCODER_H
#define ENCODER_H

#include <math.h>

#define MAPPING_NUM 16

typedef PyObject* mapping(char*);

#include "./mapping_one.h"
#include "./mapping_many.h"


#endif // ENCODER_H