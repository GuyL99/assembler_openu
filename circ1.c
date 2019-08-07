#include "helpers.h"
#include "output.c"
int circ1(list *head , symbol *symhead,data *datahead ){
    int ic = 100,dc = 0 ; 
    int i , j , haserror = 1 , cntln = 0;
    char savename[31] ;
    list *current = head ;
    symbol *symcurrent = symhead ;
    symbol *symhelper = symhead ; /* for macro */ 
    data *datacurrent = datahead ;
    while(current != NULL) /* scaning all the words in the prog */
    {
        if (current -> word[strlen(current -> word) - 1] == '\n') 
        cntln++ ;
        if (strcmp(current -> word,".define") == 0) /* case macro */
            {
                current = current -> next ; /* geting the name */
                strcpy(symcurrent ->name ,current -> word) ;
                current = current -> next -> next ; /* after the name it will always be = "num" */
                symcurrent -> value = atoi(current -> word) ;
                symcurrent -> type = macro ;
                /*symcurrent -> cmtype = none ;*/
                symcurrent-> next = malloc(sizeof(symbol)) ;
                symcurrent = symcurrent-> next ;
                cntln++ ;
                
            }
        else
        if (strcmp(current -> word,".extern") == 0) 
            {
                current = current -> next ; /* geting the name */
                cntln++ ; /* name is end of line */
                strcpy(symcurrent ->name ,current -> word) ;
                
                symcurrent -> value = 0 ;
                
                symcurrent -> type = external ;
                symcurrent-> next = malloc(sizeof(symbol)) ;
                symcurrent = symcurrent-> next ;
            } 
        else    
        if (strchr(current -> word,':') != NULL)
        {
                strncpy(symcurrent ->name ,current -> word,strlen(current -> word) - 1) ;/*without the ":"  */
                strncpy(savename,symcurrent ->name,strlen(current -> word) - 1) ;
                symcurrent -> value = ic ;
                if(strcmp(current -> next -> word,".data") == 0
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
            current = current -> next ;
            cntln++ ;
            i = 0 ; 
            while(current -> word[strlen(current -> word) - 1] != '\n') 
            {
                if(isdigit(current -> word[0]) || current -> word[0] == '-' ||current -> word[0] == '+')
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
                    if(strcmp(current -> word,",") != 0)
                    {
                    symhelper = symhead ;
                    while(symhelper != NULL) 
                    {
                        if(strcmp(symhelper -> name,current -> word) == 0)
                        {
                            strcpy(datacurrent -> name ,savename) ;
                            datacurrent -> index = i ; 
                             i++ ; 
                            datacurrent -> val = symhelper -> value ;
                            datacurrent -> type = tdata;
                            datacurrent-> next = malloc(sizeof(data)) ;
                            datacurrent = datacurrent -> next ;
                            dc++ ;
                            break ;
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
            current = current -> next ;
        }
        else
        if(strcmp(current -> word,".string") == 0) 
        {
            current = current -> next ;
        /*    cntln ;*/
            i = 0 ;
            j = 1 ; 
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
            current = current -> next ;
        }
        else
        if(conv_enum(current -> word) != NONE)
        ic++ ;
        else
        if (strchr(current -> word,'[') != NULL &&  (strchr(current -> word,']') != NULL))
        ic = ic + 2 ;
        else
        if(conv_enum3(current -> word) != rNONE)
        {
            if (strcmp(current -> next -> word , ",") == 0 && conv_enum3(current -> next -> next -> word) != rNONE)
            {
                current = current -> next -> next ; /*making sure i dont count twice if i have 2 registers  */
            }
            ic++ ;
        }
        else
        ic ++ ;
        
        current = current -> next ;
    }
    
    return haserror ; 
    
}
