//Runtime: 116 ms, faster than 33.33% of C++ online submissions for Simplified Fractions.
//Memory Usage: 21.9 MB, less than 100.00% of C++ online submissions for Simplified Fractions.
class Solution {
public:
    int gcd(int x, int y){
        if(x < y){
            swap(x, y);
        }
        
        if(y == 0) return x;
        
        return gcd(y, x%y);
    };
    
    vector<string> simplifiedFractions(int n) {
        if(n == 1) return vector<string>();
        
        vector<string> ans;
        
        for(int nom = 1; nom < n; nom++){
            for(int denom = max(2, nom); denom <= n; denom++){
                // cout << nom << "/" << denom <<": " << gcd(denom, nom) << endl;
                if(gcd(denom, nom) != 1){
                    continue;
                }
                ans.push_back(to_string(nom) + "/" + to_string(denom));
            }
        }
        
        return ans;
    }
};

//use built-in __gcd(), change the order of loop
//Runtime: 108 ms, faster than 66.67% of C++ online submissions for Simplified Fractions.
//Memory Usage: 21.8 MB, less than 100.00% of C++ online submissions for Simplified Fractions.
class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        if(n == 1) return vector<string>();
        
        vector<string> ans;
        
        for(int denom = 2; denom <= n; denom++){
            for(int nom = 1; nom < denom; nom++){
                // cout << nom << "/" << denom <<": " << gcd(denom, nom) << endl;
                if(__gcd(denom, nom) != 1){
                    continue;
                }
                ans.push_back(to_string(nom) + "/" + to_string(denom));
            }
        }
        
        return ans;
    }
};
