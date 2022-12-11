from sortedcontainers import *
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        rows=[]
        bfs=[root]
        while bfs:
            row=bfs
            rows.append([x.val for x in bfs])
            nxt_row=[]
            for node in row:
                if node.left:nxt_row.append(node.left)
                if node.right:nxt_row.append(node.right)
            bfs=nxt_row
        ans=0
        for row in rows:
            sr=SortedList(row)
            sr=[sr.index(i) for i in row]
            vis=[0]*len(row)
            for i in range(len(row)):
                if vis[i]:continue
                vis[i]=1
                j=sr[i]
                while j!=i:
                    vis[j]=1
                    ans+=1
                    j=sr[j]
                    vis[j]=1
        return ans
