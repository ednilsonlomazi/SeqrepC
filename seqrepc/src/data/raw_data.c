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
