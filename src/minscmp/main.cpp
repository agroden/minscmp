/// main.cpp
///
/// minscmp
/// compares prepared minutiae files (.drp files)
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

// std includes
#include <iostream>
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

void compare(drp_t* temp, drp_t* gallery) {

}

void print_usage() {
	std::cout << "minscmp [options] <template file>.drp <gallery file>.drp\n";
	std::cout << "compares prepared minutiae files\n"
	std::cout << "options:\n"
	std::cout << "\t-h\tprints this message\n";
	std::cout << "\t-r\ttreat gallery file argument as a directory\n";
}

int err_exit(std::string err) {
	std::cerr << "Error: " << err << "\n";
	std::cerr << "use -h for help" << std::endl;
	return -1;
}

int main(int argc, const char* argv[]) {
	std::vector<const char*> positional_args;
	bool is_dir = false;
	for (int i = 1; i < argc; ++i) {
		std::string s(argv[i]);
		if (s[0] == '-') {
			if ("-r" == s)
				is_dir = true;
			else if ("-h" == s || "--help" == s) {
				print_usage();
				return 0;
			} else {
				return err_exit("invalid option");
			}
		} else {
			positional_args.push_back(argv[i]);
		}
	}
	if (positional_args.size() != 2) {
		return err_exit("incorrect number of arguments");
	}
	// load drp files
	drp_t* temp = drp::load(positional_args[0]);
	drp_t* gallery = NULL;
	if (is_dir) {
		DIR* dir = opendir(positional_args[1]);
		if (dir == NULL)
			err_exit("could not open directory");
		struct dirent* entry = NULL;
		std::stringstream ss;
		while ((entry = readdir(dir)) != NULL) {
			if (entry->d_name[0] != '.') {
				ss << positional_args[1];
				ss << "/" << entry->d_name;
				std::string path = ss.str():
				size_t found = path.rfind(".drp");
				if (found != std::string::npos) {
					gallery = drp::load(path.c_str());
					int val = compare(temp, gallery);
					std::cout << path << ": " << val << std::endl;
				}
			}
		}
		closedir(dir);
	} else {
		gallery = drp::load(positional_args[1]);
		int val = compare(temp, gallery);
		std::cout << positional_args[1] << ": " << val << std::endl;
	}
	return 0;
}
