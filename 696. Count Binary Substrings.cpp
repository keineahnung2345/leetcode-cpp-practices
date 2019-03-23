/**
Give a string s, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
Example 2:
Input: "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
Note:

s.length will be between 1 and 50,000.
s will only consist of "0" or "1" characters.
**/

//Runtime: 1752 ms, faster than 5.41% of C++ online submissions for Count Binary Substrings.
//Memory Usage: 13.1 MB, less than 94.03% of C++ online submissions for Count Binary Substrings.
class Solution {
public:
    int countBinarySubstrings(string s) {
        int count = 0;
        
        for(int i = 0; i < s.size(); i++){
            int latterHead = i+1;
            for(;latterHead < s.size();latterHead++){
                if(s[latterHead]!=s[i]) break;
            }
            //the latter part's length won't match the former part's
            //latterHead-i: former part's length
            //s.size()-1-(latterHead-1): the remaining length
            if(s.size()-1-(latterHead-1) < latterHead-i) continue;
            bool legal = true;
            int latterTail = latterHead;
            for(;latterTail<=latterHead-1+latterHead-i;latterTail++){
                if(s[i]==s[latterTail]){
                    legal = false;
                    break;
                }
            }
            if(legal){
                //latterHead - i: former part's length
                //Method 1(TLE)
                count+=1;
                
                //Method 2(Accepted)
                //length x former part implies x legal substrings
                //record the substring and skip them
                count+=(latterHead-i);
                i+=(latterHead-i-1);
                
                // cout << i << " " << latterTail << endl;
            }
        }
        
        return count;
    }
};
