#ifndef CORE
#define CORE

#include <Python.h>

#include "./encoder.h"
#include "./data.h"

typedef struct RWStructOneD{
	unsigned seq_size;
	write_one_d* write;
	EncodedSeqsReader* read;
} RWStructOneD;

typedef struct RWStructManyD{
	unsigned seq_size;
	write_many_d* write;
	EncodedSeqsReader* read;
} RWStructManyD;

typedef struct MpStructOneD{
	char* signature;
	mapping* mp;
	RWStructOneD* rws;
} MpStructOneD;

typedef struct MpStructManyD{
	char* signature;
	unsigned dim;
	mapping* mp;
	RWStructManyD* rws;
} MpStructManyD;

/* ## The Fundamental Struct of the whole SeqrepC ##  */
typedef struct MpStruct{
	MpStructOneD* one_d;
	MpStructManyD* many_d;
} MpStruct;

PyObject* encode(char*, unsigned, char*);
PyObject* store(PyObject*, PyObject*, char*, char*);
PyObject* collect(char*, char*);

#include "./hash_tables.h"


#endif // CORE