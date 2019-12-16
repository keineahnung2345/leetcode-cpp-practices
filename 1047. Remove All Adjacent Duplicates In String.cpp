//Runtime: 44 ms, faster than 28.17% of C++ online submissions for Remove All Adjacent Duplicates In String.
//Memory Usage: 11.5 MB, less than 100.00% of C++ online submissions for Remove All Adjacent Duplicates In String.

class Solution {
public:
    string removeDuplicates(string S) {
        int nRemoved = 0;
        
        do{
            nRemoved = 0;
            for(int i = 0; i < S.size() - 1;){
                if(S[i] == S[i+1]){
                    //remove from i, length 2
                    // cout << S.size() << ", " << i << endl;
                    S.erase(i, 2);
                    i--;
                    nRemoved++;
                }else{
                    i++;
                }
            }
        }while(nRemoved > 0 && S.size() > 0);
        
        return S;
    }
};

//Two pointer:
//https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/discuss/294893/JavaC%2B%2BPython-Two-Pointers-and-Stack-Solution
//Runtime: 20 ms, faster than 82.26% of C++ online submissions for Remove All Adjacent Duplicates In String.
//Memory Usage: 11.8 MB, less than 100.00% of C++ online submissions for Remove All Adjacent Duplicates In String.

class Solution {
public:
    string removeDuplicates(string S) {
        int isrc, idst;
        for(isrc = 0, idst = 0; isrc < S.size(); isrc++, idst++){
            S[idst] = S[isrc];
            if(idst > 0 && S[idst] == S[idst-1]){
                idst -= 2;
            }
        }
        return S.substr(0, idst);
    }
};

//Stack
//https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/discuss/294893/JavaC%2B%2BPython-Two-Pointers-and-Stack-Solution
//Runtime: 16 ms, faster than 90.84% of C++ online submissions for Remove All Adjacent Duplicates In String.
//Memory Usage: 12.6 MB, less than 100.00% of C++ online submissions for Remove All Adjacent Duplicates In String.

class Solution {
public:
    string removeDuplicates(string S) {
        string ans = "";
        for(char c : S){
            if(ans.size() > 0 && c == ans.back()){
                ans.pop_back();
            }else{
                ans.push_back(c);
            }
        }
        return ans;
    }
};
