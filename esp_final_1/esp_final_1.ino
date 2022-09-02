#include <ESP8266WiFi.h>
#include <espnow.h>

//#include <Adafruit_Sensor.h>
//#include <DHT.h>

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress1[] = {0xBC, 0xDD, 0xC2, 0x9E, 0x11, 0x81};
uint8_t broadcastAddress2[] = {0x18, 0xFE, 0x34, 0xA3, 0x64, 0xFB};
uint8_t broadcastAddress3[] = {0xDC, 0x4F, 0x22, 0x0A, 0x85, 0xD5};

// Digital pin connected to the DHT sensor
//#define DHTPIN 5    

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

//DHT dht(DHTPIN, DHTTYPE);

// Define variables to store DHT readings to be sent
class ran{
  public:
  ran(){};
  int temperature(int temp){
    temp=random(9);
    return temp;
    }
  int humidity(int hum){
    hum=random(10,20);
    return hum;
    }
  };
  

int temperature;
int humidity;

// Define variables to store incoming readings
int incomingTemp;
int incomingHum;

// Updates DHT readings every 5seconds
const long interval = 5000; 
unsigned long previousMillis = 0;    // will store last time DHT was updated 

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int id;
    int temp;
    int hum;
} struct_message;

// Create a struct_message called DHTReadings to hold sensor readings
struct_message DHTReadings;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

struct_message board1;

struct_message board2;
struct_message board3;

// Create an array with all the structures
struct_message boardsStruct[3] = {board1, board2, board3};

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  
  Serial.print("Last Packet Send Status: ");
  
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  boardsStruct[incomingReadings.id-1].temp = incomingReadings.temp;
  boardsStruct[incomingReadings.id-1].hum = incomingReadings.hum;
  Serial.printf("temp value: %d \n", boardsStruct[incomingReadings.id-1].temp);
  Serial.printf("hum value: %d \n", boardsStruct[incomingReadings.id-1].hum);
  Serial.println(WiFi.macAddress());
  Serial.println();
}

void getReadings(){
  // Read Temperature
  ran ra;
  temperature=0;
  temperature = ra.temperature(temperature);
  Serial.print("Sending Temp value : ");
  Serial.println(temperature);
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = r.readTemperature(true);
  if (isnan(temperature)){
    Serial.println("Failed to read from DHT");
    temperature = 0.0;
  }
  humidity=0;
  humidity = ra.humidity(humidity);
  Serial.print("Sending Humidity value : ");
  Serial.println(humidity);
  if (isnan(humidity)){
    Serial.println("Failed to read from DHT");
    humidity = 0.0;
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  

  // Init DHT sensor
  //dht.begin();
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_add_peer(broadcastAddress2, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  unsigned long currentMillis = millis();         //Number of milliseconds passed since the program started. Data type: unsigned long
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;

    //Get DHT readings
    getReadings();

    //Set values to send
    DHTReadings.temp = temperature;
    DHTReadings.hum = humidity;
    Serial.println(WiFi.macAddress());

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress1, (uint8_t *) &DHTReadings, sizeof(DHTReadings));
    esp_now_send(broadcastAddress2, (uint8_t *) &DHTReadings, sizeof(DHTReadings));

  }
}
