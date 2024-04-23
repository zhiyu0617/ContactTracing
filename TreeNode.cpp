#include <list>

template <typename T>
class TreeNode {
public:
    T medicareId;
    int directContacts = 0;
    int totalCases = 1;
    TreeNode<T>* parentPtr;
    std::list<TreeNode<T>*> directContactsPtrList;

    // Constructors
    TreeNode(const T& medId) : medicareId(medId), parentPtr(nullptr) {}
    TreeNode(TreeNode<T>* parentPtr, const T& medId) : medicareId(medId), parentPtr(parentPtr) {}
};