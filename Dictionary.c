//--------------------------------------------------------------------------
// Dictionary.c
// 
// Dictionary ADT implemented using an array of linked lists
//--------------------------------------------------------------------------
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<assert.h>
#include"Dictionary.h"
#define tableSize 101

// Private Types and Functions ------------------------------------------------

// NodeObj type
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node type
typedef struct NodeObj* Node;

// DictionaryObj type
typedef struct DictionaryObj{
   int numItems; 
   Node* T;
} DictionaryObj;

// Dictionary type
typedef struct DictionaryObj* Dictionary;

// Constructors and Destructors ----------------------------------------------

// constructor for the Dictionary type
Dictionary newDictionary(){
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->T = calloc(tableSize, sizeof(Node));
   D->numItems = 0;
   return D;
}

// destructor: freeDictionary()
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
      free((*pD)->T);
      free(*pD);
      *pD = NULL;
   }
}

// constructor for the Node type
Node newNode(char* k, char* v){
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


// Hash Functions ------------------------------------------------------------

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int); shift = shift & (sizeInBits - 1);
   if ( shift == 0 ){
      return value;
   }
   return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int 
unsigned int pre_hash(char* input) {
   unsigned int result = 0xBAE86554; 
   while (*input) {
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}


// ADT Operations ------------------------------------------------------------

// size()
int size(Dictionary D){
   if( D==NULL ){
      fprintf(stderr,
         "Dictionary Error: size() called on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return D->numItems;
}

// lookup(): return the value at D if k=key, else return NULL
char* lookup(Dictionary D, char* k){
   if( D==NULL ){
      fprintf(stderr,
         "Dictionary Error: size() called on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   int idx = hash(k);
      Node TN = D->T[idx];
      while((TN) != NULL){
         if(strcmp(TN->key, k) == 0){
           return TN->value;
         }
         TN = TN->next;
      }

  return NULL;
}

// insert()
void insert(Dictionary D, char* k, char* v){
   if(D == NULL){
      fprintf(stderr, "Dictionary Error: insert() called on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   if(lookup(D, k) != NULL){
      fprintf(stderr,"Dictionary Error: insert() called on value where key is already at that value\n");
      exit(EXIT_FAILURE);
   }

   // if the list is empty
   int idx = hash(k);
   if((D->T[idx]) == NULL){
      D->T[idx] = newNode(k, v);
   }

   // insert at head and shift old head
   else {
      Node TH = D->T[idx];
      D->T[idx] = newNode(k, v);
      D->T[idx]->next = TH;
   }

   (D->numItems)++;
}

// void delete - two cases: deleting head or deleting inside of list
void delete(Dictionary D, char* k){
   if( D==NULL ){
      fprintf(stderr,
         "IntegerList Error: delete() called on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   // if specified key is already NULL, throw error
   if(lookup(D, k) == NULL){
      fprintf(stderr,"Dictionary Error: delete() called on value where key is already at that value\n");
      exit(EXIT_FAILURE);
   }

   int idx = hash(k);
   Node TT = D->T[idx];
   if(lookup(D, k) != NULL){
      if(strcmp(TT->key, k) == 0){
         Node TH = D->T[idx];
         D->T[idx] = TT->next;
         freeNode(&TH);
      }
      else {
         Node TH = D->T[idx];
         while(TH != NULL){
            Node TT = TH;
            TH = TH->next;
            if (strcmp(TH->key, k) == 0){
               TT->next = TH->next;
               freeNode(&TH);
            }
         }
      }
   }

   (D->numItems)--;
}

// Helper
// counts number of chars
// Make a temp node
// Set temp node to D->head
// Inside loop: add length of key and value and 2 then temp = temp->next
int countChars(Dictionary D){
   int count = 0;
   for (int i=0; i<tableSize;i++){  
      Node TN = D->T[i];
      while(TN != NULL){
         count += (strlen(TN->key)+strlen(TN->value)+2);
         TN = TN->next;
      }
   }

   return count;
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr,
         "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   for (int i = 0; i<tableSize; i++){
      Node TH;
      Node R = D->T[i];
      while (R != NULL){
         TH = R->next;
         D->T[i] = TH;
         freeNode(&R);
         R = TH;
      }
   }
   D->numItems = 0;
}

// DTS(): returns dictionary as string
char* DictionaryToString(Dictionary D){
   //char* str;
   if( D==NULL ){
      fprintf(stderr,
         "Dictionary Error: calling DictionaryToString() on NULL Dictionary "\
         "reference\n");
      exit(EXIT_FAILURE);
   }

   int n = countChars(D) + 1;
   char* str = malloc(n*sizeof(char));
   str[0] = '\0';
   for (int i = 0; i<tableSize; i++){
      Node R = D->T[i];
      while ( R!=NULL){
         strcat(str, R->key);
         strcat(str, " ");
         strcat(str, R->value);
         strcat(str, "\n");
         R = R->next;         
      }
   }

  str[n-1] = '\0';
  return str;
}
