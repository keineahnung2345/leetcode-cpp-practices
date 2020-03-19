//Recursion, divide and conquer
//https://leetcode.com/problems/different-ways-to-add-parentheses/discuss/66328/A-recursive-Java-solution-(284-ms)
//Runtime: 4 ms, faster than 84.42% of C++ online submissions for Different Ways to Add Parentheses.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Different Ways to Add Parentheses.
class Solution {
public:
    map<string, vector<int>> calculated;
    vector<int> diffWaysToCompute(string input) {
        int N = input.size();
        vector<int> result;
        for(int i = 0; i < N; i++){
            char c = input[i];
            if(c == '+' || c == '-' || c == '*'){
                string sub1 = input.substr(0, i);
                string sub2 = input.substr(i+1);
                vector<int> v1 = calculated.find(sub1) == calculated.end() ? diffWaysToCompute(sub1) : calculated[sub1];
                vector<int> v2 = calculated.find(sub2) == calculated.end() ? diffWaysToCompute(sub2) : calculated[sub2];
                for(int i1 : v1){
                    for(int i2 : v2){
                        int r;
                        switch(c){
                            case '+':
                                r = i1+i2;
                                break;
                            case '-':
                                r = i1-i2;
                                break;
                            case '*':
                                r = i1*i2;
                                break;
                        }
                        result.push_back(r);
                    }
                }
            }
        }
        //no operator inside input
        if(result.size() == 0){
            result.push_back(stoi(input));
        }
        calculated[input] = result;
        return result;
    }
};
