/* Binary Tree
*/

class BinaryTree 
{
private:
    struct node 
    {
        int data;
        int height;
        node* left;
        node* right;
        node(const int& rVal) : data(rVal),
                                height(0),
                                left(nullptr),
                                right(nullptr) {}; 
        // deep copy
        node(const node* other) : data(other->data), height(other->height) 
        {
            left = (other->left) ? new node(other->left) : nullptr;
            right = (other->right) ? new node(other->right) : nullptr;
        }
    };

public:
    BinaryTree() : _root(nullptr), _size (0) {};
    ~BinaryTree() {_deleteBranch(_root);}

    // insertion
    void insert(const int& value);

    // deletion
    bool remove(const int& value);

    // search
    bool contains(const int& value);

    // traversal


    //getter
    int size() {return _size;}
    int height() {return _height(_root);}

    void printTree();

private:
    // helper functions
    // rotate
    node* _rotateRight(node* root);
    node* _rotateLeft(node* root);

    // balance
    int _balanceFactor(node* root);
    node* _rebalance(node* root);

    // height
    int _height(node* root) { return ((root == nullptr) ? 0 : root->height); }

    // abstract node away from user
    node* _insertNode(node* root, const int& value);
    node* _removeNode(node* root, const int& value);
    bool _containsNode(node* root, const int& value);

    node* _popBiggest(node*& root);
    node* _popSmallest(node* root);
    void _deleteBranch(node* root);

    void _printTree(node* root, int level, int indentSpace);

private:
    node* _root;
    int _size;
};

