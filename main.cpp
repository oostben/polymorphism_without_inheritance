#include<iostream>
#include "library.cpp"
using namespace std;


//implement the traditional polymorphism wrapper sub class derived from object_t, so I can put a certain type into the document

class my_class_t : public object_t 
{
    virtual void draw(ostream& out, size_t position) const override 
    {
        out << string(position, ' ') << "my_class_t" << endl;
    }

};

int main() 
{
    document_t document;
    //update to use emplace back to call the constructor directly and avoid the extra copy for my new type
    document.emplace_back(new my_class_t()); //this line could result in a leak because the object could be constructed, but not yet assigned to a smart pointer
                                            //if say the growing of the vector threw an exception
                                            //most people in c++ community will tell you dint call new directly
                                            //instead call make_shared<my_class_t> to avoid this
                                            //its also better becasue it allocates the shared pointer and the class in the same block so sames a little memory and a bit of time
    document.emplace_back(make_shared<my_class_t>());
    document.emplace_back(make_shared<my_class_t>());
    document.emplace_back(make_shared<my_class_t>());
    document.emplace_back(make_shared<my_class_t>());

    draw(document,cout,0);
}