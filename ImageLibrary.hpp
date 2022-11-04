#pragma once
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stbi.h>
#include <cstdint>

struct RGB {
	unsigned char* R, * G, * B;
};

struct RGBA {
	unsigned char* R, * G, * B, * A;
};

class Texture {
public:
	Texture(const char* ImagePath) {
		int ch;
		data = stbi_load("container.jpg", &Dimensions[0], &Dimensions[1], &(ch), 0);

		channels = (int8_t)ch;
	}

	bool Load(const char* ImagePath) {
		if (data != 0) {
			stbi_image_free(data);
			data = 0;
		}

		int ch;
		data = stbi_load("container.jpg", &Dimensions[0], &Dimensions[1], &(ch), 0);

		channels = (int8_t)ch;

		return data;
	}

	RGB* operator[](int PixelLocation[2]) {
		return (RGB*)&(data[PixelLocation[1] * channels * Dimensions[0] + PixelLocation[0]]);
	}

	RGB PointX(int PixelLocation[2]) {
		return *(((RGB*)data) + ((uint64_t) PixelLocation[1] * Dimensions[0] + PixelLocation[0]));
	}

	~Texture() {
		if (data != 0) {
			stbi_image_free(data);
			data = 0;
		}
	}
private:
protected:
	unsigned char* data = 0;
	int8_t channels;
	int Dimensions[2];
};
