#include "dataStructure.h"

bool playerReviewCount(vector<list<player>> &table, int player_id, float review)
{
    int index = player_id % table.size();
    list<player>::iterator it = table.at(index).begin();
    while (it != table.at(index).end())
    {
        if ((*it).sofifa_id == player_id)
        {
            (*it).reviewCout++;
            (*it).reviewTotal += review;
            return true;
        }
        advance(it, 1);
    }
    return false;
}

void printPlayerTable(vector<list<Player>> &table)
{
    for (int i = 0; i < (int)table.size(); i++)
    {
        cout << i << ": ";
        list<Player>::iterator it = table.at(i).begin();
        while (it != table.at(i).end())
        {
            cout << (*it).sofifa_id << " " << (*it).name << " " << (*it).position << " " << (*it).reviewCout << " " << (*it).reviewTotal << "->";
            advance(it, 1);
        }
        cout << "\n";
    }
}

void loadDataStructures(vector<list<player>> &tablePlayer, vector<list<UserRating>> &tableReviews, string filenamePlayer, string filenameRatings)
{
    ifstream f(filenamePlayer);
    CsvParser parser(f);
    ifstream f2(filenameRatings);
    CsvParser parser2(f2);

    for (auto &row : parser)
    {
        try
        {
            Player player;
            player.sofifa_id = stoi(row.at(0));
            player.name = row.at(1);
            player.position = row.at(2);
            player.reviewCout = 0;
            player.reviewTotal = 0;
            int hash = player.sofifa_id % tablePlayer.size();
            tablePlayer.at(hash).push_back(player);
        }
        catch (invalid_argument const &)
        {
            //cout << "pula primeira linha 1";
        }
    }
    for (auto &row2 : parser2)
    {
        try
        {
            UserRating rating;
            rating.user_id = stoi(row2.at(0));
            rating.sofifa_id = stoi(row2.at(1));
            rating.rating = stof(row2.at(2));
            int hash = rating.user_id % tableReviews.size();
            tableReviews.at(hash).push_back(rating);
            playerReviewCount(tablePlayer, rating.sofifa_id, rating.rating);
        }
        catch (invalid_argument const &)
        {
            //cout << "pula primeira linha 2";
        }
    }
}

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    pNode->sofifa_id = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key, int sofifa_id)
{
    struct TrieNode *pCrawl = root;

    for (unsigned long long i = 0; i < key.length(); i++)
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
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->sofifa_id = sofifa_id;
}

void userSearch(vector<list<UserRating>> &tableReviews, vector<list<player>> &tablePlayer, int userID)
{
    vector<UserRating> userRatings;
    int index = userID % tableReviews.size();
    tableReviews.at(index);
    list<UserRating>::iterator it = tableReviews.at(index).begin();
    while (it != tableReviews.at(index).end())
    {
        if ((*it).user_id == userID)
        {
            userRatings.push_back((*it));
        }
        advance(it, 1);
    }
    for (int i = 0; i < (int)userRatings.size(); i++)
    {
        player p;
        int indexPlayer = userRatings.at(i).sofifa_id % tablePlayer.size();
        list<player>::iterator it2 = tablePlayer.at(indexPlayer).begin();
        while (it2 != tablePlayer.at(indexPlayer).end())
        {
            if ((*it2).sofifa_id == userRatings.at(i).sofifa_id)
            {
                p=(*it2);
            }
            advance(it2, 1);
        }
        cout << userRatings.at(i).user_id << ":" << userRatings.at(i).sofifa_id << ":" << p.name << ":" << p.reviewTotal/p.reviewCout << ":" << p.reviewCout << ":" << userRatings.at(i).rating <<"\n";
    }
}
