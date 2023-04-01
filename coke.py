due = 50

while due > 0:
    print(f"Amount Due: {due}")
    coin = int(input("Insert Coin: "))
    if coin in [25, 5, 10]:
        due = due - coin

if due <= 0:
    change = abs(due)
    print(f"Change Owed: {change}")