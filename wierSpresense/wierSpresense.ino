#include <Arduino.h>
#include <pins_arduino.h>

#include <Camera.h>
#include <File.h>
#include <SDHCI.h>
#include <RTC.h>

#include <stdio.h> /* for sprintf() */
#include <string.h>

#include <GNSS.h>
#include <GNSSPositionData.h>
#include <gpsutils/cxd56_gnss_nmea.h>
#include "QZQSM_EN.h"

// ===========================================
// * ESP8266
#include "ESP8266.h"

#define SSID "YuPiTeam"
#define PASSWORD "12345678"
#define HOST_NAME "192.168.4.3"
#define HOST_PORT_SECTION (5000)
#define HOST_PORT_SATT (5002)
#define HOST_PORT_CAPTURE (5003)
#define HOST_PORT_LOCATION (5004)

ESP8266 wifi;
// ===========================================

#define GNSS_TIMEOUT (3000)
#define GNSS_INTERVAL_TIME (1)
#define SERIAL_BAUDRATE (115200)
#define FILENAME_LEN (128)
#define STRING_BUFFER_SIZE (1000)
#define DC_HISTORY_COUNT (20)  // DC Report Array Length

#define LOG_INTERVAL_MIN (1)   // SD card logging time interval (minute)
#define DCR_INTERVAL_SEC (15)  // SD card text dc report interval (sec)

/* Global Instances */

static SDClass SD;          /* SDClass object */
static File fileObjHandle;  /* File Object */
static CamErr camerrHandle; /* Camera Error Handler Object */
static CamImage img;        /* Captured Image Handler Object */
// theCamera                /* Camera Handle, extern from Camera.h */

static SpGnss Gnss;                       /* Spresense GNSS device handler object */
static SpNavData NavData;                 /* GNSS data handler object */
static QZQSM dc_report[DC_HISTORY_COUNT]; /* QZQSM report table */
static RtcTime now;                       /* local time */

char filename[FILENAME_LEN] = { 0 };
int dc_report_index = 0;

bool location_flag = 0;   // gps location data indicator, 0:unknown, 1:known
bool localtime_flag = 0;  // RTC-UTC sync flag
bool report_flag = 0;
bool newfile_flag = 0;
bool reponse_flag = 0;

int mainboard_start_min = 0;  // time trigger for logging event

// ===========================================
// * ESP8266
void esp8266Report(String addr, uint32_t port, const uint8_t *payload, uint32_t payloadLength) {
  //uint8_t buffer[128] = { 0 };

  if (wifi.createTCP(addr, port)) {
    Serial.print("create tcp ok\r\n");

    wifi.send(payload, payloadLength);

    if (wifi.releaseTCP()) {
      Serial.print("release tcp ok\r\n");
    } else {
      Serial.print("release tcp err\r\n");
    }

  } else {
    Serial.print("create tcp err\r\n");
  }
}
// ===========================================

/* ====================================================== */
/* Supporting Functions */

/* Camera Functions */
void camPrintError(enum CamErr err) {
  Serial.print("Error: ");
  switch (err) {
    case CAM_ERR_NO_DEVICE:
      Serial.println("No Device");
      break;
    case CAM_ERR_ILLEGAL_DEVERR:
      Serial.println("Illegal device error");
      break;
    case CAM_ERR_ALREADY_INITIALIZED:
      Serial.println("Already initialized");
      break;
    case CAM_ERR_NOT_INITIALIZED:
      Serial.println("Not initialized");
      break;
    case CAM_ERR_NOT_STILL_INITIALIZED:
      Serial.println("Still picture not initialized");
      break;
    case CAM_ERR_CANT_CREATE_THREAD:
      Serial.println("Failed to create thread");
      break;
    case CAM_ERR_INVALID_PARAM:
      Serial.println("Invalid parameter");
      break;
    case CAM_ERR_NO_MEMORY:
      Serial.println("No memory");
      break;
    case CAM_ERR_USR_INUSED:
      Serial.println("Buffer already in use");
      break;
    case CAM_ERR_NOT_PERMITTED:
      Serial.println("Operation not permitted");
      break;
    default:
      break;
  }
}

void camActivate() {

  Serial.print("CAM: Initializing theCamera ...");
  camerrHandle = theCamera.begin();
  if (camerrHandle != CAM_ERR_SUCCESS) {
    camPrintError(camerrHandle);
  }
  Serial.println("CAM: Begin()");

  Serial.println("CAM: Start streaming");
  camerrHandle = theCamera.startStreaming(true, camCallback);
  if (camerrHandle != CAM_ERR_SUCCESS) {
    camPrintError(camerrHandle);
  }
  /* Auto white balance configuration */
  Serial.println("CAM: Set Auto white balance parameter");
  camerrHandle = theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_DAYLIGHT);
  if (camerrHandle != CAM_ERR_SUCCESS) {
    camPrintError(camerrHandle);
  }

  /* Set parameters about still picture. */
  Serial.println("CAM: Set still picture format");
  camerrHandle = theCamera.setStillPictureImageFormat(
    CAM_IMGSIZE_QUADVGA_H,
    CAM_IMGSIZE_QUADVGA_V,
    CAM_IMAGE_PIX_FMT_JPG);

  if (camerrHandle != CAM_ERR_SUCCESS) {
    camPrintError(camerrHandle);
  }
  Serial.println("CAM: OK");
}

void camDeactivate() {
  Serial.print("CAM: Deactivating camera ..");
  theCamera.end();
  Serial.println("done.");
}

// for mainboard status led
void reponseLED() {
  if (reponse_flag) {
    ledOff(PIN_LED3);
    reponse_flag = !reponse_flag;
  } else {
    ledOn(PIN_LED3);
    reponse_flag = !reponse_flag;
  }
}

void camCapture() {
  Serial.print("CAM: theCamera call takePicture()");
  img = theCamera.takePicture();  // output image store in img
  Serial.println(" .. done.");
}

void camCallback(CamImage img) {

  /* Check the img instance is available or not. */
  if (img.isAvailable()) {

    /* If you want RGB565 data, convert image data format to RGB565 */
    img.convertPixFormat(CAM_IMAGE_PIX_FMT_JPG);

    img.getImgSize();
    img.getImgBuff();
  } else {
    Serial.println("Failed to get video stream image");
  }
}

// save current img to filename path
void saveImg(char *filename_) {
  if (!(img.isAvailable())) {
    Serial.println("Error in saveImg: image not avaiable");
    return;
  }
  Serial.println("IMG: Saving image ..");
  fileObjHandle = SD.open(filename_, FILE_WRITE);
  fileObjHandle.write(img.getImgBuff(), img.getImgSize());
  fileObjHandle.close();
  Serial.println("IMG: Image saved.");
}

// save data to text file at filename path
void saveText(char *filename_, char *data) {
  fileObjHandle = SD.open(filename_, FILE_WRITE);
  if (fileObjHandle) {
    Serial.print("TXT: Writing text file ... ");
    fileObjHandle.println(data);
    /* Close the file */
    fileObjHandle.close();
    Serial.println("TXT: text logging done.");
  } else {
    /* If the file didn't open, print an error */
    Serial.println("TXT: error opening text file");
  }
}

/* Satellite Location and Time */

// output UTC Date and Time: OK
String getSatUTCDatetime(SpNavData *pNavData) {
  char StringBuffer[STRING_BUFFER_SIZE] = { 0 };
  snprintf(StringBuffer, STRING_BUFFER_SIZE, "%04d_%02d_%02d_%02d_%02d_%02d",
           pNavData->time.year,
           pNavData->time.month,
           pNavData->time.day,
           pNavData->time.hour,
           pNavData->time.minute,
           pNavData->time.sec);

  return String(StringBuffer);
}

// gps location data: OK
String getSatLocation(SpNavData *pNavData) {
  char StringBuffer[STRING_BUFFER_SIZE] = { 0 };

  if (pNavData->posDataExist == 0) {
    // Serial.println("Location: Unknown");
    location_flag = 0;
    snprintf(StringBuffer, STRING_BUFFER_SIZE, "%s", "Location: Unknown ");
  } else {
    location_flag = 1;
    snprintf(StringBuffer, STRING_BUFFER_SIZE, "Location: Latitude %06f Longitude %06f",
             pNavData->latitude, pNavData->longitude);
  }
  return String(StringBuffer);
}

// Adjust RTC using Satellite UTC, Bangkok Time: OK
String getSatRTCDateTime(SpNavData *pNavData) {
  char StringBuffer[STRING_BUFFER_SIZE] = { 0 };
  SpGnssTime *time = &NavData.time;
  if (time->year >= 2000) {
    RtcTime gps(time->year, time->month, time->day,
                time->hour, time->minute, time->sec, time->usec * 1000);

    gps += 7 * 60 * 60;  // Convert UTC to Bangkok time

    // Compare with the current time
    now = RTC.getTime();
    int diff = now - gps;
    if (abs(diff) >= 1) {
      RTC.setTime(gps);
    }

    snprintf(StringBuffer, STRING_BUFFER_SIZE, "%04d_%02d_%02d_%02d_%02d_%02d",
             now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());

    localtime_flag = 1;
  } else {
    localtime_flag = 0;
  }
  return String(StringBuffer);
}

/* Satellite Decoded DC Report */  //OK
String getDCContent() {
  char StringBuffer[STRING_BUFFER_SIZE] = { 0 };
  // Get DC reoprt
  void *handle = Gnss.getDCReport();
  if (handle) {
    QZQSM report;
    now = RTC.getTime();
    report.SetYear(now.year());

    report.Decode(((struct cxd56_gnss_dcreport_data_s *)handle)->sf);

    int reported = 0;
    int i;
    // Check for new report in the history record
    for (i = 0; i < DC_HISTORY_COUNT; i++) {
      if (dc_report[i] == report) {
        reported = 1;
        break;
      }
    }
    // new report detected
    if (!reported) {
      /* New DC report receive, then put it in the StringBuffer */
      snprintf(StringBuffer, STRING_BUFFER_SIZE, "%s", report.GetReport());
      dc_report[dc_report_index] = report;
      dc_report_index++;
      dc_report_index %= DC_HISTORY_COUNT;
    }
  }
  //Serial.print(StringBuffer);
  return String(StringBuffer);
}

/* ====================================================== */
// Mainboard Initialization ..
void setup() {
  /* Initialize Serial */
  Serial.begin(SERIAL_BAUDRATE);
  // ===========================================
  // * ESP8266
  wifi.begin(Serial2, 115200);

  Serial.print("Esp8266 FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.setSoftAPParam(SSID, PASSWORD)) {
    Serial.print("Create AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Create AP failure\r\n");
  }

  // ===========================================

  /* Demo Button : LTE Extension Board: D03 */
  pinMode(PIN_D03, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(PIN_D03), ISRfn, RISING);

  /* Initialize GNSS, Activate GNSS hardware */
  /* ======================================= */
  if (Gnss.begin()) {
    Serial.println("GNSS initialization error!");
  }
  // de-activate GNSS Gnss.end();

  /* select satellite system */
  Gnss.select(GPS);  //Gnss.select(GLONASS);
  Gnss.select(QZ_L1CA);
  Gnss.select(QZ_L1S);  //Gnss.select(SBAS);

  /* set interval */
  Gnss.setInterval(GNSS_INTERVAL_TIME);
  if (Gnss.start(COLD_START)) {
    Serial.println("GNSS COLD start error!");
  } else {
    Serial.println("GNSS COLD Start OK");
  }

  /* Initialize SDHCI  */
  /* ======================================= */
  Serial.print("Initializing SD card ...");
  while (!SD.begin()) {
    ; /* wait until SD card is mounted. */
  }
  Serial.println(" SD card mounted.. done.");

  /* Initialize Camera */
  /* ======================================= */
  camActivate();

  /* First run parameter */
  /* ======================================= */
  Serial.println("Assigning First run parameters ... ");
  if (Gnss.waitUpdate(GNSS_TIMEOUT)) {
    Gnss.getNavData(&NavData);  // blocking
  }
  mainboard_start_min = NavData.time.minute;
  Serial.print("Mainboard Start min = ");
  Serial.println(mainboard_start_min);
  location_flag = 0;
  localtime_flag = 0;
  newfile_flag = 1;
  report_flag = 0;
  Serial.println("\nAll setup done.\n");
  Serial.println("\n\n");
}

void loop() {

  //static int last_sec = 0;
  static int last_min = 0;
  static int last_hour = 0;
  static String filename_image;
  static String filename_report;
  static char dc_data[STRING_BUFFER_SIZE] = { 0 };

  if (Gnss.waitUpdate(GNSS_TIMEOUT)) {
    reponseLED();
    Gnss.getNavData(&NavData);
  }

  getSatRTCDateTime(&NavData);
  if (!localtime_flag) {
    ledOn(PIN_LED0);
  } else {
    ledOff(PIN_LED0);
  }

  // 1-hour interval
  if (NavData.time.hour != last_hour) {
    last_hour = NavData.time.hour;
  }

  // 1-min interval
  if (NavData.time.minute != last_min) {
    last_min = NavData.time.minute;
    newfile_flag = 1;  // different minute allow newfile to be create
  } else {
    // within same minute, disable newfile_flag
    if (newfile_flag && report_flag) {
      newfile_flag = 0;
    }
  }

  if (report_flag) {
    ledOn(PIN_LED1);
  } else {
    ledOff(PIN_LED1);
  }

  if (newfile_flag) {
    ledOn(PIN_LED2);
  } else {
    ledOff(PIN_LED2);
  }


  // DCR_INTERVAL_SEC-sec interval
  if ((NavData.time.sec % DCR_INTERVAL_SEC == 0) && report_flag) {
    Serial.println("Enter DC logging interval");
    String temp_ = getDCContent();
    Serial.println(temp_);
    int temp_len = temp_.length();
    if (temp_len >= 2) {
      Serial.print("DC interval log data length: ");
      Serial.println(temp_len);
      strcpy(filename, filename_report.c_str());
      strcpy(dc_data, temp_.c_str());
      saveText(filename, dc_data);
      Serial.println("DC Logging on SD ...ok");
      // ===========================================
      // * ESP8266
      esp8266Report(HOST_NAME, HOST_PORT_SATT, (const uint8_t *)dc_data, strlen(dc_data));
      // ===========================================
    }
  }

  // SD card writting section
  if ((((NavData.time.minute + mainboard_start_min) % LOG_INTERVAL_MIN) == 0) && localtime_flag && newfile_flag) {
    Serial.println("Enter Newfile section: NF");
    String temp_ = getSatRTCDateTime(&NavData);  // datetime as a filename
    // ===========================================
    // * ESP8266
    esp8266Report(HOST_NAME, HOST_PORT_SECTION, (const uint8_t *)temp_.c_str(), temp_.length());
    // ===========================================
    Serial.println(temp_);
    //String temp_ = getSatUTCDatetime(&NavData);
    // capture & save image
    camCapture();
    sleep(1);
    filename_image = "image_" + temp_ + ".jpg";
    strcpy(filename, filename_image.c_str());
    saveImg(filename);

    // ===========================================
    // * ESP8266
    esp8266Report(HOST_NAME, HOST_PORT_CAPTURE, (const uint8_t *)img.getImgBuff(), img.getImgSize());
    // ===========================================
    camCapture();  // discard img buffer, current bug
    Serial.println("NF: Image created.");

    // create a new report
    filename_report = "report_" + temp_ + ".txt";
    strcpy(filename, filename_report.c_str());
    strcpy(dc_data, temp_.c_str());
    saveText(filename, dc_data);
    strcpy(dc_data, getSatLocation(&NavData).c_str());
    // ===========================================
    // * ESP8266
    esp8266Report(HOST_NAME, HOST_PORT_LOCATION, (const uint8_t *)dc_data, strlen(dc_data));
    // ===========================================
    Serial.println(dc_data);
    saveText(filename, dc_data);
    Serial.println("Report created");

    report_flag = 1;  // enable report
  }
}
