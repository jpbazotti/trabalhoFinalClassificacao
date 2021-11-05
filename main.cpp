#include <iostream>
#include <string>
#include <cctype>
#include "parser.hpp"

using namespace aria::csv;
using namespace std;
#include "dataStructure.h"

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
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
    loadDataStructures(tablePlayer, tableReviews, "players_clean2.csv", "minirating.csv");
    printPlayerTable(tablePlayer);

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
        catch(const invalid_argument e){
            cout << "pula primeira linha\n";
        }
  }
  for(Player player:players){
    insert(root, player.name, player.sofifa_id);
  }
  int achou = search(root, "Thiago Emiliano da Silva");

  cout << achou << "\n";
}
