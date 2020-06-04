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

//one variable
//Runtime: 56 ms, faster than 53.92% of C++ online submissions for Reverse String.
//Memory Usage: 23.3 MB, less than 6.10% of C++ online submissions for Reverse String.
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, n = s.size();
        
        while(i < n/2){
            swap(s[i], s[n-1-i]);
            i++;
        }
    }
};
