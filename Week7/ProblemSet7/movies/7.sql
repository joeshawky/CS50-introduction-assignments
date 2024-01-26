SELECT movies.title AS movie_title, ratings.rating AS movie_rating FROM movies
JOIN ratings on ratings.movie_id = movies.id
WHERE movies.year = 2010
ORDER BY movie_rating DESC, movie_title ASC;
