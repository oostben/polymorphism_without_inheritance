#include<iostream>
using namespace std;
#include <string>
#include <vector>

void draw(const int& x, ostream& out, size_t position)
{
    out << string(position, ' ') << x << endl;
}
class object_t 
{
    public:
        object_t(const int& x):self_(x) { }

        //friend function will be friendly with a class even though it is not a member of that class and can access the private members of the class.
        friend void draw(const object_t& x,  ostream& out, size_t position) 
        {
            draw(x.self_, out, position);
        }
    private:
        int self_;
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