# Runtime: 1200 ms, faster than 56.69% of MySQL online submissions for Delete Duplicate Emails.
# Memory Usage: 0B, less than 100.00% of MySQL online submissions for Delete Duplicate Emails.

# Write your MySQL query statement below
# Trial 1
# You can't specify target table 'Person' for update in FROM clause
# delete from `Person` where `Id` not in (
#    select min(`Id`) from `Person` group by `Email`
# )
# https://stackoverflow.com/questions/45494/mysql-error-1093-cant-specify-target-table-for-update-in-from-clause

delete from `Person` where `Id` not in (
    select min(`Id`) from (select * from `Person`) as `tmp` group by `Email`
)

# official sol
# Runtime: 1475 ms, faster than 28.91% of MySQL online submissions for Delete Duplicate Emails.
# Memory Usage: 0B, less than 100.00% of MySQL online submissions for Delete Duplicate Emails.
delete p1 from `Person` p1, `Person` p2 where p1.Email = p2.Email and p1.Id > p2.Id
