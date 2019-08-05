#include "dectobinary.c"

void append_code(code *head, int machine_code){
	code * current = head;
        while (current->next != NULL) {
        	current = current->next;
        }
        current->next = malloc(sizeof(list));
	*current->next->machine_code = machine_code;
        current->next->next = NULL;
}
void write_code_to_file(code *head){
	FILE * FP = NULL;
	int i;
	code *curr = head;
	/*fopen("code.ext","a");
	fopen("code.ent","a");*/
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




int circ2(list * head_list, data * head_data, symbol * head_symbol, code *head_code){
	/*about a mile from being any close to ready, need some help if u can provide any...*/
	list *curr = head_list;
	list *curr2 = head_list;
	symbol *curr_sym = head_symbol;
	code *curr_code = head_code;
	int imFLAG = 0;
	int dirFLAG = 0;
	int code_val = 0 ;
	while (curr!=NULL){
		if (!strcmp(curr->word,".define") || !strcmp(curr->word,".data") || !strcmp(curr->word,".extern") || strcmp(curr->word,".string")){
			
		}else{
			while(curr2->word[strlen(curr2->word)]!='\n'){
				if(!imFLAG && curr2->word[0]=='#'){
					curr_code->machine_code[13] = 0;
					curr_code->machine_code[12] = 0;
					imFLAG = 1;
				}
				if(!imFLAG){
					while (curr_sym->next){
						if(!strcmp(curr2->word,head_symbol->name)){
							if(curr_sym->type ==3){
								curr_code->machine_code[13] = 1;
                                                                curr_code->machine_code[12] = 0;
								dirFLAG=1;
							}else{
								curr_code->machine_code[13] = 0;
                                                                curr_code->machine_code[12] = 1;
								dirFLAG=1;
							}
						}
						curr_sym = curr_sym->next;
					}
					if(!dirFLAG){
						if(curr2->word[strlen(curr2->word)-1] == ']'){
						
						}
					
					}
				}
				curr2= curr2->next;
			}
			if(!head_code->machine_code){
				*head_code->machine_code =*curr_code->machine_code;
				head_code->next = NULL;
			}else{
				append_code(head_code,code_val);
			
			}
		}
        	curr = curr->next;
        }
	write_code_to_file(head_code);
	return 0;
}
