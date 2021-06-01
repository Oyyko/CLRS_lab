#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

enum color
{
    RED,
    BLACK
};

struct TNode
{
    color c;
    int key;
    TNode *left;
    TNode *right;
    TNode *P;
};

string color_string(TNode *x)
{
    return x->c == RED ? "RED"s : "BLACK"s;
}

void print_node_info(TNode *x)
{
    cout << endl;
    cout << "info self: " << x->key << color_string(x) << endl;
    cout << "info P: " << x->P->key << color_string(x->P) << endl;
    cout << "info l: " << x->left->key << color_string(x->left) << endl;
    cout << "info r: " << x->right->key << color_string(x->right) << endl;
    cout << endl;
}

void LEFT_ROTATE(TNode *&root, TNode *x)
{
    TNode *nil = root->P;
    TNode *y = x->right;
    x->right = y->left;
    if (y->left != nil)
    {
        y->left->P = x;
    }
    y->P = x->P;
    if (x->P == nil)
    {
        root = y;
    }
    else if (x == x->P->left)
    {
        x->P->left = y;
    }
    else
    {
        x->P->right = y;
    }
    y->left = x;
    x->P = y;
}

void RIGHT_ROTATE(TNode *&root, TNode *x)
{
    TNode *nil = root->P;
    TNode *y = x->left;
    x->left = y->right;
    if (y->right != nil)
    {
        y->right->P = x;
    }
    y->P = x->P;
    if (x->P == nil)
    {
        root = y;
    }
    else if (x == x->P->right)
    {
        x->P->right = y;
    }
    else
    {
        x->P->left = y;
    }
    y->right = x;
    x->P = y;
}

TNode *make_node(int key)
{
    TNode *res = (TNode *)malloc(sizeof(TNode));
    res->c = RED;
    res->key = key;
    res->left = res->right = res->P = nullptr;
    return res;
}

void RB_INSERT_FIXUP(TNode *&root, TNode *z)
{
    TNode *y;
    while (z->P->c == RED)
    {
        if (z->P == z->P->P->left)
        {
            y = z->P->P->right;
            if (y->c == RED)
            {
                z->P->c = BLACK;
                y->c = BLACK;
                z->P->P->c = RED;
                z = z->P->P;
                continue;
            }
            else if (z == z->P->right)
            {
                z = z->P;
                LEFT_ROTATE(root, z);
            }

            {
                z->P->c = BLACK;
                z->P->P->c = RED;
                RIGHT_ROTATE(root, z->P->P);
            }
        }
        else
        {
            y = z->P->P->left;
            if (y->c == RED)
            {
                z->P->c = BLACK;
                y->c = BLACK;
                z->P->P->c = RED;
                z = z->P->P;
                continue;
            }
            else if (z == z->P->left)
            {
                z = z->P;
                RIGHT_ROTATE(root, z);
            }

            {
                z->P->c = BLACK;
                z->P->P->c = RED;
                LEFT_ROTATE(root, z->P->P);
            }
        }
    }
    root->c = BLACK;
}

void RB_INSERT(TNode *&root, TNode *z)
{
    TNode *nil = root->P;
    auto y = nil;
    auto x = root;
    while (x != nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->P = y;
    if (y == nil)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->c = RED;
    RB_INSERT_FIXUP(root, z);
}

TNode *generate_empty_RBTree()
{
    TNode *nil = (TNode *)malloc(sizeof(TNode));
    nil->c = BLACK;
    nil->key = -114514;
    nil->left = nil->right = nil->P = nil;
    return nil;
}

void NLR(TNode *rootnow, TNode *nil)
{
    if (rootnow == nil)
    {
        return;
    }
    cout << rootnow->key << "," << color_string(rootnow) << endl;
    //print_node_info(rootnow);
    NLR(rootnow->left, nil);
    NLR(rootnow->right, nil);
}

void LNR(TNode *rootnow, TNode *nil)
{
    if (rootnow == nil)
    {
        return;
    }
    LNR(rootnow->left, nil);
    cout << rootnow->key << "," << color_string(rootnow) << endl;
    //print_node_info(rootnow);
    LNR(rootnow->right, nil);
}

int main()
{
    streambuf *backup;
    ifstream fin;
    fin.open("insert.txt");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    int n;
    cin >> n;
    int key;
    TNode *now;
    TNode *root = generate_empty_RBTree();
    print_node_info(root);
    for (int temp = 1; temp <= n; ++temp)
    {
        cin >> key;
        now = make_node(key);
        RB_INSERT(root, now);
        //print_node_info(root);
    }

    ofstream fout1, fout2;
    fout1.open("NLR.txt");
    cout.rdbuf(fout1.rdbuf());
    NLR(root, root->P);
    fout2.open("LNR.txt");
    cout.rdbuf(fout2.rdbuf());
    //cout << "ROOT:";
    //print_node_info(root);
    LNR(root, root->P);
}