#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
struct Huffleaf 
{
    char ch;
    int freq;
    Huffleaf* left, *right;
    Huffleaf(char c, int f) 
    {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

struct comparison 
{
    bool operator()(Huffleaf* & l, Huffleaf* & r) 
    {
        if (l->freq>r->freq) 
        {
            return true;
        } 
        else 
        {
            return false;
        }
    }
};

Huffleaf* HuffmanTree(unordered_map<char,int> &frequencies) 
{
    priority_queue<Huffleaf*, vector<Huffleaf*>, comparison> pq;
    for (auto &ele : frequencies) 
    {
        pq.push(new Huffleaf(ele.first, ele.second));
    }
    while (pq.size() > 1) 
    {
        Huffleaf* left = pq.top();
        pq.pop();
        Huffleaf* right = pq.top();
        pq.pop();
        Huffleaf* internalNode = new Huffleaf('\0', left->freq+right->freq);
        internalNode->left = left;
        internalNode->right = right;
        pq.push(internalNode);
    }

    return pq.top();
}

void printcodes(Huffleaf* root, string bin) 
{
    if (root == nullptr) 
    {
        return;
    }
    if (root->ch != '\0') 
    {
        cout <<root->ch<< ": " <<bin<< "\n";
    }
    printcodes(root->left, bin+"0");
    printcodes(root->right, bin+"1");
}

unordered_map<char, int> resmap(string& characters,int* frequencies, int size) 
{
    unordered_map<char, int> fmap;
    for (int i = 0; i < size; i++) 
    {
        fmap[characters[i]] = frequencies[i];
    }
    return fmap;
}

int main() 
{
    string s;
    cin >> s;
    int size = s.length();
    int* f = new int[size];
    for (int i = 0; i < size; ++i) 
    {
        cin >> f[i];
    }
    unordered_map<char, int> finmap = resmap(s, f, size);
    Huffleaf* root = HuffmanTree(finmap);
    cout << "Huffman codes will be:\n";
    printcodes(root, "");
    return 0;
}
