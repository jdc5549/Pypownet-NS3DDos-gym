#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gym
import argparse
import ns3gym

from stable_baselines3 import PPO, A2C, DQN



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


model = DQN("MlpPolicy", env, verbose=1,tensorboard_log = './logs')
model.learn(total_timesteps=50000)
model.save("DQN_interference")