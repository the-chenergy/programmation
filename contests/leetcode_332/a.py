class Solution:
    def findTheArrayConcVal(self, nums: List[int]) -> int:
        ans=0
        nums=deque(nums)
        while len(nums)>1:
            ans+=int(str(nums[0])+str(nums[-1]))
            nums.popleft()
            nums.pop()
        if len(nums):
            ans+=nums[0]
        return ans
