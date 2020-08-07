//WA
//104 / 129 test cases passed.
//[[1,0,0,0,0,0],[0,1,0,1,0,0],[1,0,0,0,0,0],[1,1,1,0,0,0],[1,1,0,1,0,0],[1,0,0,0,0,0]]
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        
        vector<pair<int, int>> maxRight(n);
        
        for(int i = 0; i < n; ++i){
            int j;
            for(j = n-1; j >= 0 && grid[i][j] == 0; --j){}
            maxRight[i] = {n-1-j, i};
        }
        
        /*
        sort descending by count and then ascending by index
        [[1,0,0,0],[1,1,1,1],[1,0,0,0],[1,0,0,0]]
        */
        sort(maxRight.begin(), maxRight.end(),
            [](pair<int,int>& a, pair<int,int>& b){
                return (a.first == b.first) ? a.second < b.second : a.first > b.first;
            });
        for(int i = 0; i < n; ++i){
            if(maxRight[i].first < n-1-i) return -1;
        }
        
        //now we are sure that the answer exist
        int swaps = 0;
        
        for(int i = 0; i < n; ++i){
            swaps += maxRight[i].second - i;
            for(int j = i+1; j < n; ++j){
                if(maxRight[j].second < maxRight[i].second){
                    ++maxRight[j].second;
                }
            }
        }
        
        return swaps;
    }
};

//Greedy
//https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/discuss/768076/Min-Adjacent-Swaps-to-Sort-the-array-of-INTEGERS-with-Proof
//Runtime: 156 ms, faster than 100.00% of C++ online submissions for Minimum Swaps to Arrange a Binary Grid.
//Memory Usage: 25.9 MB, less than 100.00% of C++ online submissions for Minimum Swaps to Arrange a Binary Grid.
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        
        vector<int> maxRight(n);
        
        for(int i = 0; i < n; ++i){
            int j;
            for(j = n-1; j >= 0 && grid[i][j] == 0; --j){}
            maxRight[i] = n-1-j;
        }
        
        //sort descending
        vector<int> tmp = maxRight;
        sort(tmp.rbegin(), tmp.rend());
        for(int i = 0; i < n; ++i){
            if(tmp[i] < n-1-i) return -1;
        }
        
        //now we are sure that the answer exist
        int swaps = 0;
        
        for(int i = 0; i < n; ++i){
            if(maxRight[i] < n-1-i){
                //move some row up
                int j;
                for(j = i+1; j < n && maxRight[j] < n-1-i; ++j){}
                
                //jth row is what we want
                //move jth row to ith row
                //i,i+1,...,j-1,j -> j,i+1,i+2,...,j-1
                int jcount = maxRight[j];
                maxRight.erase(maxRight.begin()+j);
                maxRight.insert(maxRight.begin()+i, jcount);
                swaps += j-i;
            }
        }
        
        return swaps;
    }
};
