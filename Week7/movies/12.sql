select movies.title from movies, people, stars where movies.id = stars.movie_id and people.id = stars.person_id and people.name = 'Johnny Depp' intersect select movies.title from movies, people, stars where movies.id = stars.movie_id and people.id = stars.person_id and people.name = 'Helena Bonham Carter';