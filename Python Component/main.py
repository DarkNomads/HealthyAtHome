# Main Program

# Graphing Library
import matplotlib


# TODO
def display_menu():
    print("*-----Calorie Tracker-----*")
    print("1. Calorie intake entry")
    print("2. Calorie burned entry")
    print("3. Calculate net calorie gain/loss")
    print("4. Quit program")


def net_calorie(cal_in, cal_burn):
    net_cal = cal_in - cal_burn
    return net_cal


# TODO
def graph():
    pass


# ------------------------------------------------

# Demo

# Total calorie data
total_cal_in = 0
total_cal_burn = 0

while True:
    display_menu()
    menu_choice = input("\nSelection: ")

    if menu_choice == "1":
        total_cal_in = int(input("Enter total calorie intake: "))
    elif menu_choice == "2":
        total_cal_burn = int(input("Enter total calorie burned: "))
    elif menu_choice == "3":
        net_cal = net_calorie(total_cal_in, total_cal_burn)
        if net_cal < 0:
            print("Net calorie loss:", abs(net_cal))
        else:
            print("Net calorie gained:", net_cal)
    elif menu_choice == "4":
        exit(0)
    else:
        print("Invalid input...please try again\n")



