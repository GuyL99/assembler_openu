#include "pre.c"


int main(){
	struct return_pre *pre = prerun();
	struct list *commands_head = pre->head_return->next;
	if(!pre->valid){
		printf("syntax error stopping assembling\n");
		return 0;
	}
	/*
	symbol *sym_head = (struct sym*)malloc(sizeof(struct sym));
	symbol *dat_head = (struct data*)malloc(sizeof(struct data));
	*/

	/*TODO:send to dor's method to decode a line*/
	/*TODO:send to mine method to decode a line*/

	return 0;


}
