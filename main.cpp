#include <iostream>
#include <string>
#include <cctype>
#include "parser.hpp"

using namespace aria::csv;
using namespace std;

const int ALPHABET_SIZE = 28;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // sofifa_id é zero se não for fim de nome, se for diferente de zero, representa
    // o fim do nome e o id sofifa do jogador
    int sofifa_id;
};

typedef struct tipoNo Nodo_Rating;
struct tipoNo{
    int sofifa_id;
    int media;
    int total;
};

typedef struct rating UserRating;
struct rating{
  int user_id;
  int sofifa_id;
  float rating;
};

typedef struct player Player;
struct player{
  int sofifa_id;
  string name;
  string position;
};

unsigned long djb2Hash(string str)
{
    unsigned long hash = 5381;
    for (auto c : str)
        hash = ((hash << 5) + hash + c);

    return hash;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

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
        key[i] = tolower(key[i]);
        int index = key[i] - 'a';
        if(key[i] == ' '){
            index = 26;
        }
        if(key[i] == '-'){
            index = 27;
        }
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->sofifa_id = sofifa_id;
}

// Returns true if key presents in trie, else
// false
int search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        key[i] = tolower(key[i]);
        int index = key[i] - 'a';
        if(key[i] == ' '){
            index = 26;
        }
        if(key[i] == '-'){
            index = 27;
        }
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    if(pCrawl != NULL && (pCrawl->sofifa_id != 0)){
        return pCrawl->sofifa_id;
    }
    else{
        return 0;
    }
}

void le_entrada(){


}

int main() {
    struct TrieNode *root = getNode();

    ifstream f2("players_clean2.csv");
  CsvParser parser2(f2);
  vector<Player> players;
  for (auto& row : parser2) {
    try{
    Player player;
    player.sofifa_id=stoi(row.at(0));
    player.name=row.at(1);
    player.position=row.at(2);
    players.push_back(player);
      }catch(const invalid_argument e){
          cout << "pula primeira linha\n";
      }
  }
  for(Player player:players){
    insert(root, player.name, player.sofifa_id);
  }
  int achou = search(root, "Thiago Emiliano da Silva");

  cout << achou << "\n";
}
