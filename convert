void convert(int n)
{
    int temp , index = 6;
    char conv[7] ;
    while(n)
    {
        temp = n & 3 ;
        printf("temp %d ", temp);
        n >>= 2 ; 
        switch(temp)
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
    while(index >= 0)
    {
        conv[index] = '*' ;
        index-- ;
    }
     printf("%s", conv) ;
    
}
