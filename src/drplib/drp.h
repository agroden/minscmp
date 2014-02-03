/// drp.h
///
/// Contains functions for reading and creating records for use with minscmp.
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

#ifndef __DRP_H__
#define __DRP_H__

#include <deque>
#include <memory>
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

	typedef std::deque<std::unique_ptr<drp_row_t>> drp_group_t;

	typedef struct drp_record {
		size_t minutiae_id;
		drp_group_t neighbors;
		float ridge_direction;
		drp_record(size_t id, float rd) : 
			minutiae_id(id), neighbors(grp), ridge_direction(rd) { }
		~drp_record() { neighbors.clear(); }
	} drp_record_t;

	typedef std::deque<std::unique_ptr<drp_record_t>> drp_t;

	const drp_t* convert_xyt(size_t num_neighbors = 6, const xyt_struct* xyt);
	const drp_t* load(size_t num_neighbors = 6, const char* path);

	static float distance(size_t n_id, size_t m_id, xyt_struct* xyt);
	static float radial_angle(size_t n_id, size_t m_id, xyt_struct* xyt);
	static float positional_angle(size_t n_id, size_t m_id, xyt_struct* xyt);
}

#endif