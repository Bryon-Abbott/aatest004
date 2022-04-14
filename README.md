
# Usage: 
# get_idf
# code .

# aatest001
Test aaFSM &amp; aaLED 

#aatest002
Bring in cJSON

#aatest003
Bring in mqtt
Build aaAppLed to message back and forth

mqtt://test.mosquitto.org
mqtt://mqtt.eclipseprojects.io
mqtt://192.168.100.10 # Use to Connect to PI

#aatest004 
Bring in google Protobuf (replace cJSON)

Other Items: 
Build Status_Request : App Request status from Client
Build Register_Location_Request : Client Register a Location with the broker, Return location #
Build Register_Area_Request : Client Registers an Area with the broker, give Location, Return location #
Build Register_Controller_Request : Client Registers a Controller with the Broker, give Area, Returns Area #
Build Register_Led_Request : Client Registers an Led with the Broker, gives Controller, Returns Led # 

Build "Response" transaction to indicate state 
Build Subscribe in App to set LED colour
Provide Exit Command Button in Client & App 
Improve WiFi Connect
Secure MQTT with Certificat / UserID+PW

