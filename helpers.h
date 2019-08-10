#ifndef HELPERS_H
#define HELPERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1
#define start 100 /* ic start at 100 */ 
#define namelen 31 /* names is 31 Characters */
#define codelen 14 /* 14 bits to work with */
#define convertlen 7 /* 14 bits to 7 convert*/  
#define linelen 80 /*we can decide the len of line in file */ 
#define MIUNTWOBIT 2 /*2 bits after the right most*/
#define MIUNONEBIT 4 /*4 bits after the right most bit and two after where i wrote miun1*/
#define OPBIT 6 /*6 bits after the right most and two after where i wrote miun2 */
#define ADDRBIT 2 /*where i would print an address*/
#define NUMBIT 2 /*where i would print a num*/
#define EXTERNVAL 1 /*the value of an extern value as machine code*/
#define MAXERVAL 4096 /*value used for codeing the negative numbers with cropped edges 2^12 as the 12 bits that remain to code them in*/
/*enum for opcodes(easier to code and read this way)*/
#define MAXDAVEL 16383 /*value used for codeing the negative numbers with cropped edges 2^14 */
#define REGONEBIT 5 /*value used for codeing the first register */
#define REGTWOBIT 2 /*value used for codeing the second register */
typedef enum {mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,red,prn,jsr,rts,stop,NONE} command;
/*enum for symbol types*/
typedef enum {instrct,cmnd,macro,external} symerer;
/*diffing the string for the data*/
typedef enum {tdata,tstring}diffing;
/*for locating the words*/
typedef enum {define,dat,str,ent,ext, None} insmac;
/*easier to code regsiters this way*/
typedef enum {r0,r1,r2,r3,r4,r5,r6,r7,rNONE}regis;
/*symbol table linked list struct*/
typedef struct sym{
	char name[namelen];
	unsigned int value;
/*we are assuming a size of program between 1 and 156 instructuins*/	
	unsigned int type;
	struct sym *next;
} symbol;
/*code read struct*/
typedef struct list{
	struct list *next;
	char word[namelen];
} list;
/*data+string struct*/
typedef struct data{
	unsigned int index;	
	char name[namelen];
	int val ;	
	diffing type;
	struct data *next;
} data;
/*converting oour string to out enums(making it easier to distinguish...
 some of them could appear with \n ataches so this are duplicated*/
const static struct {/* command to string */
    command     val;
    const char *str;
} cmndcnvrt [] = {
    {mov, "mov"},
    {cmp, "cmp"},
    {add, "add"},
    {sub, "sub"},
    {not, "not"},
    {clr, "clr"},
    {lea, "lea"},
    {inc, "inc"},
    {dec, "dec"},
    {jmp, "jmp"},
    {bne, "bne"},
    {red, "red"},
    {prn, "prn"},
    {jsr, "jsr"},
    {rts, "rts"},
    {stop, "stop"},
    {rts, "rts\n"},
    {stop, "stop\n"},
};
/*converting oour string to out enums(making it easier to distinguish...
 some of them could appear with \n ataches so this are duplicated*/
command conv_enum (const char *str) 
{
     int j;
     for (j = 0;  j < sizeof (cmndcnvrt) / sizeof (cmndcnvrt[0]);  ++j)
         if (!strcmp (str, cmndcnvrt[j].str))
             return cmndcnvrt[j].val;    
     return NONE;
}
const static struct {
    insmac      val;
    const char *str;
} insmcnvrt [] = {
    {define, ".define"},
    {str, ".string"},
    {dat, ".data"},
    {ent, ".entry"},
    {ext, ".extern"},
};
/*converting oour string to out enums(making it easier to distinguish...
 some of them could appear with \n ataches so this are duplicated*/
insmac conv_enum2 (const char *str)
{
     int j;
     for (j = 0;  j < sizeof (insmcnvrt) / sizeof (insmcnvrt[0]);  ++j)
         if (!strcmp (str, insmcnvrt[j].str))
             return insmcnvrt[j].val;    
     return None;
}
const static struct {
    regis       val;
    const char *str;
} regcnvrt [] = {
    {r0, "r0"},
    {r0, "r0\n"},
    {r1, "r1"},
    {r1, "r1\n"},
    {r2, "r2"},
    {r2, "r2\n"},
    {r3, "r3"},
    {r3, "r3\n"},
    {r4, "r4"},
    {r4, "r4\n"},
    {r5, "r5"},
    {r5, "r5\n"},
    {r6, "r6"},
    {r6, "r6\n"},
    {r7, "r7"},
    {r7, "r7\n"},
};
/*converting oour string to out enums(making it easier to distinguish...
 some of them could appear with \n ataches so this are duplicated*/
regis conv_enum3 (const char *str)
{
     int j;
     for (j = 0;  j < sizeof (regcnvrt) / sizeof (regcnvrt[0]);  ++j)
         if (!strcmp (str, regcnvrt[j].str))
             return regcnvrt[j].val;    
     return rNONE;
}
#endif
