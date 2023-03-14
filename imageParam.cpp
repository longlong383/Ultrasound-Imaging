#include "imageParam.h"
#include "iostream"

using namespace std;

imageParam::imageParam()
{
    //initializing variables
    numElement = 128;
    numSample = 3338;
    numScanline = 127;
    elementPosition = genElementPosition();
    scanlinePosition = genScanlinePosition(numElement, PITCH, elementPosition);
}

imageParam::~imageParam()
{
    //deleting arrays
    deletePositionArray();
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{  
    float *eleLocation;
   eleLocation = new float[numElement];
   //creating element locations
   for (int i = 0; i < numElement; i++)
   {
        eleLocation[i] = (i-((float)(numElement-1.0)/2.0))*PITCH;
   }
   return eleLocation;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    //retrieve data components from user
    cout << "Requested Imaging Depth: ";
    cin >> desiredDepth;
    cout << endl << "Requested number of pixels: ";
    cin >> numPixel;

    //initializing 2d array for pixel locations
    float2 **scanlineLocation;
    scanlineLocation  = new float2*[numPixel]; 
    //depth increment used to determine y coordinate
    float increment = desiredDepth/(numPixel-1);
    for(int i = 0; i < numScanline; i++){
        scanlineLocation[i] = new float2[numPixel];
        float start = 0;
        for(int j = 0; j < numPixel; j++){
            //obtaining lateral position x of the pixel
            scanlineLocation[i][j].x = (i-(numScanline/2))*PITCH;
            //obtaining the depth of the pixel
            scanlineLocation[i][j].y = start;
            start += increment;
        }
    }

    return scanlineLocation;

}

//retrieving x position based on specific scanline and pixel
float imageParam::getXPosition(int scanline, int pixel)
{
    float imagePara = scanlinePosition[scanline][pixel].x;
    return imagePara;
}

//retrieving y position based on specific scanline and pixel
float imageParam::getYPosition(int scanline, int pixel)
{
    float imagePara = scanlinePosition[scanline][pixel].y;
    return imagePara;
}
//retrieving specific element
float imageParam::getElementPosition(int element)
{
    float element1 = elementPosition[element];
    return element1;
}

//retrieving imaging parameters for the next four functions
int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline() 
{
    return numScanline;
}

int imageParam::getNumPixel() 
{
    return numPixel;
}

void imageParam::deletePositionArray()
{
    //deleting each scanline
    for (int i = 0; i < numScanline; i++)
    {
        delete[] scanlinePosition[i];
    }
    delete[] elementPosition;
}









