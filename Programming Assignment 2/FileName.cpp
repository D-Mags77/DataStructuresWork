#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// Job structure which is how the file values are stored
struct Job {
    int JobIdentification;
    int QueueNumber;
    int ProcessingTime;
    int StartTime;
};

// Read jobs from file
vector<Job> readJobsFromFile(const string& filename) { 
    ifstream file(filename); //open up the file 
    vector<Job> jobs; //Initializes an empty vector called jobs with the structure of Job
    int JobIdentification; //variables for everything to track
    int NumberOfQueues;
    int QueueNumber;
    int ProcessingTime;
    int StartTime = 0; //this starts at 0 and will be incremented by 1 to show each is happeneing every second

    if (!file) { //code to say that the program could not open up the files
        cerr << "There was a problem opening up the file" << endl;
        return jobs;
    }

    file >> NumberOfQueues; //this will read the first line of the text file which is a three which is the number of queues

    while (file >> JobIdentification >> QueueNumber >> ProcessingTime) { //This loop will read from each data in the job list file.
        jobs.push_back({ JobIdentification, QueueNumber, ProcessingTime, StartTime }); //using a pushback it will then put every information inside of the vector jobs
        StartTime++;  // Jobs arrive at 1-second intervals
    }

    file.close(); //close the file
    return jobs; 
}

// Process jobs
void ProcessJobs(vector<Job>& jobs, int NumberOfQueues) {
    vector<queue<Job>> queues(NumberOfQueues); // Create separate queues for the jobs
    int CurrentTime = 0; // Start from time 0

    // Place jobs in their respective queues
    for (Job& job : jobs) {
        queues[job.QueueNumber - 1].push(job); // Adjust for 1-based indexing
    }

    // Continue processing until all queues are empty
    while (true) {
        bool allQueuesEmpty = true; // This is a boolean flag to check and see if all of the queues are empty

        // Process jobs in each queue
        for (int i = 0; i < NumberOfQueues; i++) { //this loop will iterate over each queue
            if (!queues[i].empty()) { // if the current queue is not empty
                allQueuesEmpty = false; //the boolean flag is false since the queue is not epety
                Job& currentJob = queues[i].front(); //this will retrieve the job at the front of the queue

                
                if (currentJob.StartTime + currentJob.ProcessingTime == CurrentTime) { //this is a check to see if the current job is done and it checks so by seeing if the current time reaches thte sum of the start time and procesing time of the job
                    // Print job completion details
                    cout << "Job Number: " << currentJob.JobIdentification
                        << " Queue Number: " << currentJob.QueueNumber
                        << " Time Started: " << currentJob.StartTime
                        << " Time Ended: " << CurrentTime << endl;

                    queues[i].pop(); // Remove the job from the queue once the job has been completed
                }
            }
        }

        // Exit the loop if all queues are empty
        if (allQueuesEmpty) {
            break;
        }

        // Move to the next time unit
        CurrentTime++;
    }
}

int main() {
    string filename = "JobList.txt"; //this is the name of the file
    vector<Job> jobs = readJobsFromFile(filename); //this calls the function with the file name

    if (jobs.empty()) { //if all of the jobs are empty
        cout << "We do not have any jobs to process" << endl; //sats we do not have any jobs to process
        return 0; //return 0
    }

    int NumberOfQueues = 3;  // Number of queues
    ProcessJobs(jobs, NumberOfQueues);  // Start processing jobs

    return 0; //return 0
}
