#pragma once
#include <string>

struct Point2f;
struct Rectf;
class FileReader final
{
public:
	static std::string GetAttributeValue(const std::string& attrName, const std::string& element);
	static std::string ltrim(const std::string& s);
	static Point2f ToPoint2f(const std::string& point2fStr);
	static Rectf ToRectf(const std::string& rectfStr);
};

