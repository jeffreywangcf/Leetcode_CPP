import java.nio.channels.InterruptedByTimeoutException;
import java.util.*;
import structure.*;

public class Solution {
    public static int[] runningSum(int[] nums){
        int[] ret = new int[nums.length];
        int sum = 0;
        for(int i = 0; i < nums.length; i++){
            sum += nums[i];
            ret[i] = sum;
        }
        return ret;
    }

    public static String removeVowels(String S){
        char[] ret = new char[S.length()];
        int i = 0;
        for(char c: S.toCharArray()){
            if (c != 'a' && c != 'e' && c != 'i' && c !='o' && c != 'u'){
                ret[i++] = c;
            }
        }
        return new String(ret, 0, i);
    }

    public static List<Boolean> kidsWithCandies(int[] candies, int extraCandies){
        List<Boolean> ret = new ArrayList<>();

        int max = 0;
        for(int candy: candies)
            if(candy>max)
                max = candy;

        for(int candy: candies)
            ret.add(candy + extraCandies >= max);

        return ret;
    }

    public static int[] shuffle(int[] nums, int n) {
        if(nums.length == 0)
            return new int[0];
        int[] ret = new int[n*2];
        int r = 0;
        for(int i = 0; i < n; i++){
            ret[r++] = nums[i];
            ret[r++] = nums[n + i];
        }
        return ret;
    }

    public static int numIdenticalPairs(int[] nums) {
        int count = 0;
        int[] map = new int[101];
        for(int num: nums)
            map[num]++;
        for(int val: map)
            count += (1 + val-1) * (val-1) / 2;
        return count;
    }

    public static String defangIPaddr(String address) {
        return address.replace(".", "[.]");
    }

    public static int numberOfSteps (int num) {
        int step = 0;
        while(num > 0){
            if(num % 2 == 0)
                num /= 2;
            else
                num -= 1;
            step++;
        }
        return step;
    }

    public static int[] smallerNumbersThanCurrent(int[] nums) {
        int[] ret = new int[nums.length];
        int[] sorted = nums.clone();
        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
        Arrays.sort(sorted);
        for(int i = 0; i < sorted.length; i++){
            if(i == 0) {
                map.put(sorted[0], 0);
                continue;
            }
            if(sorted[i] == sorted[i-1])
                continue;
            map.put(sorted[i], i);
        }

        for(int i = 0; i < nums.length; i++)
            ret[i] = map.get(nums[i]);

        return ret;
    }

    public static String restoreString(String s, int[] indices) {
        char[] ret = new char[s.length()];
        for(int i = 0; i < s.length(); i++)
            ret[indices[i]] = s.charAt(i);
            return  new String(ret);
    }

    public int subtractProductAndSum(int n) {
        int sum = 0;
        int product = 1;
        while(n>0){
            int digit = n % 10;
            sum += digit;
            product *= digit;
            n /= 10;
        }

        return product - sum;
    }

    public static int[] decompressRLElist(int[] nums) {
        int size = 0;
        int index = 0;

        for(int i = 0; i < nums.length - 1; i+=2)
            size += nums[i];
        int[] ret = new int[size];

        for(int i = 0; i < nums.length - 1; i+=2){
            int frequency = nums[i];
            while(frequency-- > 0)
                ret[index++] = nums[i];
        }

        return ret;
    }

    public int calculateTime(String keyboard, String word) {
        int[] map = new int[26];
        char[] keys = keyboard.toCharArray();
        for(int i = 0; i < keys.length; i++){
            char currentKey = keys[i];
            map[currentKey - 'a'] = i;
        }

        int time = 0;
        int finger = 0;
        for(char w: word.toCharArray()){
            int current = map[w - 'a'];
            time += Math.abs(current - finger);
            finger = current;
        }

        return time;
    }

    public static int xorOperation(int n, int start) {
        int result = 0;
        for(int i = 0; i < n; i++)
            result ^= start + 2 * i;
        return result;
    }

    public int[] createTargetArray(int[] nums, int[] index) {
        List result = new ArrayList<Integer>();
        for(int i = 0; i < nums.length; i++){
            result.add(index[i], nums[i]);
        }

        int[] ret = new int[result.size()];
        for(int i = 0; i < result.size(); i++)
            ret[i] = (int) result.get(i);

        return ret;
    }

    public static int balancedStringSplit(String s) {
        int index = 0;
        int count = 0;
        int leftCount = 0;
        int rightCount = 0;
        while(index < s.length()){
            if(s.charAt(index) == 'R')
                rightCount++;
            else
                leftCount++;
            if(rightCount == leftCount && rightCount != 0) {
                count++;
                leftCount = 0;
                rightCount = 0;
            }
            index++;
        }
        return count;
    }

    public List<Integer> getLonelyNodes(TreeNode root) {
        List ret = new ArrayList<Integer>();
        if(root != null){
            findLonelyNodes(root.left, root, ret);
            findLonelyNodes(root.right, root, ret);
        }
        return ret;
    }

    private void findLonelyNodes(TreeNode node, TreeNode parent, List targetList){
        if(node == null)
            return;
        if(parent.left == null || parent.right == null){
            targetList.add(node.val);
        }
        findLonelyNodes(node.left, node, targetList);
        findLonelyNodes(node.right, node, targetList);
    }

    public int rangeSumBST(TreeNode root, int L, int R) {
        return findRangeSumBST(root, L, R, 0);
    }

    private int findRangeSumBST(TreeNode root, int L, int R, int sum) {
        sum += (root.val >= L && root.val <= R) ? root.val : 0;

        if(root.left != null)
            sum = findRangeSumBST(root.left, L, R, sum);
        if(root.right != null)
            sum = findRangeSumBST(root.right, L, R, sum);

        return sum;
    }

    public int findNumbers(int[] nums) {
        int count = 0;
        for(int num: nums){
            int digit = 0;
            while(num > 0){
                digit++;
                num /= 10;
            }
            if(digit % 2 == 0)
                count++;
        }
        return count;
    }

    public int getDecimalValue(ListNode head) {
        List digits = new ArrayList<Integer>();
        while(head.next != null){
            digits.add(head.val);
            head = head.next;
        }

        return 0;


    }

    public int getDecimalValue1290(ListNode head) {
        int ret = 0;
        while(head != null){
            ret = ret * 2 + head.val;
            head = head.next;
        }
        return ret;
    }



    public static String bestPlayer(String data) {
        if (data == null || data.equals("")) {
            return null;
        }
        java.util.HashMap table = new java.util.HashMap<String, Integer>();
        String[] lines = data.split("\n");
        for (String line: lines) {
            String[] items = line.split(",");
            String name = items[0].trim();
            Integer score = Integer.parseInt(items[1].strip()) * 7;
            score += Integer.parseInt(items[2].strip()) * 3;
            if (table.get(name) == null) {
                table.put(name, score);
            } else {
                table.put(name, (Integer) table.get(name) + score);
            }
        }

        java.util.Iterator iter = table.entrySet().iterator();
        String bestName = "";
        Integer bestScore = -1;
        while (iter.hasNext()) {
            java.util.Map.Entry pair = (java.util.Map.Entry) iter.next();
            if ((Integer) pair.getValue() > bestScore) {
                bestName = (String) pair.getKey();
                bestScore = (Integer) pair.getValue();
            }
        }
        return bestName;
    }
}
