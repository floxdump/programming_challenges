"""
Solution for the `Utopian Tree` problem from the site Hacker Rank.

The complexity of getting the height of the Utopian Tree is O(1).
"""

def utopian_height(n):
    """
    Return the height of the Utopian Tree after n cycles
    """
    height = 0
    if n % 2 == 0:
        height = 2 ** (n / 2 + 1) - 1
    else:
        height = 4 * 2 ** (n / 2) - 2
    return height

if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n = int(input())
        print(utopian_height(n))
