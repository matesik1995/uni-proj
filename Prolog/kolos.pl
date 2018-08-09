dzielniki(X,W):-dzielniki(X,2,W).
dzielniki(X,Y,[Y|T]):-X mod Y =:= 0, Y1 is Y+1, dzielniki(X,Y1,T),!.
dzielniki(X,Y,T):-Y<X, Y1 is Y+1, dzielniki(X,Y1,T).
dzielniki(X,X,[]):-!.

sumeven([],0).
sumeven([H|T],X1):- H mod 2 =:= 0,!, sumeven(T,X), X1 is X+H.
sumeven([_|T],X):-sumeven(T,X).

sumodd([],0).
sumodd([H|T],X1):- H mod 2 =\= 0,!, sumodd(T,X), X1 is X+H.
sumodd([_|T],X):-sumodd(T,X).

sum(X,Y):- dzielniki(X,W), X mod 2 =:=0, sumeven(W,Y).
sum(X,Y):- dzielniki(X,W), X mod 2 =\=0, sumodd(W,Y).

swap([],[]).
swap([X,Y|T],[Y,X|T]):-sum(X,A), sum(Y,B), A>B.
swap([X,Y|T],[X|T2]):-sum(X,A),sum(Y,B), A=<B, swap([Y|T],T2).

bubble(X,Y):-swap(X,N),!,bubble(N,Y).
bubble(X,X).

