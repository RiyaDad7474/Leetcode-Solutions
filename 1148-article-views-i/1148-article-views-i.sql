# Write your MySQL query statement below
SELECT DISTINCT author_id as id 
From Views
where author_id = viewer_id
ORDER BY id;