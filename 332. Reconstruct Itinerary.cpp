//Graph, Eulerian path
//https://leetcode.com/problems/reconstruct-itinerary/discuss/78768/Short-Ruby-Python-Java-C%2B%2B
//Runtime: 88 ms, faster than 19.85% of C++ online submissions for Reconstruct Itinerary.
//Memory Usage: 15 MB, less than 54.64% of C++ online submissions for Reconstruct Itinerary.
class Solution {
public:
    unordered_map<string, multiset<string>> edges;
    vector<string> route;
    
    void dfs(string cur){
        while(!edges[cur].empty()){
            string next = *edges[cur].begin();
            edges[cur].erase(edges[cur].begin());
            // cout << next << " ";
            dfs(next);
        }
        /*
        end node has odd degree,
        so we will stuck at end node,
        now we write it to the end of route
        */
        route.insert(route.begin(), cur);
    }
    
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for(vector<string>& ticket : tickets){
            edges[ticket[0]].insert(ticket[1]);
        }
        /*
        all nodes' degrees are even,
        except for start node and end node
        */
        
        dfs("JFK");
        
        return route;
    }
};
