#include <iostream>
#include <queue>
#include <list>
using namespace std;

template <typename T>
class TreeNode {
public:
    T medicareId;
    int directContacts = 0;
    int totalCases = 1;
    TreeNode<T>* parentPtr;
    list<TreeNode<T>*> directContactsPtrList;

    // Constructors
    TreeNode(const T& medId) : medicareId(medId), parentPtr(nullptr) {}
    TreeNode(TreeNode<T>* parentPtr, const T& medId) : medicareId(medId), parentPtr(parentPtr) {}
};

template <typename T>
class ContactTree {
private:
    TreeNode<T>* root;

    TreeNode<T>* findNode(const T& medId) {
        //check if tree empty
        if (root == nullptr)
            return nullptr;

        //using queue
        queue<TreeNode<T>*> nodesQueue;
        nodesQueue.push(root);

        //traverse the lists (breadth first search traversal) until all nodes are checked
        while (!nodesQueue.empty()) {
            TreeNode<T>* current = nodesQueue.front();
            nodesQueue.pop();

            if (current->medicareId == medId) {
                return current; // found node
            }

            //add all direct contacts of the curent node to the queue
            for (TreeNode<T>* child : current->directContactsPtrList) {
                nodesQueue.push(child);
            }
        }

        return nullptr; // no match
    }

    void deleteSubtree(TreeNode<T>* node) {
        
        if (node == nullptr) return;

        // initialize queue
        queue<TreeNode<T>*> nodesQueue;

        //node(root of subtree)
        nodesQueue.push(node);

        // keep looping until queue empty (breadth-first search) traversal
        while (!nodesQueue.empty()) {

            // first node gets dequeued and assigned to a pointer (current)
            TreeNode<T>* current = nodesQueue.front();
            nodesQueue.pop();

            // each child node (pointers in directContactsPtrList) of current are added to nodesQueue
            for (TreeNode<T>* child : current->directContactsPtrList) {
                nodesQueue.push(child);
            }

            delete current;
        }
    }

    void printHierarchicalTree(TreeNode<T>* node) {
        if (node == nullptr) return;

        cout << node->medicareId << endl;

        for (TreeNode<T>* child : node->directContactsPtrList) {
            printHierarchicalTree(child);
        }
    }

public:
    // Constructor
    ContactTree() : root(nullptr) {}

    // Destructor
    ~ContactTree() {
        if (root != nullptr) {
            deleteSubtree(root);
        }
    }

    // Method to check if the tree is empty
    bool IsEmpty() {
        return root == nullptr;
    }

    // Method to get the size of the tree
    int GetSize() {
        int size = 0;
        queue<TreeNode<T>*> nodesQueue;

        //check if not empty
        if (root != nullptr) {
            nodesQueue.push(root);
        }

        // keep looping until queue empty (breadth-first search) traversal
        while (!nodesQueue.empty()) {

            // first node gets dequeued and assigned to a pointer (current)
            TreeNode<T>* current = nodesQueue.front();
            nodesQueue.pop();
            //update
            size++;

            // each child node (pointers in directContactsPtrList) of current are added to nodesQueue
            for (TreeNode<T>* child : current->directContactsPtrList) {
                nodesQueue.push(child);
            }
        }

        return size;
    }

    // Method to add patient zero
    void AddPatient0(const T& medId) {
        //check if exist already
        if (root != nullptr) {
            cout << "Patient 0 already exists." << endl;
            return;
        }
        
        //create new treenode 
        root = new TreeNode<T>(medId);
    }

    // Method to add contact between two nodes
    void AddContact(const T& parentMedId, const T& childMedId) {
        //find parent node in the tree
        TreeNode<T>* parentNode = findNode(parentMedId);
        if (parentNode == nullptr) {
            cout << "Parent with medicare ID " << parentMedId << " not found." << endl;
            return;
        }

        //create new node(child) and add to parent's list of direct contacts
        TreeNode<T>* childNode = new TreeNode<T>(parentNode, childMedId);
        parentNode->directContactsPtrList.push_back(childNode);

        //update contacts/cases
        parentNode->directContacts++;
        updateTotalCases(parentNode);
    }

    // Method to look up a contact by medicare ID
    TreeNode<T>* LookUpContact(const T& medId) {
        return findNode(medId);
    }

    // Method to delete a contact and its subtree
    void DeleteContact(const T& medId) {
        //find node to delete
        TreeNode<T>* nodeToDelete = findNode(medId);
        if (nodeToDelete == nullptr) {
            cout << "Contact with medicare ID " << medId << " not found." << endl;
            return;
        }

        // If the node to delete is the root
        if (nodeToDelete == root) {
            deleteSubtree(root);
            root = nullptr; // Update root pointer to indicate an empty tree
            return;
        }

        // once node to delete found, check if it has parent node so we can remove it from parents list of direct contacts
        TreeNode<T>* parent = nodeToDelete->parentPtr;
        if (parent != nullptr) {

            //i had to look up online
            typename list<TreeNode<T>*>::iterator it;
            // we have to do this in order to inform compiler that the line above is a type and not a variable
            //iterate tru the list of nodes(child) of the parent
            for (it = parent->directContactsPtrList.begin(); it != parent->directContactsPtrList.end(); ++it) {
                if (*it == nodeToDelete) {
                    parent->directContactsPtrList.erase(it);
                    //update
                    parent->directContacts--;
                    updateTotalCases(parent);
                    break; // Stop searching once found
                }
            }
        }

        deleteSubtree(nodeToDelete);
    }


    // Method to display contact information by medicare ID
    void DisplayContact(const T& medId) {
        TreeNode<T>* node = findNode(medId);
        if (node == nullptr) {
            cout << "Contact with medicare ID " << medId << " not found." << endl;
            return;
        }
        DisplayContact(node);
    }

    // Method to display contact information by TreeNode pointer
    void DisplayContact(TreeNode<T>* node) {
        cout << "Medicare ID: " << node->medicareId << endl;
        cout << "Direct Contacts: " << node->directContacts << endl;
        cout << "Total Cases: " << node->totalCases << endl;
    }

    // Method to trace the source of infection given a medicare ID
    void TraceSource(const T& medId) {
        TreeNode<T>* node = findNode(medId);
        if (node == nullptr) {
            cout << "Contact with medicare ID " << medId << " not found." << endl;
            return;
        }
        
        //if node found, initialize pointer for node
        TreeNode<T>* current = node;

        //keep going until it reaches the root/parent
        while (current != nullptr) {
            DisplayContact(current);
            current = current->parentPtr;
        }
    }

    // Method to print contact cases given a medicare ID
    void PrintContactCases(const T& medId) {
        TreeNode<T>* node = findNode(medId);
        if (node == nullptr) {
            cout << "Contact with medicare ID " << medId << " not found." << endl;
            return;
        }

        for (TreeNode<T>* contact : node->directContactsPtrList) {
            DisplayContact(contact);
        }
    }

    // Method to print the entire contact tree using BFS
    void PrintContactTree() {

        //make a queue
        queue<TreeNode<T>*> nodesQueue;

        if (root != nullptr) {
            nodesQueue.push(root);
        }


        while (!nodesQueue.empty()) {
            //dequeue the first node and store it in pointer current
            TreeNode<T>* current = nodesQueue.front();
            nodesQueue.pop();

            DisplayContact(current);

            //then keep looping through each child node of current and add it to the queue
            for (TreeNode<T>* child : current->directContactsPtrList) {
                nodesQueue.push(child);
            }
        }
    }

    // Method to print hierarchical tree
    void PrintHierarchicalTree() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        printHierarchicalTree(root);
    }

private:
    // function to update totalCases up the tree
    void updateTotalCases(TreeNode<T>* node) {
        while (node != nullptr) {
            node->totalCases++;
            node = node->parentPtr;
        }
    }
};
//
//int main() {
//    // Testing the ContactTree class with string values
//    ContactTree<string> tree;
//
//    // add patient zero
//    tree.AddPatient0("A");
//
//    // add contacts
//    tree.AddContact("A", "B");
//    tree.AddContact("A", "C");
//    tree.AddContact("B", "D");
//    tree.AddContact("B", "E");
//    tree.AddContact("C", "F");
//
//    // contact information
//    tree.DisplayContact("B");
//
//    // trace source of infection
//    tree.TraceSource("D");
//
//    // hierarchical tree
//    tree.PrintHierarchicalTree();
//
//    return 0;
//}

int main() {
    // Testing the ContactTree class with int values
    ContactTree<int> tree;

    // add patient zero
    tree.AddPatient0(1);

    // add contacts
    tree.AddContact(1, 2);
    tree.AddContact(1, 3);
    tree.AddContact(2, 4);
    tree.AddContact(2, 5);
    tree.AddContact(3, 6);

    cout << "Contact Info:\n";
    // contact information
    tree.DisplayContact(2);
    cout << "\nHierarchchical Tree:\n ";
    // hierarchical tree
    tree.PrintHierarchicalTree();
    cout << "\nPatients in Contact Tree:\n ";
    // contact tree
    tree.PrintContactTree();
    cout << "\nContact cases of patient:\n ";
    // contact cases of a given patient
    tree.PrintContactCases(3);
    cout << "\nTrace source of contact:\n ";
    // trace source
    tree.TraceSource(4);
 
    return 0;
}
