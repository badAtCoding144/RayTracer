#include <iostream>
#include "color.h"
#include "vec3.h"

int main(){

	const int  width = 256;
	const int  height = 256;


	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = 0; j < height; j++) {
		std::clog << "\rScanlines remaining: " << height - j << ' ' << std::flush;
		for (int i = 0; i < width; i++) {
			auto pixel_color = color(double(i) / (width - 1), double(j) / (height - 1), 0.25);
			write_color(std::cout, pixel_color);

		}
	
	
	}
	std::cerr << "\nDone.\n";


}