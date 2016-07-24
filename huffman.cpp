#include <iostream>
#include <queue>
using namespace std;

// A: 6 B: 5 C: 10 D: 2 E: 4
// 把节点按照频率放到priority_queue(最小堆)中, 
// 然后依次取出顶部最小的两个节点, 合并成一个节点,
// 再放到最小堆中, 直到堆中只有一个节点

typedef struct huffmannode {
    char sym;
    int val;
    struct huffmannode *left;
    struct huffmannode *right;
} hfnode;

class mycomp {
public:
    bool operator() (hfnode *h1, hfnode *h2) {
        return h1->val > h2->val;
    }
};

void dfs(hfnode *hfn, string s) {
    if (hfn->right == nullptr && hfn->left == nullptr) {
        cout << hfn->sym  << ":" << s << endl;
        return;
    }
    if (hfn->right) {
        dfs(hfn->right, s + "1");
    }
    if (hfn->left) {
        dfs(hfn->left, s + "0");
    }
}

void huffman(hfnode *hfn, int size) {
    priority_queue<hfnode*, vector<hfnode*>, mycomp> pq;
    hfnode *hres;
    for (int i = 0; i < size; i++) {
        pq.push(&hfn[i]);
    }
    while (pq.size() > 1) {
        hfnode *hf1 = pq.top();
        pq.pop();
        hfnode *hf2 = pq.top();
        pq.pop();
        hfnode *hfnews = new hfnode{'~', hf1->val + hf2->val, hf1, hf2};
        pq.push(hfnews);
    }
    hres = pq.top();
    dfs(hres, "");
}

int main() {
    hfnode hfn[5] = {{'A', 6, nullptr, nullptr}, {'B', 5, nullptr, nullptr},
                     {'C', 10, nullptr, nullptr}, {'D', 2, nullptr, nullptr},
                     {'E', 4, nullptr, nullptr}};
    huffman(hfn, sizeof(hfn)/sizeof(hfnode)); // 构建huffman树
    return 0;
}
