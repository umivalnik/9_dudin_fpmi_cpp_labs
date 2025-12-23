#include "forward_list_impl.h"

bool ForwardList::ForwardListIterator::operator==(const ForwardListIterator& other) const {
    return position_ == other.position_;
}

ForwardList::ForwardList() : head_(nullptr), size_(0) {}

ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {
    Node** current = &head_;
    for (Node* n = rhs.head_; n; n = n->next_) {
        *current = new Node(n->value_);
        current = &((*current)->next_);
    }
    size_ = rhs.size_;
}

ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    Node** current = &head_;
    for (size_t i = 0; i < count; ++i) {
        *current = new Node(value);
        current = &((*current)->next_);
    }
    size_ = count;
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    Node** current = &head_;
    for (int32_t v : init) {
        *current = new Node(v);
        current = &((*current)->next_);
    }
    size_ = init.size();
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this != &rhs) {
        Clear();
        Node** current = &head_;
        for (Node* n = rhs.head_; n; n = n->next_) {
            *current = new Node(n->value_);
            current = &((*current)->next_);
        }
        size_ = rhs.size_;
    }
    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

ForwardList::ForwardListIterator ForwardList::begin() {
    return ForwardListIterator(head_);
}

ForwardList::ForwardListIterator ForwardList::end() {
    return ForwardListIterator(nullptr);
}

ForwardList::ForwardListIterator ForwardList::begin() const {
    return ForwardListIterator(head_);
}

ForwardList::ForwardListIterator ForwardList::end() const {
    return ForwardListIterator(nullptr);
}

int32_t ForwardList::Front() const {
    if (!head_) throw std::out_of_range("list empty");
    return head_->value_;
}

size_t ForwardList::Size() const {
    return size_;
}

void ForwardList::PushFront(int32_t value) {
    Node* n = new Node(value);
    n->next_ = head_;
    head_ = n;
    ++size_;
}

void ForwardList::PopFront() {
    if (!head_) return;
    Node* n = head_;
    head_ = head_->next_;
    delete n;
    --size_;
}

void ForwardList::Remove(int32_t value) {
    Node** current = &head_;
    while (*current) {
        if ((*current)->value_ == value) {
            Node* tmp = *current;
            *current = (*current)->next_;
            delete tmp;
            --size_;
        }
        else {
            current = &((*current)->next_);
        }
    }
}

void ForwardList::Clear() {
    Node* current = head_;
    while (current) {
        Node* tmp = current->next_;
        delete current;
        current = tmp;
    }
    head_ = nullptr;
    size_ = 0;
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current) {
        if (current->value_ == value) return true;
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    bool first = true;
    while (current) {
        if (!first) out << " ";
        out << current->value_;
        first = false;
        current = current->next_;
    }
}

int main() {

}
