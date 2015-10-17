/* ==================================================================== */
/* Author :Priyanka Hiranandani NIT Surat                               */
/* ==================================================================== */
/* Syntax : return_double=pointpolygontest(InputArray contour, Point2f pt, bool measureDist)
/* ==================================================================== */
#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sciprint.h>
//#include<bits/stdc++.h>
using namespace cv;
using namespace std;
  extern "C"
  {
  #include "api_scilab.h"
  #include "Scierror.h"
  #include "BOOL.h"
  #include <localization.h>
  #include "../common.h"
  int pointpolygontest(char *fname, unsigned long fname_len)
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
	double *pstData	        = NULL;
        char **pstData2    	= NULL;
        double *rrows;
        double *rcols;
        double p1,p2;
        double *pst;
        double res;
        int error;
        //Point2f p;
        //checking input argument 
        CheckInputArgument(pvApiCtx,4,4);
        //checking output argument
        CheckOutputArgument(pvApiCtx, 1, 1);
         //for first argument 
         // get Address of first input  
        sciErr =getVarAddressFromPosition(pvApiCtx,1,&piAddr);
          //check for any error
             if(sciErr.iErr)   
               {
               printError(&sciErr, 0);
               return 0;
               }      
           //retrieve input array
          //SciErr getMatrixOfDouble(void* _pvCtx, int* _piAddress, int* _piRows, int* _piCols, double** _pdblReal)
        sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols,&pstData);
             if(sciErr.iErr)
               {
               printError(&sciErr, 0);
               return 0;
               }
        int k=0;
        vector<Point> contours;
        for(int i=0;i<iCols;i++)
               {   
               contours.push_back(Point2f(pstData[i],pstData[i+1])) ;   
               i++;
               }
  
    // get Address of second input
        sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
               if (sciErr.iErr)
               {
                printError(&sciErr, 0);
                return 0;
               } 
                //this function will fetch value of second argument
               error=getScalarDouble(pvApiCtx,piAddr2,&p1); 
               if(error!=0)
               {
                  sciprint("error in retrieving second argument");
               }  
              
    // get Address of third input
        sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
               if (sciErr.iErr)
               {
                printError(&sciErr, 0);
                return 0;
               } 
                //this function will fetch value of thierd argument
                error=getScalarDouble(pvApiCtx,piAddr3,&p2); 
               if(error!=0)
               {
                  sciprint("error in retrieving second argument");
               }  
              
               Point2f p=Point2f(p1,p2);
    //retriving 4rd argument
       sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
       sciErr = getMatrixOfString(pvApiCtx, piAddr4, &iRows, &iCols, NULL, NULL);
               if(sciErr.iErr)
               {
               printError(&sciErr, 0);
               return 0;
               }
       piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    //second call to retrieve length of each string of first argument
       sciErr = getMatrixOfString(pvApiCtx, piAddr4, &iRows, &iCols, piLen, NULL);
               if(sciErr.iErr)
               {
               printError(&sciErr, 0);
               return 0;
               }
       pstData2 = (char**)malloc(sizeof(char*) * iRows * iCols);
       for(int 	i = 0 ; i < iRows * iCols ; i++)
               {
       pstData2[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
               }
    //third call to retrieve data of each string of first argument
       sciErr = getMatrixOfString(pvApiCtx, piAddr4, &iRows, &iCols, piLen, pstData2);
               if(sciErr.iErr)
               {
               printError(&sciErr, 0);
               return 0;
               }
        //comparing arguments
               if(!strcmp("True",pstData2[0]))
               {
           
                res=pointPolygonTest(contours, p,true);
               }
               else if(!strcmp("False",pstData2[0]))
               {
               res=pointPolygonTest(contours,p,false);
               }
        
      
   //SciErr createMatrixOfUnsignedInteger8(void* _pvCtx, int _iVar, int _iRows, int _iCols, const unsigned char* _pucData8)
             
               error=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,res);
               if(error!=0)
               {
                    sciprint("error occurred");
                    return 0;    
               }  
    ////////// Return the output arguments to the Scilab engine //////////

               AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;

               ReturnArguments(pvApiCtx);    

               return 0;     
}
}
