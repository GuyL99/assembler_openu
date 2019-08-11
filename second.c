#include "output.c"
#include "helpers.h"
int check_miun(char word[namelen]){
	/*this function says that if the code has gotten to this point it has to have miun- so:*/
	int i;
	int flag = 0;
	if(word[0] == '#'){/*immidiate*/
		return 0;
	}
	if(conv_enum3(word)!=rNONE){/*register trace*/
		return 3;
	}
	for(i=0;i<strlen(word);i++){/*checking if it has [ so it would be declares as fixed index*/
		if(word[i] == '['){
			flag = 1;
			break;
		}
	}
	if(flag){
		return 2;
	} /*if nothing special matches it's direct*/ 
	return 1;

}
int type_one_code(list *currr,int opcode, symbol *head_sym,int ic, char codefile[namelen],char extname[namelen]){
	/*variables*/
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
	/*coding the operation*/
	m_code|=type_m2<<MIUNTWOBIT;
	m_code|=type_m<<MIUNONEBIT;
	m_code|=opcode<<OPBIT;
	/*writing it*/
	write_code_to_file(m_code,ic,codefile);
	m_code = 0;
	++ic;
	curr = curr->next;
	/*now at the operands*/
	switch(type_m){
		case 3:
			/*coding the register and checking whether a second register is in this line and if it is it codes it to the same line and raises a flag*/
			m_code|=conv_enum3(curr->word)<<REGONEBIT;
			if(type_m==type_m2){
				m_code|=conv_enum3(curr->next->next->word)<<REGTWOBIT;
				coded = TRUE;
			}
			/*writing to file and counting the ic*/
			write_code_to_file(m_code,ic,codefile);
			ic++;
			break;
		case 2:
			/*seprating the calls to the array into the array name and index*/
			strcpy(first_ind,strtok(curr->word,"["));
			strcpy(second_ind,strtok(NULL,"]"));
			m_code = 0;
			/*checking the array and coding it accordingly*/
			while(curr_sym){
				if(!strcmp(curr_sym->name,first_ind)){
					if(curr_sym->type == external){
						m_code=EXTERNVAL;
						print_to_ee(curr_sym->name,0,ic,extname);
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
			write_code_to_file(m_code,ic,codefile);
			ic++;
			m_code = 0;
			/*checking if the index is a digit or a saved name and if it's a saved name it's checking for the value attached*/
			if(!isdigit(second_ind[0])){
				while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code=EXTERNVAL;
							print_to_ee(curr_sym->name,0,ic,extname);
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
			write_code_to_file(m_code,ic,codefile);
			ic++;
			break;
		case 1:
			/*if its a direct one then all i need to do is code the address and move on...*/
			strcpy(s_word,curr->word);
			m_code=2;
			while(curr_sym){
                        	if(!strcmp(curr_sym->name,s_word)){
                        		if(curr_sym->type == external){
                        			m_code=EXTERNVAL;
						print_to_ee(curr_sym->name,0,ic,extname);
                        		}else{
                        			m_code|=curr_sym->value<<ADDRBIT;
                        		}
        				write_code_to_file(m_code,ic,codefile);
					break;
                                                                           
                        	}
                        	curr_sym = curr_sym->next;
                        }
			ic++;
			break;
		case 0:
			/*seperating the string into the piece that came after the # if it's not a number and coding the value attached*/
			strcpy(s_word,strtok(curr->word,"#"));
			if(s_word[0]=='-'){
				/*raising a negativity flag*/
				negFLAG =1;
				strcpy(s_word,strtok(s_word,"-"));
			}else if(s_word[0]=='+'){
				strcpy(s_word,strtok(s_word,"+"));
			}
			if(!isdigit(s_word[0])){
				while(curr_sym){
                                	if(!strcmp(curr_sym->name,s_word)){
                                		if(curr_sym->type == external){
                                			m_code=EXTERNVAL;
							print_to_ee(curr_sym->name,0,ic,extname);
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
				/*this is interesting I am claulating the bits of this number (negative) or 16 bit minus positive as if it was a 4096 2^12 12 bits*/
				if(negFLAG){
                			m_code|=(MAXERVAL-1*atoi(s_word2))<<NUMBIT;
				}else{
                			m_code|=atoi(s_word2)<<NUMBIT;
				}
                	}
			foundFLAG = 0;
			negFLAG = 0;
        		write_code_to_file(m_code,ic,codefile);
                	ic++;
                	break;
	}
/*reiniting variables*/
	m_code = 0;
	curr_sym = head_sym;
	curr = curr->next->next;
	memset(first_ind, '\0', sizeof first_ind);
	memset(second_ind, '\0', sizeof second_ind);
	memset(s_word, '\0', sizeof s_word);
	memset(s_word2, '\0', sizeof s_word2);
	switch(type_m2){
        	case 3:
		/*checking whether the reg is already coded and if not then codes it*/
			if(!coded){
        			m_code|=conv_enum3(curr->word)<<5;
        			write_code_to_file(m_code,ic,codefile);
        			ic++;
			}
        		break;
        	case 2:
			/*same as above*/
        		strcpy(first_ind,strtok(curr->word,"["));
        		strcpy(second_ind,strtok(NULL,"]"));
        		while(curr_sym){
        			if(!strcmp(curr_sym->name,first_ind)){
        				if(curr_sym->type == external){
        					m_code=EXTERNVAL;
						print_to_ee(curr_sym->name,0,ic,extname);
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
        		write_code_to_file(m_code,ic,codefile);
        		ic++;
        		m_code = 0;
        		if(!isdigit(second_ind[0])){
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code=EXTERNVAL;
							print_to_ee(curr_sym->name,0,ic,extname);
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
        		write_code_to_file(m_code,ic,codefile);
        		ic++;
        		break;
        	case 1:
			/*same as above*/
        		strcpy(s_word,curr->word);
        		m_code=2;
        		while(curr_sym){
                        	if(!strcmp(curr_sym->name,s_word)){
                        		if(curr_sym->type == external){
                        			m_code=EXTERNVAL;
						print_to_ee(curr_sym->name,0,ic,extname);
                        		}else{
                        			m_code|=curr_sym->value<<ADDRBIT;
                        		}
        				write_code_to_file(m_code,ic,codefile);
        				break;
                                                                           
                        	}
                        	curr_sym = curr_sym->next;
                        }
        		ic++;
        		break;
        	case 0:
			/*same as above*/
        		strcpy(s_word,strtok(curr->word,"#"));
        		if(s_word[0]=='-'){
        			negFLAG =1;
        			strcpy(s_word,strtok(s_word,"-"));
        		}else if(s_word[0]=='+'){
        			strcpy(s_word,strtok(s_word,"+"));
        		}
			/*checking if the word is \ned and if it is then dumps it*/
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
							print_to_ee(curr_sym->name,0,ic,extname);
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
                			m_code|=(MAXERVAL-1*atoi(s_word2))<<NUMBIT;
        			}else{
                			m_code|=atoi(s_word2)<<NUMBIT;
        			}
                	}
        		foundFLAG = 0;
        		write_code_to_file(m_code,ic,codefile);
                	ic++;
                	break;
        }
	return ic;

}

int type_two_code(list *currr,int opcode, symbol *head_sym, int ic, char codefile[namelen], char extname[namelen]){
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
	m_code|=type_m<<MIUNTWOBIT;
        m_code|=opcode<<OPBIT;
        write_code_to_file(m_code,ic,codefile);
	m_code = 0;
	curr = curr->next;
	++ic;
	switch(type_m){
        	case 3:
			/*just codes the reg*/
        		m_code|=conv_enum3(curr->word)<<REGONEBIT;
        		write_code_to_file(m_code,ic,codefile);
        		ic++;
        		break;
        	case 2:
			/*same as case 2 above*/
        		strcpy(first_ind,strtok(curr->word,"["));
        		strcpy(second_ind,strtok(NULL,"]"));
        		while(curr_sym){
        			if(!strcmp(curr_sym->name,first_ind)){
        				if(curr_sym->type == external){
        					m_code=EXTERNVAL;
						print_to_ee(curr_sym->name,0,ic,extname);
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
        		write_code_to_file(m_code,ic,codefile);
        		ic++;
        		if(!isdigit(second_ind[0])){
        			while(curr_sym){
                                	if(!strcmp(curr_sym->name,second_ind)){
                                		if(curr_sym->type == external){
                                			m_code=EXTERNVAL;
							print_to_ee(curr_sym->name,0,ic,extname);
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
        		write_code_to_file(m_code,ic,codefile);
        		ic++;
        		break;
        	case 1:
			/*same as case 1 above*/
        		m_code=2;
			strcpy(s_word,curr->word);
        		if (s_word[strlen(s_word)-1] == '\n'){
        			strncpy(s_word2,s_word,strlen(s_word)-1);
        		}else{
        			strcpy(s_word2,s_word);
        		}
        		while(curr_sym){
                        	if(!strcmp(curr_sym->name,s_word) || !strcmp(curr_sym->name,s_word2)){
					if(curr_sym->type == external){
                        			m_code=EXTERNVAL;
						print_to_ee(curr_sym->name,0,ic,extname);
                        		}else{
                        			m_code|=curr_sym->value<<ADDRBIT;
					}
                        	}
                        	curr_sym = curr_sym->next;
                        }
        		write_code_to_file(m_code,ic,codefile);
        		ic++;
        		break;
        	case 0:
			/*same as case 0 of the second operand*/
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
                                			m_code=EXTERNVAL;
							print_to_ee(curr_sym->name,0,ic,extname);
                                		}else{
                                			m_code|=curr_sym->value<<NUMBIT;
                                		}
						break;
                                	}
                                	curr_sym = curr_sym->next;
        			}
        		}else{
				if(negFLAG){
        				m_code|=(MAXERVAL-1*atoi(s_word2))<<NUMBIT;
				}else{
        				m_code|=atoi(s_word2)<<NUMBIT;
				}
        		}
        		write_code_to_file(m_code,ic,codefile);
        		ic++;
        		break;
        }
	return ic;
}


int type_three_code(int opcode, int ic, char codefile[namelen]){
	/*in type three I only need to code the opcode*/
	int m_code=0;
        m_code|=opcode<<OPBIT;
        write_code_to_file(m_code,ic,codefile);
	ic++;
	return ic;
}

int circ2(list *head_list, data *head_data, symbol *head_s, char obfile[namelen],char extfile[namelen],char entfile[namelen]){
	list *curr = head_list;
	data *datacurrent = head_data ;
	symbol *symcurrent =head_s ;
	int ic = start ;
	int dc = 1 ;
	int l ;
	int r = 0 ;
	char endln[namelen];
	while (curr){
		/* I again broke the code into three types type 1-2 operands operation, type 2 - 1 operand operation and type 3 - no operand operation' those are distinguishable by the way one should code them because for one the number of lines needed to code them, the number of nexts to use and such and such...*/
		/*I counted ic and returned current ic from every function*/
		switch(conv_enum(curr->word)){
			case mov:	
				ic = type_one_code(curr,0,head_s,ic,obfile,extfile);
				break;
			case cmp:	
				ic = type_one_code(curr,1,head_s,ic,obfile,extfile);
				break;
			case add:	
				ic = type_one_code(curr,2,head_s,ic,obfile,extfile);
				break;
			case sub:	
				ic = type_one_code(curr,3,head_s,ic,obfile,extfile);
				break;
			case lea:	
				ic = type_one_code(curr,6,head_s,ic,obfile,extfile);
				break;
			case inc:	
				ic = type_two_code(curr,7,head_s,ic,obfile,extfile);
				break;
			case clr:	
                        	ic = type_two_code(curr,7,head_s,ic,obfile,extfile);
                        	break;
			case dec:	
				ic = type_two_code(curr,8,head_s,ic,obfile,extfile);
				break;
			case jmp:	
				ic = type_two_code(curr,9,head_s,ic,obfile,extfile);
				break;
			case rts:	
				ic = type_three_code(14,ic,obfile);
				break;
			case not:	
				ic = type_two_code(curr,4,head_s,ic,obfile,extfile);
				break;
			case jsr:	
				ic = type_two_code(curr,13,head_s,ic,obfile,extfile);
				break;
			case prn:	
				ic = type_two_code(curr,12,head_s,ic,obfile,extfile);
				break;
			case red:	
				ic = type_two_code(curr,11,head_s,ic,obfile,extfile);
				break;
			case bne:	
				ic = type_two_code(curr,10,head_s,ic,obfile,extfile);
				break;
			case stop:
				ic = type_three_code(15,ic,obfile);
				break;
			default:
				break;
		}
		if (ic==-1){
			return 0;
		}
		if(strcmp(curr -> word , ".entry") == 0) /* case .ent file */
		{
			for (l=0;l < strlen(curr -> next -> word)-1;l++){
                		endln[l] = curr -> next -> word[l]  ;
			}
                	endln[l] = '\0' ; /* word without \n */ 
			symcurrent =head_s ;
			while(symcurrent != NULL) /* serch symbol table */
			{
				if(!strcmp(endln,symcurrent -> name)){
				   break ;
				  }
				symcurrent = symcurrent -> next ;   
			}
			if(symcurrent != NULL)/* print if found */
			print_to_ee(endln, 1 ,symcurrent -> value,entfile) ;
			else 
			printf("Error entry not found.\n");
		}
		curr = curr->next;
        }
	while(datacurrent -> next != NULL && r < 100) /* writing the data at the end of file */
   	{
		r++ ;
        	write_code_to_file(datacurrent -> val  , ic+dc-1,obfile) ;
      		datacurrent = datacurrent -> next ;
       	        dc++ ;
   	}
	return 1;
}
