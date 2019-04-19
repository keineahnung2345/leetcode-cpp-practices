#Runtime: 184 ms, faster than 87.67% of MySQL online submissions for Classes More Than 5 Students.
#Memory Usage: N/A
# Write your MySQL query statement below
# use 'having' instead of 'where' if you want to compare the result from 'group by'
# use 'count(distinct `col_name`)' to get the count of unique elements
select `class` from `courses` group by `class` having count(distinct `student`) >= 5

# other solution: using sub-query
# Runtime: 201 ms, faster than 54.20% of MySQL online submissions for Classes More Than 5 Students.
# Memory Usage: N/A
select `class` 
from (select `class`, count(distinct `student`) as `num`
     from `courses`
     group by `class`) as `tmp_table` 
where `num` >= 5;
