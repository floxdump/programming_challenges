"""
Solution for the `Pangrams` problem from the site Hacker Rank.
"""

def is_pangram(string):
    """
    Check whether string is pangram or not
    """
    a_pos = ord('a')
    letters = [0] * 26
    for char in string:
        if char.isalpha():
            letters[ord(char.lower()) - a_pos] += 1
    return all(letters)

if __name__ == '__main__':
    s = raw_input()
    if is_pangram(s):
        print 'pangram'
    else:
        print 'not pangram'
