unsigned hash(const char* mp_signature){
	unsigned long hash = 5381;
    int c;
    while ((c = *mp_signature++)){
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % MAPPING_NUM;
}
 

MpStruct* mp_hash_table_lookup(const char* mp_signature){
	int start = hash(mp_signature);
	char* cmp_signature = NULL;

	for (int i = 0; i < MAPPING_NUM; ++i){		
		int next = (i + start) % MAPPING_NUM;
		if(mp_hash_table[next] != NULL){
			if(mp_hash_table[next]->one_d != NULL){
				cmp_signature = mp_hash_table[next]->one_d->signature;
			}else{
				cmp_signature = mp_hash_table[next]->many_d->signature;
			}

			if(strcmp(cmp_signature, mp_signature)==0){
				return mp_hash_table[next];
			}
		}
	}
	PyErr_SetString(PyExc_KeyError, "This numeric representation signature is not present on SeqrepC");	
	return NULL;
}

bool mp_hash_table_insert(MpStruct* mps_item){
	char* signature = NULL;
	if(mps_item->one_d != NULL){
		signature = mps_item->one_d->signature;
	}else{
		signature = mps_item->many_d->signature;
	}

	int start = hash(signature);
	
	for (int i = 0; i < MAPPING_NUM; ++i){
		int next = (i + start) % MAPPING_NUM;
		if(mp_hash_table[next] == NULL){
			mp_hash_table[next] = mps_item;
			return true;
		}
	}	
	return false;
}

void mp_hash_table_init(){
	for (int i = 0; i < MAPPING_NUM; ++i) mp_hash_table[i] = NULL;
	for (int i = 0; i < MAPPING_NUM; ++i) mp_hash_table_insert(&mps[i]);
}