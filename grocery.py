grocery = {}
counter = 0
#counter for item variable = 0. user inputs item. counter = counter + 1 and store item in grocery if there are no other of the same item in grocery. otherwise, just counter = counter + 1

while True:
    try:
        item = input().upper()
        #check characters of item. if not in grocery, counter = counter + 1 and grocery.update({item:counter}). if in grocery, counter = key's value + 1 and grocery.update({item:counter}).
        if item not in grocery:
            counter = counter + 1
            grocery.update({item:counter})
            counter = 0
        else:
            counter = grocery.get(item) + 1
            grocery.update({item:counter})
            counter = 0
        keys = list(grocery.keys())
        keys.sort()
        sorted_grocery = {i: grocery[i] for i in keys}
    except EOFError:
        if 'sorted_grocery' in locals():
            for groceries in sorted_grocery:
                print(sorted_grocery[groceries], groceries) #print each key's value in grocery + space + each value's key in grocery
            break
        else:
            break
    except KeyError:
        pass