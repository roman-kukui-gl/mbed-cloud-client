/*******************************************************************************
 * Copyright 2016, 2017 ARM Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#include "pal.h"
#include "pal_plat_internalFlash.h"
#include "r_flash_rx_if.h"// #include "fsl_flash.h"

////////////////////////////PRIVATE///////////////////////////////////
// PAL_PRIVATE flash_config_t g_flashDescriptor = {0};
////////////////////////////END PRIVATE////////////////////////////////

palStatus_t pal_plat_internalFlashInit(void)
{
    flash_err_t status;
    palStatus_t ret = PAL_SUCCESS;

    //  Initialize the flash peripheral.
    status = R_FLASH_Open();
    if(FLASH_SUCCESS != status)
    {
        ret = PAL_ERR_INTERNAL_FLASH_INIT_ERROR;
    }
	return ret;
}


palStatus_t pal_plat_internalFlashDeInit(void)
{
    // memset(&g_flashDescriptor, 0, sizeof(g_flashDescriptor));
    /// \todo Clean memory before deinit

    // closes the flash driver.
    R_FLASH_Close();

	return PAL_SUCCESS;
}


palStatus_t pal_plat_internalFlashWrite(const size_t size, const uint32_t address, const uint32_t * buffer)
{
    palStatus_t ret = PAL_SUCCESS;
    flash_err_t status = FLASH_SUCCESS;

	/* We need to prevent flash accesses during program operation */
	__disable_irq();

    // flash_err_t R_FLASH_Write(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes);
	status = R_FLASH_Write(buffer, address, size);
	if (FLASH_SUCCESS == status)
	{
        /// \todo Implement flash verification after write operation.

		// // Must use kFlashMargin_User, or kFlashMargin_Factory for verify program
		// status = FLASH_VerifyProgram(&g_flashDescriptor, address, size, (uint32_t *)buffer, kFLASH_marginValueUser, NULL, NULL);
		// if(FLASH_SUCCESS != status)
		// {
		// 	ret = PAL_ERR_INTERNAL_FLASH_WRITE_ERROR;
		// }
	}
	__enable_irq();

    return ret;
}

palStatus_t pal_plat_internalFlashRead(const size_t size, const uint32_t address, uint32_t * buffer)
{
    /// \todo Fix exception, set proper flash areas

    // memcpy(buffer, (const void *)address, size);
    return PAL_SUCCESS;
}


palStatus_t pal_plat_internalFlashErase(uint32_t address, size_t size)
{
    palStatus_t ret = PAL_SUCCESS;
    flash_err_t  status = FLASH_SUCCESS;

    __disable_irq();

    flash_res_t blank_test_result;
    status = R_FLASH_Erase(address, pal_plat_internalFlashGetSectorSize(address));
 
    if (FLASH_SUCCESS == status)
    {
        status = R_FLASH_BlankCheck(address, pal_plat_internalFlashGetSectorSize(address), &blank_test_result);
    }

    if (FLASH_RES_BLANK != blank_test_result)
    {
        ret = PAL_ERR_INTERNAL_FLASH_ERASE_ERROR;
    }
    __enable_irq();

    return ret;
}


size_t pal_plat_internalFlashGetPageSize(void)
{
    /// \todo Replace by proper value

	// return FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE;
    return 1024;
}


size_t pal_plat_internalFlashGetSectorSize(uint32_t address)
{
    /// \todo Fix for providing sector size
    size_t devicesize = 1024;
    
    return devicesize;
}

