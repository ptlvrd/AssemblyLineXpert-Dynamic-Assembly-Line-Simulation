// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:20/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"

namespace seneca {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name;
		std::string m_product;
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string& record);
		CustomerOrder(const CustomerOrder& record);
		CustomerOrder& operator=(const CustomerOrder& record) = delete;
		CustomerOrder(CustomerOrder&& record) noexcept;
		CustomerOrder& operator=(CustomerOrder&& record) noexcept;
		~CustomerOrder();
		size_t& getm_cntItem();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !SENECA_CUSTOMERORDER_H
