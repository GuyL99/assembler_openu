void deleteList(list ** head) 
{ 
   /* deref head to get the real head */
   list * curr = *head; 
   list * next; 
  
   while (curr)  
   { 
       next = curr->next; 
       free(curr); 
       curr = next; 
   } 
    
   /* deref head to affect the real head back 
      in the caller. */
   *head = NULL; 
} 
void deleteData(data ** head) 
{ 
   /* deref head to get the real head */
   data * curr = *head; 
   data * next; 
  
   while (curr)  
   { 
       next = curr->next; 
       free(curr); 
       curr = next; 
   } 
    
   /* deref head to affect the real head back 
      in the caller. */
   *head = NULL; 
} 
void deleteSym(symbol ** head) 
{ 
   /* deref head to get the real head */
   symbol * curr = *head; 
   symbol * next; 
  
   while (curr)  
   { 
       next = curr->next; 
       free(curr); 
       curr = next; 
   } 
    
   /* deref head to affect the real head back 
      in the caller. */
   *head = NULL; 
} 
