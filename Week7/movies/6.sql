select avg(ratings.rating) from movies, ratings where ratings.movie_id = movies.id and movies.year = 2012;
