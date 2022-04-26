#include <iostream>
#include <sstream>
#include <fstream>
#include "structs.h"

std::string GetAttributeValue(const std::string& attrName, const std::string& element);
Point2f ToPoint2f(const std::string& point2fStr);

int main()
{
	std::ifstream triangleFile{ "Resources/Triangle.svg" };
	std::ifstream levelFile{ "Resources/Level.svg" };

	if (levelFile && triangleFile)
	{
		while (triangleFile.peek() != EOF)
		{
			std::string line;
			std::getline(triangleFile, line);
			if (GetAttributeValue("d", line) != "")
			{
				std::cout << "Found D attr!" << line << std::endl;
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