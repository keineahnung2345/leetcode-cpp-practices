//Runtime: 8 ms, faster than 66.67% of C++ online submissions for Most Visited Sector in a Circular Track.
//Memory Usage: 11.4 MB, less than 50.00% of C++ online submissions for Most Visited Sector in a Circular Track.
class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        //0 for padding
        vector<int> counter(n+1, 0);
        
        ++counter[rounds[0]];
        
        for(int i = 1; i < rounds.size(); ++i){
            int start = rounds[i-1]+1;
            int end = rounds[i];
            if(end >= start){
                for(int p = start; p <= end; ++p){
                    ++counter[p];
                }
            }else{
                for(int p = start; p <= n; ++p){
                    ++counter[p];
                }
                for(int p = 1; p <= end; ++p){
                    ++counter[p];
                }
            }
            
        }
        
        // for(int i = 1; i <= n; ++i){
        //     cout << i << " : " << counter[i] << endl;
        // }
        
        int max_count = *max_element(counter.begin(), counter.end());
        
        vector<int> ans;
        
        for(int i = 1; i <= n; ++i){
            if(counter[i] == max_count){
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};
