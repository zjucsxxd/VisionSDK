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
#include "kalman_filter.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor - constructs uninitialised Kalman filter
////////////////////////////////////////////////////////////////////////////////
KalmanFilter::KalmanFilter()
: mIsInitialized(false)
{
}

////////////////////////////////////////////////////////////////////////////////
// Init function - initializes Kalman filter to default values
// @param cMeasurementNoiseVar Kalman filter parameter
// @param cPostErrorVar Kalman filter parameter
// @param cInitialValue Kalman filter parameter
// @param cProcessNoiseVar Kalman filter parameter
////////////////////////////////////////////////////////////////////////////////
void KalmanFilter::Initialize(double cMeasurementNoiseVar, 
			      double cPostErrorVar, 
			      double cInitialValue, 
			      double cProcessNoiseVar)
{
   if(mIsInitialized == false)
   {
      mKalman.Initialize(1,1,0); 

      // mKalman Filter Parameters
      mKalman.mStateTransitionMatrix.SetIdentity(1); 
      mKalman.mMeasurementMatrix.SetIdentity(1); 
      mKalman.mProcessNoiseCovariance.SetIdentity(cProcessNoiseVar); 
      mKalman.mMeasurementNoiseCovariance.SetIdentity(cMeasurementNoiseVar); 

      // Initial Conditions
      mKalman.mCorrectedState.SetIdentity(cInitialValue); 
      mKalman.mPosterioriErrorCovariance.SetIdentity(cPostErrorVar); 

      // Generate the first prediction state
      mKalman.Predict(); 

      // Allocate measurement matrix
      mMeasurementMat.Create(1,1); 

      mIsInitialized = true;
   }
}

////////////////////////////////////////////////////////////////////////////////
// Reset function - initializes Kalman filter to default values
// @param cMeasurementNoiseVar Kalman filter parameter
// @param cPostErrorVar Kalman filter parameter
// @param cInitialValue Kalman filter parameter
// @param cProcessNoiseVar Kalman filter parameter
////////////////////////////////////////////////////////////////////////////////
void KalmanFilter::Reset(double cMeasurementNoiseVar, 
			 double cPostErrorVar, 
			 double cInitialValue, 
			 double cProcessNoiseVar)
{
   if(mIsInitialized == true)
   {
      mKalman.Initialize(1,1,0); 

      // mKalman Filter Parameters
      mKalman.mStateTransitionMatrix.SetIdentity(1);
      mKalman.mMeasurementMatrix.SetIdentity(1); 
      mKalman.mProcessNoiseCovariance.SetIdentity(cProcessNoiseVar); 
      mKalman.mMeasurementNoiseCovariance.SetIdentity(cMeasurementNoiseVar); 

      // Initial Conditions
      mKalman.mCorrectedState.SetIdentity(cInitialValue);
      mKalman.mPosterioriErrorCovariance.SetIdentity(cPostErrorVar); 

      // Generate the first prediction state
      mKalman.Predict(); 
   }
}

////////////////////////////////////////////////////////////////////////////////
// Updates the filter with data from new measurment
// @param cMeasurement Current measured value
////////////////////////////////////////////////////////////////////////////////
void KalmanFilter::NextMeasurement(double cMeasurement)
{
  if(mIsInitialized == true)
   {
      mMeasurementMat(0,0) = cMeasurement;

      mKalman.Correct(mMeasurementMat);

      mKalman.Predict();
   }
}

////////////////////////////////////////////////////////////////////////////////
// Returns current value of Kalman filter
// @return Curent predicted value
////////////////////////////////////////////////////////////////////////////////
double KalmanFilter::GetValue()
{
  return mKalman.mCorrectedState(0,0);
}


