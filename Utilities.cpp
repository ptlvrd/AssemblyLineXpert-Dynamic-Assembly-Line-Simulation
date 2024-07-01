// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
#include <iostream>

namespace seneca {
    char Utilities::m_delimiter = ',';

    void Utilities::trim(std::string& src) {
        if (src.length() > 0) {
            size_t begin = src.find_first_not_of(' ');
            size_t end = src.find_last_not_of(' ');
            if (begin == std::string::npos) {
                src = "";
            }
            else {
                src = src.substr(begin, end - begin + 1);
            }
        }
    }

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        size_t next_del;
        std::string result;

        if (str[next_pos] == m_delimiter) {
            more = false;
            throw - 1;
        }
        else {
            std::string temp = str.substr(next_pos);
            if ((next_del = temp.find_first_of(m_delimiter)) != std::string::npos) {
                result = temp.substr(0, next_del);
                trim(result);
                next_pos += next_del + 1;
                more = true;
            }
            else {
                result = temp;
                trim(result);
                more = false;
            }
        }

        if (m_widthField < result.length()) {
            m_widthField = result.length();
        }

        return result;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}