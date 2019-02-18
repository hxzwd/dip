
#ifndef H_FUNC
#define H_FUNC

#include "stdio.h" 
#include "stdlib.h"
#include "stdlib.h"
#include "math.h"

void calc_hist_func(uint8_t *image_buffer, uint32_t *hist_buffer, uint32_t buffer_size)
{

	uint32_t k = 0;
	for( ; k < buffer_size; k++)
	{
		hist_buffer[image_buffer[k]]++;
	}

}


void write_hist_in_file(char *hist_filename, uint32_t *hist_buffer, uint32_t hist_buffer_size)
{

	FILE *fd;
	char tmp_buf[256] = { 0 };
	uint32_t k = 0;
	
	if((fd = fopen(hist_filename, "w+")) == NULL)
	{
		fprintf(stderr, "Error open file for hist: %s\n", hist_filename);
		exit(1);
	}

	for( ; k < hist_buffer_size; k++)
	{
		fprintf(fd, "%d\n", hist_buffer[k]);
	}

	fclose(fd);

}

void calc_pdf_func(uint32_t *hist_buffer, float *pdf_buffer, uint32_t hist_size, uint32_t 
norm_coeff)
{
	uint32_t k;

	for(k = 0; k < hist_size; k++)
	{
		pdf_buffer[k] = (float)(((float)(hist_buffer[k]))/((float)norm_coeff));
	}
}

float calc_mean_func(float *pdf, uint32_t b_max)
{

	float result = 0.0;
	uint32_t k = 0;

	for( ; k < b_max; k++)
	{
		result += pdf[k]*k;
	}

	return result;
}

float calc_var_func(float *pdf, uint32_t b_max)
{
	float result = 0.0;
	float I;
	uint32_t k = 0;

	I = calc_mean_func(pdf, b_max);

	for( ; k < b_max; k++)
	{
		result += (k - I)*(k - I)*pdf[k];
	}

	return result;

}

float calc_kurtosis_func(float *pdf, uint32_t b_max)
{
	float result = 0.0;
	float D;
	float I;
	uint32_t k = 0;

	D = calc_var_func(pdf, b_max);
	I = calc_mean_func(pdf, b_max);

	for( ; k < b_max; k++)
	{
		result += (k - I)*(k - I)*(k - I)*(k - I)*pdf[k];
	}

	result = result/(D*D) - 3.0;

	return result;
}

float calc_skewness_func(float *pdf, uint32_t b_max)
{
	float result = 0.0;
	float D;
	float I;
	uint32_t k = 0;

	D = calc_var_func(pdf, b_max);
	I = calc_mean_func(pdf, b_max);

	for( ; k < b_max; k++)
	{
		result += (k - I)*(k - I)*(k - I)*pdf[k];
	}

	result = result/(D*sqrt(D));

	return result;
}

float calc_uniformity_func(float *pdf, uint32_t b_max)
{
	float result = 0.0;
	uint32_t k = 0;

	for( ; k < b_max; k++)
	{
		result += pdf[k]*pdf[k];
	}

	return result;

}

float calc_entropy_func(float *pdf, uint32_t b_max)
{
	float result = 0.0;
	uint32_t k = 0;
	float epsilon = 0.000000001;

	for( ; k < b_max; k++)
	{
		float tmp;
		if(pdf[k] == 0.0)
//			tmp = pdf[k] + epsilon;
			continue;
		else
			tmp = pdf[k];

		result += pdf[k]*log2(pdf[k]);
	}

	return -result;

}

#endif
