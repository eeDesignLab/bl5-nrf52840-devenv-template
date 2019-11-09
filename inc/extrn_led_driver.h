/**
 * @file extrn_led_driver.h
 *
 * @brief External LEDs driver interface file.
 */

#ifndef INC_EXTERN_LED_DRIVER_H_
#define INC_EXTERN_LED_DRIVER_H_

/* Identify the external LEDs of the system */
typedef enum
{
	LED1,
	LED2,
}extrn_LED_id_t;

/* Identify the possible status of external LEDs */
typedef enum
{
	LED_ON,
	LED_OFF,
	LED_BLINK,
	LED_TOGGLE,
	UNKNOWN,
}extrn_LED_status_t;

/* Representation of an external LED */
typedef struct
{
	extrn_LED_id_t     led_id;
	extrn_LED_status_t led_status;
}extrn_LED_t;

/**
 * @brief Initialize the driver for external LEDs.
 */
void extrn_LED_init(void);

/**
 * @brief Set the status of a specific external LED.
 *
 * @param   Pointer to the structure that represents the external LED.
 */
void extrn_LED_set(extrn_LED_t * p_led);

/**
 * @brief  Get the status of a specific external LED.
 *
 * @param  The LED ID.
 *
 * @return The current LED status.
 */
extrn_LED_status_t extrn_LED_get(extrn_LED_id_t led_id);

#endif /* INC_EXTERN_LED_DRIVER_H_ */
