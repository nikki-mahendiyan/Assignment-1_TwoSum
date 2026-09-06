#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>

std::pair<int,int> twoSumBruteForce(const std::vector<int>& nums, int target) 
{
    int n = nums.size();
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (nums[i] + nums[j] == target) 
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Hash-based
std::pair<int,int> twoSumHash(const std::vector<int>& nums, int target) 
{
    std::unordered_map<int,int> seen; // value -> index
    int n = nums.size();
    for (int i = 0; i < n; i++) 
    {
        int complement = target - nums[i];
        auto it = seen.find(complement);
        if (it != seen.end()) 
        {
            return {it->second, i};
        }
        seen[nums[i]] = i;
    }
    return {-1, -1};
}


bool isValidResult(const std::vector<int>& nums, int target, std::pair<int,int> result) 
{
    int i = result.first, j = result.second;
    int n = nums.size();
    if (i < 0 || j < 0) return false;
    if (i >= n || j >= n) return false;
    if (i == j) return false;
    return nums[i] + nums[j] == target;
}

void printOutcome(const std::string& label, const std::vector<int>& nums,
                   int target, std::pair<int,int> result) 
                   {
    bool yes = isValidResult(nums, target, result);
    std::cout << label << " -> indices (" << result.first << ", " << result.second << ")";
    if (yes)
    {
        std::cout << ", values (" << nums[result.first] << ", " << nums[result.second] << ")";
    }
    std::cout << ", valid: " << (ok ? "yes" : "no") << "\n";
}

void runTest(const std::string& name, const std::vector<int>& nums, int target)
 {
    std::cout << name << " (target = " << target << ")\n";
    printOutcome("  Brute force", nums, target, twoSumBruteForce(nums, target));
    printOutcome("  Hash lookup", nums, target, twoSumHash(nums, target));
    std::cout << "\n";
}

int main() 
{
    runTest("Required test", {15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9}, 24);
    runTest("Basic example", {2, 7, 11, 15}, 9);
    runTest("Duplicate values", {3, 3}, 6);
    runTest("Negative values", {-3, 4, 3, 90}, 0);
    runTest("No valid pair", {1, 2, 3, 4, 5}, 100);
    return 0;
}
