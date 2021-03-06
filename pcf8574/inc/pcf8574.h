/*
 * pcf8574.h
 *
 *  Created on: Jun 5, 2022
 *      Author: gianfranco
 *
 *  Driver documentation:
 *  - https://github.com/gtalocchino/CESE_Protocolos_Comunicacion_Sistemas_Embebidos
 */

#ifndef PCF8574_INC_PCF8574_H_
#define PCF8574_INC_PCF8574_H_


/*!
 * @brief PCF8574 status enumeration
 */
typedef enum {
   PCF8574_OK,
   PCF8574_ERROR,
   PCF8574_BUSY
} pcf8574_status;

/*!
 * @brief PCF8574 pins enumeration
 */
typedef enum {
   PCF8574_PIN_0,
   PCF8574_PIN_1,
   PCF8574_PIN_2,
   PCF8574_PIN_3,
   PCF8574_PIN_4,
   PCF8574_PIN_5,
   PCF8574_PIN_6,
   PCF8574_PIN_7,

   PCF8574_PIN_COUNT
} pcf8574_pin;

/*!
 * @brief PCF8574 pin directions enumeration
 */
typedef enum {
   PCF8574_PIN_INPUT,
   PCF8574_PIN_OUTPUT
} pcf8574_pin_direction;

/*!
 * @brief PCF8574 pin status enumeration
 */
typedef enum {
   PCF8574_PIN_RESET,
   PCF8574_PIN_SET
} pcf8574_pin_state;

/*!
 * @brief PCF8574 configuration structure definition
 */
typedef struct {
   pcf8574_pin_state pin_states[PCF8574_PIN_COUNT];
   pcf8574_pin_direction pin_directions[PCF8574_PIN_COUNT];
} pcf8574_config;


/*!
 * @brief Initializes the controller and its internal state
 *
 * This function configures the pins, the I2C bus and the interrupts
 * required for operation.
 *
 * @param config PCF8574 configure structure.
 */
pcf8574_status PCF8574_init(pcf8574_config *config);

/*!
 * @brief Sets the state of a pin
 *
 * This function sets the state of a pin. The pin must be previously
 * configured as an output. Pins configured as input cannot be set.
 *
 * @param pin PCF8574 pin enumeration.
 * @param pin_state PCF8574 pin state enumeration.
 */
pcf8574_status PCF8574_pin_write(pcf8574_pin pin, pcf8574_pin_state pin_state);

/*!
 * @brief Returns the state of a pin.
 *
 * This function returns the state of a pin.
 *
 * @param pin PCF8574 pin enumeration.
 * @retval PCF8574 pin state enumeration.
 */
pcf8574_pin_state PCF8574_pin_read(pcf8574_pin pin);

/*!
 * @brief Reinits a pin.
 *
 * This function allows you to change the configuration for a pin
 * after initialization.
 *
 * @param pin PCF8574 pin enumeration.
 * @retval PCF8574 pin state enumeration.
 */
pcf8574_status PCF8574_pin_reinit(pcf8574_pin pin, pcf8574_pin_direction pin_direction,
                                  pcf8574_pin_state pin_state);

/*!
 * @brief Notifies the driver that there has been a change in the state of a
 * device pin
 *
 *	This function is for internal use and is responsible for notifying the driver
 *	that there has been a change of state in any pin of the device.
 *
 */
void _PCF8574_interrupt_callback(void);

/*!
 * @brief Notifies the driver that the I2C receive transfer has been completed.
 *
 *	This function is for internal use and is responsible for notifying the driver
 *	that the receive transfer is complete.
 *
 */
void _PCF8574_rx_transfer_completed_callback(void);

/*!
 * @brief Notifies the driver that the I2C send transfer has been completed.
 *
 *	This function is for internal use and is responsible for notifying the driver
 *	that the send transfer is complete.
 *
 */
void _PCF8574_tx_transfer_completed_callback(void);

#endif /* PCF8574_INC_PCF8574_H_ */
