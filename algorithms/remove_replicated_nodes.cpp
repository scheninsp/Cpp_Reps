//leetcode 

class Solution {
public:
    ListNode* removeReplicatedNodes(ListNode* head) {
        if (head == NULL)
            return NULL;
		
        unordered_set<int> set;
		
        ListNode* tmp = head;
        ListNode* ans = tmp;
		
        set.insert(head->val);
		
        while (head != NULL) {
            if (set.count(head->val) == 0) {
                set.insert(head->val);
                tmp->next = new ListNode(head->val);
                tmp = tmp->next;
            }
            head = head->next;
        }
        return ans;
    }
};
