#include <math>
#include "drp.h"

drp_record(size_t num_neighbors, const xyt_struct* xyt) {
	for (size_t i = 0; i < xyt->nrows; ++i) {
		// create new group
		drp_group_t* curr_group = new drp_group_t();
		for (size_t j = 0; j < xyt->nrows; ++i) {
			// compute distance
			if (j == i)
				continue;
			float d = sqrt(pow((xyt->xcol[j] - xyt->xcol[i]), 2) + 
				pow((xyt->ycol[j] - xyt->ycol[i]), 2));
			
			if (curr_group.size() < num_neighbors)
				curr_group.push_back(new drp_row(j, d));
			else {
				for (size_t k = 0; k < num_neighbors; ++k) {
					if (curr_group.at(k) > d) {
						
					}
				}
			}
		}
		m_groups.push_back(new drp_record_t(i, curr_group, xyt->thetacol[i]));
	}
}

static drp_record* from_file(const std::string path, size_t num_neighbors = 6)
{
	
}

~drp_record()
{
	// delete every record and then every group
}

size_t size() const
{
	return m_groups.size();
}

drp_group_t* get_minutia_group(size_t idx) const
{
	return m_groups.at(idx);
}