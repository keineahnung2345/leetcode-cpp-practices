class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int shiftRightVal = 0;
        for(vector<int>& p : shift){
            shiftRightVal += p[1] * ((p[0] == 0) ? -1 : 1);
        }
        
        if(shiftRightVal == 0){
            return s;
        }
        
        string ans = "";
        
        if(shiftRightVal > 0){
            shiftRightVal = shiftRightVal % s.size();
            ans = s.substr(s.size()-shiftRightVal) + s.substr(0, s.size()-shiftRightVal);
        }else{
            int shiftLeftVal = -shiftRightVal;
            shiftLeftVal = shiftLeftVal % s.size();
            ans = s.substr(shiftLeftVal) + s.substr(0, shiftLeftVal);
        }
        
        return ans;
    }
};
