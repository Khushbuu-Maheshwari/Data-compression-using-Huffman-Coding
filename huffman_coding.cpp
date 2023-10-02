#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;
#define EMPTY_STRING " "

struct Node
{
    char ch;
    int frequency;
    Node *left, *right;
};

Node *getNode(char ch, int frequency, Node *left,
              Node *right)
{
    Node *node = new Node();
    node->ch = ch;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

struct compare
{
    bool operator()(const Node *left, const Node *right)
        const
    {
        // the highest priority item has the lowest frequency
        return left->frequency > right->frequency;
    }
};

// to check if Huffman Tree contains only a single node
bool validLeaf(Node *root)
{
    return root->left == nullptr && root->right == nullptr;
}

void Encode(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
    {
        return;
    }
    if (validLeaf(root))
    {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }
    Encode(root->left, str + "0", huffmanCode);
    Encode(root->right, str + "1", huffmanCode);
}

void Decode(Node *root, int &index, string str)
{
    if (root == nullptr)
    {
        return;
    }
    if (validLeaf(root))
    {
        cout << root->ch;
        return;
    }

    index++;
    if (str[index] == '0')
    {
        Decode(root->left, index, str);
    }
    else
    {
        Decode(root->right, index, str);
    }
}

void HuffmanTree(string symbol)
{
    if (symbol == EMPTY_STRING)
    {
        return;
    }

    unordered_map<char, int> frequency;
    for (char ch : symbol)
    {
        frequency[ch]++;
    }

    priority_queue<Node *, vector<Node *>, compare> pq;
    for (auto pair : frequency)
    {
        pq.push(getNode(pair.first, pair.second, nullptr,
                        nullptr));
    }

    while (pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        int sum = left->frequency + right->frequency;
        pq.push(getNode('\0', sum, left, right));
    }

    Node *root = pq.top();
    unordered_map<char, string> huffmanCode;
    Encode(root, EMPTY_STRING, huffmanCode);

    cout << "Huffman Codes are : \n"
         << endl;
    cout << "== == == == == == == == == == ==" << endl;

    for (auto pair : huffmanCode)
    {
        cout << pair.first << " --> " << pair.second << endl;
    }

    cout << "== == == == == == == == == == ==" << endl;
    cout << "\nThe original string is : \n"
         << symbol << endl;

    // Print encoded string
    string str;
    for (char ch : symbol)
    {
        str += huffmanCode[ch];
    }
    cout << "\nThe encoded string is : \n"
         << str << endl;
    cout << "\nThe decoded string is : \n";

    if (validLeaf(root))
    {
        // Special case : For input like a , aa , aaa , e t c .
        while (root->frequency--)
        {
            cout << root->ch;
        }
    }
    else
    {
        int index = -1;
        while (index < (int)str.size() - 1)
        {
            Decode(root, index, str);
        }
    }
}

int main()
{
    string symbol = "The quick brown fox jumps over the lazy dog";

    HuffmanTree(symbol);
    return 0;
}
