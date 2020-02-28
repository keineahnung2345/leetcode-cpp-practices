//Runtime: 8 ms, faster than 77.55% of C++ online submissions for Check If N and Its Double Exist.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Check If N and Its Double Exist.
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        for(int i = 0; i < arr.size(); i++){
            auto it = find(arr.begin(), arr.end(), arr[i]*2);
            if(it != arr.end() && it != arr.begin()+i){
                return true;
            }
        }
        return false;
    }
};
