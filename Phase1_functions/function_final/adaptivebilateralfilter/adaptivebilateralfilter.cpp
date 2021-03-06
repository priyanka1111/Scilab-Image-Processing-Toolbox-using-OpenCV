/* ==================================================================== */
/* Author :Priyanka Hiranandani NIT Surat                               */
/* ==================================================================== */
/* Syntax : return_image=adaptivebilateralfilter(InputArray src,int size_height,int size_width, double sigmaSpace,int point_x,int point_y)                                                                */
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
  int adaptivebilateralfilter(char *fname, unsigned long fname_len)
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
        int* piAddrNew            = NULL;
	int* piLen		= NULL;
	double* pstData	        = NULL;
        int* pstData2    	= NULL;
        double *rrows;
        double *rcols;
        unsigned char *pstDataR = NULL;
        unsigned char *pstDataG = NULL;
        unsigned char *pstDataB = NULL;
        int noofitem;
        double sigmaSpace;
        double sz1,sz2;
        double pi1,pi2;
        int error;
         ////checking input argument 
        CheckInputArgument(pvApiCtx,6,6);
         //checking output argument
        CheckOutputArgument(pvApiCtx, 1, 1);
         //for first argument 
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
               error=getScalarDouble(pvApiCtx,piAddr2,&sz1); 
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
             //this function will fetch value of third argument
              error=getScalarDouble(pvApiCtx,piAddr3,&sz2); 
               if(error!=0)
               {
                  sciprint("error in retrieving third argument");
               }     
              
 //fourth argument
              //fetching address of fourth argument
               sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
               if (sciErr.iErr)
               {
               printError(&sciErr, 0);
               return 0;
               }
                //this function will fetch value of fourth argument
               error=getScalarDouble(pvApiCtx,piAddr4,&sigmaSpace); 
               if(error!=0)
               {
                  sciprint("error in retrieving fourth argument");
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
               error=getScalarDouble(pvApiCtx,piAddr5,&pi1); 
               if(error!=0)
               {
                  sciprint("error in retrieving fifth argument");
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
               error=getScalarDouble(pvApiCtx,piAddr6,&pi2); 
               if(error!=0)
               {
                  sciprint("error in retrieving sixth argument");
               }         
               //calling size constructor
               Size ksize=Size(sz1,sz2);
               //calling point constructor
               Point anchor=Point(pi1,pi2);
               Mat dst;
               //calling adaptiveBilateralFilter function
               adaptiveBilateralFilter(img,dst,ksize,sigmaSpace,20.0,anchor,BORDER_DEFAULT);
               string tempstring = type2str(dst.type());
               char* checker = (char *)malloc(tempstring.size() + 1);
               memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
               returnImage(checker,dst,1);
       //returning output variable    
               AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
               ReturnArguments(pvApiCtx); 
               return 0;
         }
}
