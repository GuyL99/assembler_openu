#include "helpers.h"

int check_first_group(list *curr){
	int flag = 1;
	if (curr->word[0] == ';'){
        	return TRUE;
        }
	/*syntactly checking for the existence of enough words*/
	if(!curr->next){
        	printf("not enough arguments\n");
        	return FALSE;
        }else if (!curr->next->next){
        	printf("not enough arguments\n");	
        	return FALSE;
        }else if (!curr->next->next->next){
         	printf("not enough arguments\n");	
		if(curr->next->next->word[0] !=','){
                  printf("could be missing a comma\n");
		}
        	return FALSE;
	/*not too many though*/
	}else if (curr->next->next->next->next){
         	printf("too many arguments\n");	
        	return FALSE;
        }
	/*checking for comma words*/
        if(curr->next->next->word[0] !=','){
        	printf("could be missing a comma\n");
        	flag = 0;
        }
	/*checking if a var starts with a number*/
	if (isdigit(curr->next->word[0])){
        	printf("var names should not begin with numbers\n");
        	flag = 0;
        }
	/*rechecking for # in cases of - and +*/
	if (isdigit(curr->next->next->next->word[0])|| curr->next->next->next->word[0] == '-'||curr->next->next->next->word[0] == '+'){
        	printf("numbers sould be used stricly with '%c' marking behind them while not being inserted via data\n",'#');
        	flag = 0;
	}
	if (flag){
		return TRUE;
	}
	return FALSE;
}
int check_second_group(list *curr){
	if (curr->word[0] == ';'){
		return TRUE;
	}
	/*syntactly checking for the existence of enough words*/
	if(!curr->next){
        	printf("not enough arguments loacking operand\n");	
                return FALSE;
	}if(!strcmp(curr->next->word,",")){ 
		printf("comma in second type operation\n");
		if (curr->next->next!= NULL){
                  printf("too many arguments\n");	
                  return FALSE;
		}
		return FALSE;
	}else if (curr->next->next){
		/*Can't have a comma*/
		if(!strcmp(curr->next->next->word,",")){
			printf("comma in second type operation\n");
		}
		/*not too many though*/
         	printf("too many arguments arguments\n");	
                return FALSE;
        }
	return TRUE;
}
int check_third_group(list *curr){
	/*just needs to check that it has only the operation as an argument*/
	if(curr->next){
		printf("too many arguments\n");
		return FALSE;
	}
	return TRUE;
}
int valid_line(list *head){
	int flager =1;
	list *curr = head;
	list *curr2 = head;
	/*not checking the symbols(for lack of a better word) written in the lines beginnig*/
	if (curr->word[strlen(curr->word)-1]==':'){
		curr = curr->next;
	}
	/*splitting the lines into multiples of cases*/
	/*checking the .define .data and such...*/
	/*each of them is checked by thier design of code*/
	switch(conv_enum2(curr->word)){
        	case define:
                        if(curr->next==NULL){
                        	printf("not enough arguments\n");
                        	return FALSE;
                        }else if (!curr->next->next){
                        	printf("not enough arguments\n");	
                        	return FALSE;
                        }else if (curr->next->next->next==NULL){
                         	printf("not enough arguments\n");	
                        	if(curr->next->next->word[0] !='='){
                                  printf("no clear assigment\n");
                        	}
                        	return FALSE;
                        }else if (curr->next->next->next->next != NULL){
        		 	printf("too many arguments\n");	
                        	return FALSE;
                        }
			if(curr->next->next->word[0] !='='){
                        	printf("no clear assignment\n");
                        	flager = 0;
                        }
			if (isdigit(curr->next->word[0])){
                        	printf("var names should not begin with numbers\n");
                        	flager = 0;
                        }
                        if (flager){
                        	return TRUE;
                        }
                        return FALSE;
		case dat:
			if(curr->next==NULL){
                        	printf("not enough arguments\n");
                        	return FALSE;
			}

			curr2 = curr->next;
			/*checking while it has commas and nexts if has the other as a complement*/ 
			while (curr2->next){
				if(strcmp(curr2->word,",") && curr2->next->next){
					if(strcmp(curr2->next->word,",")){
						printf("missing a comma\n"); 
						return FALSE;
					}
				}
				curr2 = curr2->next;
			}
			return TRUE;
		case str:
			if(curr->next==NULL){
                        	printf("not enough arguments\n");
                        	return FALSE;
                        }
			if(curr->next->word[0]!='"'){
				printf("missing quotation marks\n");
                        	return FALSE;
			}
			if(curr->next->word[strlen(curr->next->word)-2]!='"'){
                        	printf("missing quotation marks\n");
                        	return FALSE;
                        }
			if(curr->next->next){
				printf("too many argumants\n");
		        	return FALSE;
			}
			return TRUE;
		case ent:
			if(curr->next==NULL){
				printf("not enough arguments\n");
                        	return FALSE;
                        }
			if(curr->next->next){
                        	printf("too many arguments\n");
                        	return FALSE;
                        }
			return TRUE;
		case ext:
			if(curr->next==NULL){
                        	printf("not enough arguments\n");
                        	return FALSE;
                        }
                        if(curr->next->next){
                        	printf("too many arguments\n");
                        	return FALSE;
                        }
                        return TRUE;
		case None:
			break;

        }
	/*checking for operations, and splitting them into the three groups - should be syntacticly different*/
	switch(conv_enum(curr->word)){
		case mov:
			return check_first_group(curr);
		case cmp:                               	
			return check_first_group(curr);
		case add:
			return check_first_group(curr);
                case sub:                                       
			return check_first_group(curr);
		case not:
			return check_second_group(curr);
                case clr:
			return check_second_group(curr);
                case lea:
			return check_first_group(curr);
                case inc:
			return check_second_group(curr);
		case dec:
			return check_second_group(curr);
                case jmp:
			return check_second_group(curr);
                case bne:
			return check_second_group(curr);
                case red:
			return check_second_group(curr);
                case prn:
			return check_second_group(curr);
                case jsr:
			return check_second_group(curr);
                case rts:
			return check_third_group(curr);
                case stop:
			return check_third_group(curr);
		case NONE:
			/*it reached the end of the line starts it should look for and found nothing so it's a bad line*/
			if (conv_enum(curr->next->next->word)==NONE && conv_enum2(curr->next->next->word)==None){
			printf("unrecognizable command\n");
				return FALSE;
			}else{
				return TRUE;
			}

	}
	return TRUE;

}

void append(list *head, char word[]){
	/*as the name suggests it appends to the head of the code list*/
	list * current = head;
        while (current->next != NULL) {
        	current = current->next;
        }
        current->next = malloc(sizeof(list));
        strcpy(current->next->word,word);
        current->next->next = NULL;
}


int prerun(list *head_tot, FILE *fp){
	int validFLAG = TRUE;
	int cntwrd = 0;
	int cntln = 0;
        struct list *head = (struct list *)malloc(sizeof(struct list));
	list * current = head;
	int valid; 
        int i=0;	
        int j=0;
        int flag=0;
	/*32 chars + 1 for \n*/
        char word[namelen + 1];
	int u,isdigflag = 0;
	char line[linelen];
	list *curr_tot = (struct list *)malloc(sizeof(struct list));
	if (head == NULL) {
        	printf("error whatever could'nt assgin mem");	
        }
	/*while not EOF*/
   	while(fgets(line,linelen,fp)){
		if(line[0]=='\n' || line[0]=='\0'){
			continue;
			/*dump empty lines*/
		}
		cntln++;
		if (line[0] == ';'){
			/*ignoring semi colon*/
		}else{
        	while(line[i]!='\n'){
			/*checking for special letters in the line to break to things when i get to them*/
		printf("%s",line);
			switch(line[i]){
				/*space is not a word so append the word to the list and go forward*/
				case ' ':
					/*if there where no previous valid characters in the line*/
					if(!flag){
						i++;
						continue;
					/*if there where no previous words in the line*/
					}else if(!cntwrd && flag){
						strcpy(head->word,word);
						head->next = NULL;	
					}else if(strcmp(word,"")){
						/*checking for spacy colos...*/
						if (word[0] == ':'){
                                                	printf("colon without anything attached, error in line %d\n",cntln);
                                        		append(head,word);
							validFLAG = FALSE;
                                                }else{
							append(head,word);
						}
                                        }
					if(flag){
					cntwrd++;
					j=0;
					/*initing the word string*/
					memset(word, '\0', sizeof word);
					break;
					}
				case '\t':
					/*same as space*/
                                	if(!flag){
						break;
					}else if(!cntwrd && flag){
						strcpy(head->word,word);
                                                head->next = NULL;	
                                	}else if (strcmp(word,"")){
						if (word[0] == ':'){
                                                	printf("colon without anything attached, error in line %d\n",cntln);
							validFLAG = FALSE;
                                                	break;
                                                }
						if(strcmp(word,"")){
                                			append(head,word);
						}
			        	}
					if (flag){
					cntwrd++;
					j=0;
					memset(word, '\0', sizeof word);
					break;
					}
				case ',':                                      	
					/*unlike the two above comma is a word so it appends it as well, everything else is similar*/
                                	if(!cntwrd && flag){
                                		strcpy(head->word,word);
                                                head->next = NULL;
						append(head,",");
                                	}else if (!flag){
						printf("error in line %d, comma at line beginning\n",cntln);
						validFLAG = FALSE;
						break;
					}else if(cntwrd && flag){
						if (word[0] == ':'){
                                                	printf("colon without anything attached, error in line %d\n",cntln);
							validFLAG = FALSE;
						}
						if(strcmp(word,"")){
                                			append(head,word);
						}
						append(head,",");
                                	}
					if(flag){
					cntwrd++;
					j=0;
					memset(word, '\0', sizeof word);
					break;
					}
				case '=':                                      	
					/*same as comma above*/
                                	if(!cntwrd && flag){
                                		strcpy(head->word,word);
                                                head->next = NULL;
                                		append(head,"=");
                                	}else if (!flag){
                                		printf("error in line %d, = at line beginning\n",cntln);
                                		break;
                                	}else if(cntwrd && flag){
                                		if (word[0] == ':'){
                                                	printf("colon without anything attached, error in line %d\n",cntln);
							validFLAG = FALSE;
                                		}
                                		if(strcmp(word,"")){
                                			append(head,word);
                                		}
                                		append(head,"=");
                                	}
                                	if(flag){
                                	cntwrd++;
                                	j=0;
                                	memset(word, '\0', sizeof word);
                                	break;
					}
				case '[':
					/*not an appending checkmark but rather a syntax err checking checkmark, checking to see if what's inside the parentheses is valid*/
					u=i+1;
					/*starts with a number flag*/
					if(isdigit(line[u])){
						isdigflag=1;		
					}
					while(line[u]!=']'){
						/*sign that's not a number nor a letter*/
						if(!isdigit(line[u]) && !isalpha(line[u])){
							printf("unallowed sign inside parentheses, error in line %d\n",cntln);
							validFLAG =FALSE;
						}
						/*if it starts with a number it can't continue with letters...*/
						if(isalpha(line[u]) && isdigflag){
							printf("number with letters, error in line %d\n",cntln);
							isdigflag=0;
							validFLAG = FALSE;
						}
						u++;
					}
					flag++ ;
                                        word[j]=line[i];	
					isdigflag=0;
                                        j++;
                                        break;
				default:
					/*defult case of non special letters*/
					flag++ ;
					word[j]=line[i];	
                                	j++;
					break;
			}
			i++;
		}
		/*appending the last word, becasue I'm checking until line[i]=='\n' so I still have a buffed word to append*/
		word[j]='\n';
		/*if the '\n' is a word for itself then I append it to the last word of the line*/
		if(!strcmp(word,"\n")){
			while (current->next) {      	
                        	current = current->next;
                        }
			strcpy(word,current->word);
			word[strlen(word)]='\n';
                        strcpy(current->word,word);
		}else{
		append(head,word);
		}
		/*appending the line to the codes entirity*/
		curr_tot = head;
		while (curr_tot){
			append(head_tot,curr_tot->word);
			curr_tot = curr_tot->next;
		}
		memset(word, '\0', sizeof word);
		memset(line, '\0', sizeof line);
		i=0;
		j=0;
		flag=0;
		cntwrd = 0;
		/*sending line into valid_line func in order to check it's validity as a line*/
		valid = valid_line(head);
		if (!valid){
			printf("error in line %d expanded above\n", cntln);
			validFLAG = 0;
		}
		}
	}
	return validFLAG;	
}
