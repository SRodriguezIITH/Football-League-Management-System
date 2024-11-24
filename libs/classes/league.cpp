#include "../../util/libraries/libs.cpp"
#include "./team.cpp"

class League {
private:
    unordered_map<string, Team*> teams;
    vector<Team*> standings;
    queue<pair<Team*, Team*>> matchSchedule;
    time_t startDate;
    time_t currentDate;

public:
    void addTeam(const string& teamName) {
        if (teams.find(teamName) == teams.end()) {
            teams[teamName] = new Team(teamName);
        }
    }

    void playGame(Team* team1, int goals1, Team* team2, int goals2) {
        team1->updateResults(goals1, goals2);
        team2->updateResults(goals2, goals1);
    }

    void scheduleMatches() {
        vector<Team*> teamList;
        for (auto& pair : teams) {
            teamList.push_back(pair.second);
        }

        int n = teamList.size();
        bool odd = false;

        if (n % 2 != 0) {
            teamList.push_back(nullptr);
            odd = true;
            n++;
        }

        int day, month, year;
        cout << "Enter the tournament start date (DD MM YYYY): ";
        cin >> day >> month >> year;

        tm startDateTm = {0};
        startDateTm.tm_mday = day;
        startDateTm.tm_mon = month - 1;
        startDateTm.tm_year = year - 1900;

        startDate = mktime(&startDateTm);
        currentDate = startDate;

        for (int round = 0; round < n - 1; ++round) {
            for (int i = 0; i < n / 2; ++i) {
                Team* team1 = teamList[i];
                Team* team2 = teamList[n - 1 - i];

                if (team1 && team2) {
                    matchSchedule.push(make_pair(team1, team2));
                }
            }
            rotate(teamList.begin() + 1, teamList.begin() + 2, teamList.end());
            currentDate += 7 * 24 * 60 * 60;
        }
        cout << "All matches have been scheduled with balanced spacing." << endl;
    }

    void playNextMatch() {
        if (!matchSchedule.empty()) {
            pair<Team*, Team*> match = matchSchedule.front();
            matchSchedule.pop();

            int score1 = rand() % 5;
            int score2 = rand() % 5;

            cout << "Playing: " << match.first->name << " vs " << match.second->name
                 << " | Score: " << score1 << " - " << score2 << endl;

            playGame(match.first, score1, match.second, score2);
            updateStandings();
        } else {
            cout << "No more matches scheduled." << endl;
        }
    }

    void playAllMatches() {
        while (!matchSchedule.empty()) {
            pair<Team*, Team*> match = matchSchedule.front();
            matchSchedule.pop();

            int score1 = rand() % 5;
            int score2 = rand() % 5;

            cout << "Playing: " << match.first->name << " vs " << match.second->name
                 << " | Score: " << score1 << " - " << score2 << endl;

            playGame(match.first, score1, match.second, score2);
        }
        updateStandings();
        cout << "All matches have been played." << endl;
    }

    void updateStandings() {
        standings.clear();
        for (auto& pair : teams) {
            standings.push_back(pair.second);
        }
        sort(standings.begin(), standings.end(), [](Team* t1, Team* t2) {
            if (t1->points != t2->points) return t1->points > t2->points;
            if (t1->goalDifference() != t2->goalDifference()) return t1->goalDifference() > t2->goalDifference();
            return t1->goalsFor > t2->goalsFor;
        });
    }

    void displayTable() {
        cout << left << setw(3) << "Pos" << setw(20) << "Team" << setw(8) << "P" << setw(8) << "W" << setw(8)
             << "D" << setw(8) << "L" << setw(8) << "GF" << setw(8) << "GA" << setw(8) << "GD" << setw(8)
             << "Pts" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        int position = 1;
        for (Team* team : standings) {
            team->displayTeamInfo(position++);
        }
    }

    void queryMaxPoints(const string& teamName, int numGames) {
        if (teams.find(teamName) != teams.end()) {
            cout << "Maximum points " << teamName << " can achieve after " << numGames << " games: "
                 << teams[teamName]->getMaxPoints(numGames) << endl;
        } else {
            cout << "Team " << teamName << " not found." << endl;
        }
    }

    void viewSchedule() {
        if (matchSchedule.empty()) {
            cout << "No matches scheduled." << endl;
            return;
        }

        time_t matchDateTime = startDate;
        tm* matchDate;
        int matchCount = 1;
        queue<pair<Team*, Team*>> tempQueue = matchSchedule;

        cout << "\n=== Match Schedule ===\n";
        while (!tempQueue.empty()) {
            pair<Team*, Team*> match = tempQueue.front();
            tempQueue.pop();

            matchDate = localtime(&matchDateTime);

            cout << "Match " << matchCount++ << ": " << match.first->name << " vs " << match.second->name
                 << " on " << put_time(matchDate, "%d-%m-%Y") << endl;

            matchDateTime += 7 * 24 * 60 * 60;
        }
    }
};

void displayMenu() {
    cout << "\n=== Welcome to the Football League Manager ===\n";
    cout << "1. Add Teams\n";
    cout << "2. Schedule Matches\n";
    cout << "3. Play Next Match\n";
    cout << "4. Display Standings\n";
    cout << "5. Query Max Points for a Team\n";
    cout << "6. View Match Schedule\n";
    cout << "7. Play All Matches\n";
    cout << "8. Exit\n";
    cout << "Please select an option: ";
};
