#include <omnetpp.h>
#include "MQTTMessage_m.h"

using namespace omnetpp;

class IoTDevice : public cSimpleModule
{
  private:
    cMessage *sendTimer;
    std::string deviceId;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  public:
    IoTDevice();
    virtual ~IoTDevice();
};

Define_Module(IoTDevice);

IoTDevice::IoTDevice()
{
    sendTimer = nullptr;
}

IoTDevice::~IoTDevice()
{
    cancelAndDelete(sendTimer);
}

void IoTDevice::initialize()
{
    deviceId = par("deviceId").stdstringValue();
    sendTimer = new cMessage("sendTimer");
    scheduleAt(simTime() + par("sendInterval"), sendTimer);
}

void IoTDevice::handleMessage(cMessage *msg)
{
    if (msg == sendTimer) {
        // Generate sensor data
        double sensorData = uniform(0, 100);

        // Create and send MQTT message
        MQTTMessage *mqttMsg = new MQTTMessage("sensorData");
//        mqttMsg->setTopic("sensor/" + deviceId);
        mqttMsg->setTopic(("sensor/" + deviceId).c_str());
//        mqttMsg->setPayload(std::to_string(sensorData));
        mqttMsg->setPayload(std::to_string(sensorData).c_str());
        send(mqttMsg, "out");

        EV << "Device " << deviceId << " sent data: " << sensorData << endl;

        // Schedule next send
        scheduleAt(simTime() + par("sendInterval"), sendTimer);
    }
}
