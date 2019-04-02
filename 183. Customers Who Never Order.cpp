# Runtime: 271 ms, faster than 39.92% of MySQL online submissions for Customers Who Never Order.
# Memory Usage: N/A

# Write your MySQL query statement below
select Name as Customers from Customers left join Orders on Customers.Id=Orders.CustomerId where Orders.CustomerId is NULL

/**
Approach: Using sub-query and NOT IN clause [Accepted]
Algorithm

If we have a list of customers who have ever ordered, it will be easy to know who never ordered.

We can use the following code to get such list.

select customerid from orders;
Then, we can use NOT IN to query the customers who are not in this list.
**/

# select Name as Customers from Customers where Customers.Id not in (select CustomerId from Orders)
