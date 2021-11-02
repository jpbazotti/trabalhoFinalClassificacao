#ifndef dataStruture_h
#define dataStruture_h
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "parser.hpp"
using namespace aria::csv;
using namespace std;

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

bool playerReviewCount(vector<list<player>> &table,int player_id,float review);
void printPlayerTable(vector<list<Player>> &table);
void loadDataStructures(vector<list<player>> &tablePlayer,vector<list<UserRating>> &tableReviews,string filenamePlayer,string filenameRatings);

#endif