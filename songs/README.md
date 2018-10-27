# Lab 3 Data processing in Databases using python and in memory sqlite3 database
## Requirements:
As this soultion keeps database in RAM you should ensure that before running app you have at least 4GB of free memory on your machine. Not fulfiling this requirement will slow processing down as SWAP memory will be used which is not the intention of script.

## Dataset:
Reduced Million Song Dataset is used by this project. It can be downloaded from following links and should be unpacked.
```
http://www.cs.put.poznan.pl/kdembczynski/lectures/data/unique_tracks.zip
http://www.cs.put.poznan.pl/kdembczynski/lectures/data/triplets_sample_20p.zip
```

## To build:
```
docker build -t python_sqlite_in_memory .
```

## To run the container:
```
docker run --name python_sqlite_in_memory_container python_sqlite_in_memory
```

## To stop and remove the container:
```
docker stop python_sqlite_in_memory_container
docker rm python_sqlite_in_memory_container
```
