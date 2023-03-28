everything = input("What is the Answer to the Great Question of Life, the Universe, and Everything? ")
str(everything).strip().lower()

match everything:
    case "42" | "forty-two" | "forty two":
        print("Yes")
    case _:
        print("No")