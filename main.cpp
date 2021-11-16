#include <cctype>
#include "dataStructure.h"
#include "search.h"


int main()
{
    vector<list<Player>> tablePlayer(5000);
    vector<list<UserRating>> tableReviews(30000);
    vector<Player> players;
    struct TrieNode *root = getNode();
    loadDataStructures(tablePlayer, tableReviews,players,root ,"players_clean2.csv", "rating.csv");
    string searchOption;
    string searchParam;
    while(true){
        cout << "Digite a pesquisa:\n";
        cin>> searchOption;
        if(searchOption=="player"){
            cin >>searchParam;
            PrefixSearch(tablePlayer,searchParam,root);
        }
        else if(searchOption=="user"){
            cin >> searchParam;
            userSearch(tableReviews,tablePlayer,stoi(searchParam));
        }
        else{
            cout << "Opcao invalida";
        }

    }
    return 0;
}
