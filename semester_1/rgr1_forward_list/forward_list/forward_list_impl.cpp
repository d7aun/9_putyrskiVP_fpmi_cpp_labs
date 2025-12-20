#include "forward_list_impl.h"

ForwardList::ForwardListIterator ForwardList::begin()
{
    ForwardListIterator tmp(this->first);
    return tmp;
}
ForwardList::ForwardListIterator ForwardList::end()
{
    Node* tmp = this->first;
    while (tmp != nullptr)
        tmp = tmp->next_;
    return ForwardListIterator(tmp);
}

// 2) const version
// TODO: think about return type
// (is it exactly ForwardListIterator?)
ForwardList::ForwardListIterator ForwardList::begin() const
{
    ForwardListIterator tmp(this->first);
    return tmp;
}
ForwardList::ForwardListIterator ForwardList::end() const
{
    Node* tmp = this->first;
    while (tmp != nullptr)
        tmp = tmp->next_;
    return ForwardListIterator(tmp);
}

// default constructor
ForwardList::ForwardList()
{
    this->first = nullptr;
}

// copy constructor
ForwardList::ForwardList(const ForwardList& rhs)
{
    this->first = nullptr;
    size_t sz = rhs.Size();
    for (size_t a = 0; a < sz; ++a) {
        PushFront(0);
    }
    ForwardListIterator i = begin();
    ForwardListIterator j = rhs.begin();
    while (i != end())
    {
        *i = *j;
        ++i; ++j;
    }
}

// Constructs a ForwardList with `count` copies of elements with value `value`.
ForwardList::ForwardList(size_t count, int32_t value)
{
    this->first = nullptr;
    for (size_t i = 0; i < count; ++i)
        PushFront(value);
}

// Constructs a ForwardList with std::initializer_list<int32_t>
ForwardList::ForwardList(std::initializer_list<int32_t> init) 
{
    int num = 0;
    size_t count = 0;
    for (int num : init)
        ++count;

    this->first = nullptr;
    for (size_t i = 0; i < count; ++i)
        PushFront(0);

    Node* tmp = this->first;
    for (int32_t num : init)
    {
        tmp->value_ = num;
        tmp = tmp->next_;
    }
}

// operator= overloading
ForwardList& ForwardList::operator=(const ForwardList& rhs)
{
    if (first == rhs.first)
        return *this;

    Clear();
    size_t sz = rhs.Size();
    for (size_t a = 0; a < sz; ++a) {
        PushFront(0);
    }
    ForwardListIterator i = begin();
    ForwardListIterator j = rhs.begin();
    while (i != end())
    {
        *i = *j;
        ++i; ++j;
    }
    return *this;
}

// destructor
ForwardList::~ForwardList()
{
    while (this->begin() != this->end())
        PopFront();
}

// insert new element on the top of the list
void ForwardList::PushFront(int32_t value)
{
    Node* tmp = new Node(value);
    tmp->next_ = this->first;
    this->first = tmp;
}

// delete first element of the list
void ForwardList::PopFront()
{
    Node* exItem = this->first;
    Node* tmp = exItem->next_;
    this->first = tmp;
    delete exItem;
}

// remove every occurence of an element in the list
// whose value equals to param `value`,
// the remaining elements must remain in the same order
void ForwardList::Remove(int32_t value)
{
    ForwardListIterator i = this->begin(), j = i;
    while (*i == value && i != this->end())
    {
        this->PopFront();
        i = this->begin(); j = i;
    }
    ++i;
    while (i != this->end())
    {
        if (*i == value)
        {
            Node* tmp = i.pos()->next_;
            j.pos()->next_ = tmp;
            delete i.pos();
            i = ForwardListIterator(j.pos()->next_);
        }
        ++i; ++j;
    }
}

// erases all the elements
void ForwardList::Clear()
{
    while (this->begin() != this->end())
        PopFront();
}

// find list's element by the `value`
// returns true, if element exists
// otherwise, returns false
bool ForwardList::FindByValue(int32_t value)
{
    ForwardListIterator i = this->begin();
    bool thereIs = false;
    while (i != this->end())
    {
        if (*i == value)
        {
            thereIs = true;
            break;
        }
        ++i;
    }
    return thereIs;
}

// print list's elements to stream separated by space
void ForwardList::Print(std::ostream& out)
{
    ForwardListIterator i = this->begin();
    if (i != this->end())
    {
        out << *i;
        ++i;
    }
    while (i != this->end())
    {
        out << " " << *i;
        ++i;
    }
}

// get first element of the list
int32_t ForwardList::Front() const
{
    if (this->first != nullptr)
    {
        ForwardListIterator i = this->begin();
        return *i;
    }
    return 0;
}

// get size of the list
size_t ForwardList::Size() const
{
    Node* tmp = this->first;
    int count = 0;
    while (tmp != nullptr)
    {
        tmp = tmp->next_;
        ++count;
    }
    return count;
}
