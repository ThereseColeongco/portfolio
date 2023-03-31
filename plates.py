def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")
    print(plate[0:2].isalpha(), plate.isalnum(), 2 <= len(plate) < 6, plate[1:len(plate)].isalpha())

def middle_not_num(s):
    for character in s:
        
            if s[i]

def is_valid(s):
    if s[0:2].isalpha() and s.isalnum() and 2 <= len(s) < 6 and
        return True
    else:
        return False


main()