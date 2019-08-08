#include "dectobinary.c"
#include "output.c"
#include "helpers.h"
int check_miun(char word[31]){
	int i;
	int flag = 0;
	if(word[0] == '#'){
		return 0;
	}
	if(conv_enum3(word)!=rNONE){
		return 3;
	}
	for(i=0;i<strlen(word);i++){
		if(word[i] == '['){
			flag = 1;
			break;
		}
	}
	if(flag){
		return 2;
	} 
	return 55;

}
int type_one_code(list *currr,int opcode, symbol *head_sym,int ic){
	int m_code=0;
	list *curr = currr;
	symbol *curr_sym = head_sym;
	int type_m=check_miun(curr->next->word);	
	int type_m2=check_miun(curr->next->next->next->word);
	int coded = FALSE;
	char first_ind[31];
	char second_ind[31];
	char s_word[31];
	int v = 0;
	int u = 0;
	m_code|=type_m2<<2;
	m_code|=type_m<<4;
	m_code|=opcode<<6;
	write_code_to_file(m_code,ic);
	m_code = 0;
	++ic;
	curr = curr->next;
	switch(type_m){
		case 3:
			m_code|=conv_enum3(curr->word)<<5;
			if(type_m==type_m2){
				m_code|=conv_enum3(curr->next->next->word)<<2;
				coded = TRUE;
			}
			write_code_to_file(m_code,ic);
			ic++;
			break;
		case 2:
			while(curr->word[v]!='['){
				first_ind[v] = curr->word[v];
				v++;	
			}
			v++;
			while(curr->word[v]!=']'){
				second_ind[u] = curr->word[v];
				u++;
				v++;
			}
			while(curr_sym){
				if(!strcmp(curr_sym->name,first_ind)){
					if(curr_sym->type == external){
						m_code|=1;
					}else{
						m_code|=2;
						m_code|=curr_sym->value<<2;
					}

				}
				curr_sym = curr_sym->next;
			}
			write_code_to_file(m_code,ic);
			ic++;
			m_code = 0;
			if(!isdigit(second_ind)){
				while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<2;
                                		}
                                                break;                       
                                	}
                                	curr_sym = curr_sym->next;
                                }
        		}else{
        			m_code|=atoi(curr->word);
        		}
			write_code_to_file(m_code,ic);
			ic++;
			break;
		case 1:
			m_code|=2;
			while(curr_sym){
                        	if(!strcmp(curr_sym->name,second_ind)){
                        		if(curr_sym->type == external){
						m_code = 0;
                        			m_code|=1;
                        		}else{
                        			m_code|=curr_sym->value<<2;
                        		}
        				write_code_to_file(m_code,ic);
					break;
                                                                           
                        	}
                        	curr_sym = curr_sym->next;
                        }
			ic++;
			break;
		case 0:
			if(!isdigit(curr->word)){
				strcpy(s_word,strtok(curr->word,"#"));
				while(curr_sym){
                                	if(!strcmp(curr_sym->name,s_word)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<2;
                                		}
						break;
                                                                                   
                                	}
                                	curr_sym = curr_sym->next;
				}
			}else{
				m_code|=atoi(curr->word);
			}
        		write_code_to_file(m_code,ic);
			ic++;
			break;
	}
	m_code = 0;
	curr_sym = head_sym;
	curr = curr->next->next;
	memset(first_ind, '\0', sizeof first_ind);
	memset(second_ind, '\0', sizeof second_ind);
	switch(type_m2){
		case 3:
			if(!coded){
				m_code|=conv_enum3(curr->word)<<2;
        			write_code_to_file(m_code,ic);
				ic++;
			}
			break;
		case 2:
			while(curr->word[v]!='['){                                       	
                		first_ind[v] = curr->word[v];
                		v++;	
                	}
                	v++;
                	while(curr->word[v]!=']'){
                		second_ind[u] = curr->word[v];
                		u++;
                		v++;
                	}
                	while(curr_sym){
                		if(!strcmp(curr_sym->name,first_ind)){
                			if(curr_sym->type == external){
                				m_code|=1;
                			}else{
                				m_code|=2;
                				m_code|=curr_sym->value<<2;
                			}
					break;
                                                                                          
                		}
                		curr_sym = curr_sym->next;
                	}
                	write_code_to_file(m_code,ic);
			curr_sym = head_sym;
			m_code = 0;
                	ic++;
                	if(!isdigit(second_ind)){
                		while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<2;
                                		}
						break;
                                                                                   
                                	}
                                	curr_sym = curr_sym->next;
                                }
        		}else{
        			m_code|=atoi(curr->word);
        		}
                	write_code_to_file(m_code,ic);
                	ic++;
                	break;
                case 1:
                	m_code|=2;
                	while(curr_sym){
                        	if(!strcmp(curr_sym->name,second_ind)){
                        		if(curr_sym->type == external){
						m_code=0;
                        			m_code|=1;
                        		}else{
                        			m_code|=curr_sym->value<<2;
                        		}
        				write_code_to_file(m_code,ic);
					break;
                                                                           
                        	}
                        	curr_sym = curr_sym->next;
                        }
                	ic++;
                	break;
                case 0:
                	if(!isdigit(curr->word)){
				strcpy(s_word,strtok(curr->word,"#"));
                		while(curr_sym){
                                	if(!strcmp(curr_sym->name,s_word)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<2;
                                		}
						break;
                                                                                   
                                	}
                                	curr_sym = curr_sym->next;
                		}
                	}else{
                		m_code|=atoi(curr->word);
                	}
        		write_code_to_file(m_code,ic);
                	ic++;
                	break;
	}
	return ic;

}

int type_two_code(list *currr,int opcode, symbol *head_sym, int ic){
	int m_code=0;
        list *curr = currr;
        int type_m=check_miun(curr->next->word);	
	symbol *curr_sym = head_sym;
        char first_ind[31];
        char second_ind[31];
	char s_word[31];
        int v = 0;
        int u = 0;
	m_code|=type_m<<2;
        m_code|=opcode<<6;
        write_code_to_file(m_code,ic);
	m_code = 0;
	curr = curr->next;
	ic++;
	switch(type_m){
        	case 3:
        		m_code|=conv_enum3(curr->word)<<5;
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        	case 2:
        		while(curr->word[v]!='['){
        			first_ind[v] = curr->word[v];
        			v++;	
        		}
        		v++;
        		while(curr->word[v]!=']'){
        			second_ind[u] = curr->word[v];
        			u++;
        			v++;
        		}
        		while(curr_sym){
        			if(!strcmp(curr_sym->name,first_ind)){
        				if(curr_sym->type == external){
        					m_code|=1;
        				}else{
        					m_code|=2;
        					m_code|=curr_sym->value<<2;
        				}
					break;
                                                                                          
        			}
        			curr_sym = curr_sym->next;
        		}
			m_code = 0;
        		write_code_to_file(m_code,ic);
        		ic++;
        		if(!isdigit(second_ind)){
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<2;
                                		}
						break;
                                                                                   
                                	}
                                	curr_sym = curr_sym->next;
                                }
        		}else{
        			m_code|=atoi(curr->word);
        		}
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        	case 1:
        		m_code|=2;
        		while(curr_sym){
                        	if(!strcmp(curr_sym->name,second_ind)){
                        		if(curr_sym->type == external){
						m_code=0;
                        			m_code|=1;
                        		}else{
                        			m_code|=curr_sym->value<<2;
                        		}
        				write_code_to_file(m_code,ic);
					break;
                        	}
                        	curr_sym = curr_sym->next;
                        }
        		ic++;
        		break;
        	case 0:
        		if(!isdigit(curr->word)){
				strcpy(s_word,strtok(curr->word,"#"));
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,s_word)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<2;
                                		}
						break;
                                	}
                                	curr_sym = curr_sym->next;
        			}
        		}else{
        			m_code|=atoi(curr->word);
        		}
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        }
	return ic;
}



int circ2(list *head_list, data *head_data, symbol *head_s){
	list *curr = head_list;
	int ic = 100 ;
	while (curr){
		switch(conv_enum(curr->word)){
			case mov:	
				ic = type_one_code(curr,0,head_s,ic);
				break;
			case cmp:	
				ic = type_one_code(curr,1,head_s,ic);
				break;
			case add:	
				ic = type_one_code(curr,2,head_s,ic);
				break;
			case sub:	
				ic = type_one_code(curr,3,head_s,ic);
				break;
			case lea:	
				ic = type_one_code(curr,6,head_s,ic);
				break;
			case inc:	
				ic = type_two_code(curr,7,head_s,ic);
				break;
			case clr:	
                        	ic = type_two_code(curr,7,head_s,ic);
                        	break;
			case dec:	
				ic = type_two_code(curr,8,head_s,ic);
				break;
			case jmp:	
				ic = type_two_code(curr,9,head_s,ic);
				break;
			case rts:	
				ic = type_two_code(curr,14,head_s,ic);
				break;
			case not:	
				ic = type_two_code(curr,4,head_s,ic);
				break;
			case jsr:	
				ic = type_two_code(curr,13,head_s,ic);
				break;
			case prn:	
				ic = type_two_code(curr,12,head_s,ic);
				break;
			case red:	
				ic = type_two_code(curr,11,head_s,ic);
				break;
			case bne:	
				ic = type_two_code(curr,10,head_s,ic);
				break;
			case stop:
				ic = type_two_code(curr,15,head_s,ic);
				break;
			default:
				break;
		}
        	curr = curr->next;
        }
	return 1;
}
