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
#define MIUNTWOBIT 2
#define MIUNONEBIT 4
#define OPBIT 6
#define ADDRBIT 2
#define NUMBIT 2
#define EXTERNVAL 1
#define MAXERVAL 4096

typedef enum {mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,red,prn,jsr,rts,stop,NONE} command;
typedef enum {A,R,E}ARE;
typedef enum {instrct,cmnd,macro,external} symerer;
typedef enum {tdata,tstring}diffing;
typedef enum {define,dat,str,ent,ext, None} insmac;
typedef enum {r0,r1,r2,r3,r4,r5,r6,r7,rNONE}regis;
typedef struct sym{
	char name[namelen];
	unsigned int value;
/*we are assuming a size of program between 1 and 156 instructuins*/	
	unsigned int type;
	struct sym *next;
} symbol;

typedef struct code{
	/*int machine_code;*/
	unsigned int machine_code[codelen];
	struct code *next;
} code;
typedef struct list{
	struct list *next;
	char word[namelen];
} list;
typedef struct data{
	unsigned int index;	
	char name[namelen];
	int val ;	
	diffing type;
	struct data *next;
} data;

const static struct {
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
regis conv_enum3 (const char *str)
{
     int j;
     for (j = 0;  j < sizeof (regcnvrt) / sizeof (regcnvrt[0]);  ++j)
         if (!strcmp (str, regcnvrt[j].str))
             return regcnvrt[j].val;    
     return rNONE;
}
#endif
