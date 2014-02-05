#include <iostream>

// note, need a preprocessing step to convert xyt data to distance, nearest neighbor and related position angle of the nearest neighbor and ridge direction (.dnar file?)

void run() {
	// unsecure thread loads the template file
	// secure thread loads gallery file
	// unsecure thread converts xyt data to dnar data
	// unsecure passes minutiae data to secure thread for comparison
	// secure thread signals either accepted, next minutia, or next neighbor
	// if accepted, unsecure thread increases counter
	// if counter >= 3 increase matching minutiae score and send next minutia
	// - else send next neighbor
	// after all minutiae are exhausted, return num matching minutiae as score
}

void print_usage() {
	std::cout << "minscmp <template file>.xyt <gallery file>.xyt\n";
	std::cout << "minscmp -p <template file>.xyt <gallery files *>.xyt\n";
}

int main(int argc, const char* argv[]) {
	print_usage();
	return 0;
}