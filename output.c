#include "helpers.h"
void print_to_ee(char name1[namelen], int valer,int ic,char filename[namelen]){
	FILE *FP;
	char name2[namelen];
	int i;
	/*same type of writing into file, just needed to tweek the file name so..*/
	/*making a new string without "\n"*/
	if(name1[strlen(name1)-1]=='\n'){
		for(i=0;i<strlen(name1)-1;i++){
			name2[i]=name1[i];
		}
		name2[i]='\0';
	}else{
		strcpy(name2,name1);
	}
	FP = fopen(filename,"a");
	fprintf(FP,"%s %u\n",name2,ic);	
	fclose(FP);
}
void write_code_to_file(int n,int ic, char codefile[namelen]){
	FILE * FP = NULL;
	int temp , index = convertlen - 1;
        char conv[convertlen] ;
	if(n < 0 )
	{
		n= n & MAXDAVEL ;
	}
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
	FP = fopen(codefile,"a");
	fprintf(FP,"%d %s\n",ic,conv);
	fclose(FP);
}
void remove_files(char obfile[namelen],char extfile[namelen],char entfile[namelen]){
	/*a function to remove the files in case of an error while circ2*/
	int remover1 = remove(extfile);
	int remover2 = remove(entfile);
	int remover3 = remove(obfile);
	if(remover1){
		printf("Error: unable to delete the .ext file");
	}
	if(remover2){
		printf("Error: unable to delete the .ent file");
	}
	if(remover3){
		printf("Error: unable to delete the .ob file");
	}

}
