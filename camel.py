camel = input("camelCase: ")

for character in camel:
    if character.isupper():
        print("_", character.lower(), end="", sep="")
    else:
        print(character, end="")

print()