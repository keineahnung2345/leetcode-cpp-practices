//DFS, need to consider epsilon!
//Runtime: 96 ms, faster than 20.53% of C++ online submissions for 24 Game.
//Memory Usage: 18 MB, less than 12.62% of C++ online submissions for 24 Game.

class Solution {
public:
    vector<char> ops;
    
    bool dfs(vector<double> nums){
        int n = nums.size();
        
        // for(double& d : nums){
        //     cout << d << " ";
        // }
        // cout << endl;
        
        if(n == 1){
            /*
            http://www.cplusplus.com/reference/cfloat/
            DBL_EPSILON: 1e-9 or smaller
            */
            //69 / 70 test cases passed.
            //fails [3,3,8,8] (expected true)
            return abs(nums[0] - 24.0) < 1e-5;
            // return abs(nums[0] - 24.0) < std::numeric_limits<double>::epsilon();
        }else{
            /*
            choose any two elements and do operation,
            so it's ok that we don't consider ()
            */
            for(int j = 1; j < n; ++j){
                for(int i = 0; i < j; ++i){
                    //choose two elements nums[i] and nums[j]
					vector<double> nextnums = nums;
                    //erase j and then i(j is larger)
                    nextnums.erase(nextnums.begin()+j);
                    nextnums.erase(nextnums.begin()+i);
                    
                    for(char& op : ops){
                        if(op == '+'){
                            nextnums.push_back(nums[i]+nums[j]);
                        }else if(op == '-'){
                            nextnums.push_back(nums[i]-nums[j]);
                        }else if(op == '*'){
                            nextnums.push_back(nums[i]*nums[j]);
                        }else if(op == '/'){
                            nextnums.push_back(nums[i]/nums[j]);
                        }
                        if(dfs(nextnums))
                            return true;
                        nextnums.pop_back();
                    }
                    
                    /*
                    forgetting this segment:
                    66 / 70 test cases passed.
                    [7,2,6,6]
                    */
                    for(char& op : ops){
                        if(op == '+'){
                            nextnums.push_back(nums[j]+nums[i]);
                        }else if(op == '-'){
                            nextnums.push_back(nums[j]-nums[i]);
                        }else if(op == '*'){
                            nextnums.push_back(nums[j]*nums[i]);
                        }else if(op == '/'){
                            nextnums.push_back(nums[j]/nums[i]);
                        }
                        if(dfs(nextnums))
                            return true;
                        nextnums.pop_back();
                    }
                }
            }
        }
        
        return false;
    }
    
    bool judgePoint24(vector<int>& nums) {
        ops = {'+', '-', '*', '/'};
        
        vector<double> dnums(nums.begin(), nums.end());
        
        return dfs(dnums);
    }
};
