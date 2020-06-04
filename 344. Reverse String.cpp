//Two Pointer
//Runtime: 44 ms, faster than 92.88% of C++ online submissions for Reverse String.
//Memory Usage: 23.5 MB, less than 6.10% of C++ online submissions for Reverse String.
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, j = s.size()-1;
        
        while(i < j){
            swap(s[i++], s[j--]);
        }
    }
};
