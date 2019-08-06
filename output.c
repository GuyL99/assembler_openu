int print_to_ee(symbol * head_symbol,char name1[31], int valer){
	symbol *curr = head_symbol;
	char new_name[31];
	FILE *FP;
	if(valer){
	FP = fopen("machine.ent","a");
	}else{
	FP = fopen("machine.ext","a");
	}
	while(curr){
		if(!strcmp(curr->name,name1)){
			strncpy(new_name,curr->name,strlen(curr->name)-1);
		printf("%s %u\n",new_name,curr->value);

			fprintf(FP,"%s %u\n",curr->name,curr->value);	
			break;	
		}
		curr = curr->next;
	}
	fclose(FP);
	return 1;
}
void write_code_to_file(code *head){
	FILE * FP = NULL;
	int i;
	code *curr = head;
	FP = fopen("machine.ob","a");
	while (curr){
		for(i=0;i<14;i++){
			if (curr->machine_code[i]==1){
				fprintf(FP,"1");
			}else{
				fprintf(FP,"0");
			}
		}
		curr = curr->next;
	}
	fclose(FP);
}
