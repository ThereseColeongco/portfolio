import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py databases/name_of.csv sequences/sequence.txt')

    people = []
    # TODO: Read database file into a variable
    database = open(f'{sys.argv[1]}', 'r')
    # each row in csv is a dict
    data_dict = csv.DictReader(database)
    # puts each dict in people list
    for dict in data_dict:
        people.append(dict)

    # TODO: Read DNA sequence file into a variable
    sequence = open(f'{sys.argv[2]}', 'r')
    s = sequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    # for each position in sequence, compute how many times STR repeats starting at that position
    # for each position, keep checking successive substrings until STR doesn't repeat anymore
    # return max number of the particular STR found in the sequence file
    # do this for each STR
    # once done, save STR counts in a data structure (list or dict)
    # check if each STR count matches a row in csv
    longest_match_results = {}
    str_list = data_dict.fieldnames  # put data_dict keys into a list
    str_list.remove("name")
    for i in range(len(str_list)):  # iterate through the list of keys starting w/ index = 1
        longest_match_results[str_list[i]] = longest_match(s[0:], str_list[i])

        # save longest_match results from the sequence in a list or dict
            # perhaps a dict where key = a particular STR and value = counts associated w/ that STR?
        # go through each row in csv and check if longest_match result for each STR matches w/ what's in that row of the csv.

    # compare STR counts against each row in csv


    # TODO: Check database for matching profiles
    matches = []
    for i in range(len(people)):  # iterate through people list
        for j in range(len(str_list)):  # iterate through str_list
            # print(str_list[j])
            # print(people[i][f"{str_list[j]}"] + 1)
            # print(int(longest_match_results[f"{str_list[j]}"]))
            # it's possible that the wrong person will print if the last match result is True
            if int(longest_match_results[f"{str_list[j]}"]) == int(people[i][f"{str_list[j]}"]):  # if counts from longest_match equals the counts for a person in people
                matches.append(True)
            else:
                matches.append(False)
        if all(i == True for i in matches):
            print(people[i]["name"])
            break
        elif i < len(people) - 1:
            matches.clear()
            continue
    if any(i == False for i in matches):
        print("No match")
            # if match is False and it hasn't gone through the whole list, it should continue...

    # there's probably a more concise way to put this ^^, isn't there?
    # the sequences that should turn up No matches don't work (either wrong name or nothing printed)
        # python dna.py databases/large.csv sequences/16.txt returns Albus when it should be No match
        # python dna.py databases/large.csv sequences/20.txt is a No match that prints nothing
    # python dna.py databases/large.csv sequences/7.txt returns Petunia when it should be Ron

    # if you've gone through all the people and there's no match, print("No match")


    database.close()
    sequence.close()


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
