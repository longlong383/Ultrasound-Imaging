#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    //assigning values to initialized variables/arrays
    numElement = 0;
    numSample = 0;
    scanline = 0;

    dataMatrix = NULL;
    next = NULL;

}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    //assigning input values to their corresponding variables
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;
    //creating datamatrix
    dataMatrix = createDataMatrix();
    //loading data and checking to see whether it opened files correctly
    if (loadRFData(dataMatrix, imagFile, realFile)== -1)
    {
        cerr << "There was an error in loading RFdata";
    }

} 
//deleting dataMatrixes 
dataBuffer::~dataBuffer()
{
    delete[] dataMatrix;
}
//used to create datamatrix with set parameters
complex **dataBuffer::createDataMatrix()
{
    dataMatrix = new complex* [numElement];
    
    for (int i = 0; i < numElement; i++)
    {
        dataMatrix[i] = new complex[numSample];
    }
    return dataMatrix;
 
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    //retrieving data for the imaginary part of the data from file
    char temp1[numSample];
    // You can use the getline() command to extract the data lines from the txt files
    for (int i = 0; i < numElement; i++)
    {
        for (int x = 0; x < numSample; x++)
        {
            //getting first character value of float array 
            if(imagFile->getline(temp1, 20)){
                //assinging character (converted to float) in file to first element to n array in RFdata
                RFData[i][x].imag = atof(temp1);
            }
            else 
            {
                return -1;
            }
        }
    }
    //retrieving real parts of the data from file
    char temp2[20];
    
    for (int i = 0; i < numElement; i++)
    {
        for (int x = 0; x < numSample; x++)
        {
            //getting first character value of float array 
            if(realFile->getline(temp2, 20)){
                //assinging character (converted to float) in file to first element to n array in RFdata
                RFData[i][x].real = atof(temp2);
            }
            //runs if if it was not able to getline from file correctly
            else 
            {
                return -1;
            }
        }
    }

    return 0;
}

float dataBuffer::getRealRFData(int element,int sample)
{
    //getting specific real sample in dataMatrix
    float r = dataMatrix[element][sample].real;
    return r; 

}
float dataBuffer::getImagRFData(int element,int sample)
{
    //same thing with getRealRFdata but with the imaginary part
    float i = dataMatrix[element][sample].imag;
    return i;
}

void dataBuffer::deleteDataMatrix()
{
    //deallocating memory for device efficiency
    for (int i = 0; i<numElement; i++)
    {
        delete dataMatrix[i];
    }
}




