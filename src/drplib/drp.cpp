/// drp.cpp
///
/// Contains functions for reading and creating records for use with minscmp.
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

#include <cmath>
#include <fstream>
#include "drp.h"

namespace drp {
	// forward declare file only convenience functions
	static float distance(size_t n_id, size_t m_id, const xyt_struct* xyt);
	static float radial_angle(size_t n_id, size_t m_id, const xyt_struct* xyt);
	static float positional_angle(size_t n_id, size_t m_id, const xyt_struct* xyt);
	
	const drp_t* convert_xyt(const xyt_struct* xyt, size_t num_neighbors) {
		drp_t* drp = new drp_t();
		for (int i = 0; i < xyt->nrows; ++i) {
			drp_record* curr = new drp_record(i, xyt->thetacol[i]);
			drp_group_t* group = curr->neighbors();
			// look for nearest neighbors
			for (int j = 0; j < xyt->nrows; ++i) {
				if (j == i)
					continue;
				float d = distance(j, i, xyt);
				// first pass, don't calculate the tough stuff yet
				if (group->size() < num_neighbors)
					group->push_back(drp_row_ptr(new drp_row(j, d)));
				else {
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
				(*n)->radial_angle(radial_angle((*n)->id(), i, xyt));
				(*n)->positional_angle(positional_angle((*n)->id(), i, xyt));
			}
			drp->push_back(drp_record_ptr(curr));
		}
		return drp;
	}


	const drp_t* load_xyt(const char* path, size_t num_neighbors) {
		xyt_struct* xyt = bz_load(path);
		const drp_t* ret = convert_xyt(xyt, num_neighbors);
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
			for (auto j = group->begin(); j != group->end(); ++i) {
				ofile << (*j)->id() << " ";
				ofile << (*j)->distance() << " ";
				ofile << (*j)->radial_angle() << " ";
				ofile << (*j)->positional_angle() << "\n";
			}
		}
		ofile.close();
	}


	const drp_t* load(const char* path) {
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


	static float distance(size_t n_id, size_t m_id, const xyt_struct* xyt) {
		return sqrt(pow((xyt->xcol[n_id] - xyt->xcol[m_id]), 2) + 
					pow((xyt->ycol[n_id] - xyt->ycol[m_id]), 2));
	}


	static float radial_angle(size_t n_id, size_t m_id, const xyt_struct* xyt) {
		return xyt->thetacol[n_id] - xyt->thetacol[m_id];
	}


	static float positional_angle(size_t n_id, size_t m_id, const xyt_struct* xyt) {
		return atan((xyt->ycol[n_id] - xyt->ycol[m_id]) / 
					(xyt->xcol[n_id] - xyt->xcol[m_id])) - xyt->thetacol[m_id];
	}
}
