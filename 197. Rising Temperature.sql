# Approach: Using JOIN and DATEDIFF() clause [Accepted]
# Runtime: 325 ms, faster than 71.99% of MySQL online submissions for Rising Temperature.
# Memory Usage: N/A
# Write your MySQL query statement below
select 
    Weather.Id as `Id`
from
    `Weather`
        join
    `Weather` w on datediff(Weather.RecordDate, w.RecordDate) = 1
        and Weather.Temperature > w.Temperature
