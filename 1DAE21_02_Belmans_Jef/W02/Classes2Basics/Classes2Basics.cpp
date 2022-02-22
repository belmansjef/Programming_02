// Jef Belmans - 1DAE21
#include <iostream>
#include <vector>
#include "Time.h"
#include "Square.h"
#include "Container.h"
using namespace std;

void TestSquares();
void CompareTimes(const Time* t1, const Time* t2);
void PrintInstancesCntr(const std::string& message);
void TestArrays();
void TestContainer();
void PrintContainer(const Container* c);

int main()
{
    // Time* t1{ new Time(20, 30, 10) };
    // Time* t2{ new Time(40, 40, 07) };

    // TestSquares();
    // CompareTimes(t1, t1);
    // CompareTimes(t1, t2);

    // PrintInstancesCntr("Before calling TestArrays");
    // TestArrays();
    // PrintInstancesCntr("After calling TestArrays");

    TestContainer();
}

void TestSquares()
{
    vector<Square*> squares{};
    squares.push_back(new Square(10.0f));
    squares.push_back(new Square(10.0f, 20.0f, 30.0f));

    cout << "--> Squares with constructor delegation\r\n";
    squares[0]->Print();
    cout << std::endl;
    squares[1]->Print();
}

void CompareTimes(const Time* t1, const Time* t2)
{
    cout << "--> Comparing two time objects\r\n";
    cout << "  ";
    t1->Print();
    cout << "  ";
    t2->Print();

    if
        (
            t1->GetHours() == t2->GetHours() &&
            t1->GetMinutes() == t2->GetMinutes() &&
            t1->GetSeconds() == t2->GetSeconds()
        )
    {
        cout << "  They are equal\r\n";
    }
    else
    {
        cout << "  They are not equal\r\n";
    }
}

void PrintInstancesCntr(const std::string& message)
{
    cout << message << " -> Nr of Time objects: ";
    cout << Time::GetNrInstances() << std::endl;
}

void TestArrays()
{
    Time* pObjects[4];
    PrintInstancesCntr("After defining the array of 4 Time object pointers");
    
    for (int i = 0; i < 4; i++)
    {
        pObjects[i] = new Time(21, 21, 21);
    }
    PrintInstancesCntr("After creating the 4 Tine objects");

    for (int i = 0; i < 4; i++)
    {
        delete pObjects[i];
        pObjects[i] = nullptr;
    }
    PrintInstancesCntr("After deleting the 4 Time objects");

    Time objects[4]{Time(10), Time(10), Time(10), Time(10)};
    PrintInstancesCntr("After defining the array of 4 Time objects");
}

void TestContainer()
{
    std::cout << "\n-- Container tests --\n";
    // Define a Container object
    const int cap{ 5 };
    std::cout << "Create container with capacity of " << cap << " elements\n";
    Container* pContainer{ new Container{cap} };
    PrintContainer(pContainer);

    // Add some values to the container
    int actNr{ 0 };
    std::cout << "\nPush back of " << (cap - 1) << " elements\n";
    for (int idx{ 1 }; idx < cap; ++idx)
    {
        pContainer->PushBack(rand() % 21);
        ++actNr;
    }
    PrintContainer(pContainer);

    std::cout << "\nChange the value of the elements (using Set)\n";
    for (int idx{ 0 }; idx < actNr; ++idx)
    {
        pContainer->Set(idx, rand() % 21);
    }
    PrintContainer(pContainer);

    std::cout << "\nPush back another " << (cap - 1) << " elements\n";
    for (int i{ 1 }; i < cap; ++i)
    {
        pContainer->PushBack(rand() % 21);
        ++actNr;
    }
    PrintContainer(pContainer);
    delete pContainer;
}

void PrintContainer(const Container* pContainer)
{
    std::cout << "-- Print container --\n";
    std::cout << "   Capacity: " << pContainer->Capacity() << std::endl;
    std::cout << "   Size: " << pContainer->Size() << std::endl;
    std::cout << "   Get the elements (using Get and Size)\n   ";
    for (int idx{ 0 }; idx < pContainer->Size(); ++idx)
    {
        std::cout << pContainer->Get(idx) << " ";
    }
    std::cout << std::endl;
}


