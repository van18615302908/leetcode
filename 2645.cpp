//给你一个字符串 word ，你可以向其中任何位置插入 "a"、"b" 或 "c" 任意次，返回使 word 有效 需要插入的最少字母数。
//如果字符串可以由 "abc" 串联多次得到，则认为该字符串 有效 。
// 输入：word = "b"
// 输出：2
// 解释：在 "b" 之前插入 "a" ，在 "b" 之后插入 "c" 可以得到有效字符串 "abc" 。
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    int addMinimum(string word) {
        int n = word.size();
        vector<int> d(n+1,0);
        for (int i = 1;i < n + 1;i++){
            d[i] = d[i - 1] + 2;
            if(i > 1 && word[i -1] > word[i -2]){
                d[i] = d[i - 1] - 1;
            }
        return d[n];
        }
    }
};