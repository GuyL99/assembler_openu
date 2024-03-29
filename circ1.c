#include "helpers.h"
#include "symch.c"
int circ1(list *head , symbol *symhead,data *datahead,char obfile[namelen] ){
    int ic = start ,dc = 0 ; 
    int i , j , l , haserror = 1 , cntln = 0;
    int datahelp = TRUE ;
    char savename[namelen] , endln[namelen] ; /* the name for data struct */
    list *current = head  ; /* always start with empty word */
    symbol *symcurrent = symhead ;
    symbol *symhelper = symhead ; /* for macro */ 
    data *datacurrent = datahead ;
    FILE *FP=fopen(obfile,"a");
    while(current != NULL) /* scaning all the words in the prog */
    { 
        if (current -> word[strlen(current -> word) - 1] == '\n') /* end of line */ 
        cntln++ ;
        if (strcmp(current -> word,".define") == 0) /* case macro */
            {
                current = current -> next ; /* geting the name */
                strcpy(symcurrent ->name ,current -> word) ; /* save name */
                current = current -> next -> next ; /* after the name it will always be = "num" */
                symcurrent -> value = atoi(current -> word) ; /* convert to int */
                symcurrent -> type = macro ;
                /*symcurrent -> cmtype = none ;*/
                symcurrent-> next = malloc(sizeof(symbol)) ;
                symcurrent = symcurrent-> next ;
                cntln++ ;
                
            }
        else
        if (strcmp(current -> word,".extern") == 0) /* case .extern */ 
            {
                current = current -> next ; /* next word after .extern supposed to be the name */
                cntln++ ; /* name is end of line */
                strcpy(symcurrent ->name ,current -> word) ;/* save name*/ 
                
                symcurrent -> value = 0 ;
                
                symcurrent -> type = external ;
                symcurrent-> next = malloc(sizeof(symbol)) ;
                symcurrent = symcurrent-> next ;
            } 
        else    
        if (strchr(current -> word,':') != NULL) /* case symbol */ 
        {
                strcpy(symcurrent -> name,strtok(current -> word , ":")) ; /*omiting ':' */
                strcpy(savename,symcurrent -> name) ;    /* saving name for data */ 
                symcurrent -> value = ic ;
                if(strcmp(current -> next -> word,".data") == 0 /* case instruct */ 
                || strcmp(current -> next -> word,".string") == 0
                || strcmp(current -> next -> word,".entry") == 0
                || strcmp(current -> next -> word,".extern") == 0
                )
                {
                symcurrent -> type = instrct ;
                 if (strcmp(current -> next -> word,".string") == 0 || strcmp(current -> next -> word,".data") == 0 ) /* case data */
                     symcurrent -> value = ic + dc ;
                }    
                else
                symcurrent -> type = cmnd ;
                /*symcurrent -> cmtype = none ;*/
                symcurrent-> next = malloc(sizeof(symbol)) ;
                symcurrent = symcurrent-> next ; 
                
                
        }
        else
        if(strcmp(current -> word,".data") == 0) 
        {
            
            current = current -> next ; /* the Variables comes after the word .data */ 
            cntln++ ;
            i = 0 ; 
            datahelp = TRUE ; /* helps detrmin if we are at the end of the line */
            strcpy(endln , "                              ") ;/* making sure the word is empty */
            while(datahelp) /* stops at the end of line */ 
            {
                if(current -> word[strlen(current -> word) - 1] == '\n')/* last word is end of line so making sure to enter the loop */
                {
                datahelp = FALSE ;
                for (l=0;l < strlen(current -> word)-1;l++) /* copying the name without \n */ 
                endln[l] = current -> word[l]  ;
                endln[l] = '\0' ;
                }
                if(isdigit(current -> word[0]) || current -> word[0] == '-' ||current -> word[0] == '+') /* case number */ 
                {
                 strcpy(datacurrent -> name ,savename) ;
                 datacurrent -> index = i ; 
                 i++ ; 
                 if (datahelp) /* end line or not */
                 datacurrent -> val = atoi(current ->word) ;
                 else
                 datacurrent -> val = atoi(endln) ;
                 
                 datacurrent -> type = tdata;
                 datacurrent-> next = malloc(sizeof(data)) ;
                 datacurrent = datacurrent -> next ;
                 dc++ ; 
                }
                else
                {
                    if(strcmp(current -> word,",") != 0) /* case macro */ 
                    {
                    symhelper = symhead ; /* helps search in the sym struct for macro , cant use macro without defining him first */  
                    while(symhelper != NULL) 
                    {
                        if(strcmp(symhelper -> name,current -> word) == 0 || (strcmp(symhelper -> name,endln) == 0 && datahelp == FALSE) )
                        {
                            strcpy(datacurrent -> name ,savename) ; /* entering the saved name from previous loop */
                            datacurrent -> index = i ; 
                             i++ ; 
                            datacurrent -> val = symhelper -> value ; /* the value of the macro */ 
                            datacurrent -> type = tdata;
                            datacurrent-> next = malloc(sizeof(data)) ;
                            datacurrent = datacurrent -> next ;
                            dc++ ;
                            break ; /* stop the search */  
                        }
                        else
                        {
                           symhelper = symhelper -> next ; 
                        }
                    }
                    if(symhelper == NULL)
                    {
                    printf("macro not found, error in line %d\n",cntln) ;
                    haserror = 0 ;
                    
                    }
                    }
                }
                if(datahelp) /* start new line at the end of the while , not here */
                current = current -> next ; 
                    
            }
           /* current = current -> next ;*/
        }
        else
        if(strcmp(current -> word,".string") == 0) 
        {
            current = current -> next ;
        /*    cntln ;*/
            i = 0 ; /* index inside data */ 
            j = 1 ; /* start at char[1] */
            while(j < strlen(current -> word) - 2)/* not including the lest and first chaer wich is " */
            {
              strcpy(datacurrent -> name ,savename) ;
                 datacurrent -> index = i ; 
                 i++ ; 
                 datacurrent -> val = (int) (current ->word[j]) ;
                 datacurrent -> type = tstring;
                 datacurrent-> next = malloc(sizeof(data)) ;
                 datacurrent = datacurrent -> next ;
                 dc++ ; 
                 
                 j++ ;
            }
            strcpy(datacurrent -> name ,savename) ; /* entering 0 to mark end of string */
                 datacurrent -> index = i ; 
                 i++ ; 
                 datacurrent -> val = (int) ('0') ;
                 datacurrent -> type = tstring;
                 datacurrent-> next = malloc(sizeof(data)) ;
                 datacurrent = datacurrent -> next ;
                 dc++ ; 
                 
                 j++ ;
           /* current = current -> next ; */
        }
        else
        if(conv_enum(current -> word) != NONE) /* case command */ 
        {
        ic++ ;
        }
        else
        if (strchr(current -> word,'[') != NULL &&  (strchr(current -> word,']') != NULL)) /* case arry */ 
        ic = ic + 2 ;
        else
        if(conv_enum3(current -> word) != rNONE) /* case register */ 
        {
            if (strcmp(current -> next -> word , ",") == 0 && conv_enum3(current -> next -> next -> word) != rNONE)
            {
                current = current -> next -> next ; /*making sure i dont count twice if i have 2 registers in succession  */
            }
            ic++ ;
        }
        else
        if (strcmp(current -> word,".entry") == 0)
        {
          current = current -> next  ;/* entry doesnt efect ic */  
        }
        else
        if (strcmp(current -> word,",") != 0)     
        {
        ic ++ ;
        }
        current = current -> next ; /* next word */ 
    }
    if(symch(symhead) == 0)/*Checks that there are no values twice */
        haserror = 0 ;
	
    fprintf(FP,"   %d %d\n",ic,dc);
    fclose(FP);

    return haserror ; /* retrun 0 if there are errors */  
    

}
