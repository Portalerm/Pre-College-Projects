#pragma once
#include "TreeNode.h"
#include <iostream>
#include<vector>
class BST
{
public:
    TreeNode* root;
    BST()
    {
        root = nullptr;
    }

    void insert(int v)
    {
        if (root == nullptr)
        {
            root = new TreeNode(v);
            return;
        }

        TreeNode* cur = root;
        while (cur != nullptr)
        {
            if (v > cur->val)
            {
                if (cur->right != nullptr)
                    cur = cur->right;
                else
                {
                    cur->right = new TreeNode(v);
                    return;
                }
            }
            else
            {
                if (cur->left != nullptr)
                    cur = cur->left;
                else
                {
                    cur->left = new TreeNode(v);
                    return;
                }
            }
        }
    }


    void print(TreeNode* cur)
    {
        if (cur == nullptr)
            return;
        print(cur->left);
        std::cout << cur->val << std::endl;
        print(cur->right);
    }

    void toVectorHelper(TreeNode* cur, std::vector<int>& scores)
    {
        if (cur == nullptr)
            return;
        toVectorHelper(cur->left, scores);
        scores.push_back(cur->val);
        toVectorHelper(cur->right, scores);
    }

    std::vector<int> toVector()
    {
        std::vector<int> scores;
        toVectorHelper(root, scores);
        return scores;
    }


};