FROM gcc:latest
COPY . /usr/src/virna
WORKDIR /usr/src/virna
RUN g++ -o virna virna.cpp