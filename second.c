#include "dectobinary.c"
#include "helpers.h"

void append_code(code *head, int machine_code){
	code * current = head;
        while (current->next) {
        	current = current->next;
        }
        current->next = malloc(sizeof(code));
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
int check_are(symbol *head,char name1[31]){
	symbol *curr = head;
	if(conv_enum3(name1)!=rNONE || name1[0]=='#'){
		return 0;
	} 
	while(curr){
		if(!strcmp(curr->name,name1)){
			if(curr->type ==external){
				return 1;
			}
			return 2;	
		}	
		curr = curr->next;
	}
	return 55;


}
int type_one_code(list *head,int opcode, symbol *head_sym){
	int m_code=0;
	list *curr = head;
	int type_m=check_miun(curr->next);	
	int type_m2=check_miun(curr->next->next->next);	
	if(type_m||type_m2){}
	return m_code;

}

int type_two_code(list *head,int opcode){
	int m_code=0;
        list *curr = head;
        int type_m=check_miun(curr->next);	;
	if(type_m){}
	return m_code;
}



int circ2(list *head_list, data *head_data, symbol *head_s, code *head_code){
	list *curr = head_list;
	int code_val = 0 ;
	while (curr){
		switch(conv_enum(curr->word)){
			case mov:	
				code_val = type_one_code(curr,0,head_s);
				break;
			case cmp:	
				code_val = type_one_code(curr,1,head_s);
				break;
			case add:	
				code_val = type_one_code(curr,2,head_s);
				break;
			case sub:	
				code_val = type_one_code(curr,3,head_s);
				break;
			case lea:	
				code_val = type_one_code(curr,6,head_s);
				break;
			case inc:	
				code_val = type_two_code(curr,7);
				break;
			case clr:	
                        	code_val = type_two_code(curr,7);
                        	break;
			case dec:	
				code_val = type_two_code(curr,8);
				break;
			case jmp:	
				code_val = type_two_code(curr,9);
				break;
			case rts:	
				code_val = type_two_code(curr,14);
				break;
			case not:	
				code_val = type_two_code(curr,4);
				break;
			case jsr:	
				code_val = type_two_code(curr,13);
				break;
			case prn:	
				code_val = type_two_code(curr,12);
				break;
			case red:	
				code_val = type_two_code(curr,11);
				break;
			case bne:	
				code_val = type_two_code(curr,10);
				break;
			case stop:
				code_val = type_two_code(curr,15);
				break;
			default:
				break;
		
		
		
		}
		append_code(head_code,code_val);
        	curr = curr->next;
        }
	return 1;
}
