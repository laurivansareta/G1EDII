#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
typedef struct trie_node trie_node_t;
struct trie_node
{
 int value;
 trie_node_t *children[ALPHABET_SIZE];
};

// trie ADT
typedef struct trie trie_t;
struct trie
{
 trie_node_t *root;
 int count;
};
typedef struct letra letras;
struct letra {

 char letra;
 int pos;

};





// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void)
{

 trie_node_t *pNode = NULL;

 pNode = (trie_node_t *)malloc(sizeof(trie_node_t));

 if (pNode)
 {
  int i;

  pNode->value = 0;

  for (i = 0; i < ALPHABET_SIZE; i++)
  {
   pNode->children[i] = NULL;
  }
 }

 return pNode;
}

// Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{


 pTrie->root = getNode();
 pTrie->count = 0;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, char key[])
{

 setlocale(LC_ALL, "Portuguese");

 int level;
 int length = strlen(key);
 int index;
 trie_node_t *pCrawl;

 pTrie->count++;
 pCrawl = pTrie->root;

 for (level = 0; level < length; level++)
 {
  index = CHAR_TO_INDEX(key[level]);
  if (!pCrawl->children[index])
  {
   pCrawl->children[index] = getNode();


  }

 
  pCrawl = pCrawl->children[index];

 }

 // mark last node as leaf
 pCrawl->value = pTrie->count;

 printf(" -Inserido- ");

}


void readAndInsert(trie_t *pTrie)
{

 setlocale(LC_ALL, "Portuguese");

 char c;

 FILE *file;
 file = fopen("smalltestfile.txt", "r");


 char string[46]; // MAIOR PALAVRA DO PORTUGUES. - Pneumoultramicroscopicossilicovulcanoconiótico -

 memset(string, 0, 46); // Deixa a string limpa.

 letras letpos[1000];

 int letraCount = 0;


 int i = 0;

 int posMark = 0; //Marcador de posição do texto

 if (file) {
  while ((c = getc(file)) != EOF) {


   if (c == ' ') { 

    if ((strcmp(string, "a") == 0) || (strcmp(string, "O") == 0) || (strcmp(string, "e") == 0)) {

     letpos[letraCount].letra = string[0];
     letpos[letraCount].pos = posMark;

     printf("\nLET - %c, POS - %d\n", letpos[letraCount].letra, letpos[letraCount].pos);

     letraCount++;

     posMark++;

     memset(string, 0, 46); //Limpar a string para a nova palavra.

     c = getc(file);

     i = 0;

    } else {
     
     printf("\n");

     c = getc(file);

     printf(" -Entrou- ");

     insert(pTrie, string);

     printf("%s - %d \n", string, posMark);

     //printf("AQUI??\n");

     memset(string, 0, 46); //Limpar a string para a nova palavra.

     i = 0;

     posMark++;
     
    }

   }

   
   string[i] = c;

   i++;

   printf("Yolo %s\n", string);
   

  }
  if (c == EOF) {

   insert(pTrie, string);

   printf("%s - %d", string, posMark);


  }

  fclose(file);

 }



}

// Returns non zero, if key presents in trie
int search(trie_t *pTrie, char key[])
{

 setlocale(LC_ALL, "Portuguese");

 int level;
 int length = strlen(key);
 int index;
 trie_node_t *pCrawl;

 pCrawl = pTrie->root;

 for (level = 0; level < length; level++)
 {
  index = CHAR_TO_INDEX(key[level]);

  if (!pCrawl->children[index])
  {
   return 0;
  }

  pCrawl = pCrawl->children[index];
 }

 return (0 != pCrawl && pCrawl->value);
}

// Driver
int main()
{

 setlocale(LC_ALL, "Portuguese");

 // Input keys (use only 'a' through 'z' and lower case)
 //char keys[][8] = { "the", "a", "there", "answer", "any", "by", "bye", "their", "banana" };
 trie_t trie;

 

 char output[][32] = { "Not present in trie", "Present in trie" };


 


 initialize(&trie);

 printf("PAST HERE ééééé\n");

 readAndInsert(&trie);

 printf("\nPASSOU DO INSERT\n");

 // Construct trie
 /*for (int i = 0; i < ARRAY_SIZE(keys); i++)
 {
  insert(&trie, keys[i]);
 }
 */

 // Search for different keys
 printf("%s --- %s\n", "é", output[search(&trie, "é")]);
 printf("%s --- %s\n", "não", output[search(&trie, "não")]);
 printf("%s --- %s\n", "portugues", output[search(&trie, "portugues")]);
 printf("%s --- %s\n", "thaw", output[search(&trie, "thaw")]);
 printf("%s --- %s\n", "banana", output[search(&trie, "banana")]);

 return 0;
}
