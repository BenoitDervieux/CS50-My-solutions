select people.name from people, movies, stars where movies.title = 'Toy Story' and people.id = stars.person_id and stars.movie_id=movies.id;
