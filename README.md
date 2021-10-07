# Adventure

Project for Object-oriented programming.

### Game Instruction

+ Game task: find the princess and take her out of the castle, if you encounter a monster during the game, the game will fail

+ The game starts: After unzipping, open test.exe

  + If it fails, type in the terminal

    ```
    cd file path
    g++ main.o Adventure.o Coordinate.o Map.o Room.o -o test
    test
    ```

    ready to run

+ First, you need to select the difficulty of the map. There are three options ABC to choose from. If you enter other illegal characters, you will be prompted and re-enter.

  + A.Easy
  + B.Moderate
  + C.Difficult

+ The initial position is Lobby, enter the selected direction according to the prompt.

  + The input must start with go, otherwise a prompt will appear and you need to re-enter.
  + If the direction is not within the selected range, it will prompt and need to re-enter.

+ Will prompt the current room.

+ When you find the princess, there will be a text prompt.

+ Encounter a monster, the game is over.