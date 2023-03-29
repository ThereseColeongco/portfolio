greeting = input("Send a greeting: ").lower().strip().split(" ", 1)[0]

if greeting == "hello" or greeting == "hello,":
    print("$0")
elif greeting[0] == "h":
    print("$20")
else:
    print("$100")