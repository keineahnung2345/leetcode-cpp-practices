//failed
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
//         if(A.find(B) != string::npos){
//             /**
//             A: "aa"
//             B: "a"
//             **/
//             return 1;
//         }
//         int prev_s = 0, s = 0;
//         int count = 0;
        
//         while((s = B.find(A, prev_s)) != string::npos){
//             cout << "prev_s: " << prev_s << ", s: " << s << endl;
//             if(prev_s == 0){
//                 //the first occurent of A in B should at 0 ~ A.size()-1
//                 if(s >= A.size()) return -1;
//                 //B[0:s] should be a substring of A
//                 if(A.find(B.substr(0, s)) == string::npos){
//                     return -1;
//                 }else if(s != 0){
//                     count++;
//                 }
//                 count++;
//                 cout << "first" << endl;
//             // }else if(s + A.size()*2 > B.size()){
//             //     //last occurence
//             //     //the last part of B should be a substring of A
//             //     if(A.find(B.substr(s+A.size(), A.size())) == string::npos) return -1;
//             //     count++;
//             //     cout << "last" << endl;
//             }else{
//                 //middle occurence
//                 //the 's' should be the same as the guessed 'prev_s'
//                 if(prev_s != s) return -1;
//                 count++;
//                 // cout << "middle" << endl;
//             }
//             cout << "count: " << count << endl;
//             //update pointer
//             //guess that the next occurence of A is at (s + A.size())
//             prev_s = s + A.size();
//         }
        
//         cout << "prev_s: " << prev_s << ", s: " << s << endl;
//         if(prev_s == 0){
//             /**
//             A: "abcd"
//             B: "cda"
//             **/
//             //not found any A in B
//             cout << "prev_s== 0" << endl;
//             cout << A.substr(0, 1) << endl;
//             if((s = B.find(A.substr(0, 1))) != string::npos){
//                 cout << B.substr(s, A.size()) << endl;
//                 if(A.find(B.substr(s, A.size())) != string::npos){
//                     count++;
//                 }
//             }
            
//             string sub_B = (s != string::npos)?B.substr(0, s):B;
//             cout << sub_B << endl;
//             if(A.find(sub_B) != string::npos){
//                 count++;
//             }
            
//             return count;
//         }
//         //if the last occurence of A in B is intact, 
//         // then prev_s should be equal to B.size()
//         if(prev_s != B.size()){
//             // prev_s-1+A.size()
//             //last occurence
//             //the last part of B should be a substring of A
//             if(A.find(B.substr(prev_s, A.size())) == string::npos) return -1;
//             count++;
//             cout << "last" << endl;
//             cout << "count: " << count << endl;
//         }
        
        // int count = 1;
        // string dup_A = A;
        // while(dup_A.find(B) == string::npos && dup_A.size() <= B.size()*2){
        //     dup_A += A;
        //     count++;
        // }
        // if(dup_A.size() > B.size()*2) return -1;
        // return count;
    }
};

//Approach #1: Ad-Hoc [Accepted]
//Runtime: 16 ms, faster than 85.90% of C++ online submissions for Repeated String Match.
//Memory Usage: 9.1 MB, less than 82.08% of C++ online submissions for Repeated String Match.
//time: O(N * (M+N)), M, N is the length of A and B respectively. M+N is the length of dup_A. 
// We compare dup_A with B, so the time used is the product of their lengths.
//space: O(M+N), used by dup_A
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        string dup_A = A;
        for(; dup_A.size() < B.size(); dup_A += A){}
        if(dup_A.find(B) != string::npos) return dup_A.size()/A.size();
        dup_A += A;
        if(dup_A.find(B) != string::npos) return dup_A.size()/A.size();
        return -1;
    }
};
