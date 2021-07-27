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
        //pass ctor arguments by value and move them into place to use our own 
        object_t(int x): self_(make_unique<int_model_t>(move(x))) { }

        object_t(const object_t& x): self_(make_unique<int_model_t>(*x.self_)) { }

        object_t(object_t&& x) noexcept = default;

        object_t& operator=(object_t&&) noexcept = default;

        object_t& operator=(const object_t& x)
        {
            return *this = object_t(x);
        }

        friend void draw(const object_t& x, ostream& out, size_t position)
        {
            x.self_->draw_(out, position);
        }
    
    private:
        struct int_model_t
        {
            int_model_t(int x): data_(move(x)) { }
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