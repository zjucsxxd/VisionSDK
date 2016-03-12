/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2011 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

 /*!*********************************************************************************
*  @file
*  @brief Implements a Kalman filter.
*
*  \section ldw_desc Description
*
*  This file contains the implementation of a Kalman filter
*
***********************************************************************************/

 
#ifndef _ICL_KALMAN_HPP___
#define _ICL_KALMAN_HPP___

/////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

#include "ICP_Types.hpp"

/////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// This function...
///
/// \param edg - [Output] reference of destination edge image

///
/// \return
/// \return ICP_R_OK - if edge detection process success.
/// \return ICP_R_UNKNOWN_ERR - if image descriptor is not valid.
/////////////////////////////////////////////////////////////////////////




class ICP_KalmanFilter
{
public:
   ICP_KalmanFilter();
   ICP_KalmanFilter(int const cDynamParams,
                    int const cMeasureParams,
                    int const cControlParams);

   ~ICP_KalmanFilter();

   LIB_RESULT Initialize(int const cDynamParams,
                         int const cMeasureParams,
                         int const cControlParams);

   LIB_RESULT Predict();
   LIB_RESULT Predict(const ICP_Mat<float>& rcControl);
   LIB_RESULT Correct(const ICP_Mat<float>& rcMeasurement);


public:
   ICP_Mat<float> mPredictedState;
   ICP_Mat<float> mCorrectedState;
   ICP_Mat<float> mStateTransitionMatrix;
   ICP_Mat<float> mExternalControlMatrix;
   ICP_Mat<float> mMeasurementMatrix;
   ICP_Mat<float> mProcessNoiseCovariance;
   ICP_Mat<float> mMeasurementNoiseCovariance;
   ICP_Mat<float> mPrioriErrorCovariance;      // Associated with predicted state
   ICP_Mat<float> mKalmanGain;
   ICP_Mat<float> mPosterioriErrorCovariance;  // Associated with corrected state


private:
   ICP_Mat<float> mTemp1;
   ICP_Mat<float> mTemp2;
   ICP_Mat<float> mTemp3;
   ICP_Mat<float> mTemp4;
   ICP_Mat<float> mTemp5;

};


#endif
