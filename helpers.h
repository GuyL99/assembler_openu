#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1
typedef enum {mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,red,prn,jsr,rts,stop,NONE} command;
typedef enum {A,R,E}ARE;
typedef enum {instrct,cmnd,macro,external} symerer;
typedef enum {tdata,tstring}diffing;
typedef enum {define,dat,str,ent,ext, None} insmac;
typedef enum {r0,r1,r2,r3,r4,r5,r6,r7,rNONE}regis;
typedef struct sym{
	char name[31];
	unsigned int value;
/*we are assuming a size of program between 1 and 156 instructuins*/	
	unsigned int type;
	struct sym *next;
} symbol;
#define start 100 
typedef struct code{
	unsigned int IC;
	int ARE[2];
	int REST[12];
	struct code *next;
} CODE;
typedef struct list{
	struct list *next;
	char word[31];
} list;
typedef struct return_pre{
	list *head_return;
	int valid;
} return_pre;
typedef struct data{
	unsigned int index;	
	char name[31];
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
    {r1, "r1"},
    {r2, "r2"},
    {r3, "r3"},
    {r4, "r4"},
    {r5, "r5"},
    {r6, "r6"},
    {r7, "r7"},
};
regis conv_enum3 (const char *str)
{
     int j;
     for (j = 0;  j < sizeof (regcnvrt) / sizeof (regcnvrt[0]);  ++j)
         if (!strcmp (str, regcnvrt[j].str))
             return regcnvrt[j].val;    
     return rNONE;
}
