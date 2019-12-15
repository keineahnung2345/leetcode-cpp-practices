//Runtime: 292 ms, faster than 7.68% of C++ online submissions for Maximum Score Words Formed by Letters.
//Memory Usage: 53.4 MB, less than 100.00% of C++ online submissions for Maximum Score Words Formed by Letters.

class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int wordScore, combScore, maxScore = 0;
        vector<int> wordsScore;
        map<char, int> lettersCount, wordCount, combCount;
        bool combExist;
        
        //create the map lettersCount
        for(char c : letters){
            if(lettersCount.find(c) == lettersCount.end()){
                lettersCount[c] = 1;
            }else{
                lettersCount[c]++;
            }
        }
        
        //calculate scores of words, fill wordsScore
        for(string word : words){
            wordCount.clear();
            wordScore = 0;
            for(char c : word){
                if(wordCount.find(c) == wordCount.end()){
                    wordCount[c] = 1;
                }else{
                    wordCount[c]++;
                }
                
                if(wordCount[c] <= lettersCount[c]){
                    wordScore += score[c-'a'];
                }else{
                    //this word cannot be formed
                    wordScore = 0;
                    break;
                }
            }
            wordsScore.push_back(wordScore);
            // cout << wordScore << " ";
        }
        // cout << endl;
        
        //enumerate 2^words.length possibles
        for(int num = 0; num < pow(2, words.size()); num++){
            combScore = 0;
            combCount.clear();
            combExist = true;
            for(int i = 0; i < words.size(); i++){
                //(num/(pow(2,i)))%2: imagine "num" as a binary number
                //then num/(pow(2,i)) is the part that after "num"'s i'th bit
                //(num/(pow(2,i)))%2 is the i'th bit of "num"
                if( (int)(num/(pow(2,i))) %2 == 1){
                    //check if this combination exist
                    for(char c : words[i]){
                        if(combCount.find(c) == combCount.end()){
                            combCount[c] = 1;
                        }else{
                            combCount[c]++;
                        }
                        
                        if(combCount[c] > lettersCount[c]){
                            combExist = false;
                        }
                    }
                    
                    if(!combExist){
                        combScore = 0;
                        break;
                    }else{
                        combScore += wordsScore[i];
                    }
                }
            }
            
            if(combScore > maxScore){
                // for(int i = 0; i < words.size(); i++){
                //     cout << (int)(num/(pow(2,i))) %2;
                // }
                // cout << endl;
                
                maxScore = combScore;
            }
        }
        
        return maxScore;
    }
};
