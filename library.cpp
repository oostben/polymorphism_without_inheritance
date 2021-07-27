#include<iostream>
using namespace std;
#include <string>
#include <vector>

//traditional polymorphism with pure virtual class and vtable, and shared pointers to manage memory scope
class object_t 
{
    public:
        virtual ~object_t() { }
        virtual void draw(ostream&, size_t) const = 0;
};

using document_t = vector<shared_ptr<object_t>>;

void draw(const document_t& x, ostream& out, size_t position)
{
    out << position << string(position, ' ') << "<document>" << endl;
    for (const auto & e: x)
    {
        e->draw(out,position + 2);
    } 
    out << position <<  string(position, ' ') << "</document>" << endl;

}