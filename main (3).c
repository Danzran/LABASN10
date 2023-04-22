#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TrieNode{
    int count;
    struct TrieNode *children[26];
};

void insert(struct TrieNode **ppTrie, char *word) {
  //Temp node for traversal
    struct TrieNode *pTrie = *ppTrie;
    //Check to see if there is already an initialized node
    if (pTrie == NULL) {
        pTrie = (struct TrieNode*)malloc(sizeof(struct TrieNode));
        pTrie->count = 0;
        for (int i = 0; i < 26; i++) {
            pTrie->children[i] = NULL;
        }
        *ppTrie = pTrie;
    }
    
    for (int i = 0; i < strlen(word); i++) {
      // fun trick to get the index with ascii values
        int index = (word[i]) - 'a';
        if (!pTrie->children[index]) {
          // calloc supposed to be better here but wasn't working for me.
            pTrie->children[index] = (struct TrieNode*)malloc(sizeof(struct TrieNode));
            pTrie->children[index]->count = 0;
            for (int j = 0; j < 26; j++) {
                pTrie->children[index]->children[j] = NULL;
            }
        }
        pTrie = pTrie->children[index];
    }
    pTrie->count++;
}

int numberOfOccurrences(struct TrieNode *pTrie, char *word) {
  // Check if initialized once again
    if (pTrie == NULL) {
        return 0;
    }

  
    for (int i = 0; i < strlen(word); i++) {
        int index = (word[i]) - 'a';
      //If the pointer doesn't exist the word is not there so return 0
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    return pTrie->count;
}

// I don't even know how this one works I had to get help
struct TrieNode *deallocateTrie(struct TrieNode *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i]) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    //read the number of the words in the dictionary
    //parse line by line, and insert each word to the trie data structure
  // I didn't know if I had to initialize in a function but I did this and it works
    struct TrieNode *trie = NULL;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++) {
        insert(&trie, pWords[i]);
    }
    for (int i=0;i<5;i++) {
        printf("\t%s : %d\n",pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
