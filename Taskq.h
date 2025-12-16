#ifndef taskq
#define taskq
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>   
#include <unistd.h>
using namespace std;

struct TaskQ { // For message queue
    int priority;
    int ind;
    bool cs;
    pid_t senderPid;
    char topic[300];
    char payload[300];
    uint8_t checksum;
 
    TaskQ() {}
    TaskQ(pid_t sid,
      const std::string &t,
      const std::string &pay,
      int id,
      bool b,
      int p = -1)
{
    // 🔑 FIX 1: zero-initialize entire struct
    memset(this, 0, sizeof(TaskQ));

    senderPid = sid;
    ind       = id;
    cs        = b;
    priority  = p;

    // 🔑 FIX 2: safe copy + termination
    strncpy(topic, t.c_str(), sizeof(topic) - 1);
    topic[sizeof(topic) - 1] = '\0';

    strncpy(payload, pay.c_str(), sizeof(payload) - 1);
    payload[sizeof(payload) - 1] = '\0';

    // 🔑 FIX 3: checksum on PLAIN data
    checksum = xorChecksum(topic) ^ xorChecksum(payload);

    // 🔑 FIX 4: encrypt only AFTER checksum
    xorEncrypt(topic, sizeof(topic));
    xorEncrypt(payload, sizeof(payload));
}

    // XOR encryption/decryption
    void xorEncrypt(char* data, size_t size) {
       uint8_t ENC_KEY = 0x5A; 
        for (size_t i = 0; i < size && data[i] != '\0'; i++) {
            data[i] ^= ENC_KEY;
        }
    }

    uint8_t xorChecksum(const char* data) const {
        uint8_t cs = 0;
        for (int i = 0; data[i]; i++) {
            cs ^= (uint8_t)data[i];
        }
        return cs;
    }
};

#endif
