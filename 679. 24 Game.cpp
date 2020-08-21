//DFS
//WA
//69 / 70 test cases passed.
//fails [3,3,8,8] (expected true)
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
            return nums[0] == 24;
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
