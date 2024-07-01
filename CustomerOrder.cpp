// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:20/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include <algorithm>

using namespace std;
namespace seneca {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder() {}

	CustomerOrder::CustomerOrder(const std::string& record) {
		Utilities util;
		size_t next_pos = 0;
		bool more = false;
		int i = 0;
		delete[] m_lstItem;
		m_name = util.extractToken(record, next_pos, more);
		if (more)
		{
			m_product = util.extractToken(record, next_pos, more);
		}
		std::string remain = "";
		if (more)
		{
			remain = record.substr(next_pos);
		}
		size_t count_delim = std::count(remain.begin(), remain.end(), util.getDelimiter());
		count_delim += 1;
		m_cntItem = count_delim;
		m_lstItem = new Item * [m_cntItem];

		next_pos = 0;
		while (more)
		{
			std::string item_name = util.extractToken(remain, next_pos, more);
			Item* item = new Item(item_name);
			m_lstItem[i] = item;
			i++;

		}
		if (util.getFieldWidth() > CustomerOrder::m_widthField)
		{
			CustomerOrder::m_widthField = util.getFieldWidth();
		}

	}

	CustomerOrder::CustomerOrder(const CustomerOrder& record) {
		throw - 1;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& record) noexcept
	{
		*this = move(record);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& record) noexcept {
		if (this != &record) {
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;
			m_name = record.m_name;
			m_product = record.m_product;
			m_cntItem = record.m_cntItem;
			m_lstItem = record.m_lstItem;
			record.m_lstItem = nullptr;
			record.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const {
		bool result = true;

		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				result = false;
				break;
			}
		}
		return result;

	}

	size_t& CustomerOrder::getm_cntItem() {
		return m_cntItem;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled==false)
				result = false;
		}
		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			Item* currentItem = m_lstItem[i];
			if (station.getItemName() == currentItem->m_itemName && !currentItem->m_isFilled) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					currentItem->m_serialNumber = station.getNextSerialNumber();
					currentItem->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << currentItem->m_itemName << "]" << endl;
					break;
				} else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << currentItem->m_itemName << "]" << endl;
				}
			}

		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << std::setfill(' ') << std::left << "] "
				<< std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			m_lstItem[i]->m_isFilled ? os << "FILLED" : os << "TO BE FILLED";
			os << std::endl;
		}
	}
}