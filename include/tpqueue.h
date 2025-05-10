// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
    struct QueueNode {
        TPQueue item;
        QueueNode* link;

        explicit QueueNode(const T& val)
            : item(val), link(nullptr) {}
    };

    QueueNode* front;

 public:
    PriorityQueue()
        : front(nullptr) {}

    ~PriorityQueue() {
        while (front != nullptr) {
            QueueNode* tmp = front;
            front = front->link;
            delete tmp;
        }
    }

    void enqueue(const T& elem) {
        auto* newElem = new QueueNode(elem);

        if (front == nullptr || elem.prior > front->item.prior) {
            newElem->link = front;
            front = newElem;
            return;
        }

        QueueNode* curr = front;
        while (curr->link != nullptr &&
            curr->link->item.prior <= elem.prior) {
            curr = curr->link;
        }

        newElem->link = curr->link;
        curr->link = newElem;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        QueueNode* temp = front;
        T result = front->item;
        front = front->link;
        delete temp;
        return result;
    }

    bool isEmpty() const noexcept {
        return front == nullptr;
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
