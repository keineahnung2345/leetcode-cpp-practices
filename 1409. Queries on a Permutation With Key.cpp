//Runtime: 20 ms, faster than 80.24% of C++ online submissions for Queries on a Permutation With Key.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Queries on a Permutation With Key.
class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> P(m);
        iota(P.begin(), P.end(), 1);
        
        vector<int> ans;
        
        for(int q : queries){
            int ix = find(P.begin(), P.end(), q) - P.begin();
            int toMove = P[ix];
            ans.push_back(ix);
            P.erase(P.begin()+ix);
            P.insert(P.begin(), toMove);
        }
        
        return ans;
    }
};
