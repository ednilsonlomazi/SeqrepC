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
            return mps->one_d->rws->write(seqs, seqs_info, dst);
        return mps->many_d->rws->write(seqs, seqs_info, dst);
    }
    mp_hash_table_init();
    return store(seqs, seqs_info, mapping_signature, dst);
}