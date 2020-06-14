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
 
