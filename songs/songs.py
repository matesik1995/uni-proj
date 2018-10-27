import sqlite3
import timeit
import logging
import sys

if len(sys.argv) > 1:
    logging.basicConfig(level=sys.argv[1].upper())
log = logging.getLogger()


def init_songs_table(conn):
    log.info("Creating songs table")

    c = conn.cursor()
    start_time = timeit.default_timer()
    c.execute("""
    CREATE TABLE IF NOT EXISTS songs (
    track_id TEXT, 
    song_id TEXT, 
    band TEXT, 
    title TEXT
    );""")
    with open("unique_tracks.txt", encoding='ISO-8859-2') as f:
        for line in f:
            c.execute("INSERT INTO songs VALUES (?, ?, ?, ?)", line[:-1].split("<SEP>"))
    c.execute("CREATE INDEX songs_idx_song_id ON songs(song_id)")
    conn.commit()
    elapsed = timeit.default_timer() - start_time

    log.info("Elapsed time: %s", elapsed)


def init_plays_table(conn):
    log.info("Creating plays table")

    c = conn.cursor()
    start_time = timeit.default_timer()
    c.execute("""
    CREATE TABLE IF NOT EXISTS plays (
    user_id BLOB, 
    song_id TEXT, 
    play_date INTEGER
    );""")
    with open("triplets_sample_20p.txt") as f:
        for line in f:
            c.execute("INSERT INTO plays VALUES (?, ?, ?)", line[:-1].split("<SEP>"))
    c.execute("CREATE INDEX plays_idx_song_id ON plays(song_id)")
    conn.commit()
    elapsed = timeit.default_timer() - start_time

    log.info("Elapsed time: %s", elapsed)


def songs_top_ten(conn):
    log.info("Exceuting `songs_top_ten` query")

    c = conn.cursor()
    query = "SELECT S.band, S.title, COUNT() FROM plays P JOIN songs S ON P.song_id = S.song_id GROUP BY P.song_id ORDER BY COUNT() DESC LIMIT 10;"

    start_time = timeit.default_timer()
    c.execute(query)
    elapsed = timeit.default_timer() - start_time
    result = c.fetchall()

    log.info("Elapsed time: %s", elapsed)

    if log.isEnabledFor(logging.DEBUG):
        c.execute("EXPLAIN QUERY PLAN " + query)
        log.debug(c.fetchall())

    return result


def user_top_ten_unique_songs(conn):
    log.info("Exceuting `user_top_ten_unique_songs` query")

    c = conn.cursor()
    query = "SELECT user_id, COUNT(DISTINCT song_id) AS c FROM plays GROUP BY user_id ORDER BY c DESC LIMIT 10;"

    start_time = timeit.default_timer()
    c.execute(query)
    elapsed = timeit.default_timer() - start_time
    result = c.fetchall()

    log.info("Elapsed time: %s", elapsed)

    if log.isEnabledFor(logging.DEBUG):
        c.execute("EXPLAIN QUERY PLAN " + query)
        log.debug(c.fetchall())

    return result


def artist_top_one(conn):
    log.info("Exceuting `artist_top_one` query")

    c = conn.cursor()
    query = "SELECT band, COUNT() AS c FROM songs S JOIN plays P ON S.song_id = P.song_id GROUP BY band ORDER BY c DESC LIMIT 1;"

    start_time = timeit.default_timer()
    c.execute(query)
    elapsed = timeit.default_timer() - start_time
    result = c.fetchone()

    log.info("Elapsed time: %s", elapsed)

    if log.isEnabledFor(logging.DEBUG):
        c.execute("EXPLAIN QUERY PLAN " + query)
        log.debug(c.fetchall())

    return result


def plays_by_month(conn):
    log.info("Exceuting `plays_by_month` query")

    c = conn.cursor()
    query = "SELECT strftime('%m', play_date, 'unixepoch') AS m, COUNT() FROM plays GROUP BY m ORDER BY m;"

    start_time = timeit.default_timer()
    c.execute(query)
    elapsed = timeit.default_timer() - start_time
    result = c.fetchall()

    log.info("Elapsed time: %s", elapsed)

    if log.isEnabledFor(logging.DEBUG):
        c.execute("EXPLAIN QUERY PLAN " + query)
        log.debug(c.fetchall())

    return result


def queen_top_three(conn):
    log.info("Exceuting `queen_top_three` query")

    c = conn.cursor()
    query = "SELECT user_id FROM plays WHERE song_id IN (SELECT S.song_id FROM songs S JOIN plays P ON S.song_id = P.song_id WHERE S.band = 'Queen' GROUP BY S.song_id ORDER BY COUNT() DESC LIMIT 3) GROUP BY user_id HAVING COUNT(DISTINCT song_id) = 3;"

    start_time = timeit.default_timer()
    c.execute(query)
    elapsed = timeit.default_timer() - start_time
    result = c.fetchall()

    log.info("Elapsed time: %s", elapsed)

    if log.isEnabledFor(logging.DEBUG):
        c.execute("EXPLAIN QUERY PLAN " + query)
        log.debug(c.fetchall())

    return result


def main():
    log.info("Connecting to database")
    conn = sqlite3.connect(":memory:")
    # conn = sqlite3.connect("database.sqlite")

    start_time = timeit.default_timer()

    init_songs_table(conn)
    init_plays_table(conn)

    for a in songs_top_ten(conn):
        print(*a)

    for a in user_top_ten_unique_songs(conn):
        print(*a)

    print(*artist_top_one(conn))

    for a in plays_by_month(conn):
        print(*a)

    for a in queen_top_three(conn):
        print(*a)

    elapsed = timeit.default_timer() - start_time
    log.info("Total time elapsed: %s", elapsed)

    log.info("Closing connection")
    conn.close()


if __name__ == "__main__":
    main()
