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
    bool timeAvailability(const std::vector<Participant>& participants, const std::time_t& startTime) const {
		// Find meetings scheduled at startTime using the schedule map
        auto it = schedule.find(startTime);
        // Iterate over existing meetings scheduled at this time
        if (it != schedule.end()) {
			// check if a participant is already scheduled at this time slot
            for (const Meeting& meeting : it->second) {
                for (const Participant& participant : participants) {
                    for (const Participant& mParticipant : meeting.participants) {
                        if (participant.email == mParticipant.email) {
                            return false; // unavailable time slot
                        }
                    }
                }
            }
        }
        // If all participants are available at given time slot, return true
        return true;
    }

public:
    // Method to add a participant to the app
    void addParticipant(const std::string& name, const std::string& email) {
        // Check if participant email is unique
        if (participantEmails.find(email) != participantEmails.end()) {
            std::cout << "Participant with email " << email << " already exists." << "\n";
            return;
        }
        // Add participant to the set of participant emails
        Participant newParticipant = {name, email};
        participantEmails.insert(email);
        std::cout << newParticipant.name << " has been added." << "\n";
    }

    // Method to add a meeting
    void addMeeting(const std::vector<Participant>& participants, std::time_t startTime) {
        // Check if the startTime corresponds to the mark of an hour
        if (std::localtime(&startTime)->tm_min != 0) {
            std::cout << "Meeting must start at the hour mark." << "\n";
            return;
        }

        // Check if the time slot is available
        if (!timeAvailability(participants, startTime)) {
            std::cout << "Time slot conflicts with participants' schedule."
            " Please select another meeting time" << "\n";
            return;
        }
        
        // call an instance of Meeting
        Meeting newMeeting = {participants, startTime};
        
        // Add the meeting to the schedule
        schedule[startTime].push_back(newMeeting);
        
        // Update participant schedule
		for (const Participant& participant : participants) {
			participantSchedule[participant.email].push_back(newMeeting);
		}

        // Convert start time to local time for display
        std::tm* localTime = std::localtime(&startTime);
        std::cout << "Meeting added on " << localTime->tm_mday 
        << "-" << (localTime->tm_mon + 1) <<  "-" << (localTime->tm_year + 1900) 
        << " at " << localTime->tm_hour << ":00 with the following participants:" << "\n";
        for (const Participant& participant : participants) {
            std::cout << "- " << participant.name << "\n";
        }
    }

	// Method to show schedule of a participant
	void showSchedule(const Participant& participant) const {		
        std::cout << "Schedule for " << participant.name << ":" << "\n";
        
        // Find participant's meetings in the participantSchedule map
        auto it = participantSchedule.find(participant.email);
        if (it != participantSchedule.end()) {
			
			// Iterate over all meetings for the participant
            for (const Meeting& meeting : it->second) {
                std::tm* localTime = std::localtime(&meeting.startTime);
                std::cout << "Meeting on " << localTime->tm_mday 
				<< "-" << (localTime->tm_mon + 1) <<  "-" << (localTime->tm_year + 1900) 
				<< " at " << localTime->tm_hour << ":00 with ";
				
				// Add meeting details (the other participants)
				unsigned cnt = 0;
                for (const Participant& mParticipant : meeting.participants) {
                    if (mParticipant.email != participant.email) {
                        std::cout << mParticipant.name;
                        cnt++;
                        if (cnt < meeting.participants.size() - 2){
							std::cout << ", ";
						}
						else if (cnt == meeting.participants.size() - 2){
							std::cout << " and ";
							}
                    }
                }
                std::cout << "\n";
            }
        } else {
            std::cout << "No meetings scheduled for " << participant.name <<"." << "\n";
        }
    }

    // Method to suggest available time slots for a meeting
    // starting earliest at the next hour mark
	void suggestTime(const std::vector<Participant>& participants) const {
	    std::cout << "The following time slots are available:" << "\n";
	    int cnt = 0; // Counter for number of suggested time slots
	
	    // Get the current time
	    std::time_t currentTime = std::time(0);
	    std::tm* localTime = std::localtime(&currentTime);
	    int currentHour = localTime->tm_hour;
	
	    // Start from the current hour plus one
	    int hour = (currentHour + 1) % 24;
	    int dayOffset = 0;
	
	    // Loop until we find 5 available time slots
	    while (cnt < 5) {
	        // Adjust hour and day as needed
	        if (hour >= 24) {
	            hour = 0;
	            dayOffset++;
	        }
	
	        // Create suggested time
	        std::tm suggestedTime = *std::localtime(&currentTime);
	        suggestedTime.tm_hour = hour;
	        suggestedTime.tm_mday += dayOffset;
	        std::time_t suggestedTime_t = std::mktime(&suggestedTime);
	
	        // Check if the time slot is available
	        if (timeAvailability(participants, suggestedTime_t)) {
	            // Convert suggested time to local time for display
	            std::tm* localTime = std::localtime(&suggestedTime_t);
	            std::cout << localTime->tm_mday 
				<< "-" << (localTime->tm_mon + 1) <<  "-" << (localTime->tm_year + 1900) 
				<< " at " << localTime->tm_hour << ":00\n";
	            cnt++;
	        }
	
	        // Move to the next hour
	        hour++;
	    }
	}
};
