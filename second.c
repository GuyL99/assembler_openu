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

int check_miun(list *curr){
	int i;
	int flag = 0;
	if(curr->word[0] == '#'){
		return 0;
	}
	switch(conv_enum3(curr->word)){
		case r0:
			return 3;
		case r1:
                	return 3;
		case r2:
                	return 3;
		case r3:
                	return 3;
                case r4:
                	return 3;
                case r5:
                	return 3;
		case r6:
                	return 3;
                case r7:
                	return 3;
		case rNONE:
			break;
	}
	for(i=0;i<strlen(curr->word);i++){
		if(curr->word[i] == '['){
			flag = 1;
		}
	}
	if(flag){
		return 2;
	} 
	switch(conv_enum2(curr->word)){
		case str:
		       return 1;	
		case dat:
		       return 1;	
		case define:
		       return 1;	
		case ext:
		       return 1;	
		case ent:
		       return 1;	
		case None:
		      printf("reached end, it's probably an error, func check miun"); 
		      return 55;
	}
	printf("reached end, it's probably an error, func check miun"); 
	return 55;

}
int type_one_code(list *head){
	int m_code=0;
	list *curr = head;
	int type_m;
	int type_m2;
	if(curr->word[strlen(curr->word)-1]==':'){
		curr = curr->next;
	}
	switch(conv_enum(curr->word)){
		case mov:
			type_m = check_miun(curr->next);	
			type_m2 = check_miun(curr->next->next->next);	
			break;
		case cmp:
                	type_m = check_miun(curr->next);	
			type_m2 = check_miun(curr->next->next->next);	
			break;
		case add:
                	type_m = check_miun(curr->next);	
                	type_m2 = check_miun(curr->next->next->next);	
                	break;
                case sub:
                	type_m = check_miun(curr->next);	
                	type_m2 = check_miun(curr->next->next->next);	
                	break;
		case lea:
                	type_m = check_miun(curr->next);	
                	type_m2 = check_miun(curr->next->next->next);	
                	break;
		default:
			break;
	}
	return m_code;

}

int type_two_code(list *head){
	int m_code=0;
        list *curr = head;
        int type_m;
        if(curr->word[strlen(curr->word)-1]==':'){
        	curr = curr->next;
        }
        switch(conv_enum(curr->word)){
		case not:
                	type_m = check_miun(curr->next);	
                	break;
		case dec:
                	type_m = check_miun(curr->next);	
                	break;
		case inc:
                	type_m = check_miun(curr->next);	
                	break;
		case jmp:
                	type_m = check_miun(curr->next);	
                	break;
		case bne:
                	type_m = check_miun(curr->next);	
                	break;
		case red:
                	type_m = check_miun(curr->next);	
                	break;
		case prn:
                	type_m = check_miun(curr->next);	
                	break;
		case jsr:
                	type_m = check_miun(curr->next);	
                	break;
		case rts:
                	type_m = check_miun(curr->next);	
                	break;
		case stop:
                	type_m = check_miun(curr->next);	
                	break;
		default:
			break;
		}
	return m_code;
}



int circ2(list *head_list, data *head_data, symbol *head_symbol, code *head_code){
	list *curr = head_list;
	symbol *curr_sym = head_symbol;
	data *curr_data = head_data;
	code *curr_code = head_code;
	int code_val = 0 ;
	while (curr){
			if(!strcmp(curr->word,"mov")){
				code_val = type_one_code(curr);	
			}
			if(!strcmp(curr->word,"cmp")){
                        	code_val = type_one_code(curr);	
                        }
        	curr = curr->next;
        }
	/*write_code_to_file(head_code);*/
	return 1;
}
