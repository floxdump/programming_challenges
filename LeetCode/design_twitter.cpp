/*
 * Solution for the `355. Design Twitter` problem from the site LeetCode.
 */

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

class Twitter
{
public:
    Twitter()
    : current_time{0}
    {}
    
    // Compose a new tweet.
    void postTweet(int userId, int tweetId)
    {
        // First tweet of userId. We should follow oneself 
        if (tweets.find(userId) == tweets.end())
        {
            follow(userId, userId);
        }
        ++current_time;
        //tweets[userId].push_back(std::make_pair(tweetId, current_time));
        tweets[userId].emplace_back(tweetId, current_time);
    }
    
    // Retrieve the 10 most recent tweet ids in the user's news feed.
    // Each item in the news feed must be posted by users who the user 
    // followed or by the user herself. Tweets must be ordered from 
    // most recent to least recent.
    std::vector<int> getNewsFeed(int userId)
    {
        auto timestamp_comparator = [](const Tweet& t1, const Tweet& t2)
        {
            return (t1.second < t2.second);
        };
        std::priority_queue<Tweet, std::vector<Tweet>, decltype(timestamp_comparator)> tweets_queue(timestamp_comparator);

        // put friend's tweets
        auto users = friends.find(userId);
        if (users != friends.end())
        {
            // iterate over friends and looking for their tweets
            for(auto const& current_friend: users->second)
            {
                auto current_friend_tweets = tweets.find(current_friend);
                if (current_friend_tweets != tweets.end())
                {
                    for(auto& tweet: current_friend_tweets->second)
                    {
                      tweets_queue.push(tweet);
                    }
                }
            }
        }
        std::vector<int> res;
        short tweet_counter = 0;
        while (tweet_counter < NEWS_FEED_LIMIT && !tweets_queue.empty())
        {
          auto item = tweets_queue.top();
          res.push_back(item.first);
          tweets_queue.pop();
          ++tweet_counter;
        }
        return res;        
    }
    
    // Follower follows a followee.
    // If the operation is invalid, it should be a no-op.
    void follow(int followerId, int followeeId)
    {
        friends[followerId].insert(followeeId);
    }
    
    // Follower unfollows a followee.
    // If the operation is invalid, it should be a no-op.
    void unfollow(int followerId, int followeeId)
    {
        if (followerId != followeeId)
        {
            friends[followerId].erase(followeeId);
        }
    }
private:
    const int NEWS_FEED_LIMIT = 10;
    typedef unsigned long long int Time;
    // tuple for storing tweet info <id, timestamp>
    typedef std::pair<int, Time> Tweet;
    // hash table for storing all tweets
    std::unordered_map<int, std::vector<Tweet>> tweets;
    // hash table for storing friends information
    std::unordered_map<int, std::unordered_set<int>> friends;
    Time current_time;    
};

int main()
{
    // Example of using Twitter class
    Twitter twitter;
    twitter.postTweet(1, 11);
    twitter.postTweet(1, 12);
    twitter.postTweet(1, 13);
    twitter.postTweet(1, 14);
    twitter.unfollow(1, 1);

    for (auto const& tweet: twitter.getNewsFeed(1))
    {
      std::cout << tweet << " ";
    }
    std::cout << std::endl;

    twitter.postTweet(2, 21);
    twitter.postTweet(2, 22);
    twitter.postTweet(1, 15);
    twitter.postTweet(2, 23);
    twitter.follow(1, 2);
    twitter.postTweet(1, 16);
    twitter.postTweet(3, 31);
    twitter.postTweet(1, 17);
    twitter.postTweet(1, 18);
    twitter.postTweet(1, 19);
    twitter.postTweet(3, 32);
    twitter.postTweet(1, 110);
    twitter.postTweet(2, 24);
    twitter.postTweet(1, 111);

    for (auto const& tweet: twitter.getNewsFeed(1))
    {
      std::cout << tweet << " ";
    }    
    std::cout << std::endl;

    twitter.unfollow(1, 2);
    for (auto const& tweet: twitter.getNewsFeed(1))
    {
      std::cout << tweet << " ";
    }    
    std::cout << std::endl;

    twitter.follow(1, 3);
    twitter.postTweet(3, 33);
    twitter.postTweet(2, 25);
    twitter.postTweet(2, 26);
    for (auto const& tweet: twitter.getNewsFeed(1))
    {
      std::cout << tweet << " ";
    }    
    std::cout << std::endl;

    return 0;
}
