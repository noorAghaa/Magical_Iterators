#include <iostream>
#include <vector>


using namespace std;

// this is for creating a doubly linked list to traverse the items from both sides
struct Item
{
    int value; // store the value

    Item* next; // pointing to next element
    Item* prev; // pointing to prev element

    // constructor
    Item(int v)
    {
        value=v;
        next=prev=nullptr;
    }
};

// container class for storing integers
class MagicalContainer
{
    Item* front; // the first item of the linked list
    Item* rear;  // the last item of the linked list
    int n_items; // total number of values in the list

    public:

    // constructor
    MagicalContainer()
    {
        n_items=0;
        front=rear=nullptr;
    }

    // add an element to the list in ascending order
    void addElement(int v)
    {
        Item* newItem = new Item(v);

        if(front==nullptr && rear == nullptr) // if the list is empty
        {
            front = rear = newItem;
            n_items++;
        }
        else if(front == rear) // if there's only one element
        {
            if(newItem->value > front->value)  // if the new item is greater , adding it after the first
            {
                rear->next = newItem;
                newItem->prev = rear;
                rear = newItem;
            }
            else // if the new item is smaller then adding it before 
            {
                newItem->next = front;
                front->prev = newItem;
                front = newItem;
            }
            
            n_items++;
        }
        else // adding item in the middle of the list
        {
            Item* t = front;

            bool flag=false;
            while (t != nullptr) // look for the spot in the list
            {
                if(t->value > newItem->value) // if the value is greater
                {
                    newItem->next = t;
                    newItem->prev = t->prev;
                    t->prev->next = newItem;
                    t->prev = newItem;
                    n_items++;
                    flag = true;
                    break;
                }

                t = t->next;
            }
            
            if(!flag) // if the item is not added in the list it should be added in the end;
            {
                rear->next = newItem;
                newItem->prev = rear;
                rear = newItem;
                n_items++;
            }
        }
    }

    // return the size of the list
    int size(){return n_items;}

    // removing an element from the list
    void removeElement(int v)
    {
        Item* f=front;

        // loop untill the end or untill the value is found
        while (f != nullptr)
        {
            if(f->value == v) // if the value is found
            {
                if(f == front)// it is the first item
                {
                    if(front == rear) // if there's only one element
                    {
                        Item* temp = front;
                        front = rear = nullptr;
                        n_items--;
                        delete temp;
                    }
                    else // if there are more elements
                    {
                        Item* temp = front;
                        front = front->next;
                        front->prev=nullptr;
                        delete temp;
                        n_items--;
                    }
                    
                }
                else if(f == rear) // it is the last item
                {
                    Item* temp = f;
                    rear = f->prev;
                    rear->next =nullptr;

                    delete temp;
                    n_items--;
                }
                else // if the item is in the middle
                {
                    Item* temp=f;
                    f->prev->next = f->next;
                    f->next->prev = f->prev;

                    delete temp;
                    n_items--;
                }
                break;
            }
            f=f->next;
        }
        
    }

    // printing the whole list
    void printElements()
    {
        Item* t = front;

        while (t != nullptr)
        {
            cout << t->value << "\t" ;
            t = t->next;
        }
        cout << endl;
    }

    // making these classes friend so that can access the private members of this container class
    friend class AscendingIterator;
    friend class SideCrossIterator;
    friend class PrimeIterator;
};


// ascending iterator
class AscendingIterator
{
    MagicalContainer data; // storing the data here
    Item* cur_ptr;          // pointer to the item pointed to by the iterator

    public:

    // constructors
    AscendingIterator(MagicalContainer mc) : data(mc), cur_ptr(nullptr) {}
    AscendingIterator():cur_ptr(nullptr){}

    // overlaoding * operator
    int& operator*() const { return cur_ptr->value; }

    // overloading -> operator
    Item* operator->() { return cur_ptr; }

    //overloading pre-increment operator
    AscendingIterator& operator++() 
    {
        if(cur_ptr != nullptr)
        {cur_ptr = cur_ptr->next;} 
        return *this; 
    }  
    //assignment operator,  copy all the data members
    AscendingIterator& operator=(const AscendingIterator& iter)
    {
        this->data = iter.data;
        this->cur_ptr = iter.cur_ptr;
        return *this;
    }

    // post increment operator
    AscendingIterator operator++(int) { AscendingIterator tmp = *this; ++(*this); return tmp; }

    // comparison operators
    friend bool operator== (const AscendingIterator& a, const AscendingIterator& b) 
    { 
        return a.cur_ptr == b.cur_ptr; 
    }
    friend bool operator!= (const AscendingIterator& a, const AscendingIterator& b) { return a.cur_ptr != b.cur_ptr; }; 

    // the begin function to start the iterator from the beginning
    AscendingIterator& begin()
    {
        cur_ptr=data.front;
        return *this;
    }

    //the end function
    const AscendingIterator end()
    {
        return AscendingIterator(MagicalContainer());
    }

    // destructor
    ~AscendingIterator()
    {

    }

};

// Sidecross Iterator
class SideCrossIterator
{
    MagicalContainer data;
    Item* ptr_forward;  // the two pointers keep the track of the iterator
    Item* ptr_backward;

    bool isCurPtrForward;

    public:

    // constructors
    SideCrossIterator(MagicalContainer mc) : data(mc) 
    {
        ptr_forward = ptr_backward=nullptr;
        isCurPtrForward=true;
    }

    SideCrossIterator()
    {
        ptr_backward=ptr_backward=nullptr;
    }
    SideCrossIterator& operator=(const SideCrossIterator& iter)
    {
        this->data = iter.data;
        this->ptr_backward = iter.ptr_backward;
        this->ptr_forward = iter.ptr_forward;
        this->isCurPtrForward = iter.isCurPtrForward;
        return *this;
    }
    int& operator*() const 
    { 
        
        if(isCurPtrForward)
            {return ptr_forward->value;}
        else
            {return ptr_backward->value;}
    }
    Item* operator->() 
    { 
        if(isCurPtrForward)
            {return ptr_forward;}
        else
            {return ptr_backward; }
    }
    SideCrossIterator& operator++() 
    {
        

        if(ptr_backward == nullptr && ptr_forward == nullptr)
        {
            return *this;
        }
        if(isCurPtrForward)
        {
            if(ptr_backward == nullptr)
                {ptr_backward= data.rear;}
            else
                {ptr_backward = ptr_backward->prev;}
            isCurPtrForward=false;
        }
        else
        {
            ptr_forward = ptr_forward->next;
            isCurPtrForward = true;
        }

        if(ptr_backward == ptr_forward)
        {
            ptr_backward = ptr_forward = nullptr;
        }

        return *this; 
    }  
    SideCrossIterator operator++(int) { SideCrossIterator tmp = *this; ++(*this); return tmp; }
    friend bool operator== (const SideCrossIterator& a, const SideCrossIterator& b) 
    { 
        if(a.ptr_forward == b.ptr_forward && a.ptr_backward == b.ptr_backward)
            return true;
        else    
            return false; 
    }
    friend bool operator!= (const SideCrossIterator& a, const SideCrossIterator& b) { return !(a==b); }; 

    SideCrossIterator begin()
    {
        ptr_forward= data.front;
    
        isCurPtrForward= true;
        return *this;
    }

    const SideCrossIterator end()
    {
        return SideCrossIterator(MagicalContainer());
    }

    ~SideCrossIterator()
    {

    }

};


class PrimeIterator
{
    MagicalContainer data;
    Item* cur_ptr;

    bool isPrime(int n)
    {
        // Corner cases
        if (n <= 1)
            return false;
    
        for (int i = 2; i * i <= n; i++) 
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    //function for searching the next prime number in the container
    Item* find_next_prime()
    {
        Item* temp= cur_ptr;

        while (temp!= nullptr)
        {
            if(isPrime(temp->value))
                return temp;
            temp = temp->next;
        }
        return temp;
    }

    public:

    PrimeIterator(MagicalContainer mc) : data(mc), cur_ptr(nullptr) {}
    PrimeIterator():cur_ptr(nullptr){}

    PrimeIterator& operator=(const PrimeIterator& iter)
    {
        this->data = iter.data;
        this->cur_ptr = iter.cur_ptr;
        return *this;
    }
    int& operator*() const { return cur_ptr->value; }
    Item* operator->() { return cur_ptr; }
    PrimeIterator& operator++() 
    {
        cur_ptr = cur_ptr->next;
        cur_ptr= find_next_prime();
        return *this; 
    }  
    PrimeIterator operator++(int) { PrimeIterator tmp = *this; ++(*this); return tmp; }


    friend bool operator== (const PrimeIterator& a, const PrimeIterator& b) 
    { 
        return a.cur_ptr == b.cur_ptr; 
    }
    friend bool operator!= (const PrimeIterator& a, const PrimeIterator& b) { return a.cur_ptr != b.cur_ptr; }; 

    PrimeIterator begin()
    {
        cur_ptr=data.front;
        cur_ptr = find_next_prime();
        return *this;
    }

    const PrimeIterator end()
    {
        return PrimeIterator( MagicalContainer());
    }

    ~PrimeIterator()
    {

    }

};