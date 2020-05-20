#include <iostream>
#include <queue>
#include <unordered_map>

// Reference:
// https://www.geeksforgeeks.org/iterative-approach-to-check-if-two-binary-trees-are-isomorphic-or-not/?ref=rp

using namespace std;

struct Node
{
    int data;
    struct Node *left, *right;
};

bool isIsomorphic(Node *root1, Node *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;
    else if (root1 == NULL || root2 == NULL)
        return false;
    
    queue<Node *> q1, q2;
    q1.push(root1);
    q2.push(root2);

    int level = 0;
    int size;

    vector<int> v2;

    unordered_map<int, int> mp;

    while (!q1.empty() && !q1.empty())
    {
        if (q1.size() != q2.size())
            return false;
        
        size = q1.size();

        level++;
        v2.clear();
        mp.clear();

        while (size--)
        {
            Node *temp1 = q1.front();
            Node *temp2 = q2.front();

            q1.pop();
            q2.pop();

            if (mp.find(temp1->data) == mp.end())
                mp[temp1->data] = 1;
            else
                mp[temp1->data]++;

            v2.push_back(temp2->data);
            
            if (temp1->left)
                q1.push(temp1->left);
            if (temp1->right)
                q1.push(temp2->right);
            if (temp2->left)
                q2.push(temp2->left);
            if (temp2->right)
                q2.push(temp2->right);
        }

        for (auto i : v2)
        {
            if (mp.find(i) == mp.end())
                return false;
            
            mp[i]--;
            
            if (mp[i] < 0)
                return false;
            else if (mp[i] == 0)
                mp.erase(i);
        }

        if (mp.size() != 0)
            return false;
    }
    return true;
}

Node* newNode(int data)
{
    Node *temp = (struct Node*) malloc(sizeof(struct Node*));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

int main()
{
    struct Node *n1 = newNode(1);
    n1->left = newNode(2);
    n1->right = newNode(3);
    n1->left->left = newNode(4);
    n1->left->right = newNode(5);
    n1->right->left = newNode(6);
    n1->left->right->left = newNode(7);
    n1->left->right->right = newNode(8);

    struct Node *n2 = newNode(1);
    n2->left = newNode(3);
    n2->right = newNode(2);
    n2->right->left = newNode(4);
    n2->right->right = newNode(5);
    n2->left->right = newNode(6);
    n2->right->right->left = newNode(8);
    n2->right->right->right = newNode(7);

    if (isIsomorphic(n1, n2))
        cout << "The 2 Binary Trees given are isomorphic\n";
    else
        cout << "The 2 Binary Trees given are not isomorphic\n";
    
}