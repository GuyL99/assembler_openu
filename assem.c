#include "pre.c"
#include "circ1.c"
#include "second.c"


int main(){
	struct list *head_list = (struct list*)malloc(sizeof(struct list));
	int pre_valid; /* making a struct of all the words in the file , without white noise, returning 0 If there are any problems*/ 
	symbol *head_sym = (symbol*)malloc(sizeof(symbol)); /* symbol table struct */
        data *head_dat = (data*)malloc(sizeof(data)); /* data for struct */ 
	int circ1_valid; /* Helps check errors */ 
	int circ2_valid;
	char codefile[namelen];/*I chose namelen length casue it stands to reason that the name of the file(whitch is a name) would use the same standarts as any name*/
	char obname[namelen];
	char extname[namelen];
	char entname[namelen];
	char codename[namelen];
	printf("please enter the name of your first code file (enter it with the .as extention)\n");
	scanf("%s",codefile);
	while(strcmp(codefile,"-1")){
		strtok(codefile,".");
		strcpy(obname,codefile);
		strcat(obname,".ob");
		strcpy(extname,codefile);
		strcat(extname,".ext");
		strcpy(entname,codefile);
		strcat(entname,".ent");
		strcpy(codename,codefile);
		strcat(codename,".as");
		pre_valid = prerun(head_list,codename);
		if(!pre_valid){
			printf("syntax error stopping assembling\n");
			break;
		}
		circ1_valid =circ1(head_list,head_sym,head_dat,obname);/* Creating the symbol table , returning 0 If there are any problems */
		if(!circ1_valid){
        		printf("circ1 error stopping assembling\n");
        		break;
        	}
 		circ2_valid = circ2(head_list,head_dat,head_sym,obname,extname,entname);/* creating output */
		if(!circ2_valid){
			/*if circ2 is not valid then as requested we are removing the files*/
			remove_files(obname,extname,entname);
        		printf("circ2 error stopping assembling\n");
        		break;
		}	
		printf("enter next code file if you have any, if your done enter -1\n");
		head_list = (struct list*)malloc(sizeof(struct list));
		head_sym = (symbol*)malloc(sizeof(symbol));
        	head_dat = (data*)malloc(sizeof(data));
		pre_valid = 0;
		circ1_valid=0; 
		circ2_valid=0;
		scanf("%s",codefile);
		memset(obname, '\0', sizeof obname);
		memset(codename, '\0', sizeof codename);
		memset(extname, '\0', sizeof extname);
		memset(entname, '\0', sizeof entname);
	}
	printf("exiting....\n");
	return 0;
}
