#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "cJSON.h"
#include "esp_event.h"

#include "mqtt_client.h"
#include "protocol_examples_common.h"
#include "nvs_flash.h"
#include "sdkconfig.h"

//#include "aamqtt.h"
#include "StateMachine.h"
#include "Led.h"
#include "aamsg.h"

#define GET_IMPLDATA(_OBJ_) ((ImplData*)(_OBJ_.implData))

// Test ;
// GPIO 12 Red
// GPIO 13 Green 
// mqtt://192.168.100.10 

// main function -
// where the execution of program begins

unsigned char mac[6] = {0};
static char macString[25]; 
esp_mqtt_client_handle_t client = NULL; 
static const char *TAG = "AATEST003";
/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO1 CONFIG_BLINK_GPIO1 
#define BLINK_GPIO2 CONFIG_BLINK_GPIO2

// Implementation data structure
typedef struct ImplData {
    CHAR topic [100];
    INT sub_mgs_id;  
    BOOL subscribed; 
} ImplData;

// static uint8_t s_led_state_red = 0;
// static uint8_t s_led_state_green = 0;
// static AA_Response s_led_response_red = {}; 
// static AA_Response s_led_response_green = {}; 

// Define two public Led state machine instances
static ImplData iData1={
    .topic = {'\0'}, 
    .sub_mgs_id = 0, 
    .subscribed = false 
}; 
static Led ledObj1={
    .ledPin = CONFIG_BLINK_GPIO1, 
    .ledStatus = LED_UNCONFIGURED, 
    .aaResp = { .aaRespCode=0, 
                 .aaRespDesc[0]='\0'}, 
    .implData = &iData1
}; 
SM_DEFINE(ledRedSM, &ledObj1)

static ImplData iData2={
    .topic = {'\0'}, 
    .sub_mgs_id = 0, 
    .subscribed = false 
}; 
static Led ledObj2={
    .ledPin = CONFIG_BLINK_GPIO2, 
    .ledStatus = LED_UNCONFIGURED, 
    .aaResp = { .aaRespCode=0, 
                 .aaRespDesc={'\0'}},                  
    .implData = &iData2                 
}; 
SM_DEFINE(ledGreenSM, &ledObj2)
///////
void parsemessage(esp_mqtt_event_handle_t e)
{
    ESP_LOGI(TAG, "MSG=%d", e->msg_id);
    ESP_LOGI(TAG, "TOPIC='%.*s'", e->topic_len, e->topic);
    ESP_LOGI(TAG, "DATA=%.*s", e->data_len, e->data);

    if (strncmp(e->topic, GET_IMPLDATA(ledObj1)->topic, e->topic_len) == 0) {
        /* Toggle the LED state */
        SM_Event(ledRedSM, LED_Toggle, NULL); 
        ESP_LOGI(TAG, "Turning the Red LED %s!", aaResponseMessage(SM_Get(ledRedSM, LED_GetResponse)));
    } else if (strncmp(e->topic, GET_IMPLDATA(ledObj2)->topic, e->topic_len) == 0) {
        /* Toggle the LED state */
        SM_Event(ledGreenSM, LED_Toggle, NULL); 
        ESP_LOGI(TAG, "Turning the Green LED %s!", aaResponseMessage(SM_Get(ledGreenSM, LED_GetResponse))); 
    }
    return; 
}
/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    char message[100]; 
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id=0;
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_publish(client, "/AA/REGISTER", aaRegisterMessage(macString), 0, 1, 0); 
        ESP_LOGI(TAG, "sent publish successful //register, msg_id=%d", msg_id);

        // Subscribe to Red LED
        //msg_id = esp_mqtt_client_subscribe(client, "/AA/R1/C1/L1", 0);    strcpy(GET_IMPLDATA(ledObj1)->topic, "/AA/R1/C1/L1");
        msg_id = esp_mqtt_client_subscribe(client, GET_IMPLDATA(ledObj1)->topic, 0);   
        GET_IMPLDATA(ledObj1)->sub_mgs_id = msg_id; 
        ESP_LOGI(TAG, "sent subscribe successful %s, msg_id=%d", GET_IMPLDATA(ledObj1)->topic, msg_id);
        // Subscribe to Green LED
        //msg_id = esp_mqtt_client_subscribe(client, "/AA/R1/C1/L2", 0);
        msg_id = esp_mqtt_client_subscribe(client, GET_IMPLDATA(ledObj2)->topic, 0);   
        GET_IMPLDATA(ledObj2)->sub_mgs_id = msg_id; 
        ESP_LOGI(TAG, "sent subscribe successful %s, msg_id=%d", GET_IMPLDATA(ledObj2)->topic, msg_id);
        //ESP_LOGI(TAG, "sent subscribe successful /AA/R1/C1/L2, msg_id=%d", msg_id);

        //msg_id = esp_mqtt_client_unsubscribe(client, "/AA/R1/C1/L2");
        //ESP_LOGI(TAG, "sent unsubscribe successful //aaiot1, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        // Note: Topic is not set in event for MQTT_EVENT_SUBSCRIBED!
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        if (GET_IMPLDATA(ledObj1)->sub_mgs_id == event->msg_id) {
            ESP_LOGI(TAG, "Subscribe Successful, topic '%s', msg_id=%d", GET_IMPLDATA(ledObj1)->topic, event->msg_id);
        }
        if (GET_IMPLDATA(ledObj2)->sub_mgs_id == event->msg_id) {
            ESP_LOGI(TAG, "Subscribe Successful, topic '%s', msg_id=%d", GET_IMPLDATA(ledObj2)->topic, event->msg_id);
        }
        sprintf(message, "Subscribed successful, msg_id=%d", event->msg_id); 
        msg_id = esp_mqtt_client_publish(client, "/AA/REGISTER", message, 0, 0, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        parsemessage(event);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
        }
        break;
    case MQTT_EVENT_BEFORE_CONNECT:
        ESP_LOGI(TAG, "MQTT_EVENT_BEFORE_CONNECT, msg_id=%d", event->msg_id);
        break;
        
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = CONFIG_BROKER_URL,
    };
    //esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    ESP_LOGI(TAG, "After init %s", mqtt_cfg.uri);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    ESP_LOGI(TAG, "After Register");
    esp_mqtt_client_start(client);
    ESP_LOGI(TAG, "After started");
}

void app_main(void)
{
    // char* msg; 
    //int msg_id;

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("LED", ESP_LOG_WARN);   

    esp_efuse_mac_get_default(mac);
    sprintf(macString, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    ESP_LOGI(TAG, "Base Mac: %s", macString);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    //strcpy(((ImplData*)(ledObj1.implData))->topic, "/AA/R1/C1/L1");
    strcpy(GET_IMPLDATA(ledObj1)->topic, "/AA/R1/C1/L1");
    strcpy(GET_IMPLDATA(ledObj2)->topic, "/AA/R1/C1/L2");

    mqtt_app_start();

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

    /* Toggle the LED state */
    SM_Event(ledRedSM, LED_SetOn, NULL); 
    ESP_LOGI(TAG, "Turning the Red LED %s!", aaResponseMessage(SM_Get(ledRedSM, LED_GetResponse)));
    /* Toggle the LED state */
    SM_Event(ledGreenSM, LED_SetOn, NULL); 
    ESP_LOGI(TAG, "Turning the Green LED %s!", aaResponseMessage(SM_Get(ledGreenSM, LED_GetResponse)));

    while (1) {
        // /* Toggle the LED state */
        // SM_Event(ledRedSM, LED_Toggle, NULL); 
        // ESP_LOGI(TAG, "Turning the Red LED %s!", aaResponseMessage(SM_Get(ledRedSM, LED_GetResponse)));
        // vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);

        // /* Toggle the LED state */
        // SM_Event(ledGreenSM, LED_Toggle, NULL); 
        // ESP_LOGI(TAG, "Turning the Green LED %s!", aaResponseMessage(SM_Get(ledGreenSM, LED_GetResponse)));
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
