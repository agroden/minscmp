/// xyt.cpp
///
/// Contains functions for reading and creating records for use with minscmp.
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

#include <fstream>
#include "xyt.h"

namespace xyt {
	void save(const char* path, const xyt_t* xyt) {
		std::ofstream ofile(path, std::ofstream::out);
		for (auto i = xyt->begin(); i != xyt->end(); ++i) {
			ofile << (*i)->x() << " ";
			ofile << (*i)->y() << " ";
			ofile << (*i)->theta() << " ";
			ofile << (*i)->quality() << "\n";
		}
		ofile.close();
	}
	
	const xyt_t* load(const char* path) {
		std::ifstream ifile(path, std::ifstream::in);
		xyt_t* xyt = new xyt_t();
		int x, y, t, q;
		while (ifile >> x >> y >> t >> q) {
			xyt_row* row = new xyt_row(x, y, t, q);
			xyt->push_back(xyt_row_ptr(row));
		}
		ifile.close();
		return xyt;
	}
}
