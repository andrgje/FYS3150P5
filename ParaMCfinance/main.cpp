#include <mpi.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
using namespace  std;
using namespace arma;
// output file
ofstream ofile;

using namespace std;


//Function to initialize agents
void initialize(vec&, double);
//Function for simulating the transactions
void transactions(vec&, int, double);
//Function to register income in given intervals
void addToHistogram(vec&, vec&, double);
//Print the results to file
void outputToFile(vec&, int);


int main(int argc, char* argv[])
{
    char* outfilename;
    int numAgents, numTransactions, total_experiments, my_rank, numprocs;
    double initial_money, interval, lambda;


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


    interval=0.05; initial_money=1; numAgents=500; numTransactions=10000; total_experiments=1000; lambda=0;

    vec histogram(60), total_histogram(60), agents(numAgents);
    int my_experiments=total_experiments/numprocs;

    for(int i=0;i<my_experiments; i++){
        cout << my_rank << i;
        initialize(agents, initial_money);
        transactions(agents, numTransactions, lambda);
        addToHistogram(agents, histogram, interval);

    }
    for( int i =0; i < 60; i++){
      MPI_Reduce(&histogram[i], &total_histogram[i], 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
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
void transactions(vec& agents, int numTransactions, double lambda){
    int agentI, agentJ;
    double epsilon, newAgentI, newAgentJ, totalMoney;

    //Initialize random number generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

    for(int k = 0; k<numTransactions;k++){
        //Pick two random agents
        agentI=(int) RandomNumberGenerator(gen)*500;
        agentJ=(int) RandomNumberGenerator(gen)*500;

        epsilon=RandomNumberGenerator(gen);

        //Sum of money that both agents have
        totalMoney=(1-lambda)*(agents[agentI]+agents[agentJ]);
        double m1 = agents[agentI];
        //Calculate new values for both agents
        newAgentI=lambda*agents[agentI]+epsilon*totalMoney;
        newAgentJ=lambda*agents[agentJ]+(1-epsilon)*totalMoney;


        //Set new values for both agents
        agents[agentI]=newAgentI;
        agents[agentJ]=newAgentJ;
    }
}

void addToHistogram(vec& agents, vec& histogram, double interval){
    double max_value=agents.max();
    //if(max_value/interval>histogram.size()){
       // histogram.resize(ceil(max_value/interval));
    //}

        for(int l=0;l<agents.size();l++){
            if(agents[l]<3){
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

