# Calorie & Macro Tracker

# Libraries
import datetime
import calendar
import matplotlib

# Functions


def display_menu():
    print("\n*-----Calorie Tracker-----*")
    print("1. Set calorie goal (daily)")
    print("2. Calculate today's net calorie")
    print("3. Display this week's progress")
    print("4. Quit program")


def calc_net_cal(weekly_cal, curr_day, cal_goal):
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


# TODO
def graph():
    pass

# --------------------------------------------------------------

# Main Program


# Get day of the week; 0 = Monday ... 6 = Sunday
curr_day = datetime.date.today().weekday()

# Weekly calories
weekly_cal = [0, 0, 0, 0, 0, 0, 0]
week = list(calendar.day_name)

# User calorie goal (daily)
cal_goal = 0

while True:
    display_menu()
    menu_choice = input("\nSelection: ")

    if menu_choice == "1":
        cal_goal = int(input("Enter your daily calorie goal: "))
    elif menu_choice == "2":
        calc_net_cal(weekly_cal, curr_day, cal_goal)
    elif menu_choice == "3":
        print("\n*-----Weekly Progress-----*")
        for day in range(7):
            print(week[day] + ": " + str(weekly_cal[day]))
    elif menu_choice == "4":
        exit(0)
    else:
        print("Invalid input...please try again")

