//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Long Pressed Name.
//Memory Usage: 8.4 MB, less than 98.25% of C++ online submissions for Long Pressed Name.

class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int cur = 0;
        char last = typed[0];
        
        for(char c : name){
            char typedc = typed[cur++];
            //ignore the redundant char
            while(typedc != c && typedc == last){
                typedc = typed[cur++];
            }
            // cout << c << " " << typedc << " " << last << endl;
            //if(typedc != c && typedc != last), then it must be wrong
            if(typedc != c && typedc != last) return false;
            //if(typedc == c), it matches
            last = typedc;
        }
        return true;
    }
};
