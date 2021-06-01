#include <iostream>
#include <string>
#include <queue>
#include <fstream>
using namespace std;

int num_of_char[256]; // num_of_char['a']=77 意思是'a'出现了77次。
string text;

void get_num_of_char()
{
    for (auto c : text)
    {
        num_of_char[c]++;
    }
}

int Log2(int n) //向上取整的Log2
{
    int ans = 0, temp = 1;
    while (temp < n)
    {
        temp <<= 1;
        ans += 1;
    }
    return ans;
}

int diff_char{};

void get_diff_char() //共有多少个不同的字符
{
    for (auto m : num_of_char)
    {
        if (m)
        {
            diff_char++;
        }
    }
}

int get_fixed_len_code_cost() //定长的花费
{
    if (diff_char == 1)
    {
        return 1;
    }
    return Log2(diff_char) * text.length();
}

struct Node
{
    Node *lchild;
    Node *rchild;
    char c;
    int weight;
};

struct NodeCmp
{
    bool operator()(Node *a, Node *b)
    {
        return a->weight > b->weight;
    }
};

Node *build_node(int weight, char c)
{
    Node *p = new Node;
    p->c = c;
    p->weight = weight;
    p->lchild = p->rchild = nullptr;
    return p;
}

struct code
{
    vector<bool> code_text;
};

Node *build_tree()
{
    priority_queue<Node *, vector<Node *>, NodeCmp> pri_queue;
    for (int i = 0; i < 256; ++i)
    {
        if (num_of_char[i])
        {
            pri_queue.push(build_node(num_of_char[i], i));
        }
    }
    Node *p, *q, *r;
    while (pri_queue.size() >= 2)
    {
        p = pri_queue.top();
        pri_queue.pop();
        q = pri_queue.top();
        pri_queue.pop();
        r = new Node;
        r->lchild = p;
        r->rchild = q;
        r->weight = p->weight + q->weight;
        pri_queue.push(r);
    }
    return r;
}

void fprint_vector_bool(vector<bool> x, ofstream &fs)
{
    for (auto m : x)
    {
        if (m)
        {
            fs.put('1');
        }
        else
        {
            fs.put('0');
        }
    }
}

void print_node(Node *x)
{
    cout << "Node: \nweight: " << x->weight << "\ncharacter: " << x->c << endl;
}

void print_tree(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    print_node(root);
    print_tree(root->lchild);
    print_tree(root->rchild);
}

void get_code(Node *root, vector<code> &table, vector<bool> path) // table['A']=1101
{
    if (root->lchild == nullptr && root->rchild == nullptr)
    {
        table[root->c].code_text = path;
        return;
    }
    path.push_back(1);
    get_code(root->lchild, table, path);
    path.pop_back();

    path.push_back(0);
    get_code(root->rchild, table, path);
}

void print_vector_bool(vector<bool> x)
{
    for (auto m : x)
    {
        if (m)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
}

int main()
{
    getline(cin, text);
    get_num_of_char();
    get_diff_char();
    ofstream fs;
    fs.open("encode.txt");
    int fixed_len_code_cost = get_fixed_len_code_cost();
    if (diff_char == 1) //特殊判断
    {
        for (int i = 1; i <= text.size(); ++i)
        {
            fs << 1;
        }
        cout << 1;
        return 0;
    }
    Node *root = build_tree();
    vector<code> table; //table[char]=code
    table.resize(256);
    vector<bool> path;
    get_code(root, table, path);
    for (int i = 0; i < 256; ++i)
    {
        if (num_of_char[i])
        {
            cout << "char: " << static_cast<char>(i) << " freq: " << num_of_char[i] << endl;
        }
    }
    for (int i = 0; i < 256; ++i)
    {
        if (table[i].code_text.size() > 0)
        {
            cout << "char: " << static_cast<char>(i) << " code: ";
            print_vector_bool(table[i].code_text);
            cout << endl;
        }
    }
    int huffman_cost{};
    for (auto c : text)
    {
        fprint_vector_bool(table[c].code_text, fs);
        huffman_cost += table[c].code_text.size();
    }
    cout << (huffman_cost + 0.0) / (fixed_len_code_cost + 0.0);
}