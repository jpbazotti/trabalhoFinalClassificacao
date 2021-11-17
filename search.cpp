#include "search.h"
void printHeader(vector<string> fields, vector<int> fieldSizes)
{
    int size=0;
    for(int i = 0; i < (int)fieldSizes.size(); i++){
        size+=(int)(fieldSizes.at(i)) + 1;
    }
    size++;
    for (int i = 0; i < size; i++)
    {
        cout << "-";
    }
    cout << "\n|";
    for (int i = 0; i < (int)fields.size(); i++)
    {
        for (int j = 0; j < (int)(fieldSizes.at(i) - fields.at(i).size()); j++)
        {
            cout << " ";
        }
        cout << fields.at(i) << "|";
    }
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << "-";
    }
    cout<<"\n";
}
void printTable(vector<string> fields, vector<int> fieldSizes)
{
    
    int size=0;
    for(int i = 0; i < (int)fieldSizes.size(); i++){
        size+=(int)(fieldSizes.at(i)) + 1;
    }
    size++;
    cout << "|";

    for (int i = 0; i < (int)fields.size(); i++)
    {
        for (int j = 0; j < (int)(fieldSizes.at(i) - fields.at(i).size()); j++)
        {
            cout << " ";
        }
        if(fields.at(i)=="nan"){
        cout << "  0" << "|";

        }
        else{
        cout << fields.at(i) << "|";
        }
    }
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << "-";
    }
    cout<<"\n";
}
void print_nodes(struct TrieNode *node, string substring, vector<int> &list_id)
{
    int i;
    char c;

    if (node->sofifa_id != 0)
    {
        list_id.push_back(node->sofifa_id);
        return;
    }
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            c = i + 'a';
            if (i == 26)
            {
                c = ' ';
            }
            if (i == 27)
            {
                c = '-';
            }
            if (i == 28)
            {
                c = '.';
            }
            //cout << substring << "\n";
            //getchar();
            print_nodes(node->children[i], substring += c, list_id);
            substring.resize(substring.size() - 1);
        }
    }
    return;
}
int searchTrie(struct TrieNode *root, string key, vector<int> &list_id)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < (int)key.length(); i++)
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
            return 0;

        pCrawl = pCrawl->children[index];
    }

    print_nodes(pCrawl, key, list_id);

    return 0;
}
void PrefixSearch(vector<list<Player>> tablePlayer, string prefix, struct TrieNode *root)
{
    vector<int> list_id(0, 100000);
    vector<int> fieldSizes={9,40,18,10,10};
    vector<string> fields={"sofifa_id","name","player_positions","rating","count"};
    searchTrie(root, prefix, list_id);
    printHeader(fields,fieldSizes);
    for (int i = 0; i < (int)list_id.size(); i++)
    {
        int hash = list_id.at(i) % tablePlayer.size();
        list<Player>::iterator it = tablePlayer.at(hash).begin();
        while (it != tablePlayer.at(hash).end())
        {
            if ((*it).sofifa_id == list_id.at(i))
            {
                vector<string> playerToString={to_string((*it).sofifa_id),(*it).name,(*it).position,to_string((*it).reviewTotal/(*it).reviewCout),to_string((*it).reviewCout)};
                printTable(playerToString,fieldSizes);
                break;
            }
            advance(it, 1);
        }
    }
}
void userSearch(vector<list<UserRating>> &tableReviews, vector<list<Player>> &tablePlayer, int userID)
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
    bSortUserRVector(userRatings);
    vector<int> fieldSizes={9,40,10,10,10};
    vector<string> fields={"sofifa_id","name","rating","count","rating"};
    printHeader(fields,fieldSizes);
    for (int i = 0; i < (int)userRatings.size(); i++)
    {
        player p;
        int indexPlayer = userRatings.at(i).sofifa_id % tablePlayer.size();
        list<player>::iterator it2 = tablePlayer.at(indexPlayer).begin();
        while (it2 != tablePlayer.at(indexPlayer).end())
        {
            if ((*it2).sofifa_id == userRatings.at(i).sofifa_id)
            {
                p = (*it2);
            }
            advance(it2, 1);
        }
        vector<string> playerToString={to_string(p.sofifa_id),p.name,to_string(p.reviewTotal/p.reviewCout),to_string(p.reviewCout), to_string(userRatings.at(i).rating)};
        printTable(playerToString,fieldSizes);
    }
}

vector<string> positionSeparator(string positions){
      positions.erase(remove(positions.begin(), positions.end(), ','), positions.end());
      vector<string> v;
      string aux="";
      for(int i;i < (int)positions.length();i++){
          if(positions.at(i)==' '){
              v.push_back(aux);
              aux="";
          }else{
              aux+=positions.at(i);
          }
      }
      v.push_back(aux);
      return(v);
}

void topPositionSearch(vector<Player> players,int topx,string pos){
    vector<int> fieldSizes={9,40,18,10,10};
    vector<string> fields={"sofifa_id","name","player_positions","rating","count"};
    printHeader(fields,fieldSizes);
    int printed=0;
    for(int i = 0;(i<(int)players.size())&&(printed<topx);i++){
        if(players.at(i).position.find(pos)!= string::npos){
            vector<string> playerToString={to_string(players.at(i).sofifa_id),players.at(i).name,players.at(i).position,to_string(players.at(i).reviewTotal/players.at(i).reviewCout),to_string(players.at(i).reviewCout)};
            printTable(playerToString,fieldSizes);
            printed++;
        }
    }
}
void bsort(vector<int> &n){

    int size = (int)n.size();
    for(int i =0;i<size;i++){
        for(int j=0;j<(size -i -1);j++){
            if(n.at(j) > n.at(j+1)){
                int temp = n.at(j);
                n.at(j)=n.at(j+1);
                n.at(j+1)=temp;
            }
        }
    }
}

vector<int> intersection(vector<int> &v1,vector<int> &v2){
    vector<int> v3;
    bsort(v1);
    bsort(v2);
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    return v3;
}