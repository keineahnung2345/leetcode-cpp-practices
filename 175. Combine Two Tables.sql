/**
Table: Person

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| PersonId    | int     |
| FirstName   | varchar |
| LastName    | varchar |
+-------------+---------+
PersonId is the primary key column for this table.
Table: Address

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| AddressId   | int     |
| PersonId    | int     |
| City        | varchar |
| State       | varchar |
+-------------+---------+
AddressId is the primary key column for this table.
 

Write a SQL query for a report that provides the following information for each person in the Person table, regardless if there is an address for each of those people:

FirstName, LastName, City, State
**/

#Runtime: 220 ms, faster than 53.98% of MySQL online submissions for Combine Two Tables.
#Memory Usage: N/A
# Write your MySQL query statement below
select `FirstName`, `LastName`, `City`, `State` from `Person` left join `Address` on Person.PersonId=Address.PersonId
