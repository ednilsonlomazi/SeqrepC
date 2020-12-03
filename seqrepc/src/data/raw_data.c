char* get_file_str(char* source){
	char* file_str = NULL;
	long length;

	FILE* file = fopen(source, "rb");
	if (file){
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);
		file_str = (char*) malloc(length);
		if (file_str){
		    fread(file_str, 1, length, file);
		}
	}	
	if(file)
		fclose(file);
	return file_str;
}
