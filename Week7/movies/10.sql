select distinct people.name from directors, people, ratings where ratings.rating >= 9.0 and people.id = directors.person_id and directors.movie_id = ratings.movie_id;
