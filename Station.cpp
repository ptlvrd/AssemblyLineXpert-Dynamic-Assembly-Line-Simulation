// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
#include "Station.h"
#include <iostream>
#include <iomanip>
#include <string>

namespace seneca {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& record) {
		Utilities util;
		bool more = true;
		size_t next_pos = 0;

		m_itemName = util.extractToken(record, next_pos, more);
		m_nxtSerialNum = std::stoi(util.extractToken(record, next_pos, more));
		m_numItems = std::stoi(util.extractToken(record, next_pos, more));
		m_description = util.extractToken(record, next_pos, more);
		Station::m_widthField = Station::m_widthField > util.getFieldWidth() ? Station::m_widthField : util.getFieldWidth();

		m_id = ++id_generator;
	}

	const std::string& Station::getItemName() const {
		return m_itemName;
	}

	size_t Station::getNextSerialNumber() {
		return m_nxtSerialNum++;
	}

	size_t Station::getQuantity() const {
		return m_numItems;
	}

	void Station::updateQuantity() {
		if (m_numItems > 0) {
			m_numItems--;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << std::setw(3) << std::right << std::setfill('0') << m_id << " | "
		   << std::left << std::setw(15) << std::setfill(' ') << m_itemName << "| "
		   <<std::right << std::setw(6) << std::setfill('0') << m_nxtSerialNum << " | ";

		if (full) {
			os << std::right << std::setfill(' ') << std::setw(4) << m_numItems << " | " << m_description;
		}

		os << std::endl;
	}

}