#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

#define num_customers 5
#define num_resources 4

int available[num_resources]; //total available resources
int maximum[num_customers][num_resources]; //maximum number of resources needed by each customer
int allocation[num_customers][num_resources]; //number of resources allocated for each customer
int need[num_customers][num_resources]; //number of resources needed for each customer
int processes[num_customers] = {0, 1, 2, 3, 4};
string commands[num_resources]; //used to take care of the user inputs


bool safety_algorithm(int customer_num) {
    for (int i = 0; i < num_customers; i++){
        for(int j = 0; j < num_resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    //array to see if each process is finished
    bool finished[num_customers] = {0};

    //stores the order of processes that satisfy the safety algorithm
    int safeOrder[num_customers];

    int work[num_resources];
    for(int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    int num_finished = 0;
    while (num_finished < num_customers) {
        //finds process that is not finished and can be satisfied
        bool found = false;
        for(int p = customer_num; p < num_customers; p++) {
            //checks if the process is finished or not
            if(finished[p] == 0) {

                //checks if the resources needed is less than resources available
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[p][j] > work[j])
                        break;
                }

                if (j == num_resources) {

                    //frees resources if p can be completed
                    for(int k = 0; k < num_resources; k++)
                        work[k] += allocation[p][k];
                    
                    safeOrder[num_finished++] = p;
                    finished[p] = 1;
                    found = true;
                }
            }
        }

        if (found == false) {
            cout << "System is not in a safe state" << endl;
            return false;
        }
    }
    return true;
}


int request_resource(int customer_num, int request[]) {
    if (safety_algorithm(customer_num)) {
        for(int i = 0; i < num_resources; i++) {
            allocation[customer_num][i] += request[i];
        }
        cout << "Request satisfied" << endl;
        for(int i = 0; i < num_resources; i++) {
            available[i] -= request[i];
            need[customer_num][i] = maximum[customer_num][i] - allocation[customer_num][i];
        }
        return 0;
    }
    cout << "Request denied" << endl;
    return -1;
}

int release_resources(int customer_num, int release[]) {
    for(int i = 0; i < num_resources; i++) {
        available[i] += release[i];
    }
}

void print_array(int array[][num_resources]) {
    for(int i = 0; i < num_customers; i++) {
        cout << "[ ";
        for(int j = 0; j < num_resources; j++) {
            cout << array[i][j] << " ";
        }
        cout << "]\t";
    }
}

void tokenize(string s, string del = " ") {
    int i = 0;
    int start, end = -1 * del.size();
    do {
        start = end + del.size();
        end = s.find(del,start);
        commands[i] = s.substr(start,end - start);
        i++;
    } while (end != -1);
}


int main(int argc, char *argv[]) {
    bool valid = true;
    if ((argc - 1) != num_resources) {
        cout << "Invalid number of resources. Please specify amount for " << num_resources << " resources";
        return -1;
    }

    for (int i = 0; i < num_resources; i++) {
        int intValue = stoi(argv[i + 1]);
        available[i] = intValue;
    }

    ifstream readFile("input.txt");
    if (!readFile.is_open()) return -1;

    for (int i = 0; i < num_customers; i++){
        for(int j = 0; j < num_resources; j++) {
            readFile >> maximum[i][j];
        }
    }

    for (int i = 0; i < num_customers; i++){
        for(int j = 0; j < num_resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    while (valid) {
    cout << endl << "Enter your command (RQ, RL, *) followed by customer number and resources: ";
    for (int i = 0; i < num_resources + 2; i++) {
        cin >> commands[i];
        if (commands[0] == "*") {
            break;
        }
    }

    if (commands[0] == "RQ") {
        int requests[num_resources];
        for(int i = 2; i < num_resources + 2; i++) {
            requests[i - 2] = stoi(commands[i]);
        }
        request_resource(stoi(commands[1]), requests);
    } else if (commands[0] == "RL") {
        for(int i = 0; i < num_resources; i++) {
            available[i] += stoi(commands[i + 2]);
            allocation[stoi(commands[1])][i] -= stoi(commands[i + 2]);
        }
    } else if (commands[0] == "*") {
        cout << "Available = [ ";
        for(int i = 0; i < num_resources; i++) {
            cout << available[i] << " ";
        }
        cout << "]" << endl;
        cout << "Maximum = ";
        print_array(maximum);
        cout << endl << "Allocation = ";
        print_array(allocation);
        cout << endl << "Need = ";
        print_array(need);

    } else {
        cout << "Invalid. Enter one of the three commands";
    }

    }

}



