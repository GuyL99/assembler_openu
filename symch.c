#include "helpers.h"
int symch(symbol symhead)
{
    symbol symcurrent = symhead ;
    symbol symhelper ;
    int count;
    int haserror = 1 ;
    
    while(symcurrent != NULL)
    {
        count = 0 ; 
        symhelper = symcurrent - next ;
        while(symhelper!=NULL)
        {
            if(strcmp(symcurrent - name ,symhelper - name) == 0) 
            count++ ;
            symhelper = symhelper - next ;
        }
        if (count  0)
        {
        printf(symbol %s is writen Twice  n,symcurrent - name) ;
        haserror = 0 ;
        }
        symcurrent = symcurrent - next ;
    
    }
    return haserror ;
    
}
