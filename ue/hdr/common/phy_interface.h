/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2015 Software Radio Systems Limited
 *
 * \section LICENSE
 *
 * This file is part of the srsUE library.
 *
 * srsUE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsUE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

/******************************************************************************
 *  File:         phy_interface.h
 *  Description:  PHY layer interfaces provided to other layers
 *  Reference:
 *****************************************************************************/

#ifndef PHY_INTERFACE_H
#define PHY_INTERFACE_H

#include <stdint.h>
#include <string>
#include "srslte/srslte.h"

namespace srsue {
  
class phy_interface_params 
{
public: 
  
  /* PHY parameters */
  typedef enum {
    
    DL_FREQ = 0, 
    UL_FREQ, 
    
    PHY_CELL_ID,

    P_MAX,
    PDSCH_RSPOWER,
    PDSCH_PB,
    
    PUSCH_EN_64QAM,
    PUSCH_RS_CYCLIC_SHIFT,
    PUSCH_RS_GROUP_ASSIGNMENT,
    DMRS_GROUP_HOPPING_EN,
    DMRS_SEQUENCE_HOPPING_EN,
    
    PUSCH_HOPPING_N_SB,
    PUSCH_HOPPING_INTRA_SF,
    PUSCH_HOPPING_OFFSET,
    
    PUCCH_DELTA_SHIFT,
    PUCCH_CYCLIC_SHIFT,
    PUCCH_N_RB_2,
    PUCCH_N_PUCCH_1_0,
    PUCCH_N_PUCCH_1_1,
    PUCCH_N_PUCCH_1_2,
    PUCCH_N_PUCCH_1_3,
    PUCCH_N_PUCCH_1,
    PUCCH_N_PUCCH_2,
    PUCCH_N_PUCCH_SR,

    SR_CONFIG_INDEX,
    
    SRS_UE_TXCOMB, 
    SRS_UE_NRRC,
    SRS_UE_DURATION,
    SRS_UE_CONFIGINDEX,
    SRS_UE_BW,
    SRS_UE_HOP,
    SRS_UE_CS,
    SRS_UE_CYCLICSHIFT,
    SRS_CS_BWCFG,
    SRS_CS_SFCFG,
    SRS_CS_ACKNACKSIMUL,
    SRS_IS_CONFIGURED,
    
    CQI_PERIODIC_PMI_IDX,
    CQI_PERIODIC_SIMULT_ACK,
    CQI_PERIODIC_FORMAT_SUBBAND,
    CQI_PERIODIC_FORMAT_SUBBAND_K,
    CQI_PERIODIC_CONFIGURED,
          
    PWRCTRL_ENABLED, 
    PWRCTRL_P0_NOMINAL_PUSCH,
    PWRCTRL_ALPHA,
    PWRCTRL_P0_NOMINAL_PUCCH,
    PWRCTRL_DELTA_PUCCH_F1,
    PWRCTRL_DELTA_PUCCH_F1B,
    PWRCTRL_DELTA_PUCCH_F2,
    PWRCTRL_DELTA_PUCCH_F2A,
    PWRCTRL_DELTA_PUCCH_F2B,
    PWRCTRL_DELTA_MSG3,
    PWRCTRL_P0_UE_PUSCH,
    PWRCTRL_DELTA_MCS_EN,
    PWRCTRL_ACC_EN,
    PWRCTRL_P0_UE_PUCCH,
    PWRCTRL_SRS_OFFSET,
        
    UCI_I_OFFSET_ACK,
    UCI_I_OFFSET_RI,
    UCI_I_OFFSET_CQI,
    
    PRACH_CONFIG_INDEX,
    PRACH_ROOT_SEQ_IDX,
    PRACH_HIGH_SPEED_FLAG,
    PRACH_ZC_CONFIG,
    PRACH_FREQ_OFFSET,
    
    PRACH_GAIN,    
    FORCE_ENABLE_64QAM,
    
    PDSCH_MAX_ITS,
    
    EQUALIZER_COEFF,
    CQI_MAX,
    CQI_OFFSET,
    CQI_FIXED,
    CQI_RANDOM_MS,
    CQI_PERIOD_MS,
    CQI_PERIOD_DUTY_100,
    
    SNR_ESTIM_ALG, 
    SNR_EMA_COEFF_100,
    CFO_INTEGER_ENABLED,
    CFO_CORRECT_TOL_HZ_100,
    TIME_CORRECT_PERIOD,
    SFO_CORRECT_DISABLE,
    SSS_ALGORITHM, 
    ESTIMATOR_FIL_W_1000,
    
    NOF_PARAMS,    
  } phy_param_t;

  /* Get/Set PHY parameters */  
  virtual void    set_param(phy_param_t param, int64_t value) = 0; 
  virtual int64_t get_param(phy_param_t param) = 0;  

};

/* Interface MAC -> PHY */
class phy_interface
{
public:
  /* Configure PRACH using parameters written with set_param() */
  virtual void configure_prach_params() = 0;
  
  /* Start synchronization with strongest cell in the current carrier frequency */
  virtual void sync_start() = 0; 
  virtual void sync_stop() = 0;
  
  virtual void prach_send(uint32_t preamble_idx, int allowed_subframe, float target_power_dbm) = 0;  
  virtual int  prach_tx_tti() = 0; 
  
  /* Indicates the transmission of a SR signal in the next opportunity */
  virtual void sr_send() = 0;  
  virtual int  sr_last_tx_tti() = 0; 
  
  /* Time advance commands */
  virtual void set_timeadv_rar(uint32_t ta_cmd) = 0;
  virtual void set_timeadv(uint32_t ta_cmd) = 0;
  
  /* Sets RAR grant payload */
  virtual void set_rar_grant(uint32_t tti, uint8_t grant_payload[SRSLTE_RAR_GRANT_LEN]) = 0; 

  /* Instruct the PHY to decode PDCCH with the CRC scrambled with given RNTI */
  virtual void pdcch_ul_search(srslte_rnti_type_t rnti_type, uint16_t rnti, int tti_start = -1, int tti_end = -1) = 0;
  virtual void pdcch_dl_search(srslte_rnti_type_t rnti_type, uint16_t rnti, int tti_start = -1, int tti_end = -1) = 0;
  virtual void pdcch_ul_search_reset() = 0;
  virtual void pdcch_dl_search_reset() = 0;
  
  virtual uint32_t get_current_tti() = 0;
  
  virtual float get_phr() = 0; 
    
};

class phy_interface_rrc
    :public phy_interface_params
{
public:
  /* Is the PHY downlink synchronized? */
  virtual bool status_is_sync() = 0;

  /* Configure UL using parameters written with set_param() */
  virtual void configure_ul_params(bool pregen_disabled = false) = 0;

  virtual void reset() = 0;
  
  virtual void resync_sfn() = 0; 

};
  
}

#endif
  
