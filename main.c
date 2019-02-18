
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#include "func.h"

#define MAX_MACRO(x, y) ((x) > (y) ? (x) : (y))
#define MIN_MACRO(x, y) ((x) < (y) ? (x) : (y))

#define DEFAULT_SIZE_W 512
#define DEFAULT_SIZE_H 512


void print_info(void)
{
	printf("C_DIP [MAIN.C]\n");
}



uint32_t m_get_i(uint32_t lin_pos, uint32_t w, uint32_t h)
{
	return (lin_pos - (lin_pos % w))/w;
}

uint32_t m_get_j(uint32_t lin_pos, uint32_t w, uint32_t h)
{
	return lin_pos % w;
}


uint8_t min_func(uint8_t x, uint8_t y)
{
	if( x < y )
		return x;
	else
		return y;
}

uint8_t max_func(uint8_t x, uint8_t y)
{
	if( x > y )
		return x;
	else
		return y;
}

uint8_t abs_diff_func(uint8_t x, uint8_t y)

{
	return max_func(x, y) - min_func(x, y); 
}


void load_image(char *image_filename, uint8_t *image_buffer)
{
	FILE *fd;
	size_t file_size;
	uint32_t counter = 0;
	uint8_t tmp_byte;
	uint32_t bytes_readed;

	if((fd = fopen(image_filename, "rb")) == NULL)
	{
		fprintf(stderr, "ERROR OPEN FILE: %s\n", image_filename);
		exit(1);
	}


	fseek(fd, 0L, SEEK_END);
	file_size = ftell(fd);
	rewind(fd);

	printf("FILE SIZE: %d [%s]\n", file_size, image_filename);


/*
	for( ; counter < file_size; counter++)
	{

	}

*/

	bytes_readed = fread(image_buffer, file_size, 1, fd);

	printf("[load_image] fread ret code = %d\n", bytes_readed);


	fclose(fd);


}


void save_image(char *image_filename, uint8_t *image_buffer, uint32_t buffer_size)
{
	FILE *fd;
	size_t file_size;
	uint32_t counter = 0;
	uint8_t tmp_byte;
	uint32_t bytes_writed;

	if((fd = fopen(image_filename, "wb")) == NULL)
	{
		fprintf(stderr, "ERROR OPEN FILE FOR SAVE: %s\n", image_filename);
		exit(1);
	}


//	fseek(fd, 0L, SEEK_END);
//	file_size = ftell(fd);
//	rewind(fd);

//	printf("FILE SIZE: %d [%s]\n", file_size, image_filename);
	printf("BUFFER SIZE: %d [->%s]\n", buffer_size, image_filename);

/*
	for( ; counter < file_size; counter++)
	{

	}

*/

	bytes_writed = fwrite(image_buffer, buffer_size, 1, fd);

	printf("[save_image] fwrite ret code = %d\n", bytes_writed);


	fclose(fd);


}


void print_image_array(uint8_t *image_buffer, uint32_t image_size)
{
	uint32_t counter = 0;
	for( ; counter < image_size; counter++)
		printf("%d\n", image_buffer[counter]);
}

void test_func(uint8_t *input_buffer, uint8_t *output_buffer, uint32_t buffer_size)
{

	uint32_t i = 0;
	for( ; i < buffer_size; i++)
	{
		output_buffer[i] = 0xFF - input_buffer[i];
	}

}

void transpose_func(uint8_t *input_buffer, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t i = 0;
	uint32_t k = 0;
	uint32_t j;

	for( ; i < w; i++)
	{
		for(j = 0; j < h; j++, k++)
		{
			output_buffer[k] = input_buffer[j*w + i];
		}
	}

}


void mirror_x_func(uint8_t *input_buffer, uint8_t *output_buffer, uint32_t w, uint32_t h)
{

	uint32_t buffer_size = w * h;	
	uint32_t i = 1;
	uint32_t j;
	uint32_t k = 0;

	for( ; i < h; i++)
	{
		for(j = 1; j <= w; j++, k++)
		{
			output_buffer[k] = input_buffer[i*w - j];
		}

	}

}

void mirror_y_func(uint8_t *input_buffer, uint8_t *output_buffer, uint32_t w, uint32_t h)
{


	uint32_t buffer_size = w * h;	
	int32_t i;
	uint32_t j;
	uint32_t k = 0;

	for(i = h - 1 ; i >= 0; i--)
	{
		for(j = 0; j < w; j++, k++)
		{
			//printf("i = %d, j = %d, k = %d, i*w + j = %d\n", i, j , k, i*w + j);
			output_buffer[k] = input_buffer[i*w + j];
		}

	}

}


void darken_blending_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
		output_buffer[k] = min_func(input_buffer_1[k], input_buffer_2[k]);
}

void mul_blending_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
	{
		float a = (float)input_buffer_1[k]/255.0f;
		float b = (float)input_buffer_2[k]/255.0f;
		output_buffer[k] = (uint8_t)(255.0*(a*b));
	}
}

void screen_blending_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
	{
		float a = (float)input_buffer_1[k]/255.0f;
		float b = (float)input_buffer_2[k]/255.0f;
		output_buffer[k] = (uint8_t)(255.0*(1.0 - (1.0 - a)*(1.0 - b)));
	}

}

void lighten_blending_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
		output_buffer[k] = max_func(input_buffer_1[k], input_buffer_2[k]);
}

void diff_blending_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
		output_buffer[k] = abs_diff_func(input_buffer_1[k], input_buffer_2[k]);
}

void dodge_blending_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
	{
		float a = (float)input_buffer_1[k]/255.0f;
		float b = (float)input_buffer_2[k]/255.0f;
		if(input_buffer_2[k] == 255)
			output_buffer[k] = 255;
		else
			output_buffer[k] = (uint8_t)(255.0*MIN_MACRO(1.0, a/(1.0 - b)));
	}

}

void bum_blending_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
	{
		float a = (float)input_buffer_1[k]/255.0f;
		float b = (float)input_buffer_2[k]/255.0f;
		if(input_buffer_2[k] == 0)
			output_buffer[k] = 0;
		else
			output_buffer[k] = (uint8_t)(255.0*(1.0 - MIN_MACRO(1.0, (1.0 - a)/b)));
	}

}


void compose_img_as_alpha_func(uint8_t *input_buffer_1, uint8_t *input_buffer_2, uint8_t *input_buffer_3, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w * h;
	uint32_t k = 0;

	for( ; k < buffer_size; k++)
	{
		float a = (float)input_buffer_1[k]/255.0f;
		float b = (float)input_buffer_2[k]/255.0f;
		float alpha = (float)input_buffer_3[k]/255.0f;
		float r = (1.0 - alpha)*b + alpha*a;
		output_buffer[k] = (uint8_t)(255.0*r);
	}

}


int32_t main(void)
{

	char *filename = "bin\\baboon.bin";
	char *out_filename = "out_bin\\baboon_out.bin";
	char *out_filename_2 = "out_bin\\baboon_out_t.bin";
	char *out_filename_3 = "out_bin\\baboon_out_3.bin";
	char *out_filename_4 = "out_bin\\baboon_out_4.bin";
	char *hist_filename = "hist\\baboon_hist.txt";

	char *filename_2 = "bin\\Peppers.bin";
	char *filename_3 = "bin\\boat.bin";
	char *out_2_f = "out_bin\\Peppers_t.bin";
	char *out_darken_blend_f = "out_bin\\darken_tmp.bin";
	char *out_mul_blend_f = "out_bin\\mul_tmp.bin";
	char *out_screen_blend_f = "out_bin\\screen_tmp.bin";
	char *out_lighten_blend_f = "out_bin\\lighten_tmp.bin";
	char *out_diff_blend_f = "out_bin\\diff_tmp.bin";
	char *out_dodge_blend_f = "out_bin\\dodge_tmp.bin";
	char *out_bum_blend_f = "out_bin\\bum_tmp.bin";
	char *out_comp_f = "out_bin\\compose_tmp.bin";

	uint8_t image_array[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint8_t image_array_2[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint8_t image_array_3[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint8_t tmp_buffer[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint8_t tmp_buffer_2[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint8_t tmp_buffer_3[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint32_t hist_buffer[256] = { 0 };
	float pdf_buffer[256] = { 0.0 };
	uint32_t image_size = DEFAULT_SIZE_W * DEFAULT_SIZE_H;
	uint32_t buffer_size = DEFAULT_SIZE_W * DEFAULT_SIZE_H;
	uint32_t hist_size = 256;
	uint32_t w_size = DEFAULT_SIZE_W;
	uint32_t h_size = DEFAULT_SIZE_H;


	print_info();
	printf("ARRAY SIZE: %d*%d = %d\n", DEFAULT_SIZE_W, DEFAULT_SIZE_H, sizeof(image_array));
	printf("DEFAULT SIZE W: %d\n", DEFAULT_SIZE_W);
	printf("DEFAULT SIZE H: %d\n", DEFAULT_SIZE_H);


	load_image(filename, image_array);
	load_image(filename_2, image_array_2);
	load_image(filename_3, image_array_3);

//	print_image_array(image_array, image_size);

	printf("%d\n", image_array[0]);
	printf("%d\n", image_array[1]);

	test_func(image_array, tmp_buffer, buffer_size);
	save_image(out_filename, tmp_buffer, buffer_size);

	transpose_func(image_array, tmp_buffer, w_size, h_size);
	save_image(out_filename_2, tmp_buffer, buffer_size);

	mirror_x_func(image_array, tmp_buffer, w_size, h_size);
	save_image(out_filename_3, tmp_buffer, buffer_size);

	mirror_y_func(image_array, tmp_buffer, w_size, h_size);
	save_image(out_filename_4, tmp_buffer, buffer_size);

	transpose_func(image_array_2, tmp_buffer_2, w_size, h_size);
	save_image(out_2_f, tmp_buffer_2, buffer_size);

	darken_blending_func(image_array, image_array_2, tmp_buffer_3, w_size, h_size);
	save_image(out_darken_blend_f, tmp_buffer_3, buffer_size);

	lighten_blending_func(image_array, image_array_2, tmp_buffer_3, w_size, h_size);
	save_image(out_lighten_blend_f, tmp_buffer_3, buffer_size);

	mul_blending_func(image_array, image_array_2, tmp_buffer_3, w_size, h_size);
	save_image(out_mul_blend_f, tmp_buffer_3, buffer_size);
	
	screen_blending_func(image_array, image_array_2, tmp_buffer_3, w_size, h_size);
	save_image(out_screen_blend_f, tmp_buffer_3, buffer_size);

	diff_blending_func(image_array, image_array_2, tmp_buffer_3, w_size, h_size);
	save_image(out_diff_blend_f, tmp_buffer_3, buffer_size);
	
	dodge_blending_func(image_array, image_array_2, tmp_buffer_3, w_size, h_size);
	save_image(out_dodge_blend_f, tmp_buffer_3, buffer_size);

	bum_blending_func(image_array, image_array_2, tmp_buffer_3, w_size, h_size);
	save_image(out_bum_blend_f, tmp_buffer_3, buffer_size);


	compose_img_as_alpha_func(image_array, image_array_2, image_array_3, tmp_buffer_3, w_size, h_size);
	save_image(out_comp_f, tmp_buffer_3, buffer_size);


//PART 2

	calc_hist_func(image_array, hist_buffer, buffer_size);
	write_hist_in_file(hist_filename, hist_buffer, hist_size);

	calc_pdf_func(hist_buffer, pdf_buffer, hist_size, buffer_size);



	uint32_t b_max;
	float I;
	float D;
	float E;
	float A;
	float E_n;
	float H_n;

	b_max = 255;
	
	I = calc_mean_func(pdf_buffer, b_max);
	printf("\n\n[MEAN] I = %f\n", I);

	D = calc_var_func(pdf_buffer, b_max);
	printf("[VAR] D = %f\n", D);

	E = calc_kurtosis_func(pdf_buffer, b_max);
	printf("[KURTOSIS] E = %f\n", E);

	A = calc_skewness_func(pdf_buffer, b_max);
	printf("[SKEWNESS] A = %f\n", A);

	E_n = calc_uniformity_func(pdf_buffer, b_max);
	printf("[UNIFORMITY] E_n = %f\n", E_n);

	H_n = calc_entropy_func(pdf_buffer, b_max);
	printf("[ENTROPY] H_n = %f\n", H_n);

	return 0;

}

