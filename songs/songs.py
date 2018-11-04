import sqlite3
import timeit
import logging
import sys

if len(sys.argv) > 1:
    logging.basicConfig(level=sys.argv[1].upper())
log = logging.getLogger()


def create_songs_table(conn):
    log.info("Creating songs table from `unique_tracks.txt`")
    c = conn.cursor()

    start_time = timeit.default_timer()

    c.execute("""
    CREATE TABLE songs (
    song_id TEXT PRIMARY KEY, 
    band TEXT, 
    title TEXT
    );
    """)

    with open("unique_tracks.txt", encoding='ISO-8859-2') as f:
        for line in f:
            c.execute("INSERT OR IGNORE INTO songs VALUES (?, ?, ?);", line[:-1].split("<SEP>")[1:])
    elapsed = timeit.default_timer() - start_time

    c.close()

    log.info("Elapsed time: %s", elapsed)


def create_plays_table(conn):
    log.info("Creating plays table from `triplets_sample_20p.txt`")
    c = conn.cursor()

    start_time = timeit.default_timer()

    c.execute("""
    CREATE TABLE plays (
    user_id TEXT, 
    song_id TEXT, 
    play_date INTEGER,
    FOREIGN KEY (song_id) REFERENCES songs(song_id)
    );
    """)

    with open("triplets_sample_20p.txt", encoding='ISO-8859-2') as f:
        for line in f:
            c.execute("INSERT INTO plays VALUES (?, ?, ?);", line[:-1].split("<SEP>"))

    c.execute("CREATE INDEX plays_idx_song_id ON plays(song_id);")

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
    create_songs_table(conn)
    create_plays_table(conn)

    queries = [
        "SELECT S.title, S.band, COUNT() FROM plays P NATURAL JOIN songs S GROUP BY P.song_id ORDER BY COUNT() DESC LIMIT 10;",
        "SELECT user_id, COUNT(DISTINCT song_id) AS c FROM plays GROUP BY user_id ORDER BY c DESC LIMIT 10;",
        "SELECT S.band, COUNT() AS c FROM plays P NATURAL JOIN songs S GROUP BY band ORDER BY c DESC LIMIT 1;",
        "SELECT strftime('%m', play_date, 'unixepoch') AS m, COUNT() FROM plays GROUP BY m ORDER BY m;",
        "SELECT user_id FROM plays WHERE song_id IN (SELECT S.song_id FROM songs S NATURAL JOIN plays P WHERE S.band = 'Queen' GROUP BY S.song_id ORDER BY COUNT() DESC LIMIT 3) GROUP BY user_id HAVING COUNT(DISTINCT song_id) = 3 ORDER BY user_id LIMIT 10;"
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
