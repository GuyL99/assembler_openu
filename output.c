#include "helpers.h"
void print_to_ee(char name1[namelen], int valer,int ic){
	FILE *FP;
	if(valer){
	FP = fopen("machine.ent","a");
	}else{
	FP = fopen("machine.ext","a");
	}
	fprintf(FP,"%s %u\n",name1,ic);	
	fclose(FP);
}
void write_code_to_file(int n,int ic){
	FILE * FP = NULL;
	/*char b[17];
    	int z;
    	b[0] = '\0';
    	for (z = 32786; z > 0; z >>= 1)
    	{
		if(z>16384){
			continue;
		}
        	strcat(b, ((m_code & z) == z) ? "1" : "0");
    	}*/
	int temp , index = convertlen - 1;
        char conv[convertlen] ;
        while(n)
        {
            temp = n & 3 ; /* 3 = 11 in binary */ 
            n >>= 2 ; /* moving 2 bits */ 
            switch(temp) /*we dont use define Because 0-4 is the name case of the converted */
            {
                case 0 :
                conv[index] = '*' ;
                break ;
                
                case 1 :
                conv[index] = '#' ;
                break ;
                
                case 2 :
                conv[index] = '%' ;
                break ;
                
                case 3 :
                conv[index] = '!' ;
                break ;
                
                default:
                printf("Error! operator is not correct") ;
            }
            index-- ;
            
        }
        while(index >= 0) /* filing zeroes */ 
        {
            conv[index] = '*' ;
            index-- ;
        }
	FP = fopen("machine.ob","a");
	fprintf(FP,"%d %s\n",ic,conv);
	fclose(FP);
}
void remove_files(){
	int remover1 = remove("machine.ext");
	int remover2 = remove("machine.ent");
	if(remover1){
		printf("Error: unable to delete the .ext file");
	}
	if(remover2){
		printf("Error: unable to delete the .ent file");
	}

}
