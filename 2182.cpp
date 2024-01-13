// 给你一个字符串 s 和一个整数 repeatLimit ，用 s 中的字符构造一个新字符串 repeatLimitedString ，使任何字母 连续 出现的次数都不超过 repeatLimit 次。你不必使用 s 中的全部字符。

// 返回 字典序最大的 repeatLimitedString 。

// 如果在字符串 a 和 b 不同的第一个位置，字符串 a 中的字母在字母表中出现时间比字符串 b 对应的字母晚，则认为字符串 a 比字符串 b 字典序更大 。如果字符串中前 min(a.length, b.length) 个字符都相同，那么较长的字符串字典序更大。

 

// 示例 1：

// 输入：s = "cczazcc", repeatLimit = 3
// 输出："zzcccac"
// 解释：使用 s 中的所有字符来构造 repeatLimitedString "zzcccac"。
// 字母 'a' 连续出现至多 1 次。
// 字母 'c' 连续出现至多 3 次。
// 字母 'z' 连续出现至多 2 次。
// 因此，没有字母连续出现超过 repeatLimit 次，字符串是一个有效的 repeatLimitedString 。
// 该字符串是字典序最大的 repeatLimitedString ，所以返回 "zzcccac" 。
// 注意，尽管 "zzcccca" 字典序更大，但字母 'c' 连续出现超过 3 次，所以它不是一个有效的 repeatLimitedString 。

#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> number(26,0);
        for(char c : s){
            number[c - 'a'] ++;
        }
        int limit  = 0;
        string result;
        for(int i = 26-1,j = 26 - 2;i >= 0;){
            if (number[i] == 0){
                limit = 0;
                i --;
                // j --; //这样如果j ==0，i==1不成立
            }else if(number[j] == 0 && j >0){
                j -- ;
            }else if(j == i ){
                j--;
            }else if( limit < repeatLimit){
                number[i] --;
                result.push_back('a'+i);
                limit ++;
            }else if(limit == repeatLimit && j >= 0){
                limit = 0;
                result.push_back('a' +j);
                number[j]--;
            }else if(i == 0 && limit == repeatLimit){
                break;
            }
        }
        return result;
    }
};

int main(){
    Solution A;
    string T = "aababab";
    int LI = 2;
    cout << A.repeatLimitedString(T,LI);
    return 0;
}


