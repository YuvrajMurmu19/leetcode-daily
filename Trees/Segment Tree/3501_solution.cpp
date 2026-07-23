/*
    Approach:
    - Preprocess all contiguous zero blocks and store their start indices, end indices,
      and lengths.
    - Build an array containing the sum of every pair of adjacent zero blocks and
      construct a Segment Tree over it to support range maximum queries.
    - For each query, use binary search (lower_bound/upper_bound) to locate the
      first and last zero blocks intersecting the query range.
    - Handle the boundary zero blocks separately and use the Segment Tree to find
      the maximum contribution from the fully contained middle zero blocks.
    - Add the maximum possible gain to the initial count of active sections.

    T.C. : O(n + q log n)
    S.C. : O(n)
*/
class Solution {
public:
    void build(int node, int left, int right, vector<int>& segTree, vector<int>& values) {
        if (left == right) {
            segTree[node] = values[left];
            return;
        }

        int mid = left + (right - left) / 2;

        build(2 * node + 1, left, mid, segTree, values);
        build(2 * node + 2, mid + 1, right, segTree, values);

        segTree[node] = max(segTree[2 * node + 1], segTree[2 * node + 2]);
    }

    int query(int start, int end, int node, int left, int right, vector<int>& segTree) {
        if (left > end || right < start) {
            return INT_MIN;
        }

        if (left >= start && right <= end) {
            return segTree[node];
        }

        int mid = left + (right - left) / 2;

        return max(
            query(start, end, 2 * node + 1, left, mid, segTree),
            query(start, end, 2 * node + 2, mid + 1, right, segTree)
        );
    }

    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int numOfOnes = 0;
        for (char ch : s) {
            if (ch == '1') {
                numOfOnes++;
            }
        }

        vector<int> zeroStart;
        vector<int> zeroEnd;

        int index = 0;
        while (index < n) {
            if (s[index] == '0') {
                int start = index;
                while (index < n && s[index] == '0') {
                    index++;
                }
                zeroStart.push_back(start);
                zeroEnd.push_back(index - 1);
            } else {
                index++;
            }
        }

        int totalBlocks = zeroStart.size();
        if (totalBlocks < 2) {
            return vector<int>(queries.size(), numOfOnes);
        }
        vector<int> zeroBlockLength(totalBlocks);

        for (int i = 0; i < totalBlocks; i++) {
            zeroBlockLength[i] = zeroEnd[i] - zeroStart[i] + 1;
        }

        int pairCount = totalBlocks - 1;
        vector<int> adjacentSum(pairCount);
        for (int i = 0; i < pairCount; i++) {
            adjacentSum[i] = zeroBlockLength[i] + zeroBlockLength[i + 1];
        }

        vector<int> segTree(4 * pairCount);
        build(0, 0, pairCount - 1, segTree, adjacentSum);
        vector<int> answer;

        for (auto& queryRange : queries) {
            int left = queryRange[0];
            int right = queryRange[1];
            int firstBlock = lower_bound(zeroEnd.begin(), zeroEnd.end(), left) - zeroEnd.begin();
            int lastBlock = upper_bound(zeroStart.begin(), zeroStart.end(), right) - zeroStart.begin() - 1;

            int bestGain = 0;

            if (firstBlock < lastBlock) {
                int leftPart = zeroEnd[firstBlock] - max(zeroStart[firstBlock], left) + 1;
                int rightPart = min(zeroEnd[lastBlock], right) - zeroStart[lastBlock] + 1;

                if (lastBlock - firstBlock == 1) {
                    bestGain = leftPart + rightPart;
                } else {
                    int option1 = leftPart + zeroBlockLength[firstBlock + 1];
                    int option2 = zeroBlockLength[lastBlock - 1] + rightPart;
                    int option3 = query(firstBlock + 1, lastBlock - 2, 0, 0, pairCount - 1, segTree);
                    bestGain = max({option1, option2, option3});
                }
            }
            answer.push_back(numOfOnes + bestGain);
        }

        return answer;
    }
};