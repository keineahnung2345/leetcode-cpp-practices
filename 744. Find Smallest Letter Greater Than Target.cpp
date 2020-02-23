//Runtime: 12 ms, faster than 93.52% of C++ online submissions for Find Smallest Letter Greater Than Target.
//Memory Usage: 9 MB, less than 72.73% of C++ online submissions for Find Smallest Letter Greater Than Target.

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        for(char letter : letters){
            if(letter > target){
                return letter;
            }
        }
        return letters[0];
    }
};
