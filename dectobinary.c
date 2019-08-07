#include "helpers.h"
int *decToBinary (int n)
{
  int neg = FALSE;
  int keeper = 1;
  static int num[14];

  int i = 13;
  if (n < 0)
    {
      neg = TRUE;
      n = n * -1;
    }
  while (n >= 0 && i >= 0)
    {

      /* storing remainder in binary array*/
      if (n > 0)
	num[i] = n % 2;
      else
	num[i] = 0;
      n = n / 2;
      i--;
    }
  if (neg)
    {
      for (i = 0; i < 14; i++)
	{
	  if (num[i])
	    num[i] = 0;
	  else
	    num[i] = 1;
	}
      for (i = 13; i >= 0 && keeper != 0; i--)
	{
	  if (num[i] + keeper == 2)
	    num[i] = 0;
	  else
	    {
	      num[i] = 1;
	      keeper = 0;
	    }
	}

    }
  return num;
}
