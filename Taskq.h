#ifndef TASKQ_H
#define TASKQ_H

#include <cstring>
#include <iostream>
#include <sys/types.h>

using namespace std;

constexpr uint8_t ENC_KEY = 0x5A;

struct TaskQ {  

    int priority;          
    int ind;               
    pid_t senderPid;       
    char topic[32];        
    char payload[256];     
    uint8_t checksum;      

    TaskQ() {}

    TaskQ(pid_t sid,
          const std::string &t,
          const std::string &pay,
          int id,
          int p = -1)
    {
        priority = p;
        senderPid = sid;
        ind = id;

        strncpy(topic, t.c_str(), sizeof(topic));
        topic[sizeof(topic) - 1] = '\0';

        strncpy(payload, pay.c_str(), sizeof(payload));
        payload[sizeof(payload) - 1] = '\0';

       
        checksum = xorChecksum(payload);

        xorCrypt(payload);
    }

    static void xorCrypt(char* data) {
        for (int i = 0; data[i] != '\0'; i++) {
            data[i] ^= ENC_KEY;
        }
    }

    static uint8_t xorChecksum(const char* data) {
        uint8_t cs = 0;
        for (int i = 0; data[i]; i++) {
            cs ^= (uint8_t)data[i];
        }
        return cs;
    }

    bool decryptAndVerify() {
        xorCrypt(payload);   

        uint8_t cs = xorChecksum(payload);
        return (cs == checksum);
    }
};

#endif 
