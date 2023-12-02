from __future__ import annotations


def edges_to_dot(edges: list[tuple[int, int] | tuple[int, int, int] |
                             list[int]],
                 node_values: list[int] | None = None) -> str:
    '`edges_to_dot` converts a graph stored as a list of `edges` into the Dot notation.'
    res = 'graph G {'
    if node_values is not None:
        for i, value in enumerate(node_values):
            res += f'\n\t{i} ["label"="{i} ({value})"]'
    for e in edges:
        if len(e) == 2:
            u, v = e
            w = None
        else:
            u, v, w = e
        res += f'\n\t{u} -- {v}'
        if w is not None:
            res += f' [label="({w})"]'
    res += '\n}'
    return res
