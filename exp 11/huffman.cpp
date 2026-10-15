//Amit Raj
// 25/DA/013

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

// Node of the Huffman Tree
struct Node
{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Compare nodes by frequency
struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->freq > b->freq;
    }
};

// Generate Huffman codes
void generateCodes(Node* root, string code,
                   unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr)
        return;

    // Leaf node represents a character
    if (root->left == nullptr && root->right == nullptr)
    {
        huffmanCode[root->ch] = code.empty() ? "0" : code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Build Huffman Tree and display codes
void huffmanCoding(string text)
{
    if (text.empty())
    {
        cout << "Input text cannot be empty.\n";
        return;
    }

    unordered_map<char, int> frequency;

    // Calculate character frequencies
    for (char ch : text)
        frequency[ch]++;

    // Min-priority queue
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character
    for (auto& pair : frequency)
        pq.push(new Node(pair.first, pair.second));

    // Build the Huffman Tree
    while (pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node('\0',
                                left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;

    // Generate binary codes
    generateCodes(root, "", huffmanCode);

    cout << "\nCharacter Frequencies and Huffman Codes:\n";
    cout << "Character\tFrequency\tCode\n";

    for (auto& pair : frequency)
    {
        char ch = pair.first;

        if (ch == ' ')
            cout << "' '";
        else
            cout << ch;

        cout << "\t\t" << pair.second
             << "\t\t" << huffmanCode[ch] << "\n";
    }

    // Encode the original text
    string encodedText;

    for (char ch : text)
        encodedText += huffmanCode[ch];

    cout << "\nOriginal Text: " << text << "\n";
    cout << "Encoded Text: " << encodedText << "\n";

    cout << "\nOriginal Size: "
         << text.size() * 8 << " bits\n";

    cout << "Encoded Size: "
         << encodedText.size() << " bits\n";

    double compressionRatio =
        (1.0 - (double)encodedText.size() /
         (text.size() * 8)) * 100;

    cout << "Size Reduction: "
         << compressionRatio << "%\n";
}

int main()
{
    string text;

    cout << "Enter the text to compress: ";
    getline(cin, text);

    huffmanCoding(text);

    return 0;
}