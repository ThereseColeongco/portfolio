def main():
    user = input("Tell me something. ")
    convert(user)

def convert(str):
    str = str.replace(":)", "🙂")
    str = str.replace(":(", "🙁")
    print(str)

main()