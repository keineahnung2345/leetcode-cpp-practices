//Runtime: 312 ms, faster than 20.09% of C++ online submissions for Minimum Number of Frogs Croaking.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Minimum Number of Frogs Croaking.
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        int pos = -2; //represents for meaningless value
        int visited = 0;
        int count = 0;
        
        vector<string> croak = {"c", "r", "o", "a", "k"};
        
        while(visited < croakOfFrogs.size()){
            pos = -2;
            bool jump = false; //whether to jump from inner loop
            while(pos == -2 || (pos >= 0 && pos < croakOfFrogs.size())){
                for(string s : croak){
                    pos = croakOfFrogs.find(s, (pos == -2) ? 0 : pos+1);
                    if(pos != string::npos){
                        //revise the char in-place, so the char won't be visited again
                        croakOfFrogs[pos] = '#';
                        visited++;
                    }else{
                        /*
                        not jump at first char, invalid string,
                        for example, we have found 'c', 'r', 'o',
                        but we cannot find 'a', it must be invalid string
                        */
                        if(s != "c") return -1;
                        //we need another frog
                        jump = true;
                        break;
                    }
                }
                if(jump) break;
            }
            
            //we have used one frog
            count++;
        }
        
        return count;
    }
};

//one pass
//https://leetcode.com/problems/minimum-number-of-frogs-croaking/discuss/586543/C%2B%2BJava-with-picture-simulation
//Runtime: 76 ms, faster than 69.22% of C++ online submissions for Minimum Number of Frogs Croaking.
//Memory Usage: 9.5 MB, less than 100.00% of C++ online submissions for Minimum Number of Frogs Croaking.
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        unordered_map<char, int> croak2id = {
            {'c', 0},
            {'r', 1},
            {'o', 2},
            {'a', 3},
            {'k', 4}
        };
        
        vector<int> count(5, 0);
        int curFrogs = 0, maxFrogs = 0;
        
        for(char c : croakOfFrogs){
            int id = croak2id[c];
            if(id == 0){
                //we need a new frog
                count[0]++;
                curFrogs++;
                maxFrogs = max(maxFrogs, curFrogs);
            }else if(id == 4){
                //one frog finish singing
                count[3]--;
                curFrogs--;
            }else{
                //one frog sing from previous char to current char
                --count[id-1];
                ++count[id];
                if(count[id-1] < 0) return -1;
            }
        }
        
        //curFrogs == 0: check if all frogs successfully finish
        return (curFrogs == 0) ? maxFrogs : -1;
    }
};
