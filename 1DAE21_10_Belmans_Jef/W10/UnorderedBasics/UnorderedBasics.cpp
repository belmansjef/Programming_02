#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
#include <iomanip>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Player.h"

void TestUnorderedSet();
void TestUnorderedMap();
void TestUnorderedMultiset();
void TestUnorderedMultimap();

#pragma region HelperDeclarations
size_t GetHashValue(const std::string& text);
template <typename T>
void PrintBuckets(const T& container);
#pragma endregion HelperDeclarations

int main()
{
	srand(unsigned int(time(nullptr)));
	std::cout << std::boolalpha;

	// Exploring the unordered associative containers
	TestUnorderedSet( );
	TestUnorderedMap( );
	TestUnorderedMultiset( );
	TestUnorderedMultimap( );

	// Wait
	std::cout << "\nPush ENTER to continue";
	std::cin.get();

	return 0;
}

void TestUnorderedSet()
{
	std::cout << "\n--> Unordered_set of city names\n";
	std::vector<std::string>  namesSrc1{
		"Aalst",
		"Kortrijk",
		"Gent",
		"Antwerpen",
		"Aalst",
		"Namen",
		"Gent",
		"Hasselt" };
	std::vector<std::string>  namesSrc2{
		"Brugge",
		"Mechelen",
		"Brussel",
		"Boom",
		"Lokeren" };


	std::cout << "\nCreate and fill the unordered_set using a given vector of cities\n";
	std::cout << "These are the elements of the vector: ";
	// TODO: 1a. Print the cities of vector namesSrc1
	for (std::string element : namesSrc1)
	{
		std::cout << element << std::endl;
	}

	// TODO: 1b. Define and fill an unordered_set of cities  
	//  using the given namesSrc1 vector as a source
	std::unordered_set<std::string> cities;
	for (std::string element : namesSrc1)
	{
		cities.insert(element);
	}

	std::cout << "\nThese are the elements of the unordered_set (with their hash value):\n";
	// TODO: 1c. Print all the elements together with their hash value, 
	// You can use the given function 'GetHashValue'
	for (std::string element : cities)
	{
		std::cout << element << std::setw(10) << " " << GetHashValue(element) << std::endl;
	}

	// TODO: 1d. Print the buckets using the given function 'PrintBuckets'
	// and have a look at the output
	PrintBuckets(cities);

	std::cout << "\nInsert another vector of city names into the unordered_set\n";
	std::cout << "These are the elements of this vector: ";
	// TODO: 1e. Print the cities of vector namesSrc2
	for (std::string element : namesSrc2)
	{
		std::cout << element << std::endl;
	}

	// TODO: 1f. Insert the cities from the vector namesSrc2 into the unordered_set
	for (std::string element : namesSrc1)
	{
		cities.insert(element);
	}

	std::cout << "\nThese are the elements of the unordered_set (with their hash value):\n";
	// TODO: 1g. Again print all the elements together with their hash value, 
	for (std::string element : cities)
	{
		std::cout << element << std::setw(10) << " " << GetHashValue(element) << std::endl;
	}

	// TODO: 1h. Print the buckets and have a look at the output
	PrintBuckets(cities);

	// TODO: 1i. Erase the cities that have a name length >= 8 and print the unordered_set elements after this erase
	for (std::string element : cities)
	{
		if (element.size() >= 8)
		{
			cities.erase(element);
			break;
		}
	}

	for (std::string element : cities)
	{
		std::cout << element << std::endl;
	}
}

void TestUnorderedMap()
{
	std::cout << "\n--> Unordered_map of Player objects, key is the name of the player\n";
	// Given is a vector of Player objects
	std::vector<Player>  playersSrc{
		Player{ "Jan", 3 },
		Player{ "Thomas", 12 },
		Player{ "Sara", 14 },
		Player{ "Kris", 8 },
		Player{ "Thomas", 6 },
		Player{ "Anna", 18 },
		Player{ "Sara", 19 }
	};

	std::cout << "\nCreate the map and then insert elements from the vector of Player objects\n";
	std::cout << "These are the elements of the vector:\n";
	// TODO: 2a. Print the players  of  vector playersSrc
	for (Player element : playersSrc) 
	{
		std::cout << "Player[" << element.GetName() <<  ", " << element.GetScore() << "]\n";
	}

	// TODO: 2b. Define and fill - using insert - an unordered_map of of Players (key is name) 
	// using the given vector of players as a source
	std::unordered_map<std::string, Player> players;
	for (Player element : playersSrc)
	{
		players.insert(std::make_pair(element.GetName(), element));
	}

	std::cout << "\nThese are the  unordered_map elements together with their hash value\n";
	// TODO: 2c. Print all the elements together with their hash value (GetHashValue)
	for (auto& key_val : players)
	{
		std::cout << "Player[" << key_val.first << ", " << key_val.second << "] " << GetHashValue(key_val.first) << std::endl;
	}

	// TODO: 2d. Print the buckets (PrintBuckets) and have a look at the output
	PrintBuckets(players);

	// TODO: 2e. Erase players with a score less than 10 
	//  and print the remaining players in the unordered_map
	//  Print the buckets
	//  Know that the moment an element is erased from within a range loop, the range loop      //  can not continue and must be ended. Ignoring that will result in a crash. 
	bool ereasedAll{ false };
	while (!ereasedAll)
	{
		for (auto& key_val : players)
		{
			if (key_val.second.GetScore() < 10)
			{
				players.erase(key_val.first);
				ereasedAll = false;
				break;
			}
			ereasedAll = true;
		}
	}

	for (auto& key_val : players)
	{
		std::cout << "Player[" << key_val.first << ", " << key_val.second << "] " << GetHashValue(key_val.first) << std::endl;
	}
	PrintBuckets(players);
}

void TestUnorderedMultiset()
{
	std::cout << "\n--> unordered_multiset of city names\n";
	std::vector<std::string>  namesSrc1{
		"Aalst",
		"Kortrijk",
		"Gent",
		"Antwerpen",
		"Aalst",
		"Namen",
		"Gent",
		"Hasselt" };
	std::vector<std::string>  namesSrc2{
		"Brugge",
		"Mechelen",
		"Brussel",
		"Gent",
		"Hasselt" };
	// TODO: 3. Copy here the code from TestUnorderedSet without the source vector definitions and 
	//       change the type of the container into a unordered_multiset
	//		 Notice that duplicates are allowed

	std::cout << "\nCreate and fill the unordered_set using a given vector of cities\n";
	std::cout << "These are the elements of the vector: ";
	// TODO: 1a. Print the cities of vector namesSrc1
	for (std::string element : namesSrc1)
	{
		std::cout << element << std::endl;
	}

	// TODO: 1b. Define and fill an unordered_set of cities  
	//  using the given namesSrc1 vector as a source
	std::unordered_set<std::string> cities;
	for (std::string element : namesSrc1)
	{
		cities.insert(element);
	}

	std::cout << "\nThese are the elements of the unordered_set (with their hash value):\n";
	// TODO: 1c. Print all the elements together with their hash value, 
	// You can use the given function 'GetHashValue'
	for (std::string element : cities)
	{
		std::cout << element << std::setw(10) << " " << GetHashValue(element) << std::endl;
	}

	// TODO: 1d. Print the buckets using the given function 'PrintBuckets'
	// and have a look at the output
	PrintBuckets(cities);

	std::cout << "\nInsert another vector of city names into the unordered_set\n";
	std::cout << "These are the elements of this vector: ";
	// TODO: 1e. Print the cities of vector namesSrc2
	for (std::string element : namesSrc2)
	{
		std::cout << element << std::endl;
	}

	// TODO: 1f. Insert the cities from the vector namesSrc2 into the unordered_set
	for (std::string element : namesSrc1)
	{
		cities.insert(element);
	}

	std::cout << "\nThese are the elements of the unordered_set (with their hash value):\n";
	// TODO: 1g. Again print all the elements together with their hash value, 
	for (std::string element : cities)
	{
		std::cout << element << std::setw(10) << " " << GetHashValue(element) << std::endl;
	}

	// TODO: 1h. Print the buckets and have a look at the output
	PrintBuckets(cities);

	// TODO: 1i. Erase the cities that have a name length >= 8 and print the unordered_set elements after this erase
	for (std::string element : cities)
	{
		if (element.size() >= 8)
		{
			cities.erase(element);
			break;
		}
	}

	for (std::string element : cities)
	{
		std::cout << element << std::endl;
	}
}

void TestUnorderedMultimap()
{
	std::cout << "\n--> unordered_multimap of Player objects, key is the name of the player\n";
	std::vector<Player>  playersSrc{ Player{ "Jan", rand() },
		Player{ "Thomas", rand() },
		Player{ "Sara", rand() },
		Player{ "Kris", rand() },
		Player{ "Thomas", rand() },
		Player{ "Anna", rand() },
		Player{ "Sara", rand() }
	};

	// TODO: 4. Copy here the code from TestUnorderedMap without the source vector definition and 
	//       change the type of the container into a unordered_multimap
	//		 Notice that duplicates are allowed

	std::cout << "\nCreate the map and then insert elements from the vector of Player objects\n";
	std::cout << "These are the elements of the vector:\n";
	// TODO: 2a. Print the players  of  vector playersSrc
	for (Player element : playersSrc)
	{
		std::cout << "Player[" << element.GetName() << ", " << element.GetScore() << "]\n";
	}

	// TODO: 2b. Define and fill - using insert - an unordered_map of of Players (key is name) 
	// using the given vector of players as a source
	std::unordered_map<std::string, Player> players;
	for (Player element : playersSrc)
	{
		players.insert(std::make_pair(element.GetName(), element));
	}

	std::cout << "\nThese are the  unordered_map elements together with their hash value\n";
	// TODO: 2c. Print all the elements together with their hash value (GetHashValue)
	for (auto& key_val : players)
	{
		std::cout << "Player[" << key_val.first << ", " << key_val.second << "] " << GetHashValue(key_val.first) << std::endl;
	}

	// TODO: 2d. Print the buckets (PrintBuckets) and have a look at the output
	PrintBuckets(players);

	// TODO: 2e. Erase players with a score less than 10 
	//  and print the remaining players in the unordered_map
	//  Print the buckets
	//  Know that the moment an element is erased from within a range loop, the range loop      //  can not continue and must be ended. Ignoring that will result in a crash. 
	bool ereasedAll{ false };
	while (!ereasedAll)
	{
		for (auto& key_val : players)
		{
			if (key_val.second.GetScore() < 10)
			{
				players.erase(key_val.first);
				ereasedAll = false;
				break;
			}
			ereasedAll = true;
		}
	}

	for (auto& key_val : players)
	{
		std::cout << "Player[" << key_val.first << ", " << key_val.second << "] " << GetHashValue(key_val.first) << std::endl;
	}
	PrintBuckets(players);
}

#pragma region HelperDefinitions
size_t GetHashValue(const std::string& text)
{
	std::hash<std::string> hashFunction;
	return hashFunction(text);
}
template <typename T>
void PrintBuckets(const T& container)
{
	// Basic data
	std::cout << "\nBucket information\n";
	std::cout << "Nr. buckets: " << container.bucket_count() << ", nr. elements: " << container.size() << '\n';
	std::cout << "Load factor: " << container.load_factor() << '\n';
	std::cout << "Max load factor: " << container.max_load_factor() << '\n';

	// The buckets that contain values
	for (size_t i{ 0 }; i < container.bucket_count(); ++i)
	{
		if (container.begin(i) != container.end(i))
		{
			std::cout << "Bucket " << i << ": ";
			for (auto it = container.begin(i); it != container.end(i); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << '\n';
		}
	}
	std::cout << '\n';
}
#pragma endregion HelperDefinitions