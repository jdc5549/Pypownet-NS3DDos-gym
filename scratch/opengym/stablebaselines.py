#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gym
import argparse
#import os,sys
#sys.path.append('~/Documents/James_C/ns3-gym/src/opengym/model/ns3gym/ns3gym')
import ns3gym

from stable_baselines3 import PPO



__author__ = "Piotr Gawlowicz"
__copyright__ = "Copyright (c) 2018, Technische Universität Berlin"
__version__ = "0.1.0"
__email__ = "gawlowicz@tkn.tu-berlin.de"


env = gym.make('ns3-v0')
env.reset()

ob_space = env.observation_space
ac_space = env.action_space
print("Observation space: ", ob_space,  ob_space.dtype)
print("Action space: ", ac_space, ac_space.dtype)


model = PPO("MlpPolicy", env, verbose=1)
model.learn(total_timesteps=25000)
model.save("PPO_opengym")