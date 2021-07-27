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
        object_t(const int & x): self_(make_unique<int_model_t>(x)) 
        { 
            cout << "ctor" << endl;
        }

        object_t(const object_t& x): self_(make_unique<int_model_t>(*x.self_)) 
        {
            cout << "copy" << endl;

        }

        //need to provide our own swap or move constructor, so that swaps workk without going to a temproary
        //move constructor (&&):
        //swap is written in terms of move
        //rvalue
        object_t(object_t&& x) noexcept : self_(move(x.self_)) 
        {
            cout << "move" << endl;
        }

        object_t& operator=(object_t x) noexcept
        {
            cout << "assignment" << endl;
            self_ = move(x.self_);
            return *this;
        }

        friend void draw(const object_t& x, ostream& out, size_t position)
        {
            x.self_->draw_(out, position);
        }
    
    private:
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