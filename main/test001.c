#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
//#include "led_strip.h"
#include "sdkconfig.h"
#include "StateMachine.h"
#include "Led.h"
// main function -
// where the execution of program begins

static const char *TAG = "Blink02";
/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO1 CONFIG_BLINK_GPIO1 
#define BLINK_GPIO2 CONFIG_BLINK_GPIO2

static uint8_t s_led_state1 = 0;
static uint8_t s_led_state2 = 0;

// Define two public Led state machine instances
static Led ledObj1={
    .ledPin = CONFIG_BLINK_GPIO1, 
    .ledStatus = LED_UNCONFIGURED, 
    .aaResp = { .aaRespCode=0, 
                 .aaRespDesc[0]='\0'}
                 
}; 
SM_DEFINE(ledRedSM, &ledObj1)

static Led ledObj2={
    .ledPin = CONFIG_BLINK_GPIO2, 
    .ledStatus = LED_UNCONFIGURED, 
    .aaResp = { .aaRespCode=0, 
                 .aaRespDesc={'\0'}}                 
}; 
SM_DEFINE(ledGreenSM, &ledObj2)

void app_main(void)
{
    LedEventData* lData;
    /* Configure the peripheral according to the LED type */
    // Configure State Machines for each LED 
    // ** Red ** 
    ESP_LOGI(TAG, "Start %s", "Red" );
    lData = SM_XAlloc(sizeof(LedEventData));
    sprintf(lData->ledAction, "Some Action: %s ...", "Red");
    ESP_LOGI(TAG, "Test LED_Configure: %s ...", "Red" );
    SM_Event(ledRedSM, LED_Configure, lData);
    // ** Green ** 
    ESP_LOGI(TAG, "Start %s", "Green" );
    lData = SM_XAlloc(sizeof(LedEventData));
    sprintf(lData->ledAction, "Some Action: %s ...", "Green");
    ESP_LOGI(TAG, "Test LED_Configure: %s ...", "Green" );
    SM_Event(ledGreenSM, LED_Configure, lData);

    while (1) {
        ESP_LOGI(TAG, "Turning the Red LED %s!", s_led_state1 == true ? "ON" : "OFF");
        /* Toggle the LED state */
        SM_Event(ledRedSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledRedSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledRedSM, LED_Toggle, NULL); 
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "Turning the Green LED %s!", s_led_state2 == true ? "ON" : "OFF");
        /* Toggle the LED state */
        SM_Event(ledGreenSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledGreenSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledGreenSM, LED_Toggle, NULL); 
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
