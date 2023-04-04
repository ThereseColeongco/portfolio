class

months = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
]

while True:
    try:
        mm, dd, yyyy = input("Date: ").split(" ").split(",").split("/")
        if mm not in months:
            mm = int(mm)
        dd = int(dd)
        yyyy = int(yyyy)
    except:
        #accepted formats:
            #January 1, 1970
            #1/1/1970
        #not accepted:
            #8 September 1636
            #yyyy mm dd
            #yyyy month dd
            #yyyy dd mm
            #yyyy dd month