#ifndef SCHEDULING_APP_H
#define SCHEDULING_APP_H

#include <iostream>
#include <vector>
#include <string>

// The Participant structure representing a participant with two attributes
struct Participant {
    std::string name;
    std::string email;
};

// The Meeting structure representing a meeting with two attributes
struct Meeting {
    std::vector<Participant> participants;
    int meetingTime; // start time of meeting in hrs (8-16)
};

// The Scheduling app class
class SchedulingApp {
private:
    std::vector<Meeting> meetings;
    // method to check availability of a list of participants for a given time slot
    bool timeAvailability(std::vector<Participant> participants, int meetingTime) const;

public:
    // method to add new participant to the app
    void addParticipant(std::string name, std::string email);

    // Method to add a meeting
    void addMeeting(std::vector<Participant> participants, int meetingTime);

    // method to show schedule of a participant
    void showSchedule(const Participant& participant) const;

    // method to suggest a time slot for a meeting with a group of participants
    void suggestTime(const std::vector<Participant>& participants) const;
};

#endif // SCHEDULING_APP_H
