#ifndef MAPPING_H
#define MAPPING_H

#include <math.h>

#define MAPPING_NUM 16

typedef PyObject* mapping(char*, unsigned);
typedef enum {true, false} bool;

#include "./mapping_one.h"
#include "./mapping_many.h"


#endif // MAPPING_H