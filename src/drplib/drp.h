/// drp.h
///
/// Contains functions for reading and creating records for use with minscmp.
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

#ifndef __DRP_H__
#define __DRP_H__

#include <deque>
#include <string>
#include "bozorth.h"

namespace drp {
	typedef struct drp_row {
		size_t minutia_id;
		float distance;
		float radial_angle;
		float positional_angle;
		drp_row(size_t id, float d, float ra = 0, float pa = 0) : 
			minutiae_id(id), distance(d), radial_angle(ra), 
			positional_angle(pa) { }
	} drp_row_t;

	typedef std::deque<drp_row_t*> drp_group_t;
	
	typedef struct drp_record {
		size_t minutiae_id;
		drp_group_t* neighbors;
		float ridge_direction;
		drp_record_t(size_t id, drp_group_t* grp, float rd) : 
			minutiae_id(id), neighbors(grp), ridge_direction(rd) { }
	} drp_record_t;

	class drp {
	public:
		drp(size_t num_neighbors = 6, const xyt_struct* xyt);
		static drp* from_file(const std::string path, size_t num_neighbors = 6);
		~drp();

		size_t size() const;
		drp_record_t* get_minutiae_group(size_t idx) const;

	private:
		std::deque<drp_record_t*> m_groups;
	};
}

#endif