//Runtime: 184 ms, faster than 97.89% of C++ online submissions for Rank Transform of an Array.
//Memory Usage: 18.1 MB, less than 100.00% of C++ online submissions for Rank Transform of an Array.

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        if(arr.size() == 0) return vector<int>();
        vector<int> indices(arr.size()), ans(arr.size());
        iota(indices.begin(), indices.end(), 0);
        
        //the index(1-based) from small to large
        sort(indices.begin(), indices.end(), 
            [&arr](const int a, const int b){
                return arr[a] < arr[b];
            });
        
        // copy(indices.begin(), indices.end(), ostream_iterator<int>(cout, " "));
        // cout << endl;
        
        int index = indices[0], last_index;
        int rank = 1;
        ans[index] = rank;
        
        //indices: sort by their corresponding value in arr
        for(int i = 1; i < indices.size(); i++){
            index = indices[i];
            last_index = indices[i-1];
            // cout << index << ", " << last_index << endl;
            //increase rank only when their corresponding values are different
            if(arr[index] != arr[last_index]) rank++;
            ans[index] = rank;
        }
        
        return ans;
    }
};
