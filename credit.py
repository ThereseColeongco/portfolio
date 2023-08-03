from cs50 import get_string

def main():
    number = get_string("Card number: ")

    first_two = number[:2]

    if checksum(number) == True:
        if first_two in ['34', '37'] and len(number) == 15:
            print("AMEX")
        elif first_two in ['51', '52', '53', '54', '55'] and len(number) == 16:
            print("MASTERCARD")
        elif len(number) in [13, 16] and number[:1] == '4':
            print("VISA")
    else:
        print("INVALID")


def checksum(card):
    card = int(card)
    all_dig = []
    mult = []
    not_mult = []
    # get every other digit, starting w/ the second-last digit

    # multiply each of those digits by 2
    # store the result in list mult
    # all other digits should be stored in list not_mult
    # get digits of each number in list mult
    # sum of digits in list mult + sum of digits in list not_mult = total
    # total % 10 == 0 → return True

    # puts all digits in card into a list, all_dig[0] = always last digit in card, so all_dig[1] = always second-last number in card
    while card > 0:
        x = card % 10
        all_dig.append(x)
        card = int(card / 10)

    # since all_dig[1] = always second-last digit in card, every other number to be multiplied by 2 has an odd index
    # and all the numbers that were not multiplied by 2 would have an even index
    for i in range(len(all_dig)):
        if i % 2 == 0:
            not_mult.append(all_dig[i])
        else:
            mult.append(all_dig[i])

    # iterates through mult and multiplies every element in it by 2
    # stores the result at the index of the original element
    for j in range(len(mult)):
        mult[j] *= 2

    mult_sum = 0
    for k in mult:
        mult_dig = [int(d) for d in str(k)]
        mult_sum += sum(mult_dig)

    not_mult_sum = 0
    for l in not_mult:
        not_mult_dig = [int(d) for d in str(l)]
        not_mult_sum += sum(not_mult_dig)

    # add the digits in list mult
    # add the digits in not_mult
    # add the sums together
    total = not_mult_sum + mult_sum

    # if last digit in total = 0, return True
    if total % 10 == 0:
        return True
    '''
    for i in reversed(range(len(card))):


        if i % 2 == 0:
            s += str(int(card[i]) * 2)
        else:
            u.append(int(card[i]))
    x = sum([int(d) for d in s])

    for j in reversed(range(len(card))):
        if j % 2 != 0:
            x += int(card[j])
    '''



main()

'''
378282246310005


'''