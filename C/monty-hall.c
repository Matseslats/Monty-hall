#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>      /* wint_t */
#include <string.h>
#include <math.h>


int wins, losses, gamesPlayed = 0;
int switchDoor = 1;
int doors = 3;
int openThisManyDoors = 1;
unsigned long long simulations = 300;
int displayrate = 1000;
int debug = 0;

void printDoors(int pick, int doorstatuses[]){
    printf("Doors: ");
    for(int i = 0; i < doors; i++){
        if(i == pick){
            printf("X");
        } else if (doorstatuses[i] == 1){
            printf("O");//"%lc\n", (wint_t)9647); // Print en åpen dør 	▯ 
        } else {
            printf("C");//"%lc\n", (wint_t)9646); // Print en lukket dør  	▮ 
        }
    }
    printf("\n\n");
}

void changeSettings(){
    gamesPlayed = wins = losses = 0;
    int stayinSettings = 1;
    while(stayinSettings){
        printf("---------------------------------------------------\n");
        printf("What setting do you want to change? | Current state\n");
        printf("---------------------------------------------------\n");
        printf("[1] Door amount                     | %d\n", doors);
        printf("[2] How many doors to open          | %d\n", openThisManyDoors);
        printf("[3] Toggle sitch door               | %s\n", switchDoor ? "True" : "False");
        printf("[4] How many simulations to run     | %d\n", simulations);
        printf("[5] Show state every x simulations  | %d\n", displayrate);
        printf("[6] Debug                           | %s\n", debug ? "True" : "False");
        printf("[0] Return to main menu\n\n");
        int option;
        scanf("%d", &option);

        switch (option){
        case 1:
            printf("Enter door amount: ");
            scanf("%d", &doors);
            break;
        case 2:
            printf("Enter how many doors to open: ");
            scanf("%d", &openThisManyDoors);
            break;
        case 3:
            switchDoor = !switchDoor;
            printf("Switching doors is now ");
            if(switchDoor){
                printf("ENABLED");
            } else {
                printf("DISABLED");
            }
            printf("\n");
            break;
        case 4:
            printf("Enter how many simulations to run: ");
            scanf("%d", &simulations);
            break;
        case 5:
            printf("Enter how often to display results (1/x): ");
            scanf("%d", &displayrate);
            break;
        case 6:
            debug = !debug;
            printf("Debugging is now ");
            if(debug){
                printf("ENABLED");
            } else {
                printf("DISABLED");
            }
            printf("\n");
            break;
        case 0:
            stayinSettings = 0;
        default:
            break;
        }
    }
}

float runSim(int sims, int printRes){
    float winAmount;
    wins = losses = gamesPlayed = 0;
    if(printRes){
        printf("Simulating....\n");
    }
    clock_t start, end;
    start = clock();
    srand(time(0));
    
    while (sims > 0){
        int repeat = openThisManyDoors;
        // Sett opp dørene
        int* isDoorOpen;
        isDoorOpen = (int *)malloc(doors * sizeof(int));
        for(int i = 0; i < doors; i++){
            isDoorOpen[i] = 0;
        }
        //int isDoorOpen[doors];
        //memset(isDoorOpen, 0, sizeof isDoorOpen);
        int a = {0};
        int yourPick = rand()%doors; // Første valg 
        int chosenDoor = rand()%doors; // Premie
        if(debug){
            printf("Your pick: %d\n", yourPick);
            printf("Win door:  %d\n", chosenDoor);
            printDoors(yourPick, isDoorOpen);
        }
        while(repeat > 0){
            // Gamehost åpner en dør, ueffektiv
            int doorHasBeenOpened = 0;
            while(!doorHasBeenOpened){
                int trytoOpen = rand()%doors;
                if(trytoOpen != yourPick && trytoOpen != chosenDoor && isDoorOpen[trytoOpen] != 1){
                    isDoorOpen[trytoOpen] = 1; // Marker dør som åpnet
                    doorHasBeenOpened = 1;
                    if(debug){
                        printf("Revealed door: %d\n", trytoOpen);
                        printDoors(yourPick, isDoorOpen);
                    }
                } /*else {
                    printf("Could not open %d\n", trytoOpen);
                }*/

            }

            // Bytt dør
            if(switchDoor){
                int doorHasBeenSwitched = 0;
                while(!doorHasBeenSwitched){
                    int newPick = rand()%doors; // Prøv å bytte til denne døren
                    if(newPick != yourPick && isDoorOpen[newPick] == 0){
                        yourPick = newPick;
                        doorHasBeenSwitched = 1;
                    } else {
                        if(debug){
                            printf("\tCould not switch to %d: Door is open? %d, your pick is %d\n", newPick, isDoorOpen[newPick], yourPick);
                        }
                    }
                }
            }
            if(debug){
                printf("New pick:  %d\n", yourPick);
                printDoors(yourPick, isDoorOpen);
            }
            repeat --;
        }

        if(yourPick == chosenDoor){
            wins ++;
        } else {
            losses ++;
        }

        gamesPlayed ++;
        if(debug == 1){
            
        }

        float isWHoleNumber = (float)gamesPlayed/displayrate;
        float winPercentage = 100*(float)wins/gamesPlayed;
        winAmount = winPercentage;
        if((sims == 1 || isWHoleNumber == floor(isWHoleNumber)) && printRes){
            printf("Games: %d \t Wins: %d \t Losses: %d \t WinPercentage: %.6f \n", gamesPlayed, wins, losses, winPercentage);
        }
        
        
        sims --;
    }

    // Bergen tiden simulasjonen tok å simulere
    end = clock();
    double time_taken = (double)(end - start) / (double)CLOCKS_PER_SEC;
    if(printRes){
        printf("Simulation took %f seconds\n", time_taken);
        printf("On average %.1f sims per sec\n", (double)gamesPlayed/time_taken);
        printf("\n\n");
    }
    return winAmount;
}

void exportMatrix(){
    FILE * file;
    file = fopen("results.csv", "w+");
    char horiDiffer = ',';
    unsigned long long saved_simulations = simulations;
    int saved_switchDoor = switchDoor;
    int saved_doors = doors;
    int saved_openThisManyDoors = openThisManyDoors;
    int saved_displayrate = displayrate;

    simulations = 10000000;
    displayrate = 10000000;
    fprintf(file, "%c", horiDiffer);
    for(int doorOpenAmount = 0; doorOpenAmount <= 9 -2; doorOpenAmount ++){
        fprintf(file, "%d doorsGamehostOpens%c ", doorOpenAmount, horiDiffer);
    }
    fprintf(file, "\n");
    for(int switchOrNot = 0; switchOrNot <= 1; switchOrNot ++){
        fprintf(file, "%s\n", switchOrNot ? "Switch" : "Stay");
        for(int doorAmount = 3; doorAmount <= 9; doorAmount ++){
            fprintf(file, "%d doors%c ", doorAmount, horiDiffer);
            for(int doorOpenAmount = 0; doorOpenAmount <= doorAmount -2; doorOpenAmount ++){
                doors = doorAmount;
                openThisManyDoors = doorOpenAmount;
                switchDoor = switchOrNot;
                float temp = 0;
                printf("Simulating %d times, %d doors, %d switch-times, %d, ", simulations, doors, openThisManyDoors, switchDoor);
                temp = runSim(simulations, 0);
                
                char buffer[10];
                sprintf(buffer, "%f", temp);

                for(int i = 0; i < sizeof buffer; i++){
                    if(buffer[i] == '.'){
                        buffer[i] == ',';
                    }
                }

                fprintf(file, "%s%c", buffer, horiDiffer);
                printf("Result: %f\n", temp);
            }
            fprintf(file, ";\n");
        }
        fprintf(file, "\n\n\n");
    }

    fclose(file);

    simulations = saved_simulations;
    switchDoor = saved_switchDoor;
    doors = saved_doors;
    openThisManyDoors = saved_openThisManyDoors;
    displayrate = saved_displayrate;

}

int main(){
    while(1){
        printf("--------------------------------------------------------------------------------------\n");
        printf("Settings: Simulations: %d\tDoors: %d\tDoors to open: %d\tSwitch %d\n", simulations, doors, openThisManyDoors, switchDoor);
        printf("--------------------------------------------------------------------------------------\n");

        printf("Enter mode\n");
        printf("[1] Run simulation\n");
        printf("[2] Change options\n");
        printf("[3] Export matrix\n");
        printf("[0] Exit\n");
        int setting;
        scanf("%d", &setting);

        float _temp = 0;
        switch (setting){
        case 1:
            _temp = runSim(simulations, 1);
            break;
        case 2:
            changeSettings();
            break;
        case 3:
            exportMatrix();
            break;
        case 0:
            exit(1);
            break;
        default:
            printf("Invalid, Enter a valid integer, and no extra characters.\n");
            break;
        }
    }
}
