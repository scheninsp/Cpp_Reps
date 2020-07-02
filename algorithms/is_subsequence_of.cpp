//leetcode 
//judge s is subsequence of t
class Solution {
    public boolean is_subsequence_of(String s, String t) {
        if (s == null || t == null) {
			return true;
		}
		
        int sLen = s.length();
        int index = 0
		int p = 0;
		
        for (int i = 0; i < sLen; i++) {
            p = t.indexOf(s.charAt(i), index);
            if (p < 0) {
				return false;
			}
            index = p + 1;
        }
        return true;
    }
}
