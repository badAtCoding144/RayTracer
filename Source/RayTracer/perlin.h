#ifndef PERLIN_H
#define PERLIN_H
#include "rtweekend.h"

class perlin {
public:
	perlin() {
		for (int i = 0; i < point_count; i++) {
			randfloat[i] = random_double();

		}
		perlin_generate_perm(perm_x);
		perlin_generate_perm(perm_y);
		perlin_generate_perm(perm_z);
	}

	double noise(const point3& p) const {
		auto u = p.x() - std::floor(p.x());
		auto v = p.y() - std::floor(p.y());
		auto w = p.z() - std::floor(p.z());

		auto i = int(std::floor(p.x()));
		auto j = int(std::floor(p.y()));
		auto k = int(std::floor(p.z()));
		double c[2][2][2];

		for (int di = 0; di < 2; di++)
			for (int dj = 0; dj < 2; dj++)
				for (int dk = 0; dk < 2; dk++)
					c[di][dj][dk] = randfloat[
						perm_x[(i + di) & 255] ^
							perm_y[(j + dj) & 255] ^
							perm_z[(k + dk) & 255]
					];

		return trilinear_interp(c, u, v, w);
	}

private:

	static const int point_count = 256;
	double randfloat[point_count];
	int perm_x[point_count];
	int perm_y[point_count];
	int perm_z[point_count];

	static void perlin_generate_perm(int* p) {
		for (int i = 0; i < point_count; i++) {
			p[i] = i;
		}
		permute(p, point_count);

	}

	static void permute(int* p, int n) {
		for (int i = n - 1; i > 0; i--) {
			int target = random_int(0, i);
			int tmp = p[i];
			p[i] = p[target];
			p[target] = tmp;
		}

	}


};


#endif