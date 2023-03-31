text = input("Input: ")
vowels = 'AEIOUaeiou'
'''
for i in range(len(vowels)):
     text.replace(vowels[i], '')

print(text)
'''
for vowel in vowels:
    print(text.replace(vowel, ''))

print(text)