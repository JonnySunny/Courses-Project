/**
 * @file algorithm.h
 *
 * @copyright Spring 2018 CSci 5801 Team 10, All rights reserved.
 */

#ifndef SRC_ALGORITHM_H_
#define SRC_ALGORITHM_H_

// Includes
#include <iostream>
#include <string>
#include <vector>
#include <sstream>  // For stringstream
#include <fstream>  // For file stream
#include <ctime>    // Date/Time string
#include "./ballot.h"
#include "./candidate.h"

/**************************************************************************/

/**
    @brief This is the base class of algorithms. It acts as an interface class that must be instantiated through one of its children.
 */
class Algorithm  {
 public:
    Algorithm(std::vector<Ballot> b, std::vector<Candidate> c, int s = 0) :
        ballot_list(b),
        candidates_list(c),
        seats(s) {}

    virtual ~Algorithm() {
        ballot_list.clear();
        candidates_list.clear();
    }

    // Getters
    /**
        @brief
        @return const int seats
    */
    const int get_Seats() {return seats;}

    /**
        @brief
        @return std::vector<Ballot> ballot_list
    */
    std::vector<Ballot> get_Ballots() {return ballot_list;}

    /**
        @brief
        @return std::vector<Candidate> candidate_list
    */
    std::vector<Candidate> get_Candidates() {return candidates_list;}


    /**
        @brief Abstract method, must be defined in child.
        The main driver function, runs the corresponding defined algorithm to determine winners and losers.
    */
    virtual void run() = 0;

    /**
        @brief Abstract method, must be defined in child.
        Prints the winners of each seat from the election to cout.
    */
    virtual void printResults() = 0;

    /**
        @brief Generate report and dreakdown of program execution. Puts report in same folder as program executable.
    */
    virtual void generateReport() {
        std::ofstream output;

        // Full report
        output.open("Full_Report.txt");
        if (output.is_open()) {
            output << report.str() << std::endl;
            output.close();

        } else {
            std::cout << "\n\n\nOutput Report file could not be opened!"
                << "\nPrinting Full Report to terminal instead...";
            std::cout << "\n\n\n" << report.str() << "\n\n";
        }

        // Short report
        output.open("Expedited_Report.txt");
        if (output.is_open()) {
            output << short_report.str() << std::endl;
            output.close();

        } else {
            std::cout << "\n\n\nOutput Report file could not be opened!"
                << "\nPrinting Short Report to terminal instead...";
            std::cout << "\n\n\n" << short_report.str() << "\n\n";
        }
    }


    /**
        @brief Returns the current date time as a string.
        @return std::string Datetime in the form <Day> <dd> <Month> <Year> <HH:MM:SS> <TZ> (UTC+/-<HMMM>)
    */
    std::string dateTime() {
        time_t t = time(&t);
        struct tm info;
        char buffer[256];

        localtime_r(&t, &info);

        strftime (buffer, sizeof(buffer), "%A %d %B %G, %T %Z (UTC%z)", &info);

        return (std::string)buffer;
    }
 

 protected:
    /*
        These are protected because they need to be extensively accessed and manipulated by child classes.
    */

    // Temporary buffers to hold information for reports
    // Added to as the program executes
    std::stringstream report;
    std::stringstream short_report;

    // List of ballots
    std::vector<Ballot> ballot_list;
    // List of candidates
    std::vector<Candidate> candidates_list;
  


 private:
    int seats;  // Seats to be filled
};

#endif  // SRC_ALGORITHM_H_
