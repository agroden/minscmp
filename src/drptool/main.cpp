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

int main(int argc, const char* argv[]) {
	if (argc < 3)
		print_usage();
	std::vector<const char*> positional_args;
	unsigned int n = 6;
	for (int i = 0; i < argc; ++i) {
		std::string s(argv[i]);
		if ("-n" == s)
			n = std::stoi(argv[i + 1]);
		else if ("-h" == s) {
			print_usage();
			break;
		} else {
			positional_args.push_back(argv[i]);
		}
	}
	const drp::drp_t* drp = drp::load_xyt(positional_args[0], n);
	drp::save(positional_args[1], drp);
	return 0;
}