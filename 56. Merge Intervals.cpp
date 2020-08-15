//TLE
//168 / 169 test cases passed.
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return intervals;
        
        sort(intervals.begin(), intervals.end());
        
        int i = 1;
        while(i < intervals.size()){
            // cout << i << " ";
            //last end >= current start
            if(intervals[i-1][1] >= intervals[i][0]){
                //merge them
                intervals[i-1][1] = max(intervals[i-1][1], intervals[i][1]);
                intervals.erase(intervals.begin()+i);
            }else{
                i++;
            }
        }
        
        return intervals;
    }
};

//Approach 2: Sorting, Greedy
//the above method removes merged intervals, this method add unmerged intervals into ans
//Runtime: 52 ms, faster than 58.81% of C++ online submissions for Merge Intervals.
//Memory Usage: 14.3 MB, less than 84.61% of C++ online submissions for Merge Intervals.
//time: O(NlogN), space: O(1) if it's in-place sorting or O(N)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return intervals;
        
        //sort by start point
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> ans;
        
        for(vector<int>& interval : intervals){
            if(ans.empty() || ans.back()[1] < interval[0]){
                ans.push_back(interval);
            }else{
                ans[ans.size()-1][1] = max(ans.back()[1], interval[1]);
            }
        }
        
        return ans;
    }
};

//Approach 1: Connected Components
//TLE
//168 / 169 test cases passed.
//time: O(build graph) + O(traverse graph) + O(merge) = O(V+E) + O(V+E) +O(V) = O(n^2+n) + O(n^2+n) + O(n) = O(n^2)
//space: O(n^2)
class Solution {
public:
    map<vector<int>, vector<vector<int>>> graph;
    set<vector<int>> visited;
    map<int, vector<vector<int>>> nodesInComp;
    
    bool overlap(vector<int>& a, vector<int>& b){
        return a[0] <= b[1] && b[0] <= a[1];
    }
    
    void buildGraph(vector<vector<int>>& intervals){
        for(vector<int>& interval1 : intervals){
            for(vector<int>& interval2: intervals){
                if(overlap(interval1, interval2)){
                    graph[interval1].push_back(interval2);
                    graph[interval2].push_back(interval1);
                }
            }
        }
    };
    
    void markComponentDFS(vector<int>& start, int compNumber){
        stack<vector<int>> stk;
        
        stk.push(start);
        
        while(!stk.empty()){
            vector<int> node = stk.top(); stk.pop();
            if(visited.find(node) == visited.end()){
                visited.insert(node);
                
                nodesInComp[compNumber].push_back(node);
                
                for(vector<int>& child : graph[node]){
                    stk.push(child);
                }
            }
        }
    };
    
    void buildComponents(vector<vector<int>>& intervals){
        int compNumber = 0;
        for(vector<int>& interval : intervals){
            if(visited.find(interval) == visited.end()){
                markComponentDFS(interval, compNumber);
                compNumber++;
            }
        }
    };
    
    vector<int> mergeNodes(vector<vector<int>> nodes){
        int minStart = nodes[0][0];
        int maxEnd = nodes[0][1];
        
        for(vector<int>& node : nodes){
            minStart = min(minStart, node[0]);
            maxEnd = max(maxEnd, node[1]);
        }
        
        return vector<int>{minStart, maxEnd};
    };
    
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        buildGraph(intervals);
        buildComponents(intervals);
        
        vector<vector<int>> merged;
        for(int comp = 0; comp < nodesInComp.size(); comp++){
            merged.push_back(mergeNodes(nodesInComp[comp]));
        }
        
        return merged;
    }
};
