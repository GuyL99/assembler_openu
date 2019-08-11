#include "pre.c"
#include "circ1.c"
#include "second.c"


int main(int argc, char *argv[]){
	FILE *fp;
	list *head_list = (list *)malloc(sizeof(list)) ;
	int pre_valid; /* making a struct of all the words in the file , without white noise, returning 0 If there are any problems*/ 
	symbol *head_sym=(symbol *)malloc(sizeof(symbol)); /* symbol table struct */
        data *head_dat =(data *)malloc(sizeof(data));/* data for struct */ 
	int circ1_valid; /* Helps check errors */ 
	int circ2_valid;
	int j ;
	/*char *codefile;I chose namelen length casue it stands to reason that the name of the file(whitch is a name) would use the same standarts as any name*/
	char obname[namelen];
	char extname[namelen];
	char entname[namelen];
	char codename[namelen];
	if (argc < 2)
 	  {
       	    printf("Missing Filename\n");
            return(1);
  	  }
  	 for(j=1; j < argc; j++)   
          {
          if (j>1)
	  {
		memset(codename, '\0', sizeof codename);
		memset(obname, '\0', sizeof obname);
		memset(extname, '\0', sizeof extname);
		memset(entname, '\0', sizeof entname);
	  }
        strcpy(codename,argv[j]);
        printf("codename : %s\n", codename);
	strcpy(entname,codename) ;
	strtok(entname,".") ;
        strcat(entname,".ent") ;
	strcpy(extname,codename) ;
	strtok(extname,".") ;
        strcat(extname,".ext") ;
	strcpy(obname,codename) ;
	strtok(obname,".") ;
        strcat(obname,".ob") ;
		
	fp = fopen(codename,"r");
	if(fp){
	pre_valid = prerun(head_list,fp);
	fclose(fp);	
	if(!pre_valid){
		printf("syntax error stopping assembling\n");
		/*deleteList(&head_list);
		deleteData(&head_dat);
		deleteSym(&head_sym);
		j++;
		continue;*/
		break;
		
	}
	if(j<1){
	while(head_list){
		printf("%s",head_list->word);
		head_list = head_list->next;
	}}
	circ1_valid =circ1(head_list,head_sym,head_dat,obname);/* Creating the symbol table , returning 0 If there are any problems */
	if(!circ1_valid){
       		printf("circ1 error stopping assembling\n");
		remove_files(obname,extname,entname);
		/*deleteList(&head_list);
		deleteData(&head_dat);
		deleteSym(&head_sym);
		j++;
		continue;*/
		break;
		
	}
 	circ2_valid = circ2(head_list,head_dat,head_sym,obname,extname,entname);/* creating output */
	if(!circ2_valid){
		/*if circ2 is not valid then as requested we are removing the files*/
		remove_files(obname,extname,entname);
        	printf("circ2 error stopping assembling\n");
		/*deleteList(&head_list);
		deleteData(&head_dat);
		deleteSym(&head_sym);
		j++;
		continue;*/
		break;
	}
	deleteList(&head_list);
	deleteData(&head_dat);
	deleteSym(&head_sym);
	head_list = (list *)malloc(sizeof(list));
	head_dat = (data *)malloc(sizeof(data));
	head_sym = (symbol *)malloc(sizeof(symbol));
	} /* end if(fp) */
	 } /* end for... */
	 exit(1);
	 return 0;
}
