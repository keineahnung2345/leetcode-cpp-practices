//Runtime: 508 ms, faster than 62.50% of C++ online submissions for People Whose List of Favorite Companies Is Not a Subset of Another List.
//Memory Usage: 38.5 MB, less than 100.00% of C++ online submissions for People Whose List of Favorite Companies Is Not a Subset of Another List.
class Solution {
public:
    template <typename T>
    bool IsSubset(std::vector<T> A, std::vector<T> B)
    {
        std::sort(A.begin(), A.end());
        std::sort(B.begin(), B.end());
        return std::includes(A.begin(), A.end(), B.begin(), B.end());
    }
    
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();
        
        vector<int> ans(n);
        
        iota(ans.begin(), ans.end(), 0);
        
        for(int i = 0; i < n; i++){
            sort(favoriteCompanies[i].begin(), favoriteCompanies[i].end());
        }
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(j == i) continue;
                // cout << "compare " << i << " and " << j << endl;
                if(std::includes(favoriteCompanies[j].begin(), favoriteCompanies[j].end(),
                  favoriteCompanies[i].begin(), favoriteCompanies[i].end())){
                // if(IsSubset(favoriteCompanies[j], favoriteCompanies[i])){
                    // cout << i << " in " << j << endl;
                    auto it = find(ans.begin(), ans.end(), i);
                    if(it != ans.end()){
                        ans.erase(it);
                    }
                    break;
                }
            }
        }
        
        return ans;
    }
};
