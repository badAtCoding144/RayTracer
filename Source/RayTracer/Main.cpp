#include <iostream>
#include "color.h"
#include "ray.h"
#include "vec3.h"

color ray_color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main(){

	int  width = 400;
	

	auto aspect_ratio = 16.0/9.0;
	
	//calculate image height and make sure its at least 1
	int height = int(width / aspect_ratio);
	height = (height < 1) ? 1 : height;

	//viewport widtsh less than one are oka because they are real valued
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height*(double(width)/height);

	//camera
	auto focal_length = 1.0;
	auto camera_center = point3(0, 0, 0);

	//calculate the vectors across hori and vert viewport edges
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	//calculate the hori and veeertical delta vectors from pixel to pixel
	auto pixel_delta_u = viewport_u / double(width);
	auto pixel_delta_v = viewport_v / double(height);

	//calculate the upper left corner of the viewport
	auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	//render
	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = 0; j < height; j++) {
		std::clog << "\rScanlines remaining: " << height - j << ' ' << std::flush;
		for (int i = 0; i < width; i++) {
			auto pixel_center = pixel100_loc + i * pixel_delta_u + j * pixel_delta_v;
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		
		}
	
	
	}

	std::clog << "\nDone.\n";	




}