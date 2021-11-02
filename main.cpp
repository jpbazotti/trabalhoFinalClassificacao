#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "parser.hpp"

using namespace aria::csv;
using namespace std;

const int ALPHABET_SIZE = 26;

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
  int reviewCout;
  float reviewTotal;
};

bool playerReviewCount(vector<list<player>> &table,int player_id,float review)
{
    int index = player_id % table.size();
    list<player>::iterator it = table.at(index).begin();
    while (it != table.at(index).end())
    {
        if ((*it).sofifa_id == player_id)
        {
          (*it).reviewCout++;
          (*it).reviewTotal += review;
          return true;
        }
        advance(it,1);
    }
    return false;
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
void printTable(vector<list<Player>> &table)
{
    for (int i = 0; i < (int)table.size(); i++)
    {
        cout << i << ": ";
        list<Player>::iterator it = table.at(i).begin();
        while (it != table.at(i).end())
        {
            cout << (*it).sofifa_id << " "<<(*it).name << " " << (*it).position << " " <<(*it).reviewCout << " " <<(*it).reviewTotal << "->";
            advance(it,1);
        }
        cout << "\n";
    }
}
void le_entrada(){


}

int main() {
  ifstream f("rating.csv");
  CsvParser parser(f);
  vector<UserRating> ratings;
  ifstream f2("players_clean2.csv");
  CsvParser parser2(f2);
  vector<list<player>> tablePlayer(5000);

  for (auto& row : parser2) {
    try{
    Player player;
    player.sofifa_id=stoi(row.at(0));
    player.name=row.at(1);
    player.position=row.at(2);
    player.reviewCout=0;
    player.reviewTotal=0;
    int hash = player.sofifa_id % tablePlayer.size();
    tablePlayer.at(hash).push_back(player);
      }catch(const invalid_argument e){
          cout << "pula primeira linha";
      }
  }
    vector<list<UserRating>> tableReviews(30000);

  for (auto& row : parser) {
    try{
    UserRating rating;
    rating.user_id=stoi(row.at(0));
    rating.sofifa_id=stoi(row.at(1));
    rating.rating=stof(row.at(2));
    int hash= rating.user_id % tableReviews.size();
    tableReviews.at(hash).push_back(rating);
    playerReviewCount(tablePlayer,rating.sofifa_id,rating.rating);
    }
    catch(const invalid_argument e){
        cout << "pula primeira linha";
    }
  }
}