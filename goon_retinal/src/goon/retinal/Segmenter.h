#ifndef __GOON_RETINAL_SEGMENTER_H
#define __GOON_RETINAL_SEGMENTER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"
#include <log4cxx/logger.h>

#include "tuly/control/module3.h"
#include <goon/data/retina.h>
#include "goon/retinal/Floodfiller.h"

// This class implements an independent segmentation unit that works in its own thread.
// It is used for multi-threaded segmentation.
// It gets region seeds by randomly sampling the image.
// It uses a Floodfiller object to extract the regions from the seeds.
// Extracted regions (if relevant size) are then inserted in the retina.
// The sampling ends when a predefined number of samples (NUM_SAMPLES) is reached.
// Derives from Module (utility base class for thread management)
// Parameters:
// NUM_SAMPLES: the number of seeds used for an image segmentation
// MIN_SIZE: regions under this size are considered irrelevant
namespace goon
{
class Segmenter: public tuly::Module3
{
public:
    enum eState
    {
        eSEG_READY,        // thread on & job done
        eSEG_WORKING     // thread on & doing job
    };

private:
    static log4cxx::LoggerPtr logger;
    int ID;                     // segmenter ID
    bool binitialized;      // init has been called, allowed to go on
    // params
    int NUM_SAMPLES;    // number of seeds used to extract regions
    int MIN_SIZE;         // minimum area of relevant regions
    // shared data
    Retina* pRetina;                    // pointer to shared retina
    cv::Mat mask_segmented2;    // pointer to shared segmentation mask
    // logic
    std::vector<cv::Point> vec_seeds;       // list of possible seeds
    Floodfiller oFloodfiller;       // object for region extractions
    cv::Mat imageCam;           // image to process (RBG)
    cv::Mat imageHSV;           // image to process (HSV)
    bool bnewRequest;           // new process requested
    int numSeedsUsed;      // number of used seeds for a frame process
    int numFloodfills;          // number of floodfills done for a frame process (successful seeds)

public:

    Segmenter();
    ~Segmenter();

    void setID(int id) {ID = id;};
    // access to shared data (retina & segmentation mask)
    void init(Retina& oRetina, cv::Mat& mask_segmented);    
    // set configuration data
    void config (std::vector<cv::Point>& listSeeds, int numSamples, int minSize);

    // launch a new frame processing. If module not ready, reject request & return false
    bool newRequest(cv::Mat& image_cam, cv::Mat& image_hsv);

    // checks if module is in READY state
    bool isReady();
    bool isWorking();
    
    int getNumFloodfills() {return numFloodfills;};
    int getUsedSeeds() {return numSeedsUsed;};
    
private:                
    // first action after thread begins 
    virtual void first();
    // process done on each loop    
    virtual void loop();             
    // last action before thread ends
    virtual void bye();

    // checks if a new process request has been done
    bool isProcessingRequested();
    // where the image processing is done
    void extractRegions();
    // gets a random index of the seeds vector.
    int getRandomIndex();

};
		  	    		  
}  
  
#endif
