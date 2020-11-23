#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>

// Error Classes
class BadParseError {};

class Workout {
    
    // Attributes
    std::string name = "";
    int calories = 0, reps = 0, restTime = 0;

    // Class Function Stubs
    public:

        // Constructors
        Workout() {}
        Workout(std::string, int, int, int);
        Workout(std::string);
        
        // File Writer & Deleter
        bool toJson(bool overwrite = false);
        void deleteJson();

        // Getters
        std::string getName() { return this->name; }
        int getCalories() { return this->calories; }
        int getReps() { return this->reps; }
        int getRestTime() { return this->restTime; }

        // Setters
        void setCalories(int calories) { this->calories = calories; this->toJson(true); }
        void setReps(int reps) { this->reps = reps; this->toJson(true); }
        void setRestTime(int restTime) { this->restTime = restTime; this->toJson(true); }
};

#endif