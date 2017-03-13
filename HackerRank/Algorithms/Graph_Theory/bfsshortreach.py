"""
Solution for the `Breadth First Search: Shortest Reach` problem from the site Hacker Rank.
"""

from collections import defaultdict, deque

EDGE_LENGTH = 6

def bsf(edges, start_node):
    """Return the dictionary of distances from start_node to all other nodes"""
    queue = deque()
    queue.append((start_node, 0))
    distances = {start_node: 0}
    while queue:
        current_node, distance = queue.popleft()
        adj_nodes = edges.get(current_node, [])
        for node in adj_nodes:
            if node not in distances:
                distances[node] = distance + EDGE_LENGTH
                queue.append((node, distance + EDGE_LENGTH))
    return distances

def get_distances(n, distances, start_node):
    """
    Return the whole string of all distances
    from start_node to (n - 1) other nodes
    """
    distances_str = []
    for node in xrange(1, n + 1):
        if node != start_node:
            if node in distances:
                distances_str.append(str(distances[node]))
            else:
                distances_str.append('-1')
    return ' '.join(distances_str)

def read_graph_data():
    """
    Read graph data from stdin
    """
    n, m = raw_input().split()
    n, m = int(n), int(m)
    edges = defaultdict(set)
    for _ in xrange(m):
        n_s, n_e = raw_input().split()
        n_s, n_e = int(n_s), int(n_e)
        edges[n_s].add(n_e)
        edges[n_e].add(n_s)
    start_node = int(raw_input())
    return n, edges, start_node

def main():
    """Main function"""
    q = int(raw_input())
    for _ in xrange(q):
        n, edges, start_node = read_graph_data()
        distances = bsf(edges, start_node)
        print get_distances(n, distances, start_node)

if __name__ == '__main__':
    main()
