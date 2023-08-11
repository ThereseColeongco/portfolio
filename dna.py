import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py databases/name_of.csv sequences/sequence.txt")

    people = []
    # TODO: Read database file into a variable
    database = open(f"{sys.argv[1]}", "r")
    # each row in csv is a dict
    data_dict = csv.DictReader(database)
    # puts each dict in people list
    for dict in data_dict:
        people.append(dict)

    # TODO: Read DNA sequence file into a variable
    sequence = open(f"{sys.argv[2]}", "r")
    s = sequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    longest_match_results = {}
    str_list = data_dict.fieldnames  # put data_dict keys into a list
    str_list.remove("name")

    # iterate through the list of keys starting w/ index = 1
    # associate longest_match results w/ the right STR and put the pair into a results dictionary.
    for i in range(len(str_list)):
        longest_match_results[str_list[i]] = longest_match(s[0:], str_list[i])

    # TODO: Check database for matching profiles
    matches = []
    for i in range(len(people)):
        for j in range(len(str_list)):
            # if counts from longest_match equals the counts for a person in people
            if int(longest_match_results[f"{str_list[j]}"]) == int(
                people[i][f"{str_list[j]}"]
            ):
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
