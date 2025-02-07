// for testing dataStruct.h
#include <iostream>
#include <cstdlib>
#include <chrono>
#include "linkedList.h"
#include "arrayList.h"
#include "stringBuilder.h"

using namespace std;
using namespace std::chrono;

void testLinkedList();
void testArrayList();
void testStringBuilder();

int NUM_LOOPS = 10000000;
bool TIME = false;

int main()
{
    auto start = high_resolution_clock::now();
    if(TIME) {
        start = high_resolution_clock::now();
    }

    testLinkedList();
    //testArrayList();
    //testStringBuilder();

    if(TIME)
    {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        auto time = duration.count();
        if(time < 1000000)
            cout << "Time taken by function: " << time << " micro-seconds" << endl;
        else 
            cout << "Time taken by function: " << time / 1000000 << " seconds" << endl;
    
    }


    return 0;
}

void test() {
/*
    myClass obj;
    std::cout << "The value is " << obj.getSomeVal() << std::endl;
*/
}

void testLinkedList()
{
    LinkedList<int> list;
    list.push_front(0);

    for(size_t x = 0; x < NUM_LOOPS; ++x) {
        list.push_index(rand(),rand()%list.getSize());
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    double time = duration.count();

    if(time < 1000000)
        cout << "Time taken by function: " << time << " micro-seconds" << endl;
    else 
        cout << "Time taken by function: " << time / 1000000 << " seconds" << endl;



/*
    for(size_t x = 0; x < (NUM_LOOPS/4); ++x) {
        list.pop_index(rand()%list.getSize());
    }
    */

/*
    for (int x = 0; x < list.getSize(); ++x)
    {
        int value = list.get_index(x);
        cout << value << endl;
    }
    */

    
}

void testStringBuilder() {
    MyDataStructures::StringBuilder builder;
    std::string str = "Hello";
    std::string sentence = "";

/*
    //  W/OUT STRING BUILDER
    for(size_t x = 0; x < NUM_LOOPS; ++x) {
        sentence = sentence + str;
    }
*/

    // W/STRING BUILDER
    for(size_t x = 0; x < NUM_LOOPS; ++x) {
        builder.append(str);
    }
    builder.toString();
}