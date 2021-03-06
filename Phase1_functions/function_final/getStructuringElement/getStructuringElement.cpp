/* ==================================================================== */
/* Author :Priyanka Hiranandani NIT Surat                               */
/* ==================================================================== */
/* Syntax :Mat_return=getStructuringElement(shape,size.x,size.y,point.x,point.y); 
/* ==================================================================== */
#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sciprint.h>
using namespace cv;
using namespace std;
  extern "C"
  {
  #include "api_scilab.h"
  #include "Scierror.h"
  #include "BOOL.h"
  #include <localization.h>
  #include "../common.h"
  int getStructuringElement(char *fname, unsigned long fname_len)
    {
    // Error management variable
        SciErr sciErr;
    //variable info
	int iRows		= 0;
	int iCols		= 0;
        int piRows		= 0;
	int piCols		= 0;
	int* piAddr1		= NULL;
        int* piAddr2            = NULL;
        int* piAddr3            = NULL;
        int* piAddr4            = NULL;
        int* piAddr5            = NULL;
        int* piAddr6            = NULL;
        int* piAddrNew            = NULL;
	int* piLen		= NULL;
	double* pstData	        = NULL;
        char** pstData2    	= NULL;
        double *rrows;
        double *rcols;
        int shape;
        int error;
        double sz1,sz2;
        double pi1,pi2;
        // checking input argument 
        CheckInputArgument(pvApiCtx,5,5);
        //checking output argument
        CheckOutputArgument(pvApiCtx, 1, 1);
        //first argument
        sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr1);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        //this function will fetch value of first argument
        sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, NULL, NULL);
        if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    //second call to retrieve length of each string
        sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen, NULL);
        if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }

        pstData2 = (char**)malloc(sizeof(char*) * iRows * iCols);
        for(int i = 0 ; i < iRows * iCols ; i++)
        {
        pstData2[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
        }
        //third call to retrieve data
        sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen, pstData2);
        if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        if(!strcmp(pstData2[0],"MORPH_RECT "))
        {
        shape=MORPH_RECT;
        }
        else if(!strcmp(pstData2[0],"MORPH_ELLIPSE"))
        {
        shape=MORPH_ELLIPSE;
        }
        else if(!strcmp(pstData2[0],"MORPH_CROSS"))
        {
        shape=MORPH_CROSS;
        }
        else if(!strcmp(pstData2[0],"CV_SHAPE_CUSTOM "))
       {
        shape= CV_SHAPE_CUSTOM;
       }
        //second argument
        sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        //this function will fetch value of second argument
        error=getScalarDouble(pvApiCtx,piAddr2,&sz1) ;  
        if(error!=0)
        {
          sciprint("error in retrieving second argument");
        } 
        //third argument
        sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        //this function will fetch value of third argument
       error=getScalarDouble(pvApiCtx,piAddr3,&sz2); 
        if(error!=0)
        {
          sciprint("error in retrieving second argument");
        } 
       //fourth argument
        sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        //this function will fetch value of fourth argument
        error=getScalarDouble(pvApiCtx,piAddr4,&pi1);   
        if(error!=0)
        {
          sciprint("error in retrieving second argument");
        }      
       
        //fifth argument
        sciErr = getVarAddressFromPosition(pvApiCtx,5,&piAddr5);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        //this function will fetch value of fifth argument
          error=getScalarDouble(pvApiCtx,piAddr5,&pi2);   
        if(error!=0)
        {
          sciprint("error in retrieving second argument");
        } 
        Size ksize=Size(sz1,sz2);
        Point anchor=Point(pi1,pi2);
        Mat dst;
        dst =getStructuringElement(shape,ksize,anchor);
        uchar depth = dst.type() & CV_MAT_DEPTH_MASK;
        double *n = NULL;
        int k=0;
        n = (double*)malloc(sizeof(double) *dst.rows *dst.cols);
        k=0;
    
        if(depth==CV_8S)
        {
          for(int i = 0;i < dst.rows;i++)
             {
        for(int j = 0;j < dst.cols;j++)
               {
           n[k] = dst.at<uchar>(i,j);k++;
               }
             }
        }
        else if(depth==CV_8U)
        {
          for(int i = 0;i < dst.rows;i++)
             {
        for(int j = 0;j < dst.cols;j++)
               {
           n[k] = dst.at<uchar>(i,j);k++;
               }
             }
        }
        else if(depth==CV_16S)
        {
          for(int i = 0;i < dst.rows;i++)
             {
        for(int j = 0;j < dst.cols;j++)
               {
           n[k] = dst.at<Vec3s>(i,j)[0];k++;
               }
             }
        }
        else if(depth==CV_16U)
        {
          for(int i = 0;i < dst.rows;i++)
             {
        for(int j = 0;j < dst.cols;j++)
               {
           n[k] = dst.at<Vec3s>(i,j)[0];k++;
               }
             }
        }
        else
        {
           for(int i = 0;i < dst.rows;i++)
             {
        for(int j = 0;j < dst.cols;j++)
               {
           n[k] = dst.at<Vec3d>(i,j)[0];k++;
               }
             }
        }
       
 //SciErr createMatrixOfInteger32(void* _pvCtx, int _iVar, int _iRows, int _iCols, const int* _piData32)
       sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1,1,dst.rows*dst.cols, n);
       free(n); // Data have been copied into Scilab memory
       if (sciErr.iErr)
        {
//Make sure everything is cleanup in case of error
        printError(&sciErr, 0);
        return 0;
        } 
        AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
        ReturnArguments(pvApiCtx);
        return 0;
  }
}
