simple IoTDevice
{
    parameters:
        string deviceId;
        double sendInterval @unit(s) = default(1s);
        double baseTemperature @unit(celsius) = default(20celsius);
        double temperatureVariation @unit(celsius) = default(5celsius);
    gates:
        output out;
}