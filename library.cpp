#include<iostream>
using namespace std;
#include <string>
#include <vector>

void draw(const int& x, ostream& out, size_t position)
{
    out << string(position, ' ') << x << endl;
}

//heap allocate int_model_t
class object_t 
{
    public:
        object_t(const int & x): self_(make_unique<int_model_t>(x)) { }

        //define our own copy constructor, make sure it actually copies the int, copied objects are equal and disjoint
        object_t(const object_t& x): self_(make_unique<int_model_t>(*x.self_)) { }

        //define our own assignment operator; satisfies the strong exception guarentee -> if we throw object is still in same state if we throw
        //basic exception guarentee -> still satisfies its invariants, but in an unkown state (we don't have this, we have strong)
        object_t& operator=(const object_t& x)
        {
            //notice, we don't optimize for self assignment, self assignment is rare so we exclude it for optimizing the 99.9% case
            object_t tmp(x);
            self_ = move(tmp.self_);
            return *this;
        }

        friend void draw(const object_t& x, ostream& out, size_t position)
        {
            x.self_->draw_(out, position);
        }
    
    private:
        //Private implementation (Pimpl) or handle-body idiom is good for seperating the implementation and reducing compile times
        struct int_model_t
        {
            int_model_t(const int& x): data_(x) { }
            void draw_(ostream& out,size_t position) const
            {
                draw(data_, out, position);
            }
            int data_;
        };

        unique_ptr<int_model_t> self_;
};

using document_t = vector<object_t>;

void draw(const document_t& x, ostream& out, size_t position)
{
    out << position << string(position, ' ') << "<document>" << endl;
    for (const auto & e: x)
    {
        draw(e,out,position + 2);
    } 
    out << position <<  string(position, ' ') << "</document>" << endl;

}