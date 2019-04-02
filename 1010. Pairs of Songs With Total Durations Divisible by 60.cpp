//Runtime: 52 ms, faster than 25.88% of C++ online submissions for Pairs of Songs With Total Durations Divisible by 60.
//Memory Usage: 11.9 MB, less than 100.00% of C++ online submissions for Pairs of Songs With Total Durations Divisible by 60.

class Solution {
public:
    int combCount(int n){
        return n*(n-1)/2;
    }
    
    int numPairsDivisibleBy60(vector<int>& time) {
        map<int, int> count;
        vector<int> key; //keys of count
        
        for(int e : time){
            e = e%60;
            if(count.find(e) != count.end()){
                count[e]++;
            }else{
                count[e] = 1;
                key.push_back(e);
            }
        }
        
        sort(key.begin(), key.end());
        
        // for(int k : key){
        //     cout << k << ", " << count[k] << endl;
        // }
        
        int ans = 0;
        
        //0 satisfy the condition itself
        if(find(key.begin(), key.end(), 0) != key.end()) ans+=combCount(count[0]);
        
        //for the rest, we need the sum of two elements
        int s = 0, f = key.size()-1;
        while(s <= f){
            int k1 = key[s], k2 = key[f];
            //0 has already been considered
            if(k1 == 0){
                s++;
                continue;
            }
            if((k1 + k2)%60 == 0){
                if(k1 != k2){
                    // cout << k1 << ", " << k2 << ", " << count[k1] * count[k2] << endl;
                    ans += count[k1] * count[k2];
                }else{
                    ans += combCount(count[k1]);
                    // cout << k1 << ", " << combCount(count[k1]) << endl;
                }
                s++;
                f--;
            }else if(k1 + k2 < 60){
                s++;
            }else{
                f--;
            }
        }
        
        return ans;
    }
};

//TLE
/**
class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int ans = 0;
        for(int i = 0; i < time.size() - 1; i++){
            for(int j = i + 1; j < time.size(); j++){
                if((time[i] + time[j])%60 == 0) ans++;
            }
        }
        return ans;
    }
};
**/

/**
https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/discuss/256738/JavaC%2B%2BPython-Two-Sum-with-K-60
**/

//Runtime: 36 ms, faster than 98.34% of C++ online submissions for Pairs of Songs With Total Durations Divisible by 60.
//Memory Usage: 11.7 MB, less than 100.00% of C++ online submissions for Pairs of Songs With Total Durations Divisible by 60.

/**
class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int ans = 0;
        vector<int> count(60);
        
        for(int t : time){
            //(60-t%60): in 1 ~ 60
            //(60-t%60)%60: in 0 ~ 59
            //every time check that how many elements can form a pair with current element
            //and we update "count" while iterating "time"
            //this avoid duplicate count
            ans += count[(60-t%60)%60];
            count[t%60]++;
        }
        return ans;
    }
};
**/
