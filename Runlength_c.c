#include <mex.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Bins of length [1],[2],[3-4],[5-8],[9-16],[17-32],[33-64],[65-128],[129-]*/
#define LENGTH2BIN(P) ((P) >128?8:LUT[(P)-1])
int LUT[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

void DoVerticalRunlength(int h, int w, int *im, int *RL);
void DoHorizontalRunlength(int h, int w, int *im, int *RL);
void DoDiagonalRunlength(int h, int w, int *im, int *RL);
void DoAntiDiagonalRunlength(int h, int w, int *im, int *RL);

void mexFunction(int nout, mxArray *out[], int nin, const mxArray *in[])
{
    /* in */
    /* [0]: im        
    
     */
    
    /* out */
    /* [0]: runlength             
     */
        
    /* variables */    
    int height;
    int width;	
    
    int *im;
    int *RL;
    int L = 4*9*2;   
    int i;
    
    /* Init misc */
    /* Remember im is in column-major order because of matlab! */
    im = (int *)mxGetData(in[0]);
    height = (int)mxGetM(in[0]);
	width = (int)mxGetN(in[0]);
    
    mwSize dims[1]={L};
    out[0] = mxCreateNumericArray(1,dims, mxINT32_CLASS,mxREAL);
	RL = (int *)mxGetData(out[0]);
    for (i=0; i < L; ++i)
        RL[i]=0;
   
    
    DoVerticalRunlength(height, width, im, RL);
    DoHorizontalRunlength(height, width, im, &RL[18]);
    DoDiagonalRunlength(height, width, im, &RL[36]);
    DoAntiDiagonalRunlength(height, width, im, &RL[54]);
}

void DoVerticalRunlength(int h, int w, int *im, int *RL)
{
    int x, y;
    int *p;
    int currentV, currentL;
    
    for (x=0; x < w; ++x)
    {
        p = &im[x*h];
        currentV = *p;
        currentL = 1;
        p++;
        for (y=1; y < h; ++y, ++p)
        {
            if (*p==currentV)
                currentL++;
            else
            {
                RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
                currentV = *p;
                currentL=1;
            }
        }
        RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
    }
}

void DoHorizontalRunlength(int h, int w, int *im, int *RL)
{
    int x, y;
    int *p;
    int currentV, currentL;
    
    for (y=0; y < h; ++y)
    {
        p = &im[y];
        currentV = *p;
        currentL = 1;
        p+=h;
        for (x=1; x < w; ++x, p+=h)
        
        {
            if (*p==currentV)
                currentL++;
            else
            {
                RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
                currentV = *p;
                currentL=1;
            }
        }
        RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
    }
}

void DoDiagonalRunlength(int h, int w, int *im, int *RL)
{
    int x, y;
    int ty, tx;
    int currentV, currentL;
    
    //Two passes, from up to down and then from left to right
    
    for (y=0; y < h; ++y)
    {
        ty=y;
        currentV = im[y];
        currentL = 1;
        for (x=1; x < w && ty < h; ++x, ++ty)
        {
            if (im[ty+x*h]==currentV)
                currentL++;
            else
            {
                RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
                currentV = im[ty+x*h];
                currentL=1;
            }
        }
        RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
    }
    
    for (x=1; x < w; ++x)
    {
        tx=x;
        currentV = im[x*h];
        currentL = 1;
        for (y=1; y < h && tx < w; ++y, ++tx)
        {
            if (im[y+tx*h]==currentV)
                currentL++;
            else
            {
                RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
                currentV = im[y+tx*h];
                currentL=1;
            }
        }
        RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
    } 
}

void DoAntiDiagonalRunlength(int h, int w, int *im, int *RL)
{
    int x, y;
    int ty, tx;
    int currentV, currentL;
    
    //Two passes, from up to down and then from left to right
    
    for (y=0; y < h; ++y)
    {
        ty=y;
        currentV = im[(w-1)*h + y];
        currentL = 1;
        for (x=w-1; x >=0 && ty < h; --x, ++ty)
        {
            if (im[ty+x*h]==currentV)
                currentL++;
            else
            {
                RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
                currentV = im[ty+x*h];
                currentL=1;
            }
        }
        RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
    }
    
    for (x=(w-2); x >= 0; --x)
    {
        tx=x;
        currentV = im[x*h];
        currentL = 1;
        for (y=1; y < h && tx >= 0; ++y, --tx)
        {
            if (im[y+tx*h]==currentV)
                currentL++;
            else
            {
                
                RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
                currentV = im[y+tx*h];
                currentL=1;
            }
        }
        RL[ (9*currentV) + LENGTH2BIN(currentL)]++;
    } 
}
