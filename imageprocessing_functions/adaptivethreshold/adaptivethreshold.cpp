/* ==================================================================== */
/* Author :Priyanka Hiranandani NIT Surat                               */
/* ==================================================================== */
/* Syntax : return_image=adaptivethreshold(InputArray src, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)  */
/* ==================================================================== */
/*The function transforms a grayscale image to a binary image according to the formulae:*/
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
  int adaptivethreshold(char *fname, unsigned long fname_len)
    {
    // Error management variable
        SciErr sciErr;
    //variable info
	int iRows		= 0;
	int iCols		= 0;
        int piRows		= 0;
	int piCols		= 0;
	int* piAddr		= NULL;
        int* piAddr2            = NULL;
        int* piAddr3            = NULL;
        int* piAddr4            = NULL;
        int* piAddr5            = NULL;
        int* piAddr6            = NULL;
        int* piAddrNew          = NULL;
	int* piLen		= NULL;
	double* pstData	        = NULL;
        char ** pstData2    	= NULL;
        double *rrows;
        double *rcols;
        double maxValue; 
        char **adaptiveMethod;
        char **thresholdType;
        double blockSize;
        double C;
        int i;
        int error;
         ////checking input argument 
        CheckInputArgument(pvApiCtx,6,6);
         //checking output argument
        CheckOutputArgument(pvApiCtx, 1, 1);
         //0for first argument 
         Mat img;
         retrieveImage(img,1);
    //second argument
           //fetching address of second argument
               sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
            //checking for error if any
               if (sciErr.iErr)
                {
                   printError(&sciErr, 0);
                   return 0;
                }
             //this function will fetch value of second argument
               sciErr = getMatrixOfDouble(pvApiCtx, piAddr2, &iRows, &iCols ,&pstData);
               error=getScalarDouble(pvApiCtx,piAddr2,&maxValue) ;  
               if(error!=0)
                {
                  sciprint("error in retrieving second argument");
                } 
  //third argument
            //fetching address of third argument
               sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
             //checking for error if any
               if (sciErr.iErr)
               {
                  printError(&sciErr, 0);
                  return 0;
               }
               sciErr = getMatrixOfString(pvApiCtx, piAddr3, &iRows, &iCols, NULL, NULL);
               piLen = (int*)malloc(sizeof(int) * iRows * iCols);
               //second call to retrieve length of each string of first argument
               sciErr = getMatrixOfString(pvApiCtx, piAddr3, &iRows, &iCols, piLen, NULL);
               if(sciErr.iErr)
               {
                  printError(&sciErr, 0);
                  return 0;
               }
               adaptiveMethod = (char**)malloc(sizeof(char*) * iRows * iCols);
               for( i = 0 ; i < iRows * iCols ; i++)
               {
                   adaptiveMethod[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
               }
               //third call to retrieve data of each string of first argument
               sciErr = getMatrixOfString(pvApiCtx, piAddr3, &iRows, &iCols, piLen, adaptiveMethod);
               if(sciErr.iErr)
               {
                  printError(&sciErr, 0);
                  return 0;
               }
             
               
 //fourth argument
              //fetching address of fourth argument
               sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
               if (sciErr.iErr)
               {
               printError(&sciErr, 0);
               return 0;
               }
                sciErr = getMatrixOfString(pvApiCtx, piAddr4, &iRows, &iCols, NULL, NULL);
               piLen = (int*)malloc(sizeof(int) * iRows * iCols);
               //second call to retrieve length of each string of first argument
               sciErr = getMatrixOfString(pvApiCtx, piAddr4, &iRows, &iCols, piLen, NULL);
               if(sciErr.iErr)
               {
                  printError(&sciErr, 0);
                  return 0;
               }
               thresholdType = (char**)malloc(sizeof(char*) * iRows * iCols);
               for(i = 0 ; i < iRows * iCols ; i++)
               {
                   thresholdType[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
               }
               //third call to retrieve data of each string of first argument
               sciErr = getMatrixOfString(pvApiCtx, piAddr4, &iRows, &iCols, piLen,thresholdType);
               if(sciErr.iErr)
               {
                  printError(&sciErr, 0);
                  return 0;
               }
             
   //fifth argument
               //fetching address of fifth argument
               sciErr = getVarAddressFromPosition(pvApiCtx,5,&piAddr5);
               if (sciErr.iErr)
               {
                printError(&sciErr, 0);
                return 0;
               }
                 //this function will fetch value of fifth argument
               error=getScalarDouble(pvApiCtx,piAddr5,&blockSize) ;  
               if(error!=0)
                {
                  sciprint("error in retrieving second argument");
                }      
//sixth argument
               //fetching address of sixth argument
               sciErr = getVarAddressFromPosition(pvApiCtx,6,&piAddr6);
               if (sciErr.iErr)
               {
                printError(&sciErr, 0);
                return 0;
               } 
                //this function will fetch value of sixth argument
               error=getScalarDouble(pvApiCtx,piAddr6,&C) ;  
               if(error!=0)
                {
                  sciprint("error in retrieving second argument");
                }       
               Mat dst;
               //calling adaptiveBilateralFilter function
               if(!(strcmp(adaptiveMethod[0],"ADAPTIVE_THRESH_MEAN_C"))&&strcmp(thresholdType[0],"THRESH_BINARY")))
               {
                adaptiveThreshold(img,dst,maxValue,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,blockSize,C);
               }
               else if(!(strcmp(adaptiveMethod[0],"ADAPTIVE_THRESH_MEAN_C")&&strcmp(thresholdType[0],"THRESH_BINARY_INV")))
               { 
                adaptiveThreshold(img,dst,maxValue,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV,blockSize,C);
               }
               else if(!(strcmp(adaptiveMethod[0],"ADAPTIVE_THRESH_GAUSSIAN_C")&&strcmp(thresholdType[0],"THRESH_BINARY")))
               {
                adaptiveThreshold(img,dst,maxValue,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,blockSize,C);
               }
               else if(!(strcmp(adaptiveMethod[0],"ADAPTIVE_THRESH_GAUSSIAN_C")&&strcmp(thresholdType[0],"THRESH_BINARY_INV")))
               {
                  adaptiveThreshold(img,dst,maxValue,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,blockSize,C);
               }    
               string tempstring = type2str(dst.type());
               char* checker = (char *)malloc(tempstring.size() + 1);
               memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
               returnImage(checker,dst,1);
               AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1 ;
               ReturnArguments(pvApiCtx);
               return 0;     
}
}
