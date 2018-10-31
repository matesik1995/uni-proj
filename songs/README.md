# Lab 3 Data processing in Databases - python and in memory sqlite3 database
## Requirements:
As this solution keeps database in RAM you should ensure that before running app you have at least 4GB of free memory on your machine. Not fulfilling this requirement will slow processing down as SWAP memory will be used which is not the intention of the project.

## Dataset:
Reduced Million Song Dataset is used within this project. It can be downloaded from following addresses and should be unpacked next to project files.
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

## Results:

Total execution time takes ~240 seconds on my machine (i5 4210H, 8GB ram)
Creating separate dimension table for data field takes much more space, time and do not improve total execution, so it was abadoned.
```
Dwight Yoakam You're The One 145267
Björk Undo 129778
Kings Of Leon Revelry 105162
Harmonia Sehr kosmisch 84981
Barry Tuckwell/Academy of St Martin-in-the-Fields/Sir Neville Marriner Horn Concerto No. 4 in E flat K495: II. Romance (Andante cantabile) 77632
Florence + The Machine Dog Days Are Over (Radio Edit) 71300
OneRepublic Secrets 58472
Five Iron Frenzy Canada 54655
Tub Ring Invalid 53494
Sam Cooke Ain't Misbehavin 49073
ec6dfcf19485cb011e0b22637075037aae34cf26 1040
119b7c88d58d0c6eb051365c103da5caf817bea6 641
b7c24f770be6b802805ac0e2106624a517643c17 637
4e73d9e058d2b1f2dba9c1fe4a8f416f9f58364f 592
d7d2d888ae04d16e994d6964214a1de81392ee04 586
6d625c6557df84b60d90426c0116138b617b9449 584
113255a012b2affeab62607563d03fbdf31b08e7 561
c1255748c06ee3f6440c51c439446886c7807095 547
db6a78c78c9239aba33861dae7611a6893fb27d5 529
99ac3d883681e21ea68071019dba828ce76fe94d 499
Coldplay 201081
01 2353423
02 2142793
03 2354696
04 2280733
05 2358146
06 2277770
07 2353362
08 2354811
09 2281371
10 2355043
11 2278369
12 2338840
00832bf55ed890afeb2b163024fbcfaf58803098
01cb7e60ba11f9b96e9899dd8da74c277145066e
0ac20218b5168c10b8075f1f8d4aff2746a2da39
1084d826f98b307256723cc5e9a3590600b87399
11abd6aaa54a50ed5575e8af9a485db752b97b42
28daf225834bae38f86555c8a03bca3bbf0e535d
429303f0cacab81f0c03ddfd7c2d472c8373e130
476a5902414891326ebcd8f6d9b5849f462704fa
4cd2428f7bfcff1e2423bbdfc1437a1572c23700
5283f472d868bfac68805acb83f35fd7142e3afd
```
