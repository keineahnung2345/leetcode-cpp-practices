/**
There is a table World

+-----------------+------------+------------+--------------+---------------+
| name            | continent  | area       | population   | gdp           |
+-----------------+------------+------------+--------------+---------------+
| Afghanistan     | Asia       | 652230     | 25500100     | 20343000      |
| Albania         | Europe     | 28748      | 2831741      | 12960000      |
| Algeria         | Africa     | 2381741    | 37100000     | 188681000     |
| Andorra         | Europe     | 468        | 78115        | 3712000       |
| Angola          | Africa     | 1246700    | 20609294     | 100990000     |
+-----------------+------------+------------+--------------+---------------+
A country is big if it has an area of bigger than 3 million square km or a population of more than 25 million.

Write a SQL solution to output big countries' name, population and area.

For example, according to the above table, we should output:

+--------------+-------------+--------------+
| name         | population  | area         |
+--------------+-------------+--------------+
| Afghanistan  | 25500100    | 652230       |
| Algeria      | 37100000    | 2381741      |
+--------------+-------------+--------------+
**/

/**
Solution
Approach I: Using WHERE clause and OR [Accepted]
Intuition

Use WHERE clause in SQL to filter these records and get the target countries.

Algorithm

According to the definition, a big country meets at least one of the following two conditions: 1. It has an area of bigger than 3 million square km. 2. It has a population of more than 25 million.

So for the first condition, we can use the following code to get the big countries of this type.

SELECT name, population, area FROM world WHERE area > 3000000
In addition, we can use below code to get big countries of more than 25 million people.

SELECT name, population, area FROM world WHERE population > 25000000
As most people may already come into mind, we can use OR to combine these two solutions for the two sub-problems together.

MySQL

SELECT
    name, population, area
FROM
    world
WHERE
    area > 3000000 OR population > 25000000
;
Approach II: Using WHERE clause and UNION [Accepted]
Algorithm

The idea of this approach is the same as the first one. However, we use UNION instead of OR.

MySQL

SELECT
    name, population, area
FROM
    world
WHERE
    area > 3000000

UNION

SELECT
    name, population, area
FROM
    world
WHERE
    population > 25000000
;
Note: This solution runs a little bit faster than the first one. However, they do not have big difference.
**/

# Your runtime beats 56.72 % of mysql submissions.
# Write your MySQL query statement below
select `name`,`population`,`area` from `World` where `population`>25000000 or `area`>3000000

# Your runtime beats 80.43 % of mysql submissions.
# Write your MySQL query statement below
SELECT name, population, area FROM world WHERE area > 3000000
UNION
SELECT name, population, area FROM world WHERE population > 25000000;
