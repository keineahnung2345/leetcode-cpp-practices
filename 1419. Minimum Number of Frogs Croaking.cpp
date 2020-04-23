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
