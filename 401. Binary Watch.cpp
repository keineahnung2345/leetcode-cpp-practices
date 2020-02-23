//Runtime: 4 ms, faster than 62.95% of C++ online submissions for Binary Watch.
//Memory Usage: 9.2 MB, less than 28.57% of C++ online submissions for Binary Watch.
class Solution {
public:
    void combUtil(vector<int>& arr, vector<int>& comb, vector<vector<int>>& combs, int start, int end, int index, int r){
        if(index == r){
            combs.push_back(comb);
            return;
        }
        for(int i = start; i <= end && end - i + 1 >= r - index; i++){
            comb[index] = arr[i];
            combUtil(arr, comb, combs, i+1, end, index+1, r);
        }
    }
        
    void getComb(vector<int>& arr, vector<vector<int>>& combs, int n, int r){
        vector<int> comb(r);
        combUtil(arr, comb, combs, 0, n-1, 0, r);
    }
    
    vector<string> readBinaryWatch(int num) {
        vector<int> choices = {1, 2, 4, 8, //hours
                             1, 2, 4, 8, 16, 32}; //minutes
        vector<int> indices(choices.size());
        iota(indices.begin(), indices.end(), 0);
        
        vector<vector<int>> combs;
        vector<string> ans;
        
        getComb(indices, combs, indices.size(), num);
        
        for(vector<int>& comb : combs){
            int hour = 0, minute = 0;
            for(int index : comb){
                if(index < 4){
                    hour += choices[index];
                }else{
                    minute += choices[index];
                }
            }
            if(hour <= 11 && minute <= 59){
                std::ostringstream ss;
                ss << hour << ":" << std::setw(2) << std::setfill('0') << minute;
                ans.push_back(ss.str());
            }
        }
        
        return ans;
    }
};
