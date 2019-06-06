# -*- coding: utf-8 -*-
"""
Created on Wed Jun  5 22:46:47 2019

@author: caoqi95
"""
import numpy as np
import matplotlib.pyplot as plt

def txt2arr():
    
    # read txt file
    f = open('policy.txt', 'r')
    lines = f.readlines()
    
    # delete spaces 
    nums = []
    for i in lines:
        if len(i) > 10:
            nums.append(i)
            
    # string to int
    real_nums = []
    for i in range(len(nums)):
        nums[i] = nums[i].strip()
        sp = nums[i].split(' ')
        one_line_nums = []
        for n in range(len(sp)):
            if sp[n] != '':
                one_line_nums.append(int(sp[n]))
        real_nums.append(one_line_nums)
    
    # convert to array
    policy_lists = [real_nums[n*21:(n+1)*21] for n in range(int(len(real_nums)/21))]
    policy_lists = np.array(policy_lists)
    
    return policy_lists

def plot_policy(policy):
    
    A = np.arange(0, 21)
    B = np.arange(0, 21)
    A, B = np.meshgrid(A, B)
    
    levels = range(-5, 6, 1)
    plt.figure(figsize=(18, 10))
    for i in range(policy.shape[0]):
        plt.subplot(231+i)
        Po = policy[i][::-1]
        CS = plt.contourf(A, B, Po, levels)
        cbar = plt.colorbar(CS)
        cbar.ax.set_ylabel('actions')
        plt.title('Policy {}'.format(i))
        plt.xlabel("Cars at Location 2")
        plt.ylabel("Cars at Location 1")
    plt.savefig('C:/Users/User/Desktop/jack/result.jpg')
    plt.show()
    
if __name__ == "__main__":
    
    policy = txt2arr()
    plot_policy(policy)
    