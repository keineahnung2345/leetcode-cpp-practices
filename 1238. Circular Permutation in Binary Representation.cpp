//Hint 1: Use gray code to generate a n-bit sequence.
//Hint 2: Rotate the sequence such that its first element is start.
//Runtime: 176 ms, faster than 68.14% of C++ online submissions for Circular Permutation in Binary Representation.
//Memory Usage: 15 MB, less than 100.00% of C++ online submissions for Circular Permutation in Binary Representation.
//https://openhome.cc/Gossip/AlgorithmGossip/GrayCode.htm

class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        //gray code
        int N = pow(2, n);
        vector<int> p(N, 0);
        
        for(int i = 1; i < N; i++){
            p[i] = p[i-1];
            
            if(i % 2 == 1){
                //for odd's bit, invert last bit
                p[i] += (p[i]%2) ? -1 : 1;
            }else{
                //for even's bit
                //(the order is starting from most singificant bit)
                //invert the bit before last 1
                //find the last 1
                int pos = N-1;
                while(!(p[i] & (int)pow(2, N-1-pos))){
                    pos--;
                }
                //the position before first 1
                pos--;
                //invert the bit
                p[i] += p[i] & (int)pow(2, N-1-pos) ? -(int)pow(2, N-1-pos) : pow(2, N-1-pos);
            }
        }
        
        int startIndex = find(p.begin(), p.end(), start) - p.begin();
        
        //do rotation
        p.insert(p.end(), p.begin(), p.begin()+startIndex);
        p.erase(p.begin(), p.begin()+startIndex);
        
        return p;
    }
};
