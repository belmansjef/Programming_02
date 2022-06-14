#include <sstream>
#include "pch.h"
#include "FileReader.h"
#include "structs.h"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string FileReader::GetAttributeValue(const std::string& attrName, const std::string& element)
{
	std::string attribute;
	std::string attrSearch{ attrName + "=" };

	size_t attrPos = element.find(attrSearch);
	if (attrPos == std::string::npos)
	{
		std::cerr << R"(Attribute ")" << attrName << R"(" not found!)";
		return "";
	}
	size_t startPos{ element.find(R"(")", attrPos) };
	size_t endPos{ element.find(R"(")", startPos + 1) };

	attribute = element.substr(startPos + 1, endPos - startPos - 1);
	return attribute;
}

std::string FileReader::ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? " " : s.substr(start);
}

Point2f FileReader::ToPoint2f(const std::string& point2fStr)
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

Rectf FileReader::ToRectf(const std::string& rectfStr)
{
	Rectf rectf;
	std::string attr;
	std::stringstream ss(rectfStr);

	std::getline(ss, attr, ',');
	rectf.left = std::stof(attr);

	std::getline(ss, attr, ',');
	rectf.bottom = std::stof(attr);

	std::getline(ss, attr, ',');
	rectf.width = std::stof(attr);

	std::getline(ss, attr, ',');
	rectf.height = std::stof(attr);

	return rectf;
}
