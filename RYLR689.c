/**

 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */
#include <main.h>
#include <RYLR689.h>

//#include <stddef.h>
#include <stdint.h>
//#include <string.h>
//#include <stdio.h>
#include <stdbool.h>

extern SPI_HandleTypeDef hspi1;

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/**
 * @brief Internal frequency of the radio
 */
#define LLCC68_XTAL_FREQ 32000000UL

#define PIN_LOW(port, pin)   		HAL_GPIO_WritePin((port), (pin), GPIO_PIN_RESET)
#define PIN_HIGH(port, pin)  		HAL_GPIO_WritePin((port), (pin), GPIO_PIN_SET)


/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */


/**
 * Commands Interface
*/ /*
typedef enum llcc68_commands_e
{
    // Operational Modes Functions
    LLCC68_SET_SLEEP                  = 0x84,
    LLCC68_SET_STANDBY                = 0x80,
    LLCC68_SET_FS                     = 0xC1,
    LLCC68_SET_TX                     = 0x83,
    LLCC68_SET_RX                     = 0x82,
    LLCC68_SET_STOP_TIMER_ON_PREAMBLE = 0x9F,
    LLCC68_SET_RX_DUTY_CYCLE          = 0x94,
    LLCC68_SET_CAD                    = 0xC5,
    LLCC68_SET_TX_CONTINUOUS_WAVE     = 0xD1,
    LLCC68_SET_TX_INFINITE_PREAMBLE   = 0xD2,
    LLCC68_SET_REGULATOR_MODE         = 0x96,
    LLCC68_CALIBRATE                  = 0x89,
    LLCC68_CALIBRATE_IMAGE            = 0x98,
    LLCC68_SET_PA_CFG                 = 0x95,
    LLCC68_SET_RX_TX_FALLBACK_MODE    = 0x93,
    // Registers and buffer Access
    LLCC68_WRITE_REGISTER = 0x0D,
    LLCC68_READ_REGISTER  = 0x1D,
    LLCC68_WRITE_BUFFER   = 0x0E,
    LLCC68_READ_BUFFER    = 0x1E,
    // DIO and IRQ Control Functions
    LLCC68_SET_DIO_IRQ_PARAMS         = 0x08,
    LLCC68_GET_IRQ_STATUS             = 0x12,
    LLCC68_CLR_IRQ_STATUS             = 0x02,
    LLCC68_SET_DIO2_AS_RF_SWITCH_CTRL = 0x9D,
    LLCC68_SET_DIO3_AS_TCXO_CTRL      = 0x97,
    // RF Modulation and Packet-Related Functions
    LLCC68_SET_RF_FREQUENCY          = 0x86,
    LLCC68_SET_PKT_TYPE              = 0x8A,
    LLCC68_GET_PKT_TYPE              = 0x11,
    LLCC68_SET_TX_PARAMS             = 0x8E,
    LLCC68_SET_MODULATION_PARAMS     = 0x8B,
    LLCC68_SET_PKT_PARAMS            = 0x8C,
    LLCC68_SET_CAD_PARAMS            = 0x88,
    LLCC68_SET_BUFFER_BASE_ADDRESS   = 0x8F,
    LLCC68_SET_LORA_SYMB_NUM_TIMEOUT = 0xA0,
    // Communication Status Information
    LLCC68_GET_STATUS           = 0xC0,
    LLCC68_GET_RX_BUFFER_STATUS = 0x13,
    LLCC68_GET_PKT_STATUS       = 0x14,
    LLCC68_GET_RSSI_INST        = 0x15,
    LLCC68_GET_STATS            = 0x10,
    LLCC68_RESET_STATS          = 0x00,
    // Miscellaneous
    LLCC68_GET_DEVICE_ERRORS = 0x17,
    LLCC68_CLR_DEVICE_ERRORS = 0x07,
} llcc68_commands_t; */

/**
 * Commands Interface buffer sizes
 */ /*
typedef enum llcc68_commands_size_e
{
    // Operational Modes Functions
    LLCC68_SIZE_SET_SLEEP                  = 2,
    LLCC68_SIZE_SET_STANDBY                = 2,
    LLCC68_SIZE_SET_FS                     = 1,
    LLCC68_SIZE_SET_TX                     = 4,
    LLCC68_SIZE_SET_RX                     = 4,
    LLCC68_SIZE_SET_STOP_TIMER_ON_PREAMBLE = 2,
    LLCC68_SIZE_SET_RX_DUTY_CYCLE          = 7,
    LLCC68_SIZE_SET_CAD                    = 1,
    LLCC68_SIZE_SET_TX_CONTINUOUS_WAVE     = 1,
    LLCC68_SIZE_SET_TX_INFINITE_PREAMBLE   = 1,
    LLCC68_SIZE_SET_REGULATOR_MODE         = 2,
    LLCC68_SIZE_CALIBRATE                  = 2,
    LLCC68_SIZE_CALIBRATE_IMAGE            = 3,
    LLCC68_SIZE_SET_PA_CFG                 = 5,
    LLCC68_SIZE_SET_RX_TX_FALLBACK_MODE    = 2,
    // Registers and buffer Access
    // Full size: this value plus buffer size
    LLCC68_SIZE_WRITE_REGISTER = 3,
    // Full size: this value plus buffer size
    LLCC68_SIZE_READ_REGISTER = 4,
    // Full size: this value plus buffer size
    LLCC68_SIZE_WRITE_BUFFER = 2,
    // Full size: this value plus buffer size
    LLCC68_SIZE_READ_BUFFER = 3,
    // DIO and IRQ Control Functions
    LLCC68_SIZE_SET_DIO_IRQ_PARAMS         = 9,
    LLCC68_SIZE_GET_IRQ_STATUS             = 2,
    LLCC68_SIZE_CLR_IRQ_STATUS             = 3,
    LLCC68_SIZE_SET_DIO2_AS_RF_SWITCH_CTRL = 2,
    LLCC68_SIZE_SET_DIO3_AS_TCXO_CTRL      = 5,
    // RF Modulation and Packet-Related Functions
    LLCC68_SIZE_SET_RF_FREQUENCY           = 5,
    LLCC68_SIZE_SET_PKT_TYPE               = 2,
    LLCC68_SIZE_GET_PKT_TYPE               = 2,
    LLCC68_SIZE_SET_TX_PARAMS              = 3,
    LLCC68_SIZE_SET_MODULATION_PARAMS_GFSK = 9,
    LLCC68_SIZE_SET_MODULATION_PARAMS_LORA = 5,
    LLCC68_SIZE_SET_PKT_PARAMS_GFSK        = 10,
    LLCC68_SIZE_SET_PKT_PARAMS_LORA        = 7,
    LLCC68_SIZE_SET_CAD_PARAMS             = 8,
    LLCC68_SIZE_SET_BUFFER_BASE_ADDRESS    = 3,
    LLCC68_SIZE_SET_LORA_SYMB_NUM_TIMEOUT  = 2,
    // Communication Status Information
    LLCC68_SIZE_GET_STATUS           = 1,
    LLCC68_SIZE_GET_RX_BUFFER_STATUS = 2,
    LLCC68_SIZE_GET_PKT_STATUS       = 2,
    LLCC68_SIZE_GET_RSSI_INST        = 2,
    LLCC68_SIZE_GET_STATS            = 2,
    LLCC68_SIZE_RESET_STATS          = 7,
    // Miscellaneous
    LLCC68_SIZE_GET_DEVICE_ERRORS = 2,
    LLCC68_SIZE_CLR_DEVICE_ERRORS = 3,
    LLCC68_SIZE_MAX_BUFFER        = 255,
    LLCC68_SIZE_DUMMY_BYTE        = 1,
} llcc68_commands_size_t; */



/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */







bool RYLR689_wait_while_busy(uint32_t timeout_ms)
{
	uint32_t t0 = HAL_GetTick();
	  while (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_0) == GPIO_PIN_SET) // PH0 BUSY
	  {
	    if ((HAL_GetTick() - t0) >= timeout_ms) return false;
	  }
	  return true;
}


 uint8_t GetStatusRYLR689(uint8_t* rx_val)
{
	uint8_t tx[2] = {
					0xC0,
					0x00
					};
	uint8_t rx[2] = {0};

    RYLR689_wait_while_busy(100); //make sure chip is ready for command
    /*
    tx[0] = 0xC0; 	//Get Status Command
	tx[1] = 0x00; 	//Receive Status Value
	tx[2] = 0x00; 	//Dummy
	tx[3] = 0x00;  //Dummy
	tx[4] = 0x00;  //Dummy

	   Clear SPI Receive Val
	  rx[0] = 0x00;
	  rx[1] = 0x00;
	  rx[2] = 0x00;
	  rx[3] = 0x00;
	  rx[4] = 0x00;
	  */

	  PIN_LOW(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);
	  for (volatile int i = 0; i < 200; i++) __NOP();

	  HAL_SPI_TransmitReceive(&hspi1, tx, rx, sizeof(tx), 100);

	  PIN_HIGH(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);

	  RYLR689_wait_while_busy(100);

	  *rx_val = rx[1];
	  return rx[1];
}


 uint8_t GetPacketTypeRYLR689(uint8_t* rx_val)
 {
 	uint8_t tx[3] = {
 					0x11, //get packet type opcode
 					0x00,
					0x00
 					};
 	uint8_t rx[3] = {0};

     RYLR689_wait_while_busy(100); //make sure chip is ready for command

     /*
     tx[0] = 0xC0; 	//Get Status Command
 	tx[1] = 0x00; 	//Receive Status Value
 	tx[2] = 0x00; 	//Dummy
 	tx[3] = 0x00;  //Dummy
 	tx[4] = 0x00;  //Dummy

 	   Clear SPI Receive Val
 	  rx[0] = 0x00;
 	  rx[1] = 0x00;
 	  rx[2] = 0x00;
 	  rx[3] = 0x00;
 	  rx[4] = 0x00;
 	  */

 	  PIN_LOW(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);
 	  __NOP(); //for (volatile int i = 0; i < 200; i++) __NOP();

 	  HAL_SPI_TransmitReceive(&hspi1, tx, rx, sizeof(tx), 100);

 	  PIN_HIGH(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);

 	  RYLR689_wait_while_busy(100);

 	  *rx_val = rx[0]; //opcode byte
 	  *(rx_val + 1) = rx[1]; //status byte
 	  *(rx_val + 2) = rx[2]; //packet byte

 	  return rx[2];
 }


 void SetPacketTypeRYLR689(uint8_t packet_type)
  {
  	uint8_t tx[2] = {
  					0x8A, //set packet type opcode
					packet_type//0x01  //packet type Lora=0x01 gfsk-0x00
  					};

      RYLR689_wait_while_busy(100); //make sure chip is ready for command


  	  PIN_LOW(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);
  	  __NOP(); //for (volatile int i = 0; i < 200; i++) __NOP();

  	  HAL_SPI_Transmit(&hspi1, tx, sizeof(tx), 100);

  	  PIN_HIGH(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);

  	  RYLR689_wait_while_busy(100);

  }


 void SetRfFrequencyRYLR689()
   {
   	uint8_t tx[5] = {
   					0x8A, //set frequency opcode
 					0x39, //0x01  //frequency 0x39300000 == 915MHz
					0x30,
					0x00,
					0x00
   					};

       RYLR689_wait_while_busy(100); //make sure chip is ready for command


   	  PIN_LOW(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);
   	  __NOP(); //for (volatile int i = 0; i < 200; i++) __NOP();

   	  HAL_SPI_Transmit(&hspi1, tx, sizeof(tx), 100);

   	  PIN_HIGH(SPI1_CS_RF_GPIO_Port, SPI1_CS_RF_Pin);

   	  RYLR689_wait_while_busy(100);

   }

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */



/* --- EOF ------------------------------------------------------------------ */
