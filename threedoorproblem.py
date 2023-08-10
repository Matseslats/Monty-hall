import random
import math
from sys import argv


if len(argv) != 4:
    print("Please use 'threedoorproblem.py NumberOfSimulations SwapOrNot[0-1] CSVFileName")
    exit()

path, simulations, swap, saveas = argv


def print_array(array):
    for i in array:
        print(i, " ", end="")
    print()

wins = 0
loose = 0
runsim = int(simulations)
gamesplayed = 0
printInfo = 0
winpercent = []
simno = []

while(runsim > 0):
    door = [False, False, False]
    doorOpen = [False, False, False]

    yourPick = math.floor(random.randrange(0,3))
    chosenDoor = math.floor(random.randrange(0,3))
    door[yourPick] = True

    if printInfo:
        print("You chose ", yourPick)
        # print_array(door)
        print("Correct is ", chosenDoor)
        # doorPiced = 0

    doorOpened = False
    while not doorOpened:  # Gjør helt til en dør en åpna
        tryToShow = math.floor(random.randrange(0,3))
        # print("Trying to show ", tryToShow+1)
        if not tryToShow == chosenDoor:  # Hvis den ikke prøver å vise premien,
            if not tryToShow == yourPick:
                if not doorOpen[tryToShow]:  # Hvis døren ikke er åpen
                    doorOpen[tryToShow] = True  # Åpne døra
                    doorOpened = True  # En dør har blitt åpnet
                    if printInfo:
                        print("Gamehost opened ", tryToShow)
                        # print_array(doorOpen)

    switch = int(swap)
    if switch:
        doorOpen[yourPick] = True  # Åpne den du ikke trodde det var
        # print_array(doorOpen)
        newPick = 4
        for i in range(3):  # Finn den døren som ikke er åpnet enda, og velg den
            if not doorOpen[i]:
                newPick = i
        yourPick = newPick
        if printInfo:
            print("You switched to ", newPick)

    if yourPick == chosenDoor:
        wins += 1
    else:
        loose += 1

    gamesplayed += 1
    winPercentage = wins/gamesplayed*100
    winpercent.append(float(winPercentage))
    simno.append(gamesplayed)
    print("Wins ", wins, "\t Losses", loose, "\t Wins [%]", winPercentage,)

    runsim -= 1


arrayToSave = [simno,winpercent]

with open(path[0:-3] + "/" + saveas, "wb") as f:
    for i in range(len(winpercent)):
        stringToWrite = ("%d;%r\n" % (i, winpercent[i])).replace('.', ',').encode()
        f.write(stringToWrite)

    f.flush()

