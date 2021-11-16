#ifndef dataStruture_h
#define dataStruture_h
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "parser.hpp"
using namespace aria::csv;
using namespace std;

const int ALPHABET_SIZE = 29;

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

bool playerReviewCount(vector<list<Player>> &table,int player_id,float review);
void printAllPlayers(vector<list<Player>> &table);
void loadDataStructures(vector<list<Player>> &tablePlayer, vector<list<UserRating>> &tableReviews, vector<Player> &players,struct TrieNode *root, string filenamePlayer, string filenameRatings);
struct TrieNode *getNode(void);
void insert(struct TrieNode *root, string key, int sofifa_id);
void bSortUserRVector(vector<UserRating> &ratings);

#endif
