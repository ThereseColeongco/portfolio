x = int(input("What is x? "))
y = int(input("What is y? "))

# having all if's means
# whether or not the previous condition was true or false,
# it will check all other if statements

# having elif's means only if previous condition was false
# will it check subsequent conditions

# once you rule out all other possible conditions,
# the only logical case left would be the last one (so you can say 'else')
if x < y:
    print("x is less than y")
#if x > y:
elif x > y:
    print("x is greater than y")
#if x == y:
#elif x == y:
else:
    print("x is equal to y")

# if x < y or x > y:
if x != y: # more concise; an equivalent statement -> if x == y
    print("x is not equal to y")
else:
    print("x is equal to y")