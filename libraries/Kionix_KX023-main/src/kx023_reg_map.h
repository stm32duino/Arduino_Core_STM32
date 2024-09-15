/**
 * @file kx023_reg_map.h
 * @author mtnguyen (manhthao.spm@gmail.com)
 * @brief This section contains the addresses for all KX023 embedded registers and also bit index of each registers
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __KX023_REG_MAP_h__
#define __KX023_REG_MAP_h__

#define KX023_XHPL_REG 0x00 // Read

#define KX023_XHPH_REG 0x01 // Read

#define KX023_YHPL_REG 0x02 // Read

#define KX023_YHPH_REG 0x03 // Read

#define KX023_ZHPL_REG 0x04 // Read

#define KX023_ZHPH_REG 0x05 // Read

#define KX023_XOUTL_REG 0x06 // Read

#define KX023_XOUTH_REG 0x07 // Read

#define KX023_YOUTL_REG 0x08 // Read

#define KX023_YOUTH_REG 0x09 // Read

#define KX023_ZOUTL_REG 0x0A // Read

#define KX023_ZOUTH_REG 0x0B // Read

#define KX023_COTR_REG 0x0C // Read

#define KX023_Who_AM_I_REG 0x0F // Read/Write

#define KX023_TSCP_REG 0x10 // Read
#define KX023_TSCP_LE_BIT 5
#define KX023_TSCP_RI_BIT 4
#define KX023_TSCP_DO_BIT 3
#define KX023_TSCP_UP_BIT 2
#define KX023_TSCP_FD_BIT 1
#define KX023_TSCP_FU_BIT 0

#define KX023_TSPP_REG 0x11 // Read
#define KX023_TSPP_LE_BIT 5
#define KX023_TSPP_RI_BIT 4
#define KX023_TSPP_DO_BIT 3
#define KX023_TSPP_UP_BIT 2
#define KX023_TSPP_FD_BIT 1
#define KX023_TSPP_FU_BIT 0

#define KX023_INS1_REG 0x12 // Read
#define KX023_INS1_TLE_BIT 5
#define KX023_INS1_TRI_BIT 4
#define KX023_INS1_TDO_BIT 3
#define KX023_INS1_TUP_BIT 2
#define KX023_INS1_TFD_BIT 1
#define KX023_INS1_TFU_BIT 0

#define KX023_INS2_REG 0x13 // Read
#define KX023_INS2_BFI_BIT 6
#define KX023_INS2_WMI_BIT 5
#define KX023_INS2_DRDY_BIT 4
#define KX023_INS2_TDTS1_BIT 3
#define KX023_INS2_TDTS0_BIT 2
#define KX023_INS2_WUFS_BIT 1
#define KX023_INS2_TPS_BIT 0
#define KX023_INS2_TDTS_MASK ((1 << KX023_INS2_TDTS1_BIT) | (1 << KX023_INS2_TDTS0_BIT))

#define KX023_INS3_REG 0x14 // Read
#define KX023_INS3_XNWU_BIT 5
#define KX023_INS3_XPWU_BIT 4
#define KX023_INS3_YNWU_BIT 3
#define KX023_INS3_YPWU_BIT 2
#define KX023_INS3_ZNWU_BIT 1
#define KX023_INS3_ZPWU_BIT 0

#define KX023_STAT_REG 0x15 // Read
#define KX023_STAT_INT_BIT 4

#define KX023_INT_REL_REG 0x17 // Read

#define KX023_CNTL1_REG 0x18 // Read/Write
#define KX023_CNTL1_PC1_BIT 7
#define KX023_CNTL1_RES_BIT 6
#define KX023_CNTL1_DRDYE_BIT 5
#define KX023_CNTL1_GSEL1_BIT 4
#define KX023_CNTL1_GSEL0_BIT 3
#define KX023_CNTL1_TDTE_BIT 2
#define KX023_CNTL1_WUFE_BIT 1
#define KX023_CNTL1_TPE_BIT 0
#define KX023_CNTL1_GSEL_MASK ((1 << KX023_CNTL1_GSEL1_BIT) | (1 << KX023_CNTL1_GSEL0_BIT))

#define KX023_CNTL2_REG 0x19 // Read/Write
#define KX023_CNTL2_SRST_BIT 7
#define KX023_CNTL2_COTC_BIT 6
#define KX023_CNTL2_LEM_BIT 5
#define KX023_CNTL2_RIM_BIT 4
#define KX023_CNTL2_DOM_BIT 3
#define KX023_CNTL2_UPM_BIT 2
#define KX023_CNTL2_FDM_BIT 1
#define KX023_CNTL2_FUM_BIT 0

#define KX023_CNTL3_REG 0x1A // Read/Write
#define KX023_CNTL3_OTP1_BIT 7
#define KX023_CNTL3_OTP0_BIT 6
#define KX023_CNTL3_OTDT2_BIT 5
#define KX023_CNTL3_OTDT1_BIT 4
#define KX023_CNTL3_OTDT0_BIT 3
#define KX023_CNTL3_OWUF2_BIT 2
#define KX023_CNTL3_OWUF1_BIT 1
#define KX023_CNTL3_OWUF0_BIT 0
#define KX023_CNTL3_OTP_MASK ((1 << KX023_CNTL3_OTP1_BIT) | (1 << KX023_CNTL3_OTP0_BIT))
#define KX023_CNTL3_OTDT_MASK ((1 << KX023_CNTL3_OTDT2_BIT) | (1 << KX023_CNTL3_OTDT1_BIT) | (1 << KX023_CNTL3_OTDT0_BIT))
#define KX023_CNTL3_OWUF_MASK ((1 << KX023_CNTL3_OWUF2_BIT) | (1 << KX023_CNTL3_OWUF1_BIT) | (1 << KX023_CNTL3_OWUF0_BIT))

#define KX023_ODCNTL_REG 0x1B // Read/Write
#define KX023_ODCNTL_IIR_BYPASS_BIT 7
#define KX023_ODCNTL_LPRO_BIT 6
#define KX023_ODCNTL_OSA3_BIT 3
#define KX023_ODCNTL_OSA2_BIT 2
#define KX023_ODCNTL_OSA1_BIT 1
#define KX023_ODCNTL_OSA0_BIT 0
#define KX023_ODCNTL_OSA_MASK ((1 << KX023_ODCNTL_OSA3_BIT) | (1 << KX023_ODCNTL_OSA2_BIT) | (1 << KX023_ODCNTL_OSA1_BIT) | (1 << KX023_ODCNTL_OSA0_BIT))

#define KX023_INC1_REG 0x1C // Read/Write
#define KX023_INC1_IEN1_BIT 5
#define KX023_INC1_IEA1_BIT 4
#define KX023_INC1_IEL1_BIT 3
#define KX023_INC1_STPOL_BIT 1
#define KX023_INC1_SPI3E_BIT 0

#define KX023_INC2_REG 0x1D // Read/Write
#define KX023_INC2_XNWUE_BIT 5
#define KX023_INC2_XPWUE_BIT 4
#define KX023_INC2_YNWUE_BIT 3
#define KX023_INC2_YPWUE_BIT 2
#define KX023_INC2_ZNWUE_BIT 1
#define KX023_INC2_ZPWUE_BIT 0

#define KX023_INC3_REG 0x1E // Read/Write
#define KX023_INC3_TLEM_BIT 5
#define KX023_INC3_TRIM_BIT 4
#define KX023_INC3_TDOM_BIT 3
#define KX023_INC3_TUPM_BIT 2
#define KX023_INC3_TFDM_BIT 1
#define KX023_INC3_TFUM_BIT 0

#define KX023_INC4_REG 0x1F      // Read/Write
#define KX023_INC4_6_BFI_BIT 6   // INC4 & INC6 share the same structure
#define KX023_INC4_6_WMI_BIT 5   // INC4 & INC6 share the same structure
#define KX023_INC4_6_DRDYI_BIT 4 // INC4 & INC6 share the same structure
#define KX023_INC4_6_TDTI_BIT 2  // INC4 & INC6 share the same structure
#define KX023_INC4_6_WUFI_BIT 1  // INC4 & INC6 share the same structure
#define KX023_INC4_6_TPI_BIT 0   // INC4 & INC6 share the same structure

#define KX023_INC5_REG 0x20 // Read/Write
#define KX023_INC5_IEN2_BIT 5
#define KX023_INC5_IEA2_BIT 4
#define KX023_INC5_IEL2_BIT 3

#define KX023_INC6_REG 0x21 // Read/Write
// #define KX023_INC4_6_BFI_BIT 6   // INC4 & INC6 share the same structure
// #define KX023_INC4_6_WMI_BIT 5   // INC4 & INC6 share the same structure
// #define KX023_INC4_6_DRDYI_BIT 4 // INC4 & INC6 share the same structure
// #define KX023_INC4_6_TDTI_BIT 2  // INC4 & INC6 share the same structure
// #define KX023_INC4_6_WUFI_BIT 1  // INC4 & INC6 share the same structure
// #define KX023_INC4_6_TPI_BIT 0   // INC4 & INC6 share the same structure

#define KX023_TILT_TIMER_REG 0x22 // Read/Write

#define KX023_WUFC_REG 0x23 // Read/Write

#define KX023_TDTRC_REG 0x24 // Read/Write
#define KX023_TDTRC_DTRE_BIT 1
#define KX023_TDTRC_STRE_BIT 0

#define KX023_TDTC_REG 0x25 // Read/Write

#define KX023_TTH_REG 0x26 // Read/Write

#define KX023_TTL_REG 0x27 // Read/Write

#define KX023_FTD_REG 0x28 // Read/Write

#define KX023_STD_REG 0x29 // Read/Write

#define KX023_TLT_REG 0x2A // Read/Write

#define KX023_TWS_REG 0x2B // Read/Write

#define KX023_ATH_REG 0x30 // Read/Write

#define KX023_TILT_ANGLE_LL_REG 0x32 // Read/Write

#define KX023_TILT_ANGLE_HL_REG 0x33 // Read/Write

#define KX023_HYST_SET_REG 0x34 // Read/Write

#define KX023_LP_CNTL_REG 0x35 // Read/Write
#define KX023_LP_CNTL_AVC2_BIT 6
#define KX023_LP_CNTL_AVC1_BIT 5
#define KX023_LP_CNTL_AVC0_BIT 4
#define KX023_LP_CNTL_AVC_MASK ((1 << KX023_LP_CNTL_AVC2_BIT) | (1 << KX023_LP_CNTL_AVC1_BIT) | (1 << KX023_LP_CNTL_AVC0_BIT))

#define KX023_BUF_CNTL1_REG 0x3A // Read/Write
#define KX023_BUF_CNTL1_SMP_TH6_BIT 6
#define KX023_BUF_CNTL1_SMP_TH5_BIT 5
#define KX023_BUF_CNTL1_SMP_TH4_BIT 4
#define KX023_BUF_CNTL1_SMP_TH3_BIT 3
#define KX023_BUF_CNTL1_SMP_TH2_BIT 2
#define KX023_BUF_CNTL1_SMP_TH1_BIT 1
#define KX023_BUF_CNTL1_SMP_TH0_BIT 0

#define KX023_BUF_CNTL2_REG 0x3B // Read/Write
#define KX023_BUF_CNTL2_BUFE_BIT 7
#define KX023_BUF_CNTL2_BRES_BIT 6
#define KX023_BUF_CNTL2_BFIE_BIT 5
#define KX023_BUF_CNTL2_BUF_M1_BIT 1
#define KX023_BUF_CNTL2_BUF_M0_BIT 0
#define KX023_BUF_CNTL2_BUF_M_MASK ((1 << KX023_BUF_CNTL2_BUF_M1_BIT) | (1 << KX023_BUF_CNTL2_BUF_M0_BIT))

#define KX023_BUF_STATUS_1_REG 0x3C // Read

#define KX023_BUF_STATUS_2_REG 0x3D // Read
#define KX023_BUF_STATUS_2_BUF_TRIG_BIT 7

#define KX023_BUF_CLEAR_REG 0x3E // Write

#define KX023_BUF_READ_REG 0x3F // Read

#define KX023_SELF_TEST_REG 0x60 // Read/Write

#endif /* __KX023_REG_MAP_h__ */
