char* get_file_str(char* source){
	char* file_str = NULL;
	size_t length;

	FILE* file = fopen(source, "rb");
	if(file == NULL){
		fprintf(stderr, "%s %s\n", "Error on open fasta file", source);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);

	fseek(file, 0, SEEK_SET);
	if ((file_str = malloc(length)) != NULL){
		if(fread(file_str, 1, length, file) < length){
			fprintf(stderr, "%s %s\n", "Error on reading fasta file", source);
			free(file_str); // not here
			file_str = NULL;
			return NULL;
		}
	}
	if(file != NULL){
		fclose(file);	
	}
	return file_str;
} 

bool is_genomic_sequence(char* seq){
	bool is_gen_seq = true;
	for (int i = 0; i < strlen(seq); ++i){
		char base = seq[i];
		if(base != 'A' && base != 'T' && base != 'U' && base != 'C' && base != 'G'){
			is_gen_seq = false;
		}
	}
	return is_gen_seq;
}