// Name: patel vrundaben vijaykumar
// Seneca Student ID:158605220
// Seneca email:vvpatel20@myseneca.ca
// Date of completion:02/04/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"
#include <fstream>
#include <iostream>
#include "Utilities.h"
#include "Workstation.h"

using namespace std;
namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations): m_cntCustomerOrder(0), m_firstStation(nullptr) {
		std::fstream f(file);
		if (f.is_open()) {
			std::string record, wstation, nextWStation;
			while (std::getline(f, record)){
				Utilities util;
				util.setDelimiter('|');
				size_t next_pos = 0;
				bool more = true;
				wstation = util.extractToken(record, next_pos, more);
				std::vector<Workstation*>::const_iterator currentstation = std::find_if(stations.cbegin(), stations.cend(), [wstation](const Workstation* workstation) {
					if (workstation->getItemName() == wstation){
						return true;
					}else {
					    return false;
					}
			    });
				if (currentstation == stations.cend()){
					throw "exception occured";
				}
                m_activeLine.push_back(*currentstation);

				if (more){
                    nextWStation = util.extractToken(record, next_pos, more);
					std::vector<Workstation*>::const_iterator nextstation = std::find_if(stations.cbegin(), stations.cend(), [nextWStation](const Workstation* workstation) {
						if (workstation->getItemName() == nextWStation){
							return true;
						}else{
							return false;
						}
					});
					if (nextstation == stations.cend()){
						throw "exception occured";
					}
					(*currentstation)->setNextStation(*nextstation);
				}
				std::for_each(m_activeLine.begin(), m_activeLine.end(), [this](Workstation* curStation) {
					std::vector<Workstation*>::iterator prevStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [curStation](Workstation* workstation) {
						return workstation->getNextStation() == curStation;
					});

					if (prevStation == m_activeLine.end()) {
						m_firstStation = curStation;
					}
				});

				if (!m_firstStation) {
					throw "exception occured";
				}
				m_cntCustomerOrder = g_pending.size();

			}
			f.close();
		}
		else
		{
			throw std::invalid_argument("Invalid file name!");
		}

    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> temp;
        auto currStation = m_firstStation;

        while (currStation) {
            temp.push_back(currStation);
            currStation = currStation->getNextStation();
        }

        m_activeLine = temp;
    }

    bool LineManager::run(std::ostream& os) {
		static size_t count = 1;
		os << "Line Manager Iteration: " << count++ << std::endl;
		if (!g_pending.empty()){
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for (auto it = m_activeLine.begin(); it != m_activeLine.end(); it++){
			(*it)->fill(os);
		}

		for (auto it = m_activeLine.begin(); it != m_activeLine.end(); it++){
			(*it)->attemptToMoveOrder();
		}
		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const {
		for (size_t i = 0; i < m_activeLine.size(); i++)
		{
			m_activeLine[i]->display(os);
		}
    }


}
