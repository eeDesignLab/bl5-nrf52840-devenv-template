/**
 * @file extrn_led_driver.c
 *
 * @brief External LEDs driver implementation file.
 */

#include "nrf_gpio.h"
#include "app_timer.h"
#include "extrn_led_driver.h"


#define EXT_LED1_PIN 			NRF_GPIO_PIN_MAP(1,10)
#define EXT_LED2_PIN 			NRF_GPIO_PIN_MAP(1,11)
#define NUMB_OF_LEDS			2U
#define BLINK_PERIOD_SEC		300U
#define EMPTY					0xFFU

APP_TIMER_DEF(blink_timer_id);

/* Buffer for store LEDs in the blink status */
static uint8_t blink_buff[NUMB_OF_LEDS];
/* Number of LEDs inside the link buffer */
static uint8_t leds_into_buff = 0;
/* Buffer for save the status of the LEDs */
static extrn_LED_status_t status_buff[NUMB_OF_LEDS];

/* Private functions */
static uint32_t extrn_LED_pin_get(extrn_LED_id_t led_id);
static void extrn_LED_toggle(extrn_LED_id_t led_id);
static void blink_buff_init(void);
static void blink_disable(extrn_LED_id_t led_id);
static void blink_enable(extrn_LED_id_t led_id);
static void blink_timeout_handler(void * p_context);


/*	Public Functions */

void extrn_LED_init(void)
{

	/* Configure GPIOs used by LEDs as outputs */
	nrf_gpio_cfg_output(EXT_LED1_PIN);
	nrf_gpio_cfg_output(EXT_LED2_PIN);

	blink_buff_init();

	/* Timer for blinking LEDs */
	app_timer_create(&blink_timer_id,
			APP_TIMER_MODE_REPEATED, blink_timeout_handler);
}

void extrn_LED_set(extrn_LED_t * p_led)
{
	/* Check LED ID validity */
	if ((p_led->led_id < 0) || (p_led->led_id > (NUMB_OF_LEDS - 1)))
	{
		return;
	}

	if (leds_into_buff && (p_led->led_status != LED_BLINK))
	{
		/* If this LED is blinking, stop it and remove it from the blink buffer */
		blink_disable(p_led->led_id);
	}

	switch (p_led->led_status)
	{

	case LED_ON:
	{
		nrf_gpio_pin_write(extrn_LED_pin_get(p_led->led_id), 1);
		break;
	}

	case LED_OFF:
	{
		nrf_gpio_pin_write(extrn_LED_pin_get(p_led->led_id), 0);
		break;
	}

	case LED_TOGGLE:
	{
		extrn_LED_toggle(extrn_LED_pin_get(p_led->led_id));
		break;
	}

	case LED_BLINK:
	{
		blink_enable(p_led->led_id);
		break;
	}

	default:
	{
		p_led->led_status = UNKNOWN;
		break;
	}

	}

	/* Save the new LED status */
	status_buff[p_led->led_id] = p_led->led_status;
}

extrn_LED_status_t extrn_LED_get(extrn_LED_id_t led_id)
{
	/* Check LED ID validity */
	if ((led_id < 0) || (led_id > (NUMB_OF_LEDS - 1)))
	{
		return UNKNOWN;
	}
	return status_buff[led_id];
}

/*	Private Functions */

/**
 * @brief  Get the pin number assigned to a specific LED.
 *
 * @param  LED ID.
 *
 * @return The pin number.
 */
static uint32_t extrn_LED_pin_get(extrn_LED_id_t led_id)
{
	uint32_t led_pin = 255;

	switch (led_id)
	{

	case LED1:
	{
		led_pin = EXT_LED1_PIN;
		break;
	}

	case LED2:
	{
		led_pin = EXT_LED2_PIN;
		break;
	}

	default:
		break;

	}

	return led_pin;
}

/**
 * @brief  Toggle a specific LED.
 *
 * @param  LED ID.
 *
 */
static void extrn_LED_toggle(extrn_LED_id_t led_id)
{
	nrf_gpio_pin_toggle(led_id);
}

/**
 * @brief  Initialize the buffer that stores LEDs in the blinking status.
 *
 */
void blink_buff_init(void)
{
	for (int i = 0; i < NUMB_OF_LEDS; ++i)
	{
		blink_buff[i] = EMPTY;
	}
}

/**
 * @brief  Remove a LED from the blink buffer. Stops the blink
 *         timer if the buffer is empty.
 *
 * @param  LED ID.
 *
 */
static void blink_disable(extrn_LED_id_t led_id)
{
	for (int i = 0; i < NUMB_OF_LEDS; ++i)
	{
		if (blink_buff[i] == led_id)
		{
			blink_buff[i] = EMPTY;
			--leds_into_buff;
			if (!leds_into_buff)
			{
				app_timer_stop(blink_timer_id);
			}
			nrf_gpio_pin_write(extrn_LED_pin_get(blink_buff[i]), 0);
			break;
		}
	}
}

/**
 * @brief  Start blinking a LED.
 *
 * @param  LED ID.
 */
static void blink_enable(extrn_LED_id_t led_id)
{
	for (int i = 0; i < NUMB_OF_LEDS; ++i)
	{
		if (blink_buff[i] == EMPTY)
		{
			blink_buff[i] = led_id;

			if (!leds_into_buff)
			{
				app_timer_start(blink_timer_id,
						APP_TIMER_TICKS(BLINK_PERIOD_SEC), NULL);
			}
			++leds_into_buff;
			break;
		}
	}
}

/**
 * @brief  Handler for timeout interrupt.
 *
 */
static void blink_timeout_handler(void * p_context)
{
	for (int i = 0; i < NUMB_OF_LEDS; ++i)
	{
		if (blink_buff[i] != EMPTY)
		{
			extrn_LED_toggle(extrn_LED_pin_get(blink_buff[i]));
		}
	}
}
