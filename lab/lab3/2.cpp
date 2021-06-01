#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

enum color
{
    RED,
    BLACK
};

struct Interval
{
    int low;
    int high;
};

bool operator<(const Interval &a, const Interval &b)
{
    return a.low < b.low;
} // compare Interval

struct TNode
{
    color c;
    Interval key;
    int max;
    TNode *left;
    TNode *right;
    TNode *P;
};

ostream &operator<<(ostream &os, const Interval &x)
{
    os << "low: " << x.low << " high: " << x.high << " ";
    return os;
} // print Interval

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
    cout << "info max: " << x->max << endl;
    cout << endl;
}

void cal_max(TNode *x)
{
    x->max = max(max(x->key.high, x->left->max), x->right->max);
}

void cal_max_to_root(TNode *x, TNode *nil)
{
    while (x != nil)
    {
        cal_max(x);
        x = x->P;
    }
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

    cal_max(y);
    cal_max(x);
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

    cal_max(y);
    cal_max(x);
}

TNode *make_node(Interval key) //make a new node
{
    TNode *res = (TNode *)malloc(sizeof(TNode));
    res->c = RED;
    res->key = key;
    res->left = res->right = res->P = nullptr;
    res->max = key.high;
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
                //cout << "LEFT: ";
                //print_node_info(z);
                //print_node_info(z->P);
                //print_node_info(z->P->P);
            }

            {
                z->P->c = BLACK;
                z->P->P->c = RED;
                RIGHT_ROTATE(root, z->P->P);
                //cout << "RIGHT: ";
                //print_node_info(z);
                //print_node_info(z->P);
                //print_node_info(z->P->P);
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

    cal_max_to_root(z, root->P);
    RB_INSERT_FIXUP(root, z);
}

TNode *generate_empty_RBTree() // generate the node nil
{
    TNode *nil = (TNode *)malloc(sizeof(TNode));
    nil->c = BLACK;
    nil->key = {-114514, -114514};
    nil->left = nil->right = nil->P = nil;
    nil->max = -114514;
    return nil;
}

void NLR(TNode *rootnow, TNode *nil)
{
    if (rootnow == nil)
    {
        return;
    }
    cout << rootnow->key << "," << color_string(rootnow) << ",max: " << rootnow->max << endl;
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
    cout << rootnow->key << "," << color_string(rootnow) << ",max: " << rootnow->max << endl;
    //print_node_info(rootnow);
    LNR(rootnow->right, nil);
}

bool is_overlap(Interval x, Interval y) // judge if they are overlapped
{
    if (x.high < y.low || y.high < x.low)
    {
        return false;
    }
    return true;
}

TNode *INTERVAL_SEARCH(TNode *root, Interval i) // find an Interval of the tree which overlap with i
{
    TNode *x = root;
    TNode *nil = root->P;
    while (x != nil && (is_overlap(x->key, i) == false))
    {
        if (x->left != nil && x->left->max >= i.low)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return x;
}

int main()
{
    streambuf *backup_cin, *backup_cout;
    ifstream fin;
    fin.open("in");
    backup_cin = cin.rdbuf();
    backup_cout = cout.rdbuf();
    cin.rdbuf(fin.rdbuf());

    int n;
    cin >> n;
    Interval x;
    TNode *now;
    TNode *root = generate_empty_RBTree();
    for (int temp = 1; temp <= n; ++temp)
    {
        cin >> x.low >> x.high;
        now = make_node(x);
        RB_INSERT(root, now);
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

    int low, high;
    cin.rdbuf(backup_cin);
    cout.rdbuf(backup_cout);
    cout << "INPUT [low,high]: " << endl;
    cin >> low >> high;
    Interval xx{low, high};
    TNode *m = INTERVAL_SEARCH(root, xx);
    if (m == root->P)
    {
        cout << "Not Found" << endl;
    }
    else
    {
        cout << m->key;
    }
}