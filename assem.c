#include "pre.c"
#include "circ1.c"
#include "second.c"


int main(){
	struct list *head_list = (struct list*)malloc(sizeof(struct list));
	int pre_valid = prerun(head_list); /* making a struct of all the words in the file , without white noise, returning 0 If there are any problems*/ 
	symbol *head_sym = (symbol*)malloc(sizeof(symbol)); 
        data *head_dat = (data*)malloc(sizeof(data));
	int circ1_valid;
	int circ2_valid;
	if(!pre_valid){
		printf("syntax error stopping assembling\n");
		return 0;
	}
	circ1_valid =circ1(head_list,head_sym,head_dat);/* Creating the symbol table , returning 0 If there are any problems */
	if(!circ1_valid){
        	printf("circ1 error stopping assembling\n");
        	return 0;
        }
 	circ2_valid = circ2(head_list,head_dat,head_sym);/* creating output */
	if(!circ2_valid){
		/*if circ2 is not valid then as requested we are removing the files*/
		remove_files();
        	printf("circ2 error stopping assembling\n");
        	return 0;
	}
	return 0;
}
