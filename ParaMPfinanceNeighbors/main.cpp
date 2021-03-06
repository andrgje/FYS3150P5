#include <mpi.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
#include <sstream>
using namespace  std;
using namespace arma;
// output file
ofstream ofile;

using namespace std;


//Function to initialize agents
void initialize(vec&, double);
//Function for simulating the transactions
void transactions(vec&, int, double, double, double, int, int);
//Function to register income in given intervals
void addToHistogram(vec&, vec&, double, int);
//Print the results to file
void outputToFile(vec&, int);
//Find maximum number of transactions that have occured between to agents

int main(int argc, char* argv[])
{
    char* outfilename;
    int numAgents, numTransactions, total_experiments, my_rank, numprocs;
    double initial_money, interval, lambda, alpha, gamma;

            outfilename=argv[1];
            ofile.open(outfilename);
            //  MPI initializations
            MPI_Init (&argc, &argv);
            MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
            MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
            if (my_rank == 0 && argc <= 1) {
              cout << "Bad Usage: " << argv[0] <<
                " read output file" << endl;
              exit(1);
            }


            interval=0.05; initial_money=1; numAgents=1000; numTransactions=100000000; total_experiments=1000; lambda=0; alpha=2; gamma=2.0;

            vec histogram(10000), agents(numAgents), total_histogram(10000);
            int my_experiments=total_experiments/numprocs;
            if(my_rank==1){
                my_experiments+=total_experiments%numprocs;
            }

            for(int i=0;i<my_experiments; i++){

                cout << my_rank<< " " << i<<"\n";
                initialize(agents, initial_money);
                transactions(agents, numTransactions, lambda, alpha, gamma, my_rank, numAgents);
                addToHistogram(agents, histogram, interval, numAgents);

                for(int j =0; j < 10000; j++){
                  MPI_Reduce(&histogram[j], &total_histogram[j], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
                }

            }


            //Write to file
            if(my_rank==0){
                outputToFile(total_histogram, total_experiments);
            }
            // End MPI
            MPI_Finalize ();


            ofile.close(); // close output file


}
//Function to initialize agents with initial money.
void initialize(vec& agents, double initial_money){
    agents.fill(initial_money);
}

//Function for simulating the transactions
void transactions(vec& agents, int numTransactions, double lambda, double alpha, double gamma, int my_rank, int numAgents){
    int agentI, agentJ;
    double epsilon, newAgentI, newAgentJ, totalMoney, wealthdiff;

    mat transactionCount(numAgents, numAgents, fill::zeros);


    double cmax=transactionCount.max();


    //Initialize random number generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

    for(int k = 0; k<numTransactions;k++){
        //Pick two random agents
        agentI=(int) (RandomNumberGenerator(gen)*numAgents);
        agentJ=(int) (RandomNumberGenerator(gen)*numAgents);

        while(agentI==agentJ){
            agentJ=(int) (RandomNumberGenerator(gen)*numAgents);
        }

        wealthdiff=abs(agents[agentI]-agents[agentJ]);
        if(wealthdiff==0){
            wealthdiff=1;
        }

        if(RandomNumberGenerator(gen)<2*pow(wealthdiff, -alpha)*pow((1+transactionCount[agentI,agentJ])/(cmax+1),gamma)){

            epsilon=RandomNumberGenerator(gen);

            //Sum of money that both agents have
            totalMoney=(1-lambda)*(agents[agentI]+agents[agentJ]);
            //Calculate new values for both agents
            newAgentI=lambda*agents[agentI]+epsilon*totalMoney;
            newAgentJ=lambda*agents[agentJ]+(1-epsilon)*totalMoney;


            //Set new values for both agents
            agents[agentI]=newAgentI;
            agents[agentJ]=newAgentJ;
            transactionCount[agentI,agentJ]+=1;
            transactionCount[agentJ,agentI]+=1;
            if(transactionCount[agentJ,agentI]>cmax){cmax=transactionCount[agentJ,agentI];}

        }
    }

}

void addToHistogram(vec& agents, vec& histogram, double interval, int numAgents){
        for(int l=0;l<numAgents;l++){
            if(agents[l]<500){
                double index = floor(agents[l]/interval);
                histogram[index]+=1;
            }
        }
}

void outputToFile(vec& histogram, int experiments){
    histogram =histogram/experiments;
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << histogram;
}

