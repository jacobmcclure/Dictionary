//-----------------------------------------------------------------------------
// DictionaryTest.c
// Test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"


int main(){
   Dictionary J = newDictionary();
   Dictionary M = newDictionary();
   char* k;
   char* str;
   char* str2;
   char* v;
   int i, j;
   char* arr0[] = {"press","to","respects","bar","hello","m8","pay"};
   char* arr1[] = {"F","pay","foo","hallo","hoy","freund","pagar"};
   char* arr2[] = {"yeet","esrever","backwards","bit","anagram","uh","bruh"};
   char* arr3[] = {"teey","reverse","sdrawkcab","tib","margana","hu","hurb"};

   printf("%d\n", size(J));
   printf("%d\n", size(M));

   for(i=0; i<7; i++){
      insert(J, arr0[i], arr1[i]);
   }

   for(j=0; j<7; j++){
      insert(M, arr2[j], arr3[j]);
   }

   printf("%d\n", size(J));
   printf("%d\n", size(M));

   // print out the Dictionary
   str = DictionaryToString(J);
   str2 = DictionaryToString(M);   
   printf("%s\n", str);
   free(str);
   printf("%s\n", str2);
   free(str2);


   for(i=0; i<7; i++){
      k = arr0[i];
      v = lookup(J, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }
   printf("\n");

   delete(J, "press");
   delete(J, "to");
   delete(J, "respects");
   delete(J, "bar");
   delete(J, "pay");

   // print out the Dictionary
   str = DictionaryToString(J);
   printf("%s\n", str);
   free(str);

   for(i=0; i<7; i++){
      k = arr0[i];
      v = lookup(J, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }
   printf("\n");

   // check size before and after makeEmpty()
   printf("%d\n", size(M));
   makeEmpty(M);
   printf("%d\n", size(M));

   printf("%d\n", size(J));
   makeEmpty(J);
   printf("%d\n", size(J));

   // free dictionaries
   freeDictionary(&J);
   freeDictionary(&M);

   return(EXIT_SUCCESS);
}
