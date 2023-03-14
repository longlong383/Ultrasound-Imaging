#include "BmodeClass.h"
#include "iostream"
using namespace std;
BmodeClass::BmodeClass()
{
    //initializing variables
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params, dataBuffer *data, int numline)
{
    //assiging variables values
    imparams = params;
    RFData = data;
    line = numline;
    //reference scanline to createscanline to fill it up
    scanline = createScanline(imparams->getNumPixel());
    beamform();
}

BmodeClass::~BmodeClass()
{
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    //creating scanline for use later on
    float *mem;
    mem = new float[numPixel];
    return mem;
}

void BmodeClass::beamform()
{
    // real and imag parts of the magnitude
    float real = 0;
    float imag = 0;
    
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        for (int y = 0; y < imparams->getNumElement(); y++)
        {
            // calculation of tfoward
            float tForward = imparams->getYPosition(line, i) / (imparams->SOS);
            // tBackward
            float tBackward = sqrt(pow(imparams->getYPosition(line, i), 2) + pow(imparams->getXPosition(line, i) - imparams->getElementPosition(y), 2)) / (imparams->SOS);
            // total flight time
            float tTotal = tForward + tBackward;
            // calculating of which sample matches with scanline location
            int sample = floor(tTotal * (imparams->FS));
            // only runs if sample is less than numSample; else, it skips and keeps going
            if (sample < imparams->getNumSample())
            {
                real += RFData->getRealRFData(y, sample);

                imag += RFData->getImagRFData(y, sample);
            }
        }

        // echo magnitude for this position
        scanline[i] = sqrt(pow(real, 2) + pow(imag, 2));
        real = 0;
        imag = 0;
    }
}

void BmodeClass::getScanline(float *data)
{
    //copying content in scanline to data so that scanline (up above) can be filled up
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i];
    }
}

void BmodeClass::deleteScanline()
{
    //delete scanline (self explanatory)
    delete[] scanline;
}