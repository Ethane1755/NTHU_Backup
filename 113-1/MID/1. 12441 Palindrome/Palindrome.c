#include <stdio.h>
#include <string.h>

int main() {
   char str[100000];

   while(scanf("%s", str)!=EOF) {
      int i, j;
      int isPalindrome = 1;//a flag

      i = 0;
      j = strlen(str)-1;

      while (i < j) {
         //printf("%c %c\n", str[i],str[j]);
         if(str[i]!=str[j]) {
            isPalindrome = 0;
            break;
         }
         i++; j--;
      }

      if (isPalindrome)
         printf("Yes\n");
      else
         printf("No\n");
   }

   return 0;
}
