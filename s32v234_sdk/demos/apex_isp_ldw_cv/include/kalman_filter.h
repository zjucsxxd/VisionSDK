/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
#ifndef _KALMANFILTER__H
#define _KALMANFILTER__H

#include <ICL_Kalman.hpp>

/**
 * Class encapsulates standard OpenCV Kalman filter to be used in 
 * Freescale LDW algorithm
 */
class KalmanFilter
{
  public:
    /**
     * Constructor - constructs uninitialised Kalman filter
     */
    KalmanFilter();
    
    /**
     * Init function - initializes Kalman filter to default values
     * @param cMeasurementNoiseVar Kalman filter parameter
     * @param cPostErrorVar Kalman filter parameter
     * @param cInitialValue Kalman filter parameter
     * @param cProcessNoiseVar Kalman filter parameter
     */
    void Initialize(double cMeasurementNoiseVar, 
		    double cPostErrorVar = 0.1f, 
		    double cInitialValue = 0.0f, 
		    double cProcessNoiseVar = 0.001f);
    
    /**
     * Reset funtion - initializes Kalman filter to default values
     * @param cMeasurementNoiseVar Kalman filter parameter
     * @param cPostErrorVar Kalman filter parameter
     * @param cInitialValue Kalman filter parameter
     * @param cProcessNoiseVar Kalman filter parameter
     */
    void Reset(double cMeasurementNoiseVar, 
	       double cPostErrorVar = 0.1f, 
	       double cInitialValue = 0.0f, 
	       double cProcessNoiseVar = 0.001f);

    /**
     * Updates the filter with data from new measurment
     * @param cMeasurement Current measured value
     */
    void NextMeasurement(const double cMeasurement);

    /**
     * Returns current value of Kalman filter
     * @return Curent predicted value
     */
    double GetValue();

  private:
    /**
     * Intermal OpenCV Kalman filter
     */
    ICP_KalmanFilter        mKalman;
    
    /**
     * Matrix specifying current measurement
     */
    ICP_Mat<float>          mMeasurementMat;
    
    /**
     * Initialized flag
     */
    bool    	                mIsInitialized;
	
	
   
   
};

#endif