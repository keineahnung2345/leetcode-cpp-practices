/**
You have a list of words and a pattern, and you want to know which words in words matches the pattern.

A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.

(Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.)

Return a list of the words in words that match the given pattern. 

You may return the answer in any order.

 

Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation,
since a and b map to the same letter.
 

Note:

1 <= words.length <= 50
1 <= pattern.length = words[i].length <= 20
**/

/**
Solution
Approach 1: Two Maps
Intuition and Algorithm

If say, the first letter of the pattern is "a", and the first letter of the word is "x", then in the permutation, "a" must map to "x".

We can write this bijection using two maps: a forward map m1 and a backwards map m2.

m1:"a"→"x"

m2:"x"→"a"

Then, if there is a contradiction later, we can catch it via one of the two maps. 
For example, if the (word, pattern) is ("aa", "xy"), we will catch the mistake in m1 (namely, m1("a")="x"="y"). 
Similarly, with (word, pattern) = ("ab", "xx"), we will catch the mistake in m2.

//Java
/**
class Solution {
    public List<String> findAndReplacePattern(String[] words, String pattern) {
        List<String> ans = new ArrayList();
        for (String word: words)
            if (match(word, pattern))
                ans.add(word);
        return ans;
    }

    public boolean match(String word, String pattern) {
        Map<Character, Character> m1 = new HashMap();
        Map<Character, Character> m2 = new HashMap();

        for (int i = 0; i < word.length(); ++i) {
            char w = word.charAt(i);
            char p = pattern.charAt(i);
            if (!m1.containsKey(w)) m1.put(w, p);
            if (!m2.containsKey(p)) m2.put(p, w);
            if (m1.get(w) != p || m2.get(p) != w)
                return false;
        }

        return true;
    }
}

Complexity Analysis

Time Complexity: O(N∗K), where N is the number of words, and KK is the length of each word.

Space Complexity: O(N∗K), the space used by the answer. 
**/

/**
Approach 2: One Map
Intuition and Algorithm

As in Approach 1, we can have some forward map \text{m1} : \mathbb{L} \rightarrow \mathbb{L}m1:L→L, where \mathbb{L}L is the set of letters.

However, instead of keeping track of the reverse map \text{m2}m2, we could simply make sure that every value \text{m1}(x)m1(x) in the codomain is reached at most once. This would guarantee the desired permutation exists.

So our algorithm is this: after defining \text{m1}(x)m1(x) in the same way as Approach 1 (the forward map of the permutation), afterwards we make sure it reaches distinct values.

//Java
class Solution {
    public List<String> findAndReplacePattern(String[] words, String pattern) {
        List<String> ans = new ArrayList();
        for (String word: words)
            if (match(word, pattern))
                ans.add(word);
        return ans;
    }

    public boolean match(String word, String pattern) {
        Map<Character, Character> M = new HashMap();
        for (int i = 0; i < word.length(); ++i) {
            char w = word.charAt(i);
            char p = pattern.charAt(i);
            if (!M.containsKey(w)) M.put(w, p);
            if (M.get(w) != p) return false;
        }

        boolean[] seen = new boolean[26];
        for (char p: M.values()) {
            if (seen[p - 'a']) return false;
            seen[p - 'a'] = true;
        }
        return true;
    }
}

Complexity Analysis

Time Complexity: O(N∗K), where N is the number of words, and KK is the length of each word.

Space Complexity: O(N∗K), the space used by the answer. 
**/

/**
//Your runtime beats 59.66 % of cpp submissions.
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> remain_words;
        for(int i = 0; i < words.size(); i++){
            map<char, char> pt2word;
            map<char, char> word2pt;
            bool match = true;
            for(int j = 0; j < words[i].size(); j++){
                if(pt2word.find(pattern[j])==pt2word.end()){ //not in map
                    pt2word.insert(make_pair(pattern[j], words[i][j]));
                }else if(words[i][j] != pt2word[pattern[j]]){
                    cout << words[i][j] << pattern[j] << (words[i][j] != pt2word[pattern[j]]) << endl;
                    match = false;
                    break;
                }
                
                if(word2pt.find(words[i][j])==word2pt.end()){ //not in map
                    word2pt.insert(make_pair(words[i][j], pattern[j]));
                }else if(pattern[j] != word2pt[words[i][j]]){
                    cout << words[i][j] << pattern[j] << (pattern[j] != word2pt[words[i][j]]) << endl;
                    match = false;
                    break;
                }
            }
            if(match){
                remain_words.push_back(words[i]);
            }
        }
        return remain_words;
    }
};
**/

//Your runtime beats 100.00 % of cpp submissions.
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> remain_words;
        for(int i = 0; i < words.size(); i++){
            map<char, char> pt2word;
            map<char, char> word2pt;
            bool match = true;
            for(int j = 0; j < words[i].size(); j++){
                if(pt2word.find(pattern[j])==pt2word.end()){ //not in map
                    pt2word.insert(make_pair(pattern[j], words[i][j]));
                }
                if(word2pt.find(words[i][j])==word2pt.end()){ //not in map
                    word2pt.insert(make_pair(words[i][j], pattern[j]));
                }
                if((words[i][j] != pt2word[pattern[j]]) || (pattern[j] != word2pt[words[i][j]])){
                    match = false;
                    break;
                }
            }
            if(match){
                remain_words.push_back(words[i]);
            }
        }
        return remain_words;
    }
};
