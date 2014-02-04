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

namespace drp {
	class minutiae {
	public:
		minutiae(unsigned int id) : m_id(id) { }
		~minutiae() { }
		unsigned int id() const { return m_id; }
	private:
		unsigned int m_id;
	};

	class drp_row : public minutiae {
	public:
		drp_row(unsigned int id, float d, float ra = 0, float pa = 0) :
			minutiae(id), m_distance(d), m_radial_angle(ra),
			m_positional_angle(pa) { }
		~drp_row() { }
		float distance() const { return m_distance; }
		float radial_angle() const { return m_radial_angle; }
		void radial_angle(float ra) { m_radial_angle = ra; }
		float positional_angle() const { return m_positional_angle; }
		void positional_angle(float pa) { m_positional_angle = pa; }
	private:
		float m_distance;
		float m_radial_angle;
		float m_positional_angle;
	};

	typedef std::unique_ptr<drp_row> drp_row_ptr;
	typedef std::deque<drp_row_ptr> drp_group_t;

	class drp_record : public minutiae {
	public:
		drp_record(unsigned int id, float rd) : minutiae(id), 
			m_ridge_direction(rd) { }
		~drp_record() { m_neighbors.clear(); }
		drp_group_t* neighbors() { return &m_neighbors; }
		float ridge_direction() { return m_ridge_direction; }
	private:
		drp_group_t m_neighbors;
		float m_ridge_direction;
	};

	typedef std::unique_ptr<drp_record> drp_record_ptr;
	typedef std::deque<drp_record_ptr> drp_t;

	const drp_t* convert_xyt(const xyt_t* xyt, size_t num_neighbors = 6);
	const drp_t* load_xyt(const char* path, size_t num_neighbors = 6);

	// file format:
	// minutiae_id ridge_direction number_of_neighbors
	// minutiae_id distance radial_angle positional_angle
	// ... (repeats for number_of_neighbors)
	void save(const char* path, const drp_t* drp);
	const drp_t* load(const char* path);
}

#endif
