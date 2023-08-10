import random, math
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

style.use('fivethirtyeight')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

graphy = []
graphx = []

wins = 0
loose = 0
runsim = 1
gamesplayed = 0
printInfo = 0


def print_array(array):
    for i in array:
        print(i, " ", end="")
    print()


def animate(i):
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

    switch = 1
    if switch:
        doorOpen[yourPick] = True  # Åpne den du ikke trodde det var
        # print_array(doorOpen)
        newPick = 4
        for i in range(3):  # FInn den døren som ikke er åpnet enda
            if not doorOpen[i]:
                newPick = i
        yourPick = newPick
        if printInfo:
            print("You switched to ", newPick)

    global wins, loose, gamesplayed
    if yourPick == chosenDoor:
        wins += 1
    else:
        loose += 1

    gamesplayed += 1
    winPercentage = wins/gamesplayed*100
    graphy.append(winPercentage)
    graphx.append(gamesplayed)
    print("Wins ", wins, "\t Losses", loose, "\t Wins [%]", winPercentage,)

    ax1.clear()
    ax1.plot(graphx, graphy)

while(True):
    animate(0)
    ani = animation.FuncAnimation(fig, animate, interval=1000)
    plt.show()
