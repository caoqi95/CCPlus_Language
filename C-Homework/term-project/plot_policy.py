# -*- coding: utf-8 -*-
"""
Created on Wed Jun  5 22:46:47 2019

@author: caoqi95
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

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
        print(Po.shape)
        CS = plt.contourf(A, B, Po, levels)
        cbar = plt.colorbar(CS)
        cbar.ax.set_ylabel('actions')
        plt.title('Policy {}'.format(i))
        plt.xlabel("Cars at Location 2")
        plt.ylabel("Cars at Location 1")
    plt.savefig('C:/Users/User/Desktop/jack/term_project/result.jpg')
    plt.show()
    
def plot_value():
    
    V = np.loadtxt('value.txt')
    fig = plt.figure(figsize=(10, 8))
    ax_surf = fig.gca(projection='3d')
    ax_surf.set_position([0.1,0.15,0.7,0.7])
    X, Y = np.meshgrid(np.arange(0, 21), np.arange(0, 21))
    surf = ax_surf.plot_surface(X, Y, V, cmap=cm.coolwarm,
                                linewidth=0, antialiased=False)
    ax_surf.set_xticks(np.arange(0,21,4).astype(int))
    ax_surf.set_yticks(np.arange(0,21,4).astype(int))
    ax_surf.set_xlabel('Number of cars at location 2')
    ax_surf.set_ylabel('Number of cars at location 1')
    ax_surf.set_title('Value function of optimal policy')
    ax_color = fig.add_axes([0.85,0.25,0.03,0.5])
    cbar = fig.colorbar(surf, cax=ax_color, 
                        orientation='vertical')
    plt.savefig('C:/Users/User/Desktop/jack/term_project/value.jpg')

if __name__ == "__main__":
    
    policy = txt2arr()
    plot_policy(policy)
    plot_value()