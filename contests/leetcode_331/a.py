class Solution:
    def pickGifts(self, gifts: List[int], k: int) -> int:
        for i in range(len(gifts)):
            gifts[i]=~gifts[i]
        heapify(gifts)
        for i in range(k):
            x=~heappop(gifts)
            x=int(sqrt(x))
            heappush(gifts,~x)
        return sum(~x for x in gifts)
