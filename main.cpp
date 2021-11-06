#include <cctype>
#include "dataStructure.h"
#include "search.h"


int main()
{
    vector<list<player>> tablePlayer(5000);
    vector<list<UserRating>> tableReviews(30000);
    vector<int> list_id(0,100000);
    loadDataStructures(tablePlayer, tableReviews, "players_clean2.csv", "minirating.csv");
    //printPlayerTable(tablePlayer);

    struct TrieNode *root = getNode();

    ifstream f2("players_clean2.csv");
    CsvParser parser2(f2);
    vector<Player> players;
    for (auto &row : parser2)
    {
        try
        {
            Player player;
            player.sofifa_id = stoi(row.at(0));
            player.name = row.at(1);
            player.position = row.at(2);
            players.push_back(player);
        }
        catch (invalid_argument const &)
        {
            //cout << "pula primeira linha\n";
        }
    }
 

    for (Player player : players)
    {
        insert(root, player.name, player.sofifa_id);
    }
    search(root, "joao pedro", list_id);

    for (int i = 0; i < (int)list_id.size(); i++)
    {
        cout << list_id.at(i) << "\n";
    }
    cout << "end";
    return 0;
}
