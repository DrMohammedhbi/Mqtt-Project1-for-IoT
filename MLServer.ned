 
simple MLServer
{
    parameters:
        double processingTime @unit(s) = default(0.1s);
    gates:
        input in;
}