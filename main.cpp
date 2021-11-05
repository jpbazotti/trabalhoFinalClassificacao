#include <iostream>
#include <string>
#include <cctype>
#include "parser.hpp"

using namespace aria::csv;
using namespace std;
#include "dataStructure.h"

void print_nodes(struct TrieNode *node, string substring, vector<int> &list_id){
    int i;
    char c;

    if(node->sofifa_id !=0){
        list_id.push_back(node->sofifa_id);
        cout << substring << " " << node->sofifa_id <<"\n";
        return;
    }
    for(i=0; i<=ALPHABET_SIZE; i++){
        if(node->children[i] != NULL){
            c = i + 'a';
            if (i == 26){
                c = ' ';
            }
            if (i == 27){
                c = '-';
            }
            if(i == 28){
                c = '.';
            }
            //cout << substring << "\n";
            //getchar();
            print_nodes(node->children[i], substring+=c, list_id);
            substring.resize(substring.size() - 1);
        }
    }
    return;
}

// Returns true if key presents in trie, else
// false
int search(struct TrieNode *root, string key, vector<int> &list_id)
{
    struct TrieNode *pCrawl = root;

    for (unsigned long long int i = 0; i < key.length(); i++)
    {
        key[i] = tolower(key[i]);
        int index = key[i] - 'a';
        if (key[i] == ' ')
        {
            index = 26;
        }
        if (key[i] == '-')
        {
            index = 27;
        }
        if(key[i] == '.'){
            index = 28;
        }
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    print_nodes(pCrawl, key, list_id);

    return 0;
}

int main()
{
    vector<list<player>> tablePlayer(5000);
    vector<list<UserRating>> tableReviews(30000);
    vector<int> list_id;
    loadDataStructures(tablePlayer, tableReviews, "players_clean2.csv", "minirating.csv");
    //printPlayerTable(tablePlayer);

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
        }
        catch(invalid_argument const&){
            //cout << "pula primeira linha\n";
        }
  }
  //for(Player player:players){
    //insert(root, player.name, player.sofifa_id);
  //}
  //int achou = search(root, "Thiago Emiliano da Silva");
  //cout << achou << "\n";

  userSearch(tableReviews,tablePlayer,1445);
  cout << "end";
  for(Player player:players){
        insert(root, player.name, player.sofifa_id);
  }
  search(root, "Fer", list_id);

    for(int i=0;i<list_id.size();i++){
        cout << list_id.at(i) << "\n";
    }
  //cout << achou << "\n";
}
