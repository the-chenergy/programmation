class Solution:
    def haveConflict(self, event1: List[str], event2: List[str]) -> bool:
        e1=[x.split(':') for x in event1]
        e2=[x.split(':') for x in event2]
        t1=[int(x[0])*60+int(x[1]) for x in e1]
        t2=[int(x[0])*60+int(x[1]) for x in e2]
        t1,t2=sorted((t1,t2))
        return t2[0]<=t1[1]
