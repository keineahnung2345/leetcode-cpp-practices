//union find
//WA
//[["a","c"],["b","e"],["c","d"],["e","d"]]
//[2.0,3.0,0.5,5.0]
//[["a","b"]]
//in the "connect (a,b) and (b,c) to (a,c)" part, it fails when the path is too long
class DSU{
public:
    map<string, string> parent;
    
    DSU(set<string>& vertices){
        for(string vertex : vertices){
            parent[vertex] = vertex;
        }
    };
    
    string find(string x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    void unite(string x, string y){
        parent[find(x)] = find(y);
    };
};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        set<string> vertices;
        map<vector<string>, double> edges;
        
        for(int i = 0; i < equations.size(); i++){
            vector<string> equation = equations[i];
            double value = values[i];
            
            vertices.insert(equation[0]);
            vertices.insert(equation[1]);
            edges[equation] = value;
            edges[{equation[1], equation[0]}] = 1/value;
        }
        
        //check how many connected components there are?
        DSU dsu(vertices);
        for(auto it = edges.begin(); it != edges.end(); it++){
            vector<string> edge = it->first;
            dsu.unite(edge[0], edge[1]);
        }
        
        //key: root of that group
        map<string, set<string>> groups;
        for(string vertex : vertices){
            groups[dsu.find(vertex)].insert(vertex);
        }
        
        // for(auto it = groups.begin(); it != groups.end(); ++it){
        //     cout << it->first << " : ";
        //     for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2){
        //         cout << *it2 << " ";
        //     }
        //     cout << endl;
        // }
        
        //for each connect component, full connect their nodes
        //we have (a,b) and (b,c), now connect them to (a,c)
        for(auto it = groups.begin(); it != groups.end(); it++){
            vector<string> oneGroup(it->second.begin(), it->second.end());
            
            for(int i = 0; i < oneGroup.size(); i++){
                for(int j = i; j < oneGroup.size(); j++){
                    string vi = oneGroup[i], vj = oneGroup[j];
                    if(i == j){
                        edges[{vi, vj}] = 1.0;
                    }else if(edges.find({vi, vj}) != edges.end()){
                        //they are connected directly
                        
                    }else{
                        // cout << vi << " and " << vj << " are connected indirectly" << endl;
                        //they can be connected indirectly
                        //find vertex vk s.t. {vi,vk} and {vk,vj} exist
                        for(int k = 0; k < oneGroup.size(); k++){
                            string vk = oneGroup[k];
                            if(edges.find({vi, vk}) != edges.end() && edges.find({vj, vk}) != edges.end()){
                                edges[{vi,vj}] = edges[{vi,vk}] * edges[{vk, vj}];
                                edges[{vj,vi}] = edges[{vj,vk}] * edges[{vk, vi}];
                                break;
                            }
                        }
                    }
                }
            }
        }
        
        // for(auto it = edges.begin(); it != edges.end(); ++it){
        //     cout << it->first[0] << ", " << it->first[1] << endl;
        // }
        
        vector<double> ans;
        
        for(vector<string>& query: queries){
            string numerator = query[0];
            string denominator = query[1];
            if(edges.find({numerator, denominator}) != edges.end()){
                ans.push_back(edges[{numerator, denominator}]);
            }else{
                ans.push_back(-1.0);
            }
        }
    
        return ans;
    }
};

//Floyd Warshall
//https://leetcode.com/problems/evaluate-division/discuss/88175/9-lines-%22Floydu2013Warshall%22-in-Python
//Runtime: 8 ms, faster than 9.29% of C++ online submissions for Evaluate Division.
//Memory Usage: 8.3 MB, less than 12.40% of C++ online submissions for Evaluate Division.
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> quot;
        
        int N = equations.size();
        
        for(int i = 0; i < N; i++){
            vector<string> equation = equations[i];
            string num = equation[0], den = equation[1];
            double value = values[i];
            quot[num][num] = 1.0;
            quot[den][den] = 1.0;
            quot[num][den] = value;
            quot[den][num] = 1.0/value;
        }
        
        for(auto it = quot.begin(); it != quot.end(); it++){
            const string& k = it->first;
            for(auto it2 = quot[k].begin(); it2 != quot[k].end(); it2++){
                const string& i = it2->first;
                for(auto it3 = quot[k].begin(); it3 != quot[k].end(); it3++){
                    const string& j = it3->first;
                    quot[i][j] = quot[i][k] * quot[k][j];
                    // adding this line gives WA!!!
                    //we don't need this line because i is not necessary <= j!
                    // quot[j][i] = quot[j][k] * quot[k][i];
                }
            }
        }
        
        vector<double> ans;
        
        for(vector<string>& query : queries){
            string num = query[0], den = query[1];
            
            if(quot[num].find(den) == quot[num].end()){
                ans.push_back(-1.0);
            }else{
                ans.push_back(quot[num][den]);
            }
        }
        
        return ans;
    }
};

//DFS
//https://leetcode.com/problems/evaluate-division/discuss/171649/1ms-DFS-with-Explanations
//Runtime: 4 ms, faster than 58.89% of C++ online submissions for Evaluate Division.
//Memory Usage: 8.5 MB, less than 8.58% of C++ online submissions for Evaluate Division.
class Solution {
public:
    double dfs(string start, string end, unordered_map<string, unordered_map<string, double>>& graph, unordered_set<string>& visited){
        if(graph.find(start) == graph.end()){
            return -1;
        }
        
        if(graph[start].find(end) != graph[start].end()){
            return graph[start][end];
        }
        
        for(const auto& nei : graph[start]){
            if(find(visited.begin(), visited.end(), nei.first) != visited.end())
                continue;
            visited.insert(nei.first);
            double res;
            if((res = dfs(nei.first, end, graph, visited)) != -1){
                return graph[start][nei.first] * res;
            }
        }
        
        return -1;
    }
    
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> quot;
        
        int N = equations.size();
        
        for(int i = 0; i < N; i++){
            const vector<string>& equation = equations[i];
            const string& num = equation[0], den = equation[1];
            const double& value = values[i];
            quot[num][num] = 1.0;
            quot[den][den] = 1.0;
            quot[num][den] = value;
            quot[den][num] = 1.0/value;
        }
        
        vector<double> ans;
        unordered_set<string> visited;
        
        for(const vector<string>& query : queries){
            const string& num = query[0], den = query[1];
            visited = {num};
            ans.push_back(dfs(num, den, quot, visited));
        }
        
        return ans;
    }
};
