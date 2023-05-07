unordered_map<int, int> c, f;

class FrequencyTracker {
public:
    FrequencyTracker() {
        c = {};
        f = {};
    }
    
    void add(int number) {
        auto& c1 = c[number];
        if (c1) f[c1]--;
        f[++c1]++;
    }
    
    void deleteOne(int number) {
        auto& c1 = c[number];
        if (!c1) return;
        f[c1]--;
        if (--c1) f[c1]++;
    }
    
    bool hasFrequency(int frequency) {
        auto it = f.find(frequency);
        return it != f.end() && it->second > 0;
    }
};

/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */
