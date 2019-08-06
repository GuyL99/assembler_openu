#include "pre.c"
#include "circ1.c"
#include "second.c"
#include "output.c"


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

	circ1_valid =circ1(head_list,head_sym,head_dat);
	if(!circ1_valid){
        	printf("circ1 error stopping assembling\n");
        	return 0;
        }

  	circ2_valid = circ2(head_list,head_dat,head_sym,head_code);
	if(!circ2_valid){}else{}

	return 0;
}
