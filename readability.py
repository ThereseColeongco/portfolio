from cs50 import get_string


def main():
    text = get_string("Text: ")

    # L = average number of letters / 100 words
    L = (count_letters(text) / count_words(text)) * 100

    # S = average number of sentences per 100 words
    S = (count_sentences(text) / count_words(text)) * 100

    # Coleman-Liau index
    index = (0.0588 * L) - (0.296 * S) - 15.8

    # reports grade level of text to nearest whole number
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade " + str(round(index)))


def count_letters(text):
    letter_count = 0
    for i in text:
        if i.isalpha() == True:
            letter_count += 1

    return letter_count


def count_words(text):
    word_count = 0
    for i in text:
        if i == " ":
            word_count += 1

    # add 1 extra to word counter b/c at the end of the text, there's 1 more word but no space to indicate a word.
    word_count += 1

    return word_count


def count_sentences(text):
    sentence_count = 0
    for i in text:
        if i in [".", "?", "!"]:
            sentence_count += 1
    return sentence_count


main()
