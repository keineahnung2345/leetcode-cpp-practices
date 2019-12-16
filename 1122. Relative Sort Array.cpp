//Code based on hints:
//Using a hashmap, we can map the values of arr2 to their position in arr2.
//After, we can use a custom sorting function.
//Runtime: 4 ms, faster than 92.33% of C++ online submissions for Relative Sort Array.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Relative Sort Array.

static map<int, int> m;

static bool my_comparator(int a, int b){
    return m[a] < m[b];
}

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int>::iterator it;
        
        for(int e : arr1){
            it = find(arr2.begin(), arr2.end(), e);
            if(it != arr2.end()){
                m[e] = it - arr2.begin();
            }else{
                //the number not in arr2 should be put at last
                //, adding "arr2.size()" so that m[e] is larger than m[x] for all x in arr2
                m[e] = arr2.size() + e;
            }
        }
        
        // for(auto it = m.begin(); it != m.end(); it++){
        //     cout << it->first << " " << it->second << endl;
        // }
        
        sort(arr1.begin(), arr1.end(), my_comparator);
        
        return arr1;
    }
};
