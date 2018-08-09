%s³ownik
hex(10,a):-!.
hex(11,b):-!.
hex(12,c):-!.
hex(13,d):-!.
hex(14,e):-!.
hex(15,f):-!.
hex(X,X):-X<10.

%decimal to hexidecimal
dTh(0,[]):-!.
dTh(X,[H|T]):-H1 is X mod 16, hex(H1,H), X1 is X//16, dTh(X1,T).

%cut letters
cut([],[]).
cut([H|T],[H|R]):-hex(X,H), X<10,!, cut(T,R).
cut([_|T],R):-cut(T,R).

%hex to dec
hTd([],0,0).
hTd([H|T],N,X):-hTd(T,N1,X1),X is X1+H*16**N1, N is N1+1.
hTd(L,X):-hTd(L,_,X).

%wyznaczanie klucza
key(X,W):-dTh(X,Y), cut(Y,Z), hTd(Z,W).

swap([X,Y|T],[Y,X|T]):-key(X,A),key(Y,B),A>B,!.
swap([Y|T],[Y|R]):-swap(T,R).

bubble(X,Y):-swap(X,N),!,bubble(N,Y).
bubble(X,X).
