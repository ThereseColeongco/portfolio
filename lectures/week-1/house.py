name = input("What's your name? ")

'''
if name == "Harry" or name == "Hermione" or name == "Ron":
    print("Gryffindor")
elif name == "Draco":
    print("Slytherin")
else:
    print("Who?")
'''

# does exact same thing as ^^ but more visually compact and
# can do more things w/ match than you can do w/ if/elif/else (not shown)
match name:
    case "Harry" | "Hermione" | "Ron":
        print("Gryffindor")
    case "Draco":
        print("Slytherin")
    case _:
        print("Who?")