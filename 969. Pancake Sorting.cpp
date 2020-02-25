//Approach 1: Sort Largest to Smallest
//Runtime: 8 ms, faster than 69.75% of C++ online submissions for Pancake Sorting.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Pancake Sorting.
class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        vector<int> ans;
        
        //skip curmax = 1 because 1 must be in correct place 
        // when all other elements all in correct place
        for(int curmax = A.size(); curmax >= 2; curmax--){
            int index = find(A.begin(), A.end(), curmax) - A.begin();
            //make index 1-based
            index += 1;
            // cout << curmax << ", " << index << endl;
            
            if(index > 1){
                //"last" is exclusive, so A[0], ..., A[index-1]
                reverse(A.begin(), A.begin() + index);
                // copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
                // cout << endl;
                ans.push_back(index);
            }
            
            if(curmax > 1){
                //A[0], ..., A[curmax-1]
                reverse(A.begin(), A.begin() + curmax);
                // copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
                // cout << endl;
                ans.push_back(curmax);
            }
            
        }
        
        return ans;
    }
};

//without actually flipping
//official solution
//time: O(N^2), space: O(N)
//Runtime: 8 ms, faster than 69.75% of C++ online submissions for Pancake Sorting.
//Memory Usage: 8.8 MB, less than 83.33% of C++ online submissions for Pancake Sorting.
class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        vector<int> ans;
        int N = A.size();
        
        vector<int> indices(N);
        iota(indices.begin(), indices.end(), 1);
        //the larget the former
        sort(indices.begin(), indices.end(), 
             [&A](const int i, const int j){return A[i-1] > A[j-1];});
        // copy(indices.begin(), indices.end(), ostream_iterator<int>(cout, " "));
        // cout << endl;
        
        for(int index : indices){
            //don't actually reverse the vector, but simulate it
            // cout << index << "->";
            for(int flip : ans){
                if(index <= flip){
                    //flip at flip'th position, so index'th position is affected
                    //old position + new position = flipped vector's size + 1
                    index = flip + 1 - index;
                }
            }
            // cout << index << endl;
            //now index becomes the true index after serveral flipping
            ans.push_back(index);
            ans.push_back(N--);
        }
        
        return ans;
    }
};
