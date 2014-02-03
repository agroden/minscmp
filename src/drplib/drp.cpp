#include <math>
#include "drp.h"

using namespace drp;

const drp_t* convert_xyt(size_t num_neighbors, const xyt_struct* xyt) {
	for (size_t i = 0; i < xyt->nrows; ++i) {
		drp_record_t* curr = new drp_record_t(i, xyt->thetacol[i]);
		// look for nearest neighbors
		for (size_t j = 0; j < xyt->nrows; ++i) {
			if (j == i)
				continue;
			float d = distance(j, i, xyt);
			// first pass, don't calculate the tough stuff yet
			if (curr->neighbors.size() < num_neighbors)
				curr->neighbors.push_back(new drp_row(j, d));
			else {
				for (auto k = curr_group.begin(); k != curr_group.end(); ++k) {
					if (k->distance > d) {
						curr->neighbors.erase(k);
						curr->neighbors.push_back(new drp_row(j, d));
						delete k;
						break;
					}
				}
			}
		}
		// calculate the rest of the info for the local group
		for (auto n = curr->neighbors.begin(); n != curr->neighbors.end(); ++n) {
			n->radial_angle = radial_angle(n->minutiae_id, i, xyt);
			n->positional_angle = positional_angle(n->minutiae_id, i, xyt);
		}
		m_groups.push_back(curr);
	}
}

const drp_t* drp::from_file(size_t num_neighbors, const char* path) {
	xyt_struct xyt;
	// TODO: fix this biz
	//bz_load(path, &xyt);
	return convert_xyt(num_neighbors, &xyt);
}

static float drp::distance(size_t n_id, size_t m_id, xyt_struct* xyt) {
	return sqrt(pow((xyt->xcol[n_id] - xyt->xcol[m_id]), 2) + 
				pow((xyt->ycol[n_id] - xyt->ycol[m_id]), 2));
}

static float drp::radial_angle(size_t n_id, size_t m_id, xyt_struct* xyt) {
	return xyt->thetacol[n->minutiae_id] - xyt->thetacol[i];
}

static float drp::positional_angle(size_t n_id, size_t m_id, xyt_struct* xyt) {
	return atan((xyt->ycol[n_id] - xyt->ycol[m_id]) / 
				(xyt->xcol[n_id] - xyt->xcol[m_id])) - xyt->thetacol[i];
}
