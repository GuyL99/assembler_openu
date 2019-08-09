void convert(int n)
{
    int temp , index = convertlen - 1;
    char conv[convertlen] ;
    while(n)
    {
        temp = n & 3 ; /* 3 = 11 in binary */ 
        printf("temp %d ", temp);
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
     printf("%s", conv) ;
    
}
