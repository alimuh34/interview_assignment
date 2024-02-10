#include <iostream>
#include <vector>
#include <string>

// the Participant structure representing a participant with two attributes 
struct Participant{ 
	std::string name;
	std::string email;
};
// The Meeting structure representing a meeting with two attributes
struct Meeting{
	std::vector<Participant> participants;
	int meetingTime; // start time of meeting in hrs (8-16)
};

// The Scheduling app class 
class SchedulingApp{
	
	private: 
	std::vector<Meeting> meetings;
	// method to check availability of a list of participants for a given time slot
	bool timeAvailability(std::vector<Participant> participants, int meetingTime) const { 
		for (const Meeting& meeting : meetings) {
			if (meeting.meetingTime == meetingTime) {
				// check if a participant is already scheduled at this time slot
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
	// method to add new participant to the app
	void addParticipant(std::string name, std::string email) {
		// call an instance of Participant
		Participant newParticipant = {name, email};
		std::cout << newParticipant.name << " has been added." << "\n";
	}
	
	// Method to add a meeting 
	void addMeeting(std::vector<Participant> participants, int meetingTime) {
		// Meetings must start at the hour, last one hour and bound between 8-17
		if (meetingTime < 800 || meetingTime > 1600 || meetingTime % 100 != 0) {
			std::cout << "Invalid meeting time. Meetings must start at the hour, last one hour and bound between 8-17 " << "\n";
			return;
		}
		if (timeAvailability(participants, meetingTime) == false) {
			std::cout << "Time slot conflicts with participants' schedule. Please select another meeting time" << "\n";
			return;
		}
		// call an instance of Meeting
		Meeting newMeeting = {participants, meetingTime};
		// Add the new meeting to the scheduling app
		meetings.push_back(newMeeting);
		std::cout << "Meeting added at " << meetingTime << " with the following participants:" << "\n";
		for (const Participant& participant : participants) {
			std::cout <<"- "<< participant.name << "\n";
		}
	}
	
	// method to show schedule of a participant
	void showSchedule(const Participant& participant) const {
		std::cout << "Schedule for " << participant.name << ":" << "\n";
		// loop through meetings to find participant's schedule
		for (const Meeting& meeting : meetings) {
			for (const Participant& mParticipant : meeting.participants) {
				if (mParticipant.email == participant.email) {
					std::cout << "Meeting at " << meeting.meetingTime << " with ";
					// print participants of the meeting
					unsigned cnt = 0;
					for (const Participant& person : meeting.participants) {
						if (person.email != participant.email) {
							std::cout << person.name;
							cnt++;
							if (cnt < meeting.participants.size() - 2) {
								std::cout << ", ";
							}
							else if (cnt == meeting.participants.size() - 2) {
								std::cout << " and ";
							}
						}
					}
					std::cout << "\n";
					// exit loop if participant is found in a meeting
					break;
				}
			}
		}
	}
	
	// method to suggest a time slot for a meeting with a group of participants
	void suggestTime(const std::vector<Participant>& participants) const {
		std::cout << "The following time slots are available:" << "\n";
		// loop through the hour marks to check for availability
		for (int i = 800; i <= 1600; i+= 100) {
			bool slotAvailable = timeAvailability(participants, i);
			if (slotAvailable) {
				std::cout << i << "\n";
			}
		}
	}
	
					
};
