#include <omnetpp.h>
#include "MQTTMessage_m.h"
#include <map>
#include <vector>

using namespace omnetpp;

class MQTTBroker : public cSimpleModule
{
  private:
    std::map<std::string, std::vector<int>> subscriptions;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(MQTTBroker);

void MQTTBroker::initialize()
{
    int numClients = par("numClients");
    // Initialize subscriptions (for simplicity, we'll assume the server is always subscribed to all topics)
    subscriptions["sensor/#"].push_back(gateSize("out") - 1);

}

void MQTTBroker::handleMessage(cMessage *msg)
{
    MQTTMessage *mqttMsg = check_and_cast<MQTTMessage *>(msg);
    std::string topic = mqttMsg->getTopic();

    EV << "Broker received message on topic: " << topic << endl;

    // Forward the message to all subscribed clients
    for (const auto &sub : subscriptions) {
        if (topic.find(sub.first) == 0) {
            for (int gateIndex : sub.second) {
                MQTTMessage *fwdMsg = mqttMsg->dup();
                send(fwdMsg, "out", gateIndex);
                EV << "Broker forwarded message to gate: " << gateIndex << endl;
            }
        }
    }

    delete mqttMsg;
}
