#include "helpers.h"
int circ1(list *head , symbol *symhead,data *datahead ){
    int ic = start ,dc = 0 ; 
    int i , j , haserror = 1 , cntln = 0;
    char savename[namelen] ; /* the name for data struct */
    list *current = head -> next ; /* always start with empty word */
    symbol *symcurrent = symhead ;
    symbol *symhelper = symhead ; /* for macro */ 
    data *datacurrent = datahead ;
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
                symcurrent -> type = instrct ;
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
            while(current -> word[strlen(current -> word) - 1] != '\n') /* stops at the end of line */ 
            {
                if(isdigit(current -> word[0]) || current -> word[0] == '-' ||current -> word[0] == '+') /* case number */ 
                {
                 strcpy(datacurrent -> name ,savename) ;
                 datacurrent -> index = i ; 
                 i++ ; 
                 datacurrent -> val = atoi(current ->word) ;
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
                        if(strcmp(symhelper -> name,current -> word) == 0)
                        {
                            strcpy(datacurrent -> name ,savename) ;
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
            while(j < strlen(current -> word) - 1)/* not including the lest and first chaer wich is " */
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
    
    return haserror ; /* retrun 0 if there are errors */  
    
}
