//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Max Difference You Can Get From Changing an Integer.
//Memory Usage: 6.1 MB, less than 100.00% of C++ online submissions for Max Difference You Can Get From Changing an Integer.
class Solution {
public:
    void replace(string& s, char toReplace, char newText){
        size_t pos = 0;
        while((pos = s.find(toReplace, pos)) != std::string::npos){
            s.replace(pos, 1, 1, newText);
        }
    };
    
    int maxDiff(int num) {
        string s = to_string(num);
        int n = s.size();
        
        int i = 0;
        while(i < n && s[i] == '9'){
            i++;
        }
        string sa = s;
        if(i != n) replace(sa, sa[i], '9');
        
        string sb = s;
        if(s[0] != '1'){
            replace(sb, sb[0], '1');
        }else{
            i = 1;
            while(i < n && (s[i] == '1' || s[i] == '0')){
                i++;
            }
            if(i != n){
                replace(sb, sb[i], '0');
            }
        }
        
        // cout << sa << " " << sb << endl;
        
        int a = stoi(sa), b = stoi(sb);
        
        return a - b;
    }
};
