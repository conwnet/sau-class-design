#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 二叉搜索树
struct Tree {
    string value; // 存一行字
    Tree *left, *right; // 二叉树左右节点
    vector<string> result; // 保存搜索结果

    // 构造函数
    Tree (string value) :
        value (value), left (0), right (0) {}
    
    // 插入操作
    void insert(string str) {
        // 根据二叉搜索树性质，判断是插入到左面还是右面
        if (str < this->value) {
            if (this->left)
                this->left->insert(str);
            else
                this->left = new Tree(str);
        } else {
            if (this->right)
                this->right->insert(str);
            else
                this->right = new Tree(str);
        }
    }

    // 二叉搜索树搜索操作
    // key 是要查询的字符串
    vector<string> search(string key) {
        Tree *p = this;
        // 根据 key 和当前节点的大小比较
        // 是去左孩子查找还是右孩子查找
        while(p && (p->left || p->right)) {
            if (p->value.find(key) == 0)
                break;
            if (key < p->value)
                p = p->left;
            else
                p = p->right;
        }
        this->result.clear();
        // 找到了第一个符合 key 的节点
        // 接下来 dfs 求出所有以 key 开头的节点
        if (p) dfs(p, key);
        return this->result;
    }

    // 深度优先遍历，求出所有以 key 开头的节点
    void dfs(Tree *node, string key) {
        if (node->value.find(key) == 0)
            this->result.push_back(node->value);
        if (node->left)
            dfs(node->left, key);
        if (node->right)
            dfs(node->right, key);
    }
};

int main()
{
    char line[1024];
    Tree *tree = new Tree("");
    FILE *fp = fopen("data.txt", "r");

    if (!fp) {
        printf("文件打开失败！");
        return 0;
    }

    // 从文件中读取所有数据
    while (fgets(line, 1024, fp))
        tree->insert(line);
   
    printf("读取文件完成！\n");
    printf("请输入一个索引进行查询：\n");
    while(scanf("%s", line)) {
        if (string(line) == "exit")
            break;
        vector<string> result = tree->search(line);
        printf("查询结果如下：\n");
        for (int i = 0; i < result.size(); i++) {
            printf("\t%s\n", result[i].c_str());
        }
        printf("----------------\n\n");
        printf("请输入一个索引进行查询：\n");
    }

    return 0;
}





