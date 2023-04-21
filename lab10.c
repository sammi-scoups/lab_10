#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    struct Trie *children[26];
    int flag;
    
}; 


void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie); // do it recurrsivelly 


void insert(struct Trie **ppTrie, char *word)
{
    struct Trie *temp = *ppTrie;
    if(temp == NULL)
    {
        temp = (struct Trie *) calloc (1, sizeof(struct Trie));
        *ppTrie = temp;
    }

    int length = strlen(word);
    
    for (int a = 0; a < length; a++){
        char y = word[a];
        if (y >= 'a' && y <= 'z')
        {
            y -='a';
            if (temp->children[y] == NULL)
            {
                temp->children[y] = (struct Trie*) calloc(1, sizeof(struct Trie)); // use calloc so it is not set to garbage value
            }
            temp = temp->children[y];
        }
    }
    temp->flag++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if(pTrie==NULL)
    {
        return 0;
    }
    
    for(int b =0; word[b] != '\0'; b++)
    {
        char x = word[b];
        if (x >= 'a' && x <= 'z')
        {
            x -= 'a';
            pTrie = pTrie->children[x];
            if (pTrie==NULL)
            {
                return 0;
            }
        }
    }
    return pTrie->flag;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }

    for (int c =0; c < 26; c++)
    {
        pTrie->children[c] = deallocateTrie(pTrie->children[c]);
    }

    free(pTrie);
    return NULL;
}

int main(void)
{
      //read the number of the words in the dictionary
      // parse line  by line, and insert each word to the trie data structure
    struct Trie *trie = NULL;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
        {
            insert(&trie,pWords[i]);
            printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
        }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;

}