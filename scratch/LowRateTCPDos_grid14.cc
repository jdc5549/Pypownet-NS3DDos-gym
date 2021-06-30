/*
 * LICENSE : GNU General Public License v3.0 (https://github.com/Saket-Upadhyay/ns3-cybersecurity-simulations/blob/master/LICENSE)
 * REPOSITORY : https://github.com/Saket-Upadhyay/ns3-cybersecurity-simulations
 * =================================================================================
 *
 * Modified from : https://github.com/samvid25/Low-Rate-TCP-DoS-Attack/pull/1
 *      - Added NetAnim Animation Support
 */

// The Topology contains 5 nodes as follows:
// 0 -> alice (sender)
// 1 -> eve (attacker)
// 2 -> switch (common switch between alice and eve)
// 3 -> switch (switch conneced to bob)
// 4 -> bob (receiver)
/*
   n1
      \ pp1 (100 Mbps, 2ms RTT)
       \
        \             -> pp1 (100 Mbps, 2ms RTT)
         \            |
          n2 ---- n3 ---- n4
         /    |
        /     -> pp2 (1.5 Mbps, 40ms RTT)
       /
      / pp1 (100 Mbps, 2ms RTT)
   n0

 ## NetAnimator Support
 This will create a LowRateTCPDoSAnim.xml . Which can be parsed in NetAnim. for graphical simulation of the attack.

*/

#include "ns3/mobility-module.h"
#include "ns3/nstime.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

#define TCP_SINK_PORT 9000
#define UDP_SINK_PORT 9001

//parameters to change
#define BULK_SEND_MAX_BYTES 2097152
#define ATTACKER_DoS_RATE "20480kb/s"
#define MAX_SIMULATION_TIME 30.0
#define NUMBER_OF_BOTS 10


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TcpHighRateDoSAttack");

int main(int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    NodeContainer nodes;
    nodes.Create(14);


    // Define the Point-To-Point Links (Helpers) and their Paramters
    PointToPointHelper pp1, pp2;
    pp1.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
    pp1.SetChannelAttribute("Delay", StringValue("1ms"));

    pp2.SetDeviceAttribute("DataRate", StringValue("1.5Mbps"));
    pp2.SetChannelAttribute("Delay", StringValue("20ms"));

    // Install the Point-To-Point Connections between Nodes
    NetDeviceContainer d01, d04, d12, d13, d14, d23, d34, d36, d38, d45, d510, d511, d512, d67, d68, d89, d813, d910, d1112, d1213;
    d01 = pp1.Install(nodes.Get(0), nodes.Get(1));
    d04 = pp1.Install(nodes.Get(0), nodes.Get(4));
    d12 = pp1.Install(nodes.Get(1), nodes.Get(2));
    d13 = pp1.Install(nodes.Get(1), nodes.Get(3));
    d14 = pp1.Install(nodes.Get(1), nodes.Get(4));
    d23 = pp1.Install(nodes.Get(2), nodes.Get(3));
    d34 = pp1.Install(nodes.Get(3), nodes.Get(4));
    d36 = pp1.Install(nodes.Get(3), nodes.Get(6));
    d38 = pp1.Install(nodes.Get(3), nodes.Get(8));
    d45 = pp1.Install(nodes.Get(4), nodes.Get(5));
    d510 = pp1.Install(nodes.Get(5), nodes.Get(10));
    d511 = pp1.Install(nodes.Get(5), nodes.Get(11));
    d512 = pp1.Install(nodes.Get(5), nodes.Get(12));
    d67 = pp1.Install(nodes.Get(6), nodes.Get(7));
    d68 = pp1.Install(nodes.Get(6), nodes.Get(8));
    d89 = pp1.Install(nodes.Get(8), nodes.Get(9));
    d813 = pp1.Install(nodes.Get(8), nodes.Get(13));
    d910 = pp1.Install(nodes.Get(9), nodes.Get(10));
    d1112 = pp1.Install(nodes.Get(11), nodes.Get(12));
    d1213 = pp1.Install(nodes.Get(12), nodes.Get(13));


    Ipv4AddressHelper a01, a04, a12, a13, a14, a23, a34, a36, a38, a45, a510, a511, a512, a67, a68, a89, a813, a910, a1112, a1213;
    a01.SetBase("10.1.1.0", "255.255.255.0");
    a04.SetBase("10.1.2.0", "255.255.255.0");
    a12.SetBase("10.1.3.0", "255.255.255.0");
    a13.SetBase("10.1.4.0", "255.255.255.0");
    a14.SetBase("10.1.5.0", "255.255.255.0");
    a23.SetBase("10.1.6.0", "255.255.255.0");
    a34.SetBase("10.1.7.0", "255.255.255.0");
    a36.SetBase("10.1.8.0", "255.255.255.0");
    a38.SetBase("10.1.9.0", "255.255.255.0");
    a45.SetBase("10.1.10.0", "255.255.255.0");
    a510.SetBase("10.1.11.0", "255.255.255.0");
    a511.SetBase("10.1.12.0", "255.255.255.0");
    a512.SetBase("10.1.13.0", "255.255.255.0");
    a67.SetBase("10.1.14.0", "255.255.255.0");
    a68.SetBase("10.1.15.0", "255.255.255.0");
    a89.SetBase("10.1.16.0", "255.255.255.0");
    a813.SetBase("10.1.17.0", "255.255.255.0");
    a910.SetBase("10.1.18.0", "255.255.255.0");
    a1112.SetBase("10.1.19.0", "255.255.255.0");
    a1213.SetBase("10.1.20.0", "255.255.255.0");

    Ipv4InterfaceContainer i01, i04, i12, i13, i14, i23, i34, i36, i38, i45, i510, i511, i512, i67, i68, i89, i813, i910, i1112, i1213;
    i01 = a01.Assign(d01);
    i04 = a04.Assign(d04);
    i12 = a12.Assign(d12);
    i13 = a13.Assign(d13);
    i14 = a14.Assign(d14);
    i23 = a23.Assign(d23);
    i34 = a34.Assign(d34);
    i36 = a36.Assign(d36);
    i38 = a38.Assign(d38);
    i45 = a45.Assign(d45);
    i510 = a510.Assign(d510);
    i511 = a511.Assign(d511);
    i512 = a512.Assign(d512);
    i67 = a67.Assign(d67);
    i68 = a68.Assign(d68);
    i89 = a89.Assign(d89);
    i813 = a813.Assign(d813);
    i910 = a910.Assign(d910);
    i1112 = a1112.Assign(d1112);
    i1213 = a1213.Assign(d1213);


    //Attacker application
    OnOffHelper onoff("ns3::UdpSocketFactory", Address(InetSocketAddress(i67.GetAddress(1), UDP_SINK_PORT)));
    onoff.SetConstantRate(DataRate(ATTACKER_DoS_RATE));
    onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=30]"));
    onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    ApplicationContainer onOffApp = onoff.Install(nodes.Get(10));
    onOffApp.Start(Seconds(0.0));
    onOffApp.Stop(Seconds(MAX_SIMULATION_TIME));

    // Sender Application (Packets generated by this application are throttled)
    BulkSendHelper bulkSend("ns3::TcpSocketFactory", InetSocketAddress(i67.GetAddress(1), TCP_SINK_PORT));
    bulkSend.SetAttribute("MaxBytes", UintegerValue(BULK_SEND_MAX_BYTES));

    ApplicationContainer bulkSendApp0 = bulkSend.Install(nodes.Get(0));
    bulkSendApp0.Start(Seconds(0.0));
    bulkSendApp0.Stop(Seconds(MAX_SIMULATION_TIME - 10));

    // ApplicationContainer bulkSendApp1 = bulkSend.Install(nodes.Get(1));
    // bulkSendApp1.Start(Seconds(0.0));
    // bulkSendApp1.Stop(Seconds(MAX_SIMULATION_TIME - 10));

    // ApplicationContainer bulkSendApp2 = bulkSend.Install(nodes.Get(2));
    // bulkSendApp2.Start(Seconds(0.0));
    // bulkSendApp2.Stop(Seconds(MAX_SIMULATION_TIME - 10));

    // ApplicationContainer bulkSendApp3 = bulkSend.Install(nodes.Get(3));
    // bulkSendApp3.Start(Seconds(0.0));
    // bulkSendApp3.Stop(Seconds(MAX_SIMULATION_TIME - 10));

    // ApplicationContainer bulkSendApp4 = bulkSend.Install(nodes.Get(4));
    // bulkSendApp4.Start(Seconds(0.0));
    // bulkSendApp4.Stop(Seconds(MAX_SIMULATION_TIME - 10));

    // ApplicationContainer bulkSendApp5 = bulkSend.Install(nodes.Get(5));
    // bulkSendApp5.Start(Seconds(0.0));
    // bulkSendApp5.Stop(Seconds(MAX_SIMULATION_TIME - 10));


    // ApplicationContainer bulkSendApp8 = bulkSend.Install(nodes.Get(8));
    // bulkSendApp8.Start(Seconds(0.0));
    // bulkSendApp8.Stop(Seconds(MAX_SIMULATION_TIME - 10));

    // ApplicationContainer bulkSendApp9 = bulkSend.Install(nodes.Get(9));
    // bulkSendApp9.Start(Seconds(0.0));
    // bulkSendApp9.Stop(Seconds(MAX_SIMULATION_TIME - 10));

    // ApplicationContainer bulkSendApp10 = bulkSend.Install(nodes.Get(10));
    // bulkSendApp10.Start(Seconds(0.0));
    // bulkSendApp10.Stop(Seconds(MAX_SIMULATION_TIME - 10));




    //UDPSink on receiver side (Only for analysis purpose)
    PacketSinkHelper UDPsink("ns3::UdpSocketFactory",
                             Address(InetSocketAddress(Ipv4Address::GetAny(), UDP_SINK_PORT)));
    ApplicationContainer UDPSinkApp = UDPsink.Install(nodes.Get(7));
    UDPSinkApp.Start(Seconds(0.0));
    UDPSinkApp.Stop(Seconds(MAX_SIMULATION_TIME));

    // TCP Sink Application on receviver side
    PacketSinkHelper TCPsink("ns3::TcpSocketFactory",
                             InetSocketAddress(Ipv4Address::GetAny(), TCP_SINK_PORT));
    ApplicationContainer TCPSinkApp7 = TCPsink.Install(nodes.Get(7));
    TCPSinkApp7.Start(Seconds(0.0));
    TCPSinkApp7.Stop(Seconds(MAX_SIMULATION_TIME));


    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // pp1.EnablePcapAll("PCAPs/tcplow");

    //Simulation NetAnim
    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX", DoubleValue(0.0), "MinY", DoubleValue(0.0), "DeltaX", DoubleValue(5.0), "DeltaY", DoubleValue(10.0),
                                  "GridWidth", UintegerValue(5), "LayoutType", StringValue("RowFirst"));

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

    mobility.Install(nodes);

    AnimationInterface anim("LowRateDDoSTcp_grid14.xml");

    ns3::AnimationInterface::SetConstantPosition(nodes.Get(0), -280, 81);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(1), -100, 270);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(2), 366, 270);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(3), 366, 54);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(4), -64, 54);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(5), -64, -54);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(6), 366, 0);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(7), 438, 0);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(8), 326, -54);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(9), 222, -108);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(10), 79, -162);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(11), -152, -270);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(12), -64, -270);
    ns3::AnimationInterface::SetConstantPosition(nodes.Get(13), 222, -216);

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}