#include "Scheduling_App.h"

int main() {
    SchedulingApp app;

    // Adding participants
    app.addParticipant("Ali", "ali@mail.com");
    app.addParticipant("Martin", "martin@mail.com");
    app.addParticipant("Mads", "mads@mail.com");
    app.addParticipant("Sofie", "sofie@mail.com");
    app.addParticipant("Ashley", "ashley@mail.com");

    std::vector<Participant> group_A = {
        {"Ali", "ali@mail.com"},
        {"Ashley", "ashley@mail.com"}, 
        {"Sofie", "sofie@mail.com"}
    };
        std::vector<Participant> group_B =  {
        {"Martin", "martin@mail.com"},
        {"Ashley", "ashley@mail.com"}, 
        {"Mads", "mads@mail.com"},
        {"Sofie", "sofie@mail.com"}
    };
    
    
    std::tm meetingTime = {};
    meetingTime.tm_year = 2024 - 1900; // Year is current year minus 1900
    meetingTime.tm_mon = 1; // February (zero-based)
    meetingTime.tm_mday = 18; //18th
    meetingTime.tm_hour = 9;  // 9 am
 //   meetingTime.tm_min = 10; 10 min past, this will create an error
    std::time_t startTime = std::mktime(&meetingTime);
    
    
    
    // Adding a meeting for group A on the 18th of February at 9 am
    app.addMeeting(group_A, startTime);
    // Adding a conflicting meeting for group B
    app.addMeeting(group_B, startTime);
    

    // Show the schedule for Ali and Martin
    Participant Ali = {"Ali", "ali@mail.com"};
    Participant Martin = {"Martin", "martin@mail.com"};
    app.showSchedule(Ali);
    app.showSchedule(Martin);

    // Suggest available time slots for a meeting for group A and B

    app.suggestTime(group_A);
    app.suggestTime(group_B);

    return 0;
}
