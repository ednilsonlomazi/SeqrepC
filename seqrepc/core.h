#ifndef CORE
#define CORE

#include <Python.h>

typedef enum {true, false} bool;

#include "./encoder.h"
#include "./data.h"

typedef struct RWStructOneD{
	write_one_d* write;
	EncodedSeqsReader* read;
} RWStructOneD;

typedef struct RWStructManyD{
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
PyObject* collect_encodings(char*, char*);
PyObject* collect_fasta(char*);

#include "./hash_tables.h"


#endif // CORE