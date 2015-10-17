/* ==================================================================== */
/* Author :Priyanka Hiranandani NIT Surat                               */
/* ==================================================================== */
/* overloaded function                                                  */
/* Syntax : return_matrix_3_xyz_values=xyz2lab(matrix_of_3_labvalues a)  */
/* ==================================================================== */
/* ==================================================================== */
#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include<stdio.h>
#include <sciprint.h>
#include<string.h>
using namespace cv;
using namespace std;
  extern "C"
  {
  #include "api_scilab.h"
  #include "Scierror.h"
  #include "BOOL.h"
  #include <localization.h>
  #include "../common.h"
  #define REF_X .9504; // Observer= 2°, Illuminant= D65
  #define REF_Y 1.00000;
  #define REF_Z 1.08883;

struct Color{
    float R,G,B,X,Y,Z,L,a,b;
};
Color xyz2lab3(float X,float Y, float Z){
    float eps = 216.f/24389.f;
    float k = 24389.f/27.f;
    float fx,fy,fz,Ls,as,bs;
    float xr=X/REF_X;
    float yr=Y/REF_Y;
    float zr=Z/REF_Z;
    if ( xr > eps )
          fx =  (float)pow(xr, 1/3.);
    else
          fx = (float) ((k * xr + 16.) / 116.);
    if ( yr > eps )
          fy =  (float)pow(yr, 1/3.);
    else
          fy = (float) ((k * yr + 16.) / 116.);
    if ( zr > eps )
          fz =  (float)pow(zr, 1/3.);
    else
         fz = (float) ((k * zr + 16.) / 116);
         Ls = ( 116 * fy ) - 16;
         as = 500*(fx-fy);
         bs = 200*(fy-fz);
    //Ls=2.55*Ls + .5;
    //as=as + .5;
    //bs=bs + .5; 
    Color lab;
    lab.L =Ls; 
    lab.a =as;
    lab.b =bs;
    return lab;
} 
 Color xyz2lab2(float X,float Y, float Z,char *s){
    double REF_X1;
    double REF_Y1;
    double REF_Z1;
    if(!strcmp(s,"a"))
    {
          REF_X1=1.0985; 
          REF_Y1= 1.0000;
          REF_Z1=0.3558;
    }
    else if(!strcmp(s,"c"))
    {
          REF_X1=0.9807; 
          REF_Y1= 1.0000;
          REF_Z1=1.1822;
    }
    else if(!strcmp(s,"d50"))
    {
          REF_X1=0.9642; 
          REF_Y1= 1.0000;
          REF_Z1=0.8251;
    }
     else if(!strcmp(s,"d65"))
    {
          REF_X1=0.9504;
          REF_Y1= 1.0000;
          REF_Z1= 1.0888;
    }
    else if(!strcmp(s,"icc"))
    {
          REF_X1=0.962; 
          REF_Y1=1.000;
          REF_Z1= 0.8249;
    }
     else if(!strcmp(s,"e"))
    {
          REF_X1=1.000;  
          REF_Y1=1.000;
          REF_Z1=1.000;
    }
    float x = X / REF_X1;
    float y = Y / REF_X1;
    float z = Z / REF_X1;

    if ( x > 0.008856 ) { x = pow( x , .3333333333f ); }
    else { x = ( 7.787 * x ) + ( 16/116.0 ); }
    if ( y > 0.008856 ) { y = pow( y , .3333333333f ); }
    else { y = ( 7.787 * y ) + ( 16/116.0 ); }
    if ( z > 0.008856 ) { z = pow( z , .3333333333f ); }
    else { z = ( 7.787 * z ) + ( 16/116.0 ); }

    Color lab;
    lab.L = ( 116 * y ) - 16;
    lab.a = 500 * ( x - y );
    lab.b = 200 * ( y - z );
    return lab;
}  
  int xyz2lab(char *fname, unsigned long fname_len)
    {
   
   // Error management variable
        SciErr sciErr;
    //variable info
	int iRows		= 0;
	int iCols		= 0;
        int piRows		= 0;
	int piCols		= 0;
        int* piAddr=NULL;
        int* piAddr1=NULL;
        int* piAddr3=NULL;
        double *value=NULL;
        int* piLen		= NULL;
        char **val;
        int i,j;
        int error;
        Color out;
        double check;
        Mat img,dst;
        float R,G,B;
        int *piAddrNew = NULL;                      
         //checking output argument
          CheckOutputArgument(pvApiCtx,1,1);
         //checking if number of input arguments are 3
        
         int k=0;
        // SciErr getMatrixOfDoubleInList(void* _pvCtx, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, double** _pdblReal)
                    double *pstDataR = NULL;
                    double *pstDataG = NULL;
                    double *pstDataB = NULL; 
                    sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr);
                    if(sciErr.iErr)   
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }
                    //retrive the matrix of the R values   
                    sciErr =  getMatrixOfDoubleInList(pvApiCtx, piAddr, 1, &iRows, &iCols, &pstDataR);
                    if(sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }
                    //retrive address of the list
                    sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr);
                    if(sciErr.iErr)   
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }   
                    //retrive the matrix of the G values 
                    sciErr = getMatrixOfDoubleInList(pvApiCtx, piAddr, 2, &iRows, &iCols, &pstDataG);
                    if(sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }
                    //retrive address of the list
                    sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr);
                    if(sciErr.iErr)   
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }   
                    //retrive the matrix of the B values 
                    sciErr = getMatrixOfDoubleInList(pvApiCtx, piAddr, 3, &iRows, &iCols, &pstDataB);
                    if(sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

         double *r,*g,*b;
         r=(double *)malloc(sizeof(double)*iRows*iCols);
         g=(double *)malloc(sizeof(double)*iRows*iCols);
         b=(double *)malloc(sizeof(double)*iRows*iCols);
                               for(int i=0;i<iRows;i++)
                               {
                                  for(int j=0;j<iCols;j++)
                                   {
                                       
                                            R= (pstDataR[k]);
                                            G= (pstDataG[k]);
                                            B= (pstDataB[k++]);
                                            out=xyz2lab3(R,G,B);
                                            cout<<R<<"\n";
                                            cout<<G<<"\n";
                                            cout<<B<<"\n";       
                                            r[j*iRows+i]=(out.L);
                                            g[j*iRows+i]=(out.a);
                                            b[j*iRows+i]=(out.b);  
                                   }
                               }
                     
    sciErr = createList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, 3, &piAddrNew);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }


    //Adding the R value matrix to the list
    //Syntax : createMatrixOfInteger32InList(void* _pvCtx, int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, const int* _piData)
    sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx)+1 , piAddrNew, 1, iRows,iCols, r);
    free(r);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    //Adding the G value matrix to the list
    sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx)+1 , piAddrNew, 2, iRows, iCols, g);
    free(g);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    //Adding the B value matrix to the list
    sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx)+1 , piAddrNew, 3, iRows, iCols, b);
    free(b);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

              
             AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
            ReturnArguments(pvApiCtx);            
            return 0;                
}                      

   }