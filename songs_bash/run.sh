#!/bin/bash
START=$(date +%s.%N)
# Utworzenie schematu 'bazy':
# songs.table: [song_id, artist, title]
awk 'BEGIN {FS="<SEP>"; OFS="\t"} {print $2, $3, $4}' unique_tracks.txt \
	| sort -t$'\t' \
	| uniq > songs.table

# plays.table [user_id, song_id, NR]
# dates.table [NR, month]
cat triplets_sample_20p.txt | tee \
	>(awk 'BEGIN {FS="<SEP>"; OFS="\t"} {print $1, $2, NR}' > plays.table) \
	>(awk 'BEGIN {FS="<SEP>"; OFS="\t"} {month = strftime("%m", $3, 1); print NR, month}' > dates.table)  \
	>/dev/null

# Zapytanie 1: Ranking popularnosci piosenek 
cat plays.table \
	| awk 'BEGIN {FS="\t"; OFS="\t"} {songs[$2]++} END  {for (song in songs) {print songs[song], song}}' \
	| sort -n \
	| tail -n 10 \
	| sort -t$'\t' -k2 \
	| join -t$'\t' - songs.table -1 2 -2 1 \
	| awk 'BEGIN {FS="\t"; OFS="\t"} {print $3, $4, $2}' \
	| sort -t$'\t' -rn -k3 \
	| sed 's/\t/ /g'

# Zapytanie 2: Ranking uzytkownikow ze wzgledu na najwieksza liczbe odsluchanych piosenek
cat plays.table \
	| awk -F'\t' '!_[$1$2]++ {print $1}' \
	| uniq -c \
	| sort -nr \
	| head -n 10 \
	| awk '{print $2, $1}'

# Zapytanie 3: Artysta z najwieksza liczba odsluchan
cat plays.table \
	| awk 'BEGIN {FS="\t"; OFS="\t"} {songs[$2]++} END  {for (song in songs) {print songs[song], song}}' \
	| sort -t$'\t' -k2 \
	| join -t$'\t' - songs.table -1 2 -2 1 \
	| awk 'BEGIN {FS="\t"; OFS="\t"} {counts[$3]+=$2} END { for (artist in counts) { print artist, counts[artist]}}' \
	| sort -t$'\t' -n -k2 \
	| tail -n 1 \
	| sed 's/\t/ /'

# Zapytanie 4: Sumaryczna liczba odsluchan w podziale na poszczegolne miesiace
cat dates.table \
	| awk -F"\t" '{counts[$2]++} END {for (month in counts) { print month, counts[month]}}' \
	| sort -n 

# Zapytanie 5: Wszyscy uzytkownicy ktorzy odsluchali wszystkie trzy najbardziej popularne piosenki zespolu Queen (top10)
cat songs.table \
	| awk 'BEGIN {FS="\t"; OFS="\t"} $2=="Queen" {print $1}' \
	| grep plays.table -f - \
	| awk 'BEGIN {FS="\t"; OFS="\t"} {counts[$2]++} END {for (song in counts) { print counts[song], song}}' \
	| sort -n \
	| tail -n3 \
	| cut -f2 \
	| grep plays.table -f - \
	| cut -f1,2 \
	| uniq \
	| awk -F'\t' '{counts[$1]++} END {for (user in counts) { if (counts[user] > 2) print user}}' \
	| sort \
	| head -n 10

END=$(date +%s.%N)
DIFF=$(awk "BEGIN {print $END - $START; exit}")
#echo $DIFF
