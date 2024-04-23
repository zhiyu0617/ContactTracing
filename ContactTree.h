#include "Queue.cpp"
#include "TreeNode.cpp"

template <typename T>
class ContactTree {
private:
    TreeNode<T>* root;

    void updateTotalCases(TreeNode<T>* node);
    TreeNode<T>* findNode(const T& medId);
    void deleteSubtree(TreeNode<T>* node);
    void printHierarchicalTree(TreeNode<T>* node);

public:
    ContactTree();
    ~ContactTree();
    bool IsEmpty();
    int GetSize();
    void AddPatient0(const T& medId);
    void AddContact(const T& parentMedId, const T& childMedId);
    TreeNode<T>* LookUpContact(const T& medId);
    void DeleteContact(const T& medId);
    void DisplayContact(const T& medId);
    void DisplayContact(TreeNode<T>* node);
    void TraceSource(const T& medId);
    void PrintContactCases(const T& medId);
    void PrintContactTree();
    void PrintHierarchicalTree();
};