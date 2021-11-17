#include "dataStructure.h"
unsigned long djb2Hash(string str)
{
    unsigned long hash = 5381;
    for (auto c : str)
        hash = ((hash << 5) + hash + c);

    return hash;
}

bool notEnoughReviews(Player player){
    return player.reviewCout<1000;
}

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

void printAllPlayers(vector<list<Player>> &table)
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

void bSortPlayerVector(vector<Player> &players)
{
    int size = (int)players.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            float c1 = players.at(j).reviewCout != 0 ? (players.at(j).reviewTotal / players.at(j).reviewCout) : 0;
            float c2 = players.at(j + 1).reviewCout != 0 ? (players.at(j + 1).reviewTotal / players.at(j + 1).reviewCout) : 0;
            if (c1 < c2)
            {
                Player temp = players.at(j);
                players.at(j) = players.at(j + 1);
                players.at(j + 1) = temp;
            }
        }
    }
}

void loadDataStructures(vector<list<Player>> &tablePlayer, vector<list<UserRating>> &tableReviews, vector<list<Tag>> &tableTags, vector<Player> &players, struct TrieNode *root, string filenamePlayer, string filenameRatings, string filenameTags)
{
    ifstream f(filenamePlayer);
    CsvParser parser(f);

    ifstream f2(filenameRatings);
    CsvParser parser2(f2);

    ifstream f3(filenameTags);
    CsvParser parser3(f3);

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
    for (auto &row3 : parser3)
    {
        try
        {
            Tag tags;
            tags.sofifa_id = {stoi(row3.at(1))};
            tags.tag_string = row3.at(2);
            int hash = djb2Hash(tags.tag_string) % (int)tableTags.size();
            bool found = false;
            list<Tag>::iterator it = tableTags.at(hash).begin();
            while (it != tableTags.at(hash).end())
            {
                if ((*it).tag_string == tags.tag_string)
                {
                    found = true;
                    if (find((*it).sofifa_id.begin(), (*it).sofifa_id.end(), tags.sofifa_id.at(0)) == (*it).sofifa_id.end())
                    {
                        (*it).sofifa_id.push_back(tags.sofifa_id.at(0));
                    }
                }
                advance(it, 1);
            }
            if (!found)
            {
                tableTags.at(hash).push_back(tags);
            }
        }

        catch (invalid_argument const &)
        {
            //cout << "pula primeira linha 2";
        }
    }
    for (int i = 0; i < (int)tablePlayer.size(); i++)
    {
        list<Player>::iterator it = tablePlayer.at(i).begin();
        while (it != tablePlayer.at(i).end())
        {
            players.push_back(*it);
            advance(it, 1);
        }
    }
    for (int i = 0; i < (int)players.size(); i++)
    {
        insert(root, players.at(i).name, players.at(i).sofifa_id);
    }
    vector<Player>::iterator newIter = remove_if(players.begin(),players.end(),notEnoughReviews);
    players.resize(newIter -  players.begin());
    bSortPlayerVector(players);
}

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
        if (key[i] == '.')
        {
            index = 28;
        }
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->sofifa_id = sofifa_id;
}

void bSortUserRVector(vector<UserRating> &ratings)
{

    int size = (int)ratings.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            if (ratings.at(j).rating < ratings.at(j + 1).rating)
            {
                UserRating temp = ratings.at(j);
                ratings.at(j) = ratings.at(j + 1);
                ratings.at(j + 1) = temp;
            }
        }
    }
}
