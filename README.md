# Football Manager Project

## Overview
The Football Manager project is a console-based application that allows users to manage a football league. The system allows you to add teams, schedule matches, play games, display standings, and view the match schedule. It includes a simple simulation of matches and updates the league standings after each match.

## Features
- Add teams to the league.
- Schedule matches between teams.
- Simulate matches and update results.
- View the current standings based on match results.
- Query maximum points a team can achieve after a set number of matches.
- View the match schedule with dates.
- Play all scheduled matches in sequence.

## Folder Structure

```
.vscode/                    # VS Code settings
libs/                        # Libraries for the application
  ├── classes/               # Class implementations for League and Team
      ├── league.cpp         # League class
      └── team.cpp           # Team class
  ├── implementation/        # Main program and match simulation
      ├── main1.cpp          # Main execution file (RUN HERE)
      └── main1.exe          # Compiled executable
  ├── util/                  # Utility files
      ├── constants          # Constants used in the program
      └── libraries          # Additional library files
          └── libs.cpp       # Utility functions
README.md                    # Project documentation

```

## How to Use
1. Add Teams: Use the option in the menu to add teams to the league.

2. Schedule Matches: Enter the start date for the league, and the system will automatically generate a schedule of matches.

3. Play Matches: You can choose to simulate a match or simulate all remaining matches.

4. View Standings: The standings will be displayed with rankings based on points, goals, and other statistics.

5. Query Max Points: You can query the maximum points a team can achieve after a given number of matches.

6. View Match Schedule: The schedule of upcoming matches will be displayed, including dates.