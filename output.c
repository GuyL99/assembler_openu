void print_to_ee(char name1[31], int valer,int ic){
	FILE *FP;
	if(valer){
	FP = fopen("machine.ent","a");
	}else{
	FP = fopen("machine.ext","a");
	}
	fprintf(FP,"%s %u\n",name1,ic);	
	fclose(FP);
}
void write_code_to_file(int m_code,int ic){
	FILE * FP = NULL;
	char b[17];
    	int z;
    	b[0] = '\0';
    	for (z = 32786; z > 0; z >>= 1)
    	{
		if(z>8192){
			continue;
		}
        	strcat(b, ((m_code & z) == z) ? "1" : "0");
    	}
	FP = fopen("machine.ob","a");
	fprintf(FP,"%d %s\n",ic,b);
	fclose(FP);
}
