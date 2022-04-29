#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "structs.h"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string GetAttributeValue(const std::string& attrName, const std::string& element);
Point2f ToPoint2f(const std::string& point2fStr);
std::string ltrim(const std::string& s);
void ProcessAttribute(const std::string& s);
std::string PointToString(const std::string& s);

int main()
{
	std::ifstream triangleFile{ "Resources/Triangle.svg" };
	std::ifstream levelFile{ "Resources/Level.svg" };

	if (levelFile && triangleFile)
	{
		while (levelFile.peek() != EOF)
		{
			std::string line;
			std::getline(levelFile, line);
			line = ltrim(line);
			std::string attribute{ GetAttributeValue("d", line) };
			
			if (line[0] == 'd')
			{
				ProcessAttribute(attribute);
			}
		}

		while (triangleFile.peek() != EOF)
		{
			std::string line;
			std::getline(triangleFile, line);
			line = ltrim(line);
			std::string attribute{ GetAttributeValue("d", line) };

			if (line[0] == 'd')
			{
				ProcessAttribute(attribute);
			}
		}
	}
}

std::string GetAttributeValue(const std::string& attrName, const std::string& element)
{
	std::string attribute;
	std::string attrSearch{ attrName + "=" };

	size_t attrPos = element.find(attrSearch);
	if (attrPos == std::string::npos)
	{
		// std::cerr << R"(Attribute ")" << attrName << R"(" not found!)";
		return "";
	}
	size_t startPos{ element.find(R"(")", attrPos) };
	size_t endPos{ element.find(R"(")", startPos + 1) };

	attribute = element.substr(startPos + 1, endPos - startPos - 1);
	return attribute;
}

Point2f ToPoint2f(const std::string& point2fStr)
{
	Point2f point;
	std::string attr;
	std::stringstream ss(point2fStr);

	std::getline(ss, attr, ',');
	point.x = std::stof(attr);

	std::getline(ss, attr, ',');
	point.y = std::stof(attr);

	return point;
}

// Trim all whitespaces at the beginning of the string
std::string ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? " " : s.substr(start);
}

void ProcessAttribute(const std::string& s)
{
	std::stringstream ss{ s };

	while (ss.peek() != EOF)
	{
		std::string attr;
		std::getline(ss, attr, ' ');

		if (!isdigit(attr[0]) && attr[0] != '-')
		{
			if (attr.size() > 1)
			{
				std::cout << std::endl << "Command: " << attr[0] << std::endl;
				attr.erase(0, 1);

				std::cout << PointToString(attr);
			}
			else
			{
				std::cout << std::endl << "Command: " << attr[0] << std::endl;
			}
		}
		else
		{
			std::cout << PointToString(attr);
		}
	}
}

std::string PointToString(const std::string& s)
{
	std::stringstream pointss;
	Point2f p{ ToPoint2f(s) };
	pointss.precision(2);
	pointss.setf(std::ios::fixed);
	pointss << "[" << p.x << ", " << p.y << "]" << std::endl; 
	return pointss.str();
}
