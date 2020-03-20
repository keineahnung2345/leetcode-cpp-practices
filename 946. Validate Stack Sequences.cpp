//Runtime: 8 ms, faster than 90.81% of C++ online submissions for Validate Stack Sequences.
//Memory Usage: 6.9 MB, less than 100.00% of C++ online submissions for Validate Stack Sequences.
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int i = 0, j = 0;
        stack<int> stk;
        int last = -1;
        
        //jump out when we cannot push or pop the stack
        while((i < pushed.size() || j < popped.size()) && (stk.size() != last)){
            last = stk.size();
            cout << i << " " << j << " " << endl;
            if(!stk.empty() && stk.top() == popped[j]){
                stk.pop();
                // cout << "pop " << popped[j] << endl;
                j++;
            }else if(i < pushed.size()){
                stk.push(pushed[i]);
                // cout << "push " << pushed[i] << endl;
                i++;
            }
        }
        
        return stk.size() == 0;
    }
};

//Approach 1: Greedy
//Runtime: 8 ms, faster than 90.81% of C++ online submissions for Validate Stack Sequences.
//Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Validate Stack Sequences.
//time: O(N), space: O(N)
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int N = pushed.size();
        stack<int> stk;
        
        int j = 0; //index to popped
        for(int x : pushed){
            stk.push(x);
            //pop once we can do that, greedy algorithm
            while(!stk.empty() && j < N && stk.top() == popped[j]){
                stk.pop();
                j++;
            }
        }
        
        return j == N;
    }
};
