#include<stdio.h>

int main()
{
   int tab[] = {0,1,2,3,4,5};

   printf("%lu %lu %lu\n", sizeof(char), sizeof(int), sizeof(double));

   int  * p1;
   char * p2;

   p1 = tab; 
   printf("%d ", *p1);
   p2 = (char *) p1;
   p2 += sizeof(int);

   printf("%d\n", *((int*)p2));
   printf("%d\n", *(p1+6));

   /*p1 = NULL;
   printf("%d", *p1);*/

   return 0;
}

