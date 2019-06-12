/*  Jack's car rental problem.  The state is n1 and n2, the number of cars
at each location a the end of the day, at most 20. Actions are numbers of cars 
to switch from location 1 to location 2, a number between -5 and +5.

prob_1(n1,new-n1) is a 26x21 array giving the probability that the number of cars at 
location 1 is new-n1, given that it starts the day at n1.  Similarly for prob_2.

rew_1(n1) is a 26 array giving the expected reward due to satisfied requests at 
location, given that the day starts with n1 cars at location 1.  Similarly for rew_2.


MDP JackCarRenral
	states cars[2]
	actions moveCars
	reward r
	discount rate 0.9
	vaild states { 0 <= cars <= 20 } 
	vaild actions {-5 <= moveCars <= 5}
	environment
		random requests [poisson(3); poisson(4)]
		random dropoffs [poisson(3); poisson(2)]
		nextMorn = min(cars + [-moveCars, moveCars], 20)
		satisfied_req = min(requests, nextMorn)
		new_cars = nextMorn + dropoff - satisfied_req
		new_cars = max(new_cars, 0)
		new_cars = min(new_cars, 20)
		r = satisfied_req * 10 - 2 * abs(moveCars)
*/

#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#define RENTAL_INCOME 10 // 10 is the reward per request
#define MOVE_COST -2 // -2 is the cost for moving a car

using namespace std; 

// Constants
const int ncar_states = 21; // including "0" cars
const int max_moves = 5;
const int next_morning = ncar_states + max_moves;
const double discount = 0.9;
const double theta = pow(10, -7); // stop when differences are smaller then theta 

// Value function and Policy
double V[ncar_states][ncar_states];
int policy[ncar_states][ncar_states];

// Probabilities
double prob_1[next_morning][ncar_states]; 
double prob_2[next_morning][ncar_states];

// Rewards
double rew_1[next_morning];
double rew_2[next_morning];

 // Declarations
double factorial(int n);
double poisson(int n, double l);
void init_probs_rewards(double probs[next_morning][ncar_states], double rewards[next_morning], 
double l_reqsts, double l_drpffs);
void policy_eval();
double calculate_value(int n1, int n2, int a);
int greedy_policy(int n1, int n2);
bool policy_improvement();


/* Factorial: n! */
double factorial(int n){
	
	if (n>0) return (n*factorial(n - 1));
	else return 1.0;
}

/* Poisson Disturibution */
double poisson(int n, double lambda){
	
	return exp(-lambda)*pow(lambda, (double) n)/factorial(n);
} 

/* Initialization */
void init_probs_rewards(double probs[next_morning][ncar_states], double rewards[next_morning], 
double l_reqsts, double l_drpffs){
	double req_prob;
	double drp_prob;
	int satisfied_req; // the number of satisfied requests
	int new_n;
	for(int req = 0; (req_prob = poisson(req, l_reqsts)) > theta; req++){
		for(int n = 0; n < next_morning; n++){
			satisfied_req = min(req, n); // at most, all the cars avaliable
			rewards[n] += RENTAL_INCOME * req_prob * satisfied_req; 
		}
		for (int drp = 0; (drp_prob = poisson(drp, l_drpffs)) > theta; drp++){
			for (int  m = 0; m < next_morning; m++){
				satisfied_req = min(req, m);
				new_n = m + drp - satisfied_req; 
				new_n = max(new_n, 0); // 0 at least
				new_n = min(20, new_n); // 20 at most
				probs[m][new_n] += req_prob * drp_prob; // add up the joint probability
			}
		}
	}
}

/* Policy Eualuation */
void policy_eval(){
	double val_tmp;
	double diff;
	int a;
	
	do{
		diff = 0.0;
		for(int n1=0; n1 < ncar_states; n1++){
			for (int n2=0; n2 < ncar_states; n2++){
				val_tmp = V[n1][n2];
				a = policy[n1][n2]; // the num of moving cars
				V[n1][n2] = calculate_value(n1, n2, a);
				diff = max(diff, fabs(V[n1][n2] - val_tmp));
			}
		}
	} while (diff > theta);
}

/* Calculate Values */
double calculate_value(int n1, int n2, int a){
	double val; 
	// determine the range of possible actions for the given state
	a = min(a, +n1);
	a = max(a, -n2);
	a = min(+5, a);
	a = max(-5, a);
	val = MOVE_COST * fabs((double) a);
	
	int morning_n1 = n1 - a;
	int morning_n2 = n2 + a;
	for (int new_n1 = 0; new_n1 < ncar_states; new_n1 ++){
		for (int new_n2 = 0; new_n2 < ncar_states; new_n2++){
			val += prob_1[morning_n1][new_n1]*prob_2[morning_n2][new_n2]*(rew_1[morning_n1] + 
			rew_1[morning_n2] + discount * V[new_n1][new_n2]);
		}
	}
	return val;
}

/* Policy Improvement */
bool policy_improvement(){
	int a;
	bool policy_stable = true;
	for (int n1=0; n1 < ncar_states; n1++){
		for (int n2=0; n2 < ncar_states; n2++){
			a = policy[n1][n2];
			policy[n1][n2] = greedy_policy(n1, n2);
			if (a != policy[n1][n2]){
				policy_stable = false;
			}
		}
	}
	return policy_stable;
}

/* Greedy policy */
int greedy_policy(int n1, int n2){
	// set the range of available actions
	int a_min = max(-5, -n2);
	int a_max = min(+5, +n1);
	double val;
	double best_val;
	double best_action;
	int a;
	
	a = a_min;
	best_action = a_min;
	best_val = calculate_value(n1, n2, a);
	for (a=a_min+1; a <= a_max; a++){
		val = calculate_value(n1, n2, a);
		if (val > best_val + pow(10, -9)){
			best_val = val;
			best_action = a;
		}
	} 
	return best_action;
}

/* Print Policy */
void print_policy(){
	printf("\nPolicy:\n");
	for (int n1=0; n1 < ncar_states; n1 ++){
		printf("\n");
		for (int n2=0; n2 < ncar_states; n2++){
			printf("%2d ", policy[ncar_states - (n1+1)][n2]);
		}
	}
	printf("\n\n");
}

/*
void print_prob_1(){
	printf("\n");
	for (int n1=0; n1 < max_morning; n1++){
		printf("\n");
		for (int n2=0; n2 <ncar_states; n2++){
			printf("%.4f ", prob_1[n1][n2]);
		}
	}
	printf("\n");
} 
void print_prob_2(){
	printf("\n");
	for (int n1=0; n1 < max_morning; n1++){
		printf("\n");
		for (int n2=0; n2 <ncar_states; n2++){
			printf("%.4f ", prob_2[n1][n2]);
		}
	}
	printf("\n");
} 
*/

/* Print optimal policy's value */
void print_value(){
	printf("\n");
	for (int i = 0; i < ncar_states; i++){
		printf("\n");
		for (int j = 0; j < ncar_states; j++){
			printf("%.2f ", V[i][j]);
		}
	}
	printf("\n");
}

int main()
{
	double lambda_1r = 3.0; // request lambda at location1 
	double lambda_1d = 3.0; // dropoff lambda at location1
	double lambda_2r = 4.0; // request lambda at location2
	double lambda_2d = 2.0; // Dropoff lambda at location2
	
	// Initialization
	init_probs_rewards(prob_1, rew_1, lambda_1r, lambda_1d); /* 1st locatoin */
	init_probs_rewards(prob_2, rew_2, lambda_2r, lambda_2d); /* 2nd location */
	
	
	print_policy();
	
	// Policy Iteration
	bool policy_stable;
	do{
		// iterative policy evaluation 
		policy_eval();
		// improve the policy; 
		policy_stable = policy_improvement();
		// print policy result
		print_policy();
	} while (!policy_stable);
	
	//print_value();
	getch();
	
	return 0;
}
