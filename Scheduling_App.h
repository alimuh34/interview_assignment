#ifndef SCHEDULING_APP_H
#define SCHEDULING_APP_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <ctime>

// the Participant structure 
struct Participant {
    std::string name;
    std::string email; // uniqueness will be ensured
};

// The Meeting structure
struct Meeting {
    std::vector<Participant> participants;
    std::time_t startTime; // Start time of meeting (00-23)
};

// The Scheduling app class 
class SchedulingApp {
private:
    std::map<std::time_t, std::vector<Meeting>> schedule; // Map start time to meetings
    std::map<std::string, std::vector<Meeting>> participantSchedule; // Map participant email to their meetings
    std::set<std::string> participantEmails; // Set to ensure unique participant emails

    // Method to check time availability for a meeting
    bool timeAvailability(const std::vector<Participant>& participants, const std::time_t& startTime) const;

public:
    // Method to add a participant to the app
    void addParticipant(const std::string& name, const std::string& email);

    // Method to add a meeting
    void addMeeting(const std::vector<Participant>& participants, std::time_t startTime);

    // Method to show schedule of a participant
    void showSchedule(const Participant& participant) const;

    // Method to suggest available time slots for a meeting
    // starting earliest at the next hour mark
    void suggestTime(const std::vector<Participant>& participants) const;
};

#endif // SCHEDULING_APP_H
