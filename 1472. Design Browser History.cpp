//Runtime: 504 ms, faster than 25.92% of C++ online submissions for Design Browser History.
//Memory Usage: 65 MB, less than 100.00% of C++ online submissions for Design Browser History.
class BrowserHistory {
public:
    vector<string> fw, bw;
    string cur;
    
    BrowserHistory(string homepage) {
        cur = homepage;
    }
    
    void print(){
        cout << "fw: ";
        for(int i = 0; i < fw.size(); i++){
            cout << fw[i] << " ";
        }
        cout << endl;
        
        cout << "bw: ";
        for(int i = 0; i < bw.size(); i++){
            cout << bw[i] << " ";
        }
        cout << endl;
        cout << endl;
    }
    
    void visit(string url) {
        fw.clear();
        bw.push_back(cur);
        cur = url;
        // print();
    }
    
    string back(int steps) {
        while(!bw.empty() && steps-- > 0){
            fw.push_back(cur);
            cur = bw.back(); bw.pop_back();
        }
        
        // print();
        return cur;
    }
    
    string forward(int steps) {
        while(!fw.empty() && steps-- > 0){
            bw.push_back(cur);
            cur = fw.back(); fw.pop_back();
        }
        
        // print();
        return cur;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
 
//two stacks
//https://leetcode.com/problems/design-browser-history/discuss/674300/Two-Stacks-vs.-List
//Runtime: 752 ms, faster than 5.01% of C++ online submissions for Design Browser History.
//Memory Usage: 120 MB, less than 100.00% of C++ online submissions for Design Browser History.
class BrowserHistory {
public:
    stack<string> fw, bw;
    string cur;
    
    BrowserHistory(string homepage) {
        cur = homepage;
    }
    
    void visit(string url) {
        fw = stack<string>(); //there is no stack::clear()!
        bw.push(cur);
        cur = url;
    }
    
    string back(int steps) {
        while(!bw.empty() && steps-- > 0){
            fw.push(cur);
            cur = bw.top(); bw.pop();
        }
        
        return cur;
    }
    
    string forward(int steps) {
        while(!fw.empty() && steps-- > 0){
            bw.push(cur);
            cur = fw.top(); fw.pop();
        }
        
        return cur;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */

//one vector holding backward and forward history
//https://leetcode.com/problems/design-browser-history/discuss/674300/Two-Stacks-vs.-List
//Runtime: 448 ms, faster than 39.59% of C++ online submissions for Design Browser History.
//Memory Usage: 55 MB, less than 100.00% of C++ online submissions for Design Browser History.
class BrowserHistory {
public:
    int cur = 0;
    vector<string> hist;
    
    BrowserHistory(string homepage) {
        hist.push_back(homepage);
    }
    
    void visit(string url) {
        /*
        hist[0...cur] is backward history
        hist[cur+1...] is forward history
        */
        //remove forward history
        hist.resize(cur+1);
        //store it into backward history
        hist.push_back(url);
        //cur now points to last element in hist
        cur++;
    }
    
    string back(int steps) {
        cur = max(0, cur-steps);
        return hist[cur];
    }
    
    string forward(int steps) {
        cur = min((int)hist.size()-1, cur+steps);
        return hist[cur];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
