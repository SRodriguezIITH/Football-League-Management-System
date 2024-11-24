#include "../../util/libraries/libs.cpp"

class Team {
public:
    string name;
    int played;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;
    int points;
    vector<int> dp;  

    
    Team(string name) : name(name), played(0), wins(0), draws(0), losses(0), goalsFor(0), goalsAgainst(0), points(0) {
        dp.push_back(0); 
    }

    
    void updateResults(int gf, int ga) {
        played++;
        goalsFor += gf;
        goalsAgainst += ga;

        if (gf > ga) {
            wins++;
            points += 3;
        } else if (gf == ga) {
            draws++;
            points += 1;
        } else {
            losses++;
        }

        
        dp.push_back(max(dp.back(), points));
    }

    
    int goalDifference() const {
        return goalsFor - goalsAgainst;
    }

    
    void displayTeamInfo(int position) const {
        cout << left << setw(3) << position << setw(20) << name << setw(8) << played << setw(8) << wins
             << setw(8) << draws << setw(8) << losses << setw(8) << goalsFor << setw(8) << goalsAgainst
             << setw(8) << goalDifference() << setw(8) << points << endl;
    }

    int getMaxPoints(int numGames) const {
        if (numGames > played) return dp[played];  
        return dp[numGames];  
    }
};