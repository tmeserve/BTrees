#include <iostream>

using namespace std;

// Reference(s):
// https://www.geeksforgeeks.org/m-way-search-trees-set-1-searching/?ref=rp
// https://www.geeksforgeeks.org/m-way-search-tree-set-2-insertion-and-deletion/

// I chose to have the number 26 to be the max because that's how many numbers are in the alphabet
// Replace 26 with any number to set it to a new max
int const MAX = 3;

int const MIN = 1;

struct Node
{
    int count;
    int value[MAX + 1];
    struct Node *child[MAX + 1];
};

int searchNode(int val, struct Node *n, int *pos)
{
    if (val < n->value[1])
    {
        *pos = 0;
        return 0;
    }

    *pos = n->count;

    while ((val < n->value[*pos]) && *pos > 1)
        (*pos)--;
    if (val == n->value[*pos])
        return 1;
    return 0;
}

struct Node* search(int val, struct Node *root, int *pos)
{
    if (root == NULL)
        return NULL;
    
    if (searchNode(val, root, pos))
        return root;
    
    return search(val, root->child[*pos], pos);
}

void fillNode(int val, struct Node *c, struct Node *n, int k)
{
    int i;

    for (i = n->count; i > k; i--)
    {
        n->value[i + 1] = n->value[i];
        n->child[i + 1] = n->child[i];
    }
    n->value[k + 1] = val;
    n->child[k + 1] = c;
    n->count++;
}

void split(int val, struct Node *c, struct Node *n, int k, int *y, struct Node **newnode)
{
    int i, mid;
    
    if (k <= MIN)
        mid = MIN;
    else
        mid = MIN + 1;

    *newnode = (struct Node*) malloc(sizeof(struct Node));
    for (i = mid + 1; i <= MAX; i++)
    {
        (*newnode)->value[i - mid] = n->value[i];
        (*newnode)->child[i - mid] = n->child[i];
    }

    (*newnode)->count = MAX - mid;
    n->count = mid;

    if (k <= MIN)
        fillNode(val, c, n, k);
    else
        fillNode(val, c, *newnode, k - mid);

    *y = n->value[n->count];
    (*newnode)->child[0] = n->child[n->count];
    n->count--;
}

int setval(int val, struct Node *n, int *p, struct Node **c)
{
    int k;

    if (n == NULL)
    {
        *p = val;
        *c = NULL;
        return 1;
    }

    if (searchNode(val, n, &k))
        printf("Key value already exists\n");

    // cout << "before if\n";
    // cout << "setval val2: " << val << endl;
    if (setval(val, n->child[k], p, c))
    {
        // cout << "setval val: " << val << endl;
        // if (val == 2)
        // {
        //     cout << "setval *p: " << *p << endl;
        // }
        if (n->count < MAX)
        {
            fillNode(*p, *c, n, k);
            // if (val == 2)
            // {
            //     cout << "setval *p: " << *p << endl;
            // }
            return 0;
        }
        split(*p, *c, n, k, p, c);
        // if (val == 2)
        // {
        //     cout << "setval *p: " << *p << endl;
        // }
        return 1;
    }
    return 0;
}

struct Node* insert(int val, struct Node *root)
{
    int i;
    struct Node *c, *n;
    int flag;

    flag = setval(val, root, &i, &c);

    if (flag)
    {
        n = (struct Node*) malloc(sizeof(struct Node));
        n->count = 1;
        n->value[1] = i;
        n->child[0] = root;
        n->child[1] = c;
        return n;
    }

    return root;
}

void rightshift(struct Node *m, int k)
{
    int i;
    struct Node *temp;
    temp = m->child[k];

    for (i = temp->count; i > 0; i--)
    {
        temp->value[i + 1] = temp->value[i];
        temp->child[i + 1] = temp->child[i];
    }
    temp->child[1] = temp->child[0];
    temp->count++;
    temp->value[1] = m->value[k];

    temp = m->child[k - 1];
    m->value[k] = temp->value[temp->count];
    m->child[k]->child[0] = temp->child[temp->count];
    temp->count--;
}

void leftshift(struct Node *m, int k)
{
    int i;
    struct Node *temp;
    
    temp = m->child[k - 1];
    temp->count++;
    temp->value[temp->count] = m->value[k];
    temp->child[temp->count] = m->child[k]->child[0];

    temp = m->child[k];
    m->value[k] = temp->value[1];
    temp->child[0] = temp->child[1];
    temp->count--;

    for (i = 1; i <= temp->count; i++)
    {
        temp->value[i] = temp->value[i + 1];
        temp->child[i] = temp->child[i + 1];
    }
}

void merge(struct Node *m, int k)
{
    int i;
    struct Node *temp1, *temp2;

    temp1 = m->child[k];
    temp2 = m->child[k - 1];
    temp2->count++;
    temp2->value[temp2->count] = m->value[k];
    temp2->child[temp2->count] = m->child[0];

    for (i = 0; i <= temp1->count; i++)
    {
        temp2->count++;
        temp2->value[temp2->count] = temp1->value[i];
        temp2->child[temp2->count] = temp1->child[i];
    }

    for (i = k; i < m->count; i++)
    {
        m->value[i] = m->value[i + 1];
        m->child[i] = m->child[i + 1];
    }
    m->count--;
    free(temp1);
}

void clear(struct Node *m, int k)
{
    int i;
    for (i = k + 1; i <= m->count; i++)
    {
        m->value[i - 1] = m->value[i];
        m->child[i - 1] = m->child[i];
    }
    m->count--;
}

void copysucc(struct Node *m, int i)
{
    struct Node *temp;
    temp = m->child[i];
    while (temp->child[0])
        temp = temp->child[0];
    m->value[i] = temp->value[i];
}

void restore(struct Node *m, int i)
{
    if (i == 0)
    {
        if (m->child[1]->count > MIN)
            leftshift(m, 1);
        else
            merge(m, 1);
    }
    else
    {
        if (i == m->count)
        {
            if (m->child[i - 1]->count > MIN)
                rightshift(m, i);
            else
                merge(m, i);
        }
        else
        {
            if (m->child[i - 1]->count > MIN)
                rightshift(m, i);
            else
            {
                if (m->child[i + 1]->count > MIN)
                    leftshift(m, i);
                else
                    merge(m, i);
            }
        }
        
    }
    
}

int delhelp(int val, struct Node *root)
{
    int i;
    int flag;
    if (root == NULL)
        return 0;
    else
    {
        flag = searchNode(val, root, &i);

        if (flag)
        {
            if (root->child[i - 1])
            {
                copysucc(root, i);
                flag = delhelp(root->value[i], root->child[i]);

                if (!flag)
                {
                    printf("\n");
                    printf("value %d not found.\n", val);
                }
            }
            else
                clear(root, i);
            
        }
        else
            flag = delhelp(val, root->child[i]);

        if (root->child[i] != NULL)
        {
            if (root->child[i]->count < MIN)
                restore(root, i);
        }
        return flag;
    }
}

struct Node* del(int val, struct Node *root)
{
    struct Node *temp;
    if (!delhelp(val, root))
    {
        printf("\n");
        printf("value %d not found.\n", val);
    }
    else
    {
        if (root->count == 0)
        {
            temp = root;
            root = root->child[0];
            free(temp);
        }
    }
    return root;
}

void print(Node *p)
{
    for (int val : p->value)
    {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    struct Node *root = new Node();

    root = insert(3, root);
    root = insert(6, root);
    root = insert(7, root);
    // root = insert(2, root);

    Node *child = root->child[1];

    child = insert(2, child);

    // for (int val : child->value)
    // {
    //     cout << "child val: " << val << endl;
    // }

    // for (int val : root->value)
    // {
    //     cout << "val: " << val << endl;
    //     for (Node *kid : child->child)
    //     {
    //         // for (int cval : kid->value)
    //         // {
    //         //     cout << "cval: " << cval << endl;
    //         // }
    //     }
    // }

    // int value = child->value[1];

    // cout << "rvalue: " << rvalue << endl;
    // cout << value << endl;
}