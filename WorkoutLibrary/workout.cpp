#include "workout.h"
#include <fstream>
#include <stdio.h>

// Defines used to easily parse data from the json files.
#define JSON_STRING_DATA readline.substr(readline.find(":") + 3, readline.find(",") - (readline.find(":") + 4))
#define JSON_INT_DATA std::stoi(readline.substr(readline.find(":") + 2, readline.find(",") - (readline.find(":") + 2)))

/*** Workout File Constructor ***/
/* Constructs a Workout object from a JSON file passed by its name */
Workout::Workout(std::string file) {
    
    // Initialize file variables.
    std::string filename = "WorkoutLibrary/workouts/" + file + ".json";
    std::ifstream workoutInput;
    std::string readline;

    /* Begin reading the file. */
    workoutInput.open(filename);

    // Check that the file is safe to read.
    if (!workoutInput.good()) {
        workoutInput.close(); 
        throw new BadParseError;
    }

    // Remove first brace.
    std::getline(workoutInput, readline);

    // Read in name data.
    std::getline(workoutInput, readline);
    this->name = JSON_STRING_DATA;

    // Read in calories data.
    std::getline(workoutInput, readline);
    this->calories = JSON_INT_DATA;

    // Read in reps data.
    std::getline(workoutInput, readline);
    this->reps = JSON_INT_DATA;

    // Read in restTime data.
    std::getline(workoutInput, readline);
    this->restTime = JSON_INT_DATA;

    // Close the file.
    workoutInput.close();

}


/*** Standard Constructor ***/
Workout::Workout(std::string name, int calories, int reps, int restTime) {
    this->name = name;
    this->calories = calories;
    this->reps = reps;
    this->restTime = restTime;
}


/*** To JSON Class Function ***/
/* Converts a Workout into a JSON file and returns the status of the operation. */
bool Workout::toJson(bool overwrite) {

    // Initialize file variables.
    std::ofstream workoutOutput;
    std::string filename = "WorkoutLibrary/workouts/" + name + ".json";

    // Check if file already exists and fail, or if it has an invalid name.
    // Can be overriden if the overwrite optional is passed as true.
    std::ifstream checkRead(filename);
    if (!overwrite && (name == "" || checkRead.good())) return false;

    // Write to the JSON file.
    workoutOutput.open(filename);
    workoutOutput << "{" << std::endl;
    workoutOutput << "\"name\": \"" + name + "\"," << std::endl;
    workoutOutput << "\"calories\": " + std::to_string(calories) + "," << std::endl;
    workoutOutput << "\"reps\": " + std::to_string(reps) + "," << std::endl;
    workoutOutput << "\"restTime\": " + std::to_string(restTime) << std::endl;
    workoutOutput << "}" << std::endl;
    workoutOutput.close();

    // Return the safety status of the file for reading.
    return workoutOutput.good();
}


/*** Delete JSON Class Function ***/
/* Deletes the JSON file associated with the Workout object. */
void Workout::deleteJson() {
    std::string filename = "WorkoutLibrary/workouts/" + this->name + ".json";
    if (remove(filename.c_str()) != 0) throw new BadParseError;
}