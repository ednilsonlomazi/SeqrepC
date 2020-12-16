char* get_file_str(char* source){

	FILE* file = fopen(source, "rb");
	if(file == NULL){
		PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to open the file");
		return NULL;
	}

	char* file_str = NULL;
	size_t length; 

	fseek(file, 0, SEEK_END);
	length = ftell(file);

	fseek(file, 0, SEEK_SET);
	if ((file_str = malloc(length)) != NULL){
		if(fread(file_str, 1, length, file) < length){
			free(file_str);
			file_str = NULL;
			PyErr_SetString(PyExc_ValueError, "An error ocurred when trying to read the file");
			return NULL;
		}
	}
	if(file != NULL){
		fclose(file);	
	}
	return file_str;
} 

bool is_genomic_sequence(char* seq){
	unsigned seq_size = strlen(seq);
	bool is_gen_seq = true;
	for (int i = 0; i < seq_size; ++i){
		char base = seq[i];
		if(base != 'A' && base != 'T' && base != 'U' && base != 'C' && base != 'G'){
			is_gen_seq = false;
		}
	}
	return is_gen_seq;
}
