//either Time Limit Exceeded or Memory Limit Exceeded
//69 / 72 test cases passed.
class Solution {
public:
    string longestPrefix(string s) {
        int N = s.size();
        int SEGMENT = 10000;
        
        //l starts from N-1(substring cannot be itself)
        for(int l = N-1; l >= 1; l--){
            // cout << l << endl;
            // string prefix = s.substr(0, l);
            // string suffix = s.substr(N-l);

            // bool same = true;
            // for(int i = 0; i < prefix.size(); i++){
            //     if(prefix[i] != suffix[i]){
            //         same = false;
            //         break;
            //     }
            // }
            // if(same){
            //     return prefix;
            // }
            // if(prefix == suffix){
            //     return prefix;
            // }
            
            
            bool same = true;
            for(int i = 0; i <= l/SEGMENT; i++){
                //partPrefix could exceed the boundary
                string partPrefix = s.substr(0+i*SEGMENT, SEGMENT);
                string partSuffix = s.substr(N-l+i*SEGMENT, SEGMENT);
                //partPrefix could exceed the boundary
                if(partPrefix.size() != partSuffix.size()){
                    partPrefix = partPrefix.substr(0, partSuffix.size());
                }
                
                for(int i = 0; i < partPrefix.size(); i++){
                    if(partPrefix[i] != partSuffix[i]){
                        same = false;
                        break;
                    }
                }
                
                if(same == false){
                    break;
                }
                
                // if(partPrefix != partSuffix){
                //     same = false;
                //     break;
                // }
            }

            if(same){
                return s.substr(0, l);
            }
        }
        
        return "";
    }
};

//KMP
//Runtime: 48 ms, faster than 28.57% of C++ online submissions for Longest Happy Prefix.
//Memory Usage: 19 MB, less than 100.00% of C++ online submissions for Longest Happy Prefix.
class Solution {
public:
    vector<int> preprocess(string& pattern){
        int n = pattern.size();
        vector<int> lps(n, 0);
        
        for(int i = 1, len = 0; i < n; ){
            if(pattern[i] == pattern[len]){
                len++;
                lps[i] = len;
                i++;
            }else if(len > 0){
                len = lps[len-1];
            }else{
                i++;
            }
        }
        
        return lps;
    };
    
    string longestPrefix(string s) {
        vector<int> lps = preprocess(s);
        // for(int e : lps){
        //     cout << e;
        // }
        // cout << endl;
        
        // int length = *max_element(lps.begin(), lps.end());
        int length = lps[lps.size()-1];
        return s.substr(0, length);
    }
};
