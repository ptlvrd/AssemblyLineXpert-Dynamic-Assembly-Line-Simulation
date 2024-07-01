// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:02/04/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"
#include <iostream>
#include<deque>


namespace seneca {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;


	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			CustomerOrder* order = &(m_orders.front());
			order->fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		if (m_orders.empty()){
			return false;
		} else {
			CustomerOrder* order = &(m_orders.front());
			if (order->isItemFilled(this->getItemName()) || this->getQuantity() < 1) {
				if (m_pNextStation) {
					*m_pNextStation += std::move(*order);
				} else {
					if (order->isOrderFilled()) {
						g_completed.push_back(std::move(*order));
					} else {
 					    g_incomplete.push_back(std::move(*order));
					}
				}
				m_orders.pop_front();
				return true;
			}
		}

		return false;
	}

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }
    void Workstation::display(std::ostream& os) const {
        if (m_pNextStation) {
            os << getItemName() << " --> " << getNextStation()->getItemName() << std::endl;
        }
        else {
            os << getItemName() << " --> End of Line" << std::endl;
        }
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

}