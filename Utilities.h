// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <iostream>
namespace seneca {
	class Utilities {
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		//Utilities() = default;
		void setFieldWidth(size_t newWidth);
		void trim(std::string& src);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}
#endif // !SENECA_UTILITIES_H
