#include<iostream>
using namespace std;
#include <string>
#include <vector>

void draw(const int& x, ostream& out, size_t position)
{
    out << string(position, ' ') << x << endl;
}

//add in a way to draw a string
void draw(const string& x, ostream& out, size_t position)
{
    out << string(position, ' ') << x << endl;
}

class object_t 
{
    public:
        //add another constructor for strings:
        object_t(string x): self_(make_unique<string_model_t>(move(x))) { }

        object_t(int x): self_(make_unique<int_model_t>(move(x))) { }

        //virtualize copy constructor
        object_t(const object_t& x): self_(x.self_->copy_()) { }

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
        //define concept base class, so we can store whatever we like:
        struct concept_t
        {
            virtual ~concept_t() = default;
            //virtualize copy:
            virtual unique_ptr<concept_t> copy_() const = 0;
            //virualize the draw function:
            virtual void draw_(ostream&, size_t) const = 0;
        };

        struct int_model_t final : concept_t
        {
            int_model_t(int x): data_(move(x)) { }

            //virtualize copy:
            unique_ptr<concept_t> copy_() const override
            {
                return make_unique<int_model_t>(*this);
            }

            void draw_(ostream& out,size_t position) const override //signals to the compiler that this must overide the virtual in concept_t
            {
                draw(data_, out, position);
            }
            int data_;
        };

        //add in string support
        struct string_model_t final : concept_t
        {
            string_model_t(string x): data_(move(x)) { }
            
            //virtualize copy:
            unique_ptr<concept_t> copy_() const override
            {
                return make_unique<string_model_t>(*this);
            }

            void draw_(ostream& out,size_t position) const override
            {
                draw(data_, out, position);
            }
            string data_;
        };

        //now store a concept for a drawable object
        unique_ptr<concept_t> self_;
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