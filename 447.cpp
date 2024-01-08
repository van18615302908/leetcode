// 给定平面上 n 对 互不相同 的点 points ，其中 points[i] = [xi, yi] 。回旋镖 是由点 (i, j, k) 表示的元组 ，其中 i 和 j 之间的距离和 i 和 k 之间的欧式距离相等（需要考虑元组的顺序）。返回平面上所有回旋镖的数量。
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


int main() {
    // 示例用法
    Solution solution;
    vector<vector<int>> points1 = {{0,0},{1,0},{2,0}};
    vector<vector<int>> points2 = {{1,1},{2,2},{3,3}};
    vector<vector<int>> points3 = {{1,1}};

    int result1 = solution.numberOfBoomerangs(points1);
    int result2 = solution.numberOfBoomerangs(points2);
    int result3 = solution.numberOfBoomerangs(points3);

    // 输出结果
    cout << "Result 1: " << result1 << endl;
    cout << "Result 2: " << result2 << endl;
    cout << "Result 3: " << result3 << endl;

    return 0;
}
