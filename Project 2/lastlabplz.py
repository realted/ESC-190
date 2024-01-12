# pseudo

'''
Dijkstra(G = (V, E), source)
    s = P{ # S is the set of explored nodes}
    pq = (0, source)
    while pg is not empty
        if cur_node in S
            continue
        cur_dist, cur_node = pq.pop()
        d(cur_node) = cur_dist
        add cur_node = cur_dist
        for each neigbour v od cur node
            pq.push(cur_dist + |(cur_node, v|), v)




'''