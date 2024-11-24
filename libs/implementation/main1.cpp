#include "../classes/league.cpp"

int main() {
    League league;
    unordered_map<int, string> teamNames;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> teamNamesSortSerial;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        fflush(stdin);

        switch (choice) {
            case 1: { 
                cout << endl << "Enter Team Names (type 'done' to finish): " << endl;
                string name;
                int serialnum = 1;

                while (true) {
                    cout << "Team " << serialnum << ": ";
                    fflush(stdin);
                    getline(cin, name);
                    if (name == "done") break;
                    teamNames[serialnum] = name;
                    serialnum++;
                }
                cout << endl << endl << "|Sr. No.|\t" << "Team" << endl;
                for (auto& entry : teamNames) {
                    teamNamesSortSerial.push({entry.first, entry.second});
                }

                while (!teamNamesSortSerial.empty()) {
                    cout << teamNamesSortSerial.top().first << "\t" << teamNamesSortSerial.top().second << endl;
                    league.addTeam(teamNamesSortSerial.top().second);
                    teamNamesSortSerial.pop();
                }

                cout << endl << endl << "Teams Added Successfully!" << endl;
                break;
            }
            case 2:  // Schedule matches
                league.scheduleMatches();
                break;

            case 3:  // Play next match
                league.playNextMatch();
                break;

            case 4:  // Display standings
                league.displayTable();
                break;

            case 5: {  // Query max points for a team
                string teamName;
                int numGames;
                cout << "Enter team name: ";
                cin >> teamName;
                cout << "Enter number of games: ";
                cin >> numGames;
                league.queryMaxPoints(teamName, numGames);
                break;
            }

            case 6:  // View match schedule
                league.viewSchedule();
                break;

            case 7:  // Play all matches
                league.playAllMatches();
                break;

            case 8:  // Exit
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;

            default:  // Invalid choice
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    }

    return 0;
}