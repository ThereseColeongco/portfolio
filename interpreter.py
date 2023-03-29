expression = input("Expression (e.g. 1 + 1): ")
x, y, z = expression.split(" ")
x = int(x)
z = int(z)

if y == "+":
    print(float(x + z))
elif y == "-":
    print(float(x - z))
elif y == "/":
    print(float(x / z))
elif y == "*":
    print(float(x * z))
else:
    print("Please input an expression with a space between number and operator (e.g. x + z)")