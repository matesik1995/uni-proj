FROM python:3-slim

# Set working dir
WORKDIR .

# Copy dataset to working dir
COPY unique_tracks.txt .
COPY triplets_sample_20p.txt .

# Copy your code
COPY songs.py .

# Set starting command (run your code)
CMD python songs.py
