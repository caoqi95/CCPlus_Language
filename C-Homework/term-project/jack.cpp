#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>


using namespace std; /* for cleaner code (min and max functions) */

// Constants
const int ncar_states = 21; // including "0" cars
const int max_moves = 5;
const int max_morning = ncar_states + max_moves;
const double discount = 0.9;
const double theta = pow(10, -7); // stop when differences are of order theta 

// Probabilities
double prob_1[max_morning][ncar_states]; // 26x21
double prob_2[max_morning][ncar_states];

// Rewards
double rew_1[max_morning];
double rew_2[max_morning];

// Value and Policy
double V[ncar_states][ncar_states];
int policy[ncar_states][ncar_states];

// Declarations
double factorial(int n);
double poisson(int n, double l);
void load_probs_rewards(double probs[max_morning][ncar_states], double rewards[max_morning], 
double l_reqsts, double l_drpffs);
void policy_eval();
double estimate_action(int n1, int n2, int a);
int greedy_policy(int n1, int n2);
bool policy_improvement();
 
/* function for Factorial: n! */
double factorial(int n){
	
	if (n>0) return (n*factorial(n - 1));
	else return (1.0);
}

/* function for Poisson Disturibution */
double poisson(int n, double lambda){
	
	return (exp(-lambda)*pow(lambda, (double) n)/factorial(n));
} 

/* function for Initialization */
void load_probs_rewards(double probs[max_morning][ncar_states], double rewards[max_morning], 
double l_reqsts, double l_drpffs){
	double req_prob;
	double drp_prob;
	int satisfied_req;
	int new_n;
	for(int req=0; (req_prob = poisson(req, l_reqsts)) > theta; req++){
		// fill the reward matrix rewards[max_morning] using the probability req_prob
		for(int n=0; n < max_morning; n++){
			satisfied_req = min(req, n); // at most, all the cars avaliable
			rewards[n] += 10 * req_prob * satisfied_req; // 10 is the reward per request
		}
		for (int drp=0; (drp_prob = poisson(drp, l_drpffs)) > theta; drp++){
			// fill the probability matrix probs[max_morning][ncar_states] 
			for (int m=0; m < max_morning; m++){
				satisfied_req = min(req, m);
				new_n = m + drp - satisfied_req; 
				new_n = max(new_n, 0); // 0 at least
				new_n = min(20, new_n); // 20 at most
				probs[m][new_n] += req_prob * drp_prob; // add up the joint probability
			}
		}
	}
}

/* function for Policy Eualuation */
void policy_eval(){
	double val_tmp;
	double diff;
	int a;
	
	do{
		diff = 0.0;
		for(int n1=0; n1 < ncar_states; n1++){
			for (int n2=0; n2 < ncar_states; n2++){
				// Assign the new value for each state; keep in diff the highest update difference
				val_tmp = V[n1][n2];
				a = policy[n1][n2];
				V[n1][n2] = estimate_action(n1, n2, a);
				diff = max(diff, fabs(V[n1][n2] - val_tmp));
			}
		}
	} while (diff > theta);
}

/* function for Estimation of Action Values */
double estimate_action(int n1, int n2, int a){
	double val; // determine the range of possible actions for the given state
	a = min(a, +n1);
	a = max(a, -n2);
	a = min(+5, a);
	a = max(-5, a);
	val = -2 * fabs((double) a);
	
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

/* function for Policy Improvement */
bool policy_improvement(){
	int b;
	bool has_changed = false;
	for (int n1=0; n1 < ncar_states; n1++){
		for (int n2=0; n2 < ncar_states; n2++){
			b = policy[n1][n2];
			// get a new policy
			policy[n1][n2] = greedy_policy(n1, n2);
			if (b != policy[n1][n2]){
				has_changed = true;
			}
		}
	}
	return has_changed;
}

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
	best_val = estimate_action(n1, n2, a);
	for (a=a_min+1; a <= a_max; a++){
		val = estimate_action(n1, n2, a);
		if (val > best_val + theta){
			best_val = val;
			best_action = a;
		}
	} 
	return best_action;
}

/* function for Print Policy */
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

int main()
{
	double lambda_1r = 3.0; // request rate at location1 
	double lambda_1d = 3.0; // dropoff rate at location1
	double lambda_2r = 4.0; // request rate at location2
	double lambda_2d = 2.0; // Dropoff rate at location2
	
	// Initialization
	load_probs_rewards(prob_1, rew_1, lambda_1r, lambda_1d); /* 1st location */
	load_probs_rewards(prob_2, rew_2, lambda_2r, lambda_2d); /* 2nd location */
	
	//print_prob_1();
	//print_prob_2();
	
	print_policy();
	// Policy Iteration
	bool has_changed;
	do{
		// iterative policy evaluation 
		policy_eval();
		// improve the policy; assign true to has_changed if the policy changed, if it did not 
		has_changed = policy_improvement();
		// print policy results
		print_policy();
	} while (has_changed);

	return 0;
}
