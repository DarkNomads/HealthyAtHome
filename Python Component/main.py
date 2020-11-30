# Calorie & Macro Tracker

# Libraries
import datetime
import calendar
import matplotlib.pyplot as plt

# Functions


def display_menu():
    print("\n*-----Calorie & Macro Tracker-----*")
    print("1. Set goals (daily)")
    print("2. Calculate today's net calorie")
    print("3. Enter today's macros")
    print("4. Display this week's progress")
    print("5. Quit program")


def calc_net_cal():
    # User enters intake/burn
    cal_in = int(input("Enter calorie intake: "))
    cal_burn = int(input("Enter calorie burned: "))
    # Calculate net calories
    net_cal = cal_in - cal_burn
    # Store net calorie information
    weekly_cal[curr_day] = net_cal
    # Display today's net calorie & compare with goal
    print("\nToday's net calorie:", net_cal)
    print("Daily calorie goal:", cal_goal)
    # Calc difference between actual net and goal
    cal_diff = net_cal - cal_goal
    if cal_diff == 0:
        print("Daily calories met.")
    elif cal_diff > 0:
        print("Daily calories exceeded goal.")
    else:
        print("Daily calories not met.")


def macro_entry_comparison():
    # User entries
    carbs = int(input("Enter today's amount of carbs(grams): "))
    fat = int(input("Enter today's amount of fat(grams): "))
    protein = int(input("Enter today's amount of protein(grams): "))
    print()

    # Store macro information
    weekly_carb[curr_day] = carbs
    weekly_fat[curr_day] = fat
    weekly_protein[curr_day] = protein

    macro_names = ["carbs", "fat", "protein"]
    macro_diff = []
    macro_goals = [carb_goal, fat_goal, protein_goal]

    # Goal comparison
    carb_diff = macro_goals[0] - carbs
    macro_diff.append(carb_diff)
    fat_diff = macro_goals[1] - fat
    macro_diff.append(fat_diff)
    protein_diff = macro_goals[2] - protein
    macro_diff.append(protein_diff)

    k = 0
    for macro in macro_diff:
        print("Amount of", macro_names[k], "goal:", macro_goals[k], "grams")
        if macro == 0:
            print("Daily amount of", macro_names[k], "met.")
        elif macro > 0:
            print("Daily amount of", macro_names[k], "not met.")
        else:
            print("Daily amount of", macro_names[k], "exceeded goal.")
        k += 1


def graph():
    # Calories plot
    plt.hlines(2250, 0, 6, colors='green', linestyles='dashed', label='Goal')
    plt.bar(short_days, weekly_cal, width=0.5)
    plt.ylabel("Calories")
    plt.xlabel("Days")
    plt.title("This Week's Calories")
    plt.legend()
    plt.show()

    # Carbs plot
    plt.hlines(160, 0, 6, colors='green', linestyles='dashed', label='Goal')
    plt.bar(short_days, weekly_carb, width=0.5)
    plt.ylabel("Carbs (g)")
    plt.xlabel("Days")
    plt.title("This Week's Amount of Carbs")
    plt.legend()
    plt.show()

    # Fat plot
    plt.hlines(87, 0, 6, colors='green', linestyles='dashed', label='Goal')
    plt.bar(short_days, weekly_fat, width=0.5)
    plt.ylabel("Fat (g)")
    plt.xlabel("Days")
    plt.title("This Week's Amount of Fat")
    plt.legend()
    plt.show()

    # Protein plot
    plt.hlines(44, 0, 6, colors='green', linestyles='dashed', label='Goal')
    plt.bar(short_days, weekly_protein, width=0.5)
    plt.ylabel("Protein (g)")
    plt.xlabel("Days")
    plt.title("This Week's Amount of Protein")
    plt.legend()
    plt.show()


# -----------------------------------------------------------------

# Main Program


# Get day of the week; 0 = Monday ... 6 = Sunday
curr_day = datetime.date.today().weekday()
week = list(calendar.day_name)

# Abbreviated days of the week list (Used for plotting data)
short_days = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]

# Open goals file (Cals, Carbs, Fat, and Protein are listed descending in the .txt file respectively.)
goals_file = open("goals.txt", "r+")

# User calorie and macro goals (daily)
cal_goal = int(goals_file.readline())
carb_goal = int(goals_file.readline())
fat_goal = int(goals_file.readline())
protein_goal = int(goals_file.readline())

# Open daily files
cal_file = open("daily_cal.txt", "r+")
carb_file = open("daily_carbs.txt", "r+")
fat_file = open("daily_fat.txt", "r+")
protein_file = open("daily_protein.txt", "r+")
# Load values into list
cal_week_str = cal_file.readline()
carb_week_str = carb_file.readline()
fat_week_str = fat_file.readline()
protein_week_str = protein_file.readline()
# Current week's calories/macro list
weekly_cal = cal_week_str.split(" ")
weekly_carb = carb_week_str.split(" ")
weekly_fat = fat_week_str.split(" ")
weekly_protein = protein_week_str.split(" ")
# Cast string to int
for i in range(len(weekly_cal)):
    weekly_cal[i] = int(weekly_cal[i])
    weekly_carb[i] = int(weekly_carb[i])
    weekly_fat[i] = int(weekly_fat[i])
    weekly_protein[i] = int(weekly_protein[i])


while True:
    display_menu()
    menu_choice = input("\nSelection: ")

    # User sets goals
    if menu_choice == "1":
        # Goal entries
        cal_goal = int(input("Enter your daily calorie goal: "))
        carb_goal = int(input("Enter your daily carb goal(grams): "))
        fat_goal = int(input("Enter your daily fat goal(grams): "))
        protein_goal = int(input("Enter your daily protein goal(grams): "))
        # Save goal values to .txt
        goals_file.seek(0)
        goals_file.write(str(cal_goal) + "\n")
        goals_file.write(str(carb_goal) + "\n")
        goals_file.write(str(fat_goal) + "\n")
        goals_file.write(str(protein_goal))
    # Calculates net calories
    elif menu_choice == "2":
        calc_net_cal()
    # Compares macro values with target
    elif menu_choice == "3":
        macro_entry_comparison()
    # Displays user's weekly progress along with graphed data
    elif menu_choice == "4":
        print("\n*-----Weekly Progress-----*")
        print("Calories, Carbs, Fat, Protein (respectively)")
        for day in range(7):
            print(week[day] + ": " + str(weekly_cal[day]), str(weekly_carb[day]), str(weekly_fat[day]),
                  str(weekly_protein[day]))
        # Graph progress for visualization
        graph()
    # Saves & quits application
    elif menu_choice == "5":
        print("Saving & quitting application...")
        # Save & close files
        cal_file.seek(0)
        carb_file.seek(0)
        fat_file.seek(0)
        protein_file.seek(0)
        for i in range(7):
            if i == 6:
                cal_file.write(str(weekly_cal[i]))
                carb_file.write(str(weekly_carb[i]))
                fat_file.write(str(weekly_fat[i]))
                protein_file.write(str(weekly_protein[i]))
            else:
                cal_file.write(str(weekly_cal[i]) + " ")
                carb_file.write(str(weekly_carb[i]) + " ")
                fat_file.write(str(weekly_fat[i]) + " ")
                protein_file.write(str(weekly_protein[i]) + " ")
        # Close all files & exit
        cal_file.close()
        carb_file.close()
        fat_file.close()
        protein_file.close()
        goals_file.close()
        exit(0)
    # Invalid input
    else:
        print("Invalid input...please try again")

