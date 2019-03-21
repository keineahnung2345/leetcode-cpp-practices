/**
SQL Schema
Write a SQL query to find all duplicate emails in a table named Person.

+----+---------+
| Id | Email   |
+----+---------+
| 1  | a@b.com |
| 2  | c@d.com |
| 3  | a@b.com |
+----+---------+
For example, your query should return the following for the above table:

+---------+
| Email   |
+---------+
| a@b.com |
+---------+
Note: All emails are in lowercase.
**/

//Runtime: 204 ms, faster than 35.61% of MySQL online submissions for Duplicate Emails.
# Write your MySQL query statement below
select `Email` from `Person` group by `Email` having count(*)>1

/**
Approach I: Using GROUP BY and a temporary table [Accepted]
Algorithm

Duplicated emails existed more than one time. To count the times each email exists, we can use the following code.

select Email, count(Email) as num
from Person
group by Email;
| Email   | num |
|---------|-----|
| a@b.com | 2   |
| c@d.com | 1   |
Taking this as a temporary table, we can get a solution as below.

select Email from
(
  select Email, count(Email) as num
  from Person
  group by Email
) as statistic
where num > 1
;
Approach II: Using GROUP BY and HAVING condition [Accepted]
A more common used way to add a condition to a GROUP BY is to use the HAVING clause, which is much simpler and more efficient.

So we can rewrite the above solution to this one.

MySQL

select Email
from Person
group by Email
having count(Email) > 1;
**/
