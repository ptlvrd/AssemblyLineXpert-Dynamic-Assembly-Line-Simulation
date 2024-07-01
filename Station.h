// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <iostream>
namespace seneca {
	class Station {
        size_t m_id;
        std::string m_itemName;
        std::string m_description;
        size_t m_nxtSerialNum;
        size_t m_numItems;
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station() = default;
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
	};
}
#endif // !SENECA_STATION_H
