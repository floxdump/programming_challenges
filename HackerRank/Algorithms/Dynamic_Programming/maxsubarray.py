"""
Solution for the `The Maximum Subarray` problem from the site Hacker Rank.

The complexity of getting the maximum possible sum of a contiguous
subarray of array is O(n), where n is the size of array.
The complexity of getting the maximum possible sum of a
a non-contiguous subarray of array is the same.
"""

def max_contiguous_subarray(array):
    """
    Return the maximum possible sum of a contiguous subarray of array.
    """
    if len(array) > 0:
        global_max = array[0]
        current_max = array[0]
        for item in array[1:]:
            current_max = max(current_max + item, item)
            global_max = max(global_max, current_max)
        return global_max
    else:
        return 0

def max_noncontiguous_subarray(array):
    """
    Return the maximum possible sum of a non-contiguous subarray of array.
    """
    if len(array) > 0:
        all_negative = True
        max_negative = None
        sum_items = 0
        for item in array:
            if item >= 0:
                all_negative = False
                sum_items += item
            else:
                if max_negative is None or item > max_negative:
                    max_negative = item
        if all_negative:
            return max_negative
        else:
            return sum_items
    else:
        return 0

if __name__ == '__main__':
    array_count = int(raw_input())
    for _ in xrange(array_count):
        _ = int(raw_input())
        array = map(int, raw_input().split())
        print('%d %d' % (max_contiguous_subarray(array),
                         max_noncontiguous_subarray(array)))
