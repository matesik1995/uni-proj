import sqlite3
import timeit
import logging
import sys

if len(sys.argv) > 1:
    logging.basicConfig(level=sys.argv[1].upper())
log = logging.getLogger()


def feed_table(conn, filename, query):
    log.info("Feeding table from: %s", filename)

    c = conn.cursor()

    start_time = timeit.default_timer()
    with open(filename, encoding='ISO-8859-2') as f:
        for line in f:
            c.execute(query, line[:-1].split("<SEP>"))
    elapsed = timeit.default_timer() - start_time

    c.close()

    log.info("Elapsed time: %s", elapsed)


def execute_query(conn, query):
    log.info("Exceuting query: %s", query)

    c = conn.cursor()

    start_time = timeit.default_timer()
    c.execute(query)
    elapsed = timeit.default_timer() - start_time
    result = c.fetchall()

    log.info("Elapsed time: %s", elapsed)

    if log.isEnabledFor(logging.DEBUG):
        if not query.startswith("CREATE"):
            c.execute("EXPLAIN QUERY PLAN " + query)
            log.debug(c.fetchall())

    c.close()

    return result


def print_result(result):
    for line in result:
        print(*line)


def main():
    log.info("Connecting to database")
    conn = sqlite3.connect(":memory:")
    # conn = sqlite3.connect("database.sqlite")

    start_time = timeit.default_timer()

    execute_query(conn, "CREATE TABLE songs (track_id TEXT, song_id TEXT, band TEXT, title TEXT);")
    feed_table(conn, "unique_tracks.txt", "INSERT INTO songs VALUES (?, ?, ?, ?);")
    execute_query(conn, "CREATE INDEX songs_idx_song_id ON songs(song_id);")

    execute_query(conn, "CREATE TABLE plays (user_id BLOB, song_id TEXT, play_date INTEGER);")
    feed_table(conn, "triplets_sample_20p.txt", "INSERT INTO plays VALUES (?, ?, ?);")
    execute_query(conn, "CREATE INDEX plays_idx_song_id ON plays(song_id);")

    queries = [
        "SELECT S.band, S.title, COUNT() FROM plays P JOIN songs S ON P.song_id = S.song_id GROUP BY P.song_id ORDER BY COUNT() DESC LIMIT 10;",
        "SELECT user_id, COUNT(DISTINCT song_id) AS c FROM plays GROUP BY user_id ORDER BY c DESC LIMIT 10;",
        "SELECT S.band, COUNT() AS c FROM plays P JOIN (SELECT DISTINCT band, song_id FROM songs) S ON P.song_id = S.song_id GROUP BY band ORDER BY c DESC LIMIT 1;",
        "SELECT strftime('%m', play_date, 'unixepoch') AS m, COUNT() FROM plays GROUP BY m ORDER BY m;",
        "SELECT user_id FROM plays WHERE song_id IN (SELECT S.song_id FROM songs S JOIN plays P ON S.song_id = P.song_id WHERE S.band = 'Queen' GROUP BY S.song_id ORDER BY COUNT() DESC LIMIT 3) GROUP BY user_id HAVING COUNT(DISTINCT song_id) = 3 ORDER BY user_id LIMIT 10;"
    ]
    for query in queries:
        result = execute_query(conn, query)
        print_result(result)

    elapsed = timeit.default_timer() - start_time
    log.info("Total time elapsed: %s", elapsed)

    log.info("Closing connection")
    conn.close()


if __name__ == "__main__":
    main()
