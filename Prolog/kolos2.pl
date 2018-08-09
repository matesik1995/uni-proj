max([X],X).
max([H|T],H):-max(T,X),H>X,!.
max([_|T],X):-max(T,X).

nth([H|_],H,1).
nth([_|T],X,N):-nth(T,X,N1), N is N1+1.

max_pos(L,X):-max(L,Y),nth(L,Y,X).

rem_r([_],[]):-!.
rem_r([H|T],[H|W]):-rem_r(T,W).
rem_l([_|T],T).

obetnij(L,W):-max_pos(L,X), length(L,Len), Len mod 2 =:=0,!, Cur is Len//2, Cur<X, rem_l(L,W1),obetnij(W1,W).
obetnij(L,W):-max_pos(L,X), length(L,Len), Len mod 2 =:=0,!, Cur is Len//2, Cur>=X, rem_r(L,W1),obetnij(W1,W).

obetnij(L,L):-max_pos(L,X), length(L,Len), Cur is Len//2+1, Cur=:=X,!.
obetnij(L,W):-max_pos(L,X), length(L,Len), Cur is Len/2, Cur<X, rem_l(L,W1),obetnij(W1,W).
obetnij(L,W):-max_pos(L,X), length(L,Len), Cur is Len/2, Cur>X, rem_r(L,W1),obetnij(W1,W).

sum([X],X).
sum([H|T],X):-sum(T,X1), X is H+X1.
srednia(L,W):-obetnij(L,X),sum(X,S), length(X,I), W is S/I.


swap([],[]).
swap([X,Y|T],[Y,X|T]):-srednia(X,A),srednia(Y,B),A>B.
swap([X,Y|T],[X|R]):-X=<Y, swap([Y|T],R).

babel(X,Y):-swap(X,N),!, babel(N,Y).
babel(X,X).
