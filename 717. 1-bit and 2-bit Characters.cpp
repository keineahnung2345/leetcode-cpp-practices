//Runtime: 0 ms, faster than 100.00% of C++ online submissions for 1-bit and 2-bit Characters.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for 1-bit and 2-bit Characters.

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        //if there are two or more "0" in the vector, 
        //all bits before(including) the 2nd last "0" can be ignored
        vector<int> zero = {0};
        vector<int>::iterator it = find_end(bits.begin(), bits.end()-1, zero.begin(), zero.end());
        
        //if there are two or more "0"
        if(it != bits.end()-1){
            cout << bits.end() - it - 1 << endl;
            //bits.end() - it: the length from 2nd last "0"
            //bits.end() - it - 1: the length from the next bit of 2nd last "0"
            //if the remaining string's length is odd, 
            //that means there will be a "0" not paired to other bits
            return (bits.end() - it - 1)%2 != 0;
        }
        
        return bits.size()%2 != 0;
    }
};
