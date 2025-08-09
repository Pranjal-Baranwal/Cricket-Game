#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_OVERS 5
#define BALLS_PER_OVER 6
#define MAX_WICKETS 10
#define MAX_PLAYERS 11
#define NAME_LENGTH 30

typedef struct {
    char name[NAME_LENGTH];
    int runs;
    int balls;
    int isOut;
} Player;

typedef struct {
    Player players[MAX_PLAYERS];
    int totalRuns;
    int totalBalls;
    int totalWickets;
    int extras;
} Innings;

int difficulty = 1;

const char *computerNames[MAX_PLAYERS] = {
    "David Warner", "Steve Smith", "Joe Root", "Kane Williamson", "Babar Azam",
    "Ben Stokes", "Quinton de Kock", "Glenn Maxwell", "Trent Boult",
    "Pat Cummins", "Shaheen Afridi"
};

int doToss() {
    int playerCall;
    printf("\n--- Toss Time ---\n");
    printf("Call the toss:\n1. Heads\n2. Tails\nEnter your choice (1 or 2): ");
    if (scanf("%d", &playerCall) != 1 || (playerCall != 1 && playerCall != 2)) {
        printf("Invalid choice. Defaulting to Heads.\n");
        playerCall = 1;
    }
    while (getchar() != '\n'); // Clear input buffer

    int tossResult = rand() % 2 + 1; // 1 = Heads, 2 = Tails

    printf("Toss result: %s\n", tossResult == 1 ? "Heads" : "Tails");

    if (playerCall == tossResult) {
        printf("You won the toss!\n");
        int choice;
        printf("Choose:\n1. Bat\n2. Bowl\nEnter your choice: ");
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
            printf("Invalid choice. Defaulting to Bat.\n");
            choice = 1;
        }
        while (getchar() != '\n');
        return choice; // 1 = Player bats first, 2 = Computer bats first
    } else {
        printf("Computer won the toss!\n");
        int compChoice = rand() % 2 + 1;
        printf("Computer chooses to %s first.\n", compChoice == 1 ? "bat" : "bowl");
        return compChoice == 2 ? 1 : 2; // Flip logic to fit your innings order
    }
}

void selectDifficulty() {
    printf("Select difficulty level:\n");
    printf("1. Easy\n2. Medium\n3. Hard\n4. Impossible\n");
    printf("Enter choice (1-4): ");
    if (scanf("%d", &difficulty) != 1) {
        difficulty = 1;
    }
    if (difficulty < 1 || difficulty > 4) {
        printf("Invalid difficulty. Defaulting to Easy.\n");
        difficulty = 1;
    }
    while (getchar() != '\n');
}

int getRiskChance(int runs, int isPlayer) {
    if (difficulty == 1) {
        if (runs >= 1 && runs <= 3) return 5;
        else if (runs == 4) return 30;
        else if (runs == 6) return 50;
        else if (runs == 0) return 2;
        return 0;
    } else if (difficulty == 2) {
        if (isPlayer) {
            if (runs == 3) return 80;
            if (runs == 4) return 50;
            if (runs == 6) return 60;
            if (runs == 0) return 5;
            if (runs >= 1 && runs <= 2) return 10;
        } else {
            if (runs == 4) return 40;
            if (runs == 6) return 60;
            if (runs == 0) return 5;
            if (runs >= 1 && runs <= 3) return 10;
        }
        return 0;
    } else if (difficulty == 3) {
        if (!isPlayer) {
            if (runs == 4 || runs == 6) return 40;
            if (runs == 0) return 10;
            if (runs >= 1 && runs <= 3) return 15;
        } else {
            if (runs == 4) return 60;
            if (runs == 6) return 70;
            if (runs == 3) return 90;
            if (runs == 0) return 10;
            if (runs >= 1 && runs <= 2) return 20;
        }
        return 0;
    } else if (difficulty == 4) {
        if (!isPlayer) {
            if (runs == 4 || runs == 6) return 35;
            else if (runs == 0) return 10;
            else return 5;
        } else {
            if (runs >= 0 && runs <= 6 && runs != 5) return 75;
            else return 0;
        }
    }
    return 0;
}

int getComputerRuns() {
    int r = rand() % 100;
    if (r < 10) return -1;
    if (r < 15) return 7;
    int runs;
    while (1) {
        runs = rand() % 7;
        if (runs != 5) break;
    }
    return runs;
}

void printScorecard(char *teamName, Innings *inning) {
    printf("\n--- %s Scorecard ---\n", teamName);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("%-20s %3d (%d balls)%s\n",
               inning->players[i].name,
               inning->players[i].runs,
               inning->players[i].balls,
               inning->players[i].isOut ? "" : " *");
    }
    printf("Extras: %d\n", inning->extras);
    printf("Total: %d/%d in %d balls\n", inning->totalRuns, inning->totalWickets, inning->totalBalls);
}

void playInnings(char *teamName, Innings *inning, int isPlayer) {
    inning->totalRuns = inning->totalBalls = inning->totalWickets = inning->extras = 0;
    printf("\n--- %s Innings ---\n", teamName);

    for (int i = 0; i < MAX_PLAYERS; i++) {
        inning->players[i].runs = 0;
        inning->players[i].balls = 0;
        inning->players[i].isOut = 0;
    }

    int batsman = 0;

    while (inning->totalBalls < MAX_OVERS * BALLS_PER_OVER && inning->totalWickets < MAX_WICKETS) {
        if (batsman >= MAX_PLAYERS) {
            printf("All players are out!\n");
            break;
        }

        int runs = -2;

        if (isPlayer) {
            int wide_chance = rand() % 100;
            if (wide_chance < 3) {
                printf("Wide ball! Extra run awarded.\n");
                inning->totalRuns++;
                inning->extras++;
                continue;
            }

            printf("Ball %d.%d - Enter runs (0-4, 6): ", inning->totalBalls / BALLS_PER_OVER + 1, inning->totalBalls % BALLS_PER_OVER + 1);
            if (scanf("%d", &runs) != 1) {
                printf("Invalid input. Try again.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            if (runs == 5 || runs < 0 || (runs > 4 && runs != 6)) {
                printf("Invalid input. Try again.\n");
                continue;
            }

            int risk = getRiskChance(runs, 1);
            int chance = rand() % 100;
            if (chance < risk) {
                printf("Oh no! You got out trying to score %d run(s)!\n", runs);
                inning->players[batsman].isOut = 1;
                inning->totalWickets++;
                inning->totalBalls++;
                batsman++;
                continue;
            }
        } else {
            runs = getComputerRuns();

            if (runs == -1) {
                printf("%s got out!\n", inning->players[batsman].name);
                inning->players[batsman].isOut = 1;
                inning->totalWickets++;
                inning->totalBalls++;
                batsman++;
                continue;
            } else if (runs == 7) {
                printf("Computer bowled a wide/no ball!\n");
                inning->totalRuns++;
                inning->extras++;
                continue;
            }

            int risk = getRiskChance(runs, 0);
            int chance = rand() % 100;
            if (chance < risk) {
                printf("Oh no! %s got out trying to score %d run(s)!\n", inning->players[batsman].name, runs);
                inning->players[batsman].isOut = 1;
                inning->totalWickets++;
                inning->totalBalls++;
                batsman++;
                continue;
            }
        }

        if ((runs >= 0 && runs <= 4) || runs == 6) {
            inning->players[batsman].runs += runs;
            inning->players[batsman].balls++;
            inning->totalRuns += runs;
            inning->totalBalls++;
            if (isPlayer)
                printf("Runs scored: %d. Total score: %d/%d\n", runs, inning->totalRuns, inning->totalWickets);
            else
                printf("%s scored %d run(s). Total: %d/%d\n", inning->players[batsman].name, runs, inning->totalRuns, inning->totalWickets);
        }
    }

    printf("%s innings over. Final score: %d/%d (Extras: %d)\n",
           teamName, inning->totalRuns, inning->totalWickets, inning->extras);
}

int main() {
    srand((unsigned int)time(0));
    Innings playerTeam, computerTeam;

    const char *userNames[MAX_PLAYERS] = {
        "Rohit Sharma", "Shikhar Dhawan", "Virat Kohli", "Ajinkya Rahane", "Hardik Pandya",
        "Suresh Raina", "MS Dhoni", "Ravindra Jadeja", "Jasprit Bumrah", "Ashish Nehra", "Varun Chakaravarthy"
    };

    for (int i = 0; i < MAX_PLAYERS; i++) {
        strncpy(playerTeam.players[i].name, userNames[i], NAME_LENGTH - 1);
        playerTeam.players[i].name[NAME_LENGTH - 1] = '\0';
        strncpy(computerTeam.players[i].name, computerNames[i], NAME_LENGTH - 1);
        computerTeam.players[i].name[NAME_LENGTH - 1] = '\0';
    }

    printf("Welcome to the Cricket Game Simulation!\n");
    selectDifficulty();

    int playerBatsFirst = doToss();

    if (playerBatsFirst == 1) {
        printf("\nYou will bat first.\n");
        playInnings("Team Player", &playerTeam, 1);
        playInnings("Team Computer", &computerTeam, 0);
    } else {
        printf("\nComputer will bat first.\n");
        playInnings("Team Computer", &computerTeam, 0);
        playInnings("Team Player", &playerTeam, 1);
    }

    printf("\n--- Match Result ---\n");
    printf("Player Team: %d/%d\n", playerTeam.totalRuns, playerTeam.totalWickets);
    printf("Computer Team: %d/%d\n", computerTeam.totalRuns, computerTeam.totalWickets);

    if (playerTeam.totalRuns > computerTeam.totalRuns) {
        printf("Player wins!\n");}
        
    else if (computerTeam.totalRuns > playerTeam.totalRuns) {
        printf("Computer wins!\n");
    } 
    else {
        printf("Match Drawn!\n");
    }

    printScorecard("Team Player", &playerTeam);
    printScorecard("Team Computer", &computerTeam);

    printf("\nPress Enter to exit...");
    while (getchar() != '\n');
    getchar();

    return 0;
}