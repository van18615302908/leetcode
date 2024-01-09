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

