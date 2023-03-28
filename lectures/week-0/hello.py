def main(): #denotes that this is main part of program
    # python is not just a language, it's also an interpreter - a program that converts code to 0's and 1's
    # ask user for their name
    name = input("What's your name? ")

    # say hello to user
    print("hello, " + name) # 1 argument, concatenation, gonna do what's in quotes 1st, then what comes after
    print("hello,", name) # pass multiple arguments to print, adds a space b/t them automatically

    # print(*objects, sep=' ', end='\n', file=sys.stdout, flush=False)
    # function = called print
    # inside parentheses = potential arguments, technically parameters
    # parameters = the inputs you CAN potentially pass into a function
    # when you use function and pass in values into parentheses, they're called arguments
    # *objects - can take any number of objects; 0, 1, infinitely many strings
    # sep=' ' - separator is space by default, i.e. input multiple arguments → each argument = separated by a space
    # end='\n' - moves cursor to new line at end of every line, i.e. after all arguments = printed, cursor moves to new line
    print("hello, ", end="") # overrides default value for end
    print(name)

    print("hello,", name, sep="") # overrides default space between arguments
    # positional parameters = first thing u pass in gets printed, then 2nd thing u pass in gets printed
    # named parameters = like sep, end; optional, passed in at end of print statement, but can also use them by name

    # corner case - when u wanna use quotes in ur string
    print('hello, "friend"')
    print("hello, 'friend'")
    print("hello, \"friend\"")
    # \n = not literally printing n but a new line
    # backslash = escape character
    # escape character = a character that invokes an alternative interpretation on the following characters in a character sequence

    # remove whitespace from str
    name = name.strip()

    # capitalize user's name
    name = name.capitalize() #but only the 1st letter, so if they give their full name, it will only capitalize the very first

    name = name.title() # capitalizes 1st letter of each word like a title

    # can put all the methods together to be more concise
    name = name.strip().title()
    # you can also put them in the input()
    # name = input("What's your name? ").strip().title()

    # split user's name into first name and last name according to where there's a space
    # e.g. (input = "First Last" → first = "First" and last = "Last")
    first, last = name.split(" ")

    print(f"hello, {first}") # f-string tells python to format things in a special way, i.e. use the variable's content within the quotes
    # strings (str) = a data type
    # built into strings in python = ability to do things to strings (string methods - functions that come w/ strings)

    # interactive mode allows u to type python in terminal and immediately get a result
    # script mode = the CLI; type exit() to get back to this mode when done w/ interactive mode



    hello(name)
    hello()


# function definition for "out of sight, out of mind" - more aesthetic
def hello(to="world"): #world = default value if no argument
    print("hello,", to)

main() # must call main() function w/c runs def main() w/c runs def hello()

# scope = variable only existing in context in w/c u define it
# global vs local variables
# can't use a variable defined in 1 function definition in another function definition
# so u can't say:
# def main():
#   name = input("What's your name? ")
#   hello()

# def hello():
#   print("hello,", name)

# main()

# b/c name doesn't exist in the scope of def hello()