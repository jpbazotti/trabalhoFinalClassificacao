#ifndef dataStruture_h
#define dataStruture_h
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
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

typedef struct tag Tag;
struct tag{
  string tag_string;
  vector<int> sofifa_id;
};

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // sofifa_id é zero se não for fim de nome, se for diferente de zero, representa
    // o fim do nome e o id sofifa do jogador
    int sofifa_id;
};

//Hash para strings
unsigned long djb2Hash(string str);
//Retorna check de player com menos de 1000 avaliacoes
bool notEnoughReviews(Player player);
//Atualiza a quantidade de reviews do jogador e o total de notas;
bool playerReviewCount(vector<list<Player>> &table,int player_id,float review);
//Imprime todos os jogadores da hash table;
void printAllPlayers(vector<list<Player>> &table);
//Faz bubble sort no vetor de players
void bSortPlayerVector(vector<Player> &players);
//Carrega todas as estruturas para memoria
void loadDataStructures(vector<list<Player>> &tablePlayer, vector<list<UserRating>> &tableReviews, vector<list<Tag>> &tableTags, vector<Player> &players, struct TrieNode *root,string filenamePlayer, string filenameRatings, string filenameTags);
//Retorna um novo nodo da Trie com filhos inicializados para null
struct TrieNode *getNode(void);
//Insere um nome na trie
void insert(struct TrieNode *root, string key, int sofifa_id);
//Faz bubble sort no vetor de user ratings
void bSortUserRVector(vector<UserRating> &ratings);

#endif
