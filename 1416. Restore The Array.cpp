//TLE
//25 / 83 test cases passed.
class Solution {
public:
    int k;
    
    bool check(string& s, int idx){
        if(idx != 0){
            //reserve this case when "s" is at the front of the comb it belongs to
            //leading 0
            if(s.size() > 1 && s[0] == '0') return false;
        }
        
        //too large
        if(s.size() > 10 || (s.size() == 10 && s[0] != '1')) return false;
        
        if(idx != 0){
            if(stoi(s) >=1 && stoi(s) <= k){
                return true;
            }
        }else{
            //reserve the case when s is '0'
            if(stoi(s) <= k){
                return true;
            }
        }
        return false;
    };
    
    bool check(vector<string>& v){
        for(int i = 0; i < v.size(); i++){
            if(!check(v[i], i)) return false;
        }
        return true;
    };
    
    int numberOfArrays(string s, int k) {
        int n = s.size();
        this->k = k;
        
        vector<int> dp(n, 0);
        
        vector<vector<string>> combs, nextCombs;
        vector<string> comb;
        
        for(int i = n-1; i >= 0; i--){
            if(combs.size() == 0){
                //haven't found valid comb yet
                comb.clear();
                comb.push_back(s.substr(i));
                if(check(comb)){
                    combs.push_back(comb);
                }
            }else{
                //prefix current char to previous comb
                // cout << "before: " << endl;
                // for(vector<string> comb : combs){
                //     for(string& s : comb){
                //         cout << s << "/";
                //     }
                //     cout << " ";
                // }
                // cout << endl;
                for(vector<string> comb : combs){
                    //isolated token
                    vector<string> comb2 = comb;
                    comb2.insert(comb2.begin(), string(1, s[i]));
                    if(check(comb2)){
                        nextCombs.push_back(comb2);
                    }
                    //merge with first token in "combs[i]"
                    comb[0] = string(1, s[i]) + comb[0];
                    if(check(comb)){
                        nextCombs.push_back(comb);
                    }
                    // for(string& s : comb){
                    //     cout << s << "/";
                    // }
                    // cout << " ";
                    // for(string& s : comb2){
                    //     cout << s << "/";
                    // }
                    // cout << " ";
                }
                // cout << endl;
                combs = nextCombs;
                nextCombs.clear();
            }
        }
        
        // for(int i = 0; i < combs.size(); i++){
        //     for(string& s : combs[i]){
        //         cout << s << "/";
        //     }
        //     cout << " ";
        // }
        // cout << endl;
        
        return combs.size();
    }
};
