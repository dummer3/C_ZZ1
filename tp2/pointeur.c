#include<stdio.h>;

int main()
{
   int i  , *ptri  = &i;
   char c1 = '1', *ptrc1 = &c1;

   int d;
   int * ptrd = &d;

   char c2 = '2', *ptrc2 = &c2;

   printf("ptri = %u ptrc1 = %u \n",ptri, ptrc1);
   printf("ptri = %x ptrc1 = %x \n",ptri, ptrc1);
   // seule la version suivante ne genere pas d'avertissement
   printf("ptri = %p ptrc1 = %p \n",ptri, ptrc1);
   printf("*ptri = %d et *ptrc1=%c", *ptri, *ptrc1);
   
   ptri++;
   printf("ptri = %u ptrc1 = %d \n",ptri, ptrc1);
   // cela permet de voir la taille d'un int et d'un char en memoire
   // sizeof(int)  sizeof(char)

   printf("valeur :: %f \nadresse:: %lu \nadresse_pointeur :: %x\n",*ptrd,ptrd,&ptrd);
   printf("c1 : %c et c2 :: %c\n",*ptrc1,*ptrc2);
   char * temp = ptrc1;
   ptrc1 = ptrc2;
   ptrc2 = temp;

   printf("c1 : %c et c2 :: %c\n",*ptrc1,*ptrc2);

   return 0 ;
}

