def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")
    print(plate[0:2].isalpha(), plate.isalnum(), 2 <= len(plate) < 6, plate[1:len(plate)].isalpha(), middle_not_num(plate), not_nil(plate))

def middle_not_num(s):
    index_list = []
    num = "0123456789"
    #iterates through num to see if any numbers are in s; if a number is found, its index is added to index_list
    for number in num:
        if number in s:
             index_list.append(s.index(number))
    #gets indexes from smallest index at which a number is found to length of s
    if index_list:
        for i in range(min(index_list), len(s)):
            print("num", s[i], i)
            if s[i].isalpha(): # checks if character at each index is a letter
                return False # if the character at 1 of the indexes is a letter, return False
            else:
                continue
    return True

def not_nil(s):
    index_list = []
    num = "0123456789"
    for number in num:
        if number in s:
             index_list.append(s.index(number)) # will print all indexes of every number in plate

    if index_list and str(s[min(index_list)]) == "0":
        return False
    else:
        return True

        # check if there is a number in s. if there is, check if there is at least 1 letter after it

# check (in this or another function) if the first number

def is_valid(s):
    if s[0:2].isalpha() and s.isalnum() and 2 <= len(s) < 6 and middle_not_num(s) and not_nil(s):
        return True
    else:
        return False

main()