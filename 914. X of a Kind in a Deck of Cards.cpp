//GCD
//time: O(N*log^2(N)), gcd's time complexity: O(log^2(N))
//space: O(N)
//Runtime: 16 ms, faster than 98.24% of C++ online submissions for X of a Kind in a Deck of Cards.
//Memory Usage: 9.8 MB, less than 100.00% of C++ online submissions for X of a Kind in a Deck of Cards.

class Solution {
public:
    int gcd(int a, int b){
        int tmp;
        if(a < b){
            tmp = a;
            a = b;
            b = tmp;
        }
        if(b == 0)return a;
        return gcd(b, a%b);
    }
    
    bool hasGroupsSizeX(vector<int>& deck) {
        if(deck.size() < 2) return false;
        map<int, int> count;
        for(int e : deck){
            count[e]++;
        }
        
        int g = 0;
        for(map<int, int>::iterator it = count.begin(); it != count.end(); it++){
            g = gcd(g, it->second);
        }
        
        if(g >= 2) return true;
        return false;
    }
};
