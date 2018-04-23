/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following student struct:
 */
const team_t team = {
    "cost2833@colorado.edu", //Replace this with your email address.
    ""                   //Replace this with your partner's email address. Leave blank if working alone.
};

/***************
 * FLIP KERNEL
 ***************/

#define RIDX_M(m, j) ((m)+(j))


/******************************************************
 * Your different versions of the flip kernel go here
 ******************************************************/

/*
 * naive_flip - The naive baseline version of flip
 */
char naive_flip_descr[] = "naive_flip: Naive baseline implementation";
void naive_flip(int dim, pixel *src, pixel *dst)
{
    int i, j;
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim; j++){
            dst[RIDX_F(i, j, dim)].red   = src[RIDX(i, j, dim)].red;
            dst[RIDX_F(i, j, dim)].green = src[RIDX(i, j, dim)].green;
            dst[RIDX_F(i, j, dim)].blue  = src[RIDX(i, j, dim)].blue;
        }
    }
}

char func_flip_descr[] = "minimized function calls in inner loop";
void func_flip(int dim, pixel *src, pixel *dst)
{
  int i, j;
  for (i = 0; i < dim; i++){
    for (j = 0; j < dim; j++){
      int didx = RIDX_F(i, j, dim);
      int sidx = RIDX(i, j, dim);
      dst[didx].red   = src[sidx].red;
      dst[didx].green = src[sidx].green;
      dst[didx].blue  = src[sidx].blue;
    }
  }
}

char row_flip_descr[] = "change row-column ordering";
void row_flip(int dim, pixel *src, pixel *dst)
{
  int i, j;
  for (i = 0; i < dim; i++) {
    for (j = 0; j< dim; j++) {
      int didx = RIDX_F(j, i, dim);
      int sidx = RIDX(j, i, dim);
      dst[didx].red   = src[sidx].red;
      dst[didx].green = src[sidx].green;
      dst[didx].blue  = src[sidx].blue;
    }
  }
}

char mult_flip_descr[] = "move multiplication outside inner loop";
void mult_flip(int dim, pixel *src, pixel *dst)
{
  int i, j;
  for (i = 0; i < dim; i++){
    int m = i*dim;
    for (j = 0; j < dim; j++){
      int didx = RIDX_F(i, j, dim);
      int sidx = RIDX_M(m, j);
      dst[didx].red   = src[sidx].red;
      dst[didx].green = src[sidx].green;
      dst[didx].blue  = src[sidx].blue;
    }
  }
}

char mem_flip_descr[] = "minimized memory access in addition to function calls";
void mem_flip(int dim, pixel *src, pixel *dst)
{
  int i, j;
  for (i = 0; i < dim; i++){
    for (j = 0; j < dim; j++){
      int didx = RIDX_F(i, j, dim);
      int sidx = RIDX(i, j, dim);
      pixel *d = &dst[didx];
      pixel *s = &src[sidx];
      d->red   = s->red;
      d->green = s->green;
      d->blue  = s->blue;
    }
  }
}

void unroll2_flip(int dim, pixel *src, pixel *dst)
{
  int i,j;
  int lim = dim-1;
  for (i = 0; i < dim; i++){
    for (j = 0; j < lim; j+=2){
      int k = j+1;
      dst[RIDX_F(i, j, dim)].red = src[RIDX(i, j, dim)].red;
      dst[RIDX_F(i, j, dim)].green = src[RIDX(i, j, dim)].green;
      dst[RIDX_F(i, j, dim)].blue = src[RIDX(i, j, dim)].blue;

      dst[RIDX_F(i, k, dim)].red = src[RIDX(i, k, dim)].red;
      dst[RIDX_F(i, k, dim)].green = src[RIDX(i, k, dim)].green;
      dst[RIDX_F(i, k, dim)].blue = src[RIDX(i, k, dim)].blue;
    }
  }
}

/*
 * flip - Your current working version of flip
 * IMPORTANT: This is the version you will be graded on
 */
char flip_descr[] = "flip: Current working version";
char unroll_descr[] = "flip: unroll twice";
void flip(int dim, pixel *src, pixel *dst)
{
  row_flip(dim, src, dst);
}

/*********************************************************************
 * register_flip_functions - Register all of your different versions
 *     of the flip kernel with the driver by calling the
 *     add_flip_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_flip_functions()
{
    add_flip_function(&flip, flip_descr);
    //add_flip_function(&row_flip, row_flip_descr);
    //add_flip_function(&naive_flip, naive_flip_descr);
    /* ... Register additional test functions here */
    //add_flip_function(&func_flip, func_flip_descr);
    //add_flip_function(&mem_flip, mem_flip_descr);
    //add_flip_function(&naive_flip, naive_flip_descr);
}


/***************
 * CONVOLVE KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the convolve function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute a pixel value */
typedef struct {
    float red;
    float green;
    float blue;
    float weight;
} pixel_sum;

/******************************************************
 * Your different versions of the convolve kernel go here
 ******************************************************/

/*
 * naive_convolve - The naive baseline version of convolve
 */
char naive_convolve_descr[] = "naive_convolve: Naive baseline implementation";
void naive_convolve(int dim, pixel *src, pixel *dst)
{
    int i, j, ii, jj, curI, curJ;
    pixel_sum ps;

    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            ps.red    = 0.0;
            ps.green  = 0.0;
            ps.blue   = 0.0;
            ps.weight = 0.0;
            for (jj = -2; jj <= 2; jj++){
                for (ii = -2; ii <= 2; ii++){
                    curJ = j+jj;
                    if(curJ<0 || curJ>=dim){
                        continue;
                    }
                    curI = i+ii;
                    if(curI<0 || curI>=dim){
                        continue;
                    }
                    ps.red   += src[RIDX(curI, curJ, dim)].red *   kernel[ii+2][jj+2];
                    ps.green += src[RIDX(curI, curJ, dim)].green * kernel[ii+2][jj+2];
                    ps.blue  += src[RIDX(curI, curJ, dim)].blue *  kernel[ii+2][jj+2];
                    ps.weight += kernel[ii+2][jj+2];
                }
            }
            dst[RIDX(i,j,dim)].red   = (unsigned short)(ps.red/ps.weight);
            dst[RIDX(i,j,dim)].green = (unsigned short)(ps.green/ps.weight);
            dst[RIDX(i,j,dim)].blue  = (unsigned short)(ps.blue/ps.weight);
        }
    }
}

char func_convolve_descr[] = "func_convolve: minimize function calls within loops";
void func_convolve(int dim, pixel *src, pixel *dst)
{
    int i, j, ii, jj, curI, curJ;
    pixel_sum ps;

    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            ps.red    = 0.0;
            ps.green  = 0.0;
            ps.blue   = 0.0;
            ps.weight = 0.0;
            for (jj = -2; jj <= 2; jj++){
                for (ii = -2; ii <= 2; ii++){
                    curJ = j+jj;
                    if(curJ<0 || curJ>=dim){
                        continue;
                    }
                    curI = i+ii;
                    if(curI<0 || curI>=dim){
                        continue;
                    }
                    int sidx = RIDX(curI, curJ, dim);
                    ps.red   += src[sidx].red *   kernel[ii+2][jj+2];
                    ps.green += src[sidx].green * kernel[ii+2][jj+2];
                    ps.blue  += src[sidx].blue *  kernel[ii+2][jj+2];
                    ps.weight += kernel[ii+2][jj+2];
                }
            }
            int didx = RIDX(i,j,dim);
            dst[didx].red   = (unsigned short)(ps.red/ps.weight);
            dst[didx].green = (unsigned short)(ps.green/ps.weight);
            dst[didx].blue  = (unsigned short)(ps.blue/ps.weight);
        }
    }
}

char row_convolve_descr[] = "row_convolve: switch row-column ordering";
void row_convolve(int dim, pixel *src, pixel *dst)
{
    int i, j, ii, jj, curI, curJ;
    pixel_sum ps;

    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            ps.red    = 0.0;
            ps.green  = 0.0;
            ps.blue   = 0.0;
            ps.weight = 0.0;
            for (jj = -2; jj <= 2; jj++){
                for (ii = -2; ii <= 2; ii++){
                    curJ = j+jj;
                    if(curJ<0 || curJ>=dim){
                        continue;
                    }
                    curI = i+ii;
                    if(curI<0 || curI>=dim){
                        continue;
                    }
                    int sidx = RIDX(curJ, curI, dim);
                    ps.red   += src[sidx].red *   kernel[jj+2][ii+2];
                    ps.green += src[sidx].green * kernel[jj+2][ii+2];
                    ps.blue  += src[sidx].blue *  kernel[jj+2][ii+2];
                    ps.weight += kernel[jj+2][ii+2];
                }
            }
            int didx = RIDX(j,i,dim);
            dst[didx].red   = (unsigned short)(ps.red/ps.weight);
            dst[didx].green = (unsigned short)(ps.green/ps.weight);
            dst[didx].blue  = (unsigned short)(ps.blue/ps.weight);
        }
    }
}

char row_convolve2_descr[] = "row_convolve: switch row-column ordering and remove some arithmetic";
void row_convolve2(int dim, pixel *src, pixel *dst)
{
    int i, j, ii, jj, curI, curJ;
    pixel_sum ps;

    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            ps.red    = 0.0;
            ps.green  = 0.0;
            ps.blue   = 0.0;
            ps.weight = 0.0;
            for (jj = -2; jj <= 2; jj++){
                for (ii = -2; ii <= 2; ii++){
                    curJ = j+jj;
                    if(curJ<0 || curJ>=dim){
                        continue;
                    }
                    curI = i+ii;
                    if(curI<0 || curI>=dim){
                        continue;
                    }
                    int sidx = RIDX(curJ, curI, dim);
                    int jk = jj+2;
                    int ik = ii+2;
                    ps.red   += src[sidx].red *   kernel[jk][ik];
                    ps.green += src[sidx].green * kernel[jk][ik];
                    ps.blue  += src[sidx].blue *  kernel[jk][ik];
                    ps.weight += kernel[jk][ik];
                }
            }
            int didx = RIDX(j,i,dim);
            dst[didx].red   = (unsigned short)(ps.red/ps.weight);
            dst[didx].green = (unsigned short)(ps.green/ps.weight);
            dst[didx].blue  = (unsigned short)(ps.blue/ps.weight);
        }
    }
}

/*
 * convolve - Your current working version of convolve.
 * IMPORTANT: This is the version you will be graded on
 */
char convolve_descr[] = "convolve: Current working version";
void convolve(int dim, pixel *src, pixel *dst)
{
    row_convolve2(dim, src, dst);
}

/*********************************************************************
 * register_convolve_functions - Register all of your different versions
 *     of the convolve kernel with the driver by calling the
 *     add_convolve_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_convolve_functions() {
    add_convolve_function(&convolve, convolve_descr);
    add_convolve_function(&row_convolve, row_convolve_descr);
    add_convolve_function(&func_convolve, func_convolve_descr);
    //add_convolve_function(&naive_convolve, naive_convolve_descr);
    /* ... Register additional test functions here */
}
