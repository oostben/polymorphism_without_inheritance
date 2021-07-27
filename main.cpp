#include<iostream>
#include "library.cpp"
using namespace std;

int main() 
{
    document_t document;
    document.emplace_back(1);
    document.emplace_back(2);
    document.emplace_back(3);
    document.emplace_back(4);
    cout << "done building vector" << endl;
    std::reverse(document.begin(), document.end());

    draw(document,cout,0);
}