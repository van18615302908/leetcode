# 2024/01/08.447

[447. 回旋镖的数量](https://leetcode.cn/problems/number-of-boomerangs/)

<font color='red'>中等</font>

<font color='red'>**哈希**</font>

给定平面上 `n` 对 **互不相同** 的点 `points` ，其中 `points[i] = [xi, yi]` 。**回旋镖** 是由点 `(i, j, k)` 表示的元组 ，其中 `i` 和 `j` 之间的距离和 `i` 和 `k` 之间的欧式距离相等（**需要考虑元组的顺序**）。

返回平面上所有回旋镖的数量。

**示例 1：**

```
输入：points = [[0,0],[1,0],[2,0]]
输出：2
解释：两个回旋镖为 [[1,0],[0,0],[2,0]] 和 [[1,0],[2,0],[0,0]]
```

**示例 2：**

```
输入：points = [[1,1],[2,2],[3,3]]
输出：2
```

**示例 3：**

```
输入：points = [[1,1]]
输出：0
```

 

**提示：**

- `n == points.length`
- `1 <= n <= 500`
- `points[i].length == 2`
- `-104 <= xi, yi <= 104`
- 所有点都 **互不相同**

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int result = 0;

        for (const auto& p : points) {
            unordered_map<int, int> distanceCount;

            for (const auto& q : points) {
                int dx = p[0] - q[0];
                int dy = p[1] - q[1];
                int distance = dx * dx + dy * dy;

                // 计算距离并将其存储在哈希表中
                distanceCount[distance]++;
            }

            // 遍历哈希表，对于每个距离，计算回旋镖数量并累加到结果中
            for (const auto& pair : distanceCount) {
                int count = pair.second;
                result += count * (count - 1);  // 回旋镖的数量为排列组合的数量，即C(n,2)
            }
        }

        return result;
    }
};
```

# 2024/01/09.2707

[2707. 字符串中的额外字符](https://leetcode.cn/problems/extra-characters-in-a-string/)

<font color='red'>中等</font>

<font color='orange'>动态规划</font>

给你一个下标从 **0** 开始的字符串 `s` 和一个单词字典 `dictionary` 。你需要将 `s` 分割成若干个 **互不重叠** 的子字符串，每个子字符串都在 `dictionary` 中出现过。`s` 中可能会有一些 **额外的字符** 不在任何子字符串中。

请你采取最优策略分割 `s` ，使剩下的字符 **最少** 。



**示例 1：**

```
输入：s = "leetscode", dictionary = ["leet","code","leetcode"]
输出：1
解释：将 s 分成两个子字符串：下标从 0 到 3 的 "leet" 和下标从 5 到 8 的 "code" 。只有 1 个字符没有使用（下标为 4），所以我们返回 1 。
```

**示例 2：**

```
输入：s = "sayhelloworld", dictionary = ["hello","world"]
输出：3
解释：将 s 分成两个子字符串：下标从 3 到 7 的 "hello" 和下标从 8 到 12 的 "world" 。下标为 0 ，1 和 2 的字符没有使用，所以我们返回 3 。
```



**提示：**

- `1 <= s.length <= 50`
- `1 <= dictionary.length <= 50`
- `1 <= dictionary[i].length <= 50`
- `dictionary[i]` 和 `s` 只包含小写英文字母。
- `dictionary` 中的单词互不相同。 

题目要求将字符串 sss 分割成若干个互不重叠的子字符串（以下简称为子串），同时要求每个子串都必须在 dictionary\textit{dictionary}dictionary 中出现。一些额外的字符可能不属于任何子串，而题目要求最小化这些额外字符的数量。

设 nnn 是 sss 的长度，现在有两种基本的分割方案：

把 sss 的最后一个字符 s[n−1]s[n-1]s[n−1] 当做是额外字符，那么问题转为长度为 n−1n-1n−1 的子问题。
找到一个 jjj 使得 sss 的后缀 s[j...n−1]s[j...n-1]s[j...n−1] 构成的子串在 dictionary\textit{dictionary}dictionary，那么问题转为长度为 j−1j-1j−1 的子问题。
因此，定义 d[i]d[i]d[i] 为 sss 前缀 s[0...i−1]s[0...i-1]s[0...i−1] 的子问题，那么 d[i]d[i]d[i] 取下面两种情况的最小值：

把 s[i−1]s[i-1]s[i−1] 当做是额外字符，d[i]=d[i−1]+1d[i] = d[i - 1] + 1d[i]=d[i−1]+1。
遍历所有的 j(j∈[0,i−1])j(j \in [0, i-1])j(j∈[0,i−1])，如果子字符串 s[j...i−1]s[j...i-1]s[j...i−1] 存在于 dictionary\textit{dictionary}dictionary 中，那么 d[i]=min⁡d[j]d[i] = \min d[j]d[i]=mind[j]。
初始状态 d[0]=0d[0] = 0d[0]=0，最终答案为 d[n]d[n]d[n]。

查找子串 s[j...i−1]s[j...i-1]s[j...i−1] 是否存在于 dictionary\textit{dictionary}dictionary 可以使用哈希表。另外在实现动态规划时，可以使用记忆化搜索，也可以使用递推，这两种方式在时空复杂度方面并没有明显差异。

```cpp
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        vector<int> d(n + 1, INT_MAX);
        unordered_map<string, int> calculated;
        for (auto a : dictionary) {
            calculated[a]++;
        }
        d[0] = 0;
        for (int i = 1; i <= n; i++) {
            d[i] = d[i - 1] + 1;
            for (int j = i - 1; j >= 0; j--) {
                if (calculated.count(s.substr(j, i - j))) {
                    d[i] = min(d[i], d[j]);
                }
            }
        }
        return d[n];
    }
};
```

# 2024/01/11.2645

[2645. 构造有效字符串的最少插入数](https://leetcode.cn/problems/minimum-additions-to-make-valid-string/)

<font color='red'>中等</font>



给你一个字符串 `word` ，你可以向其中任何位置插入 "a"、"b" 或 "c" 任意次，返回使 `word` **有效** 需要插入的最少字母数。

如果字符串可以由 "abc" 串联多次得到，则认为该字符串 **有效** 。

 

**示例 1：**

```
输入：word = "b"
输出：2
解释：在 "b" 之前插入 "a" ，在 "b" 之后插入 "c" 可以得到有效字符串 "abc" 。
```

**示例 2：**

```
输入：word = "aaa"
输出：6
解释：在每个 "a" 之后依次插入 "b" 和 "c" 可以得到有效字符串 "abcabcabc" 。
```

**示例 3：**

```
输入：word = "abc"
输出：0
解释：word 已经是有效字符串，不需要进行修改。 
```

 

**提示：**

- `1 <= word.length <= 50`
- `word` 仅由字母 "a"、"b" 和 "c" 组成。


思路与算法

定义状态 d[i]d[i]d[i] 为将前 iii 个字符（为了方便编码，下标从 111 开始）拼凑成若干个 abc\textit{abc}abc 所需要的最小插入数。那么初始状态 d[0]=0d[0] = 0d[0]=0，最终要求解 d[n]d[n]d[n]，其中 nnn 为 word\textit{word}word 的长度。

转移过程有以下几种情况：

word[i]\textit{word}[i]word[i] 单独存在于一组 abc\textit{abc}abc 中，d[i]=d[i−1]+2d[i] = d[i - 1] + 2d[i]=d[i−1]+2。
如果 word[i]>word[i−1]\textit{word}[i] \gt \textit{word}[i - 1]word[i]>word[i−1]，那么 word[i]\textit{word}[i]word[i] 可以和 word[i−1]\textit{word}[i - 1]word[i−1] 在同一组 abc\textit{abc}abc 中，d[i]=d[i−1]−1d[i] = d[i - 1] - 1d[i]=d[i−1]−1。
d[i]d[i]d[i] 取以上情况的最小值。在本题中，每个字符总是尽可能的与前面的字符去组合，因此情况 222 优于情况 111（从动态转移方程中也可以发现此规律），按照顺序依次更新 d[i]d[i]d[i] 即可，并不需要取最小值。

```cpp
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
```
