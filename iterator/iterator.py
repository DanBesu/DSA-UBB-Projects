class EdgesIterator:

    def __init__(self, edges):
        self._edges = edges
        self._index = -1

    def __iter__(self):
        return self

    def __next__(self):
        self._index += 1
        if self._index == len(self._edges):
            raise StopIteration

        return self._edges[self._index]
