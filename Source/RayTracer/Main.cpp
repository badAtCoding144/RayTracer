#include <iostream>

int main(){

	const int  width = 256;
	const int  height = 256;


	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = 0; j < height; j++) {
		std::clog << "\rScanlines remaining: " << height - j << ' ' << std::flush;
		for (int i = 0; i < width; i++) {
			auto r = double(i) / (width - 1);
			auto g = double(j) / (height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		

		}
	
	
	}
	std::cerr << "\nDone.\n";


}