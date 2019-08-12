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
	/*I did coloured and formatted output threwout the assembling proccess using the Gnome colours and formatting in terminal documentations*/	
	fp = fopen(codename,"r");
	if(fp){
		printf("\033[1;34mstarts assemblig\033[0m\n\n");
		pre_valid = prerun(head_list,fp);
		fclose(fp);	
	if(!pre_valid){
		printf("\033[1;3;4;31mSyntax error stopping assembling\033[0m\n");
		if(j<argc-1){
			printf("\033[1;34mmoving on to the next file\033[0m\n");
			printf("\n*************************************************************\n");
			printf("***************seperation between files**********************\n");
			printf("*************************************************************\n\n");
		}
		free(head_list);
		free(head_dat);
		free(head_sym);
		head_list = (list *)malloc(sizeof(list));
		head_dat = (data *)malloc(sizeof(data));
		head_sym = (symbol *)malloc(sizeof(symbol));
		continue;
	}
        printf("\033[1;3;32mprerun and syntax detection ended successfully!\033[0m\n");
        printf("\033[1;3;34mmoving to circ1:\033[0m\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	circ1_valid =circ1(head_list,head_sym,head_dat,obname);/* Creating the symbol table , returning 0 If there are any problems */
	if(!circ1_valid){
		/*breaking and destroying obfile if circ1 fires an error*/
       		printf("\033[1;3;31mcirc1 error stopping assembling\033[0m\n");
		if(j<argc-1){
			printf("\033[1;34mmoving on to the next file\033[0m\n\n\n");
			printf("\n*************************************************************\n");
			printf("***************seperation between files**********************\n");
			printf("*************************************************************\n\n");
		}
		remove_files(obname,extname,entname);
		free(head_list);
		free(head_dat);
		free(head_sym);
		head_list = (list *)malloc(sizeof(list));
		head_dat = (data *)malloc(sizeof(data));
		head_sym = (symbol *)malloc(sizeof(symbol));
		continue;
	}
        printf("\033[1;3;32mcirc1 and symbol generating ended successfully!\033[0m\n");
        printf("\033[1;3;34mmoving to circ2:\033[0m\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
 	circ2_valid = circ2(head_list,head_dat,head_sym,obname,extname,entname);/* creating output */
	if(!circ2_valid){
		/*if circ2 is not valid then as requested we are removing the files*/
		remove_files(obname,extname,entname);
        	printf("\033[1;3;31mcirc2 error stopping assembling\033[0m\n");
		if(j<argc-1){
			printf("\033[1;34mmoving on to the next file\033[0mn\n");
			printf("\n*************************************************************\n");
			printf("***************seperation between files**********************\n");
			printf("*************************************************************\n\n");
		}
		free(head_list);
		free(head_dat);
		free(head_sym);
		head_list = (list *)malloc(sizeof(list));
		head_dat = (data *)malloc(sizeof(data));
		head_sym = (symbol *)malloc(sizeof(symbol));
		continue;
	}
        printf("\033[1;3;32mcirc2 and output generation ended successfully!\033[0m\n");
        printf("\033[1;3;34mfinsishing up...\033[0m\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	free(head_list);
	free(head_dat);
	free(head_sym);
	head_list = (list *)malloc(sizeof(list));
	head_dat = (data *)malloc(sizeof(data));
	head_sym = (symbol *)malloc(sizeof(symbol));
	printf("\033[1;32mstop assemblig ended successfully!\033[0m\n");
	if(j<argc-1){
		printf("\033[1;34mmoving on to the next file\033[0m\n");
		printf("\n*************************************************************\n");
		printf("***************seperation between files**********************\n");
		printf("*************************************************************\n\n");
	}
	}else{ /* end if(fp) */
		/* I thought a lack of file existance error should be extermley noticeable so I set on blink as well*/	
        	printf("\033[1;3;5;6;4;31mERROR: could't open the file!\033[0m\n");
		if(j<argc-1){
			printf("\033[1;34mmoving on to the next file\033[0m\n");
			printf("\n*************************************************************\n");
			printf("***************seperation between files**********************\n");
			printf("*************************************************************\n\n");
		}

	}
	 } /* end for... */
	 return 0;
}
