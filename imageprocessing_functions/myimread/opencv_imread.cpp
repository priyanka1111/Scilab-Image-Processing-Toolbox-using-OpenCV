/* ==================================================================== */
/* Author :Priyanka Hiranandani NIT Surat                               */
/* ==================================================================== */
/* Syntax :return_mat=imread(String_path_to_iamge,int flag);*/
/* ==================================================================== */
#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
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
int opencv_imread(char *fname, unsigned long fname_len)
{
    // Error management variable
    SciErr sciErr;
    // Variables declaration //
    int iLen        = 0;
    int iRows       = 0;
    int iCols       = 0;
    int *piAddr1    = NULL;
    int *piAddr    = NULL;
    int *piAddrNew  = NULL;
    int piRows      = 0;
    int piCols      = 0;        
    int *piLen      = NULL;
    char **pstData  = NULL;
    char **pstData1  = NULL;
    int i,j,k=0;
    //function to check number of input variable
    CheckInputArgument(pvApiCtx, 2, 2);
    //function to check number of output variable
    CheckOutputArgument(pvApiCtx, 1, 1) ;
    // get Address of first inputs
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr);
    //check for any error
    if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
    //***************************fetching first argument******************************************//
    //first call to retrieve dimensions of first argument 
    sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, NULL, NULL);
    if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
    piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    //second call to retrieve length of each string of first argument
    sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, piLen, NULL);
    if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
    pstData = (char**)malloc(sizeof(char*) * iRows * iCols);
    for(i = 0 ; i < iRows * iCols ; i++)
        {
        pstData[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
        }
    //third call to retrieve data of each string of first argument
    sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, piLen, pstData);
    if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
     //calling imread function of open cv  
//***************************fetching second argument******************************************//
//first call to retrieve dimensions of second argument
     sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr1);
    //check for any error
    if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, NULL, NULL);
    if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
    piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    //second call to retrieve length of each string of first argument
    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen, NULL);
    if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
    pstData1 = (char**)malloc(sizeof(char*) * iRows * iCols);
    for(i = 0 ; i < iRows * iCols ; i++)
        {
        pstData1[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
        }
    //third call to retrieve data of each string of first argument
    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen, pstData1);
    if(sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
     Mat img;
     if(!strcmp(pstData1[0],"CV_LOAD_IMAGE_UNCHANGED"))
     {
          img = imread(pstData[0],CV_LOAD_IMAGE_UNCHANGED);
     }
      if(!strcmp(pstData1[0],"CV_LOAD_IMAGE_GRAYSCALE"))
     {
          img = imread(pstData[0],CV_LOAD_IMAGE_GRAYSCALE);
     }
     else if(!strcmp(pstData1[0],"CV_LOAD_IMAGE_COLOR"))
     {
          img = imread(pstData[0],CV_LOAD_IMAGE_COLOR);
     }  
     else if(!strcmp(pstData1[0],"CV_LOAD_IMAGE_ANYDEPTH"))
     {
          img = imread(pstData[0],CV_LOAD_IMAGE_ANYDEPTH);
     }  
     else if(!strcmp(pstData1[0],"CV_LOAD_IMAGE_ANYCOLOR"))
     {
          img = imread(pstData[0],CV_LOAD_IMAGE_ANYCOLOR);
     } 
    // free(pstData1);
    // free(pstData);               
     string tempstring = type2str(img.type());
     char* checker = (char *)malloc(tempstring.size() + 1);
     memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
     returnImage(checker,img,1);
    //Assigning the list as the Output Variable
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx); 
    return 0;
}
/* ==================================================================== */
}
