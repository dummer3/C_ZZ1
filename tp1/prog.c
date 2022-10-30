#include

void essai(int j) 
{
  int i;
  
  while(i<10) 
  {
    printf("%d ", i+j );
    ++i;
  }
}

int main() 
{
  int j;

    for(j=0; j< 10; ++j)  
    {
      essai(j);
      printf("\n");
    }
  
  return 0;
}

