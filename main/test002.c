#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "cJSON.h"
//#include "led_strip.h"
#include "sdkconfig.h"
#include "StateMachine.h"
#include "Led.h"
#include "aamsg.h"
// main function -
// where the execution of program begins

static const char *TAG = "AATEST002";
/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO1 CONFIG_BLINK_GPIO1 
#define BLINK_GPIO2 CONFIG_BLINK_GPIO2

static uint8_t s_led_state_red = 0;
static uint8_t s_led_state_green = 0;
static AA_Response s_led_response_red = {}; 
static AA_Response s_led_response_green = {}; 

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
    char* msg; 

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("LED", ESP_LOG_WARN);   

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
        /* Toggle the LED state */
        SM_Event(ledRedSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledRedSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledRedSM, LED_Toggle, NULL); 
        //s_led_state_red = SM_Get(ledRedSM, LED_GetStatus); 
        //ESP_LOGI(TAG, "Turning the Red LED %s!", s_led_state_red == LED_ON ? "ON" : "OFF");
        //s_led_response_red = SM_Get(ledRedSM, LED_GetResponse); 
        //msg = getResponseMessage(s_led_response_red); 
        //ESP_LOGI(TAG, "Turning the Red LED %s!", msg);
        ESP_LOGI(TAG, "Turning the Red LED %s!", jsonResponseMessage(SM_Get(ledRedSM, LED_GetResponse)));
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);

        /* Toggle the LED state */
        SM_Event(ledGreenSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledGreenSM, LED_Toggle, NULL); 
        vTaskDelay(100 / portTICK_PERIOD_MS);
        SM_Event(ledGreenSM, LED_Toggle, NULL); 
        //s_led_state_green = SM_Get(ledGreenSM, LED_GetStatus); 
        //ESP_LOGI(TAG, "Turning the Green LED %s!", s_led_state_green == LED_ON ? "ON" : "OFF");
        //s_led_response_green = SM_Get(ledGreenSM, LED_GetResponse); 
        //msg = getResponseMessage(s_led_response_green); 
        //ESP_LOGI(TAG, "Turning the Green LED %s!", msg);
        ESP_LOGI(TAG, "Turning the Green LED %s!", jsonResponseMessage(SM_Get(ledGreenSM, LED_GetResponse)));
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
