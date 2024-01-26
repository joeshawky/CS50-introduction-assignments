SELECT DISTINCT people.name FROM people
JOIN movies
JOIN directors on directors.person_id = people.id AND  directors.movie_id = movies.id
JOIN ratings on ratings.movie_id = movies.id
WHERE ratings.rating >= 9.0;
