#ifndef search_h
#define search_h
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "dataStructure.h"
using namespace aria::csv;
using namespace std;
void printHeader(vector<string> fields,vector<int> fieldSizes);
void printTable(vector<string> fields, vector<int> fieldSizes);
void print_nodes(struct TrieNode *node, string substring, vector<int> &list_id);
int searchTrie(struct TrieNode *root, string key, vector<int> &list_id);
void PrefixSearch(vector<list<Player>> tablePlayer, string prefix,struct TrieNode *root);
void userSearch(vector<list<UserRating>> &tableReviews,vector<list<player>> &tablePlayer,int userID);
#endif