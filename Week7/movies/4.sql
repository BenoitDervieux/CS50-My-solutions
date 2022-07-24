select count(movies.title) from movies, ratings where (ratings.rating = 10) and ratings.movie_id = movies.id;
