#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include "Container.cpp"
#include "TestContainerTemplate.h"
#include "Fraction.h"
#include "Vector2f.h"

void TestInitializerList();
void TestVector2fContainer();

void StartHeapControl();
void DumpMemoryLeaks();

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	{
		StartHeapControl();
		
		// Test the constructor with initializer list parameter
		TestInitializerList();

		std::cout << "\n-->Start of Container<int> test <--\n";
		TestContainer<int>( );
		std::cout << "-->End of Container<int> test <--\n\n";

		std::cout << "-->Start of Container<float> test <--\n";
		TestContainer<float>( );
		std::cout << "-->End of Container<float> test <--\n\n";

		std::cout << "-->Start of Container<string> test <--\n";
		TestContainer<std::string>( );
		std::cout << "-->End of Container<string> test <--\n\n";

		std::cout << "-->Start of Container<Fraction> test <--\n";
		TestContainer<Fraction>( );
		std::cout << "-->End of Container<Fraction> test <--\n\n";

		std::cout << "-->Start of Container<Vector2f> test <--\n";
		TestVector2fContainer();
		std::cout << "-->End of Container<Vector2f> test <--\n";
	}
	DumpMemoryLeaks();

	std::cout << "Push ENTER to continue";
	std::cin.get();
}

void TestInitializerList()
{
	// Test 1
	// Create a Container object using braced-init-list of elements
	// Print the elements
	Container<int> cont1{ 1,2,3,4,5 };
	for (int idx{}; idx < cont1.Size(); ++idx)
	{
		std::cout << cont1[idx] << " ";
	}
	std::cout << "\n";

	// Test 2
	// Assign an braced-init-list to the above Container object
	// Print the elements
	cont1 = { 20,30,40 };
	for (int idx{}; idx < cont1.Size(); ++idx)
	{
		std::cout << cont1[idx] << " ";
	}
	std::cout << "\n";

	// Test 3
	// Which Container constructor is called?
	Container<int> cont2(40);
	Container<int> cont3{ 40 };
}

void TestVector2fContainer()
{
	// using the constructor with std::initializer_list parameter
	Container<Vector2f> velocities{ Vector2f(0, 0), Vector2f(1, 0), Vector2f(0, 1), Vector2f(1,1) };

	for (int i = 0; i < 5; i++)
	{
		velocities.PushBack(Vector2f(float(rand() % 5), float(rand() % 5)));
	}

	for (int i = 0; i < velocities.Size(); i++)
	{
		std::cout << velocities[i] << std::endl;
	}

	for (int i = 0; i < velocities.Size(); i++)
	{
		velocities[i].x += 10;
	}

	for (int i = 0; i < velocities.Size(); i++)
	{
		velocities[i].y += 5;
	}

	for (int i = 0; i < velocities.Size(); i++)
	{
		std::cout << velocities.Get(i) << std::endl;
	}

}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}
