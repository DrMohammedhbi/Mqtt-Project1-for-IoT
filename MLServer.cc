#include <omnetpp.h>
#include "MQTTMessage_m.h"

using namespace omnetpp;

class MLServer : public cSimpleModule
{
  private:
    simsignal_t dataProcessedSignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(MLServer);

void MLServer::initialize()
{
    dataProcessedSignal = registerSignal("dataProcessed");
}

void MLServer::handleMessage(cMessage *msg)
{
    MQTTMessage *mqttMsg = check_and_cast<MQTTMessage *>(msg);

    // Extract sensor data
    std::string topic = mqttMsg->getTopic();
    double sensorData = std::stod(mqttMsg->getPayload());

    // Simulate ML processing
    simtime_t processingTime = par("processingTime");
    scheduleAt(simTime() + processingTime, new cMessage("processingComplete"));

    // Log the received data
    EV << "Received sensor data from " << topic << ": " << sensorData << endl;

    // Emit signal for statistics collection
    emit(dataProcessedSignal, sensorData);

    delete mqttMsg;
}
