#include "helpers.h"


int circ2(list * head_list, data * head_data, symbol * head_symbol){
	list *curr = head_list;
	while (curr!=NULL){
		if (!strcmp(curr->word,".define") || !strcmp(curr->word,".data") || !strcmp(curr->word,".extern") || strcmp(curr->word,".string")){
			return 0;		
		}  
        	curr = curr->next;
        }
}
