#include <stdio.h>

int first4(int x){
   return x/10000;
   }
int last4(int x){
   return x%10000;
   }
int first8(int x){
   return x/100000000;
   }
int last8(int x){
   return x%100000000;
   }
int shift4(int x){
   return x*10000;
   }

int main(void){
  int x;
  int a, b;
  int c1, c2, c3;

  scanf("%d", &x); 
  a = first4(x);
  b = last4(x);

  c3 = a*a + first4(2*a*b);
  c2 = last4(2*a*b+first4(b*b));
  c1 = last4(b*b);

  printf("%8d%04d%04d", c3, c2, c1);  

  return 0;
}