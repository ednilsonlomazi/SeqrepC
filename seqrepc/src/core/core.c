#include "../../core.h"
#include "../encoder/encoder.c"
#include "../data/data.c"
#include "./mps_struct.c"
#include "./hash_tables.c"

PyObject* encode(char* raw_seq, unsigned seq_size, char* mp_signature){
	if(mp_hash_table[0] != NULL){
		MpStruct* mps = mp_hash_table_lookup(mp_signature);
		if(mps->one_d != NULL)
			return (*(mps->one_d->mp))(raw_seq, seq_size);
		return (*(mps->many_d->mp))(raw_seq, seq_size);
	}
	mp_hash_table_init();
	return encode(raw_seq, seq_size, mp_signature);
}

PyObject* store(PyObject* seqs, PyObject* seqs_info, char* mapping_signature, char* dst){
	if(mp_hash_table[0] != NULL){
        MpStruct* mps = mp_hash_table_lookup(mapping_signature);
        if(mps->one_d != NULL)
            return (*(mps->one_d->rws->write))(seqs, seqs_info, dst);
        return (*(mps->many_d->rws->write))(seqs, seqs_info, dst);
    }
    mp_hash_table_init();
    return store(seqs, seqs_info, mapping_signature, dst);
}

PyObject* collect_encodings(char* mapping_signature, char* source){
    if(mp_hash_table[0] != NULL){
        MpStruct* mps = mp_hash_table_lookup(mapping_signature);
        if(mps->one_d != NULL)
            return (*(mps->one_d->rws->read))(source);
        return (*(mps->many_d->rws->read))(source);
    }
    mp_hash_table_init();
    return collect_encodings(mapping_signature, source);
}

PyObject* collect_fasta(char* source){
    PyObject* seqs_data = PyList_New(0);
    PyObject* seqs_info = PyList_New(0);
    PyObject* seqs_lines = NULL;
    PyObject* fasta_pack = PyTuple_New(2);
 
    char* file_str = get_file_str(source);

    const char* s = "\n";
    char* token = strtok(file_str, s);
    while( token != NULL ){
        if(token[0] == '>'){
            if(seqs_lines != NULL){
                PyList_Append(seqs_data, seqs_lines);   
            }
            PyList_Append(seqs_info, PyUnicode_FromString(token));
            seqs_lines = PyList_New(0);
        }else{
            PyList_Append(seqs_lines, PyUnicode_FromString(token));
        }

        if((token = strtok(NULL, s)) == NULL)
            PyList_Append(seqs_data, seqs_lines);
    }

    PyTuple_SetItem(fasta_pack, 0, seqs_data);
    PyTuple_SetItem(fasta_pack, 1, seqs_info);
    
    if(file_str){
        free(file_str);
        file_str = NULL;
    }
    return fasta_pack;
}

