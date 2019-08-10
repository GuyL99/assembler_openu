#include "output.c"
#include "helpers.h"
int check_miun(char word[namelen]){
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
	return 1;

}
int type_one_code(list *currr,int opcode, symbol *head_sym,int ic){
	int m_code=0;
	list *curr = currr;
	symbol *curr_sym = head_sym;
	int type_m=check_miun(curr->next->word);	
	int type_m2=check_miun(curr->next->next->next->word);
	int coded = FALSE;
	char first_ind[namelen];
	char second_ind[namelen];
	char s_word[namelen];
	char s_word2[namelen];
	int foundFLAG = 0;
	int negFLAG = 0;
	m_code|=type_m2<<AREBIT;
	m_code|=type_m<<MIUNTWOBIT;
	m_code|=opcode<<MIUNONEBIT;
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
			strcpy(first_ind,strtok(curr->word,"["));
			strcpy(second_ind,strtok(NULL,"]"));
			m_code = 0;
			while(curr_sym){
				if(!strcmp(curr_sym->name,first_ind)){
					if(curr_sym->type == external){
						m_code|=1;
					}else{
						m_code=2;
						m_code|=curr_sym->value<<ADDRBIT;
					}
					foundFLAG = 1;
					break;
				}
				curr_sym = curr_sym->next;
			}
			if(!foundFLAG){
				printf("error - symbol %s not found, current ic is %d\n",first_ind,ic);
				return -1;
			}
			foundFLAG = 0;
			write_code_to_file(m_code,ic);
			ic++;
			m_code = 0;
			if(!isdigit(second_ind[0])){
				while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<NUMBIT;
                                		}
						foundFLAG = 1;
                                                break;                       
                                	}
                                	curr_sym = curr_sym->next;
                                }
				if(!foundFLAG){
					printf("error - symbol %s not found, current ic is %d\n",first_ind,ic);
					return -1;
				}
				foundFLAG = 0;
        		}else{
        			m_code|=atoi(second_ind)<<NUMBIT;
        		}
			write_code_to_file(m_code,ic);
			ic++;
			break;
		case 1:
			strcpy(s_word,curr->word);
			m_code=2;
			while(curr_sym){
                        	if(!strcmp(curr_sym->name,s_word)){
                        		if(curr_sym->type == external){
						m_code = 0;
                        			m_code|=1;
                        		}else{
                        			m_code|=curr_sym->value<<ADDRBIT;
                        		}
        				write_code_to_file(m_code,ic);
					break;
                                                                           
                        	}
                        	curr_sym = curr_sym->next;
                        }
			ic++;
			break;
		case 0:
			strcpy(s_word,strtok(curr->word,"#"));
			if(s_word[0]=='-'){
				negFLAG =1;
				strcpy(s_word,strtok(s_word,"-"));
			}else if(s_word[0]=='+'){
				strcpy(s_word,strtok(s_word,"+"));
			}
			if (s_word[strlen(s_word)-1] == '\n'){
				strncpy(s_word2,s_word,strlen(s_word)-1);
			}else{
				strcpy(s_word2,s_word);
			}
			if(!isdigit(s_word2[0])){
				while(curr_sym){
                                	if(!strcmp(curr_sym->name,s_word2)){
                                		if(curr_sym->type == external){
                                			m_code|=EXTERNVAL;
                                		}else{
                                			m_code|=curr_sym->value;
                                		}
						foundFLAG = 1;
						break;
                                                                                   
                                	}
                                	curr_sym = curr_sym->next;
                		}
				if(!foundFLAG){
					printf("error - symbol %s not found, current ic is %d\n",s_word2,ic);
					return -1;
				}
                	}else{
				if(negFLAG){
                			m_code|=(-1*atoi(s_word2))<<NUMBIT;
				}else{
                			m_code|=atoi(s_word2)<<NUMBIT;
				}
                	}
			foundFLAG = 0;
			negFLAG = 0;
        		write_code_to_file(m_code,ic);
                	ic++;
                	break;
	}
	m_code = 0;
	curr_sym = head_sym;
	curr = curr->next->next;
	memset(first_ind, '\0', sizeof first_ind);
	memset(second_ind, '\0', sizeof second_ind);
	memset(s_word, '\0', sizeof s_word);
	memset(s_word2, '\0', sizeof s_word2);
	switch(type_m2){
        	case 3:
			if(!coded){
        			m_code|=conv_enum3(curr->word)<<5;
        			write_code_to_file(m_code,ic);
        			ic++;
			}
        		break;
        	case 2:
        		strcpy(first_ind,strtok(curr->word,"["));
        		strcpy(second_ind,strtok(NULL,"]"));
        		while(curr_sym){
        			if(!strcmp(curr_sym->name,first_ind)){
        				if(curr_sym->type == external){
        					m_code|=EXTERNVAL;
        				}else{
        					m_code=2;
        					m_code|=curr_sym->value<<ADDRBIT;
        				}
        				foundFLAG = 1;
        				break;
        			}
        			curr_sym = curr_sym->next;
        		}
        		if(!foundFLAG){
        			printf("error - symbol %s not found, current ic is %d\n",first_ind,ic);
        			return -1;
        		}
			curr_sym = head_sym;
        		foundFLAG = 0;
        		write_code_to_file(m_code,ic);
        		ic++;
        		m_code = 0;
        		if(!isdigit(second_ind[0])){
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<NUMBIT;
                                		}
        					foundFLAG = 1;
                                                break;                       
                                	}
                                	curr_sym = curr_sym->next;
                                }
        			if(!foundFLAG){
        				printf("error - symbol %s not found, current ic is %d\n",second_ind,ic);
        				return -1;
        			}
        			foundFLAG = 0;
        		}else{
        			m_code|=atoi(second_ind)<<NUMBIT;
        		}
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        	case 1:
        		strcpy(s_word,curr->word);
			if (s_word[strlen(s_word)-1] == '\n'){
				strncpy(s_word2,s_word,strlen(s_word)-1);
			}else{
				strcpy(s_word2,s_word);
			}
        		m_code=2;
        		while(curr_sym){
                        	if(!strcmp(curr_sym->name,s_word2)){
                        		if(curr_sym->type == external){
        					m_code = 0;
                        			m_code|=EXTERNVAL;
                        		}else{
                        			m_code|=curr_sym->value<<ADDRBIT;
                        		}
        				write_code_to_file(m_code,ic);
        				break;
                                                                           
                        	}
                        	curr_sym = curr_sym->next;
                        }
        		ic++;
        		break;
        	case 0:
        		strcpy(s_word,strtok(curr->word,"#"));
        		if(s_word[0]=='-'){
        			negFLAG =1;
        			strcpy(s_word,strtok(s_word,"-"));
        		}else if(s_word[0]=='+'){
        			strcpy(s_word,strtok(s_word,"+"));
        		}
        		if (s_word[strlen(s_word)-1] == '\n'){
        			strncpy(s_word2,s_word,strlen(s_word)-1);
        		}else{
        			strcpy(s_word2,s_word);
        		}
        		if(!isdigit(s_word2[0])){
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,s_word2)){
                                		if(curr_sym->type == external){
                                			m_code|=EXTERNVAL;
                                		}else{
                                			m_code|=curr_sym->value<<NUMBIT;
                                		}
        					foundFLAG = 1;
        					break;
                                                                                   
                                	}
                                	curr_sym = curr_sym->next;
                		}
        			if(!foundFLAG){
        				printf("error - symbol %s not found, current ic is %d\n",s_word2,ic);
        				return -1;
        			}
                	}else{
        			if(negFLAG){
                			m_code|=(-1*atoi(s_word2))<<NUMBIT;
        			}else{
                			m_code|=atoi(s_word2)<<NUMBIT;
        			}
                	}
        		foundFLAG = 0;
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
        char first_ind[namelen];
        char second_ind[namelen];
	char s_word[namelen];
	char s_word2[namelen];
        int foundFLAG = 0;
        int negFLAG = 0;
	m_code|=type_m<<AREBIT;
        m_code|=opcode<<MIUNONEBIT;
        write_code_to_file(m_code,ic);
	m_code = 0;
	curr = curr->next;
	++ic;
	switch(type_m){
        	case 3:
        		m_code|=conv_enum3(curr->word)<<5;
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        	case 2:
        		strcpy(first_ind,strtok(curr->word,"["));
        		strcpy(second_ind,strtok(NULL,"]"));
        		while(curr_sym){
        			if(!strcmp(curr_sym->name,first_ind)){
        				if(curr_sym->type == external){
        					m_code|=1;
        				}else{
        					m_code=2;
        					m_code|=curr_sym->value<<ADDRBIT;
        				}
					foundFLAG = 1;
					break;
        			}
        			curr_sym = curr_sym->next;
        		}
			if(!foundFLAG){
				printf("error - symbol %s not found, current ic is %d\n",first_ind,ic);
				return -1;
			}
			m_code = 0;
			foundFLAG = 0;
        		write_code_to_file(m_code,ic);
        		ic++;
        		if(!isdigit(second_ind[0])){
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<NUMBIT;
                                		}
						foundFLAG = 1;
						break;
                                	}
                                	curr_sym = curr_sym->next;
                                }
				if(!foundFLAG){
					printf("error - symbol %s not found, current ic is %d\n",first_ind,ic);
					return -1;
				}
        		}else{
        			m_code|=atoi(curr->word)<<NUMBIT;
        		}
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        	case 1:
        		m_code=2;
			strcpy(s_word,curr->word);
			if (s_word[strlen(s_word)-1] == '\n'){
				strncpy(s_word2,s_word,strlen(s_word)-1);
			}else{
				strcpy(s_word2,s_word);
			}
        		while(curr_sym){
                        	if(!strcmp(curr_sym->name,s_word2)){
					if(curr_sym->type == external){
						m_code=0;
                        			m_code|=1;
                        		}else{
                        			m_code|=curr_sym->value<<ADDRBIT;
					}
                        	}
                        	curr_sym = curr_sym->next;
                        }
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        	case 0:
			strcpy(s_word,strtok(curr->word,"#"));
			if(s_word[0]=='-'){
				negFLAG =1;
				strcpy(s_word,strtok(s_word,"-"));
			}else if(s_word[0]=='+'){
				strcpy(s_word,strtok(s_word,"+"));
			}
			if (s_word[strlen(s_word)-1] == '\n'){
				strncpy(s_word2,s_word,strlen(s_word)-1);
			}else{
				strcpy(s_word2,s_word);
			}
        		if(!isdigit(s_word2[0])){
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,s_word2)){
                                		if(curr_sym->type == external){
                                			m_code|=1;
                                		}else{
                                			m_code|=curr_sym->value<<NUMBIT;
                                		}
						break;
                                	}
                                	curr_sym = curr_sym->next;
        			}
        		}else{
				if(negFLAG){
        				m_code|=(-1*atoi(s_word2))<<NUMBIT;
				}else{
        				m_code|=atoi(s_word2)<<NUMBIT;
				}
        		}
        		write_code_to_file(m_code,ic);
        		ic++;
        		break;
        }
	return ic;
}



int circ2(list *head_list, data *head_data, symbol *head_s){
	list *curr = head_list;
	int ic = start ;
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
				break;
			default:
				break;
		}
		if (ic==-1){
			return 0;
		}
        	curr = curr->next;
        }
	return 1;
}
