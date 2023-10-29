# Monty hall
Simulation of the famously unintuitive Monty Hall Problem.

Imagine you are on a gameshow, in front of you are three doors. Behing two on them is a goat and behind the last one is $1,000,000. The host asks you to pick a door, you recieve whatever is behind it. After you select a door, the host opens one of the remaining doors and reveals that behind it was a goat. Following this they give you a choice, do you want to stick with your door or switch to the other closed one? 

## C
In the folder `./C/`, you can find a simulation of this problem a compiled program and a results file.

Running `.\C\monty-hall.exe` presents you with a menu where you can change the settings and see how it affects the probability of you winning. The C/executable also allows you to change the number of doors at the beginning. You you choose to switch, you alternate between being shown a door and switching util you have the only door that is closed. 

You can also change how often you want to print how many games you have won so far, and you can run a preset of simulations with 3-9 doors with the gamehost showing 0-7 doors, both with you swiching at every chance, and you not switching.

![C Program Output](c-output.png "C Program Output")

## Python
Running `py ./threedoorprobem.py <number of simulations> <switch door?> <output_file_name>` lets you simulate the gameshow and lets you check for yourself if it is an advantage to switch doors or not.

![Python Program Output](py-output.png "Python Program Output")

Running `py ./monty-hall-animated.py` simulates you playing the game many times and switching doors every time. A graph is shown showing you hoe many percent of the games so far you have won.