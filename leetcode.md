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