#include "search.h"
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
                p = (*it2);
            }
            advance(it2, 1);
        }
        cout << userRatings.at(i).user_id << ":" << userRatings.at(i).sofifa_id << ":" << p.name << ":" << p.reviewTotal / p.reviewCout << ":" << p.reviewCout << ":" << userRatings.at(i).rating << "\n";
    }
}