/// xyt.h
///
/// Contains functions for reading and creating records for use with minscmp.
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

#ifndef __XYT_H__
#define __XYT_H__

#include <deque>
#include <memory>

namespace xyt {
	class xyt_row {
	public:
		xyt_row(int x, int y, int t, int q) : m_x(x), m_y(y), m_theta(t) { }
		~xyt_row() { }
		int x() const { return m_x; }
		int y() const { return m_y; }
		int theta() const { return m_theta; }
		int quality() const { return m_quality; }
	private:
		int m_x, m_y, m_theta, m_quality;
	};

	typedef std::shared_ptr<xyt_row> xyt_row_ptr;
	typedef std::deque<xyt_row_ptr> xyt_t;

	// file format:
	// X Y T Q
	// ...
	void save(const char* path, const xyt_t* xyt);
	const xyt_t* load(const char* path);
}

#endif
