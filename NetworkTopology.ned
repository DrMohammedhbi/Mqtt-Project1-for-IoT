

network IoTMQTTNetwork
{
    parameters:
        int numDevices = default(5);
        @display("bgb=732,366");
    submodules:
        devices[numDevices]: IoTDevice {
            parameters:
                deviceId = "device" + string(index);
                @display("p=90,61,ri,100,100;i=old/handset1");
        }
        broker: MQTTBroker {
            parameters:
                //                numClients = numDevices + 1;
                numClients = parent.numDevices + 1;
                @display("p=401,183;i=block/join");
        }
        server: MLServer {
            @display("p=617,128;i=device/mainframe");
        }
    connections:
        for i=0..numDevices-1 {
            devices[i].out --> broker.in++;
        }
        broker.out++ --> server.in;
}
