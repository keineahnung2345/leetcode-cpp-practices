//Runtime: 320 ms, faster than 87.95% of C++ online submissions for Display Table of Food Orders in a Restaurant.
//Memory Usage: 63.7 MB, less than 100.00% of C++ online submissions for Display Table of Food Orders in a Restaurant.
class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        set<string> dishes;
        map<int, map<string, int>> table2orders;
        
        for(vector<string>& order : orders){
            table2orders[stoi(order[1])][order[2]] += 1;
            dishes.insert(order[2]);
        }
        
        vector<vector<string>> ans;
        vector<string> header(dishes.begin(), dishes.end());
        
        header.insert(header.begin(), "Table");
        ans.push_back(header);
        
        for(auto ait = table2orders.begin(); ait != table2orders.end(); ait++){
            vector<string> row = {to_string(ait->first)};
            for(int i = 1; i < header.size(); i++){
                if(ait->second.find(header[i]) == ait->second.end()){
                    row.push_back("0");
                }else{
                    row.push_back(to_string(ait->second[header[i]]));
                }
                
            }
            ans.push_back(row);
        }
        
        return ans;
    }
};
