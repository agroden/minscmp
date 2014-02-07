/// drp.cpp
///
/// Contains functions for reading and creating records for use with minscmp.
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

#include <cmath>
#include <fstream>
#include "drp.h"

using namespace xyt;

namespace drp {
	// forward declare file only convenience functions
	static float distance(xyt_row* n, xyt_row* m);
	static float radial_angle(xyt_row* n, xyt_row* m);
	static float positional_angle(xyt_row* n, xyt_row* m);


	drp_t* convert_xyt(const xyt_t* xyt, size_t num_neighbors) {
		drp_t* drp = new drp_t();
		for (size_t i = 0; i < xyt->size(); ++i) {
			drp_record* curr = new drp_record(i, xyt->at(i)->theta());
			drp_group_t* group = curr->neighbors();
			// look for nearest neighbors
			for (size_t j = 0; j < xyt->size(); ++j) {
				if (j == i)
					continue;
				float d = distance(xyt->at(j).get(), xyt->at(i).get());
				// first pass, don't calculate the tough stuff yet
				if (group->size() < num_neighbors)
					group->push_back(drp_row_ptr(new drp_row(j, d)));
				else {
					// look for rows to replace
					for (auto k = group->begin(); k != group->end(); ++k) {
						if ((*k)->distance() > d) {
							group->erase(k);
							group->push_back(drp_row_ptr(new drp_row(j, d)));
							break;
						}
					}
				}
			}
			// calculate the rest of the info for the local group
			for (auto n = group->begin(); n != group->end(); ++n) {
				(*n)->radial_angle(radial_angle(
					xyt->at((*n)->id()).get(), 
					xyt->at(i).get()));
				(*n)->positional_angle(positional_angle(
					xyt->at((*n)->id()).get(), 
					xyt->at(i).get()));
			}
			drp->push_back(drp_record_ptr(curr));
		}
		return drp;
	}


	drp_t* load_xyt(const char* path, size_t num_neighbors) {
		const xyt_t* xyt = xyt::load(path);
		drp_t* ret = convert_xyt(xyt, num_neighbors);
		delete xyt;
		return ret;
	}


	void save(const char* path, const drp_t* drp) {
		std::ofstream ofile(path, std::ofstream::out);
		for (auto i = drp->begin(); i != drp->end(); ++i) {
			drp_group_t* group = (*i)->neighbors();
			ofile << (*i)->id() << " ";
			ofile << (*i)->ridge_direction() << " ";
			ofile << group->size() << "\n";
			for (auto j = group->begin(); j != group->end(); ++j) {
				ofile << (*j)->id() << " ";
				ofile << (*j)->distance() << " ";
				ofile << (*j)->radial_angle() << " ";
				ofile << (*j)->positional_angle();
				if ((j + 1) != group->end())
					ofile << '\n';
			}
			if ((i + 1) != drp->end())
				ofile << '\n';
		}
		ofile.close();
	}


	drp_t* load(const char* path) {
		std::ifstream ifile(path, std::ifstream::in);
		drp_t* drp = new drp_t();
		unsigned int id;
		float rd;
		size_t n;
		while (ifile >> id >> rd >> n) {
			drp_record* curr = new drp_record(id, rd);
			drp_group_t* group = curr->neighbors();
			drp->push_back(drp_record_ptr(curr));
			float d, ra, pa;
			for (size_t i = 0; i < n; ++i) {
				ifile >> id >> d >> ra >> pa;
				group->push_back(drp_row_ptr(new drp_row(id, d, ra, pa)));
			}
		}
		ifile.close();
		return drp;
	}


	inline static float distance(xyt_row* n, xyt_row* m) {
		return sqrt(pow((n->x() - m->x()), 2) + pow((n->y() - m->y()), 2));
	}


	inline static float radial_angle(xyt_row* n, xyt_row* m) {
		return n->theta() - m->theta();
	}


	inline static float positional_angle(xyt_row* n, xyt_row* m) {
		return atan2((n->y() - m->y()), (n->x() - m->x())) - m->theta();
	}
}
