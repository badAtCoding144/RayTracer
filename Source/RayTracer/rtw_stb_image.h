#ifndef RTW_STB_IMAGE_H
#define RTW_STB_IMAGE_H

#ifdef _MSC_VER
	#pragma warning(push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "../external/stb_image.h"

#include <iostream>
#include <cstdlib>

class rtw_image {
public:
	rtw_image();
	rtw_image(const char* image_filename) {
	//loads image data from specified file if the rtw images is defined and looks only in that directory for the image file, will searcch subdirectoruies images/ for six levels up
	// otherwise it will return 0 for width and height
		auto filename = std::string(image_filename);
		auto imagedir = getenv("RTW_IMAGES");

		//search the image in likely locations

		if (imagedir && load(std::string(imagedir) + "/" + filename)) {return;}
		if (load(filename)) { return; }
		if (load("images/" + filename)) return;
		if (load("../images/" + filename)) return;
		if (load("../../images/" + filename)) return;
		if (load("../../../images/" + filename)) return;
		if (load("../../../../images/" + filename)) return;
		if (load("../../../../../images/" + filename)) return;
		if (load("../../../../../../images/" + filename)) return;

		std::cerr << "Failed to load texture image file: " << filename << std::endl;

	}

	~rtw_image() {
		delete[] bdata;
		STBI_FREE(fdata);
	}

	bool load(const std::string& filename) {
		auto n = bytes_per_pixel;
		fdata = stbi_loadf(filename.c_str(), &image_width, &image_height, &n, n);
		if (!fdata) {
			std::cerr << "Failed to load texture image file: " << filename << std::endl;
			return false;
		}

		bytes_per_scanline = bytes_per_pixel * image_width;
		convert_to_bytes();
		return true;
	
	}


	int width() const {
		return image_width;
	}

	int height() const {
		return image_height;
	}

	const unsigned char* pixel_data(int x, int y) const {
		static unsigned char magenta[] = { 255, 0, 255 };
		if (bdata == nullptr) { return magenta; }

		x = clamp(x, 0, image_width);
		y = clamp(y, 0, image_height);
		return bdata + (y * bytes_per_scanline) + (x * bytes_per_pixel);
	
	}

private:
	const int bytes_per_pixel = 3;
	float* fdata = nullptr;
	unsigned char* bdata = nullptr;
	int image_width = 0;
	int image_height = 0;
	int bytes_per_scanline = 0;

	static int clamp(int x, int low, int high) {
		if (x < low) return low;
		if (x < high) return x;
		return high-1;
	}

	static unsigned char float_to_byte(float value) {
		if (value <= 0.0) return 0;
		if (value >= 1.0) return 255;
		return static_cast<unsigned char>(value * 256);
	}

	void convert_to_bytes() {
		int total_bytes = image_width * image_height * bytes_per_pixel;
		bdata = new unsigned char[total_bytes];

		auto* bptr = bdata;
		auto* fptr = fdata;

		for (auto i = 0; i < total_bytes; i++, bptr++, fptr++) {
			*bptr = float_to_byte(*fptr);
		}
	
	}
};

#ifdef _MSC_VER
#pragma warning (pop)
#endif
#endif
