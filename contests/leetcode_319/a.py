class Solution:
    def convertTemperature(self, x: float) -> List[float]:
        return [x+273.15,x*1.8+32]
