items = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

total = [] #STOP PUTTING INITIALIZATIONS INSIDE THE LOOP OR IT WILL KEEP RE-INITIALIZING EVERY RUN OF THE LOOP

while True:
    try:
        order = input("Item: ").title() # alternative to lowering
        total.append(items[order])
        print(f"Total: ${sum(total):.2f}")
        # user inputs a key. get key's value. append value to list. sum the list. repeat until user presses ctrl-d.
        # for each key the user inputs, get its value and append it to a list. sum the list.
    except KeyError:
        pass
    except EOFError:
        print()
        break
