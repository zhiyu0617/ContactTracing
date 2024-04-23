//Multi-purpose Node meant for use in lists. Can carry a reference of any type.

template <typename T>
struct Node
{
    T data; //carries the stored data
    Node* next; //carries the address of the next node
};