template <typename T>
class MyQueue {
private:
    list<T> elements;

public:
    void push(const T& element) {
        elements.push_back(element);
    }

    void pop() {
        if (!elements.empty()) {
            elements.pop_front();
        }
    }

    T front() {
        if (!elements.empty()) {
            return elements.front();
        }
        throw runtime_error("Queue is empty");
    }

    bool empty() {
        return elements.empty();
    }
};