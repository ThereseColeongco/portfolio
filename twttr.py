text = input("Input: ")
vowels = 'AEIOUaeiou'
'''
for i in range(len(vowels)):
     text = text.replace(vowels[i], '')

print(text)
'''
for vowel in vowels:
    text = text.replace(vowel, '')

print(text)