select distinct people.name from people, movies, stars where movies.year = 2004 and people.id = stars.person_id and stars.movie_id = movies.id order by people.birth;
