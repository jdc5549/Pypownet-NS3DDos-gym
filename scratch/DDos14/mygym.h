
#define MY_GYM_ENTITY_H

#include "ns3/opengym-module.h"

namespace ns3 {

class MyGymEnv : public OpenGymEnv
{
public:
  MyGymEnv ();
  virtual ~MyGymEnv ();
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

  Ptr<OpenGymSpace> GetActionSpace();
  Ptr<OpenGymSpace> GetObservationSpace();
  bool GetGameOver();
  Ptr<OpenGymDataContainer> GetObservation();
  float GetReward();
  std::string GetExtraInfo();
  bool ExecuteActions(Ptr<OpenGymDataContainer> action);

};

}


#endif // MY_GYM_ENTITY_H