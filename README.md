# Pypownet-NS3DDos-gym
An ai-gym environment that models a power network simulator (pypownet) coupled with a communication simulator of a DDoS attack(NS3). First, a DDoS attack may occur on a given time step, in which case the communication RL agent would take router throttling actions to mitigate the impact of the attack. Based on the results of this simulation (which models the passage of 1 second), certain communication infrastructure may be affected in the power simulation, impacting the collection of sensor measurements from and the delivery of control actions to remote terminal units. Then, the power simulation step (of 1 hour) occurs, where a power node or line may be taken down randomly and the power agent must take load shedding actions to mitigate cascading failure. This is illustrated in the figure below.

![simflow](https://user-images.githubusercontent.com/31262427/123902536-011e6880-d93b-11eb-960f-d222ed3b2e65.png)

To run a Proximal Policy Optimzation (PPO) agent on this environment for 10000 steps, run the following command from the "pypownet" directory:

''' python -m pypownet.main --parameters parameters/default14 --niter 10000 --agent=PPO '''
