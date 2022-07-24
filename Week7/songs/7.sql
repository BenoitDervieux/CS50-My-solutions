select avg(songs.energy) from songs, artists where songs.artist_id = artists.id and artists.name = 'Drake';
