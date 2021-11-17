#include <cctype>
#include "dataStructure.h"
#include "search.h"


int main()
{
    vector<list<Player>> tablePlayer(5000);
    vector<list<UserRating>> tableReviews(30000);
    vector<Player> players;
    struct TrieNode *root = getNode();
    loadDataStructures(tablePlayer, tableReviews,players,root ,"players_clean2.csv", "rating.csv","tags.csv");
    string searchOption;
    string searchParam;
    int top;
    while(true){
        cout << "Digite a pesquisa:\n";
        cin>> searchOption;

        if(searchOption=="player"){
            getline(cin, searchParam);
            searchParam=searchParam.substr(searchParam.find_first_not_of(" "));
            PrefixSearch(tablePlayer,searchParam,root);
        }
        else if(searchOption=="user"){
            cin >> searchParam;
            userSearch(tableReviews,tablePlayer,stoi(searchParam));
        }
        else if(searchOption.substr(0,3) == "top"){
            top =atoi(searchOption.substr(3).c_str());
            getline(cin, searchParam);
            if(top<=0){
                cout<< "Digite um numero n valido para a pesquisa, formato topN\n";
            }else{
                auto first = searchParam.find("'");
                auto last = searchParam.find_first_of("'",first+1);
                searchParam=searchParam.substr(first+1,last-first-1);
                cout<< searchParam << "\n";
                topPositionSearch(players,top,searchParam);
            }
            
        }
        else{
            cout << "Opcao invalida" << "\n";
        }
        cin.clear();
        fflush(stdin);

    }
    return 0;
}
