/* Question 2 (30 pts) Consider the coin changing problem in which we have n denomi nations d[1 . . . n] and a target T. 
 * The goal is to make change for T using as few coins as possible. Assume all values are positive integers. 
 * – (10 points) Provide an example in which repeatedly choosing the largest denomination less than or equal to the remaining amount 
 * does not yield an optimal solution. – (20 points) Suppose that the denominations are 5 and 10. Show that repeatedly choosing the 
 * largest denomination less than or equal to the remaining amount does yield an optimal solution. (Hint: use a proof by contradiction.) 
 */

/* Consider the following set of coin denominations: {1, 3, 4} and the target value T = 6. We want to find the optimal way to make change for T.

    Using the greedy approach of repeatedly choosing the largest denomination less than or equal to the remaining amount, we would proceed as follows:

        Start with T = 6.
        Choose the largest denomination less than or equal to 6, which is 4 (6 - 4 = 2).
        Choose the largest denomination less than or equal to 2, which is 1 (2 - 1 = 1).
        Choose the largest denomination less than or equal to 1, which is 1 (1 - 1 = 0).

    The greedy approach yields a total of 3 coins: {4, 1, 1}.

    However, the optimal solution for making change for 6 using denominations {1, 3, 4} is {3, 3}, which uses only 2 coins. So, in this case, the greedy approach doesn't yield an optimal solution.
*/

/* Now, let's consider the denominations {5, 10} and a target value T. We want to prove that the greedy approach of repeatedly choosing the largest denomination less than or equal to the remaining amount yields an optimal solution.

    Proof by Contradiction:

    Assume that there exists a target value T for which the greedy approach doesn't yield an optimal solution. That is, there exists an alternative solution that uses fewer coins than the greedy approach.

    Let's denote the number of coins required by the greedy approach as N_greedy.

    If there exists an alternative solution with fewer coins, let's call the number of coins required by this alternative solution as N_alternative, where N_alternative < N_greedy.

    Now, the largest denomination available is 10, and the greedy approach would select as many 10s as possible before moving to the next denomination. Therefore, in the greedy approach, the number of 10s used is maximized.

    In the alternative solution with fewer coins (N_alternative), we can't use more 10s than the greedy approach because there are no smaller denominations. So, N_alternative should use the same or fewer 10s than N_greedy.

    Hence, N_alternative ≤ N_greedy, which contradicts our assumption that N_alternative < N_greedy. Therefore, our initial assumption is false, and the greedy approach of repeatedly choosing the largest denomination less than or equal to the remaining amount yields an optimal solution for denominations {5, 10}.

    In conclusion, the greedy approach is optimal for denominations {5, 10} because it maximizes the use of the largest denomination and yields the fewest number of coins for any target value T. 
*/