#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera {

public:
	double aspect_ratio = 1.0;  // Ratio of image width over height
	int    image_width = 100;  // Rendered image width in pixel count
	int samples_per_pixel = 10; //samples for AA per pixel
	int max_depth = 10; // max number of ray bounces into scene

	double vfov = 90.0;       // Vertical field-of-view in degrees
	point3 lookfrom = point3(0, 0, 0);
	point3 lookat = point3(0, 0, -1);
	vec3 vup = vec3(0, 1, 0);
	color background;


	double defocus_angle = 0.0;
	double focus_dist = 10;

	void render(const hittable& world) {
		initialize();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++) {
			std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
			for (int i = 0; i < image_width; i++) {
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth ,world);
				}
				write_color(std::cout, pixel_samples_scale*pixel_color);
			}
		}
		std::clog << "\rDone.                 \n";
	}

	void initialize() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		pixel_samples_scale = 1.0 / samples_per_pixel;

		center = lookfrom;


		// Determine viewport dimensions.
		auto theta = degrees_to_radians(vfov);
		auto h = std::tan(theta / 2);
	
		auto viewport_height = 2.0 * h *focus_dist;

		auto viewport_width = viewport_height * (double(image_width) / image_height);

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		// Calculate the vectors across the horizontal and down the vertical viewport edges.
		auto viewport_u = viewport_width * u;
		auto viewport_v = viewport_height * -v;

		// Calculate the horizontal and vertical delta vectors from pixel to pixel.
		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		// Calculate the location of the upper left pixel.
		auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		//calculate the defocus disk vectors
		auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
		defocus_disk_u = defocus_radius * u;
		defocus_disk_v = defocus_radius * v;
	}

private:

	int image_height;
	point3 center;
	point3 pixel00_loc;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	double pixel_samples_scale;
	vec3 u, v, w;
	vec3 defocus_disk_u;
	vec3 defocus_disk_v;

	point3 defocus_disk_sample() const {
		// Returns a random point in the camera defocus disk.
		auto p = random_in_unit_disk();
		return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
	}


	ray get_ray(int i, int j) const {
		//construct a camera ray originating from the origin and directed at randomly sampled point on the pixel at i,j
		auto offset = sample_square();
		auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
		auto ray_origin = (defocus_angle <=0) ? center : defocus_disk_sample();
		auto ray_direction = pixel_sample - ray_origin;
		auto ray_time = random_double();

		return ray(ray_origin, ray_direction, ray_time);
	}

	vec3 sample_square() const {
		//returns the vector to a random point in the unit square = [-.5,-0.5] - [+.5,+.5] 
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}


	color ray_color(const ray& r, int depth, const hittable& world) const {

		if (depth <= 0) {
			return color(0, 0, 0);
		}

		hit_record rec;


		// If the ray hits nothing, return the background color.
		if (!world.hit(r, interval(0.001, infinity), rec)) {
			return background;
		}
		ray scattered;
		color attenuation;
		color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

		if (!rec.mat->scatter(r, rec, attenuation, scattered)) {
			return color_from_emission;
		}
		color color_from_scatter = attenuation * ray_color(scattered, depth - 1, world);

		return color_from_emission + color_from_scatter;
	}


};


#endif