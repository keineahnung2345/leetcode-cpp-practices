/**
We are given two sentences A and B.  (A sentence is a string of space separated words.  Each word consists only of lowercase letters.)
A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
Return a list of all uncommon words. 
You may return the list in any order.

Example 1:

Input: A = "this apple is sweet", B = "this apple is sour"
Output: ["sweet","sour"]
Example 2:

Input: A = "apple apple", B = "banana"
Output: ["banana"]
**/

//Runtime: 8 ms, faster than 66.46% of C++ online submissions for Uncommon Words from Two Sentences.
//Memory Usage: 11.4 MB, less than 5.55% of C++ online submissions for Uncommon Words from Two Sentences.
class Solution {
public:
    vector<string> string_split(string str){
        size_t pos = 0;
        string token;
        string delimiter = " ";
        vector<string> str_vec;
        
        while ((pos = str.find(delimiter)) != string::npos) {
            token = str.substr(0, pos);
            str_vec.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        
        //add the last token
        str_vec.push_back(str);
        
        return str_vec;
    }
    
    vector<set<string>> removeDuplicates(vector<string>& v){
        set<string> dup;
        
        for(string s : v){
            if(count(v.begin(), v.end(), s) > 1){
                dup.insert(s);
                //cannot erase element while iterating it
                // v.erase(remove(v.begin(), v.end(), s), v.end());
            }
        }
        for(string s : dup){
            v.erase(remove(v.begin(), v.end(), s), v.end());
        }
        return vector<set<string>> {set<string> (v.begin(), v.end()), dup};
    }
    
    vector<string> uncommonFromSentences(string A, string B) {
        vector<string> vA = string_split(A);
        vector<string> vB = string_split(B);
        
        //remove duplicate elements
        vector<set<string>> udA = removeDuplicates(vA);
        vector<set<string>> udB = removeDuplicates(vB);
        
        set<string> uA = udA[0]; 
        set<string> uB = udB[0];
        set<string> dA = udA[1];
        set<string> dB = udB[1];
        
        //symmetric difference
        //allocate vector size as sA.size()+sB.size(),
        // because if sA and sB are all different, 
        // it will need that amount of space
        set<string> uncommons;
        set<string>::iterator s_it;
        
        // the xor of two sets
        set_symmetric_difference(uA.begin(), uA.end(), 
                                 uB.begin(), uB.end(),
                                 inserter(uncommons, uncommons.begin()));
        
        // remove duplicate from dA
        set<string> tmp;
        set_difference(make_move_iterator(uncommons.begin()), 
                            make_move_iterator(uncommons.end()), 
                            dA.begin(), dA.end(), 
                            inserter(tmp, tmp.begin()));
        uncommons.swap(tmp);
        tmp.clear();
        
        // remove duplicate from dB
        set_difference(make_move_iterator(uncommons.begin()), 
                            make_move_iterator(uncommons.end()), 
                            dB.begin(), dB.end(), 
                            inserter(tmp, tmp.begin()));
        uncommons.swap(tmp);
        tmp.clear();
        
        return vector<string> (uncommons.begin(), uncommons.end());
    }
};

/**
Approach 1: Counting
Intuition and Algorithm

Every uncommon word occurs exactly once in total. 
We can count the number of occurrences of every word, 
then return ones that occur exactly once.
**/
/**
Complexity Analysis
Time Complexity: O(M+N), where M, N are the lengths of A and B respectively.
Space Complexity: O(M+N), the space used by count. 
**/
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Uncommon Words from Two Sentences.
//Memory Usage: 9.6 MB, less than 11.11% of C++ online submissions for Uncommon Words from Two Sentences.
class Solution {
public:
    vector<string> string_split(string str){
        size_t pos = 0;
        string token;
        string delimiter = " ";
        vector<string> str_vec;
        
        while ((pos = str.find(delimiter)) != string::npos) {
            token = str.substr(0, pos);
            str_vec.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        
        //add the last token
        str_vec.push_back(str);
        
        return str_vec;
    }
    
    template <class K, class V>
    void insert_or_increment(map<K,V>& mymap, K key, V inc){
        if(mymap.find(key)==mymap.end()){
            mymap[key] = 0+inc;
        }else{
            mymap[key] += inc;
        }
    }
    
    vector<string> uncommonFromSentences(string A, string B) {
        vector<string> vA = string_split(A);
        vector<string> vB = string_split(B);
        map<string, int> mymap;
        vector<string> ans;
        
        for(string e : vA){
            insert_or_increment(mymap, e, 1);
        }
        
        for(string e : vB){
            insert_or_increment(mymap, e, 1);
        }
        
        for(pair<string, int> p : mymap){
            if(p.second==1){
                ans.push_back(p.first);
            }
        }
        
        return ans;
    }
};
