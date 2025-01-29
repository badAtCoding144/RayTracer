#include <iostream>
#include "color.h"
#include "vec3.h"

int main(){

	int  width = 400;
	

	auto aspect_ratio = 16.0/9.0;
	
	//calculate image height and make sure its at least 1
	int height = int(width / aspect_ratio);
	height = (height < 1) ? 1 : height;

	//viewport widtsh less than one are oka because they are real valued
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height*(double(width)/height);


}