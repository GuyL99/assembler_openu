#include "helpers.h"

void printcheck(list *head){
	/*TODO:implement test for errors*/
	list *curr = head;
	while (curr!=NULL){
		printf("%s",curr->word);	
		curr = curr->next;
	}
			
}
int check_first_group(list *curr){
	int flag = 1;
	if (curr->word[0] == ';'){
        	return TRUE;
        }
	if(curr->next==NULL){
        	printf("not enough arguments\n");
        	return FALSE;
        }else if (!curr->next->next){
        	printf("not enough arguments\n");	
        	return FALSE;
        }else if (curr->next->next->next==NULL){
         	printf("not enough arguments\n");	
		if(curr->next->next->word[0] !=','){
                  printf("could be missing a comma\n");
		}
        	return FALSE;
	}else if (curr->next->next->next->next != NULL){
         	printf("too many arguments\n");	
        	return FALSE;
        }
        if(curr->next->next->word[0] !=','){
        	printf("could be missing a comma\n");
        	flag = 0;
        }
	if (isdigit(curr->next->word[0])){
        	printf("var names should not begin with numbers\n");
        	flag = 0;
        }
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
	if(curr->next==NULL){
        	printf("not enough arguments loacking operand\n");	
                return FALSE;
	}if(!strcmp(curr->next->word,",")){ 
		printf("comma in second type operation\n");
		if (curr->next->next!= NULL){
                  printf("too many arguments\n");	
                  return FALSE;
		}
		return FALSE;
	}else if (curr->next->next!= NULL){
		if(!strcmp(curr->next->next->word,",")){
			printf("comma in second type operation\n");
		}
         	printf("too many arguments arguments\n");	
                return FALSE;
        }
	return TRUE;
}
int valid_line(list *head){
	int flager =1;
	list *curr = head;
	list *curr2 = head;
	if (curr->word[strlen(curr->word)-1]==':'){
		curr = curr->next;
	}
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
			while (curr2->next){
				if(strcmp(curr2->word,",")){
					if(strcmp(curr2->next->word,",") && curr2->next->next){
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
			if(curr->next){
				printf("too many arguments");
				return FALSE; 
			}
                case stop:
			if(curr->next){
                        	printf("too many arguments");
                        	return FALSE; 
                        }
		case NONE:
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
	list * current = head;
        while (current->next != NULL) {
        	current = current->next;
        }
        current->next = malloc(sizeof(list));
        strcpy(current->next->word,word);
        current->next->next = NULL;
}


struct return_pre * prerun(){
	int validFLAG = TRUE;
	FILE *fp;
	int cntwrd = 0;
	int cntln = 0;
        struct list *head = (struct list *)malloc(sizeof(struct list));
	list * current = head;
	int valid; 
        int i=0;	
        int j=0;
        int flag=0;
	/*32 chars + 1 for \n*/
        char word[32];
	char line[80];
	struct list *head_tot = (struct list*)malloc(sizeof(struct list));
	struct return_pre *pack = (struct return_pre*)malloc(sizeof(struct return_pre));
	list *curr_tot = (struct list *)malloc(sizeof(struct list));
   	fp = fopen("code.as", "r");
   	if (fp == NULL)
   	{
      		perror("Error while opening the file.\n");
      		exit(1);
   	}
	if (head == NULL) {
        	printf("error whatever could'nt assgin mem");	
        }
   	while(!feof(fp)){
		if(!fgets(line,80,fp)){
			continue;
			/*dump empty lines*/
		}
		cntln++;
		if (line[0] == ';'){
			/*ignoring semi colon*/
		}else{
        	while(line[i]!='\n'){
			switch(line[i]){
				case ' ':
					if(!flag){
						i++;
						continue;
					}else if(!cntwrd && flag){
						strcpy(head->word,word);
						head->next = NULL;	
					}else if(strcmp(word,"")){
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
					memset(word, '\0', sizeof word);
					break;
					}
				case '\t':
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
				default:
					flag++ ;
					word[j]=line[i];	
                                	j++;
					break;
			}
			i++;
		}
		word[j]='\n';
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
		valid = valid_line(head);
		/*printf("%d",valid);*/
		if (!valid){
			printf("error in line %d expanded above\n", cntln);
			validFLAG = 0;
		}
		}
	}
	pack->head_return = head_tot;
	pack->valid = validFLAG;
	printcheck(head_tot);
   	fclose(fp);
	return pack;	
}
