/**
  ******************************************************************************
  * @file    stm32wl3x_hal_mrsubg.c
  * @author  GPM Application Team
  * @brief   This file provides firmware functions to manage the MRSubG
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal.h"
#include <string.h>

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @addtogroup MRSUBG
  * @{
  */

#ifdef HAL_MRSUBG_MODULE_ENABLED

/** @defgroup MRSUBG_Private_Constants MRSUBG Private Constants
  * @{
  */
#define MAX_DBM       0x51

/**
  * @}
  */


/** @defgroup MRSUBG_Private_Macros MRSUBG Private Macros
  * @{
  */


#define S_ABS(a) ((a)>0?(a):-(a))

#define IS_FREQUENCY_BAND(FREQUENCY) (IS_FREQUENCY_BAND_HIGH(FREQUENCY) || \
                                      IS_FREQUENCY_BAND_LOW(FREQUENCY))

#define IS_FREQUENCY_BAND_HIGH(FREQUENCY) ((FREQUENCY)>=HIGH_BAND_LOWER_LIMIT && \
                                           (FREQUENCY)<=HIGH_BAND_UPPER_LIMIT)


#define IS_FREQUENCY_BAND_LOW(FREQUENCY) ((FREQUENCY)>=LOW_BAND_LOWER_LIMIT && \
                                             (FREQUENCY)<=LOW_BAND_UPPER_LIMIT)

#define IS_MODULATION(MOD) (((MOD) == MOD_2FSK) || \
					((MOD) == MOD_4FSK) || \
					((MOD) == MOD_2GFSK05) || \
					((MOD) == MOD_2GFSK1)  || \
					((MOD) == MOD_4GFSK05) || \
					((MOD) == MOD_4GFSK1) || \
					((MOD) == MOD_ASK) || \
					((MOD) == MOD_OOK) || \
					((MOD) == MOD_POLAR) || \
					((MOD) == MOD_CW) )


#define IS_DATARATE(DATARATE)      (DATARATE>=MINIMUM_DATARATE && DATARATE<=((uint64_t)MAXIMUM_DATARATE))
/**
  * @}
  */

/** @defgroup MRSUBG_Private_Variables MRSUBG Private Variables
  * @{
  */

static const uint32_t s_Channel_Filter_Bandwidth[99]=
{
  1600000,1510000,1422000,1332000,1244000,1154000,1066000, \
  976000,888000,800000,755000,711000,666000,622000,577000, \
  533000,488000,444000,400000,377000,355000,333000,311000, \
  288000,266000,244000,222000,200000,188000,178000,166000, \
  155000,144000,133000,122000,111000,100000,94400,88900,83300, \
  77800,72200,66700,61100,55600,50000,47200,44400,41600,38900, \
  36100,33300,30500,27800,25000,23600,22200,20800,19400,18100, \
  16600,15300,13900,12500,11800,11100,10400,9700,9000,8300,7600, \
  6900,6125,5910,5550,5200,4870,4500,4100,3800,3500,3125,2940, \
  2780,2600,2400,2200,2100,1900,1700
};

const uint32_t SFD_2FSK[] = {
  0x904E0000, /* "1001000001001110" */
  0x6F4E0000  /* "0110111101001110" */
};

const uint32_t SFD_4FSK[] = {
  0xD75575FD,  /* "11010111010101010111010111111101" */
  0x7DFF75FD   /* "01111101111111110111010111111101" */
};

static WMbusSubmode s_cWMbusSubmode = WMBUS_SUBMODE_NOT_CONFIGURED;

/**
  * @}
  */

/** @defgroup MRSUBG_Private_Functions MRSUBG Private Functions
  * @{
  */

static uint32_t MRSubG_ComputeDatarate(uint16_t cM, uint8_t cE);
static void MRSubG_SearchDatarateME(uint32_t lDatarate, uint16_t* pcM, uint8_t* pcE);
static void MRSubG_SearchFreqDevME(uint32_t lFDev, uint8_t* pcM, uint8_t* pcE, uint8_t bs);
static uint32_t MRSubG_ComputeFreqDeviation(uint8_t cM, uint8_t cE, uint8_t bs);
static void MRSubG_SearchChannelBwME(uint32_t lBandwidth, uint8_t* pcM, uint8_t* pcE);
static void MRSubG_ComputeSynthWord(uint32_t frequency, uint8_t* synth_int, uint32_t* synth_frac, uint8_t* band);
static int32_t MRSubG_ConvertRssiToDbm(uint16_t rssi_level_from_register);
static uint8_t MRSubG_GetAllowedMaxOutputPower(MRSubG_PA_DRVMode paMode);
static void MRSUBG_EvaluateDSSS(MRSubGModSelect xModulation, uint8_t dsssExponent);

/**
* @brief  Computes the synth word from a given frequency.
* @param  frequency Target frequency value expressed in Hz.
* @param  synth_int pointer to the int part of the synth word
* @param  synth_frac pointer to the fract part of the synth word
* @param  band pointer to the high/low band selector
* @retval None.
*/
static void MRSubG_ComputeSynthWord(uint32_t frequency, uint8_t* synth_int, uint32_t* synth_frac, uint8_t* band)
{
  if(IS_FREQUENCY_BAND_HIGH(frequency)) {
    *band = HIGH_BAND_FACTOR;
  }
  else {
    *band = LOW_BAND_FACTOR;
  }

  *synth_int = (uint32_t)(*band * frequency/LL_GetXTALFreq());

  *synth_frac = (uint32_t)(((*band * (uint64_t)frequency * (1<<20))/LL_GetXTALFreq()) - (*synth_int * (1<<20)));
}

/**
* @brief  Evaluate the data rate.
* @param  cM the mantissa value.
* @param  cE the exponent value.
* @retval The datarate.
*/
static uint32_t MRSubG_ComputeDatarate(uint16_t cM, uint8_t cE)
{
  uint32_t f_sys=LL_GetXTALFreq()/3; /* 16 MHz nominal */
  uint64_t dr;

  if(cE==0){
    dr = ((uint64_t)f_sys*cM);
    return (uint32_t)(dr>>32);
  }
  else if(cE==15){
	return ((uint64_t)f_sys*(8*cM));
  }
  else{
    dr = ((uint64_t)f_sys)*((uint64_t)cM+65536);
    return (uint32_t)(dr>>(33-cE));
  }
}

/**
* @brief  Returns the mantissa and exponent, whose value used in the datarate formula
*         will give the datarate value closer to the given datarate.
* @param  lDatarate datarate expressed in sps.
* @param  pcM pointer to the returned mantissa value.
* @param  pcE pointer to the returned exponent value.
* @retval None.
*/
static void MRSubG_SearchDatarateME(uint32_t lDatarate, uint16_t* pcM, uint8_t* pcE)
{
  uint32_t lDatarateTmp, f_sys=LL_GetXTALFreq()/3;
  uint8_t uDrE;
  uint64_t tgt1,tgt2,tgt;

  /* Search the exponent value */
  for(uDrE = 0; uDrE<16; uDrE++) {
    lDatarateTmp = MRSubG_ComputeDatarate(0xFFFF, uDrE);
    if(lDatarate<=lDatarateTmp)
      break;
  }
  (*pcE) = (uint8_t)uDrE;

  if(uDrE==0) {
    tgt=((uint64_t)lDatarate)<<32;
    (*pcM) = (uint16_t)(tgt/f_sys);
    tgt1=(uint64_t)f_sys*(*pcM);
    tgt2=(uint64_t)f_sys*((*pcM)+1);
  }
  else {
    tgt=((uint64_t)lDatarate)<<(33-uDrE);
    (*pcM) = (uint16_t)((tgt/f_sys)-65536);
    tgt1=(uint64_t)f_sys*((*pcM)+65536);
    tgt2=(uint64_t)f_sys*((*pcM)+1+65536);
  }

  (*pcM)=((tgt2-tgt)<(tgt-tgt1))?((*pcM)+1):(*pcM);
}

/**
* @brief  Returns the mantissa and exponent, whose value used in the Frequency Deviation formula
*         will give the value closer to the given one.
* @param  cM the mantissa value.
* @param  cE the exponent value.
* @param  bs the band value.
* @retval The frequency deviation.
*/
static uint32_t MRSubG_ComputeFreqDeviation(uint8_t cM, uint8_t cE, uint8_t bs){
  uint32_t f_xo = LL_GetXTALFreq();

  if(cE==0) {
    return (uint32_t)((uint64_t)f_xo*(cM*bs/8)/(bs*(1<<19)));
  }

  return (uint32_t)((uint64_t)f_xo*((256+cM)*(1<<(cE-1))*bs/8)/(bs*(1<<19)));;
}

/**
* @brief  Returns the mantissa and exponent, whose value used in the Frequency Deviation formula
*         will give the value closer to the given one.
* @param  lFDev frequency deviation expressed in Hz.
* @param  pcM pointer to the returned mantissa value.
* @param  pcE pointer to the returned exponent value.
* @param  bs the high/low band selector
* @retval None.
*/
static void MRSubG_SearchFreqDevME(uint32_t lFDev, uint8_t* pcM, uint8_t* pcE, uint8_t bs){
  uint8_t uFDevE;
  uint32_t lFDevTmp;
  uint64_t tgt1,tgt2,tgt;

  /* Search the exponent of the frequency deviation value */
  for(uFDevE = 0; uFDevE != 12; uFDevE++) {
    lFDevTmp = MRSubG_ComputeFreqDeviation(255, uFDevE, bs);
    if(lFDev<lFDevTmp)
      break;
  }
  (*pcE) = (uint8_t)uFDevE;

  if(uFDevE==0)
  {
    tgt=((uint64_t)lFDev)<<22;
    (*pcM)=(uint32_t)(tgt/LL_GetXTALFreq());
    tgt1=(uint64_t)LL_GetXTALFreq()*(*pcM);
    tgt2=(uint64_t)LL_GetXTALFreq()*((*pcM)+1);
  }
  else
  {
    tgt=((uint64_t)lFDev)<<(23-uFDevE);
    (*pcM)=(uint32_t)(tgt/LL_GetXTALFreq())-256;
    tgt1=(uint64_t)LL_GetXTALFreq()*((*pcM)+256);
    tgt2=(uint64_t)LL_GetXTALFreq()*((*pcM)+1+256);
  }

  (*pcM)=((tgt2-tgt)<(tgt-tgt1))?((*pcM)+1):(*pcM);
}

/**
* @brief  Returns the mantissa and exponent for a given bandwidth.
*         The API will search the closer value according to a fixed table of channel
*         bandwidth values (@ref s_Channel_Filter_Bandwidth) returning the corresponding mantissa
*         and exponent value.
* @param  lBandwidth bandwidth expressed in Hz. This parameter ranging between 1700 and 1600000.
* @param  pcM pointer to the returned mantissa value.
* @param  pcE pointer to the returned exponent value.
* @retval None.
*/
static void MRSubG_SearchChannelBwME(uint32_t lBandwidth, uint8_t* pcM, uint8_t* pcE)
{
  int8_t i, i_tmp;
  uint32_t f_dig=LL_GetXTALFreq()/3;
  int32_t chfltCalculation[3];

  /* Search the channel filter bandwidth table index */
  for(i=0;i<99 && (lBandwidth<(uint32_t)(((uint64_t)s_Channel_Filter_Bandwidth[i]*f_dig)/16000000));i++);

  if(i!=0) {
    /* Finds the index value with best approximation in i-1, i and i+1 elements */
    i_tmp = i;

    for(uint8_t j=0;j<3;j++) {
      if(((i_tmp+j-1)>=0) && ((i_tmp+j-1)<=98)) {
        chfltCalculation[j] = (int32_t)lBandwidth - (int32_t)(((uint64_t)s_Channel_Filter_Bandwidth[i_tmp+j-1]*f_dig)/16000000);
      }
      else {
        chfltCalculation[j] = 0x7FFFFFFF;
      }
    }
    uint32_t chfltDelta = 0xFFFFFFFF;

    for(uint8_t j=0;j<3;j++) {
      if(S_ABS(chfltCalculation[j])<chfltDelta) {
        chfltDelta = S_ABS(chfltCalculation[j]);
        i=i_tmp+j-1;
      }
    }
  }
  (*pcE) = (uint8_t)(i/9);
  (*pcM) = (uint8_t)(i%9);
}

/*
 * @brief Convert RSSI_LEVEL_ON_SYNC to dBm
 * @param rssi_level_from_register the value to convert
 * @retval The converted RSSI level in dBm
*/
static int32_t MRSubG_ConvertRssiToDbm(uint16_t rssi_level_from_register){
  return (rssi_level_from_register/2)-(96+GAIN_RX_CHAIN);
}

/**
* @brief  Returns the maximum allowed output power supported by the specific configuration
* @param  paDrvMode the configuration type.
* @retval The maximum output power.
*/
static uint8_t MRSubG_GetAllowedMaxOutputPower(MRSubG_PA_DRVMode paDrvMode){
  uint8_t retPwr = 20;

  switch(paDrvMode){
  case PA_DRV_TX:
    retPwr = 10;
    break;
  case PA_DRV_TX_HP:
    retPwr = 16;
    break;
  case PA_DRV_TX_TX_HP:
    retPwr = 18; /* Max allowed power without PA_DEGEN_ON */
    break;
  }

  return retPwr;
}

/**
* @brief  Set the proper DSSS configuration
* @param  xModulation the modulation type.
* @param  dsssExponent the DSSS exponent.
* @retval None.
*/
static void MRSUBG_EvaluateDSSS(MRSubGModSelect xModulation, uint8_t dsssExponent){
  /* Disable DSSS for modulations different from 2(G)FSK */
  if (xModulation != MOD_2GFSK05 && xModulation != MOD_2GFSK1){
    dsssExponent = 0;
  }

  uint8_t dsss_en = (dsssExponent > 0);
  uint8_t dsss_sf = (1 << dsssExponent); /* Spread Factor = 2^dssExponent */
  uint8_t dsss_acq_thr = (dsss_sf - 1);

  if (dsssExponent > 3) {
    dsss_acq_thr = dsss_sf/2;
  }

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DSSS_CTRL,  MR_SUBG_GLOB_STATIC_DSSS_CTRL_DSSS_EN, dsss_en);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DSSS_CTRL,  MR_SUBG_GLOB_STATIC_DSSS_CTRL_SPREADING_EXP, dsssExponent);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DSSS_CTRL,  MR_SUBG_GLOB_STATIC_DSSS_CTRL_ACQ_THR, dsss_acq_thr);
}

/**
  * @}
  */


/** @defgroup MRSUBG_Exported_Functions MRSUBG Exported Functions
  * @{
  */

/**
* @brief  Get the IP version of the MRSubG.
* @retval IP version.
*/
SMRSubGVersion HAL_MRSubGGetVersion(void)
{
  SMRSubGVersion MRSubGVersion;

  MRSubGVersion.product =  READ_REG_FIELD(MR_SUBG_GLOB_MISC->RFIP_VERSION, MR_SUBG_GLOB_MISC_RFIP_VERSION_PRODUCT);
  MRSubGVersion.version =  READ_REG_FIELD(MR_SUBG_GLOB_MISC->RFIP_VERSION, MR_SUBG_GLOB_MISC_RFIP_VERSION_VERSION);
  MRSubGVersion.revision = READ_REG_FIELD(MR_SUBG_GLOB_MISC->RFIP_VERSION, MR_SUBG_GLOB_MISC_RFIP_VERSION_REVISION);

  return MRSubGVersion;
}

/**
* @brief  Initializes the MR_SUBG radio interface according to the specified
*         parameters in the pxSRadioInitStruct.
* @param  pxSRadioInitStruct pointer to a SMRSubGConfig structure that
*         contains the configuration information for the MR_SUBG radio part of STM32WL3.
* @retval Error code: 0=no error, 1=error during calibration of VCO.
*/
uint8_t HAL_MRSubG_Init(SMRSubGConfig* pxSRadioInitStruct){

  assert_param(IS_FREQUENCY_BAND(pxSRadioInitStruct->lFrequencyBase));
  assert_param(IS_MODULATION(pxSRadioInitStruct->xModulationSelect));
  assert_param(IS_DATARATE(pxSRadioInitStruct->lDatarate));

  HAL_MRSubG_MspInit();

  /* Setup design values for default registers */
  MODIFY_REG_FIELD(MR_SUBG_RADIO->AFC1_CONFIG, MR_SUBG_RADIO_AFC1_CONFIG_AFC_FAST_PERIOD, 0x00);

  MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL0, MR_SUBG_RADIO_CLKREC_CTRL0_PSTFLT_LEN, 0x01);
  MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL0, MR_SUBG_RADIO_CLKREC_CTRL0_CLKREC_P_GAIN_FAST, 0x03);
  MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL0, MR_SUBG_RADIO_CLKREC_CTRL0_CLKREC_I_GAIN_FAST, 0x08);

  MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL1, MR_SUBG_RADIO_CLKREC_CTRL1_CLKREC_ALGO_SEL, 0x00);
  MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL1, MR_SUBG_RADIO_CLKREC_CTRL1_CLKREC_P_GAIN_SLOW, 0x05);
  MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL1, MR_SUBG_RADIO_CLKREC_CTRL1_CLKREC_I_GAIN_SLOW, 0x0C);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DSSS_CTRL, MR_SUBG_GLOB_STATIC_DSSS_CTRL_ACQ_HITS, 0x03);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DSSS_CTRL, MR_SUBG_GLOB_STATIC_DSSS_CTRL_ACQ_WINDOW, 0x04);

  /* Enable calibration */
  SET_BIT(MR_SUBG_GLOB_DYNAMIC->VCO_CAL_CONFIG, MR_SUBG_GLOB_DYNAMIC_VCO_CAL_CONFIG_VCO_CALIB_REQ);

  /* Avoid AGC glitches */
  WRITE_REG(MR_SUBG_RADIO->RF_FSM7_TIMEOUT, 0x0F);

  /* Set synth registers */
  HAL_MRSubG_SetFrequencyBase(pxSRadioInitStruct->lFrequencyBase);

  /* Configure modulation */
  HAL_MRSubG_SetModulation(pxSRadioInitStruct->xModulationSelect, pxSRadioInitStruct->dsssExp);

  /* Configure datarate */
  HAL_MRSubG_SetDatarate(pxSRadioInitStruct->lDatarate);

  /* Configure frequency deviation */
  HAL_MRSubG_SetFrequencyDev(pxSRadioInitStruct->lFreqDev);

  /* Configure RX channel bandwidth */
  HAL_MRSubG_SetChannelBW(pxSRadioInitStruct->lBandwidth);

  /* Configure Output Power */
  HAL_MRSubG_SetPALeveldBm(7, pxSRadioInitStruct->outputPower, pxSRadioInitStruct->PADrvMode);

  return 0;
}

/**
 * @brief  Get the main radio info for the current configuration.
 * @param  pxSRadioInitStruct pointer to a structure of the type of @ref SMRSubGConfig
 * @retval None.
 */
void HAL_MRSubG_GetInfo(SMRSubGConfig* pxSRadioInitStruct){
  pxSRadioInitStruct->lFrequencyBase = HAL_MRSubG_GetFrequencyBase();
  pxSRadioInitStruct->xModulationSelect = HAL_MRSubG_GetModulation();
  pxSRadioInitStruct->lDatarate = HAL_MRSubG_GetDatarate();
  pxSRadioInitStruct->lFreqDev = HAL_MRSubG_GetFrequencyDev();
  pxSRadioInitStruct->lBandwidth = HAL_MRSubG_GetChannelBW();
  pxSRadioInitStruct->outputPower = HAL_MRSubG_GetPALeveldBm();
  pxSRadioInitStruct->PADrvMode = LL_MRSubG_GetPADriveMode();
}

/**
* @brief  Set the Synth word and the Band Select register according to desired base carrier frequency.
* @param  lFBase the base carrier frequency expressed in Hz as unsigned word.
* @retval None.
*/
void HAL_MRSubG_SetFrequencyBase(uint32_t lFBase){
  uint8_t band;
  uint8_t synth_int;
  uint32_t synth_frac;
  uint32_t b_factor;

  assert_param(IS_FREQUENCY_BAND(lFBase));

  MRSubG_ComputeSynthWord(lFBase, &synth_int, &synth_frac, &band);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_SYNTH_INT, synth_int);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_SYNTH_FRAC, synth_frac);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->ADDITIONAL_CTRL, MR_SUBG_GLOB_DYNAMIC_ADDITIONAL_CTRL_CH_NUM, 0x00);

#if defined(IS_169MHZ)
  b_factor = (20-band)/12;
#else
  b_factor = (band/4)-1;
#endif

  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_BS, b_factor);
}

/**
* @brief  Return the base carrier frequency.
* @retval uint32_t Base carrier frequency expressed in Hz as unsigned word.
*/
uint32_t HAL_MRSubG_GetFrequencyBase(void)
{
#if defined(IS_169MHZ)
  uint8_t  bs = (READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_BS));
  bs = bs?8:20;
#else
  uint8_t  bs = ((READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_BS)+1)*4);
#endif
  uint8_t  synth_int = READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_SYNTH_INT);
  uint32_t synth_frac = READ_REG(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ) & MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_SYNTH_FRAC;
  uint32_t fbase;

  fbase = LL_GetXTALFreq()*((uint64_t)(synth_int*(1<<20) + synth_frac))/(bs*(1<<20));

  return fbase;
}

/**
* @brief  Set the datarate.
* @param  lDatarate datarate expressed in sps.
* @retval None.
*/
void HAL_MRSubG_SetDatarate(uint32_t lDatarate){
  uint8_t dr_e;
  uint16_t dr_m;

  assert_param(IS_DATARATE(lDatarate));

  /* Calculates the datarate mantissa and exponent */
  MRSubG_SearchDatarateME(lDatarate, &dr_m, &dr_e);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_DATARATE_M, dr_m);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_DATARATE_E, dr_e);
}

/**
* @brief  Return the datarate.
* @retval uint32_t Datarate expressed in sps.
*/
uint32_t HAL_MRSubG_GetDatarate(void)
{
  uint32_t dr, datarateM, datarateE;
  uint32_t f_sys;

  datarateM = READ_REG(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG) & MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_DATARATE_M;
  datarateE = READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_DATARATE_E);

  f_sys = (uint32_t)(LL_GetXTALFreq()/3);

  if (datarateE == 0)
	dr = f_sys*datarateM/(uint64_t)1<<32;
  else if (datarateE == 15) /* Jitter free mode */
    dr = f_sys/(8*datarateM);
  else
    dr = f_sys*((uint64_t)(1<<16) + datarateM)*(1<<datarateE)/((uint64_t)1<<33);

  return dr;
}

/**
* @brief  Set the frequency deviation.
* @param  lFDev frequency deviation expressed in Hz.
* @retval None.
*/
void HAL_MRSubG_SetFrequencyDev(uint32_t lFDev){
  uint8_t uFDevM, uFDevE;

#if defined(IS_169MHZ)
  uint8_t  bs = (READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_BS));
  bs = bs?8:20;
#else
  uint8_t  bs = ((READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_BS)+1)*4);
#endif

  /* Calculates the frequency deviation mantissa and exponent */
  MRSubG_SearchFreqDevME(lFDev, &uFDevM, &uFDevE, bs);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_FDEV_M, uFDevM);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_FDEV_E, uFDevE);
}

/**
* @brief  Return the frequency deviation.
* @retval uint32_t Frequency deviation value expressed in Hz.
*/
uint32_t HAL_MRSubG_GetFrequencyDev(void)
{
  uint8_t fdev_m;
  uint8_t fdev_e;
  uint32_t f_dev;
  uint16_t factor1;
  uint32_t factor2;

#if defined(IS_169MHZ)
  uint8_t  bs = (READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_BS));
  bs = bs?8:20;
#else
  uint8_t  bs = ((READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->SYNTH_FREQ, MR_SUBG_GLOB_DYNAMIC_SYNTH_FREQ_BS)+1)*4);
#endif

  fdev_m = READ_REG(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG) & MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_FDEV_M;
  fdev_e = READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_FDEV_E);

  factor1 = fdev_e==0 ? 0 : 256;
  factor2 = fdev_e==0 ? 0 : (fdev_e-1);

  f_dev = (LL_GetXTALFreq()*(uint64_t)((factor1+fdev_m)*(1<<(factor2))*bs/8)/(bs*(1<<19)));

  return f_dev;
}

/**
* @brief  Set the channel filter bandwidth.
* @param  lBandwidth channel filter bandwidth expressed in Hz.
*         The API will search the most closer value according to a fixed table of channel
*         bandwidth values (@ref s_Channel_Filter_Bandwidth).
*         To verify the settled channel bandwidth it is possible to use the HAL_MRSubG_GetChannelBW API.
* @retval None.
*/
void HAL_MRSubG_SetChannelBW(uint32_t lBandwidth)
{
  uint8_t uBwM = 0;
  uint8_t uBwE = 0;
  uint32_t f_if = 0;
  uint32_t if_offset = 0;
  uint32_t chf_threshold = 400000;
  uint32_t f_dig=LL_GetXTALFreq()/3;

  /* Calculates the channel bandwidth mantissa and exponent */
  MRSubG_SearchChannelBwME(lBandwidth, &uBwM, &uBwE);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_CHFLT_M, uBwM);
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_CHFLT_E, uBwE);

  /* Set IF to 600 kHz, if channel filter requested is greater then CHF threshold */
  if (lBandwidth > chf_threshold){
    SET_BIT(MR_SUBG_GLOB_STATIC->IF_CTRL, MR_SUBG_GLOB_STATIC_IF_CTRL_IF_MODE);

    /* Define f_if */
    f_if = 600;
  }
  else{
    /* Set antialiasing filter to 684kHz */
    CLEAR_BIT(MR_SUBG_GLOB_STATIC->IF_CTRL, MR_SUBG_GLOB_STATIC_IF_CTRL_IF_MODE);

    /* Define f_if */
    f_if = 300;
  }

  if_offset = (((f_if*100)*65536)/f_dig)*10;

  /* Set IF */
#if defined(IS_169MHZ)
  /* WL33xA */
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->IF_CTRL, MR_SUBG_GLOB_STATIC_IF_CTRL_IF_OFFSET_ANA, 0);
#else
  /* WL33x */
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->IF_CTRL, MR_SUBG_GLOB_STATIC_IF_CTRL_IF_OFFSET_ANA, if_offset);
#endif

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->IF_CTRL, MR_SUBG_GLOB_STATIC_IF_CTRL_IF_OFFSET_DIG, if_offset);
}

/**
* @brief  Return the channel filter bandwidth.
* @retval uint32_t Channel filter bandwidth expressed in Hz.
*/
uint32_t HAL_MRSubG_GetChannelBW(void)
{
  uint8_t cm, ce;

  uint32_t fclk = (LL_GetXTALFreq()/3);
  uint32_t correction_factor = fclk/16000000;

  cm = READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_CHFLT_M);
  ce = READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_CHFLT_E);

  uint8_t index = ce*9 + cm;
  return correction_factor*s_Channel_Filter_Bandwidth[index];
}

/**
* @brief  Set the modulation type.
* @param  xModulation modulation to set.
*         This parameter shall be of type @ref MRSubGModSelect.
* @param  dsssExponent the DSSS spreading exponent. 0 means DSSS disabled.
* @retval None.
*/
void HAL_MRSubG_SetModulation(MRSubGModSelect xModulation, uint8_t dsssExponent){
  assert_param(IS_MODULATION(xModulation));

  /* Internal equalizer */
  switch(xModulation){
  case MOD_2GFSK05:
  case MOD_4GFSK05:
  case MOD_2GFSK1:
  case MOD_4GFSK1:
    /*In case of gaussian filter, in order to reduce intersymbol interference (ISI),
    * we have to set the internal equalizer to 2 symbols */
    MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_AS_EQU_CTRL, 0x02);
    break;
  default:
    /* For non gaussian modulation set internal equalizer to 0 symbols */
    MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_AS_EQU_CTRL, 0x00);
  }

  /* Post filter */
  switch(xModulation){
  case MOD_4GFSK05:
  case MOD_4GFSK1:
  case MOD_4FSK:
    /*In case of 4 level FSK modulation, in order to reduce intersymbol interference (ISI),
    * we have to set the post filter len equal to 8 (register value 0). */
    MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL0, MR_SUBG_RADIO_CLKREC_CTRL0_PSTFLT_LEN, 0x00);
    break;
  default:
    MODIFY_REG_FIELD(MR_SUBG_RADIO->CLKREC_CTRL0, MR_SUBG_RADIO_CLKREC_CTRL0_PSTFLT_LEN, 0x01);
  }

  /* Modulation */
  switch(xModulation){
  case MOD_2GFSK05:
  case MOD_4GFSK05:
    MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_BT_SEL, 1);
    xModulation &= 0x0F;
    break;
  default:
    MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_BT_SEL, 0);
  }

  /* Evaluate DSSS settings */
  MRSUBG_EvaluateDSSS(xModulation, dsssExponent);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_MOD_TYPE, xModulation);
}

/**
* @brief  Return the modulation type used.
* @retval MRSubGModSelect Settled modulation type.
*/
MRSubGModSelect HAL_MRSubG_GetModulation(void)
{
  MRSubGModSelect retMod;
  retMod = (MRSubGModSelect)(READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_MOD_TYPE));

  if(retMod == MOD_2GFSK1 || retMod == MOD_4GFSK1)
  {
    /* Check the BT_SEL bit to evaluate if xGFSK1 or 05 */
    uint8_t bt = READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_BT_SEL);

    if (bt) { retMod |= 0x10; }
  }

  return retMod;
}

/**
 * @brief  Return RSSI value in dBm from content of RSSI_LEVEL_ON_SYNC field.
 * @retval int32_t RSSI value.
 */
int32_t HAL_MRSubG_GetRssidBm(void)
{
  uint16_t rssiReg = LL_MRSubG_GetRssiLevelOnSync();
  return __HAL_MRSUBG_CONVERT_RSSI_TO_DBM(rssiReg);
}

/**
 * @brief  Set the value for RSSI threshold according to the following formula:
 * RSSIdBm = (rssi_level_xx/2)-(96+GAIN_RX_CHAIN) - See equation 7 in UM_MR_SubG_IP
 * @param  rssiTh The desired RSSI threshold in dBm.
 * @retval None.
 */
void HAL_MRSubG_SetRSSIThreshold(int16_t rssiTh){
  uint16_t rssiValReg = 2*(rssiTh+(96+GAIN_RX_CHAIN));
  LL_MRSubG_SetRssiThresholdRegister(rssiValReg);
}

/**
 * @brief  Get the value for RSSI threshold in dBm
 * @retval int32_t the RSSI Threshold in dBm.
 */
int32_t HAL_MRSubG_GetRSSIThreshold(void){
  /* Return RSSI Threshold */
  uint16_t rssiReg = READ_REG(MR_SUBG_GLOB_STATIC->AS_QI_CTRL) & MR_SUBG_GLOB_STATIC_AS_QI_CTRL_RSSI_THR;
  return MRSubG_ConvertRssiToDbm(rssiReg);
}

/**
* @brief  Sets a specific PA_LEVEL register, with a value given in dBm.
* @param  cIndex PA_LEVEL to set. This parameter shall be in the range [0:7].
* @param  lPowerdBm PA value to write expressed in dBm.
* @param  drvMode PA drive modes.
* @retval None.
*/
void HAL_MRSubG_SetPALeveldBm(uint8_t cIndex, int8_t lPowerdBm, MRSubG_PA_DRVMode drvMode)
{
  int32_t pa03 = 0;
  int32_t pa07 = 0;
  uint8_t maxAllowedValue;

  SET_BIT(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_RAMP_ENABLE);

  LL_MRSubG_SetPAMode(PA_LEGACY);
  LL_MRSubG_SetPADriveMode(drvMode);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_LEVEL_MAX_INDEX, cIndex);

  maxAllowedValue = MRSubG_GetAllowedMaxOutputPower(drvMode);

  if(lPowerdBm > maxAllowedValue){
    lPowerdBm = 0x51;
    LL_MRSubG_SetPADegen(ENABLE);
  }
  else{
    int8_t tmpPow;
    tmpPow = MAX_DBM-((maxAllowedValue-lPowerdBm)*2);

    lPowerdBm = tmpPow>0?tmpPow:0;
  }

  for (int i=cIndex; i>=0; i--){
    if(i<4)
      pa03 |= (int32_t)(lPowerdBm)<<(i*8);
    else
      pa07 |= (int32_t)(lPowerdBm)<<((i%4)*8);

    lPowerdBm = (lPowerdBm - 10) > 0 ? lPowerdBm - 10 : 0;
  }

  WRITE_REG(MR_SUBG_GLOB_STATIC->PA_LEVEL_3_0, pa03);
  WRITE_REG(MR_SUBG_GLOB_STATIC->PA_LEVEL_7_4, pa07);
}

/**
* @brief  Returns a value in dBm.
* @retval int32_t Settled power level expressed in dBm.
*/
int8_t HAL_MRSubG_GetPALeveldBm(void)
{
  int32_t retDbm;

  /* Get the max PA Index */
  uint8_t maxIdx = LL_MRSubG_GetPALevelMaxIndex();

  if(maxIdx < 4){
    retDbm = READ_REG(MR_SUBG_GLOB_STATIC->PA_LEVEL_3_0) & MR_SUBG_GLOB_STATIC_PA_LEVEL_3_0_PA_LEVEL0;
    return retDbm << maxIdx * 8;
  }
  else {
    retDbm = READ_REG(MR_SUBG_GLOB_STATIC->PA_LEVEL_7_4) & MR_SUBG_GLOB_STATIC_PA_LEVEL_7_4_PA_LEVEL4;
    return retDbm << (maxIdx%4) * 8;
  }
}

/**
 * @brief  Returns the number of bytes after each TX/RX transaction.
 * @retval The number of bytes after each TX/RX transaction.
 */
uint32_t HAL_MRSubG_GetBytesOfTransaction(void){
  uint16_t used = READ_REG_FIELD(MR_SUBG_GLOB_STATUS->DATABUFFER_INFO, MR_SUBG_GLOB_STATUS_DATABUFFER_INFO_NB_DATABUFFER_USED);
  uint16_t size = READ_REG(MR_SUBG_GLOB_STATIC->DATABUFFER_SIZE) & MR_SUBG_GLOB_STATIC_DATABUFFER_SIZE_DATABUFFER_SIZE;
  uint16_t count = READ_REG_FIELD(MR_SUBG_GLOB_STATUS->DATABUFFER_INFO, MR_SUBG_GLOB_STATUS_DATABUFFER_INFO_CURRENT_DATABUFFER_COUNT);

  return (used*size)+count;
}

/*
 * @brief  Convert microseconds into interpolated absolute time value. SCM_COUNTER must be ready for meaningful results.
 * @param  microseconds Time in microseconds (integer)
 * @retval Time in interpolated absolute time units, can be used for sequencer intervals and timeouts.
 */
uint32_t HAL_MRSubG_Sequencer_Microseconds(uint32_t microseconds)
{
  /* Determine true frequency (relative to 16MHz clock) of "interpolated absolute time" value */
  uint16_t slow_clock_freq = 32000;
  uint16_t scm_counter_currval = READ_REG_FIELD(MR_SUBG_GLOB_MISC->SCM_COUNTER_VAL, MR_SUBG_GLOB_MISC_SCM_COUNTER_VAL_SCM_COUNTER_CURRVAL);
  if (scm_counter_currval != 0)
    slow_clock_freq = 32ull * 16000000ull / scm_counter_currval;
  uint64_t interpolated_absolute_time = 16u * slow_clock_freq;

  return (((uint64_t)microseconds) * interpolated_absolute_time / 1000000ull) + 0x20;
}

/*
 * @brief  Convert milliseconds into interpolated absolute time value. SCM_COUNTER must be ready for meaningful results.
 * @param  milliseconds Time in milliseconds (integer)
 * @retval Time in interpolated absolute time units, can be used for sequencer intervals and timeouts.
 */
uint32_t HAL_MRSubG_Sequencer_Milliseconds(uint32_t milliseconds)
{
  return HAL_MRSubG_Sequencer_Microseconds(milliseconds * 1000ul);
}

/*
 * @brief  Convert seconds into interpolated absolute time value. SCM_COUNTER must be ready for meaningful results.
 * @param  seconds Time in seconds (integer)
 * @retval Time in interpolated absolute time units, can be used for sequencer intervals and timeouts.
 */
uint32_t HAL_MRSubG_Sequencer_Seconds(uint32_t seconds)
{
  return HAL_MRSubG_Sequencer_Microseconds(seconds * 1000000ul);
}

/*
 * @brief  Store the current contents of all static SubGHz static configuration registers to
 *         given global configuration table for sequencer.
 * @param  cfg Pointer to global configuration table struct.
 * @retval SUCCESS if operation was successful, ERROR if RAM table pointer is not word-aligned.
 */
ErrorStatus HAL_MRSubG_Sequencer_ApplyStaticConfig(MRSubG_Sequencer_GlobalConfiguration *cfg)
{
  /* Ensure GlobalConfiguration RAM table is word-aligned */
  if (((uint32_t)cfg) % 4 != 0)
    return ERROR;

  memcpy((void*)&cfg->StaticConfigReg, (void*)MR_SUBG_GLOB_STATIC, sizeof(MR_SUBG_GLOB_STATIC_TypeDef));

  return SUCCESS;
}

/*
 * @brief  Store the current contents of all static SubGHz static configuration registers to
 *         given global configuration table for sequencer.
 * @param  cfg Pointer to global configuration table struct.
 * @param  cmd The command (e.g., TX / RX / SABORT) to issue upon execution of this sequencer action.
 * @retval SUCCESS if operation was successful, ERROR if RAM table pointer is not word-aligned
 *         or NextAction1Interval / NextAction2Interval value is invalid.
 */
ErrorStatus HAL_MRSubG_Sequencer_ApplyDynamicConfig(MRSubG_Sequencer_ActionConfiguration *cfg, MRSubGCmd cmd)
{
  /* Ensure ActionConfiguration RAM table is word-aligned */
  if (((uint32_t)cfg) % 4 != 0)
    return ERROR;

  /* NextAction1Interval and NextAction2Interval must not be smaller than (SOC_WAKEUP_OFFSET + 2) slow clock cycles */
  uint32_t soc_wakeup_offset = READ_REG_FIELD(MR_SUBG_GLOB_RETAINED->WAKEUP_CTRL, MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_SOC_WAKEUP_OFFSET);
  uint32_t min_next_action_interval = (soc_wakeup_offset + 2) * 16;
  if (cfg->NextAction1Interval != 0 && cfg->NextAction1Interval < min_next_action_interval)
    return ERROR;

  if (cfg->NextAction2Interval != 0 &&  cfg->NextAction2Interval < min_next_action_interval)
    return ERROR;

  /* Copy current dynamic register configuration to ActionConfiguration block */
  memcpy((void*)&cfg->DynamicConfigReg, (void*)MR_SUBG_GLOB_DYNAMIC, sizeof(MR_SUBG_GLOB_DYNAMIC_TypeDef));
  MODIFY_REG_FIELD(cfg->DynamicConfigReg.COMMAND, MR_SUBG_GLOB_DYNAMIC_COMMAND_COMMAND_ID, cmd);

  return SUCCESS;
}

/**
 * @brief  Set the payload length for the Basic packet format.
 * @param  nPayloadLength payload length in bytes.
 * @retval None.
 */
void HAL_MRSubG_PktBasicSetPayloadLength(uint16_t nPayloadLength){
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DATABUFFER_SIZE, MR_SUBG_GLOB_STATIC_DATABUFFER_SIZE_DATABUFFER_SIZE, nPayloadLength);
  LL_MRSUBG_SetPacketLength(nPayloadLength);
}

/**
 * @brief  Initialize the STM32WL3 Basic packet according to the specified parameters in the MRSubG_PcktBasicFields struct.
 * @param  pxPktBasicInit Basic packet init structure.
 *         This parameter is a pointer to @ref MRSubG_PcktBasicFields.
 * @retval None.
 */
void HAL_MRSubG_PacketBasicInit(MRSubG_PcktBasicFields* pxPktBasicInit){

  /* Check the parameters */
  assert_param(IS_PREAMBLE_LEN(pxPktBasicInit->PreambleLength));
  assert_param(IS_SYNC_LEN(pxPktBasicInit->SyncLength));
  assert_param(IS_FUNCTIONAL_STATE(pxPktBasicInit->DataWhitening));

  /* Set the Packet Format to Basic Packet */
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_PCKT_FORMAT, PKT_BASIC);

  /* Init the Whitening to 0x1FF */
  LL_MRSubG_PacketHandlerSetWhiteningInit(0x1FF);

  /* Set the SYNC */
  LL_MRSubG_SetSyncPresent(pxPktBasicInit->SyncPresent);
  LL_MRSubG_SetSyncLength(pxPktBasicInit->SyncLength);
  LL_MRSubG_SetSyncWord(pxPktBasicInit->SyncWord);
  LL_MRSubG_SetSecondarySync(DISABLE);

  /* Set the PREAMBLE */
  LL_MRSubG_SetPreambleLength(pxPktBasicInit->PreambleLength);
  LL_MRSubG_SetPreambleSeq(pxPktBasicInit->PreambleSequence);

  LL_MRSubG_PacketHandlerWhitening(pxPktBasicInit->DataWhitening);
  LL_MRSubG_PacketHandlerCoding(pxPktBasicInit->Coding);
  LL_MRSubG_PacketHandlerSetCrcMode(pxPktBasicInit->CrcMode);
  MODIFY_REG(MR_SUBG_GLOB_STATIC->CRC_INIT, MR_SUBG_GLOB_STATIC_CRC_INIT_CRC_INIT_VAL, 0xFFFFFFFF);

  /* Set the Fixed or Variable Packet Length mode */
  LL_MRSUBG_SetFixedVariableLength(pxPktBasicInit->FixVarLength);

  /* Set the Packet Length width. Relevant only if FIX_VAR_LEN=1  */
  LL_MRSubG_SetLenWidth(pxPktBasicInit->LengthWidth);

  LL_MRSubG_SetPostambleLength(pxPktBasicInit->PostambleLength);
  LL_MRSubG_SetPostamblSeq(pxPktBasicInit->PostambleSequence);
}

/**
 * @brief  Initialize the STM32WL3 WMBUS packet according to the specified parameters in the PktWMbusInit struct.
 * @param  pxPktWMbusInit pointer to a PktWMbusInit structure that contains the configuration information for the specified S2LP WMBUS PACKET FORMAT.
 *         This parameter is a pointer to @ref MRSubG_WMBUS_PcktFields.
 * @retval None.
 */
void HAL_MRSubG_WMBus_PacketInit(MRSubG_WMBUS_PcktFields* pxPktWMbusInit){
  /* Check the parameters */
  assert_param(IS_WMBUS_SUBMODE(pxPktWMbusInit->xWMbusSubmode));

  /* Set the Packet Format to WMBus Packet and disable HW CRC */
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_PCKT_FORMAT, PKT_BASIC);
  LL_MRSubG_PacketHandlerSetCrcMode(PKT_NO_CRC);

  s_cWMbusSubmode = pxPktWMbusInit->xWMbusSubmode;

  if(s_cWMbusSubmode==WMBUS_SUBMODE_S1_S2_LONG_HEADER) {
    LL_MRSubG_SetPreambleLength(((uint16_t)pxPktWMbusInit->PreambleLength) + WMBUS_PREAMBLE_LEN_S1S2LONGHEADER);

    /* Set the SYNC */
    LL_MRSubG_SetSyncPresent(ENABLE);
    LL_MRSubG_SetSyncLength(WMBUS_SYNC_LEN_S1S2LONGHEADER);
    LL_MRSubG_SetSyncWord(WMBUS_SYNCWORD_S1S2LONGHEADER);

    /* Set the Coding type */
    LL_MRSubG_PacketHandlerCoding(CODING_MANCHESTER);
    LL_MRSubG_PacketHandlerManchesterType(MANCHESTER_TYPE1);

    LL_MRSubG_SetPostamblSeq(POST_SEQ_1010);
  }
  else if(s_cWMbusSubmode==WMBUS_SUBMODE_S1_M_S2_T2_OTHER_TO_METER) {
    LL_MRSubG_SetPreambleLength(((uint16_t)pxPktWMbusInit->PreambleLength) + WMBUS_PREAMBLE_LEN_S1MS2T2OTHERTOMETER);

    /* Set the SYNC */
    LL_MRSubG_SetSyncPresent(ENABLE);
    LL_MRSubG_SetSyncLength(WMBUS_SYNC_LEN_S1MS2T2OTHERTOMETER);
    LL_MRSubG_SetSyncWord(WMBUS_SYNCWORD_S1MS2T2OTHERTOMETER);

    /* Set the Coding type */
    LL_MRSubG_PacketHandlerCoding(CODING_MANCHESTER);

    /* Constellation map setting */
    LL_MRSubG_SetConstellationMapping((uint8_t)2); /* See Table 42 of the ref. manual */

    LL_MRSubG_SetPostamblSeq(POST_SEQ_1010);
  }
  else if(s_cWMbusSubmode==WMBUS_SUBMODE_T1_T2_METER_TO_OTHER) {
    LL_MRSubG_SetPreambleLength(((uint16_t)pxPktWMbusInit->PreambleLength) + WMBUS_PREAMBLE_LEN_T1T2METERTOOTHER);

    /* Set the SYNC */
    LL_MRSubG_SetSyncPresent(ENABLE);
    LL_MRSubG_SetSyncLength(WMBUS_SYNC_LEN_T1T2METERTOOTHER);
    LL_MRSubG_SetSyncWord(WMBUS_SYNCWORD_T1T2METERTOOTHER);

    /* Set the Coding type */
    LL_MRSubG_PacketHandlerCoding(CODING_3o6);
  }
  else if(s_cWMbusSubmode==WMBUS_SUBMODE_R2_SHORT_HEADER) {
    LL_MRSubG_SetPreambleLength(((uint16_t)pxPktWMbusInit->PreambleLength) + WMBUS_PREAMBLE_LEN_R2);

    /* Set the SYNC */
    LL_MRSubG_SetSyncPresent(ENABLE);
    LL_MRSubG_SetSyncLength(WMBUS_SYNC_LEN_R2);
    LL_MRSubG_SetSyncWord(WMBUS_SYNCWORD_R2);

    /* Set the Coding type */
    LL_MRSubG_PacketHandlerCoding(CODING_MANCHESTER);

    /* Constellation map setting */
    LL_MRSubG_SetConstellationMapping((uint8_t)2); /* See Table 42 of the ref. manual */
  }

  LL_MRSubG_SetPostambleLength(pxPktWMbusInit->PostambleLength);
}

/**
 * @brief  Initialize the STM32WL3 802.15.4 packet according to the specified parameters in the MRSubG_802_15_4_PcktFields struct.
 * @param  px802_15_4PktInit 802.15.4 packet init structure.
 *         This parameter is a pointer to @ref MRSubG_802_15_4_PcktFields.
 * @retval 1 in case of errors.
 */
void HAL_MRSubG_802_15_4_PacketInit(MRSubG_802_15_4_PcktFields* px802_15_4PktInit){

  uint32_t const*sync_word_ptr;
  uint8_t sync_word_len;
  uint16_t preamble_len;

  /* Check the parameters */
  assert_param(IS_MODULATION_15_4G(px802_15_4PktInit->Modulation));
  assert_param(IS_FCS_TYPE(px802_15_4PktInit->FCSType));
  assert_param(IS_PREAMBLE_15_4G_LEN(px802_15_4PktInit->PreambleLength));
  assert_param(IS_FEC_TYPE(px802_15_4PktInit->FecType));
  assert_param(IS_FUNCTIONAL_STATE(px802_15_4PktInit->Whitening));
  assert_param(IS_FRAME_LEN(px802_15_4PktInit->FrameLength));

  if (px802_15_4PktInit->Modulation == MOD_2FSK) {
    sync_word_ptr = SFD_2FSK;
    sync_word_len = 2;
    preamble_len = px802_15_4PktInit->PreambleLength * 8;
  } else {
    sync_word_ptr = SFD_4FSK;
    sync_word_len = 4;
    preamble_len = px802_15_4PktInit->PreambleLength * 16;
  }

  /* Init the Whitening to 0x1FF */
  LL_MRSubG_PacketHandlerSetWhiteningInit(0x1FF);

  /* Set the Packet Format to 802.15.4 Packet */
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_PCKT_FORMAT, PKT_802_15_4);

  WRITE_REG(MR_SUBG_GLOB_STATIC->SYNC, sync_word_ptr[0]);

  WRITE_REG(MR_SUBG_GLOB_STATIC->SEC_SYNC, sync_word_ptr[1]);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_PREAMBLE_SEQ, PRE_SEQ_0101);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_PREAMBLE_LENGTH, preamble_len / 2);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SYNC_PRESENT, 1);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SYNC_LEN, SYNC_BYTE(sync_word_len));

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_CRC_MODE, px802_15_4PktInit->FCSType);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->PCKTLEN_CONFIG, MR_SUBG_GLOB_DYNAMIC_PCKTLEN_CONFIG_PCKTLEN, px802_15_4PktInit->FrameLength);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_FCS_TYPE_4G,
                   (px802_15_4PktInit->FCSType == FCS_16BIT) ? 1: 0);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_FEC_TYPE_4G, (px802_15_4PktInit->FecType > 1 ? 1 : 0));

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_INT_EN_4G,
                   ((px802_15_4PktInit->FecType == FEC_15_4_G_NRNSC) || (px802_15_4PktInit->FecType == FEC_15_4_G_RSC_Interleaving)) );

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_CODING_SEL, (px802_15_4PktInit->FecType > 0));

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_WHIT_EN, px802_15_4PktInit->Whitening);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_WHIT_BF_FEC, 0);

  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_BYTE_SWAP, 1);

  WRITE_REG(MR_SUBG_GLOB_STATIC->CRC_INIT,  ((px802_15_4PktInit->FCSType == FCS_16BIT) ? 0 : 0xFFFFFFFF));
}

/**
  * @brief MRSUBG MSP Init
  * @retval None
  */
__weak void HAL_MRSubG_MspInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MRSubG_MspInit could be implemented in the user file
    */
}

/**
  * @brief MRSUBG MSP DeInit
  * @retval None
  */
__weak void HAL_MRSubG_MspDeInit(void)
{

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MRSubG_MspDeInit could be implemented in the user file
    */
}

__weak void HAL_MRSubG_IRQ_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
             the HAL_MRSubG_IRQ_Callback could be implemented in the user file
    */
}

__weak void HAL_MRSubG_BUSY_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
             the HAL_MRSubG_BUSY_Callback could be implemented in the user file
    */
}

__weak void HAL_MRSubG_TX_RX_SEQUENCE_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
             the HAL_MRSubG_TX_RX_SEQUENCE_Callback could be implemented in the user file
    */
}

__weak void HAL_MRSubG_WKUP_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
             the HAL_MRSubG_WKUP_Callback could be implemented in the user file
    */
}

void HAL_MRSubG_IRQHandler(void)
{
  HAL_MRSubG_IRQ_Callback();
}

void HAL_MRSubG_BUSY_IRQHandler(void)
{
  HAL_MRSubG_BUSY_Callback();
}

void HAL_MRSubG_TX_RX_SEQUENCE_IRQHandler(void)
{
  HAL_MRSubG_TX_RX_SEQUENCE_Callback();
}

void HAL_MRSubG_WKUP_IRQHandler(void)
{
  HAL_MRSubG_WKUP_Callback();
}


/**
  * @}
  */

#endif /* HAL_MRSUBG_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
