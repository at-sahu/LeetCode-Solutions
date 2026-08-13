class Solution {
public:

    struct Node {
        char leftChar, rightChar;
        int left, right, best;
    };

    vector<Node> tree;

    void build(string &s, int v, int l, int r) {
        if (l == r) {
            tree[v] = {s[l], s[l], 1, 1, 1};
            return;
        }

        int mid = (l + r) / 2;

        build(s, v * 2, l, mid);
        build(s, v * 2 + 1, mid + 1, r);

        merge(v, l, r);
    }

    void merge(int v, int l, int r) {

        Node a = tree[v * 2];
        Node b = tree[v * 2 + 1];

        int mid = (l + r) / 2;

        tree[v].leftChar = a.leftChar;
        tree[v].rightChar = b.rightChar;

        tree[v].left = a.left;
        tree[v].right = b.right;

        tree[v].best = max(a.best, b.best);

        if (a.rightChar == b.leftChar) {

            tree[v].best = max(tree[v].best,
                               a.right + b.left);

            if (a.left == mid - l + 1)
                tree[v].left = a.left + b.left;

            if (b.right == r - mid)
                tree[v].right = a.right + b.right;
        }
    }

    void update(int v, int l, int r, int pos, char c) {

        if (l == r) {
            tree[v] = {c, c, 1, 1, 1};
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(v * 2, l, mid, pos, c);
        else
            update(v * 2 + 1, mid + 1, r, pos, c);

        merge(v, l, r);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {

        int n = s.size();

        tree.resize(4 * n);

        build(s, 1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {

            update(1, 0, n - 1,
                   queryIndices[i],
                   queryCharacters[i]);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};