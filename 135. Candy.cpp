//Greedy
//TLE
//47 / 48 test cases passed.
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        
        int given = 0;
        vector<int> candies(n);

        int min_ele = *min_element(ratings.begin(), ratings.end());
                
        for(int i = 0; i < ratings.size(); ++i){
            if(ratings[i] == min_ele){
                candies[i] = 1;
                ++given;
            }
        }
        
        // for(const int& candy : candies){
        //     cout << candy << " ";
        // }
        // cout << endl;
        
        while(given < n){
            for(int i = 0; i < n; ++i){
                // cout << "i: " << i << endl;
                
                if(candies[i]) continue;
                
                int candy = 1;
                
                if(i == 0 || ratings[i] <= ratings[i-1]){
                    //don't need to consider left
                    // cout << "a" << endl;
                }else if(candies[i-1] != 0){
                    //it's left child is already given candy
                    candy = max(candy, candies[i-1]+1);
                    // cout << "b" << endl;
                }else{
                    //must wait unitl child i-1 is given candy
                    // cout << "c" << endl;
                    continue;
                }
                
                
                if(i == n-1 || ratings[i] <= ratings[i+1]){
                    //don't need to consider right
                    // cout << "d" << endl;
                }else if(candies[i+1] != 0){
                    //must consider right, and right is given candy
                    candy = max(candy, candies[i+1]+1);
                    // cout << "e" << endl;
                }else{
                    //must consider right, but right is not given candy
                    // cout << "f" << endl;
                    continue;
                }
                
                candies[i] = candy;
                ++given;
            }
        }
        
        // for(const int& candy : candies){
        //     cout << candy << " ";
        // }
        // cout << endl;
        
        return accumulate(candies.begin(), candies.end(), 0);
    }
};

//Approach 1: Brute Force
//TLE
//47 / 48 test cases passed.
//time: O(N^2), space: O(N)
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        
        //give each child one candy at first time
        vector<int> candies(n, 1);
        
        bool stop = false;
        while(!stop){
            stop = true;
            for(int i = 0; i < n; ++i){
                if(i > 0 && ratings[i] > ratings[i-1]){
                    if(candies[i] <= candies[i-1]){
                        stop = false;
                        candies[i] = candies[i-1]+1;
                    }
                }
                if(i < n-1 && ratings[i] > ratings[i+1]){
                    if(candies[i] <= candies[i+1]){
                        stop = false;
                        candies[i] = candies[i+1]+1;
                    }
                }
            }   
        }
        
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
