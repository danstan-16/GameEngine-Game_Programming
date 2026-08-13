#pragma once
#include <string>

//namespace nu
//{
//	std::string ToLower(const std::string& str)
//	{
//		std::string lower = str;
//
//		for (auto& c : lower)
//		{
//			c = std::tolower(c);
//		}
//
//		return lower;
//	}
//
//	std::string ToUpper(const std::string& str)
//	{
//		std::string upper = str;
//
//		for (auto& c : upper)
//		{
//			c = std::toupper(c);
//		}
//
//		return upper;
//	}
//
//	bool EqualsIgnoreCase(const std::string& str1, const std::string& str2)
//	{
//		if (str1.size() != str2.size())
//		{
//			return false;
//		}
//
//		return ToLower(str1) == ToLower(str2);
//	}
//}