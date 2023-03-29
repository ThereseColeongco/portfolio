def main():
    meal = input("What time is it? ")

    if 7.0 <= convert(meal) <= 8.0:
        print("breakfast time")
    elif 12.0 <= convert(meal) <= 13.0:
        print("lunch time")
    elif 18.0 <= convert(meal) <= 19.0:
        print("dinner time")
    else:
        print("")

def convert(time):
    hours, mins = time.split(":")
    hours = float(hours)
    mins = float(mins)
    return hours + mins / 60

if __name__ == "__main__":
    main()