#ifndef search_h
#define search_h
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "dataStructure.h"
using namespace aria::csv;
using namespace std;
//Imprime cabecalho de uma tabela;
void printHeader(vector<string> fields,vector<int> fieldSizes);
//Imprime items de uma tabela;
void printTable(vector<string> fields, vector<int> fieldSizes);
//Retorna todas as palavras a partir de um nodo;
void print_nodes(struct TrieNode *node, string substring, vector<int> &list_id);
//Recebe uma string e acha o nodo correspondente na trie;
int searchTrie(struct TrieNode *root, string key, vector<int> &list_id);
//Retorna o resultado da pesquisa atraves de prefixo
void PrefixSearch(vector<list<Player>> tablePlayer, string prefix,struct TrieNode *root);
//Retorna o resultado da pesquisa atraves de id de usuario 
void userSearch(vector<list<UserRating>> &tableReviews,vector<list<player>> &tablePlayer,int userID);
//Recebe uma string, remove virgulas e separa em um array usando espaco em branco como delimitador
vector<string> positionSeparator(string positions);
//Retorna o resultado da pesquisa atraves de posicao do jogador 
void topPositionSearch(vector<Player> players,int topx,string pos);
#endif