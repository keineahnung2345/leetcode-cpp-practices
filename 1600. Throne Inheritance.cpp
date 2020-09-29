//Runtime: 620 ms, faster than 98.00% of C++ online submissions for Throne Inheritance.
//Memory Usage: 168.1 MB, less than 77.84% of C++ online submissions for Throne Inheritance.
class Node{
public:
    string name;
    bool dead;
    vector<Node*> children;
    
    Node(){
        name = "";
        dead = false;
    }
    
    Node(string n) : name(n) {
        dead = false;
    }
};

class ThroneInheritance {
public:
    Node* king;
    unordered_map<string, Node*> name2node;
    
    ThroneInheritance(string kingName) {
        king = new Node(kingName);
        name2node[kingName] = king;
    }
    
    void birth(string parentName, string childName) {
        Node* child = new Node(childName);
        name2node[parentName]->children.push_back(child);
        name2node[childName] = child;
    }
    
    void death(string name) {
        name2node[name]->dead = true;
    }
    
    vector<string> getInheritanceOrder() {
        vector<string> ans;
        
        //dfs
        stack<const Node*> stk;
        
        stk.push(king);
        
        while(!stk.empty()){
            const Node* cur = stk.top(); stk.pop();
            
            if(!cur->dead){
                ans.push_back(cur->name);
            }
            
            //the older, the earlier popped
            for(int i = cur->children.size()-1; i >= 0; --i){
                stk.push(cur->children[i]);
            }
        }
        
        return ans;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */
 
