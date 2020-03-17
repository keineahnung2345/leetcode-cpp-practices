//Runtime: 240 ms, faster than 24.78% of C++ online submissions for Find K Pairs with Smallest Sums.
//Memory Usage: 84.3 MB, less than 20.00% of C++ online submissions for Find K Pairs with Smallest Sums.
class pairSumGreater{
public:
    pairSumGreater(){};
    bool operator() (const vector<int>& a, const vector<int>& b){
        return a[0] + a[1] > b[0] + b[1];
    };
};

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        priority_queue<vector<int>, vector<vector<int>>, pairSumGreater> pq;
        for(int i = 0; i < nums1.size(); i++){
            for(int j = 0; j< nums2.size(); j++){
                pq.push({nums1[i], nums2[j]});
            }
        }
        
        vector<vector<int>> ans;
        while(k-- > 0 && !pq.empty()){
            ans.push_back(pq.top());
            pq.pop();
        }
        
        return ans;
    }
};
