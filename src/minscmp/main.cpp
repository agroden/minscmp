/// main.cpp
///
/// minscmp
/// compares prepared minutiae files (.drp files)
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

// std includes
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

// posix includes
#include <dirent.h>

// project includes
#include "drp.h"

using namespace drp;

// unsecure thread loads the template file
// secure thread loads gallery file
// unsecure thread converts xyt data to dnar data
// unsecure passes minutiae data to secure thread for comparison
// secure thread signals either accepted, next minutia, or next neighbor
// if accepted, unsecure thread increases counter
// if counter >= 3 increase matching minutiae score and send next minutia
// - else send next neighbor
// after all minutiae are exhausted, return num matching minutiae as score

static bool compare_neighbors(drp_group_t* t_grp, drp_group_t* g_grp, 
	unsigned int threshold = 3)
{
	if (threshold <= 0)
		threshold = 3;
	unsigned int matched_neighbors = 0;
	for (auto m_iter = t_grp->begin(); m_iter != t_grp->end(); ++m_iter)
	{
		for (auto n_iter = g_grp->begin(); n_iter != g_grp->end(); ++n_iter)
		{
			int d_delta = (*m_iter)->distance() - (*n_iter)->distance();
			int ra_delta = (*m_iter)->radial_angle() - 
				(*n_iter)->radial_angle();
			int pa_delta = (*m_iter)->positional_angle() - 
				(*n_iter)->positional_angle();
			if (abs(d_delta) <= d_delta && abs(ra_delta) <= ra_delta &&
				abs(pa_delta) <= pa_delta)
			{
				++matched_neighbors;
				// remove this neighbor from the list
				g_grp->erase(n_iter);
				break;
			}
		}
	}
	return matched_neighbors >= threshold;
}

float compare(drp_t* temp, drp_t* gallery, unsigned int threshold)
{
	if (threshold <= 0)
		threshold = temp->size();
	unsigned int matched_minutiae = 0;
	// for each minutiae in the template...
	for (auto t_iter = temp->begin(); t_iter != temp->end(); ++t_iter)
	{
		drp_group_t* t_grp = (*t_iter)->neighbors();
		// and each minutiae in the gallery...
		for (auto g_iter = gallery->begin(); g_iter != gallery->end(); ++g_iter)
		{
			// make a copy so we don't change the neighbors
			drp_group_t g_grp(*(*g_iter)->neighbors());
			// if the ridge direction is within range
			int rd_delta = (*t_iter)->ridge_direction() - 
				(*g_iter)->ridge_direction();
			if (abs(rd_delta) <= rd_delta)
			{
				if (compare_neighbors(t_grp, &g_grp))
				{
					++matched_minutiae;
					// remove this minutiae from the gallery so we don't waste 
					// time comparing it again when it has already been matched
					gallery->erase(g_iter);
					break;
				}
			}
		}
	}
	return matched_minutiae / (float)std::max(temp->size(), gallery->size());
}

void print_usage()
{
	std::cout << "minscmp [options] <template file>.drp <gallery file>.drp\n";
	std::cout << "compares prepared minutiae files\n";
	std::cout << "options:\n";
	std::cout << "\t-h\tprints this message\n";
	std::cout << "\t-r\ttreat gallery file argument as a directory\n";
	std::cout << "\t-t\tset the threshold for matching";
}

int err_exit(std::string err)
{
	std::cerr << "Error: " << err << "\n";
	std::cerr << "use -h for help" << std::endl;
	return -1;
}

int main(int argc, const char* argv[])
{
	std::vector<const char*> positional_args;
	bool is_dir = false;
	int threshold = 0;
	for (int i = 1; i < argc; ++i)
	{
		std::string s(argv[i]);
		if (s[0] == '-')
		{
			if ("-r" == s)
				is_dir = true;
			else if ("-t" == s)
			{
				if (!argv[i + 1])
				{
					return err_exit("-t flag requires an argument");
				}
				threshold = std::stoi(argv[i + 1]);
				++i;
			}
			else if ("-h" == s || "--help" == s)
			{
				print_usage();
				return 0;
			}
			else
				return err_exit("invalid option");
		}
		else
			positional_args.push_back(argv[i]);
	}
	if (positional_args.size() != 2)
		return err_exit("incorrect number of arguments");

	// load drp files
	drp_t* temp = drp::load(positional_args[0]);
	drp_t* gallery = NULL;
	if (is_dir)
	{
		DIR* dir = opendir(positional_args[1]);
		if (dir == NULL)
			err_exit("could not open directory");
		struct dirent* entry = NULL;
		std::stringstream ss;
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] != '.')
			{
				ss << positional_args[1];
				ss << "/" << entry->d_name;
				std::string path = ss.str();
				ss.str("");
				size_t found = path.rfind(".drp");
				if (found != std::string::npos)
				{
					gallery = drp::load(path.c_str());
					float val = compare(temp, gallery, threshold);
					std::cout << path << ": " << val << std::endl;
				}
			}
		}
		closedir(dir);
	}
	else
	{
		gallery = drp::load(positional_args[1]);
		float val = compare(temp, gallery, threshold);
		std::cout << positional_args[1] << ": " << val << std::endl;
	}
	return 0;
}
