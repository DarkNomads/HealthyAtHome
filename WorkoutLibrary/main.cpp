#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include "workout.cpp"

/*** Function Stubs ***/

// Menus
int mainMenu();
int workoutMenu(const int, const std::string*);
void workoutOptionsMenu(Workout*);

// Workout Functions
Workout* selectWorkout();
void createWorkout();
void viewWorkout(Workout*);
void editWorkout(Workout*);
void deleteWorkout(Workout*);

// Helpers
void clearScreen() { std::cout << std::string( 100, '\n' ); }
int validateInput(const int, const int);
void exitProgram();
void readMetaDataNames(std::string*);
int readMetaDataCount();
void writeMetaData(const int, const std::string*);


/*** Main Program ***/
int main() {
    while(true) {
        switch(mainMenu()) {
            // Select A Workout
            case 1: {
                    Workout* selectedWorkout = selectWorkout();
                    if (selectedWorkout->getName() == "") break;
                    workoutOptionsMenu(selectedWorkout);
                    break;
            }
            // Create New Workout
            case 2: {
                createWorkout();
                break;
            }
            // Quit Program
            case 3:
                exitProgram();
                break;
        }
        clearScreen();
    }

    return 0;
}


/*** Main Menu Function ***/
/* Displays all the main program options available to the user and returns the user's choice. */
int mainMenu() {
    std::cout << "\n\n";
    std::cout << "|=============================================|" << std::endl;
    std::cout << "|        HealthyAtHome Workout Library        |" << std::endl;
    std::cout << "|---------------------------------------------|" << std::endl;
    std::cout << "|        Please Choose An Option Below        |" << std::endl;
    std::cout << "|                                             |" << std::endl;
    std::cout << "|        (1) Select A Workout                 |" << std::endl;
    std::cout << "|        (2) Create New Workout               |" << std::endl;
    std::cout << "|        (3) Quit Program                     |" << std::endl;
    std::cout << "|=============================================|" << std::endl;
    std::cout << "\n\n";

    // Return the user input.
    return validateInput(1, 3);
}


/*** Workout Menu Function ***/
/* Displays all Workout objects available to the user and returns the user's cjoice. */
int workoutMenu(const int SIZE, const std::string* workoutArray) {
    clearScreen();
    std::cout << "\n\n";
    std::cout << "|=============================================|" << std::endl;
    std::cout << "|           HealthyAtHome Workouts            |" << std::endl;
    std::cout << "|---------------------------------------------|" << std::endl;
    std::cout << "|        Please Choose A Workout Below        |" << std::endl;
    std::cout << "|                                             |" << std::endl;
    for(int i = 0; i < SIZE; i++) {
        std::cout << "|        (" << i+1 << ") " << std::setw(33) << std::left << workoutArray[i] << "|" << std::endl;
    }
    std::cout << "|        (" << SIZE+1 << ") " << std::setw(33) << std::left << "Next" << "|" << std::endl;
    std::cout << "|        (" << SIZE+2 << ") " << std::setw(33) << std::left << "Previous" << "|" << std::endl;
    std::cout << "|        (" << SIZE+3 << ") " << std::setw(33) << std::left << "Back to Menu" << "|" << std::endl;
    std::cout << "|=============================================|" << std::endl;
    std::cout << "\n\n";

    return (validateInput(1, SIZE+3)-1);
}


/*** Workout Options Menu Function ***/
/* Selects whether a user wants to view/edit/delete and calls the appropriate action. */
void workoutOptionsMenu(Workout* workout) {
    int padding = ((46 - (workout->getName()).length())/2);
    std::cout << "\n\n";
    std::cout << "|=============================================|" << std::endl;
    std::cout << "|";
    for(int i = 0; i < padding; i++) std::cout << " ";
    std::cout << workout->getName();
    if((workout->getName().length())%2 == 0) padding--;
    for(int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << "|---------------------------------------------|" << std::endl;
    std::cout << "|        Please Choose An Option Below        |" << std::endl;
    std::cout << "|                                             |" << std::endl;
    std::cout << "|        (1) View Workout                     |" << std::endl;
    std::cout << "|        (2) Edit Workout                     |" << std::endl;
    std::cout << "|        (3) Delete Workout                   |" << std::endl;
    std::cout << "|=============================================|" << std::endl;
    std::cout << "\n\n";

    int choice = validateInput(1, 3);

    switch(choice) {
        case 1:
            viewWorkout(workout);
            break;
        case 2:
            editWorkout(workout);
            break;
        case 3:
            deleteWorkout(workout);
            break;
    }
}


/*** Selects Workout Function ***/
/* Selects and returns a Workout object for the user to view/edit/delete. */
Workout* selectWorkout() {

    // Fetch metadata from the metadata file.
    int numWorkouts = readMetaDataCount();
    std::string workoutNames[numWorkouts];
    readMetaDataNames(workoutNames);

    // Display the menu.
    int selected = -1;
    int offset = 0;
    int relativeSize = 0;
    while(selected == -1) {
        // If the Workouts are larger than each menu size...
        if(numWorkouts > 6) {

            // Set the relative size.
            if(offset == 0) relativeSize = 6;
            else {
                if(numWorkouts - (offset*6) > 6) relativeSize = 6;
                else relativeSize = numWorkouts - (offset*6);
            }

            // Create a new list and display the menu.
            std::string relativeNames[relativeSize];
            for(int i = 0; i < relativeSize; i++) relativeNames[i] = workoutNames[(offset*6)+i];
            selected = workoutMenu(relativeSize, relativeNames);

            // Previous page.
            if(selected == relativeSize+1){
                if(offset > 0) offset--;
                selected = -1;
            }

            // Next page.
            else if(selected == relativeSize) {
                if (numWorkouts - ((offset+1)*6) > 0) offset++;
                selected = -1;
            }

            // Return to menu.
            else if(selected == relativeSize+2) selected = -2;

            // Convert relative value to the absolute value.
            else {
                selected += (offset*6);
            }
        }
        // Show all the Workouts if they fit on one menu.
        else {
            selected = workoutMenu(numWorkouts, workoutNames);

            // Handle next and previous by returning to the same page.
            if(selected == numWorkouts || selected == numWorkouts+1) selected = -1;

            // Return to menu.
            if(selected == numWorkouts+2) selected = -2;

        }
    }

    // Return a dummy Workout to go back to the menu.
    if(selected == -2) return new Workout();

    // Return the user selected Workout.
    Workout* selectedWorkout = new Workout(workoutNames[selected]);
    return selectedWorkout;
}


/*** Create Workout Function ***/
/* Locally creates a Workout object and converts it to a JSON file. */
void createWorkout() {

    // Declare Workout property inputs.
    std::string name;
    int calories, reps, restTime;

    // Show creation prompt
    clearScreen();
    std::cout << "\n\n";
    std::cout << "|=============================================|" << std::endl;
    std::cout << "|               Workout Creator               |" << std::endl;
    std::cout << "|=============================================|" << std::endl;
    std::cout << "\n\n";
    
    // Assign the name.
    std::cout << "Enter the Workout name: ";
    std::getline(std::cin, name);

    // Assign the calories.
    std::cout << "Enter the Workout calories burned: ";
    std::cin >> calories;

    // Assign the reps.
    std::cout << "Enter the Workout repetitions: ";
    std::cin >> reps;

    // Assign the rest time.
    std::cout << "Enter the Workout rest time in seconds: ";
    std::cin >> restTime;

    // Clear the input buffer.
    std::cin.ignore();

    // Create Workout object.
    Workout* workout = new Workout(name, calories, reps, restTime);

    // Convert Workout object to JSON
    if(workout->toJson()) {

        // Update the metadata file.
        std::string workoutNames[readMetaDataCount() + 1];
        readMetaDataNames(workoutNames);
        workoutNames[readMetaDataCount()] = workout->getName();
        writeMetaData(readMetaDataCount() + 1, workoutNames );

        // Show success before returning
        std::cout << "\n\n";
        std::cout << "|=============================================|" << std::endl;
        std::cout << "|         Workout Creation Successful         |" << std::endl;
        std::cout << "|=============================================|" << std::endl;
        std::cout << "\n\n";
        getch();
    }
    else {
        // Show failure before returning
        std::cout << "\n\n";
        std::cout << "|=============================================|" << std::endl;
        std::cout << "|          Workout Creation Failed            |" << std::endl;
        std::cout << "|=============================================|" << std::endl;
        std::cout << "\n\n";
        getch();
    }
}


/*** Validate Input Function ***/
/* Checks that the input falls within the passed range, and returns the input when it is. */
int validateInput(const int MIN, const int MAX) {
    while(true) {
        // Discretely grabs the input character and converts it to a number.
        int input = getch() - '0';
        // Returns input  when it falls within the range.
        if(input >= MIN && input <= MAX) return input;
    }
}


/*** Exit Program Function ***/
/* Exits the program. */
void exitProgram() {
    clearScreen();
    std::cout << "\n\n";
    std::cout << "|=============================================|" << std::endl;
    std::cout << "|                  Goodbye!                   |" << std::endl;
    std::cout << "|=============================================|" << std::endl;
    std::cout << "\n\n";
    exit(EXIT_SUCCESS);
}


/*** Read Meta Data Count Function ***/
/* Reads in how many Workout objects exist according to the metadata file and returns that value. */
int readMetaDataCount() {
    // Initialize file variables.
    std::ifstream workoutMeta;
    std::string readline;

    /* Begin reading the file. */
    workoutMeta.open("WorkoutLibrary/workouts/meta/metadata.json");

    // Remove the first brace.
    std::getline(workoutMeta, readline);

    // Read in the workout count.
    std::getline(workoutMeta, readline);
    return std::stoi(readline.substr(readline.find(":") + 2, readline.find(",") - (readline.find(":") + 2)));
}


/*** Read Meta Data Names Function ***/
/* Reads in each Workout objects name according to the metadata file and populates passed array with the value(s). */
void readMetaDataNames(std::string* returnArray) {

    // Initialize file variables.
    std::ifstream workoutMeta;
    std::string readline;

    /* Begin reading the file. */
    workoutMeta.open("WorkoutLibrary/workouts/meta/metadata.json");

    // Move to correct read location.
    std::getline(workoutMeta, readline);
    std::getline(workoutMeta, readline);
    std::getline(workoutMeta, readline);
    std::getline(workoutMeta, readline);

    /* Read in each workout. */
    int iterator = 0;

    while(readline != "]") {
        std::string firstQuote = readline.substr(readline.find("\"") + 1);
        returnArray[iterator++] = (firstQuote.substr(0, firstQuote.find("\"")));
        std::getline(workoutMeta, readline);
    }

    // Close the file.
    workoutMeta.close();
}


/*** Write Meta Data Function ***/
/* Writes the count and the list of names passed into the function into the metadata file. */
void writeMetaData(const int count, const std::string* names)
{
    // Initialize file variables.
    std::ofstream workoutMeta;
    std::string filename = "WorkoutLibrary/workouts/meta/metadata.json";

    // Write to the JSON metadata file.
    workoutMeta.open(filename);
    workoutMeta << "{" << std::endl;
    workoutMeta << "\"count\": " + std::to_string(count) + "," << std::endl;
    workoutMeta << "\"workouts\": [" << std::endl;
    for(int i = 0; i < count; i++) {
        workoutMeta << '"' + names[i] + '"';
        if(i + 1 != count) workoutMeta << ",";
        workoutMeta << std::endl;
    }
    workoutMeta << "]" << std::endl;
    workoutMeta << "}" << std::endl;
    workoutMeta.close();
}


/*** View Workout Function ***/
/* Displays information about the Workout object passed in. */
void viewWorkout(Workout* workout) {
    clearScreen();
    int padding = ((46 - (workout->getName()).length())/2);
    std::cout << "\n\n";
    std::cout << "|=============================================|" << std::endl;
    std::cout << "|";
    for(int i = 0; i < padding; i++) std::cout << " ";
    std::cout << workout->getName();
    if((workout->getName().length())%2 == 0) padding--;
    for(int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << "|---------------------------------------------|" << std::endl;
    std::cout << "|             Workout Information             |" << std::endl;
    std::cout << "|                                             |" << std::endl;
    std::cout << "|       Calories Burned: " << std::setw(21) << std::left << workout->getCalories() << "|" << std::endl;
    std::cout << "|  Repetitions Required: " << std::setw(21) << std::left << workout->getReps() << "|" << std::endl;
    std::cout << "|   Rest Time (seconds): " << std::setw(21) << std::left << workout->getRestTime() << "|" << std::endl;
    std::cout << "|=============================================|" << std::endl;
    std::cout << "\n\n";
    getch();
}


/*** Edit Workout Function ***/
/*  Asks the user which attribute they would like to edit and updates the information. */
void editWorkout(Workout* workout) {
    int padding = ((46 - (workout->getName()).length())/2);
    std::cout << "\n\n";
    std::cout << "|=============================================|" << std::endl;
    std::cout << "|";
    for(int i = 0; i < padding; i++) std::cout << " ";
    std::cout << workout->getName();
    if((workout->getName().length())%2 == 0) padding--;
    for(int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << "|---------------------------------------------|" << std::endl;
    std::cout << "|        Please Choose An Option Below        |" << std::endl;
    std::cout << "|                                             |" << std::endl;
    std::cout << "|        (1) Edit Calories                    |" << std::endl;
    std::cout << "|        (2) Edit Reps                        |" << std::endl;
    std::cout << "|        (3) Edit Rest Time                   |" << std::endl;
    std::cout << "|=============================================|" << std::endl;
    std::cout << "\n\n";

    int choice = validateInput(1, 3);

    switch(choice) {
        case 1:
            // Assign the calories.
            int calories;
            std::cout << "Enter the Workout calories burned: ";
            std::cin >> calories;
            workout->setCalories(calories);
            break;
        case 2:
            // Assign the reps.
            int reps;
            std::cout << "Enter the Workout repetitions: ";
            std::cin >> reps;
            workout->setReps(reps);
            break;
        case 3:
            // Assign the rest time.
            int restTime;
            std::cout << "Enter the Workout rest time in seconds: ";
            std::cin >> restTime;
            workout->setRestTime(restTime);
            break;
    }
    // Clear the input buffer.
    std::cin.ignore();
}


/*** Delete Workout Function ***/
/*  Deletes the Workout object passed in and rewrites the metadata file. */
void deleteWorkout(Workout* workout) {
    int count = readMetaDataCount();
    std::string oldNames[count];
    std::string newNames[count-1];
    readMetaDataNames(oldNames);
    int j = 0;
    for(int i = 0; i < count; i++) {
        if(oldNames[i] != workout->getName()) {
            newNames[j] = oldNames[i];
            j++;
        }
    }
    for(int i = 0; i < count-1; i++) std::cout << newNames[i] << std::endl;
    writeMetaData(count-1, newNames);
    workout->deleteJson();
}
