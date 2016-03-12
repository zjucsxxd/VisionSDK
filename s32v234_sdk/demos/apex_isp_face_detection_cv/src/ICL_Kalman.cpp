/******************************************************************************
 *  (C) Copyright CogniVue Corp. 2011 All right reserved.
 *    Confidential Information
 *
 *  All parts of the CogniVue Corp. Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from Cognivue.
 ******************************************************************************
 */

/* Information for doxygen */
/**
 *  \file   <<FileName>>
 *  \brief  <<One line Description>>
 *
 *  <<Replace this with Multiline description. This should describe the
 *  file in general.>>
 */

/***************************************************************************/
/* Include files. */
#include "ICL_Kalman.hpp"
#include "../../../libs/apu/common/include/global_errors.h"
#include <algorithm>
#include <stdint.h>

/***************************************************************************/
/* Local Literals & definitions */


/***************************************************************************/
/* Externally defined global data */


/***************************************************************************/
/* Locally defined global data */


/***************************************************************************/
/**
 * \par Description
 * The first sentence is the summary of the function. Starting from the
 * next sentence is your detailed description. Doxygen creates a summary
 * and a detailed description based on these.
 *
 * \param  param1  First parameter
 *
 * \return ::LIB_SUCCESS
 **************************************************************************/
ICP_KalmanFilter::ICP_KalmanFilter()
{
}



/***************************************************************************/
/**
 * \par Description
 * The first sentence is the summary of the function. Starting from the
 * next sentence is your detailed description. Doxygen creates a summary
 * and a detailed description based on these.
 *
 * \param  param1  First parameter
 *
 * \return ::LIB_SUCCESS
 **************************************************************************/
ICP_KalmanFilter::ICP_KalmanFilter(int const cDynamParams,
                                   int const cMeasureParams,
                                   int const cControlParams)
{
   /*LIB_RESULT libResult = */ICP_KalmanFilter::Initialize(cDynamParams,
                                                       cMeasureParams,
                                                       cControlParams);
}



/***************************************************************************/
/**
 * \par Description
 * The first sentence is the summary of the function. Starting from the
 * next sentence is your detailed description. Doxygen creates a summary
 * and a detailed description based on these.
 *
 * \param  param1  First parameter
 *
 * \return ::LIB_SUCCESS
 **************************************************************************/
ICP_KalmanFilter::~ICP_KalmanFilter()
{
}



/***************************************************************************/
/**
 * \par Description
 * The first sentence is the summary of the function. Starting from the
 * next sentence is your detailed description. Doxygen creates a summary
 * and a detailed description based on these.
 *
 * \param  param1  First parameter
 *
 * \return ::LIB_SUCCESS
 **************************************************************************/
LIB_RESULT ICP_KalmanFilter::Initialize(int const cDynamParams,
                                        int const cMeasureParams,
                                        int const cControlParams)
{
   LIB_RESULT libResult = LIB_FAILURE;

   if(cDynamParams   > 0 &&
      cMeasureParams > 0)
   {
      const int cAdjustedControlParams = std::max(cControlParams, 0);

      // Predicted State (DP, 1) Zeroes
      libResult = mPredictedState.Create(cDynamParams, 1);
      libResult = mPredictedState.Fill(0.0);

      // Corrected State (DP, 1) Zeroes
      libResult = mCorrectedState.Create(cDynamParams, 1);
      libResult = mCorrectedState.Fill(0.0);

      // State transition matrix (DP, DP) Eye
      libResult = mStateTransitionMatrix.Create(cDynamParams,
                                                cDynamParams);

      libResult = mStateTransitionMatrix.SetIdentity(1.0);

      // External control matrix (DP, CP) Zeroes
      if(cAdjustedControlParams > 0)
      {
         libResult = mExternalControlMatrix.Create(cDynamParams,
                                                   cAdjustedControlParams);

         libResult = mExternalControlMatrix.Fill(0.0);
      }

      // Measurement matrix (MP, DP) Zeroes
      libResult = mMeasurementMatrix.Create(cMeasureParams,
                                            cDynamParams);

      libResult = mMeasurementMatrix.Fill(0.0);

      // Process noise covariance (DP, DP) Eye
      libResult = mProcessNoiseCovariance.Create(cDynamParams,
                                                 cDynamParams);

      libResult = mProcessNoiseCovariance.SetIdentity(1.0);

      // Measurement noise covariance (MP, MP) Eye
      libResult = mMeasurementNoiseCovariance.Create(cMeasureParams,
                                                     cMeasureParams);

      libResult = mMeasurementNoiseCovariance.SetIdentity(1.0);

      // Priori error covariance (DP, DP) Zeroes
      libResult = mPrioriErrorCovariance.Create(cDynamParams,
                                                cDynamParams);

      libResult = mPrioriErrorCovariance.Fill(0.0);

      // Kalman gain (DP, MP) Zeroes
      libResult = mKalmanGain.Create(cDynamParams,
                                     cMeasureParams);

      libResult = mKalmanGain.Fill(0.0);

      // Posteriori error covariance (DP, DP) Zeroes
      libResult = mPosterioriErrorCovariance.Create(cDynamParams,
                                                    cDynamParams);

      libResult = mPosterioriErrorCovariance.Fill(0.0);

      // Temp 1-5
      const uint32_t cMaxSize = std::max(cDynamParams,
                                         cDynamParams);

      libResult = mTemp1.Create(cMaxSize,
                                cMaxSize);

      libResult = mTemp2.Create(cMaxSize,
                                cMaxSize);

      libResult = mTemp3.Create(cMaxSize,
                                cMaxSize);

      libResult = mTemp4.Create(cMaxSize,
                                cMaxSize);

      libResult = mTemp5.Create(cMaxSize,
                                cMaxSize);
   }

   return libResult;
}



/***************************************************************************/
/**
 * \par Description
 * The first sentence is the summary of the function. Starting from the
 * next sentence is your detailed description. Doxygen creates a summary
 * and a detailed description based on these.
 *
 * \param  param1  First parameter
 *
 * \return ::LIB_SUCCESS
 **************************************************************************/
LIB_RESULT ICP_KalmanFilter::Predict()
{
   LIB_RESULT libResult = LIB_FAILURE;

   libResult = mStateTransitionMatrix.Multiply(mCorrectedState,
                                               mPredictedState);  // update the state: x'(k) = A*x(k)

   if(libResult == LIB_SUCCESS)
   {
      libResult = mStateTransitionMatrix.Multiply(mPosterioriErrorCovariance,
                                                  mTemp1);  // update error covariance matrices: temp1 = A*P(k)
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mStateTransitionMatrix.Transpose(mTemp2);  // At
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mTemp1.Multiply(mTemp2,
                                  mTemp3);   // temp1*At
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mTemp3.Add(mProcessNoiseCovariance,
                             mPrioriErrorCovariance); // P'(k) = temp1*At + Q
   }

   return libResult;
}



/***************************************************************************/
/**
 * \par Description
 * The first sentence is the summary of the function. Starting from the
 * next sentence is your detailed description. Doxygen creates a summary
 * and a detailed description based on these.
 *
 * \param  param1  First parameter
 *
 * \return ::LIB_SUCCESS
 **************************************************************************/
LIB_RESULT ICP_KalmanFilter::Correct(const ICP_Mat<float>& rcMeasurement)
{
   LIB_RESULT libResult = LIB_FAILURE;

   libResult = mMeasurementMatrix.Multiply(mPrioriErrorCovariance,
                                           mTemp2);   // temp2 = measurementMatrix * errorCovPre;

   if(libResult == LIB_SUCCESS)
   {
      libResult = mMeasurementMatrix.Transpose(mTemp1);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mTemp2.Multiply(mTemp1,
                                  mTemp3);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mTemp3.Add(mMeasurementNoiseCovariance,
                             mTemp3);  // gemm(temp2, measurementMatrix, 1, measurementNoiseCov, 1, temp3, GEMM_2_T);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mTemp3.PseudoInverse(mTemp1);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mTemp1.Multiply(mTemp2,
                                  mTemp4); // solve(temp3, temp2, temp4, DECOMP_SVD);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mTemp4.Transpose(mKalmanGain);   // gain = temp4.t();
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mMeasurementMatrix.Multiply(mPredictedState,
                                              mTemp1);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = rcMeasurement.Subtract(mTemp1,
                                         mTemp5); // temp5 = measurement - measurementMatrix*statePre;
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mKalmanGain.Multiply(mTemp5,
                                       mTemp1);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mPredictedState.Add(mTemp1,
                                      mCorrectedState);  // statePost = statePre + gain*temp5;
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mKalmanGain.Multiply(mTemp2,
                                       mTemp1);
   }

   if(libResult == LIB_SUCCESS)
   {
      libResult = mPrioriErrorCovariance.Subtract(mTemp1,
                                                  mPosterioriErrorCovariance);  // errorCovPost = errorCovPre - gain*temp2;
   }

   return libResult;
}

