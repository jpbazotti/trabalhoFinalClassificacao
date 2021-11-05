#ifndef dataStruture_h
#define dataStruture_h
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "parser.hpp"
using namespace aria::csv;
using namespace std;

const int ALPHABET_SIZE = 28;

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

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // sofifa_id é zero se não for fim de nome, se for diferente de zero, representa
    // o fim do nome e o id sofifa do jogador
    int sofifa_id;
};

bool playerReviewCount(vector<list<player>> &table,int player_id,float review);
void printPlayerTable(vector<list<Player>> &table);
void loadDataStructures(vector<list<player>> &tablePlayer,vector<list<UserRating>> &tableReviews,string filenamePlayer,string filenameRatings);
void userSearch(vector<list<UserRating>> &tableReviews,vector<list<player>> &tablePlayer,int userID);
struct TrieNode *getNode(void);
void insert(struct TrieNode *root, string key, int sofifa_id);
bool prefixSearch(struct TrieNode *root, string key, string start);

#endif
