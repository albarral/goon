/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include <algorithm>
#include <unistd.h>
#include "log4cxx/ndc.h"

#include "goon/retinal/Segmenter.h"
#include <goon/data/base/region.h>
#include <goon/features/color/rgb_color.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr Segmenter::logger(Logger::getLogger("goon.retinal"));
				 				 				 					
// constructor
Segmenter::Segmenter ()
{
    // default state is OFF (Module class constructor)
    ID = 0;
    binitialized = false;
    
    NUM_SAMPLES = 0;
    MIN_SIZE = 0;
    pRetina = 0;
    bnewRequest = false;
    beat = 0;
}

// destructor
Segmenter::~Segmenter()
{
}

void Segmenter::init(Retina& oRetina, cv::Mat& mask_segmented)
{            
    LOG4CXX_INFO(logger, "init Segmenter " << ID);
    pRetina = &oRetina;    
    mask_segmented2 = mask_segmented; // shallow copy, as all segmenters need access to shared mask segmented
    oFloodfiller.init(mask_segmented);
    binitialized = true;
}

void Segmenter::config(std::vector<cv::Point>& listSeeds, int numSamples, int minSize)
{
    vec_seeds = listSeeds;
    NUM_SAMPLES = numSamples;
    MIN_SIZE = minSize;    
}

void Segmenter::first()
{    
    log4cxx::NDC::push("Segmenter " + std::to_string(ID));   	
    
    // start in READY state
    if (binitialized)
    {
        setState(Segmenter::eSEG_READY);
        beat = 0;
        LOG4CXX_INFO(logger, "started");  
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "not initialized. Going off ... ");  
        Module3::off();        
    }
}

void Segmenter::loop()
{   
    // if new processing requested
    if (isProcessingRequested())
    {
        LOG4CXX_TRACE(logger, "processing");  
        // set state WORKING
        setState(Segmenter::eSEG_WORKING);
        // do the job
        extractRegions();
        // set state READY
        setState(Segmenter::eSEG_READY);

        newBeat();
    }
}

void Segmenter::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

bool Segmenter::newRequest(cv::Mat& image_cam, cv::Mat& image_hsv)
{
    // accept request if module is READY
    if (isReady())
    {
        LOG4CXX_TRACE(logger, "new request");  
        bnewRequest = true;
        imageCam = image_cam;
        imageHSV = image_hsv;
        return true;
    }
    // otherwise, reject it
    else
    {
        LOG4CXX_WARN(logger, "new request ignored, segmenter not in READY state");  
        return false;
    }
}

bool Segmenter::isProcessingRequested()
{
    // checks for pending request, resetting it if yes
    if (bnewRequest)
    {
        bnewRequest = false;
        return true; 
    }
    else
        return false;
}

bool Segmenter::isReady()
{
    return (getState() == Segmenter::eSEG_READY);    
}

bool Segmenter::isWorking()
{
    return (getState() == Segmenter::eSEG_WORKING);        
}

// This function performs floodfills from random seeds to segment homogeneous color regions from the image.
void Segmenter::extractRegions ()
{
    Region oRegion;
    int region_size;

    // reset counters
    int samples = 0;
    int numFloodfills = 0;
    int numRegions = 0;

    // start getting seeds from a random position in the vector
    std::vector<cv::Point>::iterator it_seed = vec_seeds.begin();
    std::advance(it_seed, getRandomIndex());
    
    while (samples < NUM_SAMPLES)
    {                 
        samples++;        
        // if seed not segmented, expand from it a new region 		
        if (mask_segmented2.at<uchar>(it_seed->y, it_seed->x) == 0)
        {		
            numFloodfills++;
            oFloodfiller.floodFill(*it_seed, imageCam, imageHSV);    
            
            region_size = oFloodfiller.getRegionArea();
         
            // if the region is big enough, accept it 
            if (region_size > MIN_SIZE)
            {
                numRegions++;
                // build the region (type, mass, mask, window, grid, color and position)
                oRegion.setType(Region::eREG_SIMPLE); 
                oRegion.setMass(region_size);
                oRegion.setMaskAndWindow(oFloodfiller.getRegionMask(), oFloodfiller.getRegionWindow());
                oRegion.setMassGrid(oFloodfiller.getMassGrid());
                oRegion.setRGBGrid(oFloodfiller.getColorGrid());
                oRegion.setGridWindow(oFloodfiller.getGridWindow());
                oRegion.setRGB(oRegion.computeMeanColor());	
                oRegion.setHSV(RGBColor::toHSV(oRegion.getRGB()));
                oRegion.setSeed(*it_seed);

                // and add it to the retina (ID assigned there)
                pRetina->addRegion(oRegion);

                LOG4CXX_TRACE(logger, "-> region " << oRegion.getID());
//                if (bdebug)                            
//                    showProgress();
            }
            else
                LOG4CXX_TRACE(logger, "-> region ignored");
        }      

        // get next seed (if end of vector reached, follow at the beginning)
        it_seed++;
        if (it_seed == vec_seeds.end())
            it_seed = vec_seeds.begin();            
    } // end while    
    
    LOG4CXX_TRACE(logger, "extracted regions = " << numRegions << ", num floodfills = " << numFloodfills << ", samples = " << samples);
}
  

int Segmenter::getRandomIndex()
{
    return (vec_seeds.size() * (float) std::rand() / RAND_MAX);
}
		

int Segmenter::getBeat() 
{
    std::lock_guard<std::mutex> locker(mutex2);
    return beat;
}

void Segmenter::newBeat()
{
    std::lock_guard<std::mutex> locker(mutex2);
    // produce new beat
    beat++;
    if (beat == 1000)
        beat = 0;
}

//void Segmenter::showProgress()
//{
//    // compute present mask, window and color
//    oExploration.computeWindow();       
//    cv::Mat mask_progress = oExploration.getRegionMask()(oExploration.getWindow());
//    oColorGrid.computeMeanColor(oExploration.getWindow());                                                                            
//    
//    // draw it in a debug image
//    oDebug.storeInfo(oExploration.getWindow(), oColorGrid.getColorMean(), mask_progress);  
//    oDebug.drawInfo();
//}

}
