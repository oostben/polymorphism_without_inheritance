#include<iostream>
using namespace std;
#include <string>
#include <vector>

using object_t = int;

void draw(const object_t& x, ostream& out, size_t position)
{
    out << string(position, ' ') << x << endl;
}

using document_t = vector<object_t>;

void draw(const document_t& x, ostream& out, size_t position)
{
    out << position << string(position, ' ') << "<document>" << endl;
    for (const auto & e: x) draw(e,out,position + 2);
    out << position <<  string(position, ' ') << "</document>" << endl;

}