znajdz([X|_],X,1).
znajdz([_|T],X,Y):- znajdz(T,X,Y1), Y is Y1+1.

spr([],[]).
spr([H|T],R):-not(znajdz(T,H,_)),!,spr(T,R).
spr([H|T],[X|R]):-znajdz(T,H,X),spr(T,R).

sum([X],X).
sum([H|T],X):- sum(T,X1),X is X1+H.

srednia(W,Y):-spr(W,X), sum(X,S), length(X,L), Y is S/L.

swap([X,Y|T],[Y,X|T]):-srednia(X,A),srednia(Y,B), A>B,!.
swap([Y|T],[Y|R]):-swap(T,R).

babel(X,Y):-swap(X,N),!,X\=N,babel(N,Y).
babel(X,X).
