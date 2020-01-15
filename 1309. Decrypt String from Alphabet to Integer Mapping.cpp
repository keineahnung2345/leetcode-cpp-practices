//Runtime: 4 ms, faster than 63.30% of C++ online submissions for Decrypt String from Alphabet to Integer Mapping.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Decrypt String from Alphabet to Integer Mapping.

class Solution {
public:
    string freqAlphabets(string s) {
        int cursor = 0;
        string ans;
        
        while(cursor < s.size()){
            if(s.find('#', cursor) - cursor != 2){
                // -1 because 'a' maps to 1
                ans += ('a' + (s[cursor] - '0' - 1));
                // cout << cursor << ", " << (char)('a' + (s[cursor] - '0')) << endl;
                cursor++;
            }else{
                // -1 because 'a' maps to 1
                ans += ('a' + stoi(s.substr(cursor, 2)) - 1);
                // cout << cursor << ", " << (char)('a' + stoi(s.substr(cursor, 2))) << endl;
                cursor+=3;
            }
        }
        
        return ans;
    }
};
