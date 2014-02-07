/// main.cpp
///
/// drptool
/// converts .xyt files to .drp files
///
/// Alexander Groden
/// created for CYB5677 - Biometric Authentication Technologies

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "drp.h"


void print_usage() {
	std::cout << "drptool [options] <infile>.xyt <outfile>.drp\n";
	std::cout << "drptool converts .xyt files to .drp files\n";
	std::cout << "options:\n";
	std::cout << "\t-h  \tprint this message\n";
	std::cout << "\t-n #\tset the number of neighbors (default 6)\n";
}


int err_exit(std::string err) {
	std::cerr << "Error: " << err << "\n";
	std::cerr << "use -h for help" << std::endl;
	return -1;
}


int main(int argc, const char* argv[]) {
	std::vector<const char*> positional_args;
	unsigned int n = 6;
	for (int i = 1; i < argc; ++i) {
		std::string s(argv[i]);
		if (s[0] == '-') {
			if ("-n" == s) {
				if (!argv[i+1]) {
					return err_exit("-n flag requires an argument");
				}
				n = std::stoi(argv[i + 1]);
				++i;
			} else if ("-h" == s) {
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

	drp::drp_t* drp = drp::load_xyt(positional_args[0], n);
	drp::save(positional_args[1], drp);
	return 0;
}
