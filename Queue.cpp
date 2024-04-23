#include "Node.h"
#include <iostream>

//Custom Queue class made from scratch, allows any datatype by using a template

template <typename T>
class Queue
{
private:
    Node<T>* front = nullptr;
    Node<T>* rear = nullptr;
    int size;
public:
    T Front()
    {
        return front->data;
    }
    T Rear()
    {
        return rear->data;
    }
    void Enqueue(const T& ref)
    {
        Node<T>* n = new Node<T>();
        n->data = ref;
        n->next = nullptr;

        if (IsEmpty())
        {
            front = n;
            rear = n;
        }
        else
        {
            rear->next = n;
            rear = n;
        }
        size++;
    }

    const T& Dequeue()
    {
        if (this->IsEmpty())
        {
            return NULL;
        }

        Node<T>* n = front;
        front = front->next;
        T dequeuedData = n->data;
        delete n;
        size--;
        return dequeuedData;
    }
    int GetSize()
    {
        return size;
    }
    bool IsEmpty()
    {
        return size == 0;
    }
    void Display()
    {
        for (Node* p = front; p != nullptr; p = p->next)
        {
            std::cout << *p->data << " ";
        }
        std::cout << "\n";
    }
};