/**@file stima.ino */

/*********************************************************************
Copyright (C) 2017  Marco Baldinetti <m.baldinetti@digiteco.it>
authors:
Paolo Patruno <p.patruno@iperbole.bologna.it>
Marco Baldinetti <m.baldinetti@digiteco.it>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#ifdef ARDUINO_ARCH_AVR
  #include <Arduino_FreeRTOS.h>
  #define WORD 1
#else
  #ifdef ARDUINO_ARCH_STM32
    #include "STM32FreeRTOS.h"
    #define WORD 4
  #else
    #include "FreeRTOS.h"
    #define WORD 4
  #endif
#endif

#include "stima.h"

/*
// Dimensions the buffer that the task being created will use as its stack.
//   NOTE:  This is the number of words the stack will hold, not the number of
//   bytes.  For example, if each stack item is 32-bits, and this is set to 100,
//   then 400 bytes (100 * 32-bits) will be allocated.
#define STACK_SIZE_RTC 150

// Structure that will hold the TCB of the task being created.
StaticTask_t xTaskBufferRtc;

// Buffer that the task being created will use as its stack.  Note this is
//   an array of StackType_t variables.  The size of StackType_t is dependent on
//   the RTOS port.
StackType_t xStackRtc[ STACK_SIZE_RTC ];
TaskHandle_t xHandleRtc;
*/

#define STACK_SIZE_SUPERVISOR 2000/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
StaticTask_t xTaskBufferSupervisor;
StackType_t xStackSupervisor[ STACK_SIZE_SUPERVISOR ];
#endif
TaskHandle_t xHandleSupervisor;

#if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
  #define STACK_SIZE_ETHERNET 200/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
  StaticTask_t xTaskBufferEthernet;
  StackType_t xStackEthernet[ STACK_SIZE_ETHERNET ];
#endif
  TaskHandle_t xHandleEthernet;
#elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
  #define STACK_SIZE_GSM 2600/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
  StaticTask_t xTaskBufferGsm;
  StackType_t xStackGsm[ STACK_SIZE_GSM ];
#endif
  TaskHandle_t xHandleGsm;
#endif

#define STACK_SIZE_SENSORREADING 2000/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
StaticTask_t xTaskBufferSensorReading;
StackType_t xStackSensorReading[ STACK_SIZE_SENSORREADING ];
#endif
TaskHandle_t xHandleSensorReading;

#if (USE_SDCARD)
#define STACK_SIZE_DATASAVING 2000/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
StaticTask_t xTaskBufferDataSaving;
StackType_t xStackDataSaving[ STACK_SIZE_DATASAVING ];
#endif
TaskHandle_t xHandleDataSaving;
#endif

#if (USE_MQTT)
#define STACK_SIZE_MQTT 2500/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
StaticTask_t xTaskBufferMqtt;
StackType_t xStackMqtt[ STACK_SIZE_MQTT ];
#endif
TaskHandle_t xHandleMqtt;
#endif

#define STACK_SIZE_TIME 1700/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
StaticTask_t xTaskBufferTime;
StackType_t xStackTime[ STACK_SIZE_TIME ];
#endif
TaskHandle_t xHandleTime;

/*
#define STACK_SIZE_RPC 300/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
StaticTask_t xTaskBufferRpc;
StackType_t xStackRpc[ STACK_SIZE_RPC ];
#endif
TaskHandle_t xHandleRpc;
*/

#define STACK_SIZE_HEARTHBEAT 2150/WORD
#if (configSUPPORT_STATIC_ALLOCATION == 1)
StaticTask_t xTaskBufferHearthBeat;
StackType_t xStackHearthBeat[ STACK_SIZE_HEARTHBEAT ];
#endif
TaskHandle_t xHandleHearthBeat;

/*
// this compute the the difference fron heap and stack
// ehwn heap and stack overload an crash happen
int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
*/

/*
void taskRtc( void * parameter )
{
  while(true){
    //LOGN(F("rtc_task start"));
    rtc_task();
    //LOGN(F("rtc_task end"));
    taskYIELD();
  }
}
*/

void taskSupervisor( void * parameter )
{
  while(true){
    //LOGN(F("supervisor_task start"));
    supervisor_task();
    //LOGN(F("supervisor_task end"));
    taskYIELD();
  }
}

#if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)

  void taskEthernet( void * parameter )
  {
    while(true){
      //LOGN(F("ethernet_task start"));
      ethernet_task();
      //LOGN(F("ethernet_task end"));
      taskYIELD();
    }
  }

#elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)

  void taskGsm( void * parameter )
  {
    while(true){
      //LOGN(F("gsm_task start"));
      gsm_task();
      //LOGN(F("gsm_task stop"));
      taskYIELD();
    }
  }
#endif

void taskSensorReading( void * parameter )
{
  while(true){
    //LOGN(F("sensorreading_task start"));
    sensors_reading_task();
    //LOGN(F("sensorreading_task stop"));
    taskYIELD();
  }
}

#if (USE_SDCARD)
void taskDataSaving( void * parameter )
{
  while(true){
    //LOGN(F("data_saving_task start"));
    data_saving_task();
    //LOGN(F("data_saving_task stop"));
    taskYIELD();
  }
}
#endif

#if (USE_MQTT)
void taskMqtt( void * parameter )
{
  while(true){
    //LOGN(F("mqtt_task start"));
    mqtt_task();
    //LOGN(F("mqtt_task stop"));
    taskYIELD();
  }
}
#endif

void taskTime( void * parameter )
{
  while(true){
    //LOGN(F("time_task start"));
    time_task();
    //LOGN(F("time_task stop"));
    taskYIELD();
  }
}

/*
void taskRpc( void * parameter = NULL )
{
  while(true){

    streamRpc.parseStream(&is_event_rpc, &Serial);
    if (is_event_rpc) {
    }
    taskYIELD();
  }
}
*/

void taskHearthBeat( void * parameter )
{
  // those initializations are here for:
  //https://community.st.com/s/question/0D50X00009XkYFaSAN/freertos-stm32-tick
  // find a better place !
  ////
  init_pins();
  init_wire();
  init_rpc();
  init_tasks();
  init_logging();
  load_configuration();
  ////init_buffers();
  init_spi();
  #if (USE_RTC)
  init_rtc();
  #elif (USE_TIMER_1)
  init_timer1();
  #endif
  init_system();
  init_sensors();
  ////
  
  while(true){
    LOGN(F("--> beat"));
    //LOGN(F("Rtc:          %d"),uxTaskGetStackHighWaterMark( xHandleRtc));
    LOGN(F("Supervisor:   %d"),uxTaskGetStackHighWaterMark( xHandleSupervisor ));
    #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
      LOGN(F("Ethernet:     %d"),uxTaskGetStackHighWaterMark( xHandleEthernet ));
    #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
      LOGN(F("Gsm:          %d"),uxTaskGetStackHighWaterMark( xHandleGsm ));
    #endif
    LOGN(F("SensorReading:%d"),uxTaskGetStackHighWaterMark( xHandleSensorReading ));
    #if (USE_SDCARD)
      LOGN(F("DataSaving:   %d"),uxTaskGetStackHighWaterMark( xHandleDataSaving ));
    #endif
    #if (USE_MQTT)
      LOGN(F("Mqtt:         %d"),uxTaskGetStackHighWaterMark( xHandleMqtt ));
    #endif
    LOGN(F("Time:         %d"),uxTaskGetStackHighWaterMark( xHandleTime ));
    LOGN(F("HearthBeat:   %d"),uxTaskGetStackHighWaterMark( xHandleHearthBeat ));
    Serial.flush();

    // I2C Bus Check
    if (i2c_error >= I2C_MAX_ERROR_COUNT) {
      LOGE(F("Restart I2C BUS"));
      init_wire();
    }

    if (is_time_set) {

    #if (MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM)
      if (is_time_for_sensors_reading_updated) {
	is_time_for_sensors_reading_updated = false;
	LOGN(F("Next acquisition scheduled at: %02u:%02u:%02u"), hour(next_ptr_time_for_sensors_reading), minute(next_ptr_time_for_sensors_reading), second(next_ptr_time_for_sensors_reading));
      }
    #endif
    }

    streamRpc.parseStream(&is_event_rpc, &Serial);

    vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}

/*
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName ){
  LOGE(F("OUT OF STACK %s"),pcTaskName);
}
*/

/*!
\fn void setup()
\brief Arduino setup function. Init watchdog, hardware, debug, buffer and load configuration stored in EEPROM.
\return void.
*/
void setup() {
   Serial.begin(115200);
   Serial.println("Starting up");
   /*
   xHandleRtc = xTaskCreateStatic(
				  taskRtc,           // Task function.
				  "Rtc",             // String with name of task.
				  STACK_SIZE_RTC,    // Stack size in words.
				  NULL,              // Parameter passed as input of the task.
				  1,                 // Priority of the task.
				  xStackRtc,         // Array to use as the task's stack.
				  &xTaskBufferRtc ); // Variable to hold the task's data structure.

   //xTaskCreate(taskRtc,"Rtc", STACK_SIZE_RTC, (void *) 1,  1, &xHandleRtc);
   vTaskSuspend( xHandleRtc);
   */

#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleSupervisor = xTaskCreateStatic(taskSupervisor,"Superv",
   					 STACK_SIZE_SUPERVISOR, NULL, 1, xStackSupervisor, &xTaskBufferSupervisor );
#else
   xTaskCreate(taskSupervisor,"Superv", STACK_SIZE_SUPERVISOR, (void *) 1,  1, &xHandleSupervisor);
#endif
   //vTaskSuspend( xHandleSupervisor);

   #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleEthernet = xTaskCreateStatic(taskEthernet, "Ether",
				       STACK_SIZE_ETHERNET, NULL, 1, xStackEthernet, &xTaskBufferEthernet );
#else
   xTaskCreate(taskEthernet,"Ether", STACK_SIZE_ETHERNET, (void *) 1,  1, &xHandleEthernet);
#endif
   vTaskSuspend( xHandleEthernet);
   #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleGsm = xTaskCreateStatic(taskGsm, "Gsm",
				  STACK_SIZE_GSM, NULL, 1, xStackGsm, &xTaskBufferGsm );
#else
   xTaskCreate(taskGsm,"Gsm", STACK_SIZE_GSM, (void *) 1,  1, &xHandleGsm);
#endif
   vTaskSuspend( xHandleGsm);
   #endif

#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleSensorReading = xTaskCreateStatic(taskSensorReading, "Sensor",
					    STACK_SIZE_SENSORREADING, NULL, 2, xStackSensorReading, &xTaskBufferSensorReading );
#else
   xTaskCreate(taskSensorReading,"Sensor", STACK_SIZE_SENSORREADING, (void *) 1,  1, &xHandleSensorReading);
#endif
   vTaskSuspend( xHandleSensorReading);

#if (USE_SDCARD)
#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleDataSaving = xTaskCreateStatic(taskDataSaving, "Saving",
					 STACK_SIZE_DATASAVING, NULL, 2, xStackDataSaving, &xTaskBufferDataSaving );
#else
   xTaskCreate(taskDataSaving,"Saving", STACK_SIZE_DATASAVING, (void *) 1,  1, &xHandleDataSaving);
#endif
   vTaskSuspend( xHandleDataSaving);
#endif

   #if (USE_MQTT)
#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleMqtt = xTaskCreateStatic(taskMqtt, "Mqtt",
				   STACK_SIZE_MQTT, NULL, 1, xStackMqtt, &xTaskBufferMqtt );
#else
   xTaskCreate(taskMqtt,"Mqtt", STACK_SIZE_MQTT, (void *) 1,  1, &xHandleMqtt);
#endif
   vTaskSuspend( xHandleMqtt);
   #endif

#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleTime = xTaskCreateStatic(taskTime, "Time",
				   STACK_SIZE_TIME, NULL, 1, xStackTime, &xTaskBufferTime );
#else
   xTaskCreate(taskTime,"time", STACK_SIZE_TIME, (void *) 1,  1, &xHandleTime);
#endif
   vTaskSuspend( xHandleTime);

   /*
   xHandleRpc = xTaskCreateStatic(taskRpc, "Rpc",
				  STACK_SIZE_RPC, NULL, 1, xStackRpc, &xTaskBufferRpc );
   //vTaskSuspend( xHandleRpc);
   */

#if (configSUPPORT_STATIC_ALLOCATION == 1)
   xHandleHearthBeat = xTaskCreateStatic(taskHearthBeat, "Beat",
					 STACK_SIZE_HEARTHBEAT, NULL, 1, xStackHearthBeat, &xTaskBufferHearthBeat );
#else
   xTaskCreate(taskHearthBeat,"Beat", STACK_SIZE_HEARTHBEAT, (void *) 1,  1, &xHandleHearthBeat);
#endif

  // The scheduler was started in initVariant() found in variantHooks.c but in RMAP was moved here
  vTaskStartScheduler(); // initialise and run the freeRTOS scheduler. Execution should never return here.

}

/*!
\fn void loop()
\brief Arduino loop function. First, initialize tasks and sensors, then execute the tasks and activates the power down if no task is running.
\return void.
*/
void loop() {
  // Empty. Things are done in Tasks.

  #if (ENABLE_SDCARD_LOGGING)   
  logFile.flush();
  #endif
  Serial.flush();
  
  #if (USE_POWER_DOWN)
  init_power_down();
  #endif
}


void logPrefix(Print* _logOutput) {
  char dt[DATE_TIME_STRING_LENGTH];
  snprintf(dt, DATE_TIME_STRING_LENGTH, "%04u-%02u-%02uT%02u:%02u:%02u", year(), month(), day(), hour(), minute(), second());  
  _logOutput->print("#");
  _logOutput->print(dt);
  _logOutput->print(" ");
}

void logSuffix(Print* _logOutput) {
  _logOutput->print('\n');
  //_logOutput->flush();  // we use this to flush every log message
}


void init_logging(){
   #if (ENABLE_SDCARD_LOGGING)      
   if (sdcard_init(&SD, SDCARD_CHIP_SELECT_PIN)) {
     LOGN(F("sdcard opened"));
     is_sdcard_open = true;
   }

   if (is_sdcard_open && sdcard_open_file(&SD, &logFile, SDCARD_LOGGING_FILE_NAME, O_RDWR | O_CREAT | O_APPEND)) {
     logFile.seekEnd(0);
     Log.begin(LOG_LEVEL, &loggingStream);
   } else {
     Log.begin(LOG_LEVEL, &Serial);
   }
   #else
     Log.begin(LOG_LEVEL, &Serial);
   #endif

   Log.setPrefix(logPrefix); // Uncomment to get timestamps as prefix
   Log.setSuffix(logSuffix); // Uncomment to get newline as suffix
}



void init_power_down(void) {

  //LOGN(F("sleep"));
    Serial.flush();

    power_adc_disable();
    power_spi_disable();
    power_timer0_disable();
    #if (USE_TIMER_1 == false)
    power_timer1_disable();
    #endif
    power_timer2_disable();

		noInterrupts ();
		sleep_enable();

		interrupts ();

		sleep_cpu();
		sleep_disable();

		power_adc_enable();
    power_spi_enable();
    power_timer0_enable();
    #if (USE_TIMER_1 == false)
    power_timer1_enable();
    #endif
    power_timer2_enable();
    //LOGN(F("wakeup"));
}

/*
void init_buffers() {
}
*/

void init_tasks() {

   is_event_supervisor = true;
   supervisor_state = SUPERVISOR_INIT;

   is_event_rpc = true;

   is_event_time = false;
   time_state = TIME_INIT;

   is_event_sensors_reading = false;
   is_event_sensors_reading_rpc = false;
   sensors_reading_state = SENSORS_READING_INIT;

   #if (USE_SDCARD)
   is_event_data_saving = false;
   data_saving_state = DATA_SAVING_INIT;
   is_sdcard_error = false;
   is_sdcard_open = false;
   #endif

   #if (USE_MQTT)
   is_event_mqtt = false;
   is_event_mqtt_paused = false;
   mqtt_state = MQTT_INIT;
   is_mqtt_subscribed = false;
   #endif

   #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
   is_event_ethernet = false;
   ethernet_state = ETHERNET_INIT;

   #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
   is_event_gsm = false;
   gsm_state = GSM_INIT;

   #endif

   rpc_state = RPC_INIT;

   is_client_connected = false;
   is_client_udp_socket_open = false;

   do_ntp_sync = false;
   is_time_set = false;
   system_time = 0;
   last_ntp_sync = -NTP_TIME_FOR_RESYNC_S;

   is_time_for_sensors_reading_updated = false;
}

void init_pins() {
   pinMode(CONFIGURATION_RESET_PIN, INPUT_PULLUP);

   pinMode(RTC_INTERRUPT_PIN, INPUT_PULLUP);

   #if (USE_SDCARD)
   pinMode(SDCARD_CHIP_SELECT_PIN, OUTPUT);
   digitalWrite(SDCARD_CHIP_SELECT_PIN, HIGH);
   #endif

   #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
   Ethernet.w5500_cspin = W5500_CHIP_SELECT_PIN;

   #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
   s800.init(GSM_ON_OFF_PIN);

   #endif
}

void init_wire() {
   // uint8_t i2c_bus_state = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()
   //
   // if (i2c_bus_state) {
   //    LOGE(F("I2C bus error: Could not clear!!!"));
   //    while(1);
   // }
   //
   // switch (i2c_bus_state) {
   //    case 1:
   //       LOGE(F("SCL clock line held low"));
   //    break;
   //
   //    case 2:
   //       LOGE(F("SCL clock line held low by slave clock stretch"));
   //    break;
   //
   //    case 3:
   //       LOGE(F("SDA data line held low"));
   //    break;
   // }

   i2c_error = 0;
#ifdef ARDUINO_ARCH_AVR
   Wire.end();
#endif
   Wire.begin();
   Wire.setClock(I2C_BUS_CLOCK);
}

void init_spi() {
   SPI.begin();
}

void init_rtc() {
   Pcf8563::disableAlarm();
   Pcf8563::disableTimer();
   Pcf8563::disableClockout();
   Pcf8563::setClockoutFrequency(RTC_FREQUENCY);
   Pcf8563::enableClockout();
   attachInterrupt(digitalPinToInterrupt(RTC_INTERRUPT_PIN), rtc_interrupt_handler, RISING);
}

void init_system() {
   #if (USE_POWER_DOWN)
   #if (USE_RTC)
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);
   #elif (USE_TIMER_1)
   set_sleep_mode(SLEEP_MODE_IDLE);
   #endif
   #endif

   // main loop state
   state = INIT;
}

void init_rpc() {
   #if (USE_RPC_METHOD_CONFIGURE)
   streamRpc.registerMethod("configure", &configure);
   #endif

   #if (USE_RPC_METHOD_PREPARE)
   streamRpc.registerMethod("prepare", &prepare);
   #endif

   #if (USE_RPC_METHOD_GETJSON)
   streamRpc.registerMethod("getjson", &getjson);
   #endif

   #if (USE_RPC_METHOD_PREPANDGET)
   streamRpc.registerMethod("prepandget", &prepandget);
   #endif

   #if (USE_RPC_METHOD_REBOOT)
   streamRpc.registerMethod("reboot", &reboot);
   #endif
}

void init_wdt(uint8_t wdt_timer) {
   wdt_disable();
   wdt_reset();
   wdt_enable(wdt_timer);
}

#if (USE_TIMER_1)
void init_timer1() {
   start_timer();
}

void start_timer() {
   TCCR1A = 0x00;                //!< Normal timer operation
   TCCR1B = 0x05;                //!< 1:1024 prescaler
   TCNT1 = TIMER1_TCNT1_VALUE;   //!< Pre-load timer counter register
   TIFR1 |= (1 << TOV1);         //!< Clear interrupt overflow flag register
   TIMSK1 |= (1 << TOIE1);       //!< Enable overflow interrupt
}

void stop_timer() {
   TCCR1B = 0x00;                //!< Stop
   TIMSK1 &= ~(1 << TOIE1);      //!< Disable overflow interrupt
   TIFR1 |= (1 << TOV1);         //!< Clear interrupt overflow flag register
   TCNT1 = TIMER1_TCNT1_VALUE;   //!< Pre-load timer counter register
}

/*!
\fn ISR(TIMER1_OVF_vect)
\brief Timer1 overflow interrupts routine.
\return void.
*/
ISR(TIMER1_OVF_vect) {
   //! Pre-load timer counter register
   TCNT1 = TIMER1_TCNT1_VALUE;
   interrupt_task_1s();
}

#elif (USE_RTC)
void rtc_interrupt_handler() {
   interrupt_task_1s();
}

#endif

void init_sensors () {
  do_reset_first_run = false;
  is_first_run = true;
  is_first_test = true;
  is_test = false;
  uint8_t sensors_count = 0;
  uint8_t sensors_error_count = 0;

  if (readable_configuration.sensors_count) {
    // read sensors configuration, create and setup
    for (uint8_t i=0; i<readable_configuration.sensors_count; i++) {
      SensorDriver::createAndSetup(readable_configuration.sensors[i].driver, readable_configuration.sensors[i].type, readable_configuration.sensors[i].address, readable_configuration.sensors[i].node, sensors, &sensors_count);
      LOGN(F("--> %l: %s-%s [ 0x%x ]: %s\t [ %s ]"), sensors_count, readable_configuration.sensors[i].driver, readable_configuration.sensors[i].type, readable_configuration.sensors[i].address, readable_configuration.sensors[i].mqtt_topic, sensors[i]->isSetted() ? OK_STRING : FAIL_STRING);
      if (!sensors[i]->isSetted()) {
        sensors_error_count++;
      }
    }

      LOGN(F(""));
   }
}

void setNextTimeForSensorReading (time_t *next_time, uint16_t time_s) {
   time_t counter = (now() / time_s);
   *next_time = (time_t) ((++counter) * time_s);
}

#if (USE_MQTT)
bool mqttConnect(char *username, char *password) {
   MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
   data.MQTTVersion = 3;
   // data.will.topicName.cstring = maint_topic;
   // data.will.message.cstring = MQTT_ON_ERROR_MESSAGE;
   // data.will.retained = true;
   // data.will.qos = MQTT::QOS1;
   // data.willFlag = true;
   data.clientID.cstring = client_id;
   data.username.cstring = username;
   data.password.cstring = password;
   data.cleansession = false;

   // LOGT(F("MQTT clientID: %s"), data.clientID.cstring);
   // LOGT(F("MQTT will message: %s"), data.will.message.cstring);
   // LOGT(F("MQTT will topic: %s"), data.will.topicName.cstring);

   return (mqtt_client.connect(data) == 0);
}

bool mqttPublish(const char *topic, const char *message, bool is_retained) {
   MQTT::Message tx_message;
   tx_message.qos = MQTT::QOS1;
   tx_message.retained = is_retained;
   tx_message.dup = false;
   tx_message.payload = (void*) message;
   tx_message.payloadlen = strlen(message);

   return (mqtt_client.publish(topic, tx_message) == 0);
}

void mqttRxCallback(MQTT::MessageData &md) {
   MQTT::Message &rx_message = md.message;
   // LOGT(F("MQTT RX: %s"), (char*)rx_message.payload);
   // LOGT(F("--> qos %l"), rx_message.qos);
   // LOGT(F("--> retained %l"), rx_message.retained);
   // LOGT(F("--> dup %l"), rx_message.dup);
   // LOGT(F("--> id %l"), rx_message.id);
}
#endif

void print_configuration() {
   getStimaNameByType(stima_name, readable_configuration.module_type);
   LOGN(F("--> type: %s"), stima_name);
   LOGN(F("--> version: %d.%d"), readable_configuration.module_main_version, readable_configuration.module_minor_version);
   LOGN(F("--> sensors: %d"), readable_configuration.sensors_count);

   #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
   LOGN(F("--> dhcp: %s"), readable_configuration.is_dhcp_enable ? "on" : "off");
   LOGN(F("--> ethernet mac: %02X:%02X:%02X:%02X:%02X:%02X"), readable_configuration.ethernet_mac[0], readable_configuration.ethernet_mac[1], readable_configuration.ethernet_mac[2], readable_configuration.ethernet_mac[3], readable_configuration.ethernet_mac[4], readable_configuration.ethernet_mac[5]);

   #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
   LOGN(F("--> gsm apn: %s"), readable_configuration.gsm_apn);
   LOGN(F("--> gsm username: %s"), readable_configuration.gsm_username);
   LOGN(F("--> gsm password: %s"), readable_configuration.gsm_password);

   #endif

   #if (USE_NTP)
   LOGN(F("--> ntp server: %s"), readable_configuration.ntp_server);
   #endif

   #if (USE_MQTT)
   LOGN(F("--> mqtt server: %s"), readable_configuration.mqtt_server);
   LOGN(F("--> mqtt port: %l"), readable_configuration.mqtt_port);
   LOGN(F("--> mqtt root topic: %s"), readable_configuration.mqtt_root_topic);
   LOGN(F("--> mqtt maint topic: %s"), readable_configuration.mqtt_maint_topic);
   LOGN(F("--> mqtt subscribe topic: %s"), readable_configuration.mqtt_subscribe_topic);
   LOGN(F("--> mqtt username: %s"), readable_configuration.mqtt_username);
   LOGN(F("--> mqtt password: %s"), readable_configuration.mqtt_password);
   #endif
}

void set_default_configuration() {
   writable_configuration.module_type = MODULE_TYPE;
   writable_configuration.module_main_version = MODULE_MAIN_VERSION;
   writable_configuration.module_minor_version = MODULE_MINOR_VERSION;

   writable_configuration.report_seconds = 0;

   writable_configuration.sensors_count = 0;
   memset(writable_configuration.sensors, 0, sizeof(sensor_t) * SENSORS_MAX);

   #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
   char temp_string[20];
   writable_configuration.is_dhcp_enable = CONFIGURATION_DEFAULT_ETHERNET_DHCP_ENABLE;
   strcpy(temp_string, CONFIGURATION_DEFAULT_ETHERNET_MAC);
   macStringToArray(writable_configuration.ethernet_mac, temp_string);
   strcpy(temp_string, CONFIGURATION_DEFAULT_ETHERNET_IP);
   ipStringToArray(writable_configuration.ip, temp_string);
   strcpy(temp_string, CONFIGURATION_DEFAULT_ETHERNET_NETMASK);
   ipStringToArray(writable_configuration.netmask, temp_string);
   strcpy(temp_string, CONFIGURATION_DEFAULT_ETHERNET_GATEWAY);
   ipStringToArray(writable_configuration.gateway, temp_string);
   strcpy(temp_string, CONFIGURATION_DEFAULT_ETHERNET_PRIMARY_DNS);
   ipStringToArray(writable_configuration.primary_dns, temp_string);

   #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
   strcpy(writable_configuration.gsm_apn, CONFIGURATION_DEFAULT_GSM_APN);
   strcpy(writable_configuration.gsm_username, CONFIGURATION_DEFAULT_GSM_USERNAME);
   strcpy(writable_configuration.gsm_password, CONFIGURATION_DEFAULT_GSM_PASSWORD);

   #endif

   #if (USE_NTP)
   strcpy(writable_configuration.ntp_server, CONFIGURATION_DEFAULT_NTP_SERVER);
   #endif

   #if (USE_MQTT)
   writable_configuration.mqtt_port = CONFIGURATION_DEFAULT_MQTT_PORT;
   strcpy(writable_configuration.mqtt_server, CONFIGURATION_DEFAULT_MQTT_SERVER);
   strcpy(writable_configuration.mqtt_root_topic, CONFIGURATION_DEFAULT_MQTT_ROOT_TOPIC);
   strcpy(writable_configuration.mqtt_maint_topic, CONFIGURATION_DEFAULT_MQTT_MAINT_TOPIC);
   strcpy(writable_configuration.mqtt_subscribe_topic, CONFIGURATION_DEFAULT_MQTT_SUBSCRIBE_TOPIC);
   strcpy(writable_configuration.mqtt_username, CONFIGURATION_DEFAULT_MQTT_USERNAME);
   strcpy(writable_configuration.mqtt_password, CONFIGURATION_DEFAULT_MQTT_PASSWORD);
   #endif

   LOGN(F("Reset configuration to default value... [ %s ]"), OK_STRING);
}

void save_configuration(bool is_default) {
   if (is_default) {
      set_default_configuration();
      LOGN(F("Save default configuration... [ %s ]"), OK_STRING);
   }
   else {
      LOGN(F("Save configuration... [ %s ]"), OK_STRING);
   }

   ee_write(&writable_configuration, CONFIGURATION_EEPROM_ADDRESS, sizeof(configuration_t));
}

void load_configuration() {

   ee_read(&writable_configuration, CONFIGURATION_EEPROM_ADDRESS, sizeof(configuration_t));

   if (digitalRead(CONFIGURATION_RESET_PIN) == LOW) {
      LOGN(F("Wait configuration..."));
   }

   while (digitalRead(CONFIGURATION_RESET_PIN) == LOW) {
      streamRpc.parseStream(&is_event_rpc, &Serial);
   }

   LOGN(F("Configuration received... [ %s ]"), OK_STRING);

   if (writable_configuration.module_type != MODULE_TYPE || writable_configuration.module_main_version != MODULE_MAIN_VERSION || writable_configuration.module_minor_version != MODULE_MINOR_VERSION) {
      save_configuration(CONFIGURATION_DEFAULT);
   }

   ee_read(&readable_configuration, CONFIGURATION_EEPROM_ADDRESS, sizeof(configuration_t));

   #if (USE_MQTT)
   getMqttClientIdFromMqttTopic(readable_configuration.mqtt_maint_topic, client_id);
   getFullTopic(maint_topic, readable_configuration.mqtt_maint_topic, MQTT_STATUS_TOPIC);
   #endif

   LOGN(F("Load configuration... [ %s ]"), OK_STRING);
   print_configuration();
}

#if (USE_RPC_METHOD_PREPARE || USE_RPC_METHOD_PREPANDGET || USE_RPC_METHOD_GETJSON)
bool extractSensorsParams(JsonObject &params, char *driver, char *type, uint8_t *address, uint8_t *node) {
   bool is_error = false;

   for (JsonObject::iterator it = params.begin(); it != params.end(); ++it) {
      if (strcmp(it.key().c_str(), "driver") == 0) {
         strncpy(driver, it.value().as<const char*>(), DRIVER_LENGTH);
      }
      else if (strcmp(it.key().c_str(), "type") == 0) {
         strncpy(type, it.value().as<const char*>(), TYPE_LENGTH);
      }
      else if (strcmp(it.key().c_str(), "address") == 0) {
         *address = it.value().as<unsigned char>();
      }
      else if (strcmp(it.key().c_str(), "node") == 0) {
         *node = it.value().as<unsigned char>();
      }
      else {
         is_error = true;
      }
   }

   return is_error;
}
#endif

#if (USE_RPC_METHOD_CONFIGURE)
int configure(JsonObject params, JsonObject result) {
   bool is_error = false;
   bool is_sensor_config = false;

   for (JsonPair it : params) {
      if (strcmp(it.key().c_str(), "reset") == 0) {
         if (it.value().as<bool>() == true) {
            set_default_configuration();
         }
      }
      else if (strcmp(it.key().c_str(), "save") == 0) {
         if (it.value().as<bool>() == true) {
            save_configuration(CONFIGURATION_CURRENT);
         }
      }
      #if (USE_MQTT)
      else if (strcmp(it.key().c_str(), "mqttserver") == 0) {
         strncpy(writable_configuration.mqtt_server, it.value().as<const char*>(), MQTT_SERVER_LENGTH);
      }
      else if (strcmp(it.key().c_str(), "mqttrootpath") == 0) {
         strncpy(writable_configuration.mqtt_root_topic, it.value().as<const char*>(), MQTT_ROOT_TOPIC_LENGTH);
         strncpy(writable_configuration.mqtt_subscribe_topic, it.value().as<const char*>(), MQTT_SUBSCRIBE_TOPIC_LENGTH);
         uint8_t mqtt_subscribe_topic_len = strlen(writable_configuration.mqtt_subscribe_topic);
         strncpy(writable_configuration.mqtt_subscribe_topic+mqtt_subscribe_topic_len, "rx", MQTT_SUBSCRIBE_TOPIC_LENGTH-mqtt_subscribe_topic_len);
      }
      else if (strcmp(it.key().c_str(), "mqttmaintpath") == 0) {
         strncpy(writable_configuration.mqtt_maint_topic, it.value().as<const char*>(), MQTT_MAINT_TOPIC_LENGTH);
      }
      else if (strcmp(it.key().c_str(), "mqttsampletime") == 0) {
         writable_configuration.report_seconds = it.value().as<unsigned int>();
      }
      else if (strcmp(it.key().c_str(), "mqttuser") == 0) {
         strncpy(writable_configuration.mqtt_username, it.value().as<const char*>(), MQTT_USERNAME_LENGTH);
      }
      else if (strcmp(it.key().c_str(), "mqttpassword") == 0) {
         strncpy(writable_configuration.mqtt_password, it.value().as<const char*>(), MQTT_PASSWORD_LENGTH);
      }
      else if (strcmp(it.key().c_str(), "sd") == 0) {
	for (JsonPair sd : it.value().as<JsonObject>()) {
	  strncpy(writable_configuration.constantdata[writable_configuration.constantdata_count].btable, sd.key().c_str(), CONSTANTDATA_BTABLE_LENGTH);
	  strncpy(writable_configuration.constantdata[writable_configuration.constantdata_count].value, sd.value().as<const char*>(), CONSTANTDATA_VALUE_LENGTH);

	  if (writable_configuration.sensors_count < USE_CONSTANTDATA_COUNT)
	    writable_configuration.constantdata_count++;
	  else {
	    is_error = true;
	  }
	}
	
      }
      #endif
      #if (USE_NTP)
      else if (strcmp(it.key().c_str(), "ntpserver") == 0) {
         strncpy(writable_configuration.ntp_server, it.value().as<const char*>(), NTP_SERVER_LENGTH);
      }
      #endif
      else if (strcmp(it.key().c_str(), "date") == 0) {
         #if (USE_RTC)
         Pcf8563::disable();
         Pcf8563::setDate(it.value().as<JsonArray>()[2].as<int>(), it.value().as<JsonArray>()[1].as<int>(), it.value().as<JsonArray>()[0].as<int>() - 2000, weekday()-1, 0);
         Pcf8563::setTime(it.value().as<JsonArray>()[3].as<int>(), it.value().as<JsonArray>()[4].as<int>(), it.value().as<JsonArray>()[5].as<int>());
         Pcf8563::enable();
         setSyncInterval(NTP_TIME_FOR_RESYNC_S);
         setSyncProvider(getSystemTime);
         #elif (USE_TIMER_1)
         setTime(it.value().as<JsonArray>()[3].as<int>(), it.value().as<JsonArray>()[4].as<int>(), it.value().as<JsonArray>()[5].as<int>(), it.value().as<JsonArray>()[2].as<int>(), it.value().as<JsonArray>()[1].as<int>(), it.value().as<JsonArray>()[0].as<int>() - 2000);
         #endif
      }
      else if (strcmp(it.key().c_str(), "mac") == 0) {
         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH)
         for (uint8_t i=0; i<ETHERNET_MAC_LENGTH; i++) {
            writable_configuration.ethernet_mac[i] = it.value().as<JsonArray>()[i];
         }
	 #else
	 LOGV(F("Configuration mac parameter ignored"));
	 #endif
      }
      #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM)
      else if (strcmp(it.key().c_str(), "gsmapn") == 0) {
         strncpy(writable_configuration.gsm_apn, it.value().as<const char*>(), GSM_APN_LENGTH);
      }
      #endif
      else if (strcmp(it.key().c_str(), "driver") == 0) {
         strncpy(writable_configuration.sensors[writable_configuration.sensors_count].driver, it.value().as<const char*>(), DRIVER_LENGTH);
         is_sensor_config = true;
      }
      else if (strcmp(it.key().c_str(), "type") == 0) {
         strncpy(writable_configuration.sensors[writable_configuration.sensors_count].type, it.value().as<const char*>(), TYPE_LENGTH);
         is_sensor_config = true;
      }
      else if (strcmp(it.key().c_str(), "address") == 0) {
         writable_configuration.sensors[writable_configuration.sensors_count].address = it.value().as<unsigned char>();
         is_sensor_config = true;
      }
      else if (strcmp(it.key().c_str(), "node") == 0) {
         writable_configuration.sensors[writable_configuration.sensors_count].node = it.value().as<unsigned char>();
         is_sensor_config = true;
      }
      else if (strcmp(it.key().c_str(), "mqttpath") == 0) {
         strncpy(writable_configuration.sensors[writable_configuration.sensors_count].mqtt_topic, it.value().as<const char*>(), MQTT_SENSOR_TOPIC_LENGTH);
         is_sensor_config = true;
      }
      else {
         is_error = true;
      }
   }

   if (is_sensor_config) {
     if (writable_configuration.sensors_count < SENSORS_MAX)
       writable_configuration.sensors_count++;
     else {
       is_error = true;
     }     
   }

   if (is_error) {
      result[F("state")] = F("error");
      return E_INVALID_PARAMS;
   }
   else {
      result[F("state")] = F("done");
      return E_SUCCESS;
   }
}
#endif

#if (USE_RPC_METHOD_PREPARE)
int prepare(JsonObject params, JsonObject result) {
   static int state;
   static bool is_error = false;
   static char driver[DRIVER_LENGTH];
   static char type[TYPE_LENGTH];
   static uint8_t address = 0;
   static uint8_t node = 0;
   static uint8_t i;
   static uint32_t wait_time;

   switch (rpc_state) {
      case RPC_INIT:
         state = E_BUSY;
         is_error = extractSensorsParams(params, driver, type, &address, &node);

         if (!is_error && !is_event_sensors_reading) {
            is_event_sensors_reading_rpc = true;
            rpc_state = RPC_EXECUTE;
         }
         else {
            rpc_state = RPC_END;
         }
      break;

      case RPC_EXECUTE:
         if (is_event_sensors_reading_rpc) {
            sensors_reading_task (true, false, driver, type, address, node, &i, &wait_time);
         }
         else {
            rpc_state = RPC_END;
         }
      break;

      case RPC_END:
         if (is_error) {
            result[F("state")] = F("error");
            state = E_INVALID_PARAMS;
         }
         else {
            result[F("state")] = F("done");
            result[F("waittime")] = wait_time;
            state = E_SUCCESS;
         }
         rpc_state = RPC_INIT;
      break;
   }

   return state;
}
#endif

#if (USE_RPC_METHOD_GETJSON)
int getjson(JsonObject params, JsonObject result) {
   static int state;
   static bool is_error = false;
   static char driver[DRIVER_LENGTH];
   static char type[TYPE_LENGTH];
   static uint8_t address = 0;
   static uint8_t node = 0;
   static uint8_t i;
   static uint32_t wait_time;
   static char sensor_reading_time_buffer[DATE_TIME_STRING_LENGTH];

   switch (rpc_state) {
      case RPC_INIT:
         state = E_BUSY;
         is_error = extractSensorsParams(params, driver, type, &address, &node);

         if (!is_error && !is_event_sensors_reading) {
            is_event_sensors_reading_rpc = true;
            rpc_state = RPC_EXECUTE;
         }
         else {
            rpc_state = RPC_END;
         }
      break;

      case RPC_EXECUTE:
         if (is_event_sensors_reading_rpc) {
            sensors_reading_task (false, true, driver, type, address, node, &i, &wait_time);
         }
         else {
            rpc_state = RPC_END;
         }
      break;

      case RPC_END:
         if (is_error) {
            result[F("state")] = F("error");
            state = E_INVALID_PARAMS;
         }
         else {
            StaticJsonBuffer<JSON_BUFFER_LENGTH*2> jsonBuffer;
            JsonObject &v = jsonBuffer.parseObject((const char*) &json_sensors_data[i][0]);
            snprintf(sensor_reading_time_buffer, DATE_TIME_STRING_LENGTH, "%04u-%02u-%02uT%02u:%02u:%02u", year(), month(), day(), hour(), minute(), second());

            result[F("state")] = F("done");
            result.createNestedObject(F("v"));

            for (JsonObject::iterator it = v.begin(); it != v.end(); ++it) {
               if (it.value().as<unsigned int>() == 0) {
                  result[F("v")][(char *) it.key().c_str()] = (char *) NULL;
               }
               else {
                  result[F("v")][(char *) it.key().c_str()] = it.value().as<unsigned int>();
               }
            }

            result[F("t")] = sensor_reading_time_buffer;
            state = E_SUCCESS;
         }
         rpc_state = RPC_INIT;
      break;
   }

   return state;
}
#endif

#if (USE_RPC_METHOD_PREPANDGET)
int prepandget(JsonObject params, JsonObject result) {
   static int state;
   static bool is_error = false;
   static char driver[DRIVER_LENGTH];
   static char type[TYPE_LENGTH];
   static uint8_t address = 0;
   static uint8_t node = 0;
   static uint8_t i;
   static uint32_t wait_time;
   static char sensor_reading_time_buffer[DATE_TIME_STRING_LENGTH];

   switch (rpc_state) {
      case RPC_INIT:
         state = E_BUSY;
         is_error = extractSensorsParams(params, driver, type, &address, &node);

         if (!is_error && !is_event_sensors_reading) {
            is_event_sensors_reading_rpc = true;
            rpc_state = RPC_EXECUTE;
         }
         else {
            rpc_state = RPC_END;
         }
      break;

      case RPC_EXECUTE:
         if (is_event_sensors_reading_rpc) {
            sensors_reading_task (true, true, driver, type, address, node, &i, &wait_time);
         }
         else {
            rpc_state = RPC_END;
         }
      break;

      case RPC_END:
         if (is_error) {
            result[F("state")] = F("error");
            state = E_INVALID_PARAMS;
         }
         else {
            StaticJsonBuffer<JSON_BUFFER_LENGTH*2> jsonBuffer;
            JsonObject &v = jsonBuffer.parseObject((const char*) &json_sensors_data[i][0]);
            snprintf(sensor_reading_time_buffer, DATE_TIME_STRING_LENGTH, "%04u-%02u-%02uT%02u:%02u:%02u", year(), month(), day(), hour(), minute(), second());

            result[F("state")] = F("done");
            result.createNestedObject(F("v"));

            for (JsonObject::iterator it = v.begin(); it != v.end(); ++it) {
               if (it.value().as<unsigned int>() == 0) {
                  result[F("v")][(char *) it.key().c_str()] = (char *) NULL;
               }
               else {
                  result[F("v")][(char *) it.key().c_str()] = it.value().as<unsigned int>();
               }
            }

            result[F("t")] = sensor_reading_time_buffer;
            state = E_SUCCESS;
         }
         rpc_state = RPC_INIT;
      break;
   }

   return state;
}
#endif

time_t getSystemTime() {
  return system_time;
}

/*
void reboot() {
  init_wdt(WDTO_1S);
  while(true);
}
*/
#if (USE_RPC_METHOD_REBOOT)
int reboot(JsonObject params, JsonObject result) {
   result[F("state")] = "done";
   init_wdt(WDTO_1S);
   while(true);
   return E_SUCCESS;
}
#endif

void interrupt_task_1s () {
  system_time++;
  setTime(system_time);

  #if (MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM)
  if (is_time_set && now() >= next_ptr_time_for_sensors_reading && next_ptr_time_for_sensors_reading) {

    sensor_reading_time.Day = day(next_ptr_time_for_sensors_reading);
    sensor_reading_time.Month = month(next_ptr_time_for_sensors_reading);
    sensor_reading_time.Year = CalendarYrToTm(year(next_ptr_time_for_sensors_reading));
    sensor_reading_time.Hour = hour(next_ptr_time_for_sensors_reading);
    sensor_reading_time.Minute = minute(next_ptr_time_for_sensors_reading);
    sensor_reading_time.Second = second(next_ptr_time_for_sensors_reading);

    setNextTimeForSensorReading((time_t *) &next_ptr_time_for_sensors_reading, readable_configuration.report_seconds);
    is_time_for_sensors_reading_updated = true;
    do_reset_first_run = true;

    if (!is_event_sensors_reading) {
      noInterrupts();
      is_test = false;
      is_event_sensors_reading = true;
      interrupts();
      xTaskResumeFromISR( xHandleSensorReading );      //xTaskResumeFromISR() is generally considered a dangerous function because its actions are not latched.
    }

    #if (USE_MQTT)
    if (is_event_mqtt) {
      noInterrupts();
      is_event_mqtt_paused = true;
      is_event_mqtt = false;
      interrupts();
      vTaskSuspend( xHandleMqtt );
    }
    #endif
  }

  if (is_time_set && now() >= next_ptr_time_for_testing_sensors && next_ptr_time_for_testing_sensors) {
    setNextTimeForSensorReading((time_t *) &next_ptr_time_for_testing_sensors, SENSORS_TESTING_DELAY_S);
    noInterrupts();
    if (!is_event_sensors_reading) {
      is_test = !is_first_test;
      is_event_sensors_reading = true;
      xTaskResumeFromISR( xHandleSensorReading );      //xTaskResumeFromISR() is generally considered a dangerous function because its actions are not latched.
    }
    interrupts();
  }
  #endif

}

void supervisor_task() {
   static uint8_t retry;
   static supervisor_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;

   static bool is_supervisor_first_run = true;
   static bool is_time_updated;

   bool is_sdcard_ok = false;

   #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
   bool *is_event_client = &is_event_ethernet;
   TaskHandle_t *xHandleClient = &xHandleEthernet;
   #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
   bool *is_event_client = &is_event_gsm;
   TaskHandle_t *xHandleClient = &xHandleGsm;
   #endif

   switch (supervisor_state) {
      case SUPERVISOR_INIT:
         retry = 0;
         start_time_ms = 0;
         is_time_updated = false;

         #if (MODULE_TYPE != STIMA_MODULE_TYPE_PASSIVE)
         if (!*is_event_client && is_client_connected) {
            is_event_client_executed = true;
         }
         else {
            is_event_time_executed = false;
         }
         #endif

         #if (USE_MQTT)
         if (is_event_mqtt_paused) {
            noInterrupts();
            if (!is_event_mqtt) {
               is_event_mqtt = true;
	       vTaskResume( xHandleMqtt );
            }
            interrupts();

            supervisor_state = SUPERVISOR_END;
            LOGV(F("SUPERVISOR_INIT ---> SUPERVISOR_END"));
         }
         else {
         #endif
            #if (USE_NTP)
            // need ntp sync ?
            if (!do_ntp_sync && ((now() - last_ntp_sync > NTP_TIME_FOR_RESYNC_S) || !is_time_set)) {
               do_ntp_sync = true;
               LOGT(F("Requested NTP time sync..."));
            }

            start_time_ms = millis();
            #endif

            #if (MODULE_TYPE != STIMA_MODULE_TYPE_PASSIVE)
            supervisor_state = SUPERVISOR_CONNECTION_LEVEL_TASK;
            LOGV(F("SUPERVISOR_INIT ---> SUPERVISOR_CONNECTION_LEVEL_TASK"));
            #else
            supervisor_state = SUPERVISOR_TIME_LEVEL_TASK;
            LOGV(F("SUPERVISOR_INIT ---> SUPERVISOR_TIME_LEVEL_TASK"));
            #endif
         #if (USE_MQTT)
         }
         #endif
      break;

      case SUPERVISOR_CONNECTION_LEVEL_TASK:
         #if (MODULE_TYPE != STIMA_MODULE_TYPE_PASSIVE)
         // enable hardware related tasks for connect
         noInterrupts();
         if (!*is_event_client && !is_event_client_executed && !is_client_connected) {
            *is_event_client = true;
	    vTaskResume( *xHandleClient );
         }
         interrupts();
         supervisor_state = SUPERVISOR_WAIT_CONNECTION_LEVEL_TASK;
         LOGV(F("SUPERVISOR_CONNECTION_LEVEL_TASK ---> SUPERVISOR_WAIT_CONNECTION_LEVEL_TASK"));
         #endif
      break;

      case SUPERVISOR_WAIT_CONNECTION_LEVEL_TASK:
         #if (MODULE_TYPE != STIMA_MODULE_TYPE_PASSIVE)
         // success
         if (!*is_event_client && is_event_client_executed && is_client_connected) {

            // reset time task for doing ntp sync
            if (is_client_udp_socket_open && do_ntp_sync) {
               is_event_time_executed = false;
               supervisor_state = SUPERVISOR_TIME_LEVEL_TASK;
               LOGV(F("SUPERVISOR_WAIT_CONNECTION_LEVEL_TASK ---> SUPERVISOR_TIME_LEVEL_TASK"));
            }
            // doing other operations...
            else {
               do_ntp_sync = false;
               supervisor_state = SUPERVISOR_MANAGE_LEVEL_TASK;
               LOGV(F("SUPERVISOR_WAIT_CONNECTION_LEVEL_TASK ---> SUPERVISOR_MANAGE_LEVEL_TASK"));
            }
         }

         // error
         if (!*is_event_client && is_event_client_executed && !is_client_connected) {
            // retry
            if ((++retry < SUPERVISOR_CONNECTION_RETRY_COUNT_MAX) || (millis() - start_time_ms < SUPERVISOR_CONNECTION_TIMEOUT_MS)) {
               is_event_client_executed = false;
               supervisor_state = SUPERVISOR_CONNECTION_LEVEL_TASK;
               LOGV(F("SUPERVISOR_WAIT_CONNECTION_LEVEL_TASK ---> SUPERVISOR_CONNECTION_LEVEL_TASK"));
            }
            // fail
            else {
               supervisor_state = SUPERVISOR_TIME_LEVEL_TASK;
               LOGV(F("SUPERVISOR_WAIT_CONNECTION_LEVEL_TASK ---> SUPERVISOR_TIME_LEVEL_TASK"));
            }
         }
         #endif
      break;

      case SUPERVISOR_TIME_LEVEL_TASK:
         // enable time task
         noInterrupts();
         if (!is_event_time && !is_event_time_executed) {
            is_event_time = true;
	    vTaskResume( xHandleTime );
         }
         interrupts();

         if (!is_event_time && is_event_time_executed) {
	    // if NTP sync fail, reset variable anyway
	    if (do_ntp_sync || ((now() - last_ntp_sync) > NTP_TIME_FOR_RESYNC_S)) {
	      last_ntp_sync = system_time;
	      do_ntp_sync = false;
	    }

	    is_time_updated = true;

            #if (USE_NTP)
            if (is_client_connected) {
               do_ntp_sync = false;

               #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM)
               noInterrupts();
               if (!*is_event_client) {
                  *is_event_client = true;
		  vTaskResume( *xHandleClient );
               }
               interrupts();
               #endif
            }
            #endif

            supervisor_state = SUPERVISOR_MANAGE_LEVEL_TASK;
            LOGV(F("SUPERVISOR_TIME_LEVEL_TASK ---> SUPERVISOR_MANAGE_LEVEL_TASK"));
         }
      break;

      case SUPERVISOR_MANAGE_LEVEL_TASK:
         if (is_time_updated) {
            LOGN(F("Current date and time is: %02u/%02u/%04u %02u:%02u:%02u"), day(), month(), year(), hour(), minute(), second());
         }

         #if (MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM)
         if (is_supervisor_first_run && is_time_set) {
            if (readable_configuration.report_seconds) {
               setNextTimeForSensorReading((time_t *) &next_ptr_time_for_sensors_reading, readable_configuration.report_seconds);

               // testing sensors
               setNextTimeForSensorReading((time_t *) &next_ptr_time_for_testing_sensors, SENSORS_TESTING_DELAY_S);

               LOGN(F("Acquisition scheduling..."));
               LOGN(F("--> observations every %l minutes"), OBSERVATIONS_MINUTES);
            }

            if (readable_configuration.report_seconds >= 60) {
               uint8_t mm = readable_configuration.report_seconds / 60;
               uint8_t ss = readable_configuration.report_seconds - mm * 60;
               if (ss) {
                  LOGN(F("--> report every %l minutes and %l seconds"), mm, ss);
               }
               else {
                  LOGN(F("--> report every %l minutes"), mm);
               }
            }
            else if (readable_configuration.report_seconds) {
               LOGN(F("--> report every %l seconds"), readable_configuration.report_seconds);
            }

            if (next_ptr_time_for_sensors_reading) {
               LOGN(F("--> starting at: %02u:%02u:%02u"), hour(next_ptr_time_for_sensors_reading), minute(next_ptr_time_for_sensors_reading), second(next_ptr_time_for_sensors_reading));
            }

            if (next_ptr_time_for_testing_sensors) {
               LOGN(F("--> testing at: %02u:%02u:%02u"), hour(next_ptr_time_for_testing_sensors), minute(next_ptr_time_for_testing_sensors), second(next_ptr_time_for_testing_sensors));
            }
         }
         #endif

         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH)
         #if (USE_MQTT)
         noInterrupts();
         if (!is_event_mqtt) {
            is_event_mqtt = true;
	    vTaskResume( xHandleMqtt );
         }
         interrupts();
         #endif

         #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM)
         #if (USE_MQTT)
         if (!*is_event_client) {
            noInterrupts();
            if (!is_event_mqtt) {
               is_event_mqtt = true;
	       vTaskResume( xHandleMqtt );
            }
            interrupts();
         }
         #endif

         #endif

         supervisor_state = SUPERVISOR_TEST_SDCARD;
      break;

      case SUPERVISOR_TEST_SDCARD:
        #if (USE_SDCARD)
        if (is_supervisor_first_run) {
          if (sdcard_init(&SD, SDCARD_CHIP_SELECT_PIN)) {
            if (sdcard_open_file(&SD, &test_file, SDCARD_TEST_FILE_NAME, O_RDWR | O_CREAT | O_APPEND)) {
              is_sdcard_ok = test_file.close();
            }
          }

          if (!is_sdcard_ok) {
            LOGE(F("SD Card... [ %s ]--> is card inserted?--> there is a valid FAT32 filesystem?"), FAIL_STRING);
          }
        }
        #endif

        supervisor_state = SUPERVISOR_END;
        LOGV(F("SUPERVISOR_MANAGE_LEVEL_TASK ---> SUPERVISOR_END"));
      break;

      case SUPERVISOR_END:
         is_supervisor_first_run = false;
         noInterrupts();
         is_event_supervisor = false;
         interrupts();
	 vTaskSuspend( NULL);

         supervisor_state = SUPERVISOR_INIT;
         LOGV(F("SUPERVISOR_END ---> SUPERVISOR_INIT"));
      break;

      case SUPERVISOR_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            supervisor_state = state_after_wait;
         }
      break;
   }
}

/*
void rtc_task() {
  if (is_time_set) {

    #if (MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM)
    if (is_time_for_sensors_reading_updated) {
      is_time_for_sensors_reading_updated = false;
      LOGN(F("Next acquisition scheduled at: %02u:%02u:%02u"), hour(next_ptr_time_for_sensors_reading), minute(next_ptr_time_for_sensors_reading), second(next_ptr_time_for_sensors_reading));
    }
    #endif
  }
  vTaskDelay(5000/portTICK_PERIOD_MS);
}
*/

void time_task() {
   static uint8_t retry;
   static time_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;

   #if (USE_NTP)
   static bool is_set_rtc_ok;
   static time_t current_ntp_time;
   time_t diff_ntp_time;
   bool is_ntp_request_ok;
   #endif

   switch (time_state) {
      case TIME_INIT:
         #if (USE_NTP)
         current_ntp_time = 0;
         is_set_rtc_ok = true;
         #endif
         retry = 0;
         state_after_wait = TIME_INIT;

         #if (USE_NTP)
         if (is_client_connected) {
            time_state = TIME_SEND_ONLINE_REQUEST;
            LOGV(F("TIME_INIT --> TIME_SEND_ONLINE_REQUEST"));
         }
         else {
            time_state = TIME_SET_SYNC_RTC_PROVIDER;
            LOGV(F("TIME_INIT --> TIME_SET_SYNC_RTC_PROVIDER"));
         }
         #else
         #if (USE_RTC)
         time_state = TIME_SET_SYNC_RTC_PROVIDER;
         LOGV(F("TIME_INIT --> TIME_SET_SYNC_RTC_PROVIDER"));
         #elif (USE_TIMER_1)
         time_state = TIME_END;
         LOGV(F("TIME_INIT --> TIME_END"));
         #endif
         #endif
      break;

      case TIME_SEND_ONLINE_REQUEST:
         #if (USE_NTP)
         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
         is_ntp_request_ok = Ntp::sendRequest(&eth_udp_client, readable_configuration.ntp_server);

         #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
         is_ntp_request_ok = Ntp::sendRequest(&s800);
         #endif

         // success
         if (is_ntp_request_ok) {
            retry = 0;
            time_state = TIME_WAIT_ONLINE_RESPONSE;
            LOGV(F("TIME_SEND_ONLINE_REQUEST --> TIME_WAIT_ONLINE_RESPONSE"));
         }
         // retry
         else if (++retry < NTP_RETRY_COUNT_MAX) {
            delay_ms = NTP_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = TIME_SEND_ONLINE_REQUEST;
            time_state = TIME_WAIT_STATE;
            LOGV(F("TIME_SEND_ONLINE_REQUEST --> TIME_WAIT_STATE"));
         }
         // fail: use old rtc time
         else {
            LOGE(F("NTP request... [ %s ]"), FAIL_STRING);
            #if (USE_RTC)
            time_state = TIME_SET_SYNC_RTC_PROVIDER;
            LOGV(F("TIME_SEND_ONLINE_REQUEST --> TIME_SET_SYNC_RTC_PROVIDER"));
            #elif (USE_TIMER_1)
            time_state = TIME_END;
            LOGV(F("TIME_SEND_ONLINE_REQUEST --> TIME_END"));
            #endif
         }
         #endif
      break;

      case TIME_WAIT_ONLINE_RESPONSE:
         #if (USE_NTP)
         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
         current_ntp_time = Ntp::getResponse(&eth_udp_client);

         #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
         current_ntp_time = Ntp::getResponse(&s800);

         #endif

         if (is_time_set && (system_time > current_ntp_time)) {
           diff_ntp_time = system_time - current_ntp_time;
         } else if (is_time_set) {
           diff_ntp_time = current_ntp_time - system_time;
         } else {
           diff_ntp_time = 0;
         }

         if ((current_ntp_time > NTP_VALID_START_TIME_S) && (diff_ntp_time <= NTP_MAX_DIFF_VALID_TIME_S)) {
            retry = 0;
            system_time = current_ntp_time;
            setTime(system_time);
            last_ntp_sync = current_ntp_time;
            LOGT(F("Current NTP date and time: %02u/%02u/%04u %02u:%02u:%02u"), day(), month(), year(), hour(), minute(), second());
            #if (USE_RTC)
            time_state = TIME_SET_SYNC_NTP_PROVIDER;
            LOGV(F("TIME_WAIT_ONLINE_RESPONSE --> TIME_WAIT_STATE"));
            #elif (USE_TIMER_1)
            time_state = TIME_SET_SYNC_NTP_PROVIDER;
            LOGV(F("TIME_WAIT_ONLINE_RESPONSE --> TIME_WAIT_STATE"));
            #endif
         }
         // retry
         else if (++retry < NTP_RETRY_COUNT_MAX) {
            delay_ms = NTP_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = TIME_WAIT_ONLINE_RESPONSE;
            time_state = TIME_WAIT_STATE;
            LOGV(F("TIME_WAIT_ONLINE_RESPONSE --> TIME_WAIT_STATE"));
         }
         // fail
         else {
            retry = 0;
            #if (USE_RTC)
            time_state = TIME_SET_SYNC_RTC_PROVIDER;
            LOGV(F("TIME_WAIT_ONLINE_RESPONSE --> TIME_SET_SYNC_RTC_PROVIDER"));
            #elif (USE_TIMER_1)
            time_state = TIME_END;
            LOGV(F("TIME_WAIT_ONLINE_RESPONSE --> TIME_END"));
            #endif
         }
         #endif
      break;

      case TIME_SET_SYNC_NTP_PROVIDER:
         #if (USE_NTP)
         is_set_rtc_ok &= Pcf8563::disable();
         is_set_rtc_ok &= Pcf8563::setDate(day(), month(), year()-2000, weekday()-1, 0);
         is_set_rtc_ok &= Pcf8563::setTime(hour(), minute(), second());
         is_set_rtc_ok &= Pcf8563::enable();

         if (!is_set_rtc_ok) {
           i2c_error++;
         }

         if (is_set_rtc_ok) {
            retry = 0;
            time_state = TIME_SET_SYNC_RTC_PROVIDER;
            LOGV(F("TIME_SET_SYNC_NTP_PROVIDER --> TIME_SET_SYNC_RTC_PROVIDER"));
         }
         // retry
         else if (++retry < NTP_RETRY_COUNT_MAX) {
            is_set_rtc_ok = true;
            delay_ms = NTP_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = TIME_SET_SYNC_NTP_PROVIDER;
            time_state = TIME_WAIT_STATE;
            LOGV(F("TIME_SET_SYNC_NTP_PROVIDER --> TIME_SET_SYNC_NTP_PROVIDER"));
         }
         // fail
         else {
           retry = 0;
           time_state = TIME_SET_SYNC_RTC_PROVIDER;
           LOGV(F("TIME_SET_SYNC_NTP_PROVIDER --> TIME_SET_SYNC_RTC_PROVIDER"));
         }
         #endif
      break;

      case TIME_SET_SYNC_RTC_PROVIDER:
         setSyncInterval(NTP_TIME_FOR_RESYNC_S);
         setSyncProvider(getSystemTime);
         LOGT(F("Current System date and time: %02u/%02u/%04u %02u:%02u:%02u"), day(), month(), year(), hour(), minute(), second());
         time_state = TIME_END;
         LOGV(F("TIME_SET_SYNC_RTC_PROVIDER --> TIME_END"));
      break;

      case TIME_END:
         is_time_set = true;
         is_event_time_executed = true;
         noInterrupts();
         is_event_time = false;
         interrupts();
         time_state = TIME_INIT;
         LOGV(F("TIME_END --> TIME_INIT"));
	 vTaskSuspend( NULL );
      break;

      case TIME_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            time_state = state_after_wait;
         }
      break;
   }
}

#if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_ETH)
void ethernet_task() {
   static uint8_t retry;
   static ethernet_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;

   switch (ethernet_state) {
      case ETHERNET_INIT:
         retry = 0;
         is_client_connected = false;
         is_client_udp_socket_open = false;
         state_after_wait = ETHERNET_INIT;
         ethernet_state = ETHERNET_CONNECT;
         LOGV(F("ETHERNET_INIT --> ETHERNET_CONNECT"));
      break;

      case ETHERNET_CONNECT:
         if (readable_configuration.is_dhcp_enable) {
            if (Ethernet.begin(readable_configuration.ethernet_mac)) {
               is_client_connected = true;
               LOGN(F("Ethernet: DHCP [ %s ]"), OK_STRING);
            }
         }
         else {
            Ethernet.begin(readable_configuration.ethernet_mac, IPAddress(readable_configuration.ip), IPAddress(readable_configuration.primary_dns), IPAddress(readable_configuration.gateway), IPAddress(readable_configuration.netmask));
            is_client_connected = true;
            LOGN(F("Ethernet: Static [ %s ]"), OK_STRING);
         }

         // success
         if (is_client_connected) {
            w5500.setRetransmissionTime(ETHERNET_RETRY_TIME_MS);
            w5500.setRetransmissionCount(ETHERNET_RETRY_COUNT);

            LOGN(F("--> ip: %l.%l.%l.%l"), Ethernet.localIP()[0], Ethernet.localIP()[1], Ethernet.localIP()[2], Ethernet.localIP()[3]);
            LOGN(F("--> netmask: %l.%l.%l.%l"), Ethernet.subnetMask()[0], Ethernet.subnetMask()[1], Ethernet.subnetMask()[2], Ethernet.subnetMask()[3]);
            LOGN(F("--> gateway: %l.%l.%l.%l"), Ethernet.gatewayIP()[0], Ethernet.gatewayIP()[1], Ethernet.gatewayIP()[2], Ethernet.gatewayIP()[3]);
            LOGN(F("--> primary dns: %l.%l.%l.%l"), Ethernet.dnsServerIP()[0], Ethernet.dnsServerIP()[1], Ethernet.dnsServerIP()[2], Ethernet.dnsServerIP()[3]);

            ethernet_state = ETHERNET_OPEN_UDP_SOCKET;
            LOGV(F("ETHERNET_CONNECT --> ETHERNET_OPEN_UDP_SOCKET"));
         }
         // retry
         else if ((++retry) < ETHERNET_RETRY_COUNT_MAX) {
            delay_ms = ETHERNET_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = ETHERNET_CONNECT;
            ethernet_state = ETHERNET_WAIT_STATE;
            LOGV(F("ETHERNET_CONNECT --> ETHERNET_WAIT_STATE"));
         }
         // fail
         else {
            retry = 0;
            ethernet_state = ETHERNET_END;
            LOGV(F("ETHERNET_CONNECT --> ETHERNET_END"));
            LOGE(F("Ethernet %s: [ %s ]"), ERROR_STRING, readable_configuration.is_dhcp_enable ? "DHCP" : "Static");
         }
      break;

      case ETHERNET_OPEN_UDP_SOCKET:
         // success
         if (eth_udp_client.begin(ETHERNET_DEFAULT_LOCAL_UDP_PORT)) {
            LOGV(F("--> udp socket local port: %l [ OK ]"), ETHERNET_DEFAULT_LOCAL_UDP_PORT);
            is_client_udp_socket_open = true;
            ethernet_state = ETHERNET_END;
            LOGV(F("ETHERNET_OPEN_UDP_SOCKET --> ETHERNET_END"));
         }
         // retry
         else if ((++retry) < ETHERNET_RETRY_COUNT_MAX) {
            delay_ms = ETHERNET_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = ETHERNET_OPEN_UDP_SOCKET;
            ethernet_state = ETHERNET_WAIT_STATE;
            LOGV(F("ETHERNET_OPEN_UDP_SOCKET --> ETHERNET_WAIT_STATE"));
         }
         // fail
         else {
            LOGE(F("--> udp socket on local port: %l [ FAIL ]"), ETHERNET_DEFAULT_LOCAL_UDP_PORT);
            retry = 0;
            ethernet_state = ETHERNET_INIT;
            LOGV(F("ETHERNET_OPEN_UDP_SOCKET --> ETHERNET_INIT"));
         }
      break;

      case ETHERNET_END:
         LOGN(F(""));
         is_event_client_executed = true;
         noInterrupts();
         is_event_ethernet = false;
         interrupts();
         ethernet_state = ETHERNET_INIT;
         LOGV(F("ETHERNET_END --> ETHERNET_INIT"));
	 vTaskSuspend( xHandleEthernet );
      break;

      case ETHERNET_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            ethernet_state = state_after_wait;
         }
      break;
   }
}

#elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_PASSIVE_GSM)
void gsm_task() {
   static gsm_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;
   static bool is_error;
   sim800_status_t sim800_status;
   uint8_t sim800_connection_status;
   static uint8_t power_off_mode = SIM800_POWER_OFF_BY_SWITCH;

   switch (gsm_state) {
      case GSM_INIT:
         is_error = false;
         is_client_connected = false;
         state_after_wait = GSM_INIT;
         gsm_state = GSM_SWITCH_ON;
      break;

      case GSM_SWITCH_ON:
         sim800_status = s800.switchOn();

         // success
         if (sim800_status == SIM800_OK) {
            gsm_state = GSM_AUTOBAUD;
         }
         else if (sim800_status == SIM800_ERROR) {
            gsm_state = GSM_END;
         }
         // wait...
      break;

      case GSM_AUTOBAUD:
         sim800_status = s800.initAutobaud();

         // success
         if (sim800_status == SIM800_OK) {
            delay_ms = SIM800_WAIT_FOR_AUTOBAUD_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = GSM_SETUP;
            gsm_state = GSM_WAIT_STATE;

         }
         // fail
         else if (sim800_status == SIM800_ERROR) {
            gsm_state = GSM_WAIT_FOR_SWITCH_OFF;
         }
         // wait...
      break;

      case GSM_SETUP:
         sim800_status = s800.setup();

         // success
         if (sim800_status == SIM800_OK) {
            gsm_state = GSM_START_CONNECTION;
         }
         // fail
         else if (sim800_status == SIM800_ERROR) {
            is_error = true;
            gsm_state = GSM_WAIT_FOR_SWITCH_OFF;
         }
         // wait...
      break;

      case GSM_START_CONNECTION:
         sim800_status = s800.startConnection(readable_configuration.gsm_apn, readable_configuration.gsm_username, readable_configuration.gsm_password);

         // success
         if (sim800_status == SIM800_OK) {
            gsm_state = GSM_CHECK_OPERATION;
         }
         // fail
         else if (sim800_status == SIM800_ERROR) {
            is_error = true;
            gsm_state = GSM_WAIT_FOR_SWITCH_OFF;
         }
         // wait...
      break;

      case GSM_CHECK_OPERATION:
         // open udp socket for query NTP
         if (do_ntp_sync) {
            gsm_state = GSM_OPEN_UDP_SOCKET;
         }
         // wait for mqtt send terminate
         else {
            gsm_state = GSM_SUSPEND;
            state_after_wait = GSM_STOP_CONNECTION;
         }
      break;

      case GSM_OPEN_UDP_SOCKET:
         sim800_connection_status = s800.connection(SIM800_CONNECTION_UDP, readable_configuration.ntp_server, NTP_SERVER_PORT);

         // success
         if (sim800_connection_status == 1) {
            is_client_udp_socket_open = true;
            is_client_connected = true;
            is_event_client_executed = true;
            state_after_wait = GSM_STOP_CONNECTION;
            gsm_state = GSM_SUSPEND;
         }
         // fail
         else if (sim800_connection_status == 2) {
            is_client_connected = false;
            is_event_client_executed = true;
            is_error = true;
            gsm_state = GSM_WAIT_FOR_SWITCH_OFF;
         }
         // wait
      break;

      case GSM_SUSPEND:
         is_client_connected = true;
         is_event_client_executed = true;
         gsm_state = state_after_wait;
         noInterrupts();
         is_event_gsm = false;
         interrupts();
	 vTaskSuspend( NULL );
      break;

      case GSM_STOP_CONNECTION:
         sim800_status = s800.stopConnection();

         // success
         if (sim800_status == SIM800_OK) {
            gsm_state = GSM_SWITCH_OFF;
         }
         // fail
         else if (sim800_status == SIM800_ERROR) {
            is_error = true;
            gsm_state = GSM_SWITCH_OFF;
         }
         // wait
      break;

      case GSM_WAIT_FOR_SWITCH_OFF:
         delay_ms = SIM800_POWER_ON_TO_OFF_DELAY_MS;
         start_time_ms = millis();
         state_after_wait = GSM_SWITCH_OFF;
         gsm_state = GSM_WAIT_STATE;
      break;

      case GSM_SWITCH_OFF:
         sim800_status = s800.switchOff(power_off_mode);

         // success
         if (sim800_status == SIM800_OK) {
            delay_ms = SIM800_WAIT_FOR_POWER_OFF_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = GSM_END;
            gsm_state = GSM_WAIT_STATE;
         }
         // fail
         else if (sim800_status == SIM800_ERROR) {
            if (power_off_mode == SIM800_POWER_OFF_BY_AT_COMMAND) {
               power_off_mode = SIM800_POWER_OFF_BY_SWITCH;
            }
            else {
               gsm_state = GSM_END;
            }
         }
         // wait...
      break;

      case GSM_END:
         if (is_error) {
         }
         is_event_client_executed = true;
         is_client_connected = false;
         is_client_udp_socket_open = false;
         noInterrupts();
         is_event_gsm = false;
         interrupts();
         gsm_state = GSM_INIT;
	 vTaskSuspend( NULL );
      break;

      case GSM_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            gsm_state = state_after_wait;
         }
      break;
   }
}

#endif

void sensors_reading_task (bool do_prepare, bool do_get, char *driver, char *type, uint8_t address, uint8_t node, uint8_t *sensor_index, uint32_t *wait_time) {
   static uint8_t i;
   static uint8_t retry;
   static sensors_reading_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;
   static bool is_sensor_found;
   switch (sensors_reading_state) {
      case SENSORS_READING_INIT:
         i = 0;
         is_sensor_found = false;

         if (driver && type && address && node) {
            while (!is_sensor_found && (i < readable_configuration.sensors_count)) {
               is_sensor_found = strcmp(sensors[i]->getDriver(), driver) == 0 && strcmp(sensors[i]->getType(), type) == 0 && sensors[i]->getAddress() == address && sensors[i]->getNode() == node;
               if (!is_sensor_found) {
                  i++;
               }
            }

            if (is_sensor_found) {
               *sensor_index = i;
            }
         }

         if (do_prepare) {
            LOGN(F("Sensors reading..."));
            retry = 0;

            if (driver && type && address && node && is_sensor_found) {
               sensors[i]->resetPrepared();
            }
            else {
               for (i=0; i<readable_configuration.sensors_count; i++) {
                  sensors[i]->resetPrepared();
               }
               i = 0;
            }

            state_after_wait = SENSORS_READING_INIT;
            sensors_reading_state = SENSORS_READING_PREPARE;
            LOGV(F("SENSORS_READING_INIT ---> SENSORS_READING_PREPARE"));
         }
         else if (do_get) {
            sensors_reading_state = SENSORS_READING_GET;
            LOGV(F("SENSORS_READING_INIT ---> SENSORS_READING_GET"));
         }
         else {
            sensors_reading_state = SENSORS_READING_END;
            LOGV(F("SENSORS_READING_INIT ---> SENSORS_READING_END"));
         }
      break;

      case SENSORS_READING_PREPARE:
         sensors[i]->prepare(is_test);
         delay_ms = sensors[i]->getDelay();
         start_time_ms = sensors[i]->getStartTime();

         if (driver && type && address && node) {
            *wait_time = delay_ms;
         }

         if (delay_ms) {
            state_after_wait = SENSORS_READING_IS_PREPARED;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
            LOGV(F("SENSORS_READING_PREPARE ---> SENSORS_READING_WAIT_STATE"));
         }
         else {
            sensors_reading_state = SENSORS_READING_IS_PREPARED;
            LOGV(F("SENSORS_READING_PREPARE ---> SENSORS_READING_IS_PREPARED"));
         }
      break;

      case SENSORS_READING_IS_PREPARED:
         // success
         if (sensors[i]->isPrepared()) {
            retry = 0;

            if (do_get) {
               sensors_reading_state = SENSORS_READING_GET;
               LOGV(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_GET"));
            }
            else {
               sensors_reading_state = SENSORS_READING_END;
               LOGV(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_END"));
            }
         }
         // retry
         else if ((++retry) < SENSORS_RETRY_COUNT_MAX) {
            i2c_error++;
            delay_ms = SENSORS_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = SENSORS_READING_PREPARE;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
            LOGV(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_WAIT_STATE"));
         }
         // fail
         else {
            if (do_get) {
               sensors_reading_state = SENSORS_READING_GET;
               LOGV(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_GET"));
            }
            else {
               sensors_reading_state = SENSORS_READING_END;
               LOGV(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_END"));
            }
            retry = 0;
         }
      break;

      case SENSORS_READING_GET:
        if (is_test) {
          sensors[i]->get(&values_readed_from_sensor[i][0], VALUES_TO_READ_FROM_SENSOR_COUNT);
        }
        else {
          sensors[i]->getJson(&values_readed_from_sensor[i][0], VALUES_TO_READ_FROM_SENSOR_COUNT, &json_sensors_data[i][0]);
        }

        delay_ms = sensors[i]->getDelay();
        start_time_ms = sensors[i]->getStartTime();

        if (delay_ms) {
          state_after_wait = SENSORS_READING_IS_GETTED;
          sensors_reading_state = SENSORS_READING_WAIT_STATE;
          LOGV(F("SENSORS_READING_GET ---> SENSORS_READING_WAIT_STATE"));
        }
        else {
          sensors_reading_state = SENSORS_READING_IS_GETTED;
          LOGV(F("SENSORS_READING_GET ---> SENSORS_READING_IS_GETTED"));
        }
      break;

      case SENSORS_READING_IS_GETTED:
         // end
         if (sensors[i]->isEnd() && !sensors[i]->isReaded()) {
            // success
            if (sensors[i]->isSuccess()) {
               retry = 0;
               sensors_reading_state = SENSORS_READING_READ;
               LOGV(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_READ"));
            }
            // retry
            else if ((++retry) < SENSORS_RETRY_COUNT_MAX) {
               i2c_error++;
               delay_ms = SENSORS_RETRY_DELAY_MS;
               start_time_ms = millis();
               state_after_wait = SENSORS_READING_GET;
               sensors_reading_state = SENSORS_READING_WAIT_STATE;
               LOGV(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_WAIT_STATE"));
            }
            // fail
            else {
               retry = 0;
               sensors_reading_state = SENSORS_READING_READ;
               LOGV(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_READ"));
            }
         }
         // not end
         else {
            sensors_reading_state = SENSORS_READING_GET;
            LOGV(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_GET"));
         }
      break;

      case SENSORS_READING_READ:
         if (driver && type && address && node) {
            sensors_reading_state = SENSORS_READING_END;
            LOGV(F("SENSORS_READING_READ ---> SENSORS_READING_END"));
         }
         else {
            sensors_reading_state = SENSORS_READING_NEXT;
            LOGV(F("SENSORS_READING_READ ---> SENSORS_READING_NEXT"));
         }
      break;

      case SENSORS_READING_NEXT:
        // next sensor
        if ((++i) < readable_configuration.sensors_count) {
          retry = 0;
          sensors_reading_state = SENSORS_READING_PREPARE;
          LOGV(F("SENSORS_READING_NEXT ---> SENSORS_READING_PREPARE"));
        }
        // success: all sensors readed
        else {
          // first time: read ptr data from sdcard
          if (is_first_run && !is_test) {
            #if (USE_MQTT)
            noInterrupts();
            if (!is_event_supervisor && is_event_mqtt_paused) {
              is_event_supervisor = true;
	      vTaskResume( xHandleSupervisor);
            }
            interrupts();
            #endif
          }

          // other time but not in test: save data to sdcard
          // normal AND NOT test: save
          if (!is_first_run && !is_test) {
            #if (USE_SDCARD)
            noInterrupts();
            if (!is_event_data_saving) {
              is_event_data_saving = true;
	      vTaskResume( xHandleDataSaving );
            }
            interrupts();
            #endif
          }

          sensors_reading_state = SENSORS_READING_END;
          LOGV(F("SENSORS_READING_NEXT ---> SENSORS_READING_END"));
        }
        break;

      case SENSORS_READING_END:
        is_first_test = false;

        if (do_reset_first_run) {
          is_first_run = false;
        }

        noInterrupts();
        if (is_event_sensors_reading) {
          is_event_sensors_reading = false;
        }

        if (is_event_sensors_reading_rpc) {
          is_event_sensors_reading_rpc = false;
        }
        interrupts();

        sensors_reading_state = SENSORS_READING_INIT;
        LOGV(F("SENSORS_READING_END ---> SENSORS_READING_INIT"));
	vTaskSuspend( NULL );
      break;

      case SENSORS_READING_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            sensors_reading_state = state_after_wait;
         }
      break;
   }
}

#if (USE_SDCARD)
void data_saving_task() {
   static uint8_t retry;
   static data_saving_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;
   static uint8_t i;
   static uint8_t k;
   static uint8_t data_count;
   static uint16_t sd_data_count;
   static char sd_buffer[MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH];
   static char topic_buffer[VALUES_TO_READ_FROM_SENSOR_COUNT][MQTT_SENSOR_TOPIC_LENGTH];
   static char message_buffer[VALUES_TO_READ_FROM_SENSOR_COUNT][MQTT_MESSAGE_LENGTH];
   char file_name[SDCARD_FILES_NAME_MAX_LENGTH];

   switch (data_saving_state) {
      case DATA_SAVING_INIT:
         retry = 0;
         sd_data_count = 0;

         if (is_sdcard_open) {
            data_saving_state = DATA_SAVING_OPEN_FILE;
            LOGV(F("DATA_SAVING_INIT ---> DATA_SAVING_OPEN_FILE"));
         }
         else {
            data_saving_state = DATA_SAVING_OPEN_SDCARD;
            LOGV(F("DATA_SAVING_INIT ---> DATA_SAVING_OPEN_SDCARD"));
         }
      break;

      case DATA_SAVING_OPEN_SDCARD:
         if (sdcard_init(&SD, SDCARD_CHIP_SELECT_PIN)) {
            retry = 0;
            is_sdcard_open = true;
            data_saving_state = DATA_SAVING_OPEN_FILE;
            LOGV(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_OPEN_FILE"));
         }
         // retry
         else if ((++retry) < DATA_SAVING_RETRY_COUNT_MAX) {
            delay_ms = DATA_SAVING_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = DATA_SAVING_OPEN_SDCARD;
            data_saving_state = DATA_SAVING_WAIT_STATE;
            LOGV(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_WAIT_STATE"));
         }
         // fail
         else {
            is_sdcard_error = true;
            is_sdcard_open = false;
            LOGE(F("SD Card... [ FAIL ]--> is card inserted?--> there is a valid FAT32 filesystem?"));

            data_saving_state = DATA_SAVING_END;
            LOGV(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_END"));
         }
      break;

      case DATA_SAVING_OPEN_FILE:
         // open sdcard file: today!
         sdcard_make_filename(now(), file_name);

         // try to open file. if ok, write sensors data on it.
         if (sdcard_open_file(&SD, &write_data_file, file_name, O_RDWR | O_CREAT | O_APPEND)) {
            retry = 0;
            i = 0;
            data_saving_state = DATA_SAVING_SENSORS_LOOP;
            LOGV(F("DATA_SAVING_OPEN_FILE ---> DATA_SAVING_SENSORS_LOOP"));
         }
         // retry
         else if ((++retry) < DATA_SAVING_RETRY_COUNT_MAX) {
            delay_ms = DATA_SAVING_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = DATA_SAVING_OPEN_FILE;
            data_saving_state = DATA_SAVING_WAIT_STATE;
            LOGV(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_WAIT_STATE"));
         }
         // fail
         else {
            LOGE(F("SD Card open file %s... [ FAIL ]"), file_name);
            is_sdcard_error = true;
            data_saving_state = DATA_SAVING_END;
            LOGV(F("DATA_SAVING_OPEN_FILE ---> DATA_SAVING_END"));
         }
      break;

      case DATA_SAVING_SENSORS_LOOP:
         if (i < readable_configuration.sensors_count) {
            k = 0;
            data_count = jsonToMqtt(&json_sensors_data[i][0], readable_configuration.sensors[i].mqtt_topic, topic_buffer, message_buffer, (tmElements_t *) &sensor_reading_time);
            data_saving_state = DATA_SAVING_DATA_LOOP;
            LOGV(F("DATA_SAVING_SENSORS_LOOP ---> DATA_SAVING_DATA_LOOP"));
         }
         else {
            LOGT(F(""));
            data_saving_state = DATA_SAVING_CLOSE_FILE;
            LOGV(F("DATA_SAVING_SENSORS_LOOP ---> DATA_SAVING_CLOSE_FILE"));
         }
      break;

      case DATA_SAVING_DATA_LOOP:
         if (k < data_count) {
            mqttToSd(&topic_buffer[k][0], &message_buffer[k][0], sd_buffer);
            data_saving_state = DATA_SAVING_WRITE_FILE;
            LOGV(F("DATA_SAVING_DATA_LOOP ---> DATA_SAVING_WRITE_FILE"));
         }
         else {
            i++;
            data_saving_state = DATA_SAVING_SENSORS_LOOP;
            LOGV(F("DATA_SAVING_DATA_LOOP ---> DATA_SAVING_SENSORS_LOOP"));
         }
      break;

      case DATA_SAVING_WRITE_FILE:
         // sdcard success
         if (write_data_file.write(sd_buffer, MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH) == (MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH)) {
            LOGT(F("SD <-- %s %s"), &topic_buffer[k][0], &message_buffer[k][0]);
            write_data_file.flush();
            retry = 0;
            k++;
            sd_data_count++;
            data_saving_state = DATA_SAVING_DATA_LOOP;
            LOGV(F("DATA_SAVING_WRITE_FILE ---> DATA_SAVING_DATA_LOOP"));
         }
         // retry
         else if ((++retry) < DATA_SAVING_RETRY_COUNT_MAX) {
            delay_ms = DATA_SAVING_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = DATA_SAVING_WRITE_FILE;
            data_saving_state = DATA_SAVING_WAIT_STATE;
            LOGV(F("DATA_SAVING_WRITE_FILE ---> DATA_SAVING_WAIT_STATE"));
         }
         // fail
         else {
            LOGE(F("SD Card writing data on file %s... [ FAIL ]"), file_name);
            is_sdcard_error = true;
            data_saving_state = DATA_SAVING_CLOSE_FILE;
            LOGV(F("DATA_SAVING_WRITE_FILE ---> DATA_SAVING_CLOSE_FILE"));
         }
      break;

      case DATA_SAVING_CLOSE_FILE:
            is_sdcard_error = !write_data_file.close();
            data_saving_state = DATA_SAVING_END;
            LOGV(F("DATA_SAVING_CLOSE_FILE ---> DATA_SAVING_END"));
         break;

      case DATA_SAVING_END:
         LOGN(F("[ %l ] data stored in sdcard... [ %s ]"), sd_data_count, is_sdcard_error ? ERROR_STRING : OK_STRING);

         noInterrupts();
         if (!is_event_supervisor) {
            is_event_supervisor = true;
	    vTaskResume( xHandleSupervisor);
         }

         is_event_data_saving = false;
         interrupts();

         data_saving_state = DATA_SAVING_INIT;
         LOGV(F("DATA_SAVING_END ---> DATA_SAVING_INIT"));
	 vTaskSuspend( NULL );
      break;

      case DATA_SAVING_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            data_saving_state = state_after_wait;
         }
      break;
   }
}
#endif

#if (USE_MQTT)
void mqtt_task() {
   static uint8_t retry;
   static mqtt_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;
   static uint8_t i;
   static uint8_t k;
   static uint16_t mqtt_data_count;
   static uint8_t data_count;
   static char sd_buffer[MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH];
   static char topic_buffer[JSONS_TO_READ_FROM_SENSOR_COUNT][MQTT_SENSOR_TOPIC_LENGTH];
   static char message_buffer[JSONS_TO_READ_FROM_SENSOR_COUNT][MQTT_MESSAGE_LENGTH];
   static char full_topic_buffer[MQTT_ROOT_TOPIC_LENGTH + MQTT_SENSOR_TOPIC_LENGTH];
   static bool is_mqtt_error;
   static bool is_mqtt_processing_sdcard;
   static bool is_mqtt_processing_json;
   static bool is_mqtt_published_data;
   static bool is_ptr_found;
   static bool is_ptr_updated;
   static bool is_eof_data_read;
   static bool is_mqtt_constantdata;
   static tmElements_t datetime;
   static time_t current_ptr_time_data;
   static time_t last_correct_ptr_time_data;
   static time_t next_ptr_time_data;
   static uint32_t ipstack_timeout_ms;
   uint8_t ipstack_status;
   char file_name[SDCARD_FILES_NAME_MAX_LENGTH];
   int read_bytes_count;

   switch (mqtt_state) {
      case MQTT_INIT:
         retry = 0;
         is_ptr_found = false;
         is_ptr_updated = false;
         is_eof_data_read = false;
         is_mqtt_error = false;
         is_mqtt_published_data = false;
	 is_mqtt_constantdata = false;
         mqtt_data_count = 0;

         if (!is_sdcard_open && !is_sdcard_error) {
            mqtt_state = MQTT_OPEN_SDCARD;
            LOGV(F("MQTT_PTR_DATA_INIT ---> MQTT_OPEN_SDCARD"));
         }
         else if (is_sdcard_open) {
            mqtt_state = MQTT_OPEN_PTR_FILE;
            LOGV(F("MQTT_PTR_DATA_INIT ---> MQTT_OPEN_PTR_FILE"));
         }
         else {
            mqtt_state = MQTT_PTR_END;
            LOGV(F("MQTT_PTR_DATA_INIT ---> MQTT_PTR_END"));
         }
      break;

      case MQTT_OPEN_SDCARD:
         if (sdcard_init(&SD, SDCARD_CHIP_SELECT_PIN)) {
            retry = 0;
            is_sdcard_open = true;
            is_sdcard_error = false;
            mqtt_state = MQTT_OPEN_PTR_FILE;
            LOGV(F("MQTT_OPEN_SDCARD ---> MQTT_OPEN_PTR_FILE"));
         }
         // retry
         else if ((++retry) < MQTT_RETRY_COUNT_MAX) {
            delay_ms = MQTT_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = MQTT_OPEN_SDCARD;
            mqtt_state = MQTT_WAIT_STATE;
            LOGV(F("MQTT_OPEN_SDCARD ---> MQTT_PTR_DATA_WAIT_STATE"));
         }
         // fail
         else {
            is_sdcard_error = true;
            is_sdcard_open = false;
            LOGE(F("SD Card... [ FAIL ]--> is card inserted?--> there is a valid FAT32 filesystem?"));

            mqtt_state = MQTT_PTR_END;
            LOGV(F("MQTT_OPEN_SDCARD ---> MQTT_PTR_END"));
         }
         break;

      case MQTT_OPEN_PTR_FILE:
         // try to open file. if ok, read ptr data.
         if (sdcard_open_file(&SD, &mqtt_ptr_file, SDCARD_MQTT_PTR_FILE_NAME, O_RDWR | O_CREAT)) {
            retry = 0;
            mqtt_state = MQTT_PTR_READ;
            LOGV(F("MQTT_OPEN_PTR_FILE ---> MQTT_PTR_READ"));
         }
         // retry
         else if ((++retry) < MQTT_RETRY_COUNT_MAX) {
            delay_ms = MQTT_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = MQTT_OPEN_PTR_FILE;
            mqtt_state = MQTT_WAIT_STATE;
            LOGV(F("MQTT_OPEN_PTR_FILE ---> MQTT_PTR_DATA_WAIT_STATE"));
         }
         // fail
         else {
            LOGE(F("SD Card open file %s... [ FAIL ]"), SDCARD_MQTT_PTR_FILE_NAME);
            is_sdcard_error = true;
            mqtt_state = MQTT_PTR_END;
            LOGV(F("MQTT_OPEN_PTR_FILE ---> MQTT_PTR_END"));
         }
      break;

      case MQTT_PTR_READ:
         ptr_time_data = UINT32_MAX;
         mqtt_ptr_file.seekSet(0);
         read_bytes_count = mqtt_ptr_file.read(&ptr_time_data, sizeof(time_t));

         // found
         if (read_bytes_count == sizeof(time_t) && ptr_time_data < now()) {
            is_ptr_found = true;
            mqtt_state = MQTT_PTR_FOUND;
            LOGV(F("MQTT_PTR_READ ---> MQTT_PTR_FOUND"));
         }
         // not found (no sdcard error): find it by starting from 1th January of this year
         else if (read_bytes_count >= 0) {
            LOGN(F("Data pointer... [ FIND ]"));
            datetime.Year = CalendarYrToTm(year(now()));
            datetime.Month = 1;
            datetime.Day = 1;
            datetime.Hour = 0;
            datetime.Minute = 0;
            datetime.Second = 0;
            ptr_time_data = makeTime(datetime);
            is_ptr_found = false;
            mqtt_state = MQTT_PTR_FIND;
            LOGV(F("MQTT_PTR_READ ---> MQTT_PTR_FIND"));
         }
         // not found (sdcard error)
         else {
            is_ptr_found = false;
            is_sdcard_error = true;
            mqtt_state = MQTT_PTR_END;
            LOGV(F("MQTT_PTR_READ ---> MQTT_PTR_END"));
         }
      break;

      case MQTT_PTR_FIND:
         // ptr not found. find it by searching in file name until today is reach.
         // if there isn't file, ptr_time_data is set to current date at 00:00:00 time.
         if (!is_ptr_found && ptr_time_data < now()) {
            sdcard_make_filename(ptr_time_data, file_name);

            if (SD.exists(file_name)) {
               is_ptr_found = true;
               is_ptr_updated = true;
               is_eof_data_read = false;
               LOGN(F("%s... [ FOUND ]"), file_name);
               mqtt_state = MQTT_PTR_END;
               LOGV(F("MQTT_PTR_FOUND ---> MQTT_PTR_END"));
            }
            else {
               LOGN(F("%s... [ NOT FOUND ]"), file_name);
               ptr_time_data += SECS_PER_DAY;
            }
         }
         // ptr not found: set ptr to yesterday (today at 00:00:00 - readable_configuration.report_seconds time).
         else if (!is_ptr_found && ptr_time_data >= now()) {
            datetime.Year = CalendarYrToTm(year());
            datetime.Month = month();
            datetime.Day = day();
            datetime.Hour = 0;
            datetime.Minute = 0;
            datetime.Second = 0;
            ptr_time_data = makeTime(datetime);
            is_ptr_found = true;
            is_ptr_updated = true;
         }
         // ptr found: sooner or later the ptr will be set in any case
         else if (is_ptr_found) {
            mqtt_state = MQTT_PTR_FOUND;
            LOGV(F("MQTT_PTR_FIND ---> MQTT_PTR_FOUND"));
         }
      break;

      case MQTT_PTR_FOUND:
         // datafile read, reach eof and is today. END.
         if (is_eof_data_read && year() == year(ptr_time_data) && month() == month(ptr_time_data) && day() == day(ptr_time_data)) {
            mqtt_state = MQTT_CLOSE_DATA_FILE;
            LOGV(F("MQTT_PTR_FOUND ---> MQTT_CLOSE_DATA_FILE"));
         }
         // datafile read, reach eof and NOT is today. go to end of this day.
         else if (is_eof_data_read) {
            datetime.Year = CalendarYrToTm(year(ptr_time_data));
            datetime.Month = month(ptr_time_data);
            datetime.Day = day(ptr_time_data) + 1;
            datetime.Hour = 0;
            datetime.Minute = 0;
            datetime.Second = 0;
            ptr_time_data = makeTime(datetime);
            ptr_time_data -= readable_configuration.report_seconds;
            is_ptr_updated = true;
            mqtt_state = MQTT_PTR_END;
            LOGV(F("MQTT_PTR_FOUND ---> MQTT_PTR_END"));
         }
         else {
            is_eof_data_read = false;
            mqtt_state = MQTT_PTR_END;
            LOGV(F("MQTT_PTR_FOUND ---> MQTT_PTR_END"));
         }
      break;

      case MQTT_PTR_END:
         // ptr data is found: send data saved on sdcard
         if (is_ptr_found && is_sdcard_open && !is_sdcard_error) {
            last_correct_ptr_time_data = ptr_time_data;
            LOGN(F("Data pointer... [ %02u/%02u/%04u %02u:%02u:%02u ] [ %s ]"), day(ptr_time_data), month(ptr_time_data), year(ptr_time_data), hour(ptr_time_data), minute(ptr_time_data), second(ptr_time_data), OK_STRING);
            mqtt_state = MQTT_OPEN;
            LOGV(F("MQTT_PTR_END ---> MQTT_OPEN"));
         }
         // ptr data is NOT found: sd card fault fallback: send last acquired sensor data
         else {
            LOGN(F("Data pointer... [ --/--/---- --:--:-- ] [ %s ]"), ERROR_STRING);
            is_sdcard_error = true;
            mqtt_state = MQTT_OPEN;
            LOGV(F("MQTT_PTR_END ---> MQTT_OPEN"));
         }
      break;

      case MQTT_OPEN:
         if (is_client_connected && mqtt_client.isConnected()) {
            mqtt_state = MQTT_CHECK;
            LOGV(F("MQTT_OPEN ---> MQTT_CHECK"));
         }
         else if (is_client_connected) {
            ipstack_timeout_ms = 0;
            mqtt_state = MQTT_CONNECT;
            LOGV(F("MQTT_OPEN ---> MQTT_CONNECT"));
         }
         // error: client not connected!
         else {
            is_mqtt_error = true;
            mqtt_state = MQTT_END;
            LOGV(F("MQTT_OPEN ---> MQTT_END"));
         }
         break;

      case MQTT_CONNECT:
         if (ipstack_timeout_ms == 0) {
            ipstack_timeout_ms = millis();
         }

         ipstack_status = ipstack.connect(readable_configuration.mqtt_server, readable_configuration.mqtt_port);

         // success
         if (ipstack_status == 1 && mqttConnect(readable_configuration.mqtt_username, readable_configuration.mqtt_password)) {
            retry = 0;
            LOGT(F("MQTT Connection... [ %s ]"), OK_STRING);
            mqtt_state = MQTT_ON_CONNECT;
            LOGV(F("MQTT_CONNECT ---> MQTT_ON_CONNECT"));
         }
         // retry
         else if (ipstack_status == 2 && (++retry) < MQTT_RETRY_COUNT_MAX) {
            delay_ms = MQTT_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = MQTT_CONNECT;
            mqtt_state = MQTT_WAIT_STATE;
            LOGV(F("MQTT_CONNECT ---> MQTT_WAIT_STATE"));
         }
         // fail
         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH)
         else if (ipstack_status == 2 || (millis() - ipstack_timeout_ms >= ETHERNET_MQTT_TIMEOUT_MS)) {
         #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM)
         else if (ipstack_status == 2) {
         #endif
            LOGE(F("MQTT Connection... [ %s ]"), FAIL_STRING);
            is_mqtt_error = true;
            mqtt_state = MQTT_ON_DISCONNECT;
            LOGV(F("MQTT_CONNECT ---> MQTT_ON_DISCONNECT"));
         }
         // wait
      break;

      case MQTT_ON_CONNECT:
         getFullTopic(full_topic_buffer, readable_configuration.mqtt_maint_topic, MQTT_STATUS_TOPIC);
         snprintf(&message_buffer[0][0], MQTT_MESSAGE_LENGTH, MQTT_ON_CONNECT_MESSAGE);

         if (mqttPublish(full_topic_buffer, &message_buffer[0][0]), true) {
            retry = 0;
            mqtt_state = MQTT_SUBSCRIBE;
            LOGV(F("MQTT_ON_CONNECT ---> MQTT_SUBSCRIBE"));
         }
         // retry
         else if ((++retry) < MQTT_RETRY_COUNT_MAX) {
            delay_ms = MQTT_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = MQTT_ON_CONNECT;
            mqtt_state = MQTT_WAIT_STATE;
            LOGV(F("MQTT_ON_CONNECT ---> MQTT_WAIT_STATE"));
         }
         // fail
         else {
            retry = 0;
            LOGE(F("MQTT on connect publish message... [ %s ]"), FAIL_STRING);
            is_mqtt_error = true;
            mqtt_state = MQTT_ON_DISCONNECT;
            LOGV(F("MQTT_ON_CONNECT ---> MQTT_ON_DISCONNECT"));
         }
      break;

      case MQTT_SUBSCRIBE:
         if (!is_mqtt_subscribed) {
            is_mqtt_subscribed = (mqtt_client.subscribe(readable_configuration.mqtt_subscribe_topic, MQTT::QOS1, mqttRxCallback) == 0);
            is_mqtt_error = !is_mqtt_subscribed;
            LOGT(F("MQTT Subscription... [ %s ]"), is_mqtt_subscribed ? OK_STRING : FAIL_STRING);
         }

         mqtt_state = MQTT_CONSTANTDATA;
         LOGV(F("MQTT_SUBSCRIBE ---> MQTT_CONSTANTDATA"));
      break;

      case MQTT_CONSTANTDATA:

	if (!is_mqtt_constantdata) {
	  i = 0;
	  is_mqtt_constantdata = true;
	}

	// publish constant station data without retry
	if (i < readable_configuration.constantdata_count) {	  
	  //memset(full_topic_buffer, 0, MQTT_ROOT_TOPIC_LENGTH + 14 + CONSTANTDATA_BTABLE_LENGTH);
	  strncpy(full_topic_buffer, readable_configuration.mqtt_root_topic, MQTT_ROOT_TOPIC_LENGTH);	  
	  strncpy(full_topic_buffer + strlen(readable_configuration.mqtt_root_topic), "-,-,-/-,-,-,-/", 14);
	  strncpy(full_topic_buffer + strlen(readable_configuration.mqtt_root_topic)+14, readable_configuration.constantdata[i].btable, CONSTANTDATA_BTABLE_LENGTH);
	  char payload[CONSTANTDATA_BTABLE_LENGTH+9];
	  // payload is a string as default; add "" around
	  strncpy(payload,"{\"v\":\"",6);
	  strncpy(payload+6,readable_configuration.constantdata[i].value,strlen(readable_configuration.constantdata[i].value));
	  strncpy(payload+6+strlen(readable_configuration.constantdata[i].value),"\"}\0",3);
	  
	  if (mqttPublish(full_topic_buffer,payload)){
	  LOGT(F("MQTT <-- %s %s"), full_topic_buffer, payload);
	  }else{
	   LOGE(F("MQTT ERROR <-- %s %s"), full_topic_buffer, payload);
	  }
	}else{
	  mqtt_state = MQTT_CHECK;
	  LOGV(F("MQTT_CONSTANTDATA ---> MQTT_CHECK"));
	}

	i++;
	  
      break;
      
      case MQTT_CHECK:
         // ptr data is found: send data saved on sdcard
         if (!is_sdcard_error) {
            is_mqtt_processing_json = false;
            is_mqtt_processing_sdcard = true;
            is_eof_data_read = false;
            mqtt_state = MQTT_OPEN_DATA_FILE;
            LOGV(F("MQTT_CHECK ---> MQTT_OPEN_DATA_FILE"));
         }
         // ptr data is NOT found: sd card fault fallback: send last acquired sensor data
         else {
            is_mqtt_processing_json = true;
            is_mqtt_processing_sdcard = false;
            i = 0;
            mqtt_state = MQTT_SENSORS_LOOP;
            LOGV(F("MQTT_CHECK ---> MQTT_SENSORS_LOOP"));
         }
      break;

      case MQTT_SENSORS_LOOP:
         if (i < readable_configuration.sensors_count) {
            k = 0;
            data_count = jsonToMqtt(&json_sensors_data[i][0], readable_configuration.sensors[i].mqtt_topic, topic_buffer, message_buffer, (tmElements_t *) &sensor_reading_time);
            mqtt_state = MQTT_DATA_LOOP;
            LOGV(F("MQTT_SENSORS_LOOP ---> MQTT_DATA_LOOP"));
         }
         else if (is_mqtt_processing_json) {
            mqtt_state = MQTT_ON_DISCONNECT;
            LOGV(F("MQTT_SENSORS_LOOP ---> MQTT_ON_DISCONNECT"));
         }
      break;

      case MQTT_SD_LOOP:
         memset(sd_buffer, 0, MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH);
         read_bytes_count = read_data_file.read(sd_buffer, MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH);

         if (read_bytes_count == MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH) {
            sdToMqtt(sd_buffer, &topic_buffer[0][0], &message_buffer[0][0]);
            current_ptr_time_data = getDateFromMessage(&message_buffer[0][0]);

            if (current_ptr_time_data >= last_correct_ptr_time_data) {
               last_correct_ptr_time_data = current_ptr_time_data;
               mqtt_state = MQTT_DATA_LOOP;
               LOGV(F("MQTT_SD_LOOP ---> MQTT_DATA_LOOP"));
            }
         }
         // EOF: End of File
         else {
            if (last_correct_ptr_time_data > ptr_time_data) {
               ptr_time_data = last_correct_ptr_time_data;
               is_ptr_updated = true;
            }
            is_eof_data_read = true;
            mqtt_state = MQTT_PTR_FOUND;
            LOGV(F("MQTT_SD_LOOP ---> MQTT_PTR_FOUND"));
         }
      break;

      case MQTT_DATA_LOOP:
         if (k < data_count && is_mqtt_processing_json) {
            getFullTopic(full_topic_buffer, readable_configuration.mqtt_root_topic, &topic_buffer[k][0]);
            mqtt_state = MQTT_PUBLISH;
            LOGV(F("MQTT_DATA_LOOP ---> MQTT_PUBLISH"));
         }
         else if (is_mqtt_processing_sdcard) {
            getFullTopic(full_topic_buffer, readable_configuration.mqtt_root_topic, &topic_buffer[0][0]);
            mqtt_state = MQTT_PUBLISH;
            LOGV(F("MQTT_DATA_LOOP ---> MQTT_PUBLISH"));
         }
         else {
            i++;
            mqtt_state = MQTT_SENSORS_LOOP;
            LOGV(F("MQTT_DATA_LOOP ---> MQTT_SENSORS_LOOP"));
         }
      break;

      case MQTT_PUBLISH:
         is_mqtt_published_data = true;

         // mqtt json success
         if (is_mqtt_processing_json && mqttPublish(full_topic_buffer, &message_buffer[k][0])) {
            LOGT(F("MQTT <-- %s %s"), &topic_buffer[k][0], &message_buffer[k][0]);
            retry = 0;
            k++;
            mqtt_data_count++;
            mqtt_state = MQTT_DATA_LOOP;
            LOGV(F("MQTT_PUBLISH ---> MQTT_DATA_LOOP"));
         }
         // mqtt sdcard success
         else if (is_mqtt_processing_sdcard && mqttPublish(full_topic_buffer, &message_buffer[0][0])) {
            LOGT(F("MQTT <-- %s %s"), &topic_buffer[0][0], &message_buffer[0][0]);
            retry = 0;
            mqtt_data_count++;
            mqtt_state = MQTT_SD_LOOP;
            LOGV(F("MQTT_PUBLISH ---> MQTT_SD_LOOP"));
         }
         // retry
         else if ((++retry) < MQTT_RETRY_COUNT_MAX) {
            delay_ms = MQTT_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = MQTT_PUBLISH;
            mqtt_state = MQTT_WAIT_STATE;
            LOGV(F("MQTT_PUBLISH ---> MQTT_WAIT_STATE"));
         }
         // fail
         else {
            ptr_time_data = current_ptr_time_data - readable_configuration.report_seconds;
            is_ptr_updated = true;

            is_eof_data_read = true;
            is_mqtt_error = true;
            LOGE(F("MQTT publish... [ %s ]"), FAIL_STRING);

            if (is_mqtt_processing_json) {
               mqtt_state = MQTT_ON_DISCONNECT;
               LOGV(F("MQTT_PUBLISH ---> MQTT_ON_DISCONNECT"));
            }
            else if (is_mqtt_processing_sdcard) {
               mqtt_state = MQTT_CLOSE_DATA_FILE;
               LOGV(F("MQTT_PUBLISH ---> MQTT_CLOSE_DATA_FILE"));
            }
         }
      break;

      case MQTT_OPEN_DATA_FILE:
         // open the file that corresponds to the next data to send
         next_ptr_time_data = ptr_time_data + readable_configuration.report_seconds;
         sdcard_make_filename(next_ptr_time_data, file_name);

         // open file for read data
         if (sdcard_open_file(&SD, &read_data_file, file_name, O_READ)) {
            retry = 0;
            mqtt_state = MQTT_SD_LOOP;
            LOGV(F("MQTT_OPEN_DATA_FILE ---> MQTT_SD_LOOP"));
         }
         // error: file doesn't exist but if is today, end.
         else if (!is_sdcard_error && year(next_ptr_time_data) == year() && month(next_ptr_time_data) == month() && day(next_ptr_time_data) == day()) {
            mqtt_state = MQTT_PTR_UPDATE;
            LOGV(F("MQTT_OPEN_DATA_FILE ---> MQTT_PTR_UPDATE"));
         }
         // error: file doesn't exist and if it isn't today, jump to next day and search in it
         else if (!is_sdcard_error) {
            is_ptr_found = false;
            ptr_time_data = next_ptr_time_data;
            mqtt_state = MQTT_PTR_FIND;
            LOGV(F("MQTT_OPEN_DATA_FILE ---> MQTT_PTR_FIND"));
         }
         // fail
         else {
            LOGE(F("SD Card open file %s... [ FAIL ]"), file_name);
            is_sdcard_error = true;
            mqtt_state = MQTT_CHECK; // fallback
            LOGV(F("MQTT_OPEN_DATA_FILE ---> MQTT_CHECK"));
         }
         break;

      case MQTT_CLOSE_DATA_FILE:
         if (is_mqtt_processing_sdcard) {
            is_sdcard_error = !read_data_file.close();
            mqtt_state = MQTT_ON_DISCONNECT;
            LOGV(F("MQTT_CLOSE_DATA_FILE ---> MQTT_ON_DISCONNECT"));
         }
         break;

      case MQTT_ON_DISCONNECT:
         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH)
         if (is_mqtt_error) {
         #endif

            getFullTopic(full_topic_buffer, readable_configuration.mqtt_maint_topic, MQTT_STATUS_TOPIC);
            snprintf(&message_buffer[0][0], MQTT_MESSAGE_LENGTH, MQTT_ON_DISCONNECT_MESSAGE);

            if (mqttPublish(full_topic_buffer, &message_buffer[0][0]), true) {
               retry = 0;
               mqtt_state = MQTT_DISCONNECT;
               LOGV(F("MQTT_ON_DISCONNECT ---> MQTT_DISCONNECT"));
            }
            // retry
            else if ((++retry) < MQTT_RETRY_COUNT_MAX) {
               delay_ms = MQTT_DELAY_MS;
               start_time_ms = millis();
               state_after_wait = MQTT_ON_DISCONNECT;
               mqtt_state = MQTT_WAIT_STATE;
               LOGV(F("MQTT_ON_DISCONNECT ---> MQTT_WAIT_STATE"));
            }
            // fail
            else {
               LOGE(F("MQTT on disconnect publish message... [ %s ]"), FAIL_STRING);
               retry = 0;
               is_mqtt_error = true;
               mqtt_state = MQTT_DISCONNECT;
               LOGV(F("MQTT_ON_DISCONNECT ---> MQTT_DISCONNECT"));
            }

         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH)
         }
         else {
            mqtt_state = MQTT_DISCONNECT;
            LOGV(F("MQTT_ON_DISCONNECT ---> MQTT_DISCONNECT"));
         }
         #endif
      break;

      case MQTT_DISCONNECT:
         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH)
         if (is_mqtt_error) {
         #endif

         mqtt_client.disconnect();
         ipstack.disconnect();
         LOGT(F("MQTT Disconnect... [ %s ]"), OK_STRING);

         #if (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_ETH || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_ETH)
         }
         #elif (MODULE_TYPE == STIMA_MODULE_TYPE_SAMPLE_GSM || MODULE_TYPE == STIMA_MODULE_TYPE_REPORT_GSM)
         // resume GSM task for closing connection
         noInterrupts();
         if (!is_event_gsm) {
            is_event_gsm = true;
	    vTaskResume( xHandleGsm );
         }
         interrupts();
         #endif

         mqtt_state = MQTT_PTR_UPDATE;
         LOGV(F("MQTT_DISCONNECT ---> MQTT_PTR_UPDATE"));

      break;

      case MQTT_PTR_UPDATE:
         if (is_ptr_updated) {
            // set ptr 1 second more for send next data to current ptr
            ptr_time_data++;

            // success
            if (mqtt_ptr_file.seekSet(0) && mqtt_ptr_file.write(&ptr_time_data, sizeof(time_t)) == sizeof(time_t)) {
               mqtt_ptr_file.flush();
               breakTime(ptr_time_data, datetime);
               LOGN(F("Data pointer... [ %02u/%02u/%04u %02u:%02u:%02u ] [ %s ]"), datetime.Day, datetime.Month, tmYearToCalendar(datetime.Year), datetime.Hour, datetime.Minute, datetime.Second, "UPDATE");
               mqtt_state = MQTT_CLOSE_PTR_FILE;
               LOGV(F("MQTT_PTR_UPDATE ---> MQTT_CLOSE_PTR_FILE"));
            }
            // retry
            else if ((++retry) < MQTT_RETRY_COUNT_MAX) {
               delay_ms = MQTT_DELAY_MS;
               start_time_ms = millis();
               state_after_wait = MQTT_PTR_UPDATE;
               mqtt_state = MQTT_WAIT_STATE;
               LOGV(F("MQTT_PTR_UPDATE ---> MQTT_WAIT_STATE"));
            }
            // fail
            else {
               LOGE(F("SD Card writing ptr data on file %s... [ %s ]"), SDCARD_MQTT_PTR_FILE_NAME, FAIL_STRING);
               mqtt_state = MQTT_CLOSE_PTR_FILE;
               LOGV(F("MQTT_PTR_UPDATE ---> MQTT_CLOSE_PTR_FILE"));
            }
         }
         else {
            mqtt_state = MQTT_CLOSE_PTR_FILE;
            LOGV(F("MQTT_PTR_UPDATE ---> MQTT_CLOSE_PTR_FILE"));
         }
         break;

      case MQTT_CLOSE_PTR_FILE:
         mqtt_ptr_file.close();
         mqtt_state = MQTT_CLOSE_SDCARD;
         LOGV(F("MQTT_CLOSE_PTR_FILE ---> MQTT_CLOSE_SDCARD"));
         break;

      case MQTT_CLOSE_SDCARD:
         is_sdcard_error = false;
         is_sdcard_open = false;
         mqtt_state = MQTT_END;
         LOGV(F("MQTT_CLOSE_SDCARD ---> MQTT_END"));
         break;

      case MQTT_END:
         if (is_mqtt_published_data) {
            LOGN(F("[ %l ] data published through mqtt... [ %s ]"), mqtt_data_count, is_mqtt_error ? ERROR_STRING : OK_STRING);

         }

         noInterrupts();
         is_event_mqtt_paused = false;
         is_event_mqtt = false;
         interrupts();

         mqtt_state = MQTT_INIT;
         LOGV(F("MQTT_END ---> MQTT_INIT"));
	 vTaskSuspend( NULL );
      break;

      case MQTT_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            mqtt_state = state_after_wait;
         }
      break;
   }
}
#endif
