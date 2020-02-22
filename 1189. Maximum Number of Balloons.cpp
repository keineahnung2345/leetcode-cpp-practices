//Runtime: 4 ms, faster than 92.10% of C++ online submissions for Maximum Number of Balloons.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Maximum Number of Balloons.

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        map<char, int> m;
        
        for(char& c : text){
            m[c]++;
        }
        
        return min({m['b'], m['a'], m['l']/2, m['o']/2, m['n']});
    }
};
