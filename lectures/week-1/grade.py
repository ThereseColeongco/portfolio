score = int(input("Score: "))

# if score >= 90 and score <= 100:
# you can also say 90 <= score, etc.
# you can be more concise in python by chaining your AND conditions:
if score >= 90:
    print("Grade: A")
# elif 90 <= score < 90:
# but because you're using elif's, you don't even need the upper bound
# if you were using if's, anything > the lowest number in a range
# will be the grade (i.e. if you got 70, you would get A, B, and C)
# but since you're using elif's if it's not A and not B,
# it must be C for a grade of 70 ) (i.e. conditions are mutually exclusive)
# but if you use this generalization, you must also get rid of the
# upper bound on the initial if, otherwise, if you for some reason get
# a score > 100, you will get a B (b/c the upper bound of 100 on A
# still exists, whereas 101 is above 80, so you get a B)
elif score >= 80:
    print("Grade: B")
elif score >= 70:
    print("Grade: C")
elif score >= 60:
    print("Grade: D")
else:
    print("Grade: F")