#include "scheduling_app.h"

int main() {
    SchedulingApp app;

    // Adding participants
    app.addParticipant("Ali", "ali@mail.com");
    app.addParticipant("Martin", "martin@mail.com");
    app.addParticipant("Mads", "mads@mail.com");
    app.addParticipant("Sofie", "sofie@mail.com");
    app.addParticipant("Ashley", "ashley@mail.com");

    // Scheduling meetings
    std::vector<Participant> meeting1Participants = {
    {"Ali", "ali@mail.com"}, 
    {"Martin", "martin@mail.com"}
    };
    app.addMeeting(meeting1Participants, 800);

    std::vector<Participant> meeting2Participants = {
    {"Mads", "mads@mail.com"}, 
    {"Sofie", "sofie@mail.com"}
    };
    app.addMeeting(meeting2Participants, 900);

    std::vector<Participant> meeting3Participants = {
    {"Ali", "ali@mail.com"}, 
    {"Ashley", "ashley@mail.com"}};
    app.addMeeting(meeting3Participants, 1400);

    // Showing schedule for participants
    app.showSchedule({"Ali", "ali@mail.com"});
    app.showSchedule({"Martin", "martin@mail.com"});
    app.showSchedule({"Mads", "mads@mail.com"});
    app.showSchedule({"Sofie", "sofie@mail.com"});
    app.showSchedule({"Ashley", "ashley@mail.com"});

    // Suggesting meeting times for a group of participants
    std::vector<Participant> groupParticipants = {
    {"Ali", "ali@mail.com"}, 
    {"Martin", "martin@mail.com"}, 
    {"Sofie", "sofie@mail.com"}
    };
    app.suggestTime(groupParticipants);

    return 0;
}
