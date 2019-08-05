#include "pre.c"
#include "circ1.c"
#include "second.c"


int main(){
	struct list *head_list = (struct list*)malloc(sizeof(struct list));
	int pre_valid = prerun(head_list);
	symbol *head_sym = (symbol*)malloc(sizeof(symbol));
        data *head_dat = (data*)malloc(sizeof(data));
        code *head_code = (code*)malloc(sizeof(code));
	int circ1_valid;
	int circ2_valid;
	if(!pre_valid){
		printf("syntax error stopping assembling\n");
		return 0;
	}
	while(head_list){
		printf("%s",head_list->word);
		head_list = head_list->next;
	}
	circ1_valid =circ1(head_list,head_sym,head_dat);
	/*TODO:send to dor's method to decode a line*/
	if(!circ1_valid){
        	printf("circ1 error stopping assembling\n");
        	return 0;
        }


	/*TODO:send to mine method to decode a line*/
  	circ2_valid = circ2(head_list,head_dat,head_sym,head_code);
	if(!circ2_valid){
        	printf("circ2 error stopping assembling\n");
        	return 0;
        }  

	return 0;


}
