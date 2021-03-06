#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
#include <algorithm>
#include "Player.h"
#include <iomanip>
#include <set> 
#include <map>

struct City
{
	explicit City(std::string name, int population) :name{ name }, population{ population } {};
	std::string name;
	int population;
};

void TestPair();
void TestSetOfIntegers();
void TestSetOfPlayers();
void TestMultiset();
void TestMapOfGameRankings();
void TestMapOfCities();
void TestMultimap();

#pragma region HelperDeclarations
void PrintNumbers(const std::vector<int>& numbers);
void PrintNumber(int nr);
std::ostream& operator<<(std::ostream& out, const City& city);
void PrintCityPair(const std::pair<std::string, City> & p);
#pragma endregion

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	std::cout << std::boolalpha;

	// Explore the ordered associative containers
	//TestPair( );

	//TestSetOfIntegers( );
	//TestSetOfPlayers( );

	//TestMultiset( );
	
	// TestMapOfGameRankings( );
	// TestMapOfCities( );
	
	TestMultimap( );

	// Wait
	std::cout << "\nPush ENTER to continue";
	std::cin.get();

	return 0;
}

void TestPair()
{
	std::cout << "\n--> TestPair\n";
	// We will consider following pairs [gameName, rating] e.g.
	//    ["Andromeda",73.62f]
	//    ["World of Warcraft",91.89f]

	std::cout << "There are many ways to create a pair\n";
	// TODO: 1a. Create 2 std::pair<std::string, float> type objects pair1 and pair2
	// - pair1: Using the 2 arg constructor
	// - pair2: Using the result of std::make_pair as argument of the pair constructor
	std::pair<std::string, float> pair1{ "Andromeda", 73.62f };
	std::pair<std::string, float> pair2{ std::make_pair("World of Warcraft", 91.89f) };

	std::cout << "\nThere are 2 ways to get the values of a pair\n";
	// TODO: 1b. Print the  pairs on the console
	// - One using first, second member
	// - The other using std::get<0> and std::get<1>
	std::cout << "[" << pair1.first << ", " << pair1.second << "]\n";
	std::cout << "[" << std::get<0>(pair2) << ", " << std::get<1>(pair2) << "]\n";
}

void TestSetOfIntegers()
{
	// TODO: 2a. Create an empty set of integer type element
	std::set<int> set1;

	// TODO: 2b. Using the insert function of the set, add the multiples of value 10 in [10, 100] 
	for (int i = 1; i <= 10; i++)
	{
		set1.insert(i * 10);
	}

	// TODO: 2c. Print the numbers using a ranged based for-loop, 
	//  You can use the  given function 'PrintNumber'
	for (int element : set1)
	{
		PrintNumber(element);
	}

	// TODO: 2d. Insert a number that is already in the set (e.g. the first number) 
	set1.insert(10);
	// TODO: 2e. Insert a number that is not yet in the set (e.g. the first number + 5)
	set1.insert(15);

	// TODO: 2f. Erase an element choose e.g. value 10 using this member function: size_type erase( const key_type& key );
	// and then print the value of the return value of calling this erase function: it is the number of elements removed
	std::cout << std::endl << set1.erase(10) << std::endl;

	// TODO: 2g. Erase this element again in the same way and print the result again
	std::cout << set1.erase(10) << std::endl;

	// TODO: 2h. Loop over the elements and erase the ones that are divisible by 3,
	for (int element : set1)
	{
		if (element % 3 == 0)
		{
			set1.erase(element);
			break;
		}
	}

}

void TestSetOfPlayers()
{
	std::cout << "\n--> Set of Player objects\n";
	// TODO: 3a. Change Player::operator< function,
	// should be printed from low to high score
	std::set<Player> players;
	players.insert({
		Player{ "Devolder", "Warre", 1000 },
		Player{ "De schoenmaker", "An", 10 },
		Player{ "Janssens","Bart", 20 },
		Player{ "Janssens","Xavier", 30 } });	
	for (const Player& p : players)
	{
		std::cout << p << std::endl;
	}
}

void TestMultiset()
{
	std::cout << "\n--> Multiset of integer numbers\n";
	std::vector<int> numbersSrc{ 10,20,30,40 };
	std::cout << "These are the elements of the vector used as source: ";
	PrintNumbers(numbersSrc);

	// TODO: 4a. Create a multiset of integers using its constructor that takes iterators of the vector numbersSrc
	//       Then print the elements of the multiset using for_each
	std::multiset<int> multiset1 (numbersSrc.begin(), numbersSrc.end());
	std::for_each(multiset1.begin(), multiset1.end(), [](int i) { std::cout << i << " "; });


	const int value{ 50 };
	const int nrTimes{ 3 };
	std::cout << "\nInserting " << nrTimes << " times the value " << value << "\n";
	// TODO: 4b. Insert the same value multiple times 
	for (size_t i = 0; i < nrTimes; i++)
	{
		multiset1.insert(value);
	}

	std::cout << "Verify that the multiset contains " << nrTimes << " times the value " << value << "\n";
	std::cout << "These are the elements of the multiset: ";
	// TODO: 4c. Print all the multiset elements
	for (int element : multiset1)
	{
		std::cout << element << ", ";
	}
	std::cout << std::endl;

	std::cout << "\nErase the value " << value << " that occurs multiple times in the multiset\n";
	// TODO: 4d. Call erase using this same value, and print the returned value (number of erased elements)
	std::cout << multiset1.erase(value) << std::endl;

	std::cout << "Verify that the multiset doesn't contain the value " << value << " anymore\n";
	// TODO: 4e. Print all the multiset elements
	std::for_each(multiset1.begin(), multiset1.end(), [](int i) { std::cout << i << " "; });
}

void TestMapOfGameRankings()
{
	std::cout << "\n--> Map of Game rankings (key is name of game, value is the score)\n";
	// Ratings from http://www.gamerankings.com/pc/index.html

	std::cout << "\n--> How to create a map and adding elements to it";
	// TODO: 5a. Create a map, key is the name of a game, value is the score
	// Don't specify a compare function, in which case the operator< of std:string (key) is used
	std::map<std::string, float> map1;

	// Some values
	// "League of Legends", 79.16f
	// "Andromeda", 73.62f
	// "Final Fantasy XIV", 78.54f
	// "World of Warcraft", 91.89f
	// "Grand Theft Auto", 94.39f
	// "Wild Hunt", 92.11f
	// "The Sims 3", 86.61f
	// "Fallout 4", 85.60f
	// "Grand Theft Auto: San Andreas", 91.94f

	// TODO: 5b. Add elements in 3 different ways, you can use the above data 
	// - Using the [] operator
	// - Using the insert function
	// - Using the emplace function
	map1["League of Legends"] = 79.16f;
	map1["Andromeda"] = 72.63f;
	map1.insert(std::make_pair("Final Fantasy XIV", 78.54f));
	map1.insert(std::pair<std::string, float>("World of Warcraft", 91.89f));
	map1.emplace("Grand Theft Auto", 94.39f);
	map1.emplace("Wild Hunt", 92.11f);

	// TODO: 5c. Print the elements of the map using a ranged-based for loop
	std::cout << "\nThese are the elements of the map after adding elements in 3 different ways\n";
	for (const auto& key_val : map1)
	{
		std::cout << "[" << key_val.first << ", " << key_val.second << "]\n";
	}


	std::cout << "\n--> How to change the content of a map";
	std::cout << "\nRemove an element using erase(key)";
	// TODO: 5d. Remove an element using erase(key)
	map1.erase("League of Legends");

	std::cout << "\nAdd an element with an already existing key but another value and check what happens\n";
	// No duplicate keys in map
	// TODO: 5e. Add an element with an already existing key and check what happens
	// - Using the [] operator
	// - Using the insert function
	// - Using the emplace function
	map1.insert(std::make_pair("Andromeda", 100.0f));

	
	// TODO: 5f. Print the elements of the map using a ranged-based for loop
	std::cout << "\nThese are the elements of the map after these change operations\n";
	for (const auto& key_val : map1)
	{
		std::cout << "[" << key_val.first << ", " << key_val.second << "]\n";
	}

	std::cout << "\n--> How to get the value of an element";
	std::cout << "\nGet the score of an existing game in 3 different ways and print the scores\n";
	// TODO: 5g. Get the score of a game in 3 different ways and print the 3 scores
	// - using []
	// - using at
	// - using find
	std::cout << map1["Andromeda"] << std::endl;
	std::cout << map1.at("Wild Hunt") << std::endl;
	std::cout << map1.find("Grand Theft Auto")->second << std::endl;

	std::cout << "\nGet the score of a not existing game in 3 different ways\n";
	// TODO: 5h. Get the score of a game in 3 different ways
	// but this time use a not existing key
	// Use this sequence:
	// - using at
	// - using find
	// - using []
	// Two of these result in an exception, one creates a new element, print the score of this element
	std::cout << map1["Battlefield"] << std::endl;
	// std::cout << map1.at("Apex Legends") << std::endl;
	// std::cout << map1.find("Risk of Rain 2")->second << std::endl;

	// TODO: 5i. And print the elements 
	std::cout << "\nThese are the elements of the map after getting some scores\n";
	for (const auto& key_val : map1)
	{
		std::cout << "[" << key_val.first << ", " << key_val.second << "]\n";
	}

	std::cout << "\n--> How to change the key of an element";
	std::cout << "\nRename one of the games";
	// TODO: 5j. Rename one of the games, e.g. "Final Fantasy XIV" into "Final Fantasy"
	// You have to do this in 2 steps: 
	// - First create a new element "Final Fantasy" and copy the value of  "Final Fantasy XIV" into it
	// - Then delete "Final Fantasy XIV" using erase
	map1.insert(std::make_pair("Final Fantasy", 0.0f));
	map1.at("Final Fantasy") = map1.at("Final Fantasy XIV");
	map1.erase("Final Fantasy XIV");

	std::cout << "\nThese are the elements of the map after changing 'Final Fantasy XIV' into 'Final Fantasy'\n";
	// TODO: 5l. Print the elements
	for (const auto& key_val : map1)
	{
		std::cout << "[" << key_val.first << ", " << key_val.second << "]\n";
	}
}


void TestMapOfCities()
{
	std::cout << "\n--> Cities map, key is the name of a city, value is the City object\n";
	// TODO: 6a. Define this map, give it the name citiesMap
	std::map<std::string, City> citiesMap;

	std::cout << "\nInsert the cities from a given vector of City objects into the map using a loop\n";
	std::vector<City>  citiesSrc{
		City("Aalst",84000) ,
		City("Kortrijk",76000) ,
		City("Gent",255000) ,
		City("Antwerpen", 504000) ,
		City("Namen",111000) ,
		City("Hasselt",77000) ,
	};

	// TODO: 6b. Print the elements of citiesSrc vector
	std::cout << "These are the elements of the vector:\n";
	for (City element : citiesSrc)
	{
		std::cout << "[" << element.name << ", " << element.population << "]\n";
	}

	// TODO: 6c. Insert the cities from citiesSrc into the map using a loop
	for (City element : citiesSrc)
	{
		citiesMap.insert(std::make_pair(element.name, element));
	}


	std::cout << "\nThese are the elements of the map after the insert operation\n";
	// TODO: 6d. Print the elements of the map using a range base for loop
	// Use a helper function PrintCityPair
	for (const auto& key_val : citiesMap)
	{
		PrintCityPair(key_val);
	}


	// TODO: 6e. Uncommenting next code line of leads to a compiler error, why?
	// You don't need to solve this error, you just have to know why it results in an error
	// std::cout << citiesMap["Namen"].population << "\n";
}

void TestMultimap()
{
	std::cout << "\n--> Multimap for an English - Dutch dictionary\n";
	//TODO: 7a. Define an English - Dutch dictionary using a multimap 
	// It contains <std::string, std::string> pairs
	std::multimap<std::string, std::string> dict;

	std::cout << "\nInsert elements from a source container (vector) into the multimap\n";
	std::vector<std::pair<std::string, std::string>> translations{
	{ "strange", "vreemd" },
	{ "date", "datum" },
	{ "smart", "heftig" },
	{ "right", "juist" },
	{ "smart", "bijdehand" },
	{ "strange", "onbekend" },
	{ "date", "dadel" },
	{ "right", "rechts" },
	{ "date", "afspraak" },
	};

	std::cout << "These are the elements of the vector:\n";
	std::cout.setf(std::ios::left, std::ios::adjustfield);
	std::cout << std::setw(10) << "English" << "Dutch";
	std::cout << std::setfill('-') << std::setw(20) << '\n';
	std::cout << std::setfill(' ') << '\n';
	// TODO:7b. Print the elements of translations vector
	for (auto element : translations)
	{
		std::cout << std::setw(10) << element.first << " " << element.second << std::endl;
	}

	// TODO: 7c. Add the elements from the translations vector above. 
	for (auto element : translations)
	{
		dict.insert(std::make_pair(element.first, element.second));
	}

	std::cout << "\nThese are the elements of the multimap after the insert operation\n";
	std::cout.setf(std::ios::left, std::ios::adjustfield);
	std::cout << std::setw(10) << "English" << "Dutch";
	std::cout << std::setfill('-') << std::setw(20) << '\n';
	std::cout << std::setfill(' ') << '\n';
	// TODO: 7d. Print all the elements
	// In which order are they printed ?
	for (auto element : dict)
	{
		std::cout << std::setw(10) << element.first << " " << element.second << std::endl;
	}


	std::cout << "\nErase the elements with a specific key";
	const std::string wordEng{ "right" };
	// TODO: 7e. Erase all the values of elements having the key "right"
	dict.erase(wordEng);
	std::cout << "\nThese are the elements of the multimap after the erase operation\n";
	// TODO: 7f. Print all the elements
	for (auto element : dict)
	{
		std::cout << std::setw(10) << element.first << " " << element.second << std::endl;
	}
}

#pragma region HelperDefinitions
void PrintNumbers(const std::vector<int>& numbers)
{
	for (int nr : numbers)
	{
		std::cout << nr << " ";
	}
	std::cout << '\n';
}

void PrintNumber(int nr)
{
	std::cout << nr << " ";
}

std::ostream& operator<<(std::ostream& out, const City& city)
{
	out << city.name << " (" << city.population << ")";
	return out;
}

void PrintCityPair(const std::pair<std::string, City> & p)
{
	std::cout << p.second << '\n';
}
#pragma endregion
