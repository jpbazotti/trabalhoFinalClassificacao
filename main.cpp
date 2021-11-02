#include "dataStructure.h"

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // sofifa_id é zero se não for fim de nome, se for diferente de zero, representa
    // o fim do nome e o id sofifa do jogador
    int sofifa_id;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    pNode->sofifa_id = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key, int sofifa_id)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->sofifa_id = sofifa_id;
}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && (pCrawl->sofifa_id != 0));
}

void le_entrada()
{
}

int main()
{
    vector<list<player>> tablePlayer(5000);
    vector<list<UserRating>> tableReviews(30000);
    loadDataStructures(tablePlayer,tableReviews,"players_clean2.csv","minirating.csv");
    printPlayerTable(tablePlayer);
}